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

#include "../addresses.h"
#include "../config.h"
#include "../drawing/drawing.h"
#include "../paint/supports.h"
#include "../interface/viewport.h"
#include "../paint/paint.h"
#include "../interface/window.h"
#include "../localisation/localisation.h"
#include "../sprites.h"
#include "../world/map.h"
#include "../world/sprite.h"
#include "ride_data.h"
#include "track_data.h"
#include "track_paint.h"
#include "../paint/map_element/map_element.h"

/* rct2: 0x007667AC */
static rct_xy16 loc_7667AC[] = {
	{.x = -1, .y = 0},
	{.x = 0, .y = -1},
	{.x = 1, .y = 0},
	{.x = 0, .y = 1},
};

/* rct2: 0x007667AE */
static rct_xy16 loc_7667AE[] = {
	{.x = 0, .y = -1},
	{.x = 1, .y = 0},
	{.x = 0, .y = 1},
	{.x = -1, .y = 0},
};

const uint8 track_map_2x2[][4] = {
	{0, 1, 2, 3},
	{1, 3, 0, 2},
	{3, 2, 1, 0},
	{2, 0, 3, 1}
};

const uint8 edges_2x2[] = {
	EDGE_NE | EDGE_NW,
	EDGE_NE | EDGE_SE,
	EDGE_SW | EDGE_NW,
	EDGE_SW | EDGE_SE,
};

const uint8 track_map_3x3[][9] = {
	{0, 1, 2, 3, 4, 5, 6, 7, 8},
	{0, 3, 5, 7, 2, 8, 1, 6, 4},
	{0, 7, 8, 6, 5, 4, 3, 1, 2},
	{0, 6, 4, 1, 8, 2, 7, 3, 5}
};

const uint8 edges_3x3[] = {
	0,
	EDGE_NE | EDGE_NW,
	EDGE_NE,
	EDGE_NE | EDGE_SE,
	EDGE_NW,
	EDGE_SE,
	EDGE_SW | EDGE_NW,
	EDGE_SW | EDGE_SE,
	EDGE_SW,
};

