/* Copyright 2013-present Facebook. All Rights Reserved. */
/* Copyright (c) 2014, Alex Zielenski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef _CAR_FORMAT_H
#define _CAR_FORMAT_H

/**
 * Compiled Asset Archive format (car)
 *
 * A car file is a BOM file with a number of special variables. Conceptually, a
 * car file contains a set of "facets", or named assets, and "renditions", or
 * specific variants of those assets based on a variety of parameters. It also
 * supports a number of other types of content which aren't supported/described.
 *
 * The highest level variable in a car file is the CARHEADER, which has some
 * metadata about the file contents, a version marker, and creator string. This
 * is stored as a custom structure.
 *
 * The next level is the list of facets, stored in FACETKEYS as a standard BOM
 * tree. In the tree, the leaf keys are the facet's name (stored as a string)
 * and the values are a list of attribute key-value pairs. Of those attributes,
 * the `identifier` key is used to find the renditions comprising the facet.
 *
 * The KEYFORMAT variable describes the order of keys used to identify renditions,
 * also in a simple custom structure format.
 *
 * Renditions are listed in the RENDITIONS variable in a BOM tree. The keys of
 * the tree hold a list of attribute values, matching the order of attribute
 * identifiers in the KEYFORMAT variable. Each rendition key is unique and has
 * an identifier connecting it to the facet it beongs to.
 *
 * Rendition values are a custom structure format with a number of pieces. The
 * first is the rendition header, which has metadata about the rendition like
 * its original file name, width, height, scale, and pixel format. Following
 * that is the information list, a variable length section describing properties
 * applying to only certain images, like slicing and format details.
 *
 * Directly after the info section is the image data. This is found in one of
 * three formats, preceded by a header specifying the data length:
 *
 *  1. Direct gzip image data. The image data matches the pixel format noted
 *     in the rendition header.
 *  2. LZVN compressed image data. LZVN is a custom compression algorithm that
 *     is also (apparently) used for compressing OS X kernel images.
 *  3. A sub-header is sometimes present, usually followed by LZVN data. The
 *     purpose of this sub-header is unclear.
 *
 */

struct car_attribute_pair {
    uint16_t identifier;
    uint16_t value;
} __attribute__((packed));

enum car_attribute_identifier {
    car_attribute_identifier_element = 1,
    car_attribute_identifier_part = 2,
    car_attribute_identifier_size = 3,
    car_attribute_identifier_direction = 4,
    car_attribute_identifier_value = 6,
    car_attribute_identifier_dimension1 = 8,
    car_attribute_identifier_dimension2 = 9,
    car_attribute_identifier_state = 10,
    car_attribute_identifier_layer = 11,
    car_attribute_identifier_scale = 12,
    car_attribute_identifier_presentation_state = 14,
    car_attribute_identifier_idiom = 15,
    car_attribute_identifier_subtype = 16,
    car_attribute_identifier_identifier = 17,
    car_attribute_identifier_previous_value = 18,
    car_attribute_identifier_previous_state = 19,
    car_attribute_identifier_size_class_horizontal = 20,
    car_attribute_identifier_size_class_vertical = 21,
    car_attribute_identifier_memory_class = 22,
    car_attribute_identifier_graphics_class = 23,

    /* Not a real value; used as a marker for the maximum identifier. */
    _car_attribute_identifier_count = 24,
};

enum car_attribute_identifier_size_value {
    car_attribute_identifier_size_value_regular = 0,
    car_attribute_identifier_size_value_small = 1,
    car_attribute_identifier_size_value_mini = 2,
    car_attribute_identifier_size_value_large = 3,
};

enum car_attribute_identifier_direction_value {
    car_attribute_identifier_direction_value_horizontal = 0,
    car_attribute_identifier_direction_value_vertical = 1,
    car_attribute_identifier_direction_value_pointing_up = 2,
    car_attribute_identifier_direction_value_pointing_down = 3,
    car_attribute_identifier_direction_value_pointing_left = 4,
    car_attribute_identifier_direction_value_pointing_right = 5,
};

enum car_attribute_identifier_value_value {
    car_attribute_identifier_value_value_off = 0,
    car_attribute_identifier_value_value_on = 1,
    car_attribute_identifier_value_value_mixed = 2,
};

