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

#include "paint.h"
#include "../drawing/drawing.h"
#include "../localisation/localisation.h"
#include "../config.h"
#include "../interface/viewport.h"
#include "map_element/map_element.h"
#include "sprite/sprite.h"
#include "../addresses.h"

const uint32 construction_markers[] = {
	COLOUR_DARK_GREEN << 19 | COLOUR_GREY << 24 | IMAGE_TYPE_USE_PALETTE << 28, // White
	2 << 19 | 0b110000 << 19 | IMAGE_TYPE_MIX_BACKGROUND << 28, // Translucent
};

/**
 *
 *  rct2: 0x0068615B
 */
void painter_setup() {
	RCT2_GLOBAL(0xEE7888, uint32) = 0x00EE788C;
	RCT2_GLOBAL(0xF1AD28, uint32) = 0;
	RCT2_GLOBAL(0xF1AD2C, uint32) = 0;
	uint8* edi = RCT2_ADDRESS(0xF1A50C, uint8);
	memset(edi, 0, 2048);
	RCT2_GLOBAL(0xF1AD0C, sint32) = -1;
	RCT2_GLOBAL(0xF1AD10, uint32) = 0;
	RCT2_GLOBAL(0xF1AD20, uint32) = 0;
	RCT2_GLOBAL(0xF1AD24, uint32) = 0;
}

/**
 * Extracted from 0x0098196c, 0x0098197c, 0x0098198c, 0x0098199c
 */
paint_struct * sub_9819_c(uint32 image_id, rct_xyz16 offset, rct_xyz16 boundBoxSize, rct_xyz16 boundBoxOffset, uint8 rotation)
{
	paint_struct * ps = RCT2_GLOBAL(0xEE7888, paint_struct*);

	if ((uint32) ps >= RCT2_GLOBAL(0xEE7880, uint32))return NULL;

	ps->image_id = image_id;

	uint32 image_element = image_id & 0x7FFFF;
	rct_g1_element * g1Element = gfx_get_g1_element(image_element);

	switch (rotation) {
		case 0:
			rotate_map_coordinates(&offset.x, &offset.y, 0);
			break;
		case 1:
			rotate_map_coordinates(&offset.x, &offset.y, 3);
			break;
		case 2:
			rotate_map_coordinates(&offset.x, &offset.y, 2);
			break;
		case 3:
			rotate_map_coordinates(&offset.x, &offset.y, 1);
			break;
	}
	offset.x += RCT2_GLOBAL(0x9DE568, sint16);
	offset.y += RCT2_GLOBAL(0x9DE56C, sint16);

	rct_xy16 map = coordinate_3d_to_2d(&offset, rotation);

	ps->x = map.x;
	ps->y = map.y;

	int left = map.x + g1Element->x_offset;
	int bottom = map.y + g1Element->y_offset;

	int right = left + g1Element->width;
	int top = bottom + g1Element->height;

	RCT2_GLOBAL(0xF1AD1C, uint16) = left;
	RCT2_GLOBAL(0xF1AD1E, uint16) = bottom;

	rct_drawpixelinfo * dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);

	if (right <= dpi->x)return NULL;
	if (top <= dpi->y)return NULL;
	if (left >= dpi->x + dpi->width)return NULL;
	if (bottom >= dpi->y + dpi->height)return NULL;


	// This probably rotates the variables so they're relative to rotation 0.
	switch (rotation) {
		case 0:
			boundBoxSize.x--;
			boundBoxSize.y--;
			rotate_map_coordinates(&boundBoxOffset.x, &boundBoxOffset.y, 0);
			rotate_map_coordinates(&boundBoxSize.x, &boundBoxSize.y, 0);
			break;
		case 1:
			boundBoxSize.x--;
			rotate_map_coordinates(&boundBoxOffset.x, &boundBoxOffset.y, 3);
			rotate_map_coordinates(&boundBoxSize.x, &boundBoxSize.y, 3);
			break;
		case 2:
			rotate_map_coordinates(&boundBoxSize.x, &boundBoxSize.y, 2);
			rotate_map_coordinates(&boundBoxOffset.x, &boundBoxOffset.y, 2);
			break;
		case 3:
			boundBoxSize.y--;
			rotate_map_coordinates(&boundBoxSize.x, &boundBoxSize.y, 1);
			rotate_map_coordinates(&boundBoxOffset.x, &boundBoxOffset.y, 1);
			break;
	}

	ps->bound_box_x_end = boundBoxSize.x + boundBoxOffset.x + RCT2_GLOBAL(0x9DE568, sint16);
	ps->bound_box_z = boundBoxOffset.z;
	ps->bound_box_z_end = boundBoxOffset.z + boundBoxSize.z;
	ps->bound_box_y_end = boundBoxSize.y + boundBoxOffset.y + RCT2_GLOBAL(0x009DE56C, sint16);
	ps->flags = 0;
	ps->bound_box_x = boundBoxOffset.x + RCT2_GLOBAL(0x9DE568, sint16);
	ps->bound_box_y = boundBoxOffset.y + RCT2_GLOBAL(0x009DE56C, sint16);
	ps->attached_ps = NULL;
	ps->var_20 = NULL;
	ps->sprite_type = RCT2_GLOBAL(RCT2_ADDRESS_PAINT_SETUP_CURRENT_TYPE, uint8);
	ps->var_29 = RCT2_GLOBAL(0x9DE571, uint8);
	ps->map_x = RCT2_GLOBAL(0x9DE574, uint16);
	ps->map_y = RCT2_GLOBAL(0x9DE576, uint16);
	ps->mapElement = RCT2_GLOBAL(0x9DE578, rct_map_element*);

	return ps;
}

