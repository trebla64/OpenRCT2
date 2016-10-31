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

#include "../../cheats.h"
#include "../../common.h"
#include "../../config.h"
#include "../../interface/viewport.h"
#include "../../peep/staff.h"
#include "../../world/map.h"
#include "../paint.h"
#include "map_element.h"
#include "surface.h"

const uint8 byte_97B444[] = {
	0, 2, 1, 3, 8, 10, 9, 11, 4, 6,
	5, 7, 12, 14, 13, 15, 0, 0, 0, 0,
	0, 0, 0, 17, 0, 0, 0, 16, 0, 18,
	15, 0
};

// rct2: 0x97B464, 0x97B474, 0x97B484, 0x97B494
const rct_xy16 viewport_surface_paint_data[][4] = {
	{
		{32,  0},
		{-32, 32},
		{-64, -32},
		{0,   -64}
	},
	{
		{0,   32},
		{-64, 0},
		{-32, -64},
		{32,  -32}
	},
	{
		{0,   -32},
		{0,   0},
		{-32, 0},
		{-32, -32}
	},
	{
		{-32, 0},
		{-32, -32},
		{0,   -32},
		{0,   0}
	}
};

enum
{
	CORNER_TOP,
	CORNER_RIGHT,
	CORNER_BOTTOM,
	CORNER_LEFT
};

typedef struct corner_height corner_height;

struct corner_height
{
	uint8 top;
	uint8 right;
	uint8 bottom;
	uint8 left;
};

/**
 * rct2: 0x0097B4A4 (R), 0x0097B4C4 (T), 0x0097B4E4 (L), 0x0097B504 (B)
 */
const corner_height corner_heights[] = {
//   T  R  B  L
	{0, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	{0, 0, 1, 1},
	{1, 0, 0, 0},
	{1, 0, 1, 0},
	{1, 0, 0, 1},
	{1, 0, 1, 1},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 1},
	{0, 1, 1, 1},
	{1, 1, 0, 0},
	{1, 1, 1, 0},
	{1, 1, 0, 1},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	{0, 0, 1, 1},
	{1, 0, 0, 0},
	{1, 0, 1, 0},
	{1, 0, 0, 1},
	{1, 0, 1, 2},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 1},
	{0, 1, 2, 1},
	{1, 1, 0, 0},
	{1, 2, 1, 0},
	{2, 1, 0, 1},
	{1, 1, 1, 1},
};

// bottom left tint
const uint8 byte_97B524[] = {
	2, 5, 1, 4, 2, 5, 1, 2, 2, 4,
	1, 2, 1, 3, 0, 3, 1, 5, 0
};

// top left tint
const uint32 byte_97B537[] = {
	2, 5, 2, 4, 2, 5, 1, 1, 3, 4,
	3, 2, 1, 2, 0, 3, 1, 5, 0
};

// top right tint
const uint8 byte_97B54A[] = {
	2, 2, 2, 4, 0, 0, 1, 1, 3, 4,
	3, 5, 1, 2, 2, 3, 1, 5, 0
};

// bottom right tint
const uint8 byte_97B55D[] = {
	2, 2, 1, 4, 0, 0, 1, 2, 2, 4,
	1, 5, 1, 3, 2, 3, 1, 5, 0
};

const uint8 stru_97B570[][2] = {
	{2, 2},
	{3, 3},
	{3, 5},
	{3, 3},
	{4, 4},
	{4, 6},
	{2, 2},
	{3, 3},
	{3, 5},
	{3, 3},
	{2, 3},
	{2, 3},
	{2, 3},
	{3, 4},
	{2, 3},
	{3, 4}
};

const sint16 word_97B590[] = {
	0,
	0,
	-32,
	0,
	0,
	-48,
	0,
	0,
	-32,
	0,
	-16,
	-16,
	-16,
	-16,
	-16,
	-16,
};

// tunnel offset
const uint8 byte_97B5B0[] = {
	0, 0, 0, 3, 3, 3, 6, 6, 6, 6,
	10, 11, 12, 13, 14, 14
};

const uint32 stru_97B5C0[][5] = {
	{1579, 1599, 1589, 1609, 0},
	{1747, 1767, 1757, 1777, 1},
	{1663, 1683, 1673, 1693, 2},
	{1831, 1851, 1841, 1861, 3},
};

const uint32 stru_97B640[][16] = {
	{1615, 1619, 1623, 1627, 1631, 1635, 1639, 1643, 1647, 1651, 1655, 1659, 1615, 1627, 1639, 1651},
	{1783, 1787, 1791, 1795, 1799, 1803, 1807, 1811, 1815, 1819, 1823, 1827, 1783, 1795, 1807, 1819},
	{1699, 1703, 1707, 1711, 1715, 1719, 1723, 1727, 1731, 1735, 1739, 1743, 1699, 1711, 1723, 1735},
	{1867, 1871, 1875, 1879, 1883, 1887, 1891, 1895, 1899, 1903, 1907, 1911, 1867, 1879, 1891, 1903},
};

const uint8 byte_97B740[] = {
	0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
	0, 3, 0, 1, 4, 0
};

const uint32 dword_97B750[][2] = {
	{SPR_TERRAIN_GRASS,                                          SPR_TERRAIN_GRASS_GRID},
	{SPR_TERRAIN_SAND_YELLOW,                                    SPR_TERRAIN_SAND_YELLOW_GRID},
	{SPR_TERRAIN_DIRT,                                           SPR_TERRAIN_DIRT_GRID},
	{SPR_TERRAIN_ROCK,                                           SPR_TERRAIN_ROCK_GRID},
	{SPR_TERRAIN_MARTIAN,                                        SPR_TERRAIN_MARTIAN_GRID},
	{SPR_TERRAIN_CHECKERBOARD,                                   SPR_TERRAIN_CHECKERBOARD_GRID},
	{SPR_TERRAIN_GRASS_CLUMPS,                                   SPR_TERRAIN_GRASS_CLUMPS_GRID},
	{SPR_TERRAIN_ICE,                                            SPR_TERRAIN_ICE_GRID},
	{SPR_TERRAIN_GRID | COLOUR_BRIGHT_RED << 19 | 0x20000000,    SPR_TERRAIN_GRID_GRID | COLOUR_BRIGHT_RED << 19 | 0x20000000},
	{SPR_TERRAIN_GRID | COLOUR_YELLOW << 19 | 0x20000000,        SPR_TERRAIN_GRID_GRID | COLOUR_YELLOW << 19 | 0x20000000},
	{SPR_TERRAIN_GRID | COLOUR_BRIGHT_PURPLE << 19 | 0x20000000, SPR_TERRAIN_GRID_GRID | COLOUR_BRIGHT_PURPLE << 19 | 0x20000000},
	{SPR_TERRAIN_GRID | COLOUR_BRIGHT_GREEN << 19 | 0x20000000,  SPR_TERRAIN_GRID_GRID | COLOUR_BRIGHT_GREEN << 19 | 0x20000000},
	{SPR_TERRAIN_SAND_RED,                                       SPR_TERRAIN_SAND_RED_GRID},
	{SPR_TERRAIN_SAND,                                           SPR_TERRAIN_SAND_GRID},
	{SPR_TERRAIN_CHECKERBOARD_INVERTED,                          SPR_TERRAIN_CHECKERBOARD_INVERTED_GRID},
};

const uint32 dword_97B7C8[] = {
	SPR_TERRAIN_GRASS_UNDERGROUND,
	SPR_TERRAIN_SAND_YELLOW_UNDERGROUND,
	SPR_TERRAIN_DIRT_UNDERGROUND,
	SPR_TERRAIN_ROCK_UNDERGROUND,
	SPR_TERRAIN_MARTIAN_UNDERGROUND,
	SPR_TERRAIN_CHECKERBOARD_UNDERGROUND,
	SPR_TERRAIN_GRASS_CLUMPS_UNDERGROUND,
	SPR_TERRAIN_ICE_UNDERGROUND,
	SPR_TERRAIN_GRID_UNDERGROUND | COLOUR_BRIGHT_RED << 19 | 0x20000000,
	SPR_TERRAIN_GRID_UNDERGROUND | COLOUR_YELLOW << 19 | 0x20000000,
	SPR_TERRAIN_GRID_UNDERGROUND | COLOUR_BRIGHT_PURPLE << 19 | 0x20000000,
	SPR_TERRAIN_GRID_UNDERGROUND | COLOUR_BRIGHT_GREEN << 19 | 0x20000000,
	SPR_TERRAIN_SAND_RED_UNDERGROUND,
	SPR_TERRAIN_SAND_UNDERGROUND,
	SPR_TERRAIN_CHECKERBOARD_INVERTED_UNDERGROUND,
};