enum car_attribute_identifier_state_value {
    car_attribute_identifier_state_value_normal = 0,
    car_attribute_identifier_state_value_rollover = 1,
    car_attribute_identifier_state_value_pressed = 2,
    car_attribute_identifier_state_value_obsolete_inactive = 3,
    car_attribute_identifier_state_value_disabled = 4,
    car_attribute_identifier_state_value_deeply_pressed = 5,
};

enum car_attribute_identifier_layer_value {
    car_attribute_identifier_layer_value_base = 0,
    car_attribute_identifier_layer_value_highlight = 1,
    car_attribute_identifier_layer_value_mask = 2,
    car_attribute_identifier_layer_value_pulse = 3,
    car_attribute_identifier_layer_value_hit_mask = 4,
    car_attribute_identifier_layer_value_pattern_overlay = 5,
    car_attribute_identifier_layer_value_outline = 6,
    car_attribute_identifier_layer_value_interior = 7,
};

enum car_attribute_identifier_presentation_state_value {
    car_attribute_identifier_presentation_state_active = 0,
    car_attribute_identifier_presentation_state_inactive = 1,
    car_attribute_identifier_presentation_state_active_main = 2,
};

enum car_attribute_identifier_idiom_value {
    car_attribute_identifier_idiom_value_universal = 0,
    car_attribute_identifier_idiom_value_phone = 1,
    car_attribute_identifier_idiom_value_pad = 2,
    car_attribute_identifier_idiom_value_tv = 3,
    car_attribute_identifier_idiom_value_car = 4,
    car_attribute_identifier_idiom_value_watch = 5,
    car_attribute_identifier_idiom_value_marketing = 6,
};

enum car_attribute_identifier_size_class_value {
    car_attribute_identifier_size_class_value_unspecified = 0,
    car_attribute_identifier_size_class_value_compact = 1,
    car_attribute_identifier_size_class_value_regular = 2,
};

// values seem to be little endian, unlike BOM
struct car_header {
    char magic[4]; // RATC

    uint32_t ui_version; // 31 01 00 00
    uint32_t storage_version; // 08 00 00 00
    uint32_t storage_timestamp; // 36 83 45 54
    uint32_t rendition_count; // 38 00 00 00

    char file_creator[128]; // string, appears to end with newline (0A)
    char other_creator[256]; // string, appears to be NUL-terminated
    uint8_t uuid[16];

    uint32_t associated_checksum; // CRC32?
    uint32_t schema_version; // 04 00 00 00
    uint32_t color_space_id; // 01 00 00 00
    uint32_t key_semantics; // 01 00 00 00
} __attribute__((packed));

struct car_key_format {
    char magic[4]; // 'kfmt'
    uint32_t reserved;
    uint32_t num_identifiers;
    uint32_t identifier_list[0];
} __attribute__((packed));

struct car_facet_key {
    char facet_name[0]; // length is key length
} __attribute__((packed));

struct car_facet_value {
    // ????
    struct {
        uint16_t x;
        uint16_t y;
    } hot_spot;

    uint16_t attributes_count;
    struct car_attribute_pair attributes[0];
} __attribute__((packed));

struct car_part_element_key {
    uint32_t part_element_id; // maybe id? increments
} __attribute__((packed));

struct car_part_element_value {
    uint32_t unknown1;
    uint32_t unknown2;
    char name[0]; // length - 8
} __attribute__((packed));

struct car_rendition_key {
    uint16_t values[0]; // flat list of short values in the order of the attributes from the keyformat plus a trailing null
};

struct car_rendition_info_header {
    uint32_t magic;
    uint32_t length;
} __attribute__((packed));

struct car_rendition_value {
    char magic[4]; // CTSI is Core Theme Structured Image
    uint32_t version; // current known version is 1

    struct {
        unsigned int is_header_flagged_fpo : 1;
        unsigned int is_excluded_from_contrast_filter : 1;
        unsigned int is_vector : 1;
        unsigned int is_opaque : 1;
        unsigned int reserved : 28;
    } flags;

    uint32_t width;
    uint32_t height;
    uint32_t scale_factor; // scale * 100. 100 is 1x, 200 is 2x, etc.
    uint32_t pixel_format; // 'ARGB' ('BGRA' in little endian), if it is 0x47413820 (GA8) then the colorspace will be gray or 'PDF ' if a pdf
    uint32_t color_space_id : 4; // colorspace ID. 0 for sRGB, all else for generic rgb, used only if pixelFormat 'ARGB'
    uint32_t reserved : 28;

    struct {
        uint32_t modification_date;  // modification date in seconds since 1970?
        uint16_t layout; // layout/type of the rendition
        uint16_t reserved; // always zero
        char name[128];
    } metadata;

