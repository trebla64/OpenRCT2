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

enum {
	SPR_DODGEMS_FLOOR = 21925,
	SPR_DODGEMS_ROOF_FRAME = 21926, // 4 directions
	SPR_DODGEMS_ROOF_GLASS = 21930, // 4 directions
	SPR_DODGEMS_FENCE_TOP_RIGHT = 21934,
	SPR_DODGEMS_FENCE_BOTTOM_RIGHT = 21935,
	SPR_DODGEMS_FENCE_BOTTOM_LEFT = 21936,
	SPR_DODGEMS_FENCE_TOP_LEFT = 21937
};

const uint32 dodgems_fence_sprites[] = {
	SPR_DODGEMS_FENCE_TOP_RIGHT,
	SPR_DODGEMS_FENCE_BOTTOM_RIGHT,
	SPR_DODGEMS_FENCE_BOTTOM_LEFT,
	SPR_DODGEMS_FENCE_TOP_LEFT
};

static void paint_dodgems_roof(int height, int offset)
{
	uint32 image_id = (SPR_DODGEMS_ROOF_FRAME + offset) | RCT2_GLOBAL(0x00F44198, uint32);
	sub_98196C(image_id, 0, 0, 32, 32, 2, height, get_current_rotation());

	image_id = (SPR_DODGEMS_ROOF_GLASS + offset) | (0xF << 19) | (0x1 << 24) | 0x40000000;
	paint_attach_to_previous_ps(image_id, 0, 0);
}

static void paint_dodgems(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	uint8 relativeTrackSequence = track_map_4x4[direction][trackSequence];

	int edges = edges_4x4[relativeTrackSequence];
	rct_ride * ride = get_ride(rideIndex);
	rct_xy16 position = {RCT2_GLOBAL(0x009DE56A, sint16), RCT2_GLOBAL(0x009DE56E, sint16)};

	wooden_a_supports_paint_setup(direction & 1, 0, height, RCT2_GLOBAL(0x00F441A0, uint32), NULL);

	uint32 imageId = SPR_DODGEMS_FLOOR | RCT2_GLOBAL(0x00F4419C, uint32);
	sub_98197C(imageId, 0, 0, 30, 30, 1, height, 1, 1, height, get_current_rotation());

	track_paint_util_paint_fences(edges, position, mapElement, ride, RCT2_GLOBAL(0x00F4419C, uint32), height, dodgems_fence_sprites, get_current_rotation());

	switch (direction) {
		case 2:
			trackSequence = 15 - trackSequence;
			// fallthrough
		case 0:
			if ((trackSequence / 4) & 1) {
				paint_dodgems_roof(height + 30, 0);
			} else {
				paint_dodgems_roof(height + 30, 2);
			}
			break;

		case 3:
			trackSequence = 15 - trackSequence;
			// fallthrough
		case 1:
			if ((trackSequence / 4) & 1) {
				paint_dodgems_roof(height + 30, 1);
			} else {
				paint_dodgems_roof(height + 30, 3);
			}
			break;
	}

	paint_util_set_segment_support_height(SEGMENTS_ALL, height + 36, 0x20);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/**
 * rct2:
 */
TRACK_PAINT_FUNCTION get_track_paint_function_dodgems(int trackType, int direction) {
	if (trackType != FLAT_TRACK_ELEM_4_X_4) {
		return NULL;
	}

	return paint_dodgems;
}
