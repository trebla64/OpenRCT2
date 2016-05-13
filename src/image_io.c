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

#include <png.h>

#include "image_io.h"

static void my_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
static void my_png_write_data(png_structp png_ptr, png_bytep data, png_size_t length);
static void my_png_flush(png_structp png_ptr);

bool image_io_png_read(uint8 **pixels, uint32 *width, uint32 *height, const utf8 *path)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;

	// Setup PNG structures
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		return false;
	}
 
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	// Open PNG file
	SDL_RWops *fp = SDL_RWFromFile(path, "rb");
	if (fp == NULL) {
		return false;
	}

	// Set error handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		SDL_RWclose(fp);
		return false;
	}
 
	// Setup png reading
	png_set_read_fn(png_ptr, fp, my_png_read_data);
	png_set_sig_bytes(png_ptr, sig_read);

	// To simplify the reading process, convert 4-16 bit data to 24-32 bit data
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
 
	// Read header
	png_uint_32 pngWidth, pngHeight;
	int bit_depth, colour_type, interlace_type;
	png_get_IHDR(png_ptr, info_ptr, &pngWidth, &pngHeight, &bit_depth, &colour_type, &interlace_type, NULL, NULL);

	// Read pixels as 32bpp RGBA data
	png_size_t rowBytes = png_get_rowbytes(png_ptr, info_ptr);
	png_bytepp rowPointers = png_get_rows(png_ptr, info_ptr);
	uint8 *pngPixels = (uint8*)malloc(pngWidth * pngHeight * 4);
	uint8 *dst = pngPixels;
	if (colour_type == PNG_COLOR_TYPE_RGB) {
		// 24-bit PNG (no alpha)
		assert(rowBytes == pngWidth * 3);
		for (png_uint_32 i = 0; i < pngHeight; i++) {
			uint8 *src = rowPointers[i];
			for (png_uint_32 x = 0; x < pngWidth; x++) {
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = *src++;
				*dst++ = 255;
			}
		}
	} else {
		// 32-bit PNG (with alpha)
		assert(rowBytes == pngWidth * 4);
		for (png_uint_32 i = 0; i < pngHeight; i++) {
			memcpy(dst, rowPointers[i], rowBytes);
			dst += rowBytes;
		}
	}
 
	// Close the PNG
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	SDL_RWclose(fp);

	// Return the output data
	*pixels = (uint8*)pngPixels;
	if (width != NULL) *width = pngWidth;
	if (height != NULL) *height = pngHeight;
	return true;
}

bool image_io_png_write(const rct_drawpixelinfo *dpi, const rct_palette *palette, const utf8 *path)
{
	// Get image size
	int stride = dpi->width + dpi->pitch;

	// Setup PNG
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return false;
	}

	png_colorp png_palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof(png_color));
	for (int i = 0; i < 256; i++) {
		const rct_palette_entry *entry = &palette->entries[i];
		png_palette[i].blue		= entry->blue;
		png_palette[i].green	= entry->green;
		png_palette[i].red		= entry->red;
	}

	png_set_PLTE(png_ptr, info_ptr, png_palette, PNG_MAX_PALETTE_LENGTH);

	// Open file for writing
	SDL_RWops *file = SDL_RWFromFile(path, "wb");
	if (file == NULL) {
		png_free(png_ptr, png_palette);
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return false;
	}
	png_set_write_fn(png_ptr, file, my_png_write_data, my_png_flush);

	// Set error handler
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_free(png_ptr, png_palette);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		SDL_RWclose(file);
		return false;
	}

	// Write header
	png_set_IHDR(
		png_ptr, info_ptr, dpi->width, dpi->height, 8,
		PNG_COLOR_TYPE_PALETTE, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
	);
	png_byte transparentIndex = 0;
	png_set_tRNS(png_ptr, info_ptr, &transparentIndex, 1, NULL);
	png_write_info(png_ptr, info_ptr);

	// Write pixels
	uint8 *bits = dpi->bits;
	for (int y = 0; y < dpi->height; y++) {
		png_write_row(png_ptr, (png_byte *)bits);
		bits += stride;
	}

	// Finish
	png_write_end(png_ptr, NULL);
	SDL_RWclose(file);

	png_free(png_ptr, png_palette);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	return true;
}