    uint32_t info_len; // size of the list of information after header but before bitmap

    struct {
        uint32_t bitmap_count;
        uint32_t reserved;
        uint32_t payload_size; // size of all the proceeding information listLength + data
    } bitmaps;

    struct car_rendition_info_header info[0];
} __attribute__((packed));

enum car_rendition_value_pixel_format {
    car_rendition_value_pixel_format_argb = 'ARGB',
    car_rendition_value_pixel_format_pdf = 'PDF ',
    car_rendition_value_pixel_format_raw_data = 'DATA',
    car_rendition_value_pixel_format_jpeg = 'JPEG',
};

enum car_rendition_value_layout {
    car_rendition_value_layout_gradient = 6,
    car_rendition_value_layout_effect = 7,
    car_rendition_value_layout_one_part_fixed_size = 10,
    car_rendition_value_layout_one_part_tile = 11,
    car_rendition_value_layout_one_part_scale = 12,
    car_rendition_value_layout_three_part_horizontal_tile = 20,
    car_rendition_value_layout_three_part_horizontal_scale = 21,
    car_rendition_value_layout_three_part_horizontal_uniform = 22,
    car_rendition_value_layout_three_part_vertical_tile = 23,
    car_rendition_value_layout_three_part_vertical_scale = 24,
    car_rendition_value_layout_three_part_vertical_uniform = 25,
    car_rendition_value_layout_nine_part_tile = 30,
    car_rendition_value_layout_nine_part_scale = 31,
    car_rendition_value_layout_nine_part_horizontal_uniform_vertical_scale = 32,
    car_rendition_value_layout_nine_part_horizontal_scale_vertical_uniform = 33,
    car_rendition_value_layout_six_part = 40,
    car_rendition_value_layout_animation_filmstrip = 50,

    // Non-images > 999:
    car_rendition_value_layout_RawData = 1000,
    car_rendition_value_layout_ExternalLink = 1001,
    car_rendition_value_layout_LayerStack = 1002,
    car_rendition_value_layout_InternalLink = 1003,
    car_rendition_value_layout_AssetPack = 1004,
};

struct car_rendition_info_slice {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
} __attribute__((packed));

struct car_rendition_info_slices {
    struct car_rendition_info_header header;
    unsigned int nslices;
    struct car_rendition_info_slice slices[0];
} __attribute__((packed));

struct car_rendition_info_metrics_metric {
    uint32_t width;
    uint32_t height;
} __attribute__((packed));

struct car_rendition_info_metrics {
    struct car_rendition_info_header header;
    uint32_t nmetrics; // todo should the below be an array?
    struct car_rendition_info_metrics_metric top_right_inset;
    struct car_rendition_info_metrics_metric bottom_left_inset;
    struct car_rendition_info_metrics_metric image_size;
} __attribute__((packed));

enum car_rendition_info_magic {
    car_rendition_info_magic_slices = 1001,
    car_rendition_info_magic_metrics = 1003,
    car_rendition_info_magic_composition = 1004,
    car_rendition_info_magic_uti = 1005,
    car_rendition_info_magic_bitmap_info = 1006,
    car_rendition_info_magic_bytes_per_row = 1007,
    car_rendition_info_magic_reference = 1010,
};

struct car_rendition_data_header1 {
    char magic[4]; // CELM
    uint32_t unknown1; // always 0
    uint32_t unknown2; // always 2 (or 3?)
    uint32_t length; // length of data
    uint8_t data[0]; // length
};

struct car_rendition_data_header2 {
    char magic[4]; // KCBC
    uint32_t unknown1;
    uint32_t unknown2;
    uint32_t unknown3;
    uint32_t length;
    uint8_t data[0];
};

enum car_rendition_data_compression_magic {
    car_rendition_data_compression_magic_deflate = 0x1f8b0800,
    car_rendition_data_compression_magic_lzvn = 0x0e16160e,
};

const char *const car_header_variable;
const char *const car_key_format_variable;
const char *const car_facet_keys_variable;
const char *const car_part_info_variable;
const char *const car_element_info_variable;
const char *const car_renditions_variable;
const char *const car_colors_variable;
const char *const car_fonts_variable;
const char *const car_font_sizes_variable;
const char *const car_glyphs_variable;
const char *const car_bezels_variable;

const char *const car_attribute_identifier_names[_car_attribute_identifier_count];

#endif /* _CAR_FORMAT_H */