/**
 *  rct2: 0x006861AC, 0x00686337, 0x006864D0, 0x0068666B, 0x0098196C
 *
 * @param image_id (ebx)
 * @param x_offset (al)
 * @param y_offset (cl)
 * @param bound_box_length_x (di)
 * @param bound_box_length_y (si)
 * @param bound_box_length_z (ah)
 * @param z_offset (dx)
 * @param rotation (ebp)
 * @return (ebp) paint_struct on success (CF == 0), NULL on failure (CF == 1)
 */
paint_struct * sub_98196C(
	uint32 image_id,
	sint8 x_offset, sint8 y_offset,
	sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z,
	sint16 z_offset,
	uint32 rotation
) {
	assert((uint16) bound_box_length_x == (sint16) bound_box_length_x);
	assert((uint16) bound_box_length_y == (sint16) bound_box_length_y);

	RCT2_GLOBAL(0xF1AD28, paint_struct*) = 0;
	RCT2_GLOBAL(0xF1AD2C, uint32) = 0;

	//Not a paint struct but something similar
	paint_struct *ps = RCT2_GLOBAL(0xEE7888, paint_struct*);

	if ((uint32) ps >= RCT2_GLOBAL(0xEE7880, uint32)) {
		return NULL;
	}

	ps->image_id = image_id;

	uint32 image_element = image_id & 0x7FFFF;
	rct_g1_element *g1Element = gfx_get_g1_element(image_element);

	rct_xyz16 coord_3d = {
		.x = x_offset, // ax
		.y = y_offset, // cx
		.z = z_offset
	};

	rct_xyz16 boundBox = {
		.x = bound_box_length_x, // di
		.y = bound_box_length_y, // si
		.z = bound_box_length_z,
	};

	switch (rotation) {
		case 0:
			rotate_map_coordinates(&coord_3d.x, &coord_3d.y, MAP_ELEMENT_DIRECTION_WEST);

			boundBox.x--;
			boundBox.y--;
			rotate_map_coordinates(&boundBox.x, &boundBox.y, MAP_ELEMENT_DIRECTION_WEST);
			break;

		case 1:
			rotate_map_coordinates(&coord_3d.x, &coord_3d.y, MAP_ELEMENT_DIRECTION_SOUTH);

			boundBox.x--;
			rotate_map_coordinates(&boundBox.x, &boundBox.y, MAP_ELEMENT_DIRECTION_SOUTH);
			break;

		case 2:
			rotate_map_coordinates(&coord_3d.x, &coord_3d.y, MAP_ELEMENT_DIRECTION_EAST);
			rotate_map_coordinates(&boundBox.x, &boundBox.y, MAP_ELEMENT_DIRECTION_EAST);
			break;

		case 3:
			rotate_map_coordinates(&coord_3d.x, &coord_3d.y, MAP_ELEMENT_DIRECTION_NORTH);

			boundBox.y--;
			rotate_map_coordinates(&boundBox.x, &boundBox.y, MAP_ELEMENT_DIRECTION_NORTH);
			break;
	}

	coord_3d.x += RCT2_GLOBAL(0x9DE568, sint16);
	coord_3d.y += RCT2_GLOBAL(0x9DE56C, sint16);

	ps->bound_box_x_end = coord_3d.x + boundBox.x;
	ps->bound_box_y_end = coord_3d.y + boundBox.y;

	// TODO: check whether this is right. edx is ((bound_box_length_z + z_offset) << 16 | z_offset)
	ps->bound_box_z = coord_3d.z;
	ps->bound_box_z_end = (boundBox.z + coord_3d.z);

	rct_xy16 map = coordinate_3d_to_2d(&coord_3d, rotation);

	ps->x = map.x;
	ps->y = map.y;

	sint16 left = map.x + g1Element->x_offset;
	sint16 bottom = map.y + g1Element->y_offset;

	sint16 right = left + g1Element->width;
	sint16 top = bottom + g1Element->height;

	RCT2_GLOBAL(0xF1AD1C, sint16) = left;
	RCT2_GLOBAL(0xF1AD1E, sint16) = bottom;

	rct_drawpixelinfo *dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);

	if (right <= dpi->x) return NULL;
	if (top <= dpi->y) return NULL;
	if (left >= (dpi->x + dpi->width)) return NULL;
	if (bottom >= (dpi->y + dpi->height)) return NULL;

	ps->flags = 0;
	ps->bound_box_x = coord_3d.x;
	ps->bound_box_y = coord_3d.y;
	ps->attached_ps = NULL;
	ps->var_20 = NULL;
	ps->sprite_type = RCT2_GLOBAL(RCT2_ADDRESS_PAINT_SETUP_CURRENT_TYPE, uint8);
	ps->var_29 = RCT2_GLOBAL(0x9DE571, uint8);
	ps->map_x = RCT2_GLOBAL(0x9DE574, uint16);
	ps->map_y = RCT2_GLOBAL(0x9DE576, uint16);
	ps->mapElement = RCT2_GLOBAL(0x9DE578, rct_map_element*);

	RCT2_GLOBAL(0xF1AD28, paint_struct*) = ps;

	sint32 edi;
	switch (rotation) {
		case 0:
			edi = coord_3d.y + coord_3d.x;
			break;

		case 1:
			edi = coord_3d.y - coord_3d.x + 0x2000;
			break;

		case 2:
			edi = -(coord_3d.y + coord_3d.x) + 0x4000;
			break;

		case 3:
			edi = coord_3d.x - coord_3d.y + 0x2000;
			break;
	}

	if (edi < 0) {
		edi = 0;
	}

	edi /= 32;
	edi = min(edi, 0x1FF); // 511

	ps->var_18 = edi;

	paint_struct *old_ps = RCT2_ADDRESS(0x00F1A50C, paint_struct*)[edi];
	RCT2_ADDRESS(0x00F1A50C, paint_struct*)[edi] = ps;
	ps->next_quadrant_ps = old_ps;

	if ((uint16)edi < RCT2_GLOBAL(0x00F1AD0C, uint32)) {
		RCT2_GLOBAL(0x00F1AD0C, uint32) = edi;
	}

	if ((uint16)edi > RCT2_GLOBAL(0x00F1AD10, uint32)) {
		RCT2_GLOBAL(0x00F1AD10, uint32) = edi;
	}

	RCT2_GLOBAL(0xEE7888, paint_struct*) ++;

	return ps;
}

