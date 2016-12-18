#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#include "../rct2/addresses.h"
#include "../common.h"
#include "../OpenRCT2.h"
#include "../sprites.h"
#include "../util/util.h"
#include "drawing.h"

void *_g1Buffer = NULL;

rct_gx g2;

#ifdef NO_RCT2
	rct_g1_element *g1Elements = NULL;
#else
	rct_g1_element *g1Elements = RCT2_ADDRESS(RCT2_ADDRESS_G1_ELEMENTS, rct_g1_element);
#endif

static const uint32 fadeSprites[] = {
	SPR_NONE,
	SPR_FADE_1,
	SPR_FADE_2,
	SPR_FADE_3,
	SPR_FADE_4,
	SPR_FADE_5,
	SPR_FADE_6,
	SPR_FADE_7,
};

static void read_and_convert_gxdat(SDL_RWops *file, size_t count, rct_g1_element *elements)
{
	rct_g1_element_32bit *g1Elements32 = calloc(count, sizeof(rct_g1_element_32bit));
	SDL_RWread(file, g1Elements32, count * sizeof(rct_g1_element_32bit), 1);
	for (size_t i = 0; i < count; i++) {
		/* Double cast to silence compiler warning about casting to
		 * pointer from integer of mismatched length.
		 */
		elements[i].offset        = (uint8*)(uintptr_t)g1Elements32[i].offset;
		elements[i].width         = g1Elements32[i].width;
		elements[i].height        = g1Elements32[i].height;
		elements[i].x_offset      = g1Elements32[i].x_offset;
		elements[i].y_offset      = g1Elements32[i].y_offset;
		elements[i].flags         = g1Elements32[i].flags;
		elements[i].zoomed_offset = g1Elements32[i].zoomed_offset;
	}
	free(g1Elements32);
}

/**
 *
 *  rct2: 0x00678998
 */
bool gfx_load_g1()
{
	log_verbose("loading g1 graphics");

	SDL_RWops *file;
	rct_g1_header header;
	unsigned int i;

	file = SDL_RWFromFile(get_file_path(PATH_ID_G1), "rb");
	if (file != NULL) {
		if (SDL_RWread(file, &header, 8, 1) == 1) {
			/* We need to load in the data file, which has an `offset` field,
			 * which is supposed to hold a pointer, but is only 32 bit long.
			 * We will load a 32 bit version of rct_g1_element and then convert
			 * pointers to however long our machine wants them.
			 */

			#pragma pack(push, 1)
			// Size: 0x10
			typedef struct {
				uint32 offset;			// 0x00 note: uint32 always!
				sint16 width;			// 0x04
				sint16 height;			// 0x06
				sint16 x_offset;		// 0x08
				sint16 y_offset;		// 0x0A
				uint16 flags;			// 0x0C
				uint16 zoomed_offset;	// 0x0E
			} rct_g1_element_32bit;
			assert_struct_size(rct_g1_element_32bit, 0x10);
			#pragma pack(pop)

			/* number of elements is stored in g1.dat, but because the entry
			 * headers are static, this can't be variable until made into a
			 * dynamic array.
			 */
			header.num_entries = 29294;

			// Read element headers
#ifdef NO_RCT2
			g1Elements = calloc(324206, sizeof(rct_g1_element));
#endif

			read_and_convert_gxdat(file, header.num_entries, g1Elements);

			// Read element data
			_g1Buffer = malloc(header.total_size);
			SDL_RWread(file, _g1Buffer, header.total_size, 1);

			SDL_RWclose(file);

			// Fix entry data offsets
			for (i = 0; i < header.num_entries; i++)
				g1Elements[i].offset += (uintptr_t)_g1Buffer;

			return true;
		}
		SDL_RWclose(file);
	}

	log_fatal("Unable to load g1 graphics");
	if (!gOpenRCT2Headless) {
		platform_show_messagebox("Unable to load g1.dat. Your RollerCoaster Tycoon 2 path may be incorrectly set.");
	}
	return false;
}

void gfx_unload_g1()
{
	SafeFree(_g1Buffer);
#ifdef NO_RCT2
	SafeFree(g1Elements);
#endif
}