const uint8 track_map_4x4[][16] = {
	{0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15},
	{3,  7,  11, 15, 2,  6,  10, 14, 1,  5,  9,  13, 0,  4,  8,  12},
	{15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
	{12, 8,  4,  0,  13, 9,  5,  1,  14, 10, 6,  2,  15, 11, 7,  3},
};

const uint8 edges_4x4[] = {
	EDGE_NE | EDGE_NW,
	EDGE_NE,
	EDGE_NE,
	EDGE_NE | EDGE_SE,
	EDGE_NW,
	0,
	0,
	EDGE_SE,
	EDGE_NW,
	0,
	0,
	EDGE_SE,
	EDGE_NW | EDGE_SW,
	EDGE_SW,
	EDGE_SW,
	EDGE_SW | EDGE_SE
};

const uint8 track_map_1x4[][4] = {
	{0, 1, 2, 3},
	{2, 3, 0, 1},
	{2, 3, 0, 1},
	{0, 1, 2, 3},
};

const uint32 floorSpritesCork[] = {
	SPR_FLOOR_CORK_SE_SW,
	SPR_FLOOR_CORK_SW,
	SPR_FLOOR_CORK_SE,
	SPR_FLOOR_CORK
};

const uint32 fenceSpritesRope[] = {
	SPR_FENCE_ROPE_NE,
	SPR_FENCE_ROPE_SE,
	SPR_FENCE_ROPE_SW,
	SPR_FENCE_ROPE_NW
};

const uint32 fenceSpritesMetalB[] = {
	SPR_FENCE_METAL_B_NE,
	SPR_FENCE_METAL_B_SE,
	SPR_FENCE_METAL_B_SW,
	SPR_FENCE_METAL_B_NW
};

const uint32 trackSpritesSubmarineRideMiniHelicoptersQuarterTurn3Tiles[4][3] = {
	{
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_0,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_1,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_2
	}, {
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_0,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_1,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_2
	}, {
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_0,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_1,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_2
	}, {
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_0,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_1,
		SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_2
	}
};

const uint32 trackSpritesSubmarineRideMiniHelicoptersQuarterTurn1Tile[4] = {
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_SW_NW,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_NW_NE,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_NE_SE,
	SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_SE_SW,
};

static const uint32 trackSpritesGhostTrainSpinningTunnel[2][2][4] = {
	{
		{
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_0,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_1,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_2,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_3
		},
		{
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_0,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_1,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_2,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_3
		}
	},
	{
		{
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_0,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_1,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_2,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_3
		},
		{
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_0,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_1,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_2,
			SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_3
		}
	}
};

enum
{
	SPR_STATION_COVER_OFFSET_NE_SW_BACK_0 = 0,
	SPR_STATION_COVER_OFFSET_NE_SW_BACK_1,
	SPR_STATION_COVER_OFFSET_NE_SW_FRONT,
	SPR_STATION_COVER_OFFSET_SE_NW_BACK_0,
	SPR_STATION_COVER_OFFSET_SE_NW_BACK_1,
	SPR_STATION_COVER_OFFSET_SE_NW_FRONT,
	SPR_STATION_COVER_OFFSET_HIGH
};

bool gUseOriginalRidePaint = false;

bool track_paint_util_has_fence(enum edge edge, rct_xy16 position, rct_map_element * mapElement, rct_ride * ride, uint8 rotation)
{
	rct_xy16 offset;
	switch (edge) {
		case EDGE_NE:
			offset = loc_7667AC[rotation];
			break;
		case EDGE_SE:
			offset = loc_7667AE[(rotation + 2) & 3];
			break;
		case EDGE_SW:
			offset = loc_7667AC[(rotation + 2) & 3];
			break;
		case EDGE_NW:
			offset = loc_7667AE[rotation];
			break;
	}

	uint16 entranceLoc =
		((position.x / 32) + offset.x) |
		(((position.y / 32) + offset.y) << 8);

	int entranceId = map_get_station(mapElement);

	return (ride->entrances[entranceId] != entranceLoc && ride->exits[entranceId] != entranceLoc);
}

void track_paint_util_paint_floor(uint8 edges, uint32 colourFlags, uint16 height, const uint32 floorSprites[4], uint8 rotation)
{
	uint32 imageId;

	if (edges & EDGE_SW && edges & EDGE_SE) {
		imageId = floorSprites[0];
	} else if (edges & EDGE_SW) {
		imageId = floorSprites[1];
	} else if (edges & EDGE_SE) {
		imageId = floorSprites[2];
	} else {
		imageId = floorSprites[3];
	}

	sub_98197C(imageId | colourFlags, 0, 0, 32, 32, 1, height, 0, 0, height, rotation);
}

void track_paint_util_paint_fences(uint8 edges, rct_xy16 position, rct_map_element * mapElement, rct_ride * ride, uint32 colourFlags, uint16 height, const uint32 fenceSprites[4], uint8 rotation)
{
	uint32 imageId;

	if (edges & EDGE_NW && track_paint_util_has_fence(EDGE_NW, position, mapElement, ride, rotation)) {
		imageId = fenceSprites[3] | colourFlags;
		sub_98199C(imageId, 0, 0, 32, 1, 7, height, 0, 2, height + 2, rotation);
	}
	if (edges & EDGE_NE && track_paint_util_has_fence(EDGE_NE, position, mapElement, ride, rotation)) {
		imageId = fenceSprites[0] | colourFlags;
		sub_98199C(imageId, 0, 0, 1, 32, 7, height, 2, 0, height + 2, rotation);
	}
	if (edges & EDGE_SE && track_paint_util_has_fence(EDGE_SE, position, mapElement, ride, rotation)) {
		imageId = fenceSprites[1] | colourFlags;
		sub_98197C(imageId, 0, 0, 32, 1, 7, height, 0, 30, height + 2, rotation);
	}
	if (edges & EDGE_SW && track_paint_util_has_fence(EDGE_SW, position, mapElement, ride, rotation)) {
		imageId = fenceSprites[2] | colourFlags;
		sub_98197C(imageId, 0, 0, 1, 32, 7, height, 30, 0, height + 2, rotation);
	}
}

/* Supports are only placed every 2 tiles for flat pieces*/
bool track_paint_util_should_paint_supports(rct_xy16 position)
{
	if ((position.x & (1 << 5)) == (position.y & (1 << 5)))
		return true;

	if ((!(position.x & (1 << 5))) && (!(position.y & (1 << 5))))
		return true;

	return false;
}

void track_paint_util_draw_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};
	rct_ride * ride = get_ride(rideIndex);
	const rct_ride_entrance_definition * entranceStyle = &RideEntranceDefinitions[ride->entrance_style];
	const bool hasGreenLight = (bool) (mapElement->properties.track.sequence & 0x80);

	bool hasFence;
	uint32 imageId;

	if (direction == 0 || direction == 2) {
		//height += 5 (height + 5);
		hasFence = track_paint_util_has_fence(EDGE_NW, position, mapElement, ride, get_current_rotation());

		if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 0) {
			if (hasGreenLight) {
				imageId = (hasFence ? SPR_STATION_PLATFORM_FENCED_END_GREEN_LIGHT_SW_NE : SPR_STATION_PLATFORM_END_GREEN_LIGHT_SW_NE) | RCT2_GLOBAL(0x00F4419C, uint32);
			} else {
				imageId = (hasFence ? SPR_STATION_PLATFORM_FENCED_END_RED_LIGHT_SW_NE : SPR_STATION_PLATFORM_END_RED_LIGHT_SW_NE) | RCT2_GLOBAL(0x00F4419C, uint32);
			}
		} else if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 2) {
			imageId = (hasFence ? SPR_STATION_PLATFORM_BEGIN_FENCED_SW_NE : SPR_STATION_PLATFORM_BEGIN_SW_NE) | RCT2_GLOBAL(0x00F4419C, uint32);
		} else {
			imageId = (hasFence ? SPR_STATION_PLATFORM_FENCED_SW_NE : SPR_STATION_PLATFORM_SW_NE) | RCT2_GLOBAL(0x00F4419C, uint32);
		}
		sub_98196C(imageId, 0, 0, 32, 8, 1, height + 5, get_current_rotation());
		//height -= 5 (height)
		track_paint_util_draw_station_covers(EDGE_NW, hasFence, entranceStyle, direction, height);
		//height += 5 (height + 5)

		if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 0) {
			imageId = (hasGreenLight ? SPR_STATION_PLATFORM_END_GREEN_LIGHT_SW_NE : SPR_STATION_PLATFORM_END_RED_LIGHT_SW_NE) | RCT2_GLOBAL(0x00F4419C, uint32);
		} else if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 2) {
			imageId = SPR_STATION_PLATFORM_BEGIN_SW_NE | RCT2_GLOBAL(0x00F4419C, uint32);
		} else {
			imageId = SPR_STATION_PLATFORM_SW_NE | RCT2_GLOBAL(0x00F4419C, uint32);
		}
		sub_98196C(imageId, 0, 24, 32, 8, 1, height + 5, get_current_rotation());
		//height += 2 (height + 7)

		hasFence = track_paint_util_has_fence(EDGE_SE, position, mapElement, ride, get_current_rotation());
		if (hasFence) {
			if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 0) {
				imageId = SPR_STATION_BEGIN_ANGLE_FENCE_SW_NE | RCT2_GLOBAL(0x00F4419C, uint32);
			} else if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 2) {
				imageId = SPR_STATION_LIGHT_BACK_ANGLE_FENCED_NE_SW | RCT2_GLOBAL(0x00F4419C, uint32);
			} else {
				imageId = SPR_STATION_FENCE_SW_NE | RCT2_GLOBAL(0x00F4419C, uint32);
			}
			sub_98196C(imageId, 0, 31, 32, 1, 7, height + 7, get_current_rotation());
		} else if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 0) {
			// Addition: draw only small fence if there is an entrance/exit at the beginning
			imageId = SPR_STATION_FENCE_SMALL_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 31, 23, 1, 8, 7, height + 7, get_current_rotation());
		} else if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 2) {
			// Addition: draw only small fence if there is an entrance/exit at the end
			imageId = SPR_STATION_LIGHT_BACK_NE_SW | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 31, 23, 1, 8, 7, height + 7, get_current_rotation());
		}
		//height -= 7 (height)
		track_paint_util_draw_station_covers(EDGE_SE, hasFence, entranceStyle, direction, height);
		//height += 7 (height + 7)

		if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 0) {
			imageId = SPR_STATION_FENCE_SMALL_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 31, 0, 1, 8, 7, height + 7, get_current_rotation());
		} else if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 2) {
			imageId = SPR_STATION_LIGHT_BACK_NE_SW | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 31, 0, 1, 8, 7, height + 7, get_current_rotation());
		}
	} else if (direction == 1 || direction == 3) {
		//height += 5 (height + 5);
		hasFence = track_paint_util_has_fence(EDGE_NE, position, mapElement, ride, get_current_rotation());

		if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 3) {
			if (hasGreenLight) {
				imageId = (hasFence ? SPR_STATION_PLATFORM_FENCED_END_GREEN_LIGHT_NW_SE : SPR_STATION_PLATFORM_END_GREEN_LIGHT_NW_SE) | RCT2_GLOBAL(0x00F4419C, uint32);
			} else {
				imageId = (hasFence ? SPR_STATION_PLATFORM_FENCED_END_RED_LIGHT_NW_SE : SPR_STATION_PLATFORM_END_RED_LIGHT_NW_SE) | RCT2_GLOBAL(0x00F4419C, uint32);
			}
		} else if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 1) {
			imageId = (hasFence ? SPR_STATION_PLATFORM_BEGIN_FENCED_NW_SE : SPR_STATION_PLATFORM_BEGIN_NW_SE) | RCT2_GLOBAL(0x00F4419C, uint32);
		} else {
			imageId = (hasFence ? SPR_STATION_PLATFORM_FENCED_NW_SE : SPR_STATION_PLATFORM_NW_SE) | RCT2_GLOBAL(0x00F4419C, uint32);
		}
		sub_98196C(imageId, 0, 0, 8, 32, 1, height + 5, get_current_rotation());
		//height -= 5 (height)
		track_paint_util_draw_station_covers(EDGE_NE, hasFence, entranceStyle, direction, height);
		//height += 5 (height + 5)

		if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 3) {
			imageId = (hasGreenLight ? SPR_STATION_PLATFORM_END_GREEN_LIGHT_NW_SE : SPR_STATION_PLATFORM_END_RED_LIGHT_NW_SE) | RCT2_GLOBAL(0x00F4419C, uint32);
		} else if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 1) {
			imageId = SPR_STATION_PLATFORM_BEGIN_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
		} else {
			imageId = SPR_STATION_PLATFORM_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
		}
		sub_98196C(imageId, 24, 0, 8, 32, 1, height + 5, get_current_rotation());
		//height += 2 (height + 7)

		hasFence = track_paint_util_has_fence(EDGE_SW, position, mapElement, ride, get_current_rotation());
		if (hasFence) {
			if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 3) {
				imageId = SPR_STATION_BEGIN_ANGLE_FENCE_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			} else if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 1) {
				imageId = SPR_STATION_LIGHT_BACK_ANGLE_FENCED_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			} else {
				imageId = SPR_STATION_FENCE_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			}
			sub_98196C(imageId, 31, 0, 1, 32, 7, height + 7, get_current_rotation());
		} else if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 3) {
			// Addition: draw only small fence if there is an entrance/exit at the beginning
			imageId = SPR_STATION_FENCE_SMALL_SW_NE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 23, 31, 8, 1, 7, height + 7, get_current_rotation());
		} else if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 1) {
			// Addition: draw only small fence if there is an entrance/exit at the end
			imageId = SPR_STATION_LIGHT_BACK_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 23, 31, 8, 1, 7, height + 7, get_current_rotation());
		}

		//height -= 7 (height)
		track_paint_util_draw_station_covers(EDGE_SW, hasFence, entranceStyle, direction, height);
		//height += 7 (height + 7)

		if (mapElement->properties.track.type == TRACK_ELEM_BEGIN_STATION && direction == 3) {
			imageId = SPR_STATION_FENCE_SMALL_SW_NE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 0, 31, 8, 1, 7, height + 7, get_current_rotation());
		} else if (mapElement->properties.track.type == TRACK_ELEM_END_STATION && direction == 1) {
			imageId = SPR_STATION_LIGHT_BACK_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 0, 31, 8, 1, 7, height + 7, get_current_rotation());
		}
	}
}