/**
 *  rct2: 0x00686806, 0x006869B2, 0x00686B6F, 0x00686D31, 0x0098197C
 *
 * @param image_id (ebx)
 * @param x_offset (al)
 * @param y_offset (cl)
 * @param bound_box_length_x (di)
 * @param bound_box_length_y (si)
 * @param bound_box_length_z (ah)
 * @param z_offset (dx)
 * @param bound_box_offset_x (0x009DEA52)
 * @param bound_box_offset_y (0x009DEA54)
 * @param bound_box_offset_z (0x009DEA56)
 * @param rotation (ebp)
 * @return (ebp) paint_struct on success (CF == 0), NULL on failure (CF == 1)
 */
paint_struct * sub_98197C(
	uint32 image_id,
	sint8 x_offset, sint8 y_offset,
	sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z,
	sint16 z_offset,
	sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z,
	uint32 rotation
) {

	RCT2_GLOBAL(0xF1AD28, paint_struct*) = 0;
	RCT2_GLOBAL(0xF1AD2C, uint32) = 0;

	rct_xyz16 offset = {.x = x_offset, .y = y_offset, .z = z_offset};
	rct_xyz16 boundBoxSize = {.x = bound_box_length_x, .y = bound_box_length_y, .z = bound_box_length_z};
	rct_xyz16 boundBoxOffset = {.x = bound_box_offset_x, .y = bound_box_offset_y, .z = bound_box_offset_z};
	paint_struct * ps = sub_9819_c(image_id, offset, boundBoxSize, boundBoxOffset, rotation);

	if (ps == NULL) {
		return NULL;
	}

	RCT2_GLOBAL(0xF1AD28, paint_struct*) = ps;

	rct_xy16 attach = {
		.x = ps->bound_box_x,
		.y = ps->bound_box_y
	};

	rotate_map_coordinates(&attach.x, &attach.y, rotation);
	switch (rotation) {
	case 0:
		break;
	case 1:
	case 3:
		attach.x += 0x2000;
		break;
	case 2:
		attach.x += 0x4000;
		break;
	}

	sint16 di = attach.x + attach.y;

	if (di < 0)
		di = 0;

	di /= 32;
	if (di > 511)
		di = 511;

	ps->var_18 = di;
	paint_struct* old_ps = RCT2_ADDRESS(0x00F1A50C, paint_struct*)[di];
	RCT2_ADDRESS(0x00F1A50C, paint_struct*)[di] = ps;
	ps->next_quadrant_ps = old_ps;

	if ((uint16)di < RCT2_GLOBAL(0x00F1AD0C, uint32)) {
		RCT2_GLOBAL(0x00F1AD0C, uint32) = di;
	}

	if ((uint16)di > RCT2_GLOBAL(0x00F1AD10, uint32)) {
		RCT2_GLOBAL(0x00F1AD10, uint32) = di;
	}

	RCT2_GLOBAL(0xEE7888, paint_struct*)++;
	return ps;
}