void gfx_unload_g2()
{
	SafeFree(g2.elements);
}

bool gfx_load_g2()
{
	log_verbose("loading g2 graphics");

	SDL_RWops *file;
	unsigned int i;

	char path[MAX_PATH];

	platform_get_openrct_data_path(path, sizeof(path));
	safe_strcat_path(path, "g2.dat", MAX_PATH);
	file = SDL_RWFromFile(path, "rb");
	if (file != NULL) {
		if (SDL_RWread(file, &g2.header, 8, 1) == 1) {
			// Read element headers
			g2.elements = malloc(g2.header.num_entries * sizeof(rct_g1_element));

			read_and_convert_gxdat(file, g2.header.num_entries, g2.elements);

			// Read element data
			g2.data = malloc(g2.header.total_size);
			SDL_RWread(file, g2.data, g2.header.total_size, 1);

			SDL_RWclose(file);

			// Fix entry data offsets
			for (i = 0; i < g2.header.num_entries; i++)
				g2.elements[i].offset += (uintptr_t)g2.data;

			return true;
		}
		SDL_RWclose(file);
	}

	log_fatal("Unable to load g2 graphics");
	if (!gOpenRCT2Headless) {
		platform_show_messagebox("Unable to load g2.dat");
	}
	return false;
}

/**
 * This function looks like it initialises the 0x009E3CE4 array which references sprites used for background / palette mixing or
 * something. Further investigation is needed.
 */
void sub_68371D()
{
	for (int i = 0; i < countof(fadeSprites); i++) {
		const uint32 spriteId = fadeSprites[i];
		if (spriteId == SPR_NONE) {
			unk_9E3CE4[i] = NULL;
		} else {
			unk_9E3CE4[i] = g1Elements[fadeSprites[i]].offset;
		}
	}
}

/**
 * Copies a sprite onto the buffer. There is no compression used on the sprite
 * image.
 *  rct2: 0x0067A690
 */
static void FASTCALL gfx_bmp_sprite_to_buffer(uint8* palette_pointer, uint8* unknown_pointer, uint8* source_pointer, uint8* dest_pointer, rct_g1_element* source_image, rct_drawpixelinfo *dest_dpi, int height, int width, int image_type){
	uint16 zoom_level = dest_dpi->zoom_level;
	uint8 zoom_amount = 1 << zoom_level;
	uint32 dest_line_width = (dest_dpi->width / zoom_amount) + dest_dpi->pitch;
	uint32 source_line_width = source_image->width * zoom_amount;

	// Image uses the palette pointer to remap the colours of the image
	if (image_type & IMAGE_TYPE_REMAP){
		assert(palette_pointer != NULL);

		//image with remaps
		for (; height > 0; height -= zoom_amount){
			uint8* next_source_pointer = source_pointer + source_line_width;
			uint8* next_dest_pointer = dest_pointer + dest_line_width;
			for (int no_pixels = width; no_pixels > 0; no_pixels -= zoom_amount, source_pointer += zoom_amount, dest_pointer++){
				uint8 pixel = *source_pointer;
				pixel = palette_pointer[pixel];
				if (pixel){
					*dest_pointer = pixel;
				}
			}

			source_pointer = next_source_pointer;
			dest_pointer = next_dest_pointer;
		}
		return;
	}

	//Image is Transparent. It only uses source pointer for
	//telling if it needs to be drawn not for colour. Colour provided
	//by the palette pointer.
	if (image_type & IMAGE_TYPE_TRANSPARENT){//Not tested
		assert(palette_pointer != NULL);
		for (; height > 0; height -= zoom_amount){
			uint8* next_source_pointer = source_pointer + source_line_width;
			uint8* next_dest_pointer = dest_pointer + dest_line_width;

			for (int no_pixels = width; no_pixels > 0; no_pixels -= zoom_amount, source_pointer += zoom_amount, dest_pointer++){
				uint8 pixel = *source_pointer;
				if (pixel){
					pixel = *dest_pointer;
					pixel = palette_pointer[pixel];
					*dest_pointer = pixel;
				}
			}

			source_pointer = next_source_pointer;
			dest_pointer = next_dest_pointer;
		}
		return;
	}

	//Basic bitmap no fancy stuff
	if (!(source_image->flags & G1_FLAG_BMP)){//Not tested
		for (; height > 0; height -= zoom_amount){
			uint8* next_source_pointer = source_pointer + source_line_width;
			uint8* next_dest_pointer = dest_pointer + dest_line_width;

			for (int no_pixels = width; no_pixels > 0; no_pixels -= zoom_amount, dest_pointer++, source_pointer += zoom_amount){
				*dest_pointer = *source_pointer;
			}

			dest_pointer = next_dest_pointer;
			source_pointer = next_source_pointer;
		}
		return;
	}

	//Basic bitmap with no draw pixels
	for (; height > 0; height -= zoom_amount){
		uint8* next_source_pointer = source_pointer + source_line_width;
		uint8* next_dest_pointer = dest_pointer + dest_line_width;

		for (int no_pixels = width; no_pixels > 0; no_pixels -= zoom_amount, dest_pointer++, source_pointer += zoom_amount){
			uint8 pixel = *source_pointer;
			if (pixel){
				*dest_pointer = pixel;
			}
		}
		dest_pointer = next_dest_pointer;
		source_pointer = next_source_pointer;
	}
	return;
}

