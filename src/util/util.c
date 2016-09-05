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

// Include common.h before SDL, otherwise M_PI gets redefined
#include "../common.h"

#include <SDL.h>
#include "../localisation/localisation.h"
#include "../platform/platform.h"
#include "util.h"
#include "zlib.h"

bool gUseRLE = true;

int squaredmetres_to_squaredfeet(int squaredMetres)
{
	// 1 metre squared = 10.7639104 feet squared
	// RCT2 approximates as 11
	return squaredMetres * 11;
}

int metres_to_feet(int metres)
{
	// 1 metre = 3.2808399 feet
	// RCT2 approximates as 3.28125
	return (metres * 840) / 256;
}

int mph_to_kmph(int mph)
{
	// 1 mph = 1.60934 kmph
	// RCT2 approximates as 1.609375
	return (mph * 1648) >> 10;
}

int mph_to_dmps(int mph)
{
	// 1 mph = 4.4704 decimeters/s
	return (mph * 73243) >> 14;
}

bool filename_valid_characters(const utf8 *filename)
{
	for (int i = 0; filename[i] != '\0'; i++) {
		if (filename[i] == '\\' || filename[i] == '/' || filename[i] == ':' || filename[i] == '?' ||
			filename[i] == '*' || filename[i] == '<' || filename[i] == '>' || filename[i] == '|')
			return false;
	}
	return true;
}

utf8 *path_get_directory(const utf8 *path)
{
	// Find the last slash or backslash in the path
	char *filename = strrchr(path, platform_get_path_separator());
	
	// If the path is invalid (e.g. just a file name), return NULL
	if (filename == NULL)
		return NULL;
	
	char *directory = _strdup(path);
	safe_strtrunc(directory, strlen(path) - strlen(filename) + 2);
	
	return directory;
}
	
const char *path_get_filename(const utf8 *path)
{
	// Find last slash or backslash in the path
	char *filename = strrchr(path, platform_get_path_separator());

	// Checks if the path is valid (e.g. not just a file name)
	if (filename == NULL)
	{
		// Return the input string to keep things working
		return path;
	}

	// Increase pointer by one, to get rid of the slashes
	filename++;

	return filename;
}

// Returns the extension (dot inclusive) from the given path, or the end of the
// string when no extension was found.
const char *path_get_extension(const utf8 *path)
{
	// Get the filename from the path
	const char *filename = path_get_filename(path);

	// Try to find the most-right dot in the filename
	char *extension = strrchr(filename, '.');

	// When no dot was found, return a pointer to the null-terminator
	if (extension == NULL)
		extension = strrchr(filename, '\0');

	return extension;
}

void path_set_extension(utf8 *path, const utf8 *newExtension)
{
	// Remove existing extension (check first if there is one)
	if (path_get_extension(path) < strrchr(path, '\0'))
		path_remove_extension(path);
	// Append new extension
	path_append_extension(path, newExtension);
}

void path_append_extension(utf8 *path, const utf8 *newExtension)
{
	// Append a dot to the filename if the new extension doesn't start with it
	char *endOfString = strrchr(path, '\0');
	if (newExtension[0] != '.')
		*endOfString++ = '.';

	// Append the extension to the path
	safe_strcpy(endOfString, newExtension, MAX_PATH - (endOfString - path) - 1);
}

void path_remove_extension(utf8 *path)
{
	// Find last dot in filename, and replace it with a null-terminator
	char *lastDot = strrchr(path_get_filename(path), '.');
	if (lastDot != NULL)
		*lastDot = '\0';
	else
		log_warning("No extension found. (path = %s)", path);
}

bool readentirefile(const utf8 *path, void **outBuffer, int *outLength)
{
	SDL_RWops *fp;
	int fpLength;
	void *fpBuffer;

	// Open file
	fp = SDL_RWFromFile(path, "rb");
	if (fp == NULL)
		return 0;

	// Get length
	fpLength = (int)SDL_RWsize(fp);

	// Read whole file into a buffer
	fpBuffer = malloc(fpLength);
	SDL_RWread(fp, fpBuffer, fpLength, 1);
	SDL_RWclose(fp);

	*outBuffer = fpBuffer;
	*outLength = fpLength;
	return 1;
}

