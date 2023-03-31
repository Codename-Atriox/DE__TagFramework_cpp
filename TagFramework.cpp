#include "pch.h"
#include "TagFramework.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


TAG_OBJ_TYPE Opentag(string _In_tag_path, void* _Out_data)
{
	ifstream file_stream(_In_tag_path, ios::binary | ios::ate);
	if (!file_stream.is_open()){
		return FAILED_OPENING;
	}
	std::streamsize file_size = file_stream.tellg();

	if (file_size < tag_header_size){
		return FAILED_SIZE;
	}

	char* tag_bytes = new char[file_size];
	file_stream.seekg(0, ios::beg);
	file_stream.getline(tag_bytes, file_size);

	uint64_t current_byte_offset = 0;

	// read header from bytes
	tag_header* header = reinterpret_cast<tag_header*>(&tag_bytes[0]);
	current_byte_offset += tag_header_size;
	if (header->Magic != 1752392565) {
		return FAILED_MAGIC;
	}

	// index each significant block
	uint64_t tag_dependencies_offset = current_byte_offset;
	current_byte_offset += header->DependencyCount * tag_dependency_size;

	uint64_t data_blocks_offset = current_byte_offset;
	current_byte_offset += header->DataBlockCount * data_block_size;

	uint64_t tag_structs_offset = current_byte_offset;
	current_byte_offset += header->TagStructCount * tag_def_structure_size;

	uint64_t data_references_offset = current_byte_offset;
	current_byte_offset += header->DataReferenceCount * data_reference_size;

	uint64_t tag_fixup_references_offset = current_byte_offset;
	current_byte_offset += header->DataReferenceCount * data_reference_size;

	uint64_t string_table_offset = current_byte_offset;
	current_byte_offset += header->StringTableSize;

	uint64_t zoneset_info_offset = current_byte_offset;
	current_byte_offset += header->ZoneSetDataSize; // unsure if this includes the header or just all the elements

	// current_byte_offset now serves as whatever comes after that point
	// ok now we need to get the offsets for the 3 extra blocks (or was it two?) although these can be calculated inplace rather easily as they're only one long + another

	uint64_t data_1_offset = header->HeaderSize;
	uint64_t data_2_offset = header->HeaderSize + header->DataSize;
	uint64_t data_3_offset = header->HeaderSize + header->DataSize + header->ResourceDataSize;

	// now we note any unmapped data segments in the file
	if (data_3_offset + header->ActualResoureDataSize != file_size)
	{

	}

	// first we should figure out the tag type, which we can do by looking through the tag structs 
	// and seeing which is the root, the guid will tell us which tag this is
	uint64_t target_group = 0;

	for (uint32_t c = 0; c < header->TagStructCount; c++) {
		tag_def_structure* curr_struct = reinterpret_cast<tag_def_structure*>(&tag_bytes[tag_structs_offset + (c * tag_def_structure_size)]);
		if (curr_struct->Type != 0) continue;

		target_group = curr_struct->GUID_1 ^ curr_struct->GUID_2;
		break;
	}

	if (target_group == 0) 
		return FAILED_GUID;

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
		resulting_group = bitmap;

		char byte[32];
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


	return resulting_group;
}