uint8* FASTCALL gfx_draw_sprite_get_palette(int image_id, uint32 tertiary_colour) {
	int image_type = (image_id & 0xE0000000);
	if (image_type == 0)
		return NULL;

	if (!(image_type & IMAGE_TYPE_REMAP_2_PLUS)) {
		uint8 palette_ref = (image_id >> 19) & 0xFF;
		if (!(image_type & IMAGE_TYPE_TRANSPARENT)) {
			palette_ref &= 0x7F;
		}

		uint16 palette_offset = palette_to_g1_offset[palette_ref];
		return g1Elements[palette_offset].offset;
	}
	else {
		uint8* palette_pointer = gPeepPalette;

		uint32 primary_offset = palette_to_g1_offset[(image_id >> 19) & 0x1F];
		uint32 secondary_offset = palette_to_g1_offset[(image_id >> 24) & 0x1F];

		if (!(image_type & IMAGE_TYPE_REMAP)) {
			palette_pointer = gOtherPalette;
#if defined(DEBUG_LEVEL_2) && DEBUG_LEVEL_2
			assert(tertiary_colour < PALETTE_TO_G1_OFFSET_COUNT);
#endif // DEBUG_LEVEL_2
			uint32 tertiary_offset = palette_to_g1_offset[tertiary_colour];
			rct_g1_element* tertiary_palette = &g1Elements[tertiary_offset];
			memcpy(palette_pointer + 0x2E, &tertiary_palette->offset[0xF3], 12);
		}
		rct_g1_element* primary_palette = &g1Elements[primary_offset];
		rct_g1_element* secondary_palette = &g1Elements[secondary_offset];

		memcpy(palette_pointer + 0xF3, &primary_palette->offset[0xF3], 12);
		memcpy(palette_pointer + 0xCA, &secondary_palette->offset[0xF3], 12);

		return palette_pointer;
	}
}

/**
 *
 *  rct2: 0x0067A28E
 * image_id (ebx)
 * image_id as below
 * 0b_111X_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX image_type
 * 0b_XXX1_11XX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX image_sub_type (unknown pointer)
 * 0b_XXX1_1111_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX secondary_colour
 * 0b_XXXX_XXXX_1111_1XXX_XXXX_XXXX_XXXX_XXXX primary_colour
 * 0b_XXXX_X111_1111_1XXX_XXXX_XXXX_XXXX_XXXX palette_ref
 * 0b_XXXX_XXXX_XXXX_X111_1111_1111_1111_1111 image_id (offset to g1)
 * x (cx)
 * y (dx)
 * dpi (esi)
 * tertiary_colour (ebp)
 */
void FASTCALL gfx_draw_sprite_software(rct_drawpixelinfo *dpi, int image_id, int x, int y, uint32 tertiary_colour)
{
	uint8* palette_pointer = gfx_draw_sprite_get_palette(image_id, tertiary_colour);
	if (image_id & IMAGE_TYPE_REMAP_2_PLUS) {
		image_id |= IMAGE_TYPE_REMAP;
	}


	gfx_draw_sprite_palette_set_software(dpi, image_id, x, y, palette_pointer, NULL);
}

