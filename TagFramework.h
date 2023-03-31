// TagFramework.h - Contains the logic for reading tag files into renderable objects
#pragma once
#include <string>
#include <map>
#include <stdint.h>

#ifdef TAGFRAMEWORKCPP_EXPORTS
#define TAGFRAMEWORK_API __declspec(dllexport)
#else
#define TAGFRAMEWORK_API __declspec(dllimport)
#endif

using namespace std;

// this defines the possible data type output from reading a tag file
// if its none of these, then the data will be discarded as we have no use for it
// thus returning a nullptr
enum TAG_OBJ_TYPE
{
    FAILED_OPENING,
    FAILED_SIZE,
    FAILED_MAGIC,
    FAILED_GUID,
	NONE,
	bitmap,
	render_model,
	physics_model,
	collision_model,
	bsp,
	runtime_geo,
	terrain,
	level
};
// the structures for each of these will be included in separate .h files, so they may be more easily regenerated in the instance of a structure change by 343

// this function will be the do all open tag file and return data object if possible
extern "C" TAGFRAMEWORK_API TAG_OBJ_TYPE Opentag(string _In_tag_path, void* _Out_data);



// /////////////////// //
// TAG FILE STRUCTURES //
// /////////////////// // 

// //////////////////////////////// //
// NOTES CAN BE FOUND IN C:A EDITOR //
// //////////////////////////////// //

const unsigned int tag_header_size               = 0x50;
const unsigned int tag_dependency_size           = 0x18;
const unsigned int data_block_size               = 0x10;
const unsigned int tag_def_structure_size        = 0x20;
const unsigned int data_reference_size           = 0x14;
const unsigned int tag_fixup_reference_size      = 0x10;
const unsigned int zoneset_header_size           = 0x10;
const unsigned int zoneset_instance_header_size  = 0x10;
const unsigned int zoneset_tag_size              = 0x08;
#pragma pack(push, 1)
struct tag_header{
    uint32_t        Magic;
    uint32_t        Version;
    uint64_t        Unk_0x08;
    uint64_t        AssetChecksum;
    uint32_t        DependencyCount;
    uint32_t        DataBlockCount;
    uint32_t        TagStructCount;
    uint32_t        DataReferenceCount;
    uint32_t        TagReferenceCount;
    uint32_t        StringTableSize;
    uint32_t        ZoneSetDataSize;   
    uint32_t        Unk_0x34; 
    uint32_t        HeaderSize;
    uint32_t        DataSize;
    uint32_t        ResourceDataSize;
    uint32_t        ActualResoureDataSize; 
    uint8_t         HeaderAlignment;
    uint8_t         TagDataAlightment;
    uint8_t         ResourceDataAligment;
    uint8_t         ActualResourceDataAligment;
    uint32_t        Unk_0x4C;
};
struct tag_dependency{
    uint32_t        GroupTag;
    uint32_t        NameOffset;
    uint64_t        AssetID;
    uint32_t        GlobalID;
    uint32_t        Unk_0x14;
};
struct data_block{
    uint32_t        Size;
    uint16_t        Unk_0x04;
    uint16_t        Section;
    uint64_t        Offset;
};
struct tag_def_structure{
    uint64_t        GUID_1;
    uint64_t        GUID_2;
    uint16_t        Type;
    uint16_t        Unk_0x12;
    int32_t         TargetIndex;
    int32_t         FieldBlock;
    uint32_t        FieldOffset;
};
struct data_reference{
    int32_t         ParentStructIndex;
    int32_t         Unk_0x04;
    int32_t         TargetIndex;
    int32_t         FieldBlock;
    uint32_t        FieldOffset;
};
struct tag_fixup_reference{
    int32_t         FieldBlock;
    uint32_t        FieldOffset;
    uint32_t        NameOffset;
    int32_t         DepdencyIndex;
};
// realistically doesn't need structures as we're not reading this information
struct zoneset_header {
    int32_t         Unk_0x00;
    int32_t         ZonesetCount;
    int32_t         Unk_0x08;
    int32_t         Unk_0x0C;
};
struct zoneset_instance_header{
    int32_t         StringID;
    int32_t         TagCount;
    int32_t         ParentCount;
    int32_t         FooterCount;
};
struct zoneset_tag {
    uint32_t        GlobalID;
    int32_t         StringID;
};
#pragma pack(pop)