/**
 *
 *  rct2: 0x00686EF0, 0x00687056, 0x006871C8, 0x0068733C, 0x0098198C
 *
 * @param image_id (ebx)
 * @param x_offset (al)
 * @param y_offset (cl)
 * @param bound_box_length_x (di)
 * @param bound_box_length_y (si)
 * @param bound_box_length_z (ah)
 * @param z_offset (dx)
 * @param bound_box_offset_x (0x009DEA52)
 * @param bound_box_offset_y (0x009DEA54)
 * @param bound_box_offset_z (0x009DEA56)
 * @param rotation (ebp)
 * @return (ebp) paint_struct on success (CF == 0), NULL on failure (CF == 1)
 */
paint_struct * sub_98198C(
	uint32 image_id,
	sint8 x_offset, sint8 y_offset,
	sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z,
	sint16 z_offset,
	sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z,
	uint32 rotation
) {
	assert((uint16) bound_box_length_x == (sint16) bound_box_length_x);
	assert((uint16) bound_box_length_y == (sint16) bound_box_length_y);

	RCT2_GLOBAL(0xF1AD28, paint_struct*) = 0;
	RCT2_GLOBAL(0xF1AD2C, uint32) = 0;

	rct_xyz16 offset = {.x = x_offset, .y = y_offset, .z = z_offset};
	rct_xyz16 boundBoxSize = {.x = bound_box_length_x, .y = bound_box_length_y, .z = bound_box_length_z};
	rct_xyz16 boundBoxOffset = {.x = bound_box_offset_x, .y = bound_box_offset_y, .z = bound_box_offset_z};
	paint_struct * ps = sub_9819_c(image_id, offset, boundBoxSize, boundBoxOffset, rotation);

	if (ps == NULL) {
		return NULL;
	}

	RCT2_GLOBAL(0xF1AD28, paint_struct*) = ps;
	RCT2_GLOBAL(0xEE7888, paint_struct*)++;
	return ps;
}

/**
 *
 *  rct2: 0x006874B0, 0x00687618, 0x0068778C, 0x00687902, 0x0098199C
 *
 * @param image_id (ebx)
 * @param x_offset (al)
 * @param y_offset (cl)
 * @param bound_box_length_x (di)
 * @param bound_box_length_y (si)
 * @param bound_box_length_z (ah)
 * @param z_offset (dx)
 * @param bound_box_offset_x (0x009DEA52)
 * @param bound_box_offset_y (0x009DEA54)
 * @param bound_box_offset_z (0x009DEA56)
 * @param rotation (ebp)
 * @return (ebp) paint_struct on success (CF == 0), NULL on failure (CF == 1)
 */
