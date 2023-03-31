/*
; CONTENT AUTOGENERATED BY CODENAME ATRIOX: PLUGIN CONVERTOR
; CONVERTOR VERSION: 0.4.0
; SOURCE TIMESTAMP: [EXAMPLE]
; SOURCE GAME VERSION: [EXAMPLE]
; SOURCE PLUGIN: bitm
; GENERATED TIMESTAMP: 3/31/2023 12:00:00 AM -> 9:44:56 AM
*/

#pragma once
#include "commons.h"
#pragma pack(push, 1)

// ///////////////// //
// STRUCT REFERENCES //
// ///////////////// //

struct BitmapGroup {
	AnyTag_struct_definition BLANK;
	uint32_t Usage;
	uint32_t UsageId;
	uint32_t Package;
	uint32_t texture_group;
	BitmapGroup__BitmapGroupFlags Flags;
	int16_t sprite_spacing;
	int16_t MIP_sample_count;
	float bump_map_height;
	float fade_factor;
	float blur;
	float mip_map_blur;
	BitmapGroup__CurveOverride curve_mode;
	int8_t max_mipmap_level;
	int16_t max_resolution;
	BitmapUsage__BitmapForcedFormat force_bitmap_format;
	BitmapGroup__SignedDistanceFieldMethod sdf_generation;
	int8_t target_platform;
	int16_t spread_factor;
	uint8_t generated_pad8ed2[2];
	_s_tagblock<BitmapUsage> usage_override;
	_s_tagblock<BitmapGroupSequence> manual_sequences;
	_s_data source_data;
	_s_tagblock<SourcePaths> source_paths;
	uint64_t source_checksum;
	_s_argbfloat min_color;
	_s_argbfloat max_color;
	_s_tagblock<BitmapGroupSequence> sequences;
	_s_tagblock<BitmapData> bitmaps;
};
struct AnyTag_struct_definition {
	int64_t vtable_space;
	s_anyTagGuts internal_struct;
};
struct BitmapUsage {
	uint32_t name;
	uint32_t editor_group;
	float source_gamma;
	BitmapCurve bitmap_curve;
	BitmapUsage__BitmapUsageFlag flags;
	BitmapUsage__BitmapSlicer slicer;
	BitmapUsage__BitmapDicerFlag dicer_flags;
	BitmapUsage__BitmapPacker packer;
	BitmapUsage__BitmapPackerFlag packer_flags;
	BitmapType type;
	int8_t mipmap_limit;
	BitmapUsage__BitmapSmallestMip smallest_mip;
	BitmapUsage__BitmapDownsampleFilter downsample_filter;
	int8_t filter_radius_bias;
	uint8_t generated_pad122e[1];
	BitmapUsage__BitmapDownsampleFlag downsample_flags;
	uint8_t generated_pad5ee3[2];
	_s_rgbfloat sprite_background_color;
	Floatmap__Swizzle swizzle_red;
	Floatmap__Swizzle swizzle_green;
	Floatmap__Swizzle swizzle_blue;
	Floatmap__Swizzle swizzle_alpha;
	BitmapUsage__BitmapForcedFormat bitmap_format;
	BitmapColorSpace source_color_space;
	BitmapColorSpace target_color_space;
};
struct BitmapGroupSequence {
	char name[32];
	int16_t first_bitmap_index;
	int16_t bitmap_count;
	_s_tagblock<BitmapGroupSprite> sprites;
};
struct SourcePaths {
	WWWWWWWWWWW source_path;
	_s_tagblock<BitmapSourceFile> intermediate_paths;
};
struct BitmapGroupSequence {
	char name[32];
	int16_t first_bitmap_index;
	int16_t bitmap_count;
	_s_tagblock<BitmapGroupSprite> sprites;
};
struct BitmapData {
	int16_t width;
	int16_t height;
	uint16_t depth;
	BitmapType type;
	uint8_t generated_paddca3[1];
	BitmapFormat format;
	BitmapFlags flags;
	int8_t mipmap_count;
	BitmapCurve curve;
	uint8_t generated_pad8fee[2];
	float streaming_scale;
	int16_t sourceWidth;
	int16_t sourceHeight;
	_s_resource<BitmapDataResource> bitmap_resource_handle;
};
struct s_anyTagGuts {
	int32_t global_tag_ID;
	uint8_t local_tag_handle[4];
};
struct BitmapGroupSprite {
	int16_t bitmap_index;
	uint8_t generated_pad2095[2];
	float left;
	float right;
	float top;
	float bottom;
	_s_doublefloat registration_point;
};
struct BitmapSourceFile {
	WWWWWWWWWWW path;
};
struct BitmapGroupSprite {
	int16_t bitmap_index;
	uint8_t generated_pad2095[2];
	float left;
	float right;
	float top;
	float bottom;
	_s_doublefloat registration_point;
};
struct BitmapDataResource {
	_s_data pixels;
	int32_t hardware_format;
	int8_t tileMode;
	uint8_t format;
	BitmapDataResourceFlags bitmap_data_resource_flags;
	int8_t alignmentBits;
	uint8_t highResMipCountAndFlags;
	uint8_t mipCountPerArraySlice;
	uint8_t generated_padff1b[6];
	int64_t runtime_data;
	_s_tagblock<StreamingBitmapData> streamingData;
	uint8_t generated_padb266[4];
};
struct StreamingBitmapData {
	int32_t offset;
	int32_t size;
	int32_t chunkInfo;
	int32_t dimensions;
};