const uint32 dword_97B804[] = {
	SPR_TERRAIN_PATTERN_GRASS,
	SPR_TERRAIN_PATTERN_SAND_YELLOW,
	SPR_TERRAIN_PATTERN_DIRT,
	SPR_TERRAIN_PATTERN_ROCK,
	SPR_TERRAIN_PATTERN_MARTIAN,
	SPR_TERRAIN_PATTERN_GRASS,
	SPR_TERRAIN_PATTERN_GRASS_CLUMPS,
	SPR_TERRAIN_PATTERN_ICE,
	SPR_TERRAIN_PATTERN_GRASS,
	SPR_TERRAIN_PATTERN_GRASS,
	SPR_TERRAIN_PATTERN_GRASS,
	SPR_TERRAIN_PATTERN_GRASS,
	SPR_TERRAIN_PATTERN_SAND_RED,
	SPR_TERRAIN_PATTERN_SAND
};

enum
{
	FLAG_DONT_SMOOTHEN = (1 << 0),
	FLAG_DONT_SMOOTHEN_SELF = (1 << 1),
};

const uint8 byte_97B83C[] = {
	0, // GRASS
	0, // SAND (YELLOW)
	0, // DIRT
	FLAG_DONT_SMOOTHEN_SELF, // ROCK
	FLAG_DONT_SMOOTHEN_SELF, // MARTIAN
	FLAG_DONT_SMOOTHEN_SELF | FLAG_DONT_SMOOTHEN, // GRASS
	0, // GRASS_CLUMPS
	0, // ICE
	FLAG_DONT_SMOOTHEN_SELF | FLAG_DONT_SMOOTHEN, // GRASS
	FLAG_DONT_SMOOTHEN_SELF | FLAG_DONT_SMOOTHEN, // GRASS
	FLAG_DONT_SMOOTHEN_SELF | FLAG_DONT_SMOOTHEN, // GRASS
	FLAG_DONT_SMOOTHEN_SELF | FLAG_DONT_SMOOTHEN, // GRASS
	0, // SAND_RED
	0  // SAND
};

const uint8 byte_97B84A[] = {
	0, 1, 2, 3, 4, 14, 6, 7, 8, 9,
	10, 11, 12, 13
};

const uint32 dword_97B858[][2] = {
	{SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_1, SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_1_GRID},
	{SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_2, SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_2_GRID},
	{SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_3, SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_3_GRID},
	{SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_4, SPR_TERRAIN_GRASS_LENGTH_4_VARIANT_4_GRID},
};

const uint32 dword_97B878[][2] = {
	{SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_1, SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_1_GRID},
	{SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_2, SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_2_GRID},
	{SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_3, SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_3_GRID},
	{SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_4, SPR_TERRAIN_GRASS_LENGTH_6_VARIANT_4_GRID},
};

const uint32 dword_97B898[][2] = {
	{SPR_TERRAIN_GRASS_MOWED_90, SPR_TERRAIN_GRASS_MOWED_90_GRID},
	{SPR_TERRAIN_GRASS_MOWED,    SPR_TERRAIN_GRASS_MOWED_GRID},
	{SPR_TERRAIN_GRASS_MOWED_90, SPR_TERRAIN_GRASS_MOWED_90_GRID},
	{SPR_TERRAIN_GRASS_MOWED,    SPR_TERRAIN_GRASS_MOWED_GRID}
};

typedef struct tile_descriptor tile_descriptor;

struct tile_descriptor
{
	rct_map_element * map_element;
	uint8 terrain;
	uint8 slope;
	corner_height corner_heights;
};

static uint8 viewport_surface_paint_setup_get_relative_slope(rct_map_element * mapElement, int rotation)
{
	uint8 slope = mapElement->properties.surface.slope;

	uint16 di = (slope & 0x0F) << rotation;
	uint8 ebx = slope & 0x10;

	di = ((di >> 4) | di) & 0x0F;
	return ebx | di;
}

/**
 * rct2: 0x0065E890, 0x0065E946, 0x0065E9FC, 0x0065EAB2
 */
static void viewport_surface_smoothen_edge(enum edge edge, struct tile_descriptor self, struct tile_descriptor neighbour)
{

	if (neighbour.map_element == NULL) {
		return;
	}

	uint32 maskImageBase = 0;
	uint8 neighbourCorners[2] = { 0 };
	uint8 ownCorners[2] = { 0 };

	switch (edge) {
		case EDGE_BOTTOMLEFT:
			maskImageBase = SPR_TERRAIN_EDGE_MASK_BOTTOM_LEFT;
			neighbourCorners[0] = neighbour.corner_heights.top;
			neighbourCorners[1] = neighbour.corner_heights.right;
			ownCorners[0] = self.corner_heights.left;
			ownCorners[1] = self.corner_heights.bottom;
			break;
		case EDGE_BOTTOMRIGHT:
			maskImageBase = SPR_TERRAIN_EDGE_MASK_BOTTOM_RIGHT;
			neighbourCorners[0] = neighbour.corner_heights.top;
			neighbourCorners[1] = neighbour.corner_heights.left;
			ownCorners[0] = self.corner_heights.right;
			ownCorners[1] = self.corner_heights.bottom;
			break;
		case EDGE_TOPLEFT:
			maskImageBase = SPR_TERRAIN_EDGE_MASK_TOP_LEFT;
			neighbourCorners[0] = neighbour.corner_heights.right;
			neighbourCorners[1] = neighbour.corner_heights.bottom;
			ownCorners[0] = self.corner_heights.top;
			ownCorners[1] = self.corner_heights.left;
			break;
		case EDGE_TOPRIGHT:
			maskImageBase = SPR_TERRAIN_EDGE_MASK_TOP_RIGHT;
			neighbourCorners[0] = neighbour.corner_heights.left;
			neighbourCorners[1] = neighbour.corner_heights.bottom;
			ownCorners[0] = self.corner_heights.top;
			ownCorners[1] = self.corner_heights.right;
			break;
	}

	if (ownCorners[0] != neighbourCorners[0] || ownCorners[1] != neighbourCorners[1]) {
		// Only smoothen tiles that align
		return;
	}

	uint8 dh = 0, cl = 0;
	switch(edge) {
		case EDGE_BOTTOMLEFT:
			dh = byte_97B524[byte_97B444[self.slope]];
			cl = byte_97B54A[byte_97B444[neighbour.slope]];
			break;

		case EDGE_TOPLEFT:
			dh = byte_97B537[byte_97B444[self.slope]];
			cl = byte_97B55D[byte_97B444[neighbour.slope]];
			break;

		case EDGE_BOTTOMRIGHT:
			dh = byte_97B55D[byte_97B444[self.slope]];
			cl = byte_97B537[byte_97B444[neighbour.slope]];
			break;

		case EDGE_TOPRIGHT:
			dh = byte_97B54A[byte_97B444[self.slope]];
			cl = byte_97B524[byte_97B444[neighbour.slope]];
			break;

	}

	if (self.terrain == neighbour.terrain) {
		// same tint
		if (cl == dh) {
			return;
		}

		if (byte_97B83C[self.terrain] & FLAG_DONT_SMOOTHEN_SELF) {
			return;
		}
	} else {
		if (byte_97B83C[self.terrain] & FLAG_DONT_SMOOTHEN) {
			return;
		}

		if (byte_97B83C[neighbour.terrain] & FLAG_DONT_SMOOTHEN) {
			return;
		}
	}

	uint32 image_id = maskImageBase + byte_97B444[self.slope];

	attached_paint_struct * out;
	if (paint_attach_to_previous_ps(image_id, 0, 0)) {
		out = g_aps_F1AD2C;
		// set content and enable masking
		out->colour_image_id = dword_97B804[neighbour.terrain] + cl;
		out->flags |= PAINT_STRUCT_FLAG_IS_MASKED;
	}
}

