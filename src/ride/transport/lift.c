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

#include "../../common.h"
#include "../../interface/viewport.h"
#include "../../paint/paint.h"
#include "../../paint/supports.h"
#include "../track_paint.h"
#include "../track.h"

enum {
	SPR_LIFT_CAGE_BACK = 14994,
	SPR_LIFT_CAGE_FRONT = 14995,
	SPR_LIFT_CAGE_NE_BACK = 14996,
	SPR_LIFT_CAGE_NE_FRONT = 14997,
	SPR_LIFT_CAGE_SE_BACK = 14998,
	SPR_LIFT_CAGE_SE_FRONT = 14999,
	SPR_LIFT_CAGE_SW_BACK = 15000,
	SPR_LIFT_CAGE_SW_FRONT = 15001,
	SPR_LIFT_CAGE_NW_BACK = 15002,
	SPR_LIFT_CAGE_NW_FRONT = 15003,
};

static const uint32 lift_cage_sprites[][2] = {
	{SPR_LIFT_CAGE_BACK,    SPR_LIFT_CAGE_FRONT},
	{SPR_LIFT_CAGE_NE_BACK, SPR_LIFT_CAGE_NE_FRONT},
	{SPR_LIFT_CAGE_SE_BACK, SPR_LIFT_CAGE_SE_FRONT},
	{SPR_LIFT_CAGE_SW_BACK, SPR_LIFT_CAGE_SW_FRONT},
	{SPR_LIFT_CAGE_NW_BACK, SPR_LIFT_CAGE_NW_FRONT},
};

static void paint_lift_cage(sint8 index, uint32 colourFlags, int height, uint8 rotation)
{
	uint32 imageId;

	imageId = lift_cage_sprites[1 + index][0] | colourFlags;
	sub_98197C(imageId, 0, 0, 2, 2, 30, height, 2, 2, height, get_current_rotation());

	imageId = lift_cage_sprites[1 + index][1] | colourFlags;
	sub_98197C(imageId, 0, 0, 2, 2, 30, height, 28, 28, height, get_current_rotation());
}

/** rct2: 0x0076C6CC */
static void paint_lift_base(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = track_map_3x3[direction][trackSequence];

	if (trackSequence == 0) {
		paint_lift_cage(direction, gTrackColours[SCHEME_TRACK], height, get_current_rotation());

		paint_lift_cage(-1, gTrackColours[SCHEME_TRACK], height + 32, get_current_rotation());

		paint_lift_cage(-1, gTrackColours[SCHEME_TRACK], height + 64, get_current_rotation());

		paint_util_set_vertical_tunnel(height + 96);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);

#ifdef __TESTPAINT__
		paint_util_set_general_support_height(height + 32, 0x20);
#else
		paint_util_set_general_support_height(height + 96, 0x20);
#endif

		return;
	}

	int edges = edges_3x3[trackSequence];
	rct_ride * ride = get_ride(rideIndex);
	rct_xy16 position = {gPaintMapPosition.x, gPaintMapPosition.y};

	uint32 imageId = SPR_FLOOR_METAL_B | gTrackColours[SCHEME_SUPPORTS];
		sub_98197C(imageId, 0, 0, 32, 32, 1, height, 0, 0, height, get_current_rotation());

		track_paint_util_paint_fences(edges, position, mapElement, ride, gTrackColours[SCHEME_TRACK], height, fenceSpritesMetalB, get_current_rotation());

	int blockedSegments = 0;
	switch (trackSequence) {
		case 1: blockedSegments = SEGMENT_B8 | SEGMENT_C8 | SEGMENT_B4 | SEGMENT_CC | SEGMENT_BC; break;
		case 2: blockedSegments = SEGMENT_B4 | SEGMENT_CC | SEGMENT_BC; break;
		case 3: blockedSegments = SEGMENT_B4 | SEGMENT_CC | SEGMENT_BC | SEGMENT_D4 | SEGMENT_C0; break;
		case 4: blockedSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_B8; break;
		case 5: blockedSegments = SEGMENT_BC | SEGMENT_D4 | SEGMENT_C0; break;
		case 6: blockedSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_B8 | SEGMENT_D0 | SEGMENT_C0; break;
		case 7: blockedSegments = SEGMENT_B8 | SEGMENT_D0 | SEGMENT_C0 | SEGMENT_D4 | SEGMENT_BC; break;
		case 8: blockedSegments = SEGMENT_B8 | SEGMENT_D0 | SEGMENT_C0; break;
	}
	paint_util_set_segment_support_height(blockedSegments, 0xFFFF, 0);
	paint_util_set_segment_support_height(SEGMENTS_ALL & ~blockedSegments, height + 2, 0x20);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x0076C6DC */
static void paint_lift_tower_section(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence == 1) {
		return;
	}

	paint_lift_cage(-1, gTrackColours[SCHEME_TRACK], height, get_current_rotation());

	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);

	paint_util_set_vertical_tunnel(height + 32);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/**
 * rct2: 0x0076C5BC
 */
TRACK_PAINT_FUNCTION get_track_paint_function_lift(int trackType, int direction)
{
	switch (trackType) {
		case TRACK_ELEM_TOWER_BASE:
			return paint_lift_base;

		case TRACK_ELEM_TOWER_SECTION:
			return paint_lift_tower_section;
	}

	return NULL;
}
