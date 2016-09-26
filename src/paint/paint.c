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

const uint32 construction_markers[] = {
	COLOUR_DARK_GREEN << 19 | COLOUR_GREY << 24 | IMAGE_TYPE_REMAP, // White
	2 << 19 | 0b110000 << 19 | IMAGE_TYPE_TRANSPARENT, // Translucent
};

paint_struct * g_ps_F1AD28;
attached_paint_struct * g_aps_F1AD2C;
paint_string_struct *pss1;
paint_string_struct *pss2;

#ifdef NO_RCT2
paint_entry gPaintStructs[4000];
uint32 _F1AD0C;
uint32 _F1AD10;
static paint_struct *_paint_struct_quadrants[512];
void *g_currently_drawn_item;
paint_entry * gEndOfPaintStructArray;
sint16 gUnk9DE568;
sint16 gUnk9DE56C;
paint_struct gUnkF1A4CC;
uint8 gPaintInteractionType;
support_height gSupportSegments[9] = { 0 };
support_height gSupport;

#else
#define _paint_struct_quadrants (RCT2_ADDRESS(0x00F1A50C, paint_struct*))
#define _F1AD0C RCT2_GLOBAL(0xF1AD0C, uint32)
#define _F1AD10 RCT2_GLOBAL(0xF1AD10, uint32)
#endif

static const uint8 BoundBoxDebugColours[] = {
	0,   // NONE
	102, // TERRAIN
	114, // SPRITE
	229, // RIDE
	126, // WATER
	138, // SCENERY
	150, // FOOTPATH
	162, // FOOTPATH_ITEM
	174, // PARK
	186, // WALL
	198, // LARGE_SCENERY
	210, // LABEL
	222, // BANNER
};

bool gPaintBoundingBoxes;

/**
 *
 *  rct2: 0x0068615B
 */
void painter_setup() {
	gNextFreePaintStruct = gPaintStructs;
	g_ps_F1AD28 = NULL;
	g_aps_F1AD2C = NULL;
	for (int i = 0; i < 512; i++) {
		_paint_struct_quadrants[i] = NULL;
	}
	_F1AD0C = -1;
	_F1AD10 = 0;
	pss1 = NULL;
	pss2 = NULL;
}

/**
 * Extracted from 0x0098196c, 0x0098197c, 0x0098198c, 0x0098199c
 */