bool track_paint_util_draw_station_covers(enum edge edge, bool hasFence, const rct_ride_entrance_definition * entranceStyle, uint8 direction, uint16 height)
{
	if (!(RCT2_GLOBAL(0x0141E9DB, uint8) & 3)) {
		return false;
	}

	uint32 imageId;
	uint32 baseImageId = entranceStyle->base_image_id;
	int imageOffset;
	rct_xyz16 offset, bounds, boundsOffset;

	offset = (rct_xyz16) {0, 0, height};
	switch (edge) {
		case EDGE_NE:
			bounds = (rct_xyz16) {1, 30, 0};
			boundsOffset = (rct_xyz16) {0, 1, height + 1};
			imageOffset = hasFence ? SPR_STATION_COVER_OFFSET_SE_NW_BACK_1 : SPR_STATION_COVER_OFFSET_SE_NW_BACK_0;
			break;
		case EDGE_SE:
			bounds = (rct_xyz16) {32, 32, 0};
			boundsOffset = (rct_xyz16) {1, 0, height + 23};
			imageOffset = SPR_STATION_COVER_OFFSET_NE_SW_FRONT;
			break;
		case EDGE_SW:
			bounds = (rct_xyz16) {32, 32, 0};
			boundsOffset = (rct_xyz16) {0, 0, height + 23};
			imageOffset = SPR_STATION_COVER_OFFSET_SE_NW_FRONT;
			break;
		case EDGE_NW:
			bounds = (rct_xyz16) {30, 1, 30};
			boundsOffset = (rct_xyz16) {1, 0, height + 1};
			imageOffset = hasFence ? SPR_STATION_COVER_OFFSET_NE_SW_BACK_1 : SPR_STATION_COVER_OFFSET_NE_SW_BACK_0;
			break;
	}

	if (RCT2_GLOBAL(0x00F441A0, uint32) != 0x20000000) {
		baseImageId &= 0x7FFFF;
	}

	if (baseImageId <= 0x20) {
		return false;
	}

	if (baseImageId & 0x40000000) {
		imageId = (baseImageId & 0xBFFFFFFF) + imageOffset;
		sub_98197C(imageId, (sint8)offset.x, (sint8)offset.y, bounds.x, bounds.y, (sint8)bounds.z, offset.z, boundsOffset.x, boundsOffset.y, boundsOffset.z, get_current_rotation());

		uint32 edi = RCT2_GLOBAL(0x00F44198, uint32) & (0b11111 << 19);

		// weird jump
		imageId = (baseImageId | edi) + 0x3800000 + imageOffset + 12;
		sub_98199C(imageId, (sint8)offset.x, (sint8)offset.y, bounds.x, bounds.y, (sint8)bounds.z, offset.z, boundsOffset.x, boundsOffset.y, boundsOffset.z, get_current_rotation());
		return true;
	}

	imageId = (baseImageId + imageOffset) | RCT2_GLOBAL(0x00F44198, uint32);
	sub_98197C(imageId, (sint8)offset.x, (sint8)offset.y, bounds.x, bounds.y, (sint8)bounds.z, offset.z, boundsOffset.x, boundsOffset.y, boundsOffset.z, get_current_rotation());
	return true;
}