paint_struct * sub_98199C(
	uint32 image_id,
	sint8 x_offset, sint8 y_offset,
	sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z,
	sint16 z_offset,
	sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z,
	uint32 rotation
) {
	assert((uint16) bound_box_length_x == (sint16) bound_box_length_x);
	assert((uint16) bound_box_length_y == (sint16) bound_box_length_y);

	if (RCT2_GLOBAL(0xF1AD28, uint32) == 0) {
		return sub_98197C(
			image_id,
			x_offset, y_offset,
			bound_box_length_x, bound_box_length_y, bound_box_length_z,
			z_offset,
			bound_box_offset_x, bound_box_offset_y, bound_box_offset_z,
			rotation
		);
	}

	rct_xyz16 offset = {.x = x_offset, .y = y_offset, .z = z_offset};
	rct_xyz16 boundBox = {.x = bound_box_length_x, .y = bound_box_length_y, .z = bound_box_length_z};
	rct_xyz16 boundBoxOffset = {.x = bound_box_offset_x, .y = bound_box_offset_y, .z = bound_box_offset_z};
	paint_struct * ps = sub_9819_c(image_id, offset, boundBox, boundBoxOffset, rotation);

	if (ps == NULL) {
		return NULL;
	}

	paint_struct *old_ps = RCT2_GLOBAL(0xF1AD28, paint_struct*);
	old_ps->var_20 = ps;

	RCT2_GLOBAL(0xF1AD28, paint_struct*) = ps;
	RCT2_GLOBAL(0xEE7888, paint_struct*)++;
	return ps;
}

/**
 * rct2: 0x006881D0
 *
 * @param image_id (ebx)
 * @param x (ax)
 * @param y (cx)
 * @return (!CF) success
 */
bool paint_attach_to_previous_attach(uint32 image_id, uint16 x, uint16 y)
{
    if (RCT2_GLOBAL(0xF1AD2C, uint32) == 0) {
        return paint_attach_to_previous_ps(image_id, x, y);
    }

    attached_paint_struct * ps = RCT2_GLOBAL(0xEE7888, attached_paint_struct *);

    if ((uint32) ps >= RCT2_GLOBAL(0xEE7880, uint32)) {
        return false;
    }

    ps->image_id = image_id;
    ps->x = x;
    ps->y = y;
    ps->flags = 0;

    attached_paint_struct * ebx = RCT2_GLOBAL(0xF1AD2C, attached_paint_struct *);

    ps->next = NULL;
    ebx->next = ps;

    RCT2_GLOBAL(0xF1AD2C, attached_paint_struct *) = ps;

    RCT2_GLOBAL(0xEE7888, attached_paint_struct *)++;

    return true;
}

/**
 * rct2: 0x0068818E
 *
 * @param image_id (ebx)
 * @param x (ax)
 * @param y (cx)
 * @return (!CF) success
 */
bool paint_attach_to_previous_ps(uint32 image_id, uint16 x, uint16 y)
{
    attached_paint_struct * ps = RCT2_GLOBAL(0xEE7888, attached_paint_struct *);

    if ((uint32) ps >= RCT2_GLOBAL(0xEE7880, uint32)) {
        return false;
    }

    ps->image_id = image_id;
    ps->x = x;
    ps->y = y;
    ps->flags = 0;

    paint_struct * masterPs = RCT2_GLOBAL(0xF1AD28, paint_struct *);
    if (masterPs == NULL) {
        return false;
    }

    RCT2_GLOBAL(0x00EE7888, attached_paint_struct *)++;

    attached_paint_struct * oldFirstAttached = masterPs->attached_ps;
	masterPs->attached_ps = ps;

    ps->next = oldFirstAttached;

    RCT2_GLOBAL(0xF1AD2C, attached_paint_struct *) = ps;

    return true;
}

/**
 * rct2: 0x00685EBC, 0x00686046, 0x00685FC8, 0x00685F4A, 0x00685ECC
 * @param amount (eax)
 * @param string_id (bx)
 * @param y (cx)
 * @param z (dx)
 * @param offset_x (si)
 * @param y_offsets (di)
 * @param rotation (ebp)
 */
void sub_685EBC(money32 amount, uint16 string_id, sint16 y, sint16 z, sint8 y_offsets[], sint16 offset_x, uint32 rotation)
{
	paint_string_struct * ps = RCT2_GLOBAL(0xEE7888, paint_string_struct*);

	if ((uint32) ps >= RCT2_GLOBAL(0xEE7880, uint32)) {
		return;
	}

	ps->string_id = string_id;
	ps->next = 0;
	ps->args[0] = amount;
	ps->args[1] = y;
	ps->args[2] = (int) y_offsets;
	ps->args[3] = 0;
	ps->y_offsets = (uint8 *) y_offsets;

	rct_xyz16 position = {.x = RCT2_GLOBAL(0x9DE568, sint16), .y = RCT2_GLOBAL(0x9DE56C, sint16), .z = z};
	rct_xy16 coord = coordinate_3d_to_2d(&position, rotation);

	ps->x = coord.x + offset_x;
	ps->y = coord.y;

	RCT2_GLOBAL(0xEE7888, paint_string_struct*)++;

	paint_string_struct * oldPs = RCT2_GLOBAL(0xF1AD24, paint_string_struct*);

	RCT2_GLOBAL(0xF1AD24, paint_string_struct*) = ps;

	if (oldPs == 0) { // 0 or NULL?
		RCT2_GLOBAL(0xF1AD20, paint_string_struct *) = ps;
	} else {
		oldPs->next = ps;
	}
}