/**
 * rct2: 0x0065F63B, 0x0065F77D
 */
static void viewport_surface_draw_land_side_top(enum edge edge, uint8 height, uint8 terrain, struct tile_descriptor self, struct tile_descriptor neighbour)
{
	registers regs;

	rct_xy8 offset = {0, 0};
	rct_xy8 bounds = {0, 0};
	switch (edge) {
		case EDGE_TOPLEFT:
			regs.al = self.corner_heights.top;
			regs.cl = self.corner_heights.left;

			regs.ah = neighbour.corner_heights.right;
			regs.ch = neighbour.corner_heights.bottom;

			offset.y = -2;
			bounds.x = 30;
			break;

		case EDGE_TOPRIGHT:
			regs.al = self.corner_heights.top;
			regs.cl = self.corner_heights.right;

			regs.ah = neighbour.corner_heights.left;
			regs.ch = neighbour.corner_heights.bottom;

			offset.x = -2;
			bounds.y = 30;
			break;

		default:
			return;
	}

	regs.dl = height;

	// save ecx
	if (neighbour.map_element == NULL) {
		regs.ah = 1;
		regs.ch = 1;
	}

	// al + cl probably are self tile corners, while ah/ch are neighbour tile corners
	if (regs.al <= regs.ah && regs.cl <= regs.ch) {
		return;
	}

	if (!(gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE)) {
		uint8 incline = (regs.cl - regs.al) + 1;

		uint32 image_id = stru_97B5C0[terrain][3] + (edge == EDGE_TOPLEFT ? 3 : 0) + incline; // var_c;
		sint16 y = (regs.dl - regs.al) * 16;
		paint_attach_to_previous_ps(image_id, 0, y);
		return;
	}

	uint32 base_image_id = stru_97B5C0[terrain][1] + (edge == EDGE_TOPLEFT ? 5 : 0); // var_04

	const uint8 rotation = get_current_rotation();
	uint8 cur_height = min(regs.ch, regs.ah);
	if (regs.ch != regs.ah) {
		// neightbour tile corners aren't level
		uint32 image_offset = 3;
		if (regs.ch > regs.ah) {
			image_offset = 4;
		}

		if (cur_height != regs.al && cur_height != regs.cl) {
			uint32 image_id = base_image_id + image_offset;
			sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, cur_height * 16, rotation);
			cur_height++;
		}
	}

	regs.ah = regs.cl;

	while (cur_height < regs.al && cur_height < regs.ah) {
		sub_98196C(base_image_id, offset.x, offset.y, bounds.x, bounds.y, 15, cur_height * 16, rotation);
		cur_height++;
	}

	uint32 image_offset = 1;
	if (cur_height >= regs.al) {
		image_offset = 2;

		if (cur_height >= regs.ah) {
			return;
		}
	}

	uint32 image_id = base_image_id + image_offset;
	sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, cur_height * 16, rotation);
}

/**
 * rct2: 0x0065EB7D, 0x0065F0D8
 */
static void viewport_surface_draw_land_side_bottom(enum edge edge, uint8 height, uint8 edgeStyle, struct tile_descriptor self, struct tile_descriptor neighbour)
{
	registers regs;

	rct_xy8 offset = {0, 0};
	rct_xy8 bounds = {0, 0};
	rct_xy16 tunnelBounds = {1, 1};
	rct_xy16 tunnelTopBoundBoxOffset = {0, 0};

	tunnel_entry * tunnelArray;
	switch (edge) {
		case EDGE_BOTTOMLEFT:
			regs.al = self.corner_heights.left;
			regs.cl = self.corner_heights.bottom;

			regs.ah = neighbour.corner_heights.top;
			regs.ch = neighbour.corner_heights.right;

			offset.x = 30;
			bounds.y = 30;
			tunnelBounds.x = 32;
			tunnelTopBoundBoxOffset.y = 31;

			tunnelArray = gLeftTunnels;
			break;

		case EDGE_BOTTOMRIGHT:
			regs.al = self.corner_heights.right;
			regs.cl = self.corner_heights.bottom;

			regs.ah = neighbour.corner_heights.top;
			regs.ch = neighbour.corner_heights.left;

			offset.y = 30;
			bounds.x = 30;
			tunnelBounds.y = 32;
			tunnelTopBoundBoxOffset.x = 31;

			tunnelArray = gRightTunnels;
			break;

		default:
			return;
	}

	if (neighbour.map_element == 0) {
		regs.ch = 1;
		regs.ah = 1;
	}

	if (regs.al <= regs.ah && regs.cl <= regs.ch) {
		return;
	}

	uint32 base_image_id = stru_97B5C0[edgeStyle][0];
	if (gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE) {
		base_image_id = stru_97B5C0[edgeStyle][1];
	}

	if (edge == EDGE_BOTTOMRIGHT) {
		base_image_id += 5;
	}

	const uint8 rotation = get_current_rotation();
	uint8 curHeight = min(regs.ah, regs.ch);
	if (regs.ch != regs.ah) {
		// If bottom part of edge isn't straight, add a filler
		uint32 image_offset = 3;

		if (regs.ch >= regs.ah) {
			image_offset = 4;
		}

		if (curHeight != regs.al && curHeight != regs.cl) {
			uint32 image_id = base_image_id + image_offset;
			sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, curHeight * 16, rotation);
			curHeight++;
		}
	}

	regs.ah = regs.cl;

	while (true) {
		if (curHeight >= regs.al || curHeight >= regs.cl) {
			// If top of edge isn't straight, add a filler
			uint32 image_offset = 1;
			if (curHeight >= regs.al) {
				image_offset = 2;

				if (curHeight >= regs.cl) {
					return;
				}
			}

			uint32 image_id = base_image_id + image_offset;

			sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, curHeight * 16, rotation);

			return;
		}

		if (curHeight != tunnelArray[0].height) {
			// Normal walls
			while (curHeight > tunnelArray[0].height) {
				// TODO: Should probably be done by just keeping track of the current index
				memmove(&tunnelArray[0], &tunnelArray[1], sizeof(tunnel_entry) * (TUNNEL_MAX_COUNT - 1));
			}

			if (curHeight != tunnelArray[0].height) {
				sub_98196C(base_image_id, offset.x, offset.y, bounds.x, bounds.y, 15, curHeight * 16, rotation);

				curHeight++;
				continue;
			}
		}
		
		// Tunnels
		uint8 tunnelType = tunnelArray[0].type;
		uint8 tunnelHeight = stru_97B570[tunnelType][0];
		sint16 zOffset = curHeight;

		if ((zOffset + tunnelHeight) > regs.ah || (zOffset + tunnelHeight) > regs.al) {
			tunnelType = byte_97B5B0[tunnelType];
		}

		zOffset *= 16;

		sint16 boundBoxOffsetZ = zOffset + word_97B590[tunnelType];
		sint8 boundBoxLength = stru_97B570[tunnelType][1] * 16;
		if (boundBoxOffsetZ < 16) {
			boundBoxOffsetZ += 16;
			boundBoxLength -= 16;
		}


		uint32 image_id = stru_97B640[edgeStyle][tunnelType] + (edge == EDGE_BOTTOMRIGHT ? 2 : 0);
		sub_98197C(image_id, offset.x, offset.y, tunnelBounds.x, tunnelBounds.y, boundBoxLength - 1, zOffset, 0, 0, boundBoxOffsetZ, rotation);


		boundBoxOffsetZ = curHeight * 16;
		boundBoxLength = stru_97B570[tunnelType][1] * 16;
		boundBoxOffsetZ += word_97B590[tunnelType];
		if (boundBoxOffsetZ == 0) {
			boundBoxOffsetZ += 16;
			boundBoxLength -= 16;
		}

		image_id = stru_97B640[edgeStyle][tunnelType] + (edge == EDGE_BOTTOMRIGHT ? 2 : 0) + 1;
		sub_98197C(image_id, offset.x, offset.y, tunnelBounds.x, tunnelBounds.y, boundBoxLength - 1, curHeight * 16, tunnelTopBoundBoxOffset.x, tunnelTopBoundBoxOffset.y, boundBoxOffsetZ, rotation);

		curHeight += stru_97B570[tunnelType][0];

		// TODO: Should probably be done by just keeping track of the current index
		memmove(&tunnelArray[0], &tunnelArray[1], sizeof(tunnel_entry) * (TUNNEL_MAX_COUNT - 1));
	}
}