void track_paint_util_draw_station_platform(rct_ride *ride, uint8 direction, int height, int zOffset, rct_map_element * mapElement)
{
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};
	const rct_ride_entrance_definition * entranceStyle = &RideEntranceDefinitions[ride->entrance_style];
	if (direction & 1) {
		bool hasFence = track_paint_util_has_fence(EDGE_NE, position, mapElement, ride, get_current_rotation());
		uint32 imageId = (hasFence ? SPR_STATION_NARROW_EDGE_FENCED_NE : SPR_STATION_NARROW_EDGE_NE) | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 0, 0, 8, 32, 1, height + zOffset, get_current_rotation());
		track_paint_util_draw_station_covers(EDGE_NE, hasFence, entranceStyle, direction, height);

		imageId = SPR_STATION_NARROW_EDGE_SW | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 24, 0, 8, 32, 1, height + zOffset, get_current_rotation());

		hasFence = track_paint_util_has_fence(EDGE_SW, position, mapElement, ride, get_current_rotation());
		if (hasFence) {
			imageId = SPR_STATION_FENCE_NW_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 31, 0, 1, 32, 7, height + zOffset + 2, get_current_rotation());
		}
		track_paint_util_draw_station_covers(EDGE_SW, hasFence, entranceStyle, direction, height);
	} else {
		bool hasFence = track_paint_util_has_fence(EDGE_NW, position, mapElement, ride, get_current_rotation());
		uint32 imageId = (hasFence ? SPR_STATION_NARROW_EDGE_FENCED_NW : SPR_STATION_NARROW_EDGE_NW) | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 0, 0, 32, 8, 1, height + zOffset, get_current_rotation());
		track_paint_util_draw_station_covers(EDGE_NW, hasFence, entranceStyle, direction, height);

		imageId = SPR_STATION_NARROW_EDGE_SE | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 0, 24, 32, 8, 1, height + zOffset, get_current_rotation());

		hasFence = track_paint_util_has_fence(EDGE_SE, position, mapElement, ride, get_current_rotation());
		if (hasFence) {
			imageId = SPR_STATION_FENCE_SW_NE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 0, 31, 32, 1, 7, height + zOffset + 2, get_current_rotation());
		}
		track_paint_util_draw_station_covers(EDGE_SE, hasFence, entranceStyle, direction, height);
	}
}

void track_paint_util_draw_pier(rct_ride * ride, const rct_ride_entrance_definition * entranceStyle, rct_xy16 position, uint8 direction, int height, rct_map_element * mapElement, uint8 rotation)
{
	bool hasFence;
	uint32 imageId;

	if (direction & 1) {
		hasFence = track_paint_util_has_fence(EDGE_NE, position, mapElement, ride, get_current_rotation());
		imageId = (hasFence ? SPR_STATION_PIER_EDGE_NE_FENCED : SPR_STATION_PIER_EDGE_NE) | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98197C(imageId, 0, 0, 6, 32, 1, height, 2, 0, height, get_current_rotation());
		track_paint_util_draw_station_covers(EDGE_NE, hasFence, entranceStyle, direction, height);

		imageId = SPR_STATION_PIER_EDGE_SW | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 24, 0, 8, 32, 1, height, get_current_rotation());

		hasFence = track_paint_util_has_fence(EDGE_SW, position, mapElement, ride, get_current_rotation());
		if (hasFence) {
			imageId = SPR_STATION_PIER_FENCE_SW | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 31, 0, 1, 32, 7, height + 2, get_current_rotation());
		}
		track_paint_util_draw_station_covers(EDGE_SW, hasFence, entranceStyle, direction, height);
	} else {
		hasFence = track_paint_util_has_fence(EDGE_NW, position, mapElement, ride, rotation);
		imageId = (hasFence ? SPR_STATION_PIER_EDGE_NW_FENCED : SPR_STATION_PIER_EDGE_NW) | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98197C(imageId, 0, 0, 32, 6, 1, height, 0, 2, height, rotation);
		track_paint_util_draw_station_covers(EDGE_NW, hasFence, entranceStyle, direction, height);

		imageId = SPR_STATION_PIER_EDGE_SE | RCT2_GLOBAL(0x00F4419C, uint32);
		sub_98196C(imageId, 0, 24, 32, 8, 1, height, rotation);

		hasFence = track_paint_util_has_fence(EDGE_SE, position, mapElement, ride, rotation);
		if (hasFence) {
			imageId = SPR_STATION_PIER_FENCE_SE | RCT2_GLOBAL(0x00F4419C, uint32);
			sub_98196C(imageId, 0, 31, 32, 1, 7, height + 2, rotation);
		}
		track_paint_util_draw_station_covers(EDGE_SE, hasFence, entranceStyle, direction, height);
	}
}

const rct_xy16 defaultRightHelixUpSmallQuarterBoundLengths[4][3][2] = {
	{
		{32, 20},
		{16, 16},
		{20, 32}
	},
	{
		{20, 32},
		{16, 16},
		{ {32, 20}, {32, 1} }
	},
	{
		{ {0}, {32, 1} },
		{16, 16},
		{ {0}, {32, 20} }
	},
	{
		{ {20, 32}, {1, 32} },
		{16, 16},
		{32, 20},
	}
};

const rct_xyz16 defaultRightHelixUpSmallQuarterBoundOffsets[4][3][2] = {
	{
		{0, 6},
		{16, 16},
		{6, 0},
	},
	{
		{6, 0},
		{16, 0},
		{ {0, 6}, {0, 21} },
	},
	{
		{ {0}, {0, 21} },
		{0, 0, 21},
		{ {0}, {21, 0} },
	},
	{
		{ {6, 0}, {21, 0} },
		{0, 16},
		{0, 6},
	}
};

static const sint8 right_helix_up_small_quarter_tiles_sprite_map[] = {0, -1, 1, 2};