/*
* rct: 0x0067A46E
* image_id (ebx) and also (0x00EDF81C)
* palette_pointer (0x9ABDA4)
* unknown_pointer (0x9E3CDC)
* dpi (edi)
* x (cx)
* y (dx)
*/
void FASTCALL gfx_draw_sprite_palette_set_software(rct_drawpixelinfo *dpi, int image_id, int x, int y, uint8* palette_pointer, uint8* unknown_pointer)
{
	int image_element = image_id & 0x7FFFF;
	int image_type = image_id & 0xE0000000;

	rct_g1_element *g1_source = gfx_get_g1_element(image_element);

	if (dpi->zoom_level != 0 && (g1_source->flags & G1_FLAG_HAS_ZOOM_SPRITE)) {
		rct_drawpixelinfo zoomed_dpi = {
			.bits = dpi->bits,
			.x = dpi->x >> 1,
			.y = dpi->y >> 1,
			.height = dpi->height>>1,
			.width = dpi->width>>1,
			.pitch = dpi->pitch,
			.zoom_level = dpi->zoom_level - 1
		};
		gfx_draw_sprite_palette_set_software(&zoomed_dpi, image_type | (image_element - g1_source->zoomed_offset), x >> 1, y >> 1, palette_pointer, unknown_pointer);
		return;
	}

	if (dpi->zoom_level != 0 && (g1_source->flags & G1_FLAG_NO_ZOOM_DRAW)) {
		return;
	}

	//Its used super often so we will define it to a separate variable.
	int zoom_level = dpi->zoom_level;
	int zoom_mask = 0xFFFFFFFF << zoom_level;

	if (zoom_level && g1_source->flags & G1_FLAG_RLE_COMPRESSION){
		x -= ~zoom_mask;
		y -= ~zoom_mask;
	}

	//This will be the height of the drawn image
	int height = g1_source->height;
	//This is the start y coordinate on the destination
	sint16 dest_start_y = y + g1_source->y_offset;

	// For whatever reason the RLE version does not use
	// the zoom mask on the y coordinate but does on x.
	if (g1_source->flags & G1_FLAG_RLE_COMPRESSION){
		dest_start_y -= dpi->y;
	}
	else{
		dest_start_y = (dest_start_y&zoom_mask) - dpi->y;
	}
	//This is the start y coordinate on the source
	int source_start_y = 0;

	if (dest_start_y < 0){
		//If the destination y is negative reduce the height of the
		//image as we will cut off the bottom
		height += dest_start_y;
		//If the image is no longer visible nothing to draw
		if (height <= 0){
			return;
		}
		//The source image will start a further up the image
		source_start_y -= dest_start_y;
		//The destination start is now reset to 0
		dest_start_y = 0;
	}
	else{
		if (g1_source->flags & G1_FLAG_RLE_COMPRESSION && zoom_level){
			source_start_y -= dest_start_y & ~zoom_mask;
			height += dest_start_y & ~zoom_mask;
		}
	}

	int dest_end_y = dest_start_y + height;

	if (dest_end_y > dpi->height){
		//If the destination y is outside of the drawing
		//image reduce the height of the image
		height -= dest_end_y - dpi->height;
	}
	//If the image no longer has anything to draw
	if (height <= 0)return;

	dest_start_y >>= zoom_level;
	dest_end_y >>= zoom_level;

	//This will be the width of the drawn image
	int width = g1_source->width;
	//This is the source start x coordinate
	int source_start_x = 0;
	//This is the destination start x coordinate
	sint16 dest_start_x = ((x + g1_source->x_offset + ~zoom_mask)&zoom_mask) - dpi->x;

	if (dest_start_x < 0){
		//If the destination is negative reduce the width
		//image will cut off the side
		width += dest_start_x;
		//If there is no image to draw
		if (width <= 0){
			return;
		}
		//The source start will also need to cut off the side
		source_start_x -= dest_start_x;
		//Reset the destination to 0
		dest_start_x = 0;
	}
	else{
		if (g1_source->flags & G1_FLAG_RLE_COMPRESSION && zoom_level){
			source_start_x -= dest_start_x & ~zoom_mask;
		}
	}

	int dest_end_x = dest_start_x + width;

	if (dest_end_x > dpi->width){
		//If the destination x is outside of the drawing area
		//reduce the image width.
		width -= dest_end_x - dpi->width;
		//If there is no image to draw.
		if (width <= 0)return;
	}

	dest_start_x >>= zoom_level;
	dest_end_x >>= zoom_level;

	uint8* dest_pointer = (uint8*)dpi->bits;
	//Move the pointer to the start point of the destination
	dest_pointer += ((dpi->width >> zoom_level) + dpi->pitch) * dest_start_y + dest_start_x;

	if (g1_source->flags & G1_FLAG_RLE_COMPRESSION){
		//We have to use a different method to move the source pointer for
		//rle encoded sprites so that will be handled within this function
		gfx_rle_sprite_to_buffer(g1_source->offset, dest_pointer, palette_pointer, dpi, image_type, source_start_y, height, source_start_x, width);
		return;
	}
	uint8* source_pointer = g1_source->offset;
	//Move the pointer to the start point of the source
	source_pointer += g1_source->width*source_start_y + source_start_x;

	if (!(g1_source->flags & G1_FLAG_1)) {
		gfx_bmp_sprite_to_buffer(palette_pointer, unknown_pointer, source_pointer, dest_pointer, g1_source, dpi, height, width, image_type);
	}
	return;
}