/**
 *
 *  rct2: 0x0068B6C2
 */
void viewport_paint_setup()
{
	rct_drawpixelinfo* dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);

	rct_xy16 mapTile = {
		.x = dpi->x & 0xFFE0,
		.y = (dpi->y - 16) & 0xFFE0
	};

	sint16 half_x = mapTile.x >> 1;

	uint16 num_vertical_quadrants = (dpi->height + 2128) >> 5;

	switch (get_current_rotation()){
	case 0:
		mapTile.x = mapTile.y - half_x;
		mapTile.y = mapTile.y + half_x;

		mapTile.x &= 0xFFE0;
		mapTile.y &= 0xFFE0;

		for (; num_vertical_quadrants > 0; --num_vertical_quadrants){
			map_element_paint_setup(mapTile.x, mapTile.y);
			sprite_paint_setup(mapTile.x, mapTile.y);

			sprite_paint_setup(mapTile.x - 32, mapTile.y + 32);

			map_element_paint_setup(mapTile.x, mapTile.y + 32);
			sprite_paint_setup(mapTile.x, mapTile.y + 32);

			mapTile.x += 32;
			sprite_paint_setup(mapTile.x, mapTile.y);

			mapTile.y += 32;
		}
		break;
	case 1:
		mapTile.x = -mapTile.y - half_x;
		mapTile.y = mapTile.y - half_x - 16;

		mapTile.x &= 0xFFE0;
		mapTile.y &= 0xFFE0;

		for (; num_vertical_quadrants > 0; --num_vertical_quadrants){
			map_element_paint_setup(mapTile.x, mapTile.y);
			sprite_paint_setup(mapTile.x, mapTile.y);

			sprite_paint_setup(mapTile.x - 32, mapTile.y - 32);

			map_element_paint_setup(mapTile.x - 32, mapTile.y);
			sprite_paint_setup(mapTile.x - 32, mapTile.y);

			mapTile.y += 32;
			sprite_paint_setup(mapTile.x, mapTile.y);

			mapTile.x -= 32;
		}
		break;
	case 2:
		mapTile.x = -mapTile.y + half_x;
		mapTile.y = -mapTile.y - half_x;

		mapTile.x &= 0xFFE0;
		mapTile.y &= 0xFFE0;

		for (; num_vertical_quadrants > 0; --num_vertical_quadrants){
			map_element_paint_setup(mapTile.x, mapTile.y);
			sprite_paint_setup(mapTile.x, mapTile.y);

			sprite_paint_setup(mapTile.x + 32, mapTile.y - 32);

			map_element_paint_setup(mapTile.x, mapTile.y - 32);
			sprite_paint_setup(mapTile.x, mapTile.y - 32);

			mapTile.x -= 32;

			sprite_paint_setup(mapTile.x, mapTile.y);

			mapTile.y -= 32;
		}
		break;
	case 3:
		mapTile.x = mapTile.y + half_x;
		mapTile.y = -mapTile.y + half_x - 16;

		mapTile.x &= 0xFFE0;
		mapTile.y &= 0xFFE0;

		for (; num_vertical_quadrants > 0; --num_vertical_quadrants){
			map_element_paint_setup(mapTile.x, mapTile.y);
			sprite_paint_setup(mapTile.x, mapTile.y);

			sprite_paint_setup(mapTile.x + 32, mapTile.y + 32);

			map_element_paint_setup(mapTile.x + 32, mapTile.y);
			sprite_paint_setup(mapTile.x + 32, mapTile.y);

			mapTile.y -= 32;

			sprite_paint_setup(mapTile.x, mapTile.y);

			mapTile.x += 32;
		}
		break;
	}
}