void track_paint_util_right_helix_up_small_quarter_tiles_paint(const sint8 thickness[2], sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][3][2], const rct_xy16 offsets[4][3][2], const rct_xy16 boundsLengths[4][3][2], const rct_xyz16 boundsOffsets[4][3][2], uint8 rotation)
{
	int index = right_helix_up_small_quarter_tiles_sprite_map[trackSequence];
	if (index < 0) {
		return;
	}

	if (sprites[direction][index][0] != 0) {
		uint32 imageId = sprites[direction][index][0] | colourFlags;
		rct_xy16 offset = (offsets == NULL ? (rct_xy16) { 0, 0 } : offsets[direction][index][0]);
		rct_xy16 boundsLength = boundsLengths[direction][index][0];
		rct_xyz16 boundsOffset = (boundsOffsets == NULL ? (rct_xyz16) { .x = offset.x, .y = offset.y, .z = 0 } : boundsOffsets[direction][index][0]);

		sub_98197C(imageId, (sint8)offset.x, (sint8)offset.y, boundsLength.x, boundsLength.y, thickness[0], height, boundsOffset.x, boundsOffset.y, height + boundsOffset.z, rotation);
	}
	if (sprites[direction][index][1] != 0) {
		uint32 imageId = sprites[direction][index][1] | colourFlags;
		rct_xy16 offset = (offsets == NULL ? (rct_xy16){0, 0} : offsets[direction][index][1]);
		rct_xy16 boundsLength = boundsLengths[direction][index][1];
		rct_xyz16 boundsOffset = (boundsOffsets == NULL ? (rct_xyz16){.x = offset.x, .y = offset.y, .z = 0} : boundsOffsets[direction][index][1]);

		sub_98197C(imageId, (sint8) offset.x, (sint8) offset.y, boundsLength.x, boundsLength.y, thickness[1], height, boundsOffset.x, boundsOffset.y, height + boundsOffset.z, rotation);
	}
}

const rct_xyz16 defaultRightHelixUpLargeQuarterBoundOffsets[4][5][2] = {
	{
		{0, 6},
		{0,  16},
		{0,  0},
		{16, 0},
		{6, 0},
	},
	{
		{6, 0},
		{16, 0},
		{0,  16},
		{0,  0},
		{ {0, 6}, {0, 27} },
	},
	{
		{ {0}, {0, 27} },
		{0,  0, 27},
		{16, 16, 27},
		{0,  0, 27},
		{ {0}, {27, 0} },
	},
	{
		{{6, 0}, {27, 0} },
		{0,  0},
		{16, 0},
		{0,  16},
		{0, 6},
	}
};

const rct_xy16 defaultRightHelixUpLargeQuarterBoundLengths[4][5][2] = {
	{
		{32, 20},
		{32, 16},
		{16, 16},
		{16, 32},
		{20, 32},
	},
	{
		{20, 32},
		{16, 32},
		{16, 16},
		{32, 16},
		{ {32, 20}, {32, 1} },
	},
	{
		{ {0}, {32, 1} },
		{32, 16},
		{16, 16},
		{16, 32},
		{ {0}, {1, 32} },
	},
	{
		{{20, 32}, {1, 32} },
		{16, 32},
		{16, 16},
		{32, 16},
		{32, 20},
	}
};

static const sint8 right_helix_up_large_quarter_sprite_map[] = {0, -1, 1, 2, -1, 3, 4};
void track_paint_util_right_helix_up_large_quarter_tiles_paint(const sint8 thickness[2], sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][5][2], const rct_xy16 offsets[4][5][2], const rct_xy16 boundsLengths[4][5][2], const rct_xyz16 boundsOffsets[4][5][2], uint8 rotation)
{
	int index = right_helix_up_large_quarter_sprite_map[trackSequence];
	if (index < 0) {
		return;
	}

	if (sprites[direction][index][0] != 0) {
		uint32 imageId = sprites[direction][index][0] | colourFlags;
		rct_xy16 offset = (offsets == NULL ? (rct_xy16) { 0, 0 } : offsets[direction][index][0]);
		rct_xy16 boundsLength = boundsLengths[direction][index][0];
		rct_xyz16 boundsOffset = (boundsOffsets == NULL ? (rct_xyz16) { .x = offset.x, .y = offset.y, .z = 0 } : boundsOffsets[direction][index][0]);

		sub_98197C(imageId, (sint8)offset.x, (sint8)offset.y, boundsLength.x, boundsLength.y, thickness[0], height, boundsOffset.x, boundsOffset.y, height + boundsOffset.z, rotation);
	}
	if (sprites[direction][index][1] != 0) {
		uint32 imageId = sprites[direction][index][1] | colourFlags;
		rct_xy16 offset = (offsets == NULL ? (rct_xy16){0, 0} : offsets[direction][index][1]);
		rct_xy16 boundsLength = boundsLengths[direction][index][1];
		rct_xyz16 boundsOffset = (boundsOffsets == NULL ? (rct_xyz16){.x = offset.x, .y = offset.y, .z = 0} : boundsOffsets[direction][index][1]);

		sub_98197C(imageId, (sint8) offset.x, (sint8) offset.y, boundsLength.x, boundsLength.y, thickness[1], height, boundsOffset.x, boundsOffset.y, height + boundsOffset.z, rotation);
	}
}

const rct_xy16 defaultLeftEighthToDiagBoundLengths[4][4] = {
	{
		{32, 20},
		{32, 16},
		{16, 16},
		{16, 16},
	},
	{
		{20, 32},
		{16, 34},
		{16, 16},
		{18, 16},
	},
	{
		{32, 20},
		{32, 16},
		{16, 16},
		{16, 16},
	},
	{
		{20, 32},
		{16, 32},
		{16, 16},
		{16, 16},
	},
};

const rct_xyz16 defaultLeftEighthToDiagBoundOffsets[4][4] = {
	{
		{0, 6},
		{0,  0},
		{0,  16},
		{16, 16},
	},
	{
		{6, 0},
		{0,  0},
		{16, 16},
		{16, 0},
	},
	{
		{0, 6},
		{0,  16},
		{16, 0},
		{0,  0},
	},
	{
		{6, 0},
		{16, 0},
		{0,  0},
		{0,  16},
	},
};

const rct_xy16 defaultRightEighthToDiagBoundLengths[4][4] = {
	{
		{32, 20},
		{32, 16},
		{16, 16},
		{16, 16},
	},
	{
		{20, 32},
		{16, 32},
		{16, 16},
		{16, 16},
	},
	{
		{32, 20},
		{34, 16},
		{28, 28},
		{16, 18},
	},
	{
		{20, 32},
		{16, 32},
		{16, 16},
		{16, 16},
	},
};

const rct_xyz16 defaultRightEighthToDiagBoundOffsets[4][4] = {
	{
		{0, 6},
		{0,  16},
		{0,  0},
		{16, 0},
	},
	{
		{6, 0},
		{16, 0},
		{0,  16},
		{0,  0},
	},
	{
		{0, 6},
		{0,  0},
		{4,  4},
		{0,  16},
	},
	{
		{6, 0},
		{0,  0},
		{16, 0},
		{16, 16},
	},
};

const sint8 defaultEighthToDiagThickness[4][4] = {
	{
		1,
		1,
		1,
		1,
	},
	{
		1,
		1,
		1,
		1,
	},
	{
		1,
		1,
		1,
		1,
	},
	{
		1,
		1,
		1,
		1,
	},
};

