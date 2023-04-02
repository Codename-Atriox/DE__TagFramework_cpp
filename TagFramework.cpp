#include "pch.h"
#include "TagFramework.h"
#include "TagStructs/bitm.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
class tag_loading_offsets{
public:
	uint64_t tag_dependencies_offset;
	uint64_t data_blocks_offset;
	uint64_t tag_structs_offset;
	uint64_t data_references_offset;
	uint64_t tag_fixup_references_offset;
	uint64_t string_table_offset;
	uint64_t zoneset_info_offset;
	uint64_t data_1_offset; // tag data
	uint64_t data_2_offset; // resource data
	uint64_t data_3_offset; // alt resource data
};

static uint64_t resolve_datablock_offset(data_block* datar, tag_loading_offsets* offsets)
{
	if (datar->Section == 0) return datar->Offset;
	else if (datar->Section == 1) return offsets->data_1_offset + datar->Offset;
	else if (datar->Section == 2) return offsets->data_2_offset + datar->Offset;
	else if (datar->Section == 3) return offsets->data_3_offset + datar->Offset;
}
TAG_OBJ_TYPE Opentag(string _In_tag_path, void* _Out_data)
{
	ifstream file_stream(_In_tag_path, ios::binary | ios::ate);
	if (!file_stream.is_open()){
		return FAILED_OPENING;
	}
	ifstream::pos_type file_size = file_stream.tellg(); // need to rever this to whatever else this was before i think
	

	if (file_size < tag_header_size){
		return FAILED_SIZE;
	}

	char* tag_bytes = new char[file_size];
	file_stream.seekg(0, ios::beg);
	file_stream.read(tag_bytes, file_size);

	uint64_t current_byte_offset = 0;

	// read header from bytes
	tag_header* header = reinterpret_cast<tag_header*>(&tag_bytes[0]);
	current_byte_offset += tag_header_size;
	if (header->Magic != 1752392565) {
		delete tag_bytes;
		return FAILED_MAGIC;
	}

	tag_loading_offsets* offsets = new tag_loading_offsets();
	// index each significant block
	offsets->tag_dependencies_offset = current_byte_offset;
	current_byte_offset += header->DependencyCount * tag_dependency_size;

	offsets->data_blocks_offset = current_byte_offset;
	current_byte_offset += header->DataBlockCount * data_block_size;

	offsets->tag_structs_offset = current_byte_offset;
	current_byte_offset += header->TagStructCount * tag_def_structure_size;

	offsets->data_references_offset = current_byte_offset;
	current_byte_offset += header->DataReferenceCount * data_reference_size;

	offsets->tag_fixup_references_offset = current_byte_offset;
	current_byte_offset += header->DataReferenceCount * data_reference_size;

	offsets->string_table_offset = current_byte_offset;
	current_byte_offset += header->StringTableSize;

	offsets->zoneset_info_offset = current_byte_offset;
	current_byte_offset += header->ZoneSetDataSize; // unsure if this includes the header or just all the elements

	// current_byte_offset now serves as whatever comes after that point
	// ok now we need to get the offsets for the 3 extra blocks (or was it two?) although these can be calculated inplace rather easily as they're only one long + another

	offsets->data_1_offset = header->HeaderSize;
	offsets->data_2_offset = header->HeaderSize + header->DataSize;
	offsets->data_3_offset = header->HeaderSize + header->DataSize + header->ResourceDataSize;

	// now we note any unmapped data segments in the file
	if (offsets->data_3_offset + header->ActualResoureDataSize != file_size)
	{

	}

	// first we should figure out the tag type, which we can do by looking through the tag structs 
	// and seeing which is the root, the guid will tell us which tag this is
	uint64_t target_group = 0;
	tag_def_structure* root_struct = nullptr; // we need this guy so we know which datablock is the root

	for (uint32_t c = 0; c < header->TagStructCount; c++) {
		tag_def_structure* curr_struct = reinterpret_cast<tag_def_structure*>(&tag_bytes[offsets->tag_structs_offset + (c * tag_def_structure_size)]);
		if (curr_struct->Type != 0) continue;

		target_group = curr_struct->GUID_1 ^ curr_struct->GUID_2;
		root_struct = curr_struct;
		break;
	}

	if (target_group == 0){
		delete tag_bytes;
		delete offsets;
		return FAILED_GUID;
	}

	// lets do runtime fixups on the file now
	// fixup tag definition structures
	for (uint32_t c = 0; c < header->TagStructCount; c++){
		tag_def_structure* current_struct = reinterpret_cast<tag_def_structure*> (&tag_bytes[offsets->tag_structs_offset + (c * tag_def_structure_size)]);
		if (current_struct->FieldBlock == -1) continue; // we dont need to give the main struct's pointer to anything as we already have it
		data_block* datar = reinterpret_cast<data_block*> (&tag_bytes[offsets->data_blocks_offset + (current_struct->FieldBlock * data_block_size)]);

		// we have to write the offset differently, depending on what type of struct this is
		if (current_struct->Type == 1 || current_struct->Type == 3){ // struct or custom?
			_basic_tagblock* tagblock = reinterpret_cast<_basic_tagblock*>(& tag_bytes[resolve_datablock_offset(datar, offsets) + current_struct->FieldOffset]);
			if (current_struct->TargetIndex != -1){
				data_block* contained_datar = reinterpret_cast<data_block*> (&tag_bytes[offsets->data_blocks_offset + (current_struct->TargetIndex * data_block_size)]);
				tagblock->content_ptr = &tag_bytes[resolve_datablock_offset(contained_datar, offsets)];
			} else tagblock->content_ptr = nullptr;
		} else if (current_struct->Type == 2){ // resource
			// we're not going to read external types right now
			_basic_resource* resource = reinterpret_cast<_basic_resource*>(&tag_bytes[resolve_datablock_offset(datar, offsets) + current_struct->FieldOffset]);
			if (resource->is_chunked_resource == 0)
			{
				// we dont currently support tagblocks
			}
			else
			{
				if (current_struct->TargetIndex != -1) {
					data_block* contained_datar = reinterpret_cast<data_block*> (&tag_bytes[offsets->data_blocks_offset + (current_struct->TargetIndex * data_block_size)]);
					resource->content_ptr = &tag_bytes[resolve_datablock_offset(contained_datar, offsets)];
				}
				else resource->content_ptr = nullptr;
			}
		}else{ // unknown
		

		}
	}
	// fixup data references
	for (uint32_t c = 0; c < header->DataReferenceCount; c++)
	{
		data_reference* current_datar = reinterpret_cast<data_reference*>(&tag_bytes[offsets->data_references_offset + (c * data_reference_size)]);
		data_block* datar = reinterpret_cast<data_block*> (&tag_bytes[offsets->data_blocks_offset + (current_datar->FieldBlock * data_block_size)]);

		// we have to write the offset differently, depending on what type of struct this is
		_basic_data* _datarblock = reinterpret_cast<_basic_data*>(&tag_bytes[resolve_datablock_offset(datar, offsets) + current_datar->FieldOffset]);
		if (current_datar->TargetIndex != -1) {
			data_block* contained_datar = reinterpret_cast<data_block*> (&tag_bytes[offsets->data_blocks_offset + (current_datar->TargetIndex * data_block_size)]);
			_datarblock->content_ptr = &tag_bytes[resolve_datablock_offset(contained_datar, offsets)];
		} else _datarblock->content_ptr = nullptr;
	}
	// fixup tag references
	/*
	for (uint32_t c = 0; c < header->TagReferenceCount; c++)
	{
		tag_fixup_reference* current_struct = reinterpret_cast<tag_fixup_reference*> (&tag_bytes[offsets->tag_fixup_references_offset + (c * tag_fixup_reference_size)]);


	}
	*/

	/*
		mode: 13546876791234752572
		rtgo: 4657725475941061082
		bitm: 1236057003492058159
		levl: 9265759122008847170
	*/
	TAG_OBJ_TYPE resulting_group = NONE;
	switch (target_group)
	{
	case 1236057003492058159: // bitmap
		{

			resulting_group = bitmap;

			data_block* root_datar = reinterpret_cast<data_block*> (&tag_bytes[offsets->data_blocks_offset + (root_struct->TargetIndex * data_block_size)]);
			BitmapGroup* bitmapa = reinterpret_cast<BitmapGroup*> (&tag_bytes[resolve_datablock_offset(root_datar, offsets)]);

			//char byte[32];
			string poop_Farty = "test";
		}
		break;
	case 4657725475941061082: // runtime geo
		resulting_group = runtime_geo;

		break;
	case 13546876791234752572: // model
		resulting_group = render_model;


		break;
	case 9265759122008847170: // level
		resulting_group = level;


		break;

	}

	delete offsets;
	return resulting_group;
}