int bitscanforward(int source)
{
	#if defined(_MSC_VER) && (_MSC_VER >= 1400) // Visual Studio 2005
		int i;
		uint8 success = _BitScanForward(&i, source);
		return success != 0 ? i : -1;
	#elif defined(__GNUC__)
		int success = __builtin_ffs(source);
		return success - 1;
	#else
	#pragma message "Falling back to iterative bitscan forward, consider using intrinsics"
	// This is a low-hanging optimisation boost, check if your compiler offers
	// any intrinsic.
	// cf. https://github.com/OpenRCT2/OpenRCT2/pull/2093
	for (int i = 0; i < 32; i++)
		if (source & (1u << i))
			return i;

	return -1;
	#endif
}

int bitcount(int source)
{
	int result = 0;
	for (int i = 0; i < 32; i++) {
		if (source & (1u << i)) {
			result++;
		}
	}
	return result;
}

bool strequals(const char *a, const char *b, int length, bool caseInsensitive)
{
	return caseInsensitive ?
		_strnicmp(a, b, length) == 0 :
		strncmp(a, b, length) == 0;
}

/* case insensitive compare */
int strcicmp(char const *a, char const *b)
{
	for (;; a++, b++) {
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a)
			return d;
	}
}

/* Case insensitive logical compare */
// Example:
// - Guest 10
// - Guest 99
// - Guest 100
// - John v2.0
// - John v2.1
int strlogicalcmp(char const *a, char const *b) {
	for (;; a++, b++) {
		int result = tolower(*a) - tolower(*b);
		bool both_numeric = *a >= '0' && *a <= '9' && *b >= '0' && *b <= '9';
		if (result != 0 || !*a || both_numeric) { // difference found || end of string
			if (both_numeric) { // a and b both start with a number
				// Get the numbers in the string at current positions
				int na = 0 , nb = 0;
				for (; *a >= '0' && *a <= '9'; a++) { na *= 10; na += *a - '0'; }
				for (; *b >= '0' && *b <= '9'; b++) { nb *= 10; nb += *b - '0'; }
				// In case the numbers are the same
				if (na == nb)
					continue;
				return na - nb;
			}
			else {
				return result;
			}
		}
	}

	assert(false);
}

utf8 * safe_strtrunc(utf8 * text, size_t size)
{
	assert(text != NULL);

	if (size == 0) return text;
	
	const char *sourceLimit = text + size - 1;
	char *ch = text;
	char *last = text;
	uint32 codepoint;
	while ((codepoint = utf8_get_next(ch, (const utf8 **)&ch)) != 0) {
		if (ch <= sourceLimit) {
			last = ch;
		} else {
			break;
		}
	}
	*last = 0;

	return text;
}

char *safe_strcpy(char * destination, const char * source, size_t size)
{
	assert(destination != NULL);
	assert(source != NULL);

	if (size == 0) return destination;

	char * result = destination;

	bool truncated = false;
	const char *sourceLimit = source + size - 1;
	const char *ch = source;
	uint32 codepoint;
	while ((codepoint = utf8_get_next(ch, &ch)) != 0) {
		if (ch <= sourceLimit) {
			destination = utf8_write_codepoint(destination, codepoint);
		} else {
			truncated = true;
		}
	}
	*destination = 0;

	if (truncated) {
		log_warning("Truncating string \"%s\" to %d bytes.", result, size);
	}
	return result;
}

char *safe_strcat(char *destination, const char *source, size_t size)
{
	assert(destination != NULL);
	assert(source != NULL);

	if (size == 0) {
		return destination;
	}

	char *result = destination;

	size_t i;
	for (i = 0; i < size; i++) {
		if (*destination == '\0') {
			break;
		} else {
			destination++;
		}
	}

	bool terminated = false;
	for (; i < size; i++) {
		if (*source != '\0') {
			*destination++ = *source++;
		} else {
			*destination = *source;
			terminated = true;
			break;
		}
	}

	if (!terminated) {
		result[size - 1] = '\0';
		log_warning("Truncating string \"%s\" to %d bytes.", result, size);
	}

	return result;
}