static const sint8 eighth_to_diag_sprite_map[] = {0, 1, 2, -1, 3};
void track_paint_util_eighth_to_diag_tiles_paint(const sint8 thickness[4][4], sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][4], const rct_xy16 offsets[4][4], const rct_xy16 boundsLengths[4][4], const rct_xyz16 boundsOffsets[4][4], uint8 rotation)
{
	int index = eighth_to_diag_sprite_map[trackSequence];
	if (index < 0) {
		return;
	}

	uint32 imageId = sprites[direction][index] | colourFlags;
	rct_xy16 offset = (offsets == NULL ? (rct_xy16) { 0, 0 } : offsets[direction][index]);
	rct_xy16 boundsLength = boundsLengths[direction][index];
	rct_xyz16 boundsOffset = (boundsOffsets == NULL ? (rct_xyz16) { .x = offset.x, .y = offset.y, .z = 0 } : boundsOffsets[direction][index]);

	sub_98197C(imageId, (sint8)offset.x, (sint8)offset.y, boundsLength.x, boundsLength.y, thickness[direction][index], height, boundsOffset.x, boundsOffset.y, height + boundsOffset.z, rotation);
}

const rct_xy16 defaultDiagTileOffsets[4] = {
	{-16, -16},
	{-16, -16},
	{-16, -16},
	{-16, -16},
};

const rct_xy16 defaultDiagBoundLengths[4] = {
	{32, 32},
	{32, 32},
	{32, 32},
	{32, 32},
};

static const sint8 diag_sprite_map[4][4] = {
	{-1, 0,  -1, -1},
	{-1, -1, -1, 0},
	{-1, -1, 0,  -1},
	{0,  -1, -1, -1},
};

void track_paint_util_diag_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4], const rct_xy16 offsets[4], const rct_xy16 boundsLengths[4], const rct_xyz16 boundsOffsets[4], uint8 rotation)
{
	int index = diag_sprite_map[direction][trackSequence];
	if (index < 0) {
		return;
	}

	uint32 imageId = sprites[direction] | colourFlags;
	rct_xy16 offset = (offsets == NULL ? (rct_xy16) { 0, 0 } : offsets[direction]);
	rct_xy16 boundsLength = boundsLengths[direction];
	rct_xyz16 boundsOffset = (boundsOffsets == NULL ? (rct_xyz16) { .x = offset.x, .y = offset.y, .z = 0 } : boundsOffsets[direction]);

	sub_98197C(imageId, (sint8)offset.x, (sint8)offset.y, boundsLength.x, boundsLength.y, thickness, height, boundsOffset.x, boundsOffset.y, height + boundsOffset.z, rotation);
}

const uint8 mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[] = {6, 4, 5, 3, 1, 2, 0};

const rct_xy16 defaultRightQuarterTurn5TilesOffsets[4][5] = {
	{
		{0, 6},
		{0,  16},
		{0,  0},
		{16, 0},
		{6, 0},
	},
	{
		{6, 0},
		{16, 0},
		{0,  16},
		{0,  0},
		{0, 6},
	},
	{
		{0, 6},
		{0,  0},
		{16, 16},
		{0,  0},
		{6, 0},
	},
	{
		{6, 0},
		{0,  0},
		{16, 0},
		{0,  16},
		{0, 6},
	}
};

const rct_xy16 defaultRightQuarterTurn5TilesBoundLengths[4][5] = {
	{
		{32, 20},
		{32, 16},
		{16, 16},
		{16, 32},
		{20, 32},
	},
	{
		{20, 32},
		{16, 32},
		{16, 16},
		{32, 16},
		{32, 20},
	},
	{
		{32, 20},
		{32, 16},
		{16, 16},
		{16, 32},
		{20, 32},
	},
	{
		{20, 32},
		{16, 32},
		{16, 16},
		{32, 16},
		{32, 20},
	}
};

static const sint8 right_quarter_turn_5_tiles_sprite_map[] = {0, -1, 1, 2, -1, 3, 4};
void track_paint_util_right_quarter_turn_5_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][5], const rct_xy16 offsets[4][5], const rct_xy16 boundsLengths[4][5], const rct_xy16 boundsOffsets[4][5], uint8 rotation)
{
	int index = right_quarter_turn_5_tiles_sprite_map[trackSequence];
	if (index < 0) {
		return;
	}

	uint32 imageId = sprites[direction][index] | colourFlags;
	rct_xy16 offset = (offsets == NULL ? (rct_xy16){0, 0} : offsets[direction][index]);
	rct_xy16 boundsLength = boundsLengths[direction][index];
	rct_xy16 boundsOffset = (boundsOffsets == NULL ? offset : boundsOffsets[direction][index]);

	sub_98197C(imageId, (sint8) offset.x, (sint8) offset.y, boundsLength.x, boundsLength.y, thickness, height, boundsOffset.x, boundsOffset.y, height, rotation);
}

void track_paint_util_right_quarter_turn_5_tiles_paint_2(sint16 height, int direction, uint8 rotation, uint8 trackSequence, uint32 colourFlags, const sprite_bb sprites[][5])
{
	sint8 sprite = right_quarter_turn_5_tiles_sprite_map[trackSequence];
	if (sprite < 0) {
		return;
	}

	const sprite_bb *spriteBB = &sprites[direction][sprite];
	uint32 imageId = spriteBB->sprite_id | colourFlags;
	sub_98197C(imageId,
				(sint8)spriteBB->offset.x, (sint8)spriteBB->offset.y,
				spriteBB->bb_size.x, spriteBB->bb_size.y, (sint8)spriteBB->bb_size.z,
				height + spriteBB->offset.z,
				spriteBB->bb_offset.x, spriteBB->bb_offset.y, height + spriteBB->bb_offset.z,
				rotation);
}

const uint8 mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[] = {3, 1, 2, 0};

const rct_xy16 defaultRightQuarterTurn3TilesOffsets[4][3] = {
	{
		{0, 6},
		{16, 16},
		{6, 0},
	},
	{
		{6, 0},
		{16, 0},
		{0, 6},
	},
	{
		{0, 6},
		{0,  0},
		{6, 0},
	},
	{
		{6, 0},
		{0,  16},
		{0, 6},
	}
};

const rct_xy16 defaultRightQuarterTurn3TilesBoundLengths[4][3] = {
	{
		{32, 20},
		{16, 16},
		{20, 32},
	},
	{
		{20, 32},
		{16, 16},
		{32, 20},
	},
	{
		{32, 20},
		{16, 16},
		{20, 32},
	},
	{
		{20, 32},
		{16, 16},
		{32, 20},
	}
};

