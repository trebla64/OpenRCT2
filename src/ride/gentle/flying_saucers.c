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

#include "../../interface/viewport.h"
#include "../../paint/paint.h"
#include "../../paint/supports.h"
#include "../track_paint.h"
#include "../track.h"

enum
{
	SPR_FLYING_SAUCERS_FLOOR = 21920,
	SPR_FLYING_SAUCERS_FENCE_NE = 21921,
	SPR_FLYING_SAUCERS_FENCE_SE = 21922,
	SPR_FLYING_SAUCERS_FENCE_SW = 21923,
	SPR_FLYING_SAUCERS_FENCE_NW = 21924,
};

static const uint32 flying_saucers_fence_sprites[] = {
	SPR_FLYING_SAUCERS_FENCE_NE,
	SPR_FLYING_SAUCERS_FENCE_SE,
	SPR_FLYING_SAUCERS_FENCE_SW,
	SPR_FLYING_SAUCERS_FENCE_NW,
};

/**
 * rct2: 0x008873D8
 */
static void paint_flying_saucers(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	uint8 relativeTrackSequence = track_map_4x4[direction][trackSequence];

	int edges = edges_4x4[relativeTrackSequence];
	rct_ride * ride = get_ride(rideIndex);
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};

	wooden_a_supports_paint_setup(direction & 1, 0, height, RCT2_GLOBAL(0x00F441A0, uint32), NULL);

	uint32 imageId = SPR_FLYING_SAUCERS_FLOOR | RCT2_GLOBAL(0x00F44198, uint32);
	sub_98197C(imageId, 0, 0, 30, 30, 1, height, 1, 1, height, get_current_rotation());

	track_paint_util_paint_fences(edges, position, mapElement, ride, RCT2_GLOBAL(0x00F44198, uint32), height, flying_saucers_fence_sprites, get_current_rotation());

	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/**
 * rct2: 0x00887208
 */
TRACK_PAINT_FUNCTION get_track_paint_function_flying_saucers(int trackType, int direction)
{
	if (trackType != FLAT_TRACK_ELEM_4_X_4) {
		return NULL;
	}

	return paint_flying_saucers;
}