char *safe_strcat_path(char *destination, const char *source, size_t size)
{
	const char pathSeparator = platform_get_path_separator();

	size_t length = strnlen(destination, size);
	if (length >= size - 1) {
		return destination;
	}

	if (destination[length - 1] != pathSeparator) {
		destination[length] = pathSeparator;
		destination[length + 1] = '\0';
	}

	return safe_strcat(destination, source, size);
}

char *safe_strtrimleft(char *destination, const char *source, size_t size)
{
	while (*source == ' ' && *source != '\0') {
		source++;
	}
	return safe_strcpy(destination, source, size);
}

bool utf8_is_bom(const char *str)
{
	return str[0] == (char)0xEF && str[1] == (char)0xBB && str[2] == (char)0xBF;
}

bool str_is_null_or_empty(const char *str)
{
	return str == NULL || str[0] == 0;
}

uint32 srand0, srand1, srand2, srand3;

void util_srand(int source) {
	srand0 = source;
	srand1 = srand0 ^ (source >> 24);
	srand2 = srand1 ^ (source >> 16);
	srand3 = srand2 ^ (source >> 8);
}

uint32 util_rand() {
	uint32 temp = srand0 ^ (srand0 << 11);
	srand0 = srand1;
	srand1 = srand2;
	srand2 = srand3;
	srand3 = srand3 ^ (srand3 >> 19) ^ temp ^ (temp >> 8);
	return srand3;
}

#define CHUNK 128*1024
#define MAX_ZLIB_REALLOC 4*1024*1024

/**
 * @brief Inflates zlib-compressed data
 * @param data Data to be decompressed
 * @param data_in_size Size of data to be decompressed
 * @param data_out_size Pointer to a variable where output size will be written. If not 0, it will be used to set initial output buffer size.
 * @return Returns a pointer to memory holding decompressed data or NULL on failure.
 * @note It is caller's responsibility to free() the returned pointer once done with it.
 */
unsigned char *util_zlib_inflate(unsigned char *data, size_t data_in_size, size_t *data_out_size)
{
	int ret = Z_OK;
	uLongf out_size = (uLong)*data_out_size;
	if (out_size == 0)
	{
		// Try to guesstimate the size needed for output data by applying the
		// same ratio it would take to compress data_in_size.
		out_size = (uLong)data_in_size * (uLong)data_in_size / compressBound((uLong)data_in_size);
		out_size = min(MAX_ZLIB_REALLOC, out_size);
	}
	uLongf buffer_size = out_size;
	unsigned char *buffer = malloc(buffer_size);
	do {
		if (ret == Z_BUF_ERROR)
		{
			buffer_size *= 2;
			out_size = buffer_size;
			buffer = realloc(buffer, buffer_size);
		} else if (ret == Z_STREAM_ERROR) {
			log_error("Your build is shipped with broken zlib. Please use the official build.");
			free(buffer);
			return NULL;
		} else if (ret < 0) {
			log_error("Error uncompressing data.");
			free(buffer);
			return NULL;
		}
		ret = uncompress(buffer, &out_size, data, (uLong)data_in_size);
	} while (ret != Z_OK);
	buffer = realloc(buffer, out_size);
	*data_out_size = out_size;
	return buffer;
}

/**
 * @brief Deflates input using zlib
 * @param data Data to be compressed
 * @param data_in_size Size of data to be compressed
 * @param data_out_size Pointer to a variable where output size will be written
 * @return Returns a pointer to memory holding compressed data or NULL on failure.
 * @note It is caller's responsibility to free() the returned pointer once done with it.
 */
unsigned char *util_zlib_deflate(unsigned char *data, size_t data_in_size, size_t *data_out_size)
{
	int ret = Z_OK;
	uLongf out_size = (uLongf)*data_out_size;
	uLong buffer_size = compressBound((uLong)data_in_size);
	unsigned char *buffer = malloc(buffer_size);
	do {
		if (ret == Z_BUF_ERROR)
		{
			buffer_size *= 2;
			out_size = buffer_size;
			buffer = realloc(buffer, buffer_size);
		} else if (ret == Z_STREAM_ERROR) {
			log_error("Your build is shipped with broken zlib. Please use the official build.");
			free(buffer);
			return NULL;
		}
		ret = compress(buffer, &out_size, data, (uLong)data_in_size);
	} while (ret != Z_OK);
	*data_out_size = out_size;
	buffer = realloc(buffer, *data_out_size);
	return buffer;
}