static const sint8 right_quarter_turn_3_tiles_sprite_map[] = {0, -1, 1, 2};
void track_paint_util_right_quarter_turn_3_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][3], const rct_xy16 offsets[4][3], const rct_xy16 boundsLengths[4][3], const rct_xy16 boundsOffsets[4][3], uint8 rotation)
{
	int index = right_quarter_turn_3_tiles_sprite_map[trackSequence];
	if (index < 0) {
		return;
	}

	uint32 imageId = sprites[direction][index] | colourFlags;
	rct_xy16 offset = (offsets == NULL ? (rct_xy16){0, 0} : offsets[direction][index]);
	rct_xy16 boundsLength = boundsLengths[direction][index];
	rct_xy16 boundsOffset = (boundsOffsets == NULL ? offset : boundsOffsets[direction][index]);

	sub_98197C(imageId, (sint8) offset.x, (sint8) offset.y, boundsLength.x, boundsLength.y, thickness, height, boundsOffset.x, boundsOffset.y, height, rotation);
}

void track_paint_util_right_quarter_turn_3_tiles_tunnel(sint16 height, uint8 direction, uint8 trackSequence, uint8 tunnelType)
{
	if (direction == 0 && trackSequence == 0) {
		paint_util_push_tunnel_left(height, tunnelType);
	}

	if (direction == 0 && trackSequence == 3) {
		paint_util_push_tunnel_right(height, tunnelType);
	}


	if (direction == 1 && trackSequence == 3) {
		paint_util_push_tunnel_left(height, tunnelType);
	}


	if (direction == 3 && trackSequence == 0) {
		paint_util_push_tunnel_right(height, tunnelType);
	}
}


static const sint8 left_quarter_turn_3_tiles_sprite_map[] = {2, -1, 1, 0};
void track_paint_util_left_quarter_turn_3_tiles_paint(sint8 thickness, sint16 height, int direction, uint8 trackSequence, uint32 colourFlags, const uint32 sprites[4][3], uint8 rotation)
{
	sint8 sprite = left_quarter_turn_3_tiles_sprite_map[trackSequence];
	if (sprite < 0) {
		return;
	}

	uint32 imageId = sprites[(direction + 1) % 4][sprite] | colourFlags;

	switch (direction) {
		case 0:
			switch (trackSequence) {
				case 0: sub_98197C(imageId, 0, 0, 32, 20, thickness, height, 0, 6, height, rotation); break;
				case 2: sub_98197C(imageId, 0, 0, 16, 16, thickness, height, 16, 0, height, rotation); break;
				case 3: sub_98197C(imageId, 0, 0, 20, 32, thickness, height, 6, 0, height, rotation); break;
			}
			break;

		case 1:
			switch (trackSequence) {
				case 0: sub_98197C(imageId, 0, 0, 20, 32, thickness, height, 6, 0, height, rotation); break;
				case 2: sub_98197C(imageId, 0, 0, 16, 16, thickness, height, 0, 0, height, rotation); break;
				case 3: sub_98197C(imageId, 0, 0, 32, 20, thickness, height, 0, 6, height, rotation); break;
			}
			break;

		case 2:
			switch (trackSequence) {
				case 0: sub_98197C(imageId, 0, 0, 32, 20, thickness, height, 0, 6, height, rotation); break;
				case 2: sub_98197C(imageId, 0, 0, 16, 16, thickness, height, 0, 16, height, rotation); break;
				case 3: sub_98197C(imageId, 0, 0, 20, 32, thickness, height, 6, 0, height, rotation); break;
			}
			break;

		case 3:
			switch (trackSequence) {
				case 0: sub_98197C(imageId, 0, 0, 20, 32, thickness, height, 6, 0, height, rotation); break;
				case 2: sub_98197C(imageId, 0, 0, 16, 16, thickness, height, 16, 16, height, rotation); break;
				case 3: sub_98197C(imageId, 0, 0, 32, 20, thickness, height, 0, 6, height, rotation); break;
			}
			break;
	}
}

void track_paint_util_left_quarter_turn_3_tiles_tunnel(sint16 height, uint8 direction, uint8 trackSequence)
{
	if (direction == 0 && trackSequence == 0) {
		paint_util_push_tunnel_left(height, TUNNEL_0);
	}


	if (direction == 2 && trackSequence == 3) {
		paint_util_push_tunnel_right(height, TUNNEL_0);
	}


	if (direction == 3 && trackSequence == 0) {
		paint_util_push_tunnel_right(height, TUNNEL_0);
	}

	if (direction == 3 && trackSequence == 3) {
		paint_util_push_tunnel_left(height, TUNNEL_0);
	}
}


void track_paint_util_left_quarter_turn_1_tile_paint(sint8 thickness, sint16 height, sint16 boundBoxZOffset, int direction, uint32 colourFlags, const uint32 * sprites, uint8 rotation)
{
	uint32 imageId = sprites[direction] | colourFlags;

	switch (direction) {
		case 0: sub_98197C(imageId, 0, 0, 26, 24, thickness, height, 6, 2, height + boundBoxZOffset, rotation); break;
		case 1: sub_98197C(imageId, 0, 0, 26, 26, thickness, height, 0, 0, height + boundBoxZOffset, rotation); break;
		case 2: sub_98197C(imageId, 0, 0, 24, 26, thickness, height, 2, 6, height + boundBoxZOffset, rotation); break;
		case 3: sub_98197C(imageId, 0, 0, 24, 24, thickness, height, 6, 6, height + boundBoxZOffset, rotation); break;
	}
}

void track_paint_util_left_quarter_turn_1_tile_tunnel(sint16 height, uint8 direction, uint8 trackSequence)
{
	switch (direction) {
		case 0:
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
	}
}

void track_paint_util_spinning_tunnel_paint(sint8 thickness, sint16 height, uint8 direction, uint8 rotation)
{

	int frame = gScenarioTicks >> 2 & 3;
	uint32 colourFlags = RCT2_GLOBAL(0x00F4419C, uint32);

	uint32 colourFlags2 = RCT2_GLOBAL(0x00F44198, uint32);
	if (colourFlags2 & ((uint32)IMAGE_TYPE_UNKNOWN << 28)) {
		colourFlags |= colourFlags2 & ((uint32)IMAGE_TYPE_UNKNOWN << 28 | 0x1F << 24);
	}

	uint32 imageId = trackSpritesGhostTrainSpinningTunnel[direction & 1][0][frame] | colourFlags;
	if (direction == 0 || direction == 2) {
		sub_98199C(imageId, 0, 0, 28, 20, thickness, height, 2, 6, height, rotation);
	} else {
		sub_98199C(imageId, 0, 0, 20, 28, thickness, height, 6, 2, height, rotation);
	}

	imageId = trackSpritesGhostTrainSpinningTunnel[direction & 1][1][frame] | colourFlags;
	if (direction == 0 || direction == 2) {
		sub_98197C(imageId, 0, 0, 26, 1, 23, height, 4, 28, height, rotation);
	} else {
		sub_98197C(imageId, 0, 0, 1, 26, 23, height, 28, 4, height, rotation);
	}
}