void sub_688217_helper(uint16 ax, uint8 flag)
{
	paint_struct *ps, *ps_temp;
	paint_struct *ps_next = RCT2_GLOBAL(0x00EE7884, paint_struct*);

	do {
		ps = ps_next;
		ps_next = ps_next->next_quadrant_ps;
		if (ps_next == NULL) return;
	} while (ax > ps_next->var_18);

	ps_temp = ps;

	do {
		ps = ps->next_quadrant_ps;
		if (ps == NULL) break;

		if (ps->var_18 > ax + 1) {
			ps->var_1B = 1 << 7;
		}
		else if (ps->var_18 == ax + 1) {
			ps->var_1B = (1 << 1) | (1 << 0);
		}
		else if (ps->var_18 == ax) {
			ps->var_1B = flag | (1 << 0);
		}
	} while (ps->var_18 <= ax + 1);

	ps = ps_temp;

	uint8 rotation = get_current_rotation();
	while (true) {
		while (true) {
			ps_next = ps->next_quadrant_ps;
			if (ps_next == NULL) return;
			if (ps_next->var_1B & (1 << 7)) return;
			if (ps_next->var_1B & (1 << 0)) break;
			ps = ps_next;
		}

		ps_next->var_1B &= ~(1 << 0);
		ps_temp = ps;

		typedef struct bound_box {
			uint16 x;
			uint16 y;
			uint16 z;
			uint16 x_end;
			uint16 y_end;
			uint16 z_end;
		} bound_box;

		bound_box initialBBox = {
			.x = ps_next->bound_box_x,
			.y = ps_next->bound_box_y,
			.z = ps_next->bound_box_z,
			.x_end = ps_next->bound_box_x_end,
			.y_end = ps_next->bound_box_y_end,
			.z_end = ps_next->bound_box_z_end
		};


		while (true) {
			ps = ps_next;
			ps_next = ps_next->next_quadrant_ps;
			if (ps_next == NULL) break;
			if (ps_next->var_1B & (1 << 7)) break;
			if (!(ps_next->var_1B & (1 << 1))) continue;

			int yes = 0;
			switch (rotation) {
			case 0:
				if (initialBBox.z_end >= ps_next->bound_box_z && initialBBox.y_end >= ps_next->bound_box_y && initialBBox.x_end >= ps_next->bound_box_x
					&& !(initialBBox.z < ps_next->bound_box_z_end && initialBBox.y < ps_next->bound_box_y_end && initialBBox.x < ps_next->bound_box_x_end))
					yes = 1;
				break;
			case 1:
				if (initialBBox.z_end >= ps_next->bound_box_z && initialBBox.y_end >= ps_next->bound_box_y && initialBBox.x_end < ps_next->bound_box_x
					&& !(initialBBox.z < ps_next->bound_box_z_end && initialBBox.y < ps_next->bound_box_y_end && initialBBox.x >= ps_next->bound_box_x_end))
					yes = 1;
				break;
			case 2:
				if (initialBBox.z_end >= ps_next->bound_box_z && initialBBox.y_end < ps_next->bound_box_y && initialBBox.x_end < ps_next->bound_box_x
					&& !(initialBBox.z < ps_next->bound_box_z_end && initialBBox.y >= ps_next->bound_box_y_end && initialBBox.x >= ps_next->bound_box_x_end))
					yes = 1;
				break;
			case 3:
				if (initialBBox.z_end >= ps_next->bound_box_z && initialBBox.y_end < ps_next->bound_box_y && initialBBox.x_end >= ps_next->bound_box_x
					&& !(initialBBox.z < ps_next->bound_box_z_end && initialBBox.y >= ps_next->bound_box_y_end && initialBBox.x < ps_next->bound_box_x_end))
					yes = 1;
				break;
			}

			if (yes) {
				ps->next_quadrant_ps = ps_next->next_quadrant_ps;
				paint_struct *ps_temp2 = ps_temp->next_quadrant_ps;
				ps_temp->next_quadrant_ps = ps_next;
				ps_next->next_quadrant_ps = ps_temp2;
				ps_next = ps;
			}
		}

		ps = ps_temp;
	}
}

/**
 *
 *  rct2: 0x00688217
 */
void sub_688217()
{
	paint_struct *ps = RCT2_GLOBAL(0x00EE7888, paint_struct*);
	paint_struct *ps_next;
	RCT2_GLOBAL(0x00EE7888, paint_struct*)++;
	RCT2_GLOBAL(0x00EE7884, paint_struct*) = ps;
	ps->next_quadrant_ps = NULL;
	uint32 edi = RCT2_GLOBAL(0x00F1AD0C, uint32);
	if (edi == -1)
		return;

	do {
		ps_next = RCT2_GLOBAL(0x00F1A50C + 4 * edi, paint_struct*);
		if (ps_next != NULL) {
			ps->next_quadrant_ps = ps_next;
			do {
				ps = ps_next;
				ps_next = ps_next->next_quadrant_ps;
			} while (ps_next != NULL);
		}
	} while (++edi <= RCT2_GLOBAL(0x00F1AD10, uint32));

	uint32 eax = RCT2_GLOBAL(0x00F1AD0C, uint32);

	sub_688217_helper(eax & 0xFFFF, 1 << 1);

	eax = RCT2_GLOBAL(0x00F1AD0C, uint32);

	while (++eax < RCT2_GLOBAL(0x00F1AD10, uint32))
		sub_688217_helper(eax & 0xFFFF, 0);
}

