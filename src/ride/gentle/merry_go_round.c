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

#include "../../addresses.h"
#include "../../interface/viewport.h"
#include "../../paint/paint.h"
#include "../../paint/supports.h"
#include "../track_paint.h"
#include "../track.h"

/** rct2: 0x0142805C */
static const uint32 merry_go_round_rider_offsets[] = {
	0, 32, 64, 96, 16, 48, 80, 112
};

/** rct2: 0x0142807C */
static const uint16 merry_go_round_breakdown_vibration[] = {
	0, 1, 2, 3, 4, 3, 2, 1, 0, 0
};

/**
 * rct2: 0x0076287D
 */
static void paint_merry_go_round_structure(uint8 rideIndex, uint8 direction, sint8 xOffset, sint8 yOffset, uint16 height)
{
	rct_map_element * savedMapElement = g_currently_drawn_item;
	height += 7;

	rct_ride * ride = get_ride(rideIndex);
	rct_ride_entry * ride_type = get_ride_entry(ride->subtype);
	rct_vehicle * vehicle = NULL;

	uint32 baseImageId = ride_type->vehicles[0].base_image_id;

	if (ride->lifecycle_flags & RIDE_LIFECYCLE_ON_TRACK
	    && ride->vehicles[0] != SPRITE_INDEX_NULL) {
		gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_SPRITE;
		vehicle = GET_VEHICLE(ride->vehicles[0]);
		g_currently_drawn_item = vehicle;

		if (ride->lifecycle_flags & (RIDE_LIFECYCLE_BREAKDOWN_PENDING | RIDE_LIFECYCLE_BROKEN_DOWN)
		    && ride->breakdown_reason_pending == BREAKDOWN_CONTROL_FAILURE
		    && ride->breakdown_sound_modifier >= 128) {
			height += merry_go_round_breakdown_vibration[(vehicle->current_time >> 1) & 7];
		}
	}

	uint32 rotationOffset = 0;
	if (vehicle != NULL) {
		uint32 rotation = ((vehicle->sprite_direction >> 3) + get_current_rotation()) << 5;
		rotationOffset = (vehicle->vehicle_sprite_type + rotation) % 128;
	}

	uint32 imageOffset = rotationOffset & 0x1F;

	uint32 imageColourFlags = gTrackColours[SCHEME_MISC];
	if (imageColourFlags == 0x20000000) {
		imageColourFlags = ride->vehicle_colours[0].body_colour << 19 | ride->vehicle_colours[0].trim_colour << 24 | 0xA0000000;
	}

	uint32 imageId = (baseImageId + imageOffset) | imageColourFlags;
	sub_98197C(imageId, xOffset, yOffset, 24, 24, 48, height, xOffset + 16, yOffset + 16, height, get_current_rotation());

	rct_drawpixelinfo * dpi = unk_140E9A8;
	if (dpi->zoom_level == 0
	    && ride->lifecycle_flags & RIDE_LIFECYCLE_ON_TRACK
	    && vehicle != NULL) {

		for (int peep = 0; peep <= 14; peep += 2) {
			if (vehicle->num_peeps <= peep) {
				break;
			}

			imageOffset = (merry_go_round_rider_offsets[peep / 2] + rotationOffset) % 128;
			imageOffset -= 13;

			if (imageOffset >= 68) {
				continue;
			}

			imageColourFlags = vehicle->peep_tshirt_colours[peep] << 19 | vehicle->peep_tshirt_colours[peep + 1] << 24 | 0x0A0000000;
			imageId = (baseImageId + 32 + imageOffset) | imageColourFlags;
			sub_98199C(imageId, xOffset, yOffset, 24, 24, 48, height, xOffset + 16, yOffset + 16, height, get_current_rotation());
		}
	}

	g_currently_drawn_item = savedMapElement;
	gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_RIDE;
}

/**
 * rct2: 0x00761B0C
 */
static void paint_merry_go_round(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = track_map_3x3[direction][trackSequence];

	int edges = edges_3x3[trackSequence];
	rct_ride * ride = get_ride(rideIndex);
	rct_xy16 position = {gPaintMapPosition.x, gPaintMapPosition.y};

	wooden_a_supports_paint_setup((direction & 1), 0, height, gTrackColours[SCHEME_MISC], NULL);

	track_paint_util_paint_floor(edges, gTrackColours[SCHEME_TRACK], height, floorSpritesCork, get_current_rotation());

	track_paint_util_paint_fences(edges, position, mapElement, ride, gTrackColours[SCHEME_MISC], height, fenceSpritesRope, get_current_rotation());

	switch(trackSequence) {
		case 1: paint_merry_go_round_structure(rideIndex, direction, 32, 32, height); break;
		case 3: paint_merry_go_round_structure(rideIndex, direction, 32, -32, height); break;
		case 5: paint_merry_go_round_structure(rideIndex, direction, 0, -32, height); break;
		case 6: paint_merry_go_round_structure(rideIndex, direction, -32, 32, height); break;
		case 7: paint_merry_go_round_structure(rideIndex, direction, -32, -32, height); break;
		case 8: paint_merry_go_round_structure(rideIndex, direction, -32, 0, height); break;
	}

	int cornerSegments = 0;
	switch (trackSequence) {
		case 1:
			// top
			cornerSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC;
			break;
		case 3:
			// right
			cornerSegments = SEGMENT_CC | SEGMENT_BC | SEGMENT_D4;
			break;
		case 6:
			// left
			cornerSegments = SEGMENT_C8 | SEGMENT_B8 | SEGMENT_D0;
			break;
		case 7:
			// bottom
			cornerSegments = SEGMENT_D0 | SEGMENT_C0 | SEGMENT_D4;
			break;
	}

	paint_util_set_segment_support_height(cornerSegments, height + 2, 0x20);
	paint_util_set_segment_support_height(SEGMENTS_ALL & ~cornerSegments, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 64, 0x20);
}

/**
 * rct2: 0x0076190C
 */
TRACK_PAINT_FUNCTION get_track_paint_function_merry_go_round(int trackType, int direction)
{
	if (trackType != FLAT_TRACK_ELEM_3_X_3) {
		return NULL;
	}

	return paint_merry_go_round;
}