/**
 * Draws the given colour image masked out by the given mask image. This can currently only cope with bitmap formatted mask and
 * colour images. Presumably the original game never used RLE images for masking. Colour 0 represents transparent.
 *
 *  rct2: 0x00681DE2
 */
void FASTCALL gfx_draw_sprite_raw_masked_software(rct_drawpixelinfo *dpi, int x, int y, int maskImage, int colourImage)
{
	int left, top, right, bottom, width, height;
	rct_g1_element *imgMask = &g1Elements[maskImage & 0x7FFFF];
	rct_g1_element *imgColour = &g1Elements[colourImage & 0x7FFFF];

	assert(imgMask->flags & G1_FLAG_BMP);
	assert(imgColour->flags & G1_FLAG_BMP);

	if (dpi->zoom_level != 0) {
		// TODO implement other zoom levels (probably not used though)
		assert(false);
		return;
	}

	width = min(imgMask->width, imgColour->width);
	height = min(imgMask->height, imgColour->height);

	x += imgMask->x_offset;
	y += imgMask->y_offset;

	left = max(dpi->x, x);
	top = max(dpi->y, y);
	right = min(dpi->x + dpi->width, x + width);
	bottom = min(dpi->y + dpi->height, y + height);

	width = right - left;
	height = bottom - top;
	if (width < 0 || height < 0)
		return;

	int skipX = left - x;
	int skipY = top - y;

	uint8 *maskSrc = imgMask->offset + (skipY * imgMask->width) + skipX;
	uint8 *colourSrc = imgColour->offset + (skipY * imgColour->width) + skipX;
	uint8 *dst = dpi->bits + (left - dpi->x) + ((top - dpi->y) * (dpi->width + dpi->pitch));

	int maskWrap = imgMask->width - width;
	int colourWrap = imgColour->width - width;
	int dstWrap = ((dpi->width + dpi->pitch) - width);
	for (int y = top; y < bottom; y++) {
		for (int x = left; x < right; x++) {
			uint8 colour = (*colourSrc) & (*maskSrc);
			if (colour != 0) {
				*dst = colour;
			}

			maskSrc++;
			colourSrc++;
			dst++;
		}
		maskSrc += maskWrap;
		colourSrc += colourWrap;
		dst += dstWrap;
	}
}

rct_g1_element *gfx_get_g1_element(int image_id) {
	if (image_id < SPR_G2_BEGIN) {
		return &g1Elements[image_id];
	}

	return &g2.elements[image_id - SPR_G2_BEGIN];
}