/**
 * rct2: 0x0066039B, 0x006604F1
 */
static void viewport_surface_draw_water_side_top(enum edge edge, uint8 height, uint8 terrain, struct tile_descriptor self, struct tile_descriptor neighbour)
{
	registers regs;

	rct_xy8 offset = {0, 0};
	rct_xy8 bounds = {0, 0};
	switch (edge) {
		case EDGE_TOPLEFT:
			regs.al = self.corner_heights.top;
			regs.cl = self.corner_heights.left;

			regs.ah = neighbour.corner_heights.right;
			regs.ch = neighbour.corner_heights.bottom;

			offset.y = -2;
			bounds.x = 30;
			break;

		case EDGE_TOPRIGHT:
			regs.al = self.corner_heights.top;
			regs.cl = self.corner_heights.right;

			regs.ah = neighbour.corner_heights.left;
			regs.ch = neighbour.corner_heights.bottom;

			offset.x = -2;
			bounds.y = 30;
			break;

		default:
			return;
	}


	regs.dl = height;

	// save ecx
	if (neighbour.map_element == NULL) {
		regs.ah = 1;
		regs.ch = 1;
	} else {
		regs.dh = neighbour.map_element->properties.surface.terrain & 0x1F;
		if (regs.dl == regs.dh) {
			return;
		}

		regs.al = regs.dl;
		regs.cl = regs.dl;
	}

	// al + cl probably are self tile corners, while ah/ch are neighbour tile corners
	if (regs.al <= regs.ah && regs.cl <= regs.ch) {
		return;
	}

	uint32 base_image_id = stru_97B5C0[terrain][2]; // var_08

	if (gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE) {
		base_image_id = stru_97B5C0[terrain][1];  // var_04
	}

	base_image_id += (edge == EDGE_TOPLEFT ? 5 : 0);

	const uint8 rotation = get_current_rotation();
	uint8 cur_height = min(regs.ch, regs.ah);
	if (regs.ch != regs.ah) {
		// neightbour tile corners aren't level
		uint32 image_offset = 3;
		if (regs.ch > regs.ah) {
			image_offset = 4;
		}

		if (cur_height != regs.al && cur_height != regs.cl) {
			uint32 image_id = base_image_id + image_offset;
			sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, cur_height * 16, rotation);
			cur_height++;
		}
	}

	regs.ah = regs.cl;

	while (cur_height < regs.al && cur_height < regs.ah) {
		sub_98196C(base_image_id, 0, 0, bounds.x, bounds.y, 15, cur_height * 16, rotation);
		cur_height++;
	}

	uint32 image_offset = 1;
	if (cur_height >= regs.al) {
		image_offset = 2;

		if (cur_height >= regs.ah) {
			return;
		}
	}

	uint32 image_id = base_image_id + image_offset;
	sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, cur_height * 16, rotation);
}

/**
 * rct2: 0x0065F8B9, 0x0065FE26
 */
static void viewport_surface_draw_water_side_bottom(enum edge edge, uint8 height, uint8 edgeStyle, struct tile_descriptor self, struct tile_descriptor neighbour)
{
	registers regs;

	rct_xy8 offset = {0, 0};
	rct_xy8 bounds = {0, 0};
	rct_xy16 tunnelBounds = {1, 1};
	rct_xy16 tunnelTopBoundBoxOffset = {0, 0};

	tunnel_entry * tunnelArray;
	switch (edge) {
		case EDGE_BOTTOMLEFT:
			regs.al = self.corner_heights.left;
			regs.cl = self.corner_heights.bottom;

			regs.ah = neighbour.corner_heights.top;
			regs.ch = neighbour.corner_heights.right;

			offset.x = 30;
			bounds.y = 30;
			tunnelBounds.x = 32;
			tunnelTopBoundBoxOffset.y = 31;

			tunnelArray = gLeftTunnels;
			break;

		case EDGE_BOTTOMRIGHT:
			regs.al = self.corner_heights.right;
			regs.cl = self.corner_heights.bottom;

			regs.ah = neighbour.corner_heights.top;
			regs.ch = neighbour.corner_heights.left;

			offset.y = 30;
			bounds.x = 30;
			tunnelBounds.y = 32;
			tunnelTopBoundBoxOffset.x = 31;

			tunnelArray = gRightTunnels;
			break;

		default:
			return;
	}

	regs.dl = height;

	if (neighbour.map_element == 0) {
		regs.ch = 1;
		regs.ah = 1;
	} else {
		regs.dh = neighbour.map_element->properties.surface.terrain & 0x1F;
		if (regs.dl == regs.dh) {
			return;
		}

		regs.al = regs.dl;
		regs.cl = regs.dl;
	}

	if (regs.al <= regs.ah && regs.cl <= regs.ch) {
		return;
	}

	uint32 base_image_id = stru_97B5C0[edgeStyle][0];
	if (gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE) {
		base_image_id = stru_97B5C0[edgeStyle][1];
	}

	if (edge == EDGE_BOTTOMRIGHT) {
		base_image_id += 5;
	}

	const uint8 rotation = get_current_rotation();
	uint8 curHeight = min(regs.ah, regs.ch);
	if (regs.ch != regs.ah) {
		// If bottom part of edge isn't straight, add a filler
		uint32 image_offset = 3;

		if (regs.ch >= regs.ah) {
			image_offset = 4;
		}

		if (curHeight != regs.al && curHeight != regs.cl) {
			uint32 image_id = base_image_id + image_offset;
			sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, curHeight * 16, rotation);
			curHeight++;
		}
	}

	regs.ah = regs.cl;

	while (true) {
		if (curHeight >= regs.al || curHeight >= regs.cl) {
			// If top of edge isn't straight, add a filler
			uint32 image_offset = 1;
			if (curHeight >= regs.al) {
				image_offset = 2;

				if (curHeight >= regs.cl) {
					return;
				}
			}

			uint32 image_id = base_image_id + image_offset;

			sub_98196C(image_id, offset.x, offset.y, bounds.x, bounds.y, 15, curHeight * 16, rotation);

			return;
		}

		if (curHeight != tunnelArray[0].height) {
			// Normal walls
			while (curHeight > tunnelArray[0].height) {
				// TODO: Should probably be done by just keeping track of the current index
				memmove(&tunnelArray[0], &tunnelArray[1], sizeof(tunnel_entry) * (TUNNEL_MAX_COUNT - 1));
			}

			sub_98196C(base_image_id, offset.x, offset.y, bounds.x, bounds.y, 15, curHeight * 16, rotation);

			curHeight++;
			continue;
		}

		// Tunnels
		uint8 tunnelType = tunnelArray[0].type;
		uint8 tunnelHeight = stru_97B570[tunnelType][0];
		sint16 zOffset = curHeight;

		if ((zOffset + tunnelHeight) > regs.ah || (zOffset + tunnelHeight) > regs.al) {
			tunnelType = byte_97B5B0[tunnelType];
		}

		zOffset *= 16;

		sint16 boundBoxOffsetZ = zOffset + word_97B590[tunnelType];
		sint8 boundBoxLength = stru_97B570[tunnelType][1] * 16;
		if (boundBoxOffsetZ < 16) {
			boundBoxOffsetZ += 16;
			boundBoxLength -= 16;
		}


		uint32 image_id = stru_97B640[edgeStyle][tunnelType] + (edge == EDGE_BOTTOMRIGHT ? 2 : 0);
		sub_98197C(image_id, offset.x, offset.y, tunnelBounds.x, tunnelBounds.y, boundBoxLength - 1, zOffset, 0, 0, boundBoxOffsetZ, rotation);


		boundBoxOffsetZ = curHeight * 16;
		boundBoxLength = stru_97B570[tunnelType][1] * 16;
		boundBoxOffsetZ += word_97B590[tunnelType];
		if (boundBoxOffsetZ == 0) {
			boundBoxOffsetZ += 16;
			boundBoxLength -= 16;
		}

		image_id = stru_97B640[edgeStyle][tunnelType] + (edge == EDGE_BOTTOMRIGHT ? 2 : 0) + 1;
		sub_98197C(image_id, offset.x, offset.y, tunnelBounds.x, tunnelBounds.y, boundBoxLength - 1, curHeight * 16, tunnelTopBoundBoxOffset.x, tunnelTopBoundBoxOffset.y, boundBoxOffsetZ, rotation);

		curHeight += stru_97B570[tunnelType][0];

		// TODO: Should probably be done by just keeping track of the current index
		memmove(&tunnelArray[0], &tunnelArray[1], sizeof(tunnel_entry) * (TUNNEL_MAX_COUNT - 1));
	}
}