// /////////////// //
// FLAG REFERENCES //
// /////////////// //

struct BitmapGroup__BitmapGroupFlags {
	uint32_t content;
	static bool bitmap_is_TILED() { return (content & 0b00000000000000000000000000000001); }
	static bool use_less_blurry_bump_map() { return (content & 0b00000000000000000000000000000010); }
	static bool dither_when_compressing() { return (content & 0b00000000000000000000000000000100); }
	static bool generate_random_sprites() { return (content & 0b00000000000000000000000000001000); }
	static bool ignore_alpha_channel() { return (content & 0b00000000000000000000000000010000); }
	static bool alpha_channel_stores_TRANSPARENCY() { return (content & 0b00000000000000000000000000100000); }
	static bool preserve_alpha_channel_in_mipmaps_for_ALPHA_TEST() { return (content & 0b00000000000000000000000001000000); }
	static bool only_use_on_demand() { return (content & 0b00000000000000000000000010000000); }
	static bool apply_max_resolution_after_slicing() { return (content & 0b00000000000000000000000100000000); }
	static bool Pre_filter_cubemaps() { return (content & 0b00000000000000000000001000000000); }
	static bool has_valid_min_and_max_values() { return (content & 0b00000000000000000000010000000000); }
	static bool SDF_Only_store_inside_values() { return (content & 0b00000000000000000000100000000000); }
	static bool SDF_Store_direction() { return (content & 0b00000000000000000001000000000000); }
	static bool SDF_Store_initial_values_in_alpha_channel() { return (content & 0b00000000000000000010000000000000); }
	static bool Has_Custom_MipMaps() { return (content & 0b00000000000000000100000000000000); }
	static bool Validate_Has_Custom_MipMaps() { return (content & 0b00000000000000001000000000000000); }
	static bool Is_Light_Probes() { return (content & 0b00000000000000010000000000000000); }
};
struct BitmapUsage__BitmapUsageFlag {
	uint8_t content;
	static bool Ignore_Curve_Override() { return (content & 0b00000001); }
	static bool Dont_Allow_Size_Optimization() { return (content & 0b00000010); }
	static bool Swap_Axes() { return (content & 0b00000100); }
	static bool Pre_filter_cubemaps() { return (content & 0b00001000); }
};
struct BitmapUsage__BitmapDicerFlag {
	uint8_t content;
	static bool Convert_Plate_Color_Key_to_Alpha_Channel() { return (content & 0b00000001); }
	static bool Rotate_Cube_Map_to_Match_DirectX_Format() { return (content & 0b00000010); }
	static bool Sprites__Shrink_Elements_to_Smallest_Non_Zero_Alpha_Region() { return (content & 0b00000100); }
	static bool Sprites__Shrink_Elements_to_Smallest_Non_Zero_Color_And_Alpha_Region() { return (content & 0b00001000); }
	static bool Unsigned____Signed_Scale_and_Bias() { return (content & 0b00010000); }
	static bool Color_Grading_sRGB_Correction() { return (content & 0b00100000); }
	static bool Color_Grading_Rec709_Correction() { return (content & 0b01000000); }
};
struct BitmapUsage__BitmapPackerFlag {
	uint8_t content;
	static bool Shrink_Sprite_Texture_Pages_Tightly_to_Content() { return (content & 0b00000001); }
};
struct BitmapUsage__BitmapDownsampleFlag {
	uint16_t content;
	static bool Sprites___Color_Bleed_in_Zero_Alpha_Regions() { return (content & 0b0000000000000001); }
	static bool Pre_Multiply_Alpha__before_downsampling_() { return (content & 0b0000000000000010); }
	static bool Post_Divide_Alpha__after_downsampling_() { return (content & 0b0000000000000100); }
	static bool Height_Map___Convert_to_Bump_Map() { return (content & 0b0000000000001000); }
	static bool Detail_Map___Fade_to_Gray() { return (content & 0b0000000000010000); }
	static bool Signed____Unsigned_Scale_and_Bias() { return (content & 0b0000000000100000); }
	static bool Illum_Map___Fade_to_Black() { return (content & 0b0000000001000000); }
	static bool ZBump___Scale_by_height_and_renormalize() { return (content & 0b0000000010000000); }
	static bool Cubemap___Fix_seams() { return (content & 0b0000000100000000); }
	static bool Calculate_specular_power() { return (content & 0b0000001000000000); }
	static bool Downsample_Bumps_in_Angular_Space() { return (content & 0b0000010000000000); }
	static bool Standard_Orientation_of_Normals_in_Angular_Space_and_Renormalize() { return (content & 0b0000100000000000); }
	static bool Generate_RGB_luminance_into_alpha_channel() { return (content & 0b0001000000000000); }
};
struct BitmapFlags {
	uint16_t content;
	static bool power_of_two_dimensions() { return (content & 0b0000000000000001); }
	static bool compressed() { return (content & 0b0000000000000010); }
	static bool swap_axes() { return (content & 0b0000000000000100); }
	static bool mutable_at_runtime() { return (content & 0b0000000000001000); }
};
struct BitmapDataResourceFlags {
	uint8_t content;
	static bool Indicates_that_the_bitmap_data_resource_contains_a_3D_texture() { return (content & 0b00000001); }
	static bool This_bitmap_data_is_required_for_CPUgameplay__like_terrian_collision_() { return (content & 0b00000010); }
	static bool Single_Mip_Texture() { return (content & 0b00000100); }
	static bool UI_Texture() { return (content & 0b00001000); }
};