/**
 *
 *  rct2: 0x00688596
 *  Part of 0x688485
 */
void paint_attached_ps(paint_struct* ps, attached_paint_struct* attached_ps, rct_drawpixelinfo* dpi) {
	for (; attached_ps; attached_ps = attached_ps->next) {
		sint16 x = attached_ps->x + ps->x;
		sint16 y = attached_ps->y + ps->y;

		int image_id = attached_ps->image_id;
		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_RIDES) {
			if (ps->sprite_type == 3) {
				if (image_id & 0x40000000) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}

		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_SCENERY) {
			if (ps->sprite_type == 5) {
				if (image_id & 0x40000000) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}

		if (attached_ps->flags & PAINT_STRUCT_FLAG_IS_MASKED) {
			gfx_draw_sprite_raw_masked(dpi, x, y, image_id, attached_ps->colour_image_id);
		}
		else {
			gfx_draw_sprite(dpi, image_id, x, y, ps->tertiary_colour);
		}
	}
}

/* rct2: 0x00688485 */
void paint_quadrant_ps() {
	rct_drawpixelinfo* dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);
	paint_struct* ps = RCT2_GLOBAL(0xEE7884, paint_struct*);
	paint_struct* previous_ps = ps->next_quadrant_ps;

	for (ps = ps->next_quadrant_ps; ps;) {
		sint16 x = ps->x;
		sint16 y = ps->y;
		if (ps->sprite_type == 2) {
			if (dpi->zoom_level >= 1) {
				x &= 0xFFFE;
				y &= 0xFFFE;
				if (dpi->zoom_level >= 2) {
					x &= 0xFFFC;
					y &= 0xFFFC;
				}
			}
		}
		int image_id = ps->image_id;
		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_RIDES) {
			if (ps->sprite_type == 3) {
				if (!(image_id & 0x40000000)) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}
		if (gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE) {
			if (ps->sprite_type == 9) {
				if (!(image_id & 0x40000000)) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}
		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_SCENERY) {
			if (ps->sprite_type == 10 || ps->sprite_type == 12 || ps->sprite_type == 9 || ps->sprite_type == 5) {
				if (!(image_id & 0x40000000)) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}

		if (ps->flags & PAINT_STRUCT_FLAG_IS_MASKED)
			gfx_draw_sprite_raw_masked(dpi, x, y, image_id, ps->colour_image_id);
		else
			gfx_draw_sprite(dpi, image_id, x, y, ps->tertiary_colour);

		if (ps->var_20 != 0) {
			ps = ps->var_20;
			continue;
		}

		paint_attached_ps(ps, ps->attached_ps, dpi);
		ps = previous_ps->next_quadrant_ps;
		previous_ps = ps;
	}

}

static void draw_pixel_info_crop_by_zoom(rct_drawpixelinfo *dpi)
{
	int zoom = dpi->zoom_level;
	dpi->zoom_level = 0;
	dpi->x >>= zoom;
	dpi->y >>= zoom;
	dpi->width >>= zoom;
	dpi->height >>= zoom;
}

/**
 *
 *  rct2: 0x006860C3
 */
void viewport_draw_money_effects()
{
	utf8 buffer[256];

	paint_string_struct *ps = RCT2_GLOBAL(0x00F1AD20, paint_string_struct*);
	if (ps == NULL)
		return;

	rct_drawpixelinfo dpi = *(RCT2_GLOBAL(0x0140E9A8, rct_drawpixelinfo*));
	draw_pixel_info_crop_by_zoom(&dpi);

	do {
		format_string(buffer, ps->string_id, &ps->args);
		gCurrentFontSpriteBase = FONT_SPRITE_BASE_MEDIUM;

		bool forceSpriteFont = false;
		const currency_descriptor *currencyDesc = &CurrencyDescriptors[gConfigGeneral.currency_format];
		if (gUseTrueTypeFont && font_supports_string_sprite(currencyDesc->symbol_unicode)) {
			forceSpriteFont = true;
		}

		gfx_draw_string_with_y_offsets(&dpi, buffer, 0, ps->x, ps->y, (sint8 *)ps->y_offsets, forceSpriteFont);
	} while ((ps = ps->next) != NULL);
}