/**
 *
 *  rct2: 0x006C4794
 */
void track_paint(uint8 direction, int height, rct_map_element *mapElement)
{
	rct_drawpixelinfo *dpi = unk_140E9A8;
	rct_ride *ride;
	int rideIndex, trackType, trackColourScheme, trackSequence;

	rideIndex = mapElement->properties.track.ride_index;
	ride = get_ride(rideIndex);
	if (ride->type == RIDE_TYPE_NULL) {
		log_error("Attempted to paint invalid ride: %d", rideIndex);
		return;
	}

	// HACK Set entrance style to plain if none to stop glitch until entrance track piece is implemented
	bool isEntranceStyleNone = false;
	if (ride->entrance_style == RIDE_ENTRANCE_STYLE_NONE) {
		isEntranceStyleNone = true;
		ride->entrance_style = RIDE_ENTRANCE_STYLE_PLAIN;
	}

	if (!(RCT2_GLOBAL(0x009DEA6F, uint8) & 1) || rideIndex == RCT2_GLOBAL(0x00F64DE8, uint8)) {
		trackType = mapElement->properties.track.type;
		trackSequence = mapElement->properties.track.sequence & 0x0F;
		trackColourScheme = mapElement->properties.track.colour & 3;

		if ((gCurrentViewportFlags & VIEWPORT_FLAG_TRACK_HEIGHTS) && dpi->zoom_level == 0) {
			gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_NONE;
			if (TrackHeightMarkerPositions[trackType] & (1 << trackSequence)) {
				uint16 ax = RideData5[ride->type].z_offset;
				uint32 ebx = 0x20381689 + (height + 8) / 16;
				ebx += RCT2_GLOBAL(RCT2_ADDRESS_CONFIG_HEIGHT_MARKERS, uint16);
				ebx -= RCT2_GLOBAL(0x01359208, uint16);
				sub_98197C(ebx, 16, 16, 1, 1, 0, height + ax + 3, 1000, 1000, 2047, get_current_rotation());
			}
		}

		gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_RIDE;
		RCT2_GLOBAL(0x00F44198, uint32) = (ride->track_colour_main[trackColourScheme] << 19) | (ride->track_colour_additional[trackColourScheme] << 24) | 0xA0000000;
		RCT2_GLOBAL(0x00F441A0, uint32) = 0x20000000;
		RCT2_GLOBAL(0x00F441A4, uint32) = 0x20C00000;
		RCT2_GLOBAL(0x00F4419C, uint32) = (ride->track_colour_supports[trackColourScheme] << 19) | 0x20000000;
		if (mapElement->type & MAP_ELEMENT_TYPE_FLAG_HIGHLIGHT) {
			RCT2_GLOBAL(0x00F44198, uint32) = 0x21600000;
			RCT2_GLOBAL(0x00F4419C, uint32) = 0x21600000;
			RCT2_GLOBAL(0x00F441A0, uint32) = 0x21600000;
			RCT2_GLOBAL(0x00F441A4, uint32) = 0x21600000;
		}
		if (mapElement->flags & MAP_ELEMENT_FLAG_GHOST) {
			uint32 ghost_id = construction_markers[gConfigGeneral.construction_marker_colour];
			gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_NONE;
			RCT2_GLOBAL(0x00F44198, uint32) = ghost_id;
			RCT2_GLOBAL(0x00F4419C, uint32) = ghost_id;
			RCT2_GLOBAL(0x00F441A0, uint32) = ghost_id;
			RCT2_GLOBAL(0x00F441A4, uint32) = ghost_id;
		}

		int rideType = ride->type;
		if (rideType == RIDE_TYPE_JUNIOR_ROLLER_COASTER && gUseOriginalRidePaint) {
			switch (trackType) {
			case TRACK_ELEM_60_DEG_UP:
			case TRACK_ELEM_25_DEG_UP_TO_60_DEG_UP:
			case TRACK_ELEM_60_DEG_UP_TO_25_DEG_UP:
			case TRACK_ELEM_60_DEG_DOWN:
			case TRACK_ELEM_25_DEG_DOWN_TO_60_DEG_DOWN:
			case TRACK_ELEM_60_DEG_DOWN_TO_25_DEG_DOWN:
			case TRACK_ELEM_DIAG_60_DEG_UP:
			case TRACK_ELEM_DIAG_25_DEG_UP_TO_60_DEG_UP:
			case TRACK_ELEM_DIAG_60_DEG_UP_TO_25_DEG_UP:
			case TRACK_ELEM_DIAG_60_DEG_DOWN:
			case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_60_DEG_DOWN:
			case TRACK_ELEM_DIAG_60_DEG_DOWN_TO_25_DEG_DOWN:
				rideType = RIDE_TYPE_WATER_COASTER;
				break;

			case TRACK_ELEM_FLAT_TO_60_DEG_UP:
			case TRACK_ELEM_60_DEG_UP_TO_FLAT:
			case TRACK_ELEM_FLAT_TO_60_DEG_DOWN:
			case TRACK_ELEM_60_DEG_DOWN_TO_FLAT:
				return;
			}
		}

		TRACK_PAINT_FUNCTION_GETTER paintFunctionGetter = RideTypeTrackPaintFunctions[rideType];
		if (paintFunctionGetter != NULL && !gUseOriginalRidePaint) {
			TRACK_PAINT_FUNCTION paintFunction = paintFunctionGetter(trackType, direction);
			if (paintFunction != NULL) {
				paintFunction(rideIndex, trackSequence, direction, height, mapElement);
			}
		}
		else {
#ifndef NO_RCT2
			TRACK_PAINT_FUNCTION **trackTypeList = (TRACK_PAINT_FUNCTION**)RideTypeTrackPaintFunctionsOld[rideType];
			uint32 *trackDirectionList = (uint32*)trackTypeList[trackType];

			// Have to call from this point as it pushes esi and expects callee to pop it
			RCT2_CALLPROC_X(
				0x006C4934,
				rideType,
				(int)trackDirectionList,
				direction,
				height,
				(int)mapElement,
				rideIndex * sizeof(rct_ride),
				trackSequence
				);
#endif
		}
	}

	if (isEntranceStyleNone) {
		ride->entrance_style = RIDE_ENTRANCE_STYLE_NONE;
	}
}