/**
 * rct2: 0x0066062C
 *
 * @param direction (cl)
 * @param height (dx)
 * @param map_element (esi)
 */
void surface_paint(uint8 direction, uint16 height, rct_map_element * mapElement)
{
	rct_drawpixelinfo * dpi = unk_140E9A8;
	gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_TERRAIN;
	gDidPassSurface = true;
	gSurfaceElement = mapElement;

	uint16 zoomLevel = dpi->zoom_level;

	const uint8 rotation = get_current_rotation();
	uint32 terrain_type = map_element_get_terrain(mapElement);
	uint32 surfaceShape = viewport_surface_paint_setup_get_relative_slope(mapElement, rotation);

	rct_xy16 base = {
		.x = gUnk9DE568,
		.y = gUnk9DE56C
	};

	corner_height ch = corner_heights[surfaceShape];
	tile_descriptor selfDescriptor = {
		.map_element = mapElement,
		.slope = surfaceShape,
		.terrain = terrain_type,
		.corner_heights = {
			.top = height / 16 + ch.top,
			.right = height / 16 + ch.right,
			.bottom = height / 16 + ch.bottom,
			.left = height / 16 + ch.left,
		}
	};

	tile_descriptor tileDescriptors[5];
	tileDescriptors[0] = selfDescriptor;

	for (int i = 0; i < 4; i++) {
		rct_xy16 offset = viewport_surface_paint_data[i][rotation];
		rct_xy16 position = {.x = base.x + offset.x, .y = base.y + offset.y};

		tileDescriptors[i + 1].map_element = NULL;
		if (position.x > 0x2000 || position.y > 0x2000) {
			continue;
		}

		rct_map_element * surfaceElement = map_get_surface_element_at(position.x / 32, position.y / 32);
		if (surfaceElement == NULL) {
			continue;
		}

		tileDescriptors[i + 1].map_element = surfaceElement;
		tileDescriptors[i + 1].terrain = map_element_get_terrain(surfaceElement);
		uint32 ebx = viewport_surface_paint_setup_get_relative_slope(surfaceElement, rotation);
		tileDescriptors[i + 1].slope = ebx;

		uint8 baseHeight = surfaceElement->base_height / 2;
		corner_height ch = corner_heights[ebx];
		tileDescriptors[i + 1].corner_heights.top = baseHeight + ch.top;
		tileDescriptors[i + 1].corner_heights.right = baseHeight + ch.right;
		tileDescriptors[i + 1].corner_heights.bottom = baseHeight + ch.bottom;
		tileDescriptors[i + 1].corner_heights.left = baseHeight + ch.left;
	}


	if ((gCurrentViewportFlags & VIEWPORT_FLAG_LAND_HEIGHTS) && (zoomLevel == 0)) {
		sint16 x = gPaintMapPosition.x, y = gPaintMapPosition.y;

		int dx = map_element_height(x + 16, y + 16) & 0xFFFF;
		dx += 3;

		int image_id = (SPR_HEIGHT_MARKER_BASE + dx / 16) | 0x20780000;
		image_id += get_height_marker_offset();
		image_id -= gMapBaseZ;

		sub_98196C(image_id, 16, 16, 1, 1, 0, height, rotation);
	}


	bool has_surface = false;
	if (gVerticalTunnelHeight * 16 == height) {
		// Vertical tunnels
		sub_98197C(1575, 0, 0, 1, 30, 39, height, -2, 1, height - 40, rotation);
		sub_98197C(1576, 0, 0, 30, 1, 0, height, 1, 31, height, rotation);
		sub_98197C(1577, 0, 0, 1, 30, 0, height, 31, 1, height, rotation);
		sub_98197C(1578, 0, 0, 30, 1, 39, height, 1, -2, height - 40, rotation);
	} else {
		bool showGridlines = (gCurrentViewportFlags & VIEWPORT_FLAG_GRIDLINES);

		int branch = -1;
		if ((mapElement->properties.surface.terrain & 0xE0) == 0) {
			if ((mapElement->type & 0x3) == 0) {
				if (zoomLevel == 0) {
					if ((gCurrentViewportFlags & 0x1001) == 0) {
						branch = mapElement->properties.surface.grass_length & 0x7;
					}
				}
			}
		}

		assert(surfaceShape < countof(byte_97B444));
		uint8 image_offset = byte_97B444[surfaceShape];
		int image_id;
		uint32 ebp = terrain_type;
		switch (branch) {
			case 0:
				// loc_660C90
				image_id = dword_97B898[rotation][showGridlines ? 1 : 0] + image_offset;
				break;

			case 1:
			case 2:
			case 3:
			default:
				// loc_660C9F
				if (rotation & 1) {
					assert(ebp < countof(byte_97B84A));
					ebp = byte_97B84A[ebp];
				}
				assert(ebp < countof(dword_97B750));
				image_id = dword_97B750[ebp][showGridlines ? 1 : 0] + image_offset;

				if (gScreenFlags & (SCREEN_FLAGS_TRACK_DESIGNER | SCREEN_FLAGS_TRACK_MANAGER)) {
					// TODO: SPR_TERRAIN_TRACK_DESIGNER ???
					image_id = 2623;
				}

				if (gCurrentViewportFlags & (VIEWPORT_FLAG_UNDERGROUND_INSIDE | VIEWPORT_FLAG_HIDE_BASE)) {
					image_id &= 0xDC07FFFF; // remove colour
					image_id |= 0x41880000;
				}
				break;

			case 4:
			case 5:
				// loc_660C44
			case 6:
				// loc_660C6A
			{
				sint16 x = gPaintMapPosition.x & 0x20;
				sint16 y = gPaintMapPosition.y & 0x20;
				int index = (y | (x << 1)) >> 5;

				if (branch == 6) {
					image_id = dword_97B878[index][showGridlines ? 1 : 0] + image_offset;
				} else {
					image_id = dword_97B858[index][showGridlines ? 1 : 0] + image_offset;
				}
				break;
			}

		}

		sub_98196C(image_id, 0, 0, 32, 32, -1, height, rotation);
		has_surface = true;
	}

// Draw Staff Patrol Areas
	// loc_660D02
	if (gStaffDrawPatrolAreas != 0xFFFF) {
		sint32 staffIndex = gStaffDrawPatrolAreas;
		bool is_staff_list = staffIndex & 0x8000;
		uint8 staffType = staffIndex & 0x7FFF;
		sint16 x = gPaintMapPosition.x, y = gPaintMapPosition.y;

		uint32 image_id = 0x20000000;
		uint8 patrolColour = 7;

		if (!is_staff_list) {
			rct_peep * staff = GET_PEEP(staffIndex);
			if (!staff_is_patrol_area_set(staff->staff_id, x, y)) {
				patrolColour = 1;
			}
			staffType = staff->staff_type;
		}

		if (staff_is_patrol_area_set(200 + staffType, x, y)) {
			assert(surfaceShape < countof(byte_97B444));

			image_id |= SPR_TERRAIN_SELECTION_PATROL_AREA + byte_97B444[surfaceShape];
			image_id |= patrolColour << 19;
			paint_attach_to_previous_ps(image_id, 0, 0);
		}
	}

	// Draw Peep Spawns
	if (((gScreenFlags & SCREEN_FLAGS_SCENARIO_EDITOR) || gCheatsSandboxMode) &&
		gCurrentViewportFlags & VIEWPORT_FLAG_LAND_OWNERSHIP
	) {
		rct_xy16 pos = {gPaintMapPosition.x, gPaintMapPosition.y};
		for (int i = 0; i < 2; ++i) {
			rct2_peep_spawn * spawn = &gPeepSpawns[i];

			if ((spawn->x & 0xFFE0) == pos.x && (spawn->y & 0xFFE0) == pos.y) {
				// TODO: SPR_TERRAIN_SELECTION_SQUARE_SIMPLE ??? (no variations)
				sub_98196C(2624, 0, 0, 32, 32, 16, spawn->z * 16, rotation);

				int offset = ((spawn->direction ^ 2) + rotation) & 3;
				uint32 image_id = (3111 + offset) | 0x20380000;
				sub_98196C(image_id, 0, 0, 32, 32, 19, spawn->z * 16, rotation);
			}
		}
	}

	if (gCurrentViewportFlags & VIEWPORT_FLAG_LAND_OWNERSHIP) {
		// loc_660E9A:
		if (mapElement->properties.surface.ownership & OWNERSHIP_OWNED) {
			assert(surfaceShape < countof(byte_97B444));
			// TODO: SPR_TERRAIN_SELECTION_SQUARE?
			paint_attach_to_previous_ps(2625 + byte_97B444[surfaceShape], 0, 0);
		} else if (mapElement->properties.surface.ownership & OWNERSHIP_AVAILABLE) {
			rct_xy16 pos = {gPaintMapPosition.x, gPaintMapPosition.y};
			paint_struct * backup = g_ps_F1AD28;
			int height = (map_element_height(pos.x + 16, pos.y + 16) & 0xFFFF) + 3;
			sub_98196C(22955, 16, 16, 1, 1, 0, height, rotation);
			g_ps_F1AD28 = backup;
		}
	}

	if (gCurrentViewportFlags & VIEWPORT_FLAG_CONSTRUCTION_RIGHTS
	    && !(mapElement->properties.surface.ownership & OWNERSHIP_OWNED)) {
		if (mapElement->properties.surface.ownership & OWNERSHIP_CONSTRUCTION_RIGHTS_OWNED) {
			assert(surfaceShape < countof(byte_97B444));
			// TODO: SPR_TERRAIN_SELECTION_DOTTED ???
			paint_attach_to_previous_ps(2644 + byte_97B444[surfaceShape], 0, 0);
		} else if (mapElement->properties.surface.ownership & OWNERSHIP_CONSTRUCTION_RIGHTS_AVAILABLE) {
			paint_struct * backup = g_ps_F1AD28;
			rct_xy16 pos = {gPaintMapPosition.x, gPaintMapPosition.y};
			int height = map_element_height(pos.x + 16, pos.y + 16) & 0xFFFF;
			sub_98196C(22956, 16, 16, 1, 1, 0, height + 3, rotation);
			g_ps_F1AD28 = backup;
		}
	}

	// ebx[0] = esi;
	// ebp[4] = ebp;
	// ebp[8] = ebx

	if (gMapSelectFlags & MAP_SELECT_FLAG_ENABLE) {
		// loc_660FB8:
		rct_xy16 pos = {gPaintMapPosition.x, gPaintMapPosition.y};
		if (pos.x >= gMapSelectPositionA.x &&
			pos.x <= gMapSelectPositionB.x &&
			pos.y >= gMapSelectPositionA.y &&
			pos.y <= gMapSelectPositionB.y
		) {
			uint16 mapSelectionType = gMapSelectType;
			if (mapSelectionType >= MAP_SELECT_TYPE_EDGE_0) {
				// Walls
				// loc_661089:
				uint32 eax = ((((mapSelectionType - 9) + rotation) & 3) + 0x21) << 19;
				uint32 image_id = (SPR_TERRAIN_SELECTION_EDGE + byte_97B444[surfaceShape]) | eax | 0x20000000;
				paint_attach_to_previous_ps(image_id, 0, 0);
			} else if (mapSelectionType >= MAP_SELECT_TYPE_QUARTER_0) {
				// loc_661051:(no jump)
				// Selection split into four quarter segments
				uint32 eax = ((((mapSelectionType - MAP_SELECT_TYPE_QUARTER_0) + rotation) & 3) + 0x27) << 19;
				uint32 image_id = (SPR_TERRAIN_SELECTION_QUARTER + byte_97B444[surfaceShape]) | eax | 0x20000000;
				paint_attach_to_previous_ps(image_id, 0, 0);
			} else if (mapSelectionType <= MAP_SELECT_TYPE_FULL) {
				// Corners
				uint32 eax = mapSelectionType;
				if (mapSelectionType != MAP_SELECT_TYPE_FULL) {
					eax = (mapSelectionType + rotation) & 3;
				}

				eax = (eax + 0x21) << 19;
				uint32 image_id = (SPR_TERRAIN_SELECTION_CORNER + byte_97B444[surfaceShape]) | eax | 0x20000000;
				paint_attach_to_previous_ps(image_id, 0, 0);
			} else {
				int local_surfaceShape = surfaceShape;
				int local_height = height;
				// Water tool
				if (mapElement->properties.surface.terrain & 0x1F) {
					int waterHeight = (mapElement->properties.surface.terrain & 0x1F) * 16;
					if (waterHeight > height) {
						local_height += 16;

						if (waterHeight != local_height
						    || !(local_surfaceShape & 0x10)) {
							local_height = waterHeight;
							local_surfaceShape = 0;
						} else {
							registers regs = { 0 };

							regs.bl = (surfaceShape ^ 0xF) << 2;
							regs.bh = regs.bl >> 4;
							local_surfaceShape = (regs.bh & 0x3) | (regs.bl & 0xC);
						}
					}
				}

				int image_id = (SPR_TERRAIN_SELECTION_CORNER + byte_97B444[local_surfaceShape]) | 0x21300000;

				paint_struct * backup = g_ps_F1AD28;
				sub_98196C(image_id, 0, 0, 32, 32, 1, local_height, rotation);
				g_ps_F1AD28 = backup;
			}
		}
	}

	if (gMapSelectFlags & MAP_SELECT_FLAG_ENABLE_CONSTRUCT) {
		rct_xy16 pos = {gPaintMapPosition.x, gPaintMapPosition.y};

		rct_xy16 * tile;
		for (tile = gMapSelectionTiles; tile->x != -1; tile++) {
			if (tile->x != pos.x || tile->y != pos.y) {
				continue;
			}

			uint32 colours = COLOUR_GREY << 24 | COLOUR_BRIGHT_PURPLE << 19;
			if (gMapSelectFlags & MAP_SELECT_FLAG_GREEN) {
				colours = COLOUR_GREY << 24 | COLOUR_SATURATED_GREEN << 19;
			}

			uint32 image_id = (SPR_TERRAIN_SELECTION_CORNER + byte_97B444[surfaceShape]) | colours | 0x20000000;
			paint_attach_to_previous_ps(image_id, 0, 0);
			break;
		}
	}

	if (zoomLevel == 0
	    && has_surface
	    && !(gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE)
	    && !(gCurrentViewportFlags & VIEWPORT_FLAG_HIDE_BASE)
	    && gConfigGeneral.landscape_smoothing) {
		viewport_surface_smoothen_edge(EDGE_TOPLEFT, tileDescriptors[0], tileDescriptors[3]);
		viewport_surface_smoothen_edge(EDGE_TOPRIGHT, tileDescriptors[0], tileDescriptors[4]);
		viewport_surface_smoothen_edge(EDGE_BOTTOMLEFT, tileDescriptors[0], tileDescriptors[1]);
		viewport_surface_smoothen_edge(EDGE_BOTTOMRIGHT, tileDescriptors[0], tileDescriptors[2]);
	}


	if (gCurrentViewportFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE
	    && !(gCurrentViewportFlags & VIEWPORT_FLAG_HIDE_BASE)
	    && !(gScreenFlags & (SCREEN_FLAGS_TRACK_DESIGNER | SCREEN_FLAGS_TRACK_MANAGER))) {

		uint8 image_offset = byte_97B444[surfaceShape];
		uint32 base_image = terrain_type;
		if (rotation & 1) {
			base_image = byte_97B84A[terrain_type];
		}
		uint32 image_id = dword_97B7C8[base_image] + image_offset;
		paint_attach_to_previous_ps(image_id, 0, 0);
	}

	if (!(gCurrentViewportFlags & VIEWPORT_FLAG_HIDE_VERTICAL)) {
		// loc_66122C:
		uint8 al_edgeStyle = mapElement->properties.surface.slope & 0xE0;
		uint8 di_type = mapElement->type & 0x80;

		uint32 eax = al_edgeStyle + di_type * 2;
		if (eax != 32 && eax != 0 && eax != 96 && eax != 64) {
			log_verbose("eax: %d", eax);
		}

		tunnel_entry backupLeftTunnels[TUNNEL_MAX_COUNT];
		tunnel_entry backupRightTunnels[TUNNEL_MAX_COUNT];

#ifdef __MINGW32__
		// The other code crashes mingw 4.8.2, as available on Travis
		for (int i = 0; i < TUNNEL_MAX_COUNT; i++) {
			backupLeftTunnels[i] = gLeftTunnels[i];
			backupRightTunnels[i] = gRightTunnels[i];
		}
#else
		memcpy(backupLeftTunnels, gLeftTunnels, sizeof(tunnel_entry) * TUNNEL_MAX_COUNT);
		memcpy(backupRightTunnels, gRightTunnels, sizeof(tunnel_entry) * TUNNEL_MAX_COUNT);
#endif

		viewport_surface_draw_land_side_top(EDGE_TOPLEFT, height / 16, eax / 32, tileDescriptors[0], tileDescriptors[3]);
		viewport_surface_draw_land_side_top(EDGE_TOPRIGHT, height / 16, eax / 32, tileDescriptors[0], tileDescriptors[4]);
		viewport_surface_draw_land_side_bottom(EDGE_BOTTOMLEFT, height / 16, eax / 32, tileDescriptors[0], tileDescriptors[1]);
		viewport_surface_draw_land_side_bottom(EDGE_BOTTOMRIGHT, height / 16, eax / 32, tileDescriptors[0], tileDescriptors[2]);


#ifdef __MINGW32__
		// The other code crashes mingw 4.8.2, as available on Travis
		for (int i = 0; i < TUNNEL_MAX_COUNT; i++) {
			gLeftTunnels[i] = backupLeftTunnels[i];
			gRightTunnels[i] = backupRightTunnels[i];
		}
#else
		memcpy(gLeftTunnels, backupLeftTunnels, sizeof(tunnel_entry) * TUNNEL_MAX_COUNT);
		memcpy(gRightTunnels, backupRightTunnels, sizeof(tunnel_entry) * TUNNEL_MAX_COUNT);
#endif
	}

	if (mapElement->properties.surface.terrain & 0x1F) {
		// loc_6615A9: (water height)
		gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_WATER;

		uint16 localHeight = height + 16;
		uint16 waterHeight = (mapElement->properties.surface.terrain & 0x1F) * 16;

		if (!gTrackDesignSaveMode) {
			gUnk141E9DC = waterHeight;

			int image_offset = 0;
			if (waterHeight <= localHeight) {
				image_offset = byte_97B740[surfaceShape & 0xF];
			}

			int image_id = (SPR_WATER_MASK + image_offset) | 0x61000000;
			sub_98196C(image_id, 0, 0, 32, 32, -1, waterHeight, rotation);

			paint_attach_to_previous_ps(SPR_WATER_OVERLAY + image_offset, 0, 0);

			// This wasn't in the original, but the code depended on globals that were only set in a different conditional
			uint8 al_edgeStyle = mapElement->properties.surface.slope & 0xE0;
			uint8 di_type = mapElement->type & 0x80;

			uint32 eax = al_edgeStyle + di_type * 2;
			assert(eax % 32 == 0);
			// end new code

			viewport_surface_draw_water_side_top(EDGE_TOPLEFT, waterHeight / 16, eax / 32, tileDescriptors[0], tileDescriptors[3]);
			viewport_surface_draw_water_side_top(EDGE_TOPRIGHT, waterHeight / 16, eax / 32, tileDescriptors[0], tileDescriptors[4]);
			viewport_surface_draw_water_side_bottom(EDGE_BOTTOMLEFT, waterHeight / 16, eax / 32, tileDescriptors[0], tileDescriptors[1]);
			viewport_surface_draw_water_side_bottom(EDGE_BOTTOMRIGHT, waterHeight / 16, eax / 32, tileDescriptors[0], tileDescriptors[2]);
		}
	}

	if ((mapElement->properties.surface.ownership & 0x0F) &&
		!gTrackDesignSaveMode
	) {
		// Owned land boundary fences
		gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_PARK;

		registers regs = { 0 };
		regs.al = mapElement->properties.surface.ownership & 0x0F;
		regs.ax = regs.ax << rotation;
		regs.ah = regs.al >> 4;

		uint8 al = regs.al | regs.ah;

		for (int i = 0; i < 4; i++) {
			int bit = al & 1;
			al >>= 1;

			if (bit == 0) {
				continue;
			}


			int bit_1, bit_8, bit_4, bit_2;
			rct_xy8 offset;
			rct_xy16 box_offset, box_size;
			uint32 image_1, image_2, image_3;
			switch (i) {
				case 0:
					// Bottom right
					bit_1 = 1;
					bit_8 = 8;
					bit_4 = 4;
					bit_2 = 2;
					image_1 = 22872;
					image_2 = 22876;
					image_3 = 22874;
					offset = (rct_xy8) {1, 31};
					box_size = (struct rct_xy16) {.x=30, .y=1};
					box_offset = (struct rct_xy16) {.x=1, .y=31};
					break;

				case 1:
					// Bottom left
					bit_1 = 1;
					bit_8 = 2;
					bit_4 = 4;
					bit_2 = 8;
					image_1 = 22873;
					image_2 = 22877;
					image_3 = 22875;
					offset = (rct_xy8) {31, 0};
					box_size = (struct rct_xy16) {.x=1, .y=30};
					box_offset = (struct rct_xy16) {.x=31, .y=1};
					break;

				case 2:
					// Top left
					bit_1 = 4;
					bit_8 = 2;
					bit_4 = 8;
					bit_2 = 1;
					image_1 = 22872;
					image_2 = 22874;
					image_3 = 22876;
					offset = (rct_xy8) {1, 0};
					box_size = (struct rct_xy16) {30, 1};
					box_offset = (struct rct_xy16) {1, 1};
					// TODO: Fences on top tile get clipped after a while
					break;

				case 3:
					// Top right
					bit_1 = 4;
					bit_8 = 8;
					bit_4 = 2;
					bit_2 = 1;
					image_1 = 22873;
					image_2 = 22875;
					image_3 = 22877;
					offset = (rct_xy8) {1, 1};
					box_size = (struct rct_xy16) {1, 30};
					box_offset = (struct rct_xy16) {1, 1};
					break;
			}

			uint32 image_4, image_5;
			if (i == 0 || i == 1) {
				image_4 = image_3;
				image_5 = image_2;
			} else {
				image_4 = image_2;
				image_5 = image_3;
			}

			int local_ebx = surfaceShape;
			int local_height = height;
			int image_id = 0;
			if (!(local_ebx & bit_1)) { // first
				if (local_ebx & bit_8) { // second
					image_id = image_3;
				} else {
					image_id = image_1;
				}
			} else if (!(local_ebx & bit_8)) { // loc_6619A2:
				image_id = image_2;
			} else {
				local_height += 16;

				if (!(local_ebx & 0x10)) { // loc_6619B5 (first)
					image_id = image_1;
				} else if (local_ebx & bit_4) { // loc_6619B5 (second)
					image_id = image_4;
				} else if (local_ebx & bit_2) { // loc_6619B5 (third)
					image_id = image_5;
				} else {
					image_id = image_1;
				}
			}

			sub_98197C(image_id, offset.x, offset.y, box_size.x, box_size.y, 9, local_height, box_offset.x, box_offset.y, local_height + 1, rotation);
		}
	}

	gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_TERRAIN;
	g141E9DB |= G141E9DB_FLAG_1;

	switch (surfaceShape) {
		default:
			// loc_661C2C
			//     00
			//   00  00
			// 00  00  00
			//   00  00
			//     00
			paint_util_set_segment_support_height(
				SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4,
				height,
				0
			);
			paint_util_force_set_general_support_height(height, 0);
			break;

		case 1:
			// loc_661CB9
			//     00
			//   00  00
			// 01  01  01
			//   1B  1B
			//     1B
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, height, 0);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_BC, height, 1);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_D4, height + 6, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_C0, height + 6 + 6, 0x1B);
			paint_util_force_set_general_support_height(height, 1);
			break;

		case 2:
			// loc_661D4E
			//     02
			//   17  00
			// 17  02  00
			//   17  00
			//     02
			paint_util_set_segment_support_height(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, height, 0);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C0, height, 2);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_D0, height + 6, 0x17);
			paint_util_set_segment_support_height(SEGMENT_B8, height + 6 + 6, 0x17);
			paint_util_force_set_general_support_height(height, 2);
			break;

		case 3:
			// loc_661DE3
			//     03
			//   03  03
			// 03  03  03
			//   03  03
			//     03
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_CC | SEGMENT_BC, height + 2, 3);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_C4 | SEGMENT_D4, height + 2 + 6, 3);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_D0 | SEGMENT_C0, height + 2 + 6 + 6, 3);
			paint_util_force_set_general_support_height(height, 3);
			break;

		case 4:
			// loc_661E7C
			//     1E
			//   1E  1E
			// 04  04  04
			//   00  00
			//     00
			paint_util_set_segment_support_height(SEGMENT_C0 | SEGMENT_D0 | SEGMENT_D4, height, 0);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_BC, height, 4);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_CC, height + 6, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_B4, height + 6 + 6, 0x1E);
			paint_util_force_set_general_support_height(height, 4);
			break;

		case 5:
			// loc_661F11
			//     1E          ▓▓
			//   1E  1E      ▒▒  ▒▒
			// 05  05  05  ░░  ░░  ░░
			//   1B  1B      ▒▒  ▒▒
			//     1B          ▓▓
			paint_util_set_segment_support_height(SEGMENT_B4, height + 6 + 6, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_CC, height + 6, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_BC, height, 5);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_D4, height + 6, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_C0, height + 6 + 6, 0x1B);
			paint_util_force_set_general_support_height(height, 5);
			break;

		case 6:
			// loc_661FA6
			//     06          ▓▓
			//   06  06      ▓▓  ▒▒
			// 06  06  06  ▓▓  ▒▒  ░░
			//   06  06      ▒▒  ░░
			//     06          ░░
			paint_util_set_segment_support_height(SEGMENT_BC | SEGMENT_D4 | SEGMENT_C0, height + 2, 6);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC, height + 2 + 6, 6);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C8 | SEGMENT_B4, height + 2 + 6 + 6, 6);
			paint_util_force_set_general_support_height(height, 6);
			break;

		case 7:
			// loc_66203F
			//     07          ▓▓
			//   00  17      ▓▓  ▒▒
			// 00  07  17  ▓▓  ▓▓  ░░
			//   00  17      ▓▓  ▒▒
			//     07          ▓▓
			paint_util_set_segment_support_height(SEGMENT_BC, height + 4, 0x17);
			paint_util_set_segment_support_height(SEGMENT_CC | SEGMENT_D4, height + 4 + 6, 0x17);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C0, height + 4 + 6 + 6, 7);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_D0 | SEGMENT_B8, height + 4 + 6 + 6, 0);
			paint_util_force_set_general_support_height(height, 7);
			break;

		case 8:
			// loc_6620D8
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C8 | SEGMENT_D0, height, 0);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C0, height, 8);
			paint_util_set_segment_support_height(SEGMENT_CC | SEGMENT_D4, height + 6, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_BC, height + 6 + 6, 0x1D);
			paint_util_force_set_general_support_height(height, 8);
			break;

		case 9:
			// loc_66216D
			paint_util_force_set_general_support_height(height, 9);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_B8, height + 2, 9);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC, height + 2 + 6, 9);
			paint_util_set_segment_support_height(SEGMENT_C0 | SEGMENT_D4 | SEGMENT_BC, height + 2 + 6 + 6, 9);
			break;

		case 10:
			// loc_662206
			paint_util_force_set_general_support_height(height, 0xA);
			paint_util_set_segment_support_height(SEGMENT_B8, height + 6 + 6, 0x17);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_D0, height + 6, 0x17);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C0, height, 0xA);
			paint_util_set_segment_support_height(SEGMENT_CC | SEGMENT_D4, height + 6, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_BC, height + 6 + 6, 0x1D);
			break;

		case 11:
			// loc_66229B
			paint_util_force_set_general_support_height(height, 0xB);
			paint_util_set_segment_support_height(SEGMENT_B4, height + 4, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_CC, height + 4 + 6, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_BC, height + 4 + 6 + 6, 0xB);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_D4 | SEGMENT_C0, height + 4 + 6 + 6, 0);
			break;

		case 12:
			// loc_662334
			paint_util_force_set_general_support_height(height, 0xC);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_D0 | SEGMENT_C0, height + 2, 0xC);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_C4 | SEGMENT_D4, height + 2 + 6, 0xC);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_CC | SEGMENT_BC, height + 2 + 6 + 6, 0xC);
			break;

		case 13:
			// loc_6623CD
			paint_util_force_set_general_support_height(height, 0xD);
			paint_util_set_segment_support_height(SEGMENT_B8, height + 4, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_D0, height + 4 + 6, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C0, height + 4 + 6 + 6, 0xD);
			paint_util_set_segment_support_height(SEGMENT_CC | SEGMENT_D4 | SEGMENT_BC, height + 4 + 6 + 6, 0);
			break;

		case 14:
			// loc_662466
			paint_util_force_set_general_support_height(height, 0xE);
			paint_util_set_segment_support_height(SEGMENT_C0, height + 4, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_D4, height + 4 + 6, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_BC, height + 4 + 6 + 6, 0xE);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_CC | SEGMENT_B4, height + 4 + 6 + 6, 0);
			break;

		case 23:
			// loc_6624FF
			paint_util_force_set_general_support_height(height, 0x17);
			paint_util_set_segment_support_height(SEGMENT_BC, height + 4, 0x17);
			paint_util_set_segment_support_height(SEGMENT_CC | SEGMENT_D4, height + 4 + 6, 0x17);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C0, height + 4 + 6 + 6, 0x17);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_D0, height + 4 + 6 + 6 + 6, 0x17);
			paint_util_set_segment_support_height(SEGMENT_B8, height + 4 + 6 + 6 + 6 + 6, 0x17);
			break;

		case 27:
			// loc_6625A0
			paint_util_force_set_general_support_height(height, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_B4, height + 4, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_CC, height + 4 + 6, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_BC, height + 4 + 6 + 6, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_D4, height + 4 + 6 + 6 + 6, 0x1B);
			paint_util_set_segment_support_height(SEGMENT_C0, height + 4 + 6 + 6 + 6 + 6, 0x1B);
			break;

		case 29:
			// loc_662641
			paint_util_force_set_general_support_height(height, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_B8, height + 4, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_D0, height + 4 + 6, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C0, height + 4 + 6 + 6, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_CC | SEGMENT_D4, height + 4 + 6 + 6 + 6, 0x1D);
			paint_util_set_segment_support_height(SEGMENT_BC, height + 4 + 6 + 6 + 6 + 6, 0x1D);
			break;

		case 30:
			// loc_6626E2
			paint_util_force_set_general_support_height(height, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_C0, height + 4, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_D0 | SEGMENT_D4, height + 4 + 6, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_BC, height + 4 + 6 + 6, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_C8 | SEGMENT_CC, height + 4 + 6 + 6 + 6, 0x1E);
			paint_util_set_segment_support_height(SEGMENT_B4, height + 4 + 6 + 6 + 6 + 6, 0x1E);
			break;
	}

}