static paint_struct * sub_9819_c(uint32 image_id, rct_xyz16 offset, rct_xyz16 boundBoxSize, rct_xyz16 boundBoxOffset, uint8 rotation)
{
	if (gNextFreePaintStruct >= gEndOfPaintStructArray) return NULL;
	paint_struct * ps = &gNextFreePaintStruct->basic;

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
	offset.x += gUnk9DE568;
	offset.y += gUnk9DE56C;

	rct_xy16 map = coordinate_3d_to_2d(&offset, rotation);

	ps->x = map.x;
	ps->y = map.y;

	int left = map.x + g1Element->x_offset;
	int bottom = map.y + g1Element->y_offset;

	int right = left + g1Element->width;
	int top = bottom + g1Element->height;

	rct_drawpixelinfo * dpi = unk_140E9A8;

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

	ps->bound_box_x_end = boundBoxSize.x + boundBoxOffset.x + gUnk9DE568;
	ps->bound_box_z = boundBoxOffset.z;
	ps->bound_box_z_end = boundBoxOffset.z + boundBoxSize.z;
	ps->bound_box_y_end = boundBoxSize.y + boundBoxOffset.y + gUnk9DE56C;
	ps->flags = 0;
	ps->bound_box_x = boundBoxOffset.x + gUnk9DE568;
	ps->bound_box_y = boundBoxOffset.y + gUnk9DE56C;
	ps->attached_ps = NULL;
	ps->var_20 = NULL;
	ps->sprite_type = gPaintInteractionType;
	ps->var_29 = 0;
	ps->map_x = gPaintMapPosition.x;
	ps->map_y = gPaintMapPosition.y;
	ps->mapElement = g_currently_drawn_item;
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

	g_ps_F1AD28 = 0;
	g_aps_F1AD2C = NULL;

	if (gNextFreePaintStruct >= gEndOfPaintStructArray) {
		return NULL;
	}

	paint_struct *ps = &gNextFreePaintStruct->basic;
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

	coord_3d.x += gUnk9DE568;
	coord_3d.y += gUnk9DE56C;

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

	rct_drawpixelinfo *dpi = unk_140E9A8;

	if (right <= dpi->x) return NULL;
	if (top <= dpi->y) return NULL;
	if (left >= (dpi->x + dpi->width)) return NULL;
	if (bottom >= (dpi->y + dpi->height)) return NULL;

	ps->flags = 0;
	ps->bound_box_x = coord_3d.x;
	ps->bound_box_y = coord_3d.y;
	ps->attached_ps = NULL;
	ps->var_20 = NULL;
	ps->sprite_type = gPaintInteractionType;
	ps->var_29 = 0;
	ps->map_x = gPaintMapPosition.x;
	ps->map_y = gPaintMapPosition.y;
	ps->mapElement = g_currently_drawn_item;

	g_ps_F1AD28 = ps;

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

	paint_struct *old_ps = _paint_struct_quadrants[edi];
	_paint_struct_quadrants[edi] = ps;
	ps->next_quadrant_ps = old_ps;

	if ((uint16)edi < _F1AD0C) {
		_F1AD0C = edi;
	}

	if ((uint16)edi > _F1AD10) {
		_F1AD10 = edi;
	}

	gNextFreePaintStruct++;

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

	g_ps_F1AD28 = 0;
	g_aps_F1AD2C = NULL;

	rct_xyz16 offset = {.x = x_offset, .y = y_offset, .z = z_offset};
	rct_xyz16 boundBoxSize = {.x = bound_box_length_x, .y = bound_box_length_y, .z = bound_box_length_z};
	rct_xyz16 boundBoxOffset = {.x = bound_box_offset_x, .y = bound_box_offset_y, .z = bound_box_offset_z};
	paint_struct * ps = sub_9819_c(image_id, offset, boundBoxSize, boundBoxOffset, rotation);

	if (ps == NULL) {
		return NULL;
	}

	g_ps_F1AD28 = ps;

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
	paint_struct* old_ps = _paint_struct_quadrants[di];
	_paint_struct_quadrants[di] = ps;
	ps->next_quadrant_ps = old_ps;

	if ((uint16)di < _F1AD0C) {
		_F1AD0C = di;
	}

	if ((uint16)di > _F1AD10) {
		_F1AD10 = di;
	}

	gNextFreePaintStruct++;
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

	g_ps_F1AD28 = 0;
	g_aps_F1AD2C = NULL;

	rct_xyz16 offset = {.x = x_offset, .y = y_offset, .z = z_offset};
	rct_xyz16 boundBoxSize = {.x = bound_box_length_x, .y = bound_box_length_y, .z = bound_box_length_z};
	rct_xyz16 boundBoxOffset = {.x = bound_box_offset_x, .y = bound_box_offset_y, .z = bound_box_offset_z};
	paint_struct * ps = sub_9819_c(image_id, offset, boundBoxSize, boundBoxOffset, rotation);

	if (ps == NULL) {
		return NULL;
	}

	g_ps_F1AD28 = ps;
	gNextFreePaintStruct++;
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

	if (g_ps_F1AD28 == NULL) {
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

	paint_struct *old_ps = g_ps_F1AD28;
	old_ps->var_20 = ps;

	g_ps_F1AD28 = ps;
	gNextFreePaintStruct++;
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
    if (g_aps_F1AD2C == NULL) {
        return paint_attach_to_previous_ps(image_id, x, y);
    }
	
	if (gNextFreePaintStruct >= gEndOfPaintStructArray) {
        return false;
    }
	attached_paint_struct * ps = &gNextFreePaintStruct->attached;
    ps->image_id = image_id;
    ps->x = x;
    ps->y = y;
    ps->flags = 0;

    attached_paint_struct * ebx = g_aps_F1AD2C;

    ps->next = NULL;
    ebx->next = ps;

	g_aps_F1AD2C = ps;

	gNextFreePaintStruct++;

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
	if (gNextFreePaintStruct >= gEndOfPaintStructArray) {
        return false;
    }
	attached_paint_struct * ps = &gNextFreePaintStruct->attached;

    ps->image_id = image_id;
    ps->x = x;
    ps->y = y;
    ps->flags = 0;

	paint_struct * masterPs = g_ps_F1AD28;
    if (masterPs == NULL) {
        return false;
    }

	gNextFreePaintStruct++;

    attached_paint_struct * oldFirstAttached = masterPs->attached_ps;
	masterPs->attached_ps = ps;

    ps->next = oldFirstAttached;

	g_aps_F1AD2C = ps;

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
void sub_685EBC(money32 amount, rct_string_id string_id, sint16 y, sint16 z, sint8 y_offsets[], sint16 offset_x, uint32 rotation)
{
	if (gNextFreePaintStruct >= gEndOfPaintStructArray) {
        return;
    }
	paint_string_struct * ps = &gNextFreePaintStruct->string;

	ps->string_id = string_id;
	ps->next = 0;
	ps->args[0] = amount;
	ps->args[1] = y;
	ps->args[2] = 0;
	ps->args[3] = 0;
	ps->y_offsets = (uint8 *) y_offsets;

	rct_xyz16 position = {.x = gUnk9DE568, .y = gUnk9DE56C, .z = z};
	rct_xy16 coord = coordinate_3d_to_2d(&position, rotation);

	ps->x = coord.x + offset_x;
	ps->y = coord.y;

	gNextFreePaintStruct++;

	paint_string_struct * oldPs = pss2;

	pss2 = ps;

	if (oldPs == 0) { // 0 or NULL?
		pss1 = ps;
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
	rct_drawpixelinfo* dpi = unk_140E9A8;

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

static void sub_688217_helper(uint16 ax, uint8 flag)
{
	paint_struct *ps, *ps_temp;
	paint_struct *ps_next = &unk_EE7884->basic;

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

	paint_struct *ps_next;
	unk_EE7884 = gNextFreePaintStruct++;
	paint_struct *ps = &unk_EE7884->basic;
	ps->next_quadrant_ps = NULL;
	uint32 edi = _F1AD0C;
	if (edi == -1)
		return;

	do {
		ps_next = _paint_struct_quadrants[edi];
		if (ps_next != NULL) {
			ps->next_quadrant_ps = ps_next;
			do {
				ps = ps_next;
				ps_next = ps_next->next_quadrant_ps;
			} while (ps_next != NULL);
		}
	} while (++edi <= _F1AD10);

	uint32 eax = _F1AD0C;

	sub_688217_helper(eax & 0xFFFF, 1 << 1);

	eax = _F1AD0C;

	while (++eax < _F1AD10)
		sub_688217_helper(eax & 0xFFFF, 0);
}

/**
 *
 *  rct2: 0x00688596
 *  Part of 0x688485
 */
static void paint_attached_ps(paint_struct* ps, attached_paint_struct* attached_ps, rct_drawpixelinfo* dpi) {
	for (; attached_ps; attached_ps = attached_ps->next) {
		sint16 x = attached_ps->x + ps->x;
		sint16 y = attached_ps->y + ps->y;

		int image_id = attached_ps->image_id;
		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_RIDES) {
			if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_RIDE) {
				if (image_id & 0x40000000) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}

		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_SCENERY) {
			if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_SCENERY) {
				if (image_id & 0x40000000) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}
		
		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_PATHS) {
			if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_FOOTPATH) {
				if (!(image_id & 0x40000000)) {
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
	rct_drawpixelinfo* dpi = unk_140E9A8;
	paint_struct* ps = &unk_EE7884->basic;
	paint_struct* previous_ps = ps->next_quadrant_ps;

	for (ps = ps->next_quadrant_ps; ps;) {
		sint16 x = ps->x;
		sint16 y = ps->y;
		if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_SPRITE) {
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
			if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_RIDE) {
				if (!(image_id & 0x40000000)) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}
		if (gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE) {
			if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_WALL) {
				if (!(image_id & 0x40000000)) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}
		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_PATHS) {
			if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_FOOTPATH || 
				ps->sprite_type == VIEWPORT_INTERACTION_ITEM_FOOTPATH_ITEM ||
				ps->sprite_type == VIEWPORT_INTERACTION_ITEM_BANNER) {
				if (!(image_id & 0x40000000)) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}
		if (gCurrentViewportFlags & VIEWPORT_FLAG_SEETHROUGH_SCENERY) {
			if (ps->sprite_type == VIEWPORT_INTERACTION_ITEM_LARGE_SCENERY || 
				ps->sprite_type == VIEWPORT_INTERACTION_ITEM_WALL || 
				ps->sprite_type == VIEWPORT_INTERACTION_ITEM_SCENERY) {
				if (!(image_id & 0x40000000)) {
					image_id &= 0x7FFFF;
					image_id |= 0x41880000;
				}
			}
		}

		if (gPaintBoundingBoxes && dpi->zoom_level == 0) {
			uint8 colour = BoundBoxDebugColours[ps->sprite_type];

			rct_xyz16 frontTop = {.x = ps->bound_box_x_end, .y = ps->bound_box_y_end, .z = ps->bound_box_z_end};
			rct_xy16 screenCoordFrontTop = coordinate_3d_to_2d(&frontTop, get_current_rotation());
			rct_xyz16 frontBottom = {.x = ps->bound_box_x_end, .y = ps->bound_box_y_end, .z = ps->bound_box_z};
			rct_xy16 screenCoordFrontBottom = coordinate_3d_to_2d(&frontBottom, get_current_rotation());

			rct_xyz16 leftTop = {.x = ps->bound_box_x, .y = ps->bound_box_y_end, .z = ps->bound_box_z_end};
			rct_xy16 screenCoordLeftTop = coordinate_3d_to_2d(&leftTop, get_current_rotation());
			rct_xyz16 leftBottom = {.x = ps->bound_box_x, .y = ps->bound_box_y_end, .z = ps->bound_box_z};
			rct_xy16 screenCoordLeftBottom = coordinate_3d_to_2d(&leftBottom, get_current_rotation());

			rct_xyz16 rightTop = {.x = ps->bound_box_x_end, .y = ps->bound_box_y, .z = ps->bound_box_z_end};
			rct_xy16 screenCoordRightTop = coordinate_3d_to_2d(&rightTop, get_current_rotation());
			rct_xyz16 rightBottom = {.x = ps->bound_box_x_end, .y = ps->bound_box_y, .z = ps->bound_box_z};
			rct_xy16 screenCoordRightBottom = coordinate_3d_to_2d(&rightBottom, get_current_rotation());

			rct_xyz16 backTop = {.x = ps->bound_box_x, .y = ps->bound_box_y, .z = ps->bound_box_z_end};
			rct_xy16 screenCoordBackTop = coordinate_3d_to_2d(&backTop, get_current_rotation());
			rct_xyz16 backBottom = {.x = ps->bound_box_x, .y = ps->bound_box_y, .z = ps->bound_box_z};
			rct_xy16 screenCoordBackBottom = coordinate_3d_to_2d(&backBottom, get_current_rotation());

			// bottom square
			gfx_draw_line(dpi, screenCoordFrontBottom.x, screenCoordFrontBottom.y, screenCoordLeftBottom.x, screenCoordLeftBottom.y, colour);
			gfx_draw_line(dpi, screenCoordBackBottom.x, screenCoordBackBottom.y, screenCoordLeftBottom.x, screenCoordLeftBottom.y, colour);
			gfx_draw_line(dpi, screenCoordBackBottom.x, screenCoordBackBottom.y, screenCoordRightBottom.x, screenCoordRightBottom.y, colour);
			gfx_draw_line(dpi, screenCoordFrontBottom.x, screenCoordFrontBottom.y, screenCoordRightBottom.x, screenCoordRightBottom.y, colour);

			//vertical back + sides
			gfx_draw_line(dpi, screenCoordBackTop.x, screenCoordBackTop.y, screenCoordBackBottom.x, screenCoordBackBottom.y, colour);
			gfx_draw_line(dpi, screenCoordLeftTop.x, screenCoordLeftTop.y, screenCoordLeftBottom.x, screenCoordLeftBottom.y, colour);
			gfx_draw_line(dpi, screenCoordRightTop.x, screenCoordRightTop.y, screenCoordRightBottom.x, screenCoordRightBottom.y, colour);

			// top square back
			gfx_draw_line(dpi, screenCoordBackTop.x, screenCoordBackTop.y, screenCoordLeftTop.x, screenCoordLeftTop.y, colour);
			gfx_draw_line(dpi, screenCoordBackTop.x, screenCoordBackTop.y, screenCoordRightTop.x, screenCoordRightTop.y, colour);

			if (ps->flags & PAINT_STRUCT_FLAG_IS_MASKED) {
				gfx_draw_sprite_raw_masked(dpi, x, y, image_id, ps->colour_image_id);
			} else {
				gfx_draw_sprite(dpi, image_id, x, y, ps->tertiary_colour);
			}

			// vertical front
			gfx_draw_line(dpi, screenCoordFrontTop.x, screenCoordFrontTop.y, screenCoordFrontBottom.x, screenCoordFrontBottom.y, colour);

			// top square
			gfx_draw_line(dpi, screenCoordFrontTop.x, screenCoordFrontTop.y, screenCoordLeftTop.x, screenCoordLeftTop.y, colour);
			gfx_draw_line(dpi, screenCoordFrontTop.x, screenCoordFrontTop.y, screenCoordRightTop.x, screenCoordRightTop.y, colour);
		} else {
			if (ps->flags & PAINT_STRUCT_FLAG_IS_MASKED) {
				gfx_draw_sprite_raw_masked(dpi, x, y, image_id, ps->colour_image_id);
			} else {
				gfx_draw_sprite(dpi, image_id, x, y, ps->tertiary_colour);
			}
		}


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

	paint_string_struct *ps = pss1;
	if (ps == NULL)
		return;

	rct_drawpixelinfo dpi = *(unk_140E9A8);
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