// /////////////// //
// ENUM REFERENCES //
// /////////////// //

enum BitmapGroup__CurveOverride {
	choose_best = 0,
	force_FAST = 1,
	force_PRETTY = 2,
};
enum BitmapUsage__BitmapForcedFormat {
	Use_Default__defined_by_usage_ = 0,
	Best_Compressed_Color_Format = 1,
	Best_Uncompressed_Color_Format = 2,
	Best_Compressed_Bump_Format = 3,
	Best_Uncompressed_Bump_Format = 4,
	Best_Compressed_Monochrome_Format = 5,
	Best_Uncompressed_Monochrome_Format = 6,
	Best_Compressed_Monochrome_Format_without_alpha = 7,
	unused2 = 8,
	unused3 = 9,
	unused4 = 10,
	unused5 = 11,
	unused6 = 12,
	____Color_and_Alpha_formats____ = 13,
	bc1_unorm__a_k_a__DXT1___Compressed_Color___Color_Key_Alpha_ = 14,
	bc2_unorm__a_k_a__DXT3___Compressed_Color___4_bit_Alpha_ = 15,
	bc3_unorm__a_k_a__DXT5___Compressed_Color___Compressed_8_bit_Alpha_ = 16,
	_24_bit_Color___8_bit_Alpha = 17,
	_8_bit_Monochrome___8_bit_Alpha = 18,
	___Channel_Mask__3_bit_Color___1_bit_Alpha_ = 19,
	___30_bit_Color___2_bit_Alpha = 20,
	___48_bit_Color___16_bit_Alpha = 21,
	___HALF_Color___Alpha = 22,
	___FLOAT_Color___Alpha = 23,
	r8_unorm__8_bit_Intensity_replicated_to_RGBA_ = 24,
	DEPRECATED_DXT3A__4_bit_Intensity_replicated_to_ARGB_ = 25,
	bc4_unorm_rrrr__a_k_a__DXT5A___Compressed_Intensity_replicated_to_ARGB_ = 26,
	Compressed_Monochrome___Alpha = 27,
	b4g4r4a4__12_bit_color___4_bit_alpha_ = 28,
	____Color_only_formats____ = 29,
	_8_bit_Monochrome = 30,
	___Compressed_24_bit_Color = 31,
	___32_bit_Color__R11G11B10_ = 32,
	___16_bit_Monochrome = 33,
	___16_bit_Red___Green_Only = 34,
	___16_bit_signed_RGBA = 35,
	___HALF_Red_Only = 36,
	___FLOAT_Red_Only = 37,
	___HALF_Red___Green_Only = 38,
	___FLOAT_Red___Green_Only = 39,
	___HALF_Monochrome = 40,
	DEPRECATED_Compressed_4_bit_Monochrome = 41,
	Compressed_Interpolated_Monochrome = 42,
	bc6h_uf16__HDR_RGB_unsigned_half_float_ = 43,
	bc6h_sf16__HDR_RGB_signed_half_float_ = 44,
	bc7_unorm__High_quality_bc3_ = 45,
	____Alpha_only_formats____ = 46,
	DEPRECATED_DXT3A__4_bit_Alpha_ = 47,
	bc4_unorm_000r__a_k_a__DXT5A___8_bit_Compressed_Alpha_ = 48,
	_8_bit_Alpha = 49,
	unused28 = 50,
	unused29 = 51,
	unused30 = 52,
	____Normal_map_formats____ = 53,
	bc5_snorm__a_k_a__DXN__Compressed_Normals__better_ = 54,
	DEPRECATED_CTX1_Compressed_Normals__smaller_ = 55,
	_16_bit_Normals = 56,
	_32_bit_Normals = 57,
	_8_bit_4_channel_Vector = 58,
};
enum BitmapGroup__SignedDistanceFieldMethod {
	Neighbors__Multithreaded_ = 0,
	Neighbors = 1,
	Cached_Euclidean__Multithreaded_ = 2,
	Cached_Euclidean = 3,
	_8SSEDT = 4,
};
enum BitmapCurve {
	unknown = 0,
	xRGB__gamma_about_2_0_ = 1,
	gamma_2_0 = 2,
	linear = 3,
	offset_log = 4,
	sRGB__gamma_2_2_ = 5,
	Rec709__gamma_2_2_ = 6,
};
enum BitmapUsage__BitmapSlicer {
	Automatically_Determine_Slicer = 0,
	No_Slicing__each_source_bitmap_generates_one_element_ = 1,
	Color_Plate_Slicer = 2,
	Cube_Map_Slicer = 3,
	Color_Grading_Slicer = 4,
};
enum BitmapUsage__BitmapPacker {
	No_packing = 0,
	Sprite_Pack__packs_elements_into_as_few_bitmaps_as_possible_ = 1,
	Sprite_Pack_if_needed__packs_elements_into_as_few_bitmaps_as_possible_ = 2,
	_3D_Pack__packs_elements_into_a_3D_bitmap_ = 3,
};
enum BitmapType {
	_2D_texture = 0,
	_3D_texture = 1,
	cube_map = 2,
	array = 3,
};
enum BitmapUsage__BitmapSmallestMip {
	_1_pixel = 0,
	_2_pixel = 1,
	_4_pixel = 2,
	_8_pixel = 3,
	_16_pixel = 4,
	_32_pixel = 5,
	_64_pixel = 6,
	_128_pixel = 7,
	_256_pixel = 8,
	_512_pixel = 9,
	_1024_pixel = 10,
};
enum BitmapUsage__BitmapDownsampleFilter {
	Point_Sampled = 0,
	Box_Filter = 1,
	Blackman_Filter = 2,
	Lanczos_Filter = 3,
	Nuttall_Filter = 4,
	Blackman_Harris_Filter = 5,
	Blackman_Nuttall_Filter = 6,
	Flat_Top_Filter = 7,
	Extreme_Filter = 8,
	Min_Filter = 9,
};
enum Floatmap__Swizzle {
	Default = 0,
	Source_Red_Channel = 1,
	Source_Green_Channel = 2,
	Source_Blue_Channel = 3,
	Source_Alpha_Channel = 4,
	Set_to_1_0 = 5,
	Set_to_0_0 = 6,
	Set_to_0_5 = 7,
	Random = 8,
	One_Minus_Source_Red_Channel = 9,
	One_Minus_Source_Green_Channel = 10,
	One_Minus_Source_Blue_Channel = 11,
	One_Minus_Source_Alpha_Channel = 12,
	Negative_Source_Red_Channel = 13,
	Negative_Source_Green_Channel = 14,
	Negative_Source_Blue_Channel = 15,
	Negative_Source_Alpha_Channel = 16,
};
enum Floatmap__Swizzle {
	Default = 0,
	Source_Red_Channel = 1,
	Source_Green_Channel = 2,
	Source_Blue_Channel = 3,
	Source_Alpha_Channel = 4,
	Set_to_1_0 = 5,
	Set_to_0_0 = 6,
	Set_to_0_5 = 7,
	Random = 8,
	One_Minus_Source_Red_Channel = 9,
	One_Minus_Source_Green_Channel = 10,
	One_Minus_Source_Blue_Channel = 11,
	One_Minus_Source_Alpha_Channel = 12,
	Negative_Source_Red_Channel = 13,
	Negative_Source_Green_Channel = 14,
	Negative_Source_Blue_Channel = 15,
	Negative_Source_Alpha_Channel = 16,
};
enum Floatmap__Swizzle {
	Default = 0,
	Source_Red_Channel = 1,
	Source_Green_Channel = 2,
	Source_Blue_Channel = 3,
	Source_Alpha_Channel = 4,
	Set_to_1_0 = 5,
	Set_to_0_0 = 6,
	Set_to_0_5 = 7,
	Random = 8,
	One_Minus_Source_Red_Channel = 9,
	One_Minus_Source_Green_Channel = 10,
	One_Minus_Source_Blue_Channel = 11,
	One_Minus_Source_Alpha_Channel = 12,
	Negative_Source_Red_Channel = 13,
	Negative_Source_Green_Channel = 14,
	Negative_Source_Blue_Channel = 15,
	Negative_Source_Alpha_Channel = 16,
};
enum Floatmap__Swizzle {
	Default = 0,
	Source_Red_Channel = 1,
	Source_Green_Channel = 2,
	Source_Blue_Channel = 3,
	Source_Alpha_Channel = 4,
	Set_to_1_0 = 5,
	Set_to_0_0 = 6,
	Set_to_0_5 = 7,
	Random = 8,
	One_Minus_Source_Red_Channel = 9,
	One_Minus_Source_Green_Channel = 10,
	One_Minus_Source_Blue_Channel = 11,
	One_Minus_Source_Alpha_Channel = 12,
	Negative_Source_Red_Channel = 13,
	Negative_Source_Green_Channel = 14,
	Negative_Source_Blue_Channel = 15,
	Negative_Source_Alpha_Channel = 16,
};
enum BitmapUsage__BitmapForcedFormat {
	Use_Default__defined_by_usage_ = 0,
	Best_Compressed_Color_Format = 1,
	Best_Uncompressed_Color_Format = 2,
	Best_Compressed_Bump_Format = 3,
	Best_Uncompressed_Bump_Format = 4,
	Best_Compressed_Monochrome_Format = 5,
	Best_Uncompressed_Monochrome_Format = 6,
	Best_Compressed_Monochrome_Format_without_alpha = 7,
	unused2 = 8,
	unused3 = 9,
	unused4 = 10,
	unused5 = 11,
	unused6 = 12,
	____Color_and_Alpha_formats____ = 13,
	bc1_unorm__a_k_a__DXT1___Compressed_Color___Color_Key_Alpha_ = 14,
	bc2_unorm__a_k_a__DXT3___Compressed_Color___4_bit_Alpha_ = 15,
	bc3_unorm__a_k_a__DXT5___Compressed_Color___Compressed_8_bit_Alpha_ = 16,
	_24_bit_Color___8_bit_Alpha = 17,
	_8_bit_Monochrome___8_bit_Alpha = 18,
	___Channel_Mask__3_bit_Color___1_bit_Alpha_ = 19,
	___30_bit_Color___2_bit_Alpha = 20,
	___48_bit_Color___16_bit_Alpha = 21,
	___HALF_Color___Alpha = 22,
	___FLOAT_Color___Alpha = 23,
	r8_unorm__8_bit_Intensity_replicated_to_RGBA_ = 24,
	DEPRECATED_DXT3A__4_bit_Intensity_replicated_to_ARGB_ = 25,
	bc4_unorm_rrrr__a_k_a__DXT5A___Compressed_Intensity_replicated_to_ARGB_ = 26,
	Compressed_Monochrome___Alpha = 27,
	b4g4r4a4__12_bit_color___4_bit_alpha_ = 28,
	____Color_only_formats____ = 29,
	_8_bit_Monochrome = 30,
	___Compressed_24_bit_Color = 31,
	___32_bit_Color__R11G11B10_ = 32,
	___16_bit_Monochrome = 33,
	___16_bit_Red___Green_Only = 34,
	___16_bit_signed_RGBA = 35,
	___HALF_Red_Only = 36,
	___FLOAT_Red_Only = 37,
	___HALF_Red___Green_Only = 38,
	___FLOAT_Red___Green_Only = 39,
	___HALF_Monochrome = 40,
	DEPRECATED_Compressed_4_bit_Monochrome = 41,
	Compressed_Interpolated_Monochrome = 42,
	bc6h_uf16__HDR_RGB_unsigned_half_float_ = 43,
	bc6h_sf16__HDR_RGB_signed_half_float_ = 44,
	bc7_unorm__High_quality_bc3_ = 45,
	____Alpha_only_formats____ = 46,
	DEPRECATED_DXT3A__4_bit_Alpha_ = 47,
	bc4_unorm_000r__a_k_a__DXT5A___8_bit_Compressed_Alpha_ = 48,
	_8_bit_Alpha = 49,
	unused28 = 50,
	unused29 = 51,
	unused30 = 52,
	____Normal_map_formats____ = 53,
	bc5_snorm__a_k_a__DXN__Compressed_Normals__better_ = 54,
	DEPRECATED_CTX1_Compressed_Normals__smaller_ = 55,
	_16_bit_Normals = 56,
	_32_bit_Normals = 57,
	_8_bit_4_channel_Vector = 58,
};
enum BitmapColorSpace {
	Automatic = 0,
	Rec709 = 1,
	DCI_P3 = 2,
	Rec2020 = 3,
};
enum BitmapColorSpace {
	Automatic = 0,
	Rec709 = 1,
	DCI_P3 = 2,
	Rec2020 = 3,
};
enum BitmapType {
	_2D_texture = 0,
	_3D_texture = 1,
	cube_map = 2,
	array = 3,
};
enum BitmapFormat {
	a8_unorm__000A_ = 0,
	r8_unorm_rrr1__RRR1_ = 1,
	r8_unorm_rrrr__RRRR_ = 2,
	r8g8_unorm_rrrg__RRRG_ = 3,
	unused1 = 4,
	unused2 = 5,
	b5g6r5_unorm = 6,
	unused3 = 7,
	b5g6r5a1_unorm = 8,
	b4g4r4a4_unorm = 9,
	b8g8r8x8_unorm = 10,
	b8g8r8a8_unorm = 11,
	unused4 = 12,
	DEPRECATED_dxt5_bias_alpha = 13,
	bc1_unorm__dxt1_ = 14,
	bc2_unorm__dxt3_ = 15,
	bc3_unorm__dxt5_ = 16,
	DEPRECATED_a4r4g4b4_font = 17,
	unused7 = 18,
	unused8 = 19,
	DEPRECATED_SOFTWARE_rgbfp32 = 20,
	unused9 = 21,
	r8g8_snorm__v8u8_ = 22,
	DEPRECATED_g8b8 = 23,
	r32g32b32a32_float__abgrfp32_ = 24,
	r16g16b16a16_float__abgrfp16_ = 25,
	r16_float_rrr1__16f_mono_ = 26,
	r16_float_r000__16f_red_ = 27,
	r8g8b8a8_snorm__q8w8v8u8_ = 28,
	r10g10b10a2_unorm__a2r10g10b10_ = 29,
	r16g16b16a16_unorm__a16b16g16r16_ = 30,
	r16g16_snorm__v16u16_ = 31,
	r16_unorm_rrr0__L16_ = 32,
	r16g16_unorm__r16g16_ = 33,
	r16g16b16a16_snorm__signedr16g16b16a16_ = 34,
	DEPRECATED_dxt3a = 35,
	bc4_unorm_rrrr__dxt5a_ = 36,
	bc4_snorm_rrrr = 37,
	DEPRECATED_dxt3a_1111 = 38,
	bc5_snorm__dxn_ = 39,
	DEPRECATED_ctx1 = 40,
	DEPRECATED_dxt3a_alpha_only = 41,
	DEPRECATED_dxt3a_monochrome_only = 42,
	bc4_unorm_000r__dxt5a_alpha_ = 43,
	bc4_unorm_rrr1__dxt5a_mono_ = 44,
	bc5_unorm_rrrg__dxn_mono_alpha_ = 45,
	bc5_snorm_rrrg__dxn_mono_alpha_signed_ = 46,
	bc6h_uf16_ = 47,
	bc6h_sf16_ = 48,
	bc7_unorm_ = 49,
	d24_unorm_s8_uint__depth_24_ = 50,
	r11g11b10_float = 51,
	r16g16_float = 52,
};
enum BitmapCurve {
	unknown = 0,
	xRGB__gamma_about_2_0_ = 1,
	gamma_2_0 = 2,
	linear = 3,
	offset_log = 4,
	sRGB__gamma_2_2_ = 5,
	Rec709__gamma_2_2_ = 6,
};
#pragma pack(pop)