static void my_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
	SDL_RWops *file = (SDL_RWops*)png_get_io_ptr(png_ptr);
	SDL_RWread(file, data, length, 1);
}

static void my_png_write_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
	SDL_RWops *file = (SDL_RWops*)png_get_io_ptr(png_ptr);
	SDL_RWwrite(file, data, length, 1);
}

static void my_png_flush(png_structp png_ptr)
{

}

// Bitmap header structs, for cross platform purposes
typedef struct BitmapFileHeader {
	uint16 bfType;
	uint32 bfSize;
	uint16 bfReserved1;
	uint16 bfReserved2;
	uint32 bfOffBits;
} BitmapFileHeader;

typedef struct BitmapInfoHeader {
	uint32 biSize;
	sint32 biWidth;
	sint32 biHeight;
	uint16 biPlanes;
	uint16 biBitCount;
	uint32 biCompression;
	uint32 biSizeImage;
	sint32 biXPelsPerMeter;
	sint32 biYPelsPerMeter;
	uint32 biClrUsed;
	uint32 biClrImportant;
} BitmapInfoHeader;

/**
 *
 *  rct2: 0x00683D20
 */
bool image_io_bmp_write(const rct_drawpixelinfo *dpi, const rct_palette *palette, const utf8 *path)
{
	BitmapFileHeader header;
	BitmapInfoHeader info;

	int i, y, width, height, stride;
	uint8 *buffer, *row;
	SDL_RWops *fp;
	unsigned int bytesWritten;

	// Open binary file for writing
	if ((fp = SDL_RWFromFile(path, "wb")) == NULL){
		return false;
	}

	// Allocate buffer
	buffer = malloc(0xFFFF);
	if (buffer == NULL) {
		SDL_RWclose(fp);
		return false;
	}

	// Get image size
	width = dpi->width;
	height = dpi->height;
	stride = dpi->width + dpi->pitch;

	// File header
	memset(&header, 0, sizeof(header));
	header.bfType = 0x4D42;
	header.bfSize = height * stride + 1038;
	header.bfOffBits = 1038;

	bytesWritten = SDL_RWwrite(fp, &header, sizeof(BitmapFileHeader), 1);
	if (bytesWritten != 1) {
		SDL_RWclose(fp);
		SafeFree(buffer);
		log_error("failed to save screenshot");
		return false;
	}

	// Info header
	memset(&info, 0, sizeof(info));
	info.biSize = sizeof(info);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biBitCount = 8;
	info.biXPelsPerMeter = 2520;
	info.biYPelsPerMeter = 2520;
	info.biClrUsed = 246;

	bytesWritten = SDL_RWwrite(fp, &info, sizeof(BitmapInfoHeader), 1);
	if (bytesWritten != 1) {
		SDL_RWclose(fp);
		SafeFree(buffer);
		log_error("failed to save screenshot");
		return false;
	}

	// Palette
	memset(buffer, 0, 246 * 4);
	for (i = 0; i < 246; i++) {
		const rct_palette_entry *entry = &palette->entries[i];
		buffer[i * 4 + 0] = entry->blue;
		buffer[i * 4 + 1] = entry->green;
		buffer[i * 4 + 2] = entry->red;
	}

	bytesWritten = SDL_RWwrite(fp, buffer, sizeof(char), 246 * 4);
	if (bytesWritten != 246*4){
		SDL_RWclose(fp);
		SafeFree(buffer);
		log_error("failed to save screenshot");
		return false;
	}

	// Image, save upside down
	for (y = dpi->height - 1; y >= 0; y--) {
		row = dpi->bits + y * (dpi->width + dpi->pitch);

		memset(buffer, 0, stride);
		memcpy(buffer, row, dpi->width);

		bytesWritten = SDL_RWwrite(fp, buffer, sizeof(char), stride);
		if (bytesWritten != stride){
			SDL_RWclose(fp);
			SafeFree(buffer);
			log_error("failed to save screenshot");
			return false;
		}
	}

	SDL_RWclose(fp);
	free(buffer);
	return true;
}
