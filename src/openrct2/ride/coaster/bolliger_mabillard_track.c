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

#include "../../drawing/drawing.h"
#include "../../paint/supports.h"
#include "../../interface/viewport.h"
#include "../../paint/map_element/map_element.h"
#include "../../paint/paint.h"
#include "../../sprites.h"
#include "../../world/map.h"
#include "../../world/sprite.h"
#include "../ride_data.h"
#include "../track_data.h"
#include "../track_paint.h"
#include "bolliger_mabillard_track.h"

void bolliger_mabillard_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17486, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17487, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17488, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17489, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
			case 0:
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17146, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17147, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	static const uint32 imageIds[4][3] = {
			{ 17154, 17150, SPR_STATION_BASE_A_SW_NE },
			{ 17155, 17151, SPR_STATION_BASE_A_NW_SE },
			{ 17154, 17150, SPR_STATION_BASE_A_SW_NE },
			{ 17155, 17151, SPR_STATION_BASE_A_NW_SE },
	};

	if (mapElement->properties.track.type == TRACK_ELEM_END_STATION) {
		sub_98197C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 1, height, 0, 6, height + 3);
	} else {
		sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 1, height, 0, 6, height + 3);
	}
	sub_98196C_rotated(direction, imageIds[direction][2] | gTrackColours[SCHEME_MISC], 0, 0, 32, 32, 1, height);
	track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], supportType);

	rct_ride * ride = get_ride(rideIndex);
	track_paint_util_draw_station_platform(ride, direction, height, 9, mapElement);

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17498, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17499, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17500, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17501, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17204, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17205, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17206, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17207, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17514, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17515, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17516, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17517, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 32, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17220, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17221, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17222, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17223, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 32, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 56, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

void bolliger_mabillard_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17490, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17491, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17492, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17493, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17196, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17197, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17198, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17199, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17502, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17503, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17506, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17504, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17507, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17505, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17208, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17209, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17212, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17210, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17213, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17211, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 72, 0x20);
}

void bolliger_mabillard_track_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17508, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17509, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17512, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17510, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17513, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17511, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17214, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17215, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17218, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17216, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17219, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17217, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 72, 0x20);
}

void bolliger_mabillard_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17494, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17495, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17496, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17497, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17200, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17201, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17202, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17203, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

void bolliger_mabillard_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_60_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_to_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17259, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17264, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17269, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17254, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17258, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17263, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17268, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17253, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17257, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17262, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17267, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17252, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17256, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17261, 0, 0, 16, 32, 3, height, 0, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17266, 0, 0, 16, 32, 3, height, 0, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17251, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17255, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17260, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17265, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17250, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17156, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17164, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17157, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17165, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17158, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17159, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17160, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17161, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17162, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17166, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17163, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17167, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17162, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17166, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17163, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17167, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17160, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17161, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17158, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17159, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17156, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17164, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17157, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17165, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_banked_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17279, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17290, 0, 0, 32, 1, 26, height, 0, 27, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17284, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17289, 0, 0, 32, 20, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17274, 0, 0, 32, 20, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17278, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17283, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
					metal_a_supports_paint_setup(supportType, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17288, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17273, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17277, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17282, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17287, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17272, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17276, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17281, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17286, 0, 0, 16, 32, 3, height, 0, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17271, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17275, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17280, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17285, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17291, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17270, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_banked_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_banked_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17168, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17172, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17169, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17173, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17170, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17171, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17174, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17175, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17176, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17178, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17177, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17179, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17180, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17184, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17181, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17185, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17182, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17183, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

void bolliger_mabillard_track_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17186, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17187, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17188, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17190, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17189, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17191, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

void bolliger_mabillard_track_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_to_right_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_to_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17192, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17193, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17194, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17195, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17344, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17349, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17354, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17359, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17345, 0, 0, 32, 16, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17350, 0, 0, 32, 16, 3, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17355, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17360, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17346, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17351, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17356, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17361, 0, 0, 16, 16, 3, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17347, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17352, 0, 0, 16, 32, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17357, 0, 0, 16, 32, 3, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17362, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17348, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17353, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17358, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17363, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 3:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17324, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17329, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17334, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17339, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17325, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17330, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17335, 0, 0, 32, 16, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17340, 0, 0, 32, 16, 3, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17326, 0, 0, 16, 16, 3, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17331, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17336, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17341, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17327, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17332, 0, 0, 16, 32, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17337, 0, 0, 16, 32, 3, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17342, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17328, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17333, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17338, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17343, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 1:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_right_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_left_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17308, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17312, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17311, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17315, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17309, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17313, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17310, 0, 0, 32, 26, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17314, 0, 0, 32, 26, 3, height, 0, 6, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17310, 0, 0, 32, 26, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17314, 0, 0, 32, 26, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17309, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17313, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17311, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17315, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17308, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17312, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 2:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17316, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17320, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17319, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17323, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17317, 0, 0, 32, 26, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17321, 0, 0, 32, 26, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17318, 0, 0, 32, 26, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17322, 0, 0, 32, 26, 3, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17318, 0, 0, 32, 26, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17322, 0, 0, 32, 26, 3, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17317, 0, 0, 32, 26, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17321, 0, 0, 32, 26, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17319, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17323, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17316, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17320, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 2:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_vertical_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17594, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17602, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17601, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17609, 0, 6, 32, 20, 7, height);
					metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17595, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17603, 0, 14, 32, 2, 63, height);
					metal_a_supports_paint_setup(supportType, 4, 11, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17600, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17608, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17596, 16, 0, 3, 16, 119, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17604, 12, 0, 3, 16, 119, height, 12, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17599, 10, 16, 4, 16, 119, height, 10, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17607, 16, 16, 2, 16, 119, height, 16, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17597, 0, 0, 32, 16, 3, height + 32);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17605, 0, 0, 32, 16, 3, height + 32);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17598, 0, 16, 32, 16, 3, height + 32);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17606, 0, 16, 32, 16, 3, height + 32);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 5:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17598, 0, 16, 32, 16, 3, height + 32);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17606, 0, 16, 32, 16, 3, height + 32);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17597, 0, 0, 32, 16, 3, height + 32);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17605, 0, 0, 32, 16, 3, height + 32);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 7:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17599, 10, 16, 4, 16, 119, height, 10, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17607, 16, 16, 2, 16, 119, height, 16, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17596, 16, 0, 3, 16, 119, height, 16, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17604, 12, 0, 3, 16, 119, height, 12, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 8:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17600, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17608, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17595, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17603, 0, 14, 32, 2, 63, height);
					metal_a_supports_paint_setup(supportType, 4, 11, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 9:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17601, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17609, 0, 6, 32, 20, 7, height);
					metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17594, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17602, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height - 8, TUNNEL_7);
					break;
				case 2:
					paint_util_push_tunnel_left(height - 8, TUNNEL_7);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_vertical_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17625, 0, 6, 32, 20, 7, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17617, 0, 6, 32, 20, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17618, 0, 6, 32, 20, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17610, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17624, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17616, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17619, 0, 14, 32, 2, 63, height);
					metal_a_supports_paint_setup(supportType, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17611, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17623, 16, 16, 2, 16, 119, height, 16, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17615, 10, 16, 4, 16, 119, height, 10, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17620, 12, 0, 3, 16, 119, height, 12, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17612, 16, 0, 2, 16, 119, height, 16, 0, height);
					break;
			}
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17622, 0, 16, 32, 16, 3, height + 32);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17614, 0, 16, 32, 16, 3, height + 32);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17621, 0, 0, 32, 16, 3, height + 32);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17613, 0, 0, 32, 16, 3, height + 32);
					break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 5:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17621, 0, 0, 32, 16, 3, height + 32);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17613, 0, 0, 32, 16, 3, height + 32);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17622, 0, 16, 32, 16, 3, height + 32);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17614, 0, 16, 32, 16, 3, height + 32);
					break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 7:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17620, 12, 0, 3, 16, 119, height, 12, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17612, 16, 0, 2, 16, 119, height, 16, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17623, 16, 16, 2, 16, 119, height, 16, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17615, 10, 16, 4, 16, 119, height, 10, 16, height);
					break;
			}
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 8:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17619, 0, 14, 32, 2, 63, height);
					metal_a_supports_paint_setup(supportType, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17611, 0, 0, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17624, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17616, 0, 6, 32, 26, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 9:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17618, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17610, 0, 6, 32, 20, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17625, 0, 6, 32, 20, 7, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17617, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height - 8, TUNNEL_7);
					break;
				case 2:
					paint_util_push_tunnel_left(height - 8, TUNNEL_7);
					break;
			}
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
	}

	track_paint_util_right_vertical_loop_segments(direction, trackSequence);
}

void bolliger_mabillard_track_left_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17229, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17232, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17235, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17226, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17228, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17231, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17234, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17225, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17227, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17230, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17233, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17224, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_left_quarter_turn_3(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17241, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17248, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17244, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17247, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17238, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17240, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17243, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17246, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17237, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17239, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17242, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17245, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17249, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17236, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_left_quarter_turn_3_bank(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17375, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17377, 0, 6, 32, 20, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17379, 0, 6, 32, 20, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17373, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17374, 6, 0, 20, 32, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17376, 6, 0, 20, 32, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17378, 6, 0, 20, 32, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17372, 6, 0, 20, 32, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 3:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17364, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17366, 0, 6, 32, 20, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17368, 0, 6, 32, 20, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17370, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17365, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17367, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17369, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17371, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 1:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_right_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_left_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17399, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17406, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17402, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17405, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17396, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17398, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17401, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17404, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17395, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17397, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17400, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17403, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17407, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17394, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height + 8, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height + 8, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17396, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17399, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17406, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17402, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17405, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 1:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17395, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17398, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17401, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17404, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17394, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17397, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17400, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17403, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17407, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17380, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17383, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17386, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17389, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17393, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17381, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17384, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17387, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17390, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17382, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17385, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17392, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17388, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17391, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height + 8, TUNNEL_6);
					break;
				case 1:
					paint_util_push_tunnel_left(height + 8, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17383, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17386, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17389, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17393, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17380, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17384, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17387, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17390, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17381, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17385, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17392, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17388, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17391, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17382, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_right_half_banked_helix_up_small(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_left_half_banked_helix_up_small(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17439, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17450, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17444, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17449, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17434, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17438, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17443, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17448, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17433, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17437, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17442, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17447, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17432, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17436, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17441, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17446, 0, 0, 16, 32, 3, height, 0, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17431, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17435, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17440, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17445, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17451, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17430, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height + 8, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height + 8, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17434, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17439, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17450, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17444, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17449, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 1:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 8:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 9:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17433, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17438, 0, 0, 16, 32, 3, height, 0, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17443, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17448, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17432, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17437, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17442, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17447, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 11:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 12:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17431, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17436, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17441, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17446, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17430, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17435, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17440, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17445, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17451, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17408, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17413, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17418, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17423, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17429, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17409, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17414, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17419, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17424, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17410, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17415, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17420, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17425, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17411, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17416, 0, 0, 16, 32, 3, height, 0, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17421, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17426, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17412, 0, 0, 20, 32, 3, height, 6, 0, height);
					metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17417, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17428, 0, 0, 1, 32, 26, height, 27, 0, height);
					metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17422, 0, 0, 1, 32, 26, height, 27, 0, height);
					metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17427, 0, 0, 20, 32, 3, height, 6, 0, height);
					metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height + 8, TUNNEL_6);
					break;
				case 1:
					paint_util_push_tunnel_left(height + 8, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17413, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17418, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17423, 0, 0, 20, 32, 3, height, 6, 0, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17429, 0, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17408, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 8:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 9:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17414, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17419, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17424, 0, 0, 16, 32, 3, height, 0, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17409, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17415, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17420, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17425, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17410, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 11:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 12:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17416, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17421, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17426, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17411, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17417, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17428, 0, 0, 32, 1, 26, height, 0, 27, height);
					metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17422, 0, 0, 32, 1, 26, height, 0, 27, height);
					metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17427, 0, 0, 32, 20, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17412, 0, 0, 32, 20, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_right_half_banked_helix_up_large(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_left_half_banked_helix_up_large(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17301, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17305, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17302, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17306, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17303, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17307, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17300, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17304, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
	}
	track_paint_util_left_quarter_turn_1_tile_tunnel(direction, height, -8, TUNNEL_7, +56, TUNNEL_8);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

void bolliger_mabillard_track_right_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17292, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17296, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17293, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17297, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17294, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17298, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17295, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17299, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
	}
	track_paint_util_right_quarter_turn_1_tile_tunnel(direction, height, -8, TUNNEL_7, +56, TUNNEL_8);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

void bolliger_mabillard_track_left_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17148, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17149, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_25_deg_up_left_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17914, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17915, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17916, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17917, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_25_deg_up_right_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17918, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17919, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17920, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17921, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_on_ride_photo(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(supportType, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(supportType, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17146, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 1:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(supportType, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(supportType, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17147, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 2:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(supportType, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(supportType, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17146, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 3:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(supportType, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(supportType, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17147, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
	}
	track_paint_util_onride_photo_paint(direction, height + 3, mapElement);
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_25_deg_down_left_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_right_banked(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_25_deg_down_right_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_left_banked(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_90_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17526, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17527, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17528, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17529, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
					break;
			}
			paint_util_set_vertical_tunnel(height + 32);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			break;
	}
}

void bolliger_mabillard_track_90_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_90_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_60_deg_up_to_90_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17518, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17519, 0, 0, 2, 20, 55, height, 24, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17520, 0, 0, 2, 20, 55, height, 24, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17521, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_vertical_tunnel(height + 56);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			break;
	}
}

void bolliger_mabillard_track_90_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_60_deg_up_to_90_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_90_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17522, 0, 0, 32, 20, 3, height, 0, 6, height + 8);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17523, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17524, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17525, 0, 0, 32, 20, 3, height, 0, 6, height + 8);
			break;
	}
	switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height + 48, TUNNEL_8);
			break;
		case 2:
			paint_util_push_tunnel_left(height + 48, TUNNEL_8);
			break;
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 80, 0x20);
}

void bolliger_mabillard_track_60_deg_down_to_90_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17524, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17525, 0, 0, 32, 20, 3, height, 0, 6, height + 8);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17522, 0, 0, 32, 20, 3, height, 0, 6, height + 8);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17523, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 48, TUNNEL_8);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 80, 0x20);
			break;
		case 1:
			break;
	}
}

void bolliger_mabillard_track_left_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17546, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17550, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17554, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17558, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17547, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17551, 0, 0, 34, 16, 3, height, 0, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17555, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17559, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17548, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17552, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17556, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17560, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17549, 0, 0, 16, 16, 3, height, 16, 16, height);
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17553, 0, 0, 16, 18, 3, height, 0, 16, height);
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17557, 0, 0, 16, 16, 3, height, 0, 0, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17561, 0, 0, 16, 16, 3, height, 16, 0, height);
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17530, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17534, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17538, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17542, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17531, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17535, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17539, 0, 0, 34, 16, 3, height, 0, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17543, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17532, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17536, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17540, 0, 0, 28, 28, 3, height, 4, 4, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17544, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17533, 0, 0, 16, 16, 3, height, 16, 0, height);
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17537, 0, 0, 16, 16, 3, height, 0, 0, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17541, 0, 0, 16, 18, 3, height, 0, 16, height);
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17545, 0, 0, 16, 16, 3, height, 16, 16, height);
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	bolliger_mabillard_track_right_eighth_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	bolliger_mabillard_track_left_eighth_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17578, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17582, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17586, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17590, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17579, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17583, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17587, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17591, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17580, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17584, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17588, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17592, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17581, 0, 0, 16, 16, 3, height, 16, 16, height);
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17585, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17589, 0, 0, 16, 16, 3, height, 0, 0, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17593, 0, 0, 16, 16, 3, height, 16, 0, height);
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17562, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17566, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17570, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17574, 0, 0, 32, 1, 26, height, 0, 27, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17563, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17567, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17571, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17575, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17564, 0, 0, 16, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17568, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17572, 0, 0, 28, 28, 0, height, 4, 4, height + 27);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17576, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17565, 0, 0, 16, 16, 3, height, 16, 0, height);
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17569, 0, 0, 16, 16, 3, height, 0, 0, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17573, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17577, 0, 0, 16, 16, 3, height, 16, 16, height);
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	bolliger_mabillard_track_right_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	bolliger_mabillard_track_left_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_diag_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17861, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17791, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17858, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17788, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17860, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17790, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17859, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17789, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17873, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17803, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17870, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17800, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17872, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17802, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17871, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17801, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17885, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17815, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17882, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17812, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17884, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17814, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 32, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17883, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 36, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 32, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 36, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 32, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17813, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 36, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 32, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 36, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17865, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17795, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17862, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17792, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17864, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17794, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17863, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17793, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17877, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17807, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17874, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17804, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17876, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17806, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17875, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17805, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17881, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17811, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17878, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17808, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17880, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17810, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17879, -16, -16, 16, 16, 3, height, 0, 0, height);
						metal_b_supports_paint_setup(supportType, 0, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17809, -16, -16, 16, 16, 3, height, 0, 0, height);
						metal_b_supports_paint_setup(supportType, 0, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 21, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17869, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17799, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17866, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17796, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17868, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17798, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17867, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17797, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17871, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17801, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17872, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17802, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17870, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17800, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17873, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17803, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17883, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17813, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17884, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17814, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17882, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17812, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 24, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17885, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 28, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 24, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 28, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 24, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17815, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 28, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 24, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 28, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17867, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17797, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17868, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17798, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17866, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17796, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17869, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17799, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			break;
	}

	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_diag_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17879, -16, -16, 16, 16, 3, height, 0, 0, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17809, -16, -16, 16, 16, 3, height, 0, 0, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17880, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17810, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17878, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17808, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17881, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17811, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 17, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17875, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17805, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17876, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17806, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17874, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17804, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17877, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17807, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17863, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17793, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17864, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17794, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17862, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17792, -16, -16, 32, 32, 3, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17865, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17795, -16, -16, 32, 32, 3, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_flat_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17889, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17819, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17886, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17816, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17888, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17818, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17887, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17817, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_60_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17893, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17823, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17890, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17820, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17892, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17822, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17891, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17821, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_flat_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17891, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17821, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17892, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17822, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17890, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17820, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17893, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17823, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_60_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17887, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 3:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17817, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17888, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17818, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 2:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17886, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			} else {
				switch (direction) {
					case 2:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17816, -16, -16, 32, 32, 4, height, -16, -16, height);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17889, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			} else {
				switch (direction) {
					case 0:
						metal_b_supports_paint_setup(supportType, 1, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 1:
						sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17819, -16, -16, 32, 32, 4, height, -16, -16, height);
						metal_b_supports_paint_setup(supportType, 0, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 2:
						metal_b_supports_paint_setup(supportType, 2, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
					case 3:
						metal_b_supports_paint_setup(supportType, 3, 5, height, gTrackColours[SCHEME_SUPPORTS]);
						break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17831, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17828, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17832, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17830, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17829, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17836, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17833, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17835, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17837, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17834, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17834, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17835, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17837, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17833, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17836, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17829, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17830, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17828, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17832, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17831, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17851, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17848, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17852, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17850, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17849, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17856, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17853, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17855, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17857, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17854, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17841, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17838, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17842, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17840, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17839, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17846, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17843, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17845, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17847, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17844, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17844, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17845, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17847, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17843, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17846, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			break;
	}

	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_diag_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17839, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17840, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17838, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17842, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17841, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			break;
	}

	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_diag_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17854, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17855, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17857, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17853, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17856, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17849, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17850, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17848, -16, -16, 32, 32, 3, height, -16, -16, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17852, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_b_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17851, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17827, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17824, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17826, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17825, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_diag_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17825, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17826, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17824, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					metal_a_supports_paint_setup(supportType, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17827, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(supportType, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(supportType, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(supportType, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_bank_to_left_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17725, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17727, 0, 6, 32, 20, 3, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17731, 0, 6, 32, 1, 26, height, 0, 27, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17729, 0, 6, 32, 20, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17723, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17724, 6, 0, 20, 32, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17726, 6, 0, 20, 32, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17728, 6, 0, 20, 32, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17722, 6, 0, 20, 32, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_8);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_bank_to_right_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17714, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17716, 0, 6, 32, 20, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17718, 0, 6, 32, 20, 3, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17730, 0, 6, 32, 1, 26, height, 0, 27, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17720, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17715, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17717, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17719, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17721, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height, TUNNEL_8);
					break;
				case 1:
					paint_util_push_tunnel_left(height, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_quarter_turn_3_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17717, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17719, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17721, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17715, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17716, 6, 0, 20, 32, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17718, 6, 0, 20, 32, 3, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17730, 6, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17720, 6, 0, 20, 32, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17714, 6, 0, 20, 32, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_quarter_turn_3_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17722, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17724, 0, 6, 32, 20, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17726, 0, 6, 32, 20, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17728, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17723, 6, 0, 20, 32, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17725, 6, 0, 20, 32, 3, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17727, 6, 0, 20, 32, 3, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17731, 6, 0, 1, 32, 26, height, 27, 0, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17729, 6, 0, 20, 32, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height, TUNNEL_6);
					break;
				case 1:
					paint_util_push_tunnel_left(height, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
	}
}

void bolliger_mabillard_track_block_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17150, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17151, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

void bolliger_mabillard_track_left_banked_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18025, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18027, 0, 6, 32, 1, 34, height, 0, 27, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18029, 0, 6, 32, 20, 3, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18023, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18024, 6, 0, 20, 32, 3, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18026, 6, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18028, 6, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18022, 6, 0, 20, 32, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 3:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_banked_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18014, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18016, 0, 6, 32, 20, 3, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18018, 0, 6, 32, 1, 34, height, 0, 27, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18020, 0, 6, 32, 20, 3, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18015, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18017, 6, 0, 1, 32, 34, height, 27, 0, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18019, 6, 0, 1, 32, 34, height, 27, 0, height);
					metal_a_supports_paint_setup(supportType, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18021, 6, 0, 20, 32, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 1:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_banked_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_right_banked_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_banked_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bolliger_mabillard_track_left_banked_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_banked_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17978, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17983, 0, 0, 32, 1, 34, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17988, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17993, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17979, 0, 0, 32, 16, 3, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17984, 0, 0, 1, 1, 34, height, 30, 30, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17989, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17994, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17980, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17985, 0, 0, 1, 1, 34, height, 30, 30, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17990, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17995, 0, 0, 16, 16, 3, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17981, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17986, 0, 0, 1, 1, 34, height, 30, 30, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17991, 0, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17996, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17982, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17987, 0, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17992, 0, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17997, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 3:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_banked_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17958, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17963, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17968, 0, 0, 32, 1, 34, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17973, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17959, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17964, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17969, 0, 0, 1, 1, 34, height, 30, 30, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17974, 0, 0, 32, 16, 3, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17960, 0, 0, 16, 16, 3, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17965, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17970, 0, 0, 1, 1, 34, height, 30, 30, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17975, 0, 0, 16, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 4:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17961, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17966, 0, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17971, 0, 0, 1, 1, 34, height, 30, 30, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17976, 0, 0, 16, 32, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17962, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17967, 0, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17972, 0, 0, 1, 32, 34, height, 27, 0, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17977, 0, 0, 20, 32, 3, height, 6, 0, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height + 8, TUNNEL_8);
					break;
				case 1:
					paint_util_push_tunnel_left(height + 8, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_banked_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_right_banked_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_banked_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bolliger_mabillard_track_left_banked_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_25_deg_up_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17922, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17923, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17930, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17924, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17925, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_25_deg_up_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17926, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17927, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17928, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17931, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17929, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_left_banked_25_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17932, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17933, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17940, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17934, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17935, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_right_banked_25_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17936, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17937, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17938, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17941, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17939, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_25_deg_down_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_banked_25_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_25_deg_down_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_banked_25_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_banked_25_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_banked_25_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_25_deg_up_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_banked_flat_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17942, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17943, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17944, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17945, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_right_banked_flat_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17946, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17947, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17948, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17949, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_left_banked_25_deg_up_to_left_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17950, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17951, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17952, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17953, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

void bolliger_mabillard_track_right_banked_25_deg_up_to_right_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17954, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17955, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17956, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17957, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

void bolliger_mabillard_track_left_banked_flat_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_banked_25_deg_up_to_right_banked_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_banked_flat_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_banked_25_deg_up_to_left_banked_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_banked_25_deg_down_to_left_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_banked_flat_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_banked_25_deg_down_to_right_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_banked_flat_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_flat_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17894, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17895, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17902, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17896, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17897, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_flat_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17898, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17899, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17900, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17903, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17901, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

void bolliger_mabillard_track_left_banked_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17904, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17905, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17912, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17906, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17907, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

void bolliger_mabillard_track_right_banked_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17908, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17909, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17910, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17913, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17911, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(supportType, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

void bolliger_mabillard_track_flat_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_banked_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_flat_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_banked_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_banked_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_flat_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_banked_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_flat_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_quarter_turn_1_90_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17998, 0, 0, 2, 20, 63, height, 4, 6, height + 8);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17999, 0, 0, 2, 20, 63, height, 4, 6, height + 8);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18007, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18008, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18001, 0, 0, 2, 20, 63, height, 4, 6, height + 8);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18009, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
			}
			paint_util_set_vertical_tunnel(height + 96);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 96, 0x20);
			break;
		case 1:
			break;
	}
}

void bolliger_mabillard_track_right_quarter_turn_1_90_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18002, 0, 0, 2, 20, 63, height, 4, 6, height + 8);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18010, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18011, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18004, 0, 0, 2, 20, 63, height, 4, 6, height + 8);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18012, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18005, 0, 0, 2, 20, 63, height, 4, 6, height + 8);
					break;
			}
			paint_util_set_vertical_tunnel(height + 96);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 96, 0x20);
			break;
		case 1:
			break;
	}
}

void bolliger_mabillard_track_left_quarter_turn_1_90_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_quarter_turn_1_90_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_quarter_turn_1_90_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_quarter_turn_1_90_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

/* The following track elements used to be specific to the Vertical Roller Coaster */
void bolliger_mabillard_track_flat_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17464, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17465, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17468, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17466, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17469, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17467, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
		}
		metal_a_supports_paint_setup(supportType, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17452, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17453, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17456, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17454, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17457, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17455, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
		}
		metal_a_supports_paint_setup(supportType, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 64, 0x20);
}

void bolliger_mabillard_track_60_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17470, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17471, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17474, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17472, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17475, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17473, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
		}
		metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
	} else {
		switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17458, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17459, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17462, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17460, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17463, 0, 0, 32, 2, 43, height, 0, 4, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17461, 0, 0, 32, 27, 4, height, 0, 2, height);
				break;
		}
		metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_6);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 72, 0x20);
}

void bolliger_mabillard_track_flat_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_60_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_60_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_flat_to_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_brake_for_drop(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17482, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17485, 0, 0, 32, 2, 43, height, 0, 4, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17483, 0, 0, 32, 27, 4, height, 0, 2, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17480, 0, 0, 32, 27, 4, height, 0, 2, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17481, 0, 0, 1, 24, 43, height, 29, 4, height + 2);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17484, 0, 0, 32, 2, 43, height, 0, 4, height);
			break;
	}
	metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 72, 0x20);
}

/* The following track elements used to be specific to the Steel Twister */
void bolliger_mabillard_track_half_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17626, 0, 6, 32, 20, 3, height);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17634, 0, 6, 32, 20, 11, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17633, 0, 6, 32, 20, 9, height);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17641, 0, 6, 32, 20, 7, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17627, 0, 0, 32, 20, 3, height, 0, 6, height);
					metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17635, 0, 14, 3, 20, 63, height, 28, 6, height);
					metal_a_supports_paint_setup(supportType, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17632, 0, 6, 3, 20, 63, height, 28, 6, height);
					metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17640, 0, 6, 32, 20, 3, height);
					metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17628, 16, 0, 2, 16, 119, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17636, 12, 0, 3, 16, 119, height, 12, 0, height);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17631, 10, 16, 4, 12, 119, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17639, 16, 16, 2, 16, 119, height, 15, 6, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17629, 0, 0, 32, 16, 3, height + 32);
					break;
				case 1:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17637, 0, 0, 32, 16, 3, height + 32);
					break;
				case 2:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17630, 0, 16, 32, 12, 3, height + 32);
					break;
				case 3:
					sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17638, 0, 16, 32, 12, 3, height + 32);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_half_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_half_loop_up(rideIndex, 3 - trackSequence, direction, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_corkscrew_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17690, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17693, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17696, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17699, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
			}

			track_paint_util_left_corkscrew_up_supports(direction, height);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17691, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17694, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17697, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17700, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17692, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17695, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17698, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17701, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(supportType, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
				case 2:
					paint_util_push_tunnel_right(height + 8, TUNNEL_6);
					break;
				case 3:
					paint_util_push_tunnel_left(height + 8, TUNNEL_6);
					break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_corkscrew_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17702, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17705, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17708, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17711, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17703, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17706, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17709, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17712, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
					break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17704, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17707, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17710, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17713, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
					break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(supportType, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
				case 0:
					paint_util_push_tunnel_right(height + 8, TUNNEL_6);
					break;
				case 1:
					paint_util_push_tunnel_left(height + 8, TUNNEL_6);
					break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_corkscrew_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_corkscrew_up(rideIndex, 2 - trackSequence, (direction + 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_corkscrew_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_corkscrew_up(rideIndex, 2 - trackSequence, (direction - 1) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_flat_to_60_deg_up_long_base(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18030, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18034, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18038, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18042, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18031, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18035, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18039, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18043, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18032, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18036, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18040, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18044, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18033, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18037, 0, 0, 32, 1, 98, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18041, 0, 0, 32, 1, 98, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18045, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 18, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height + 24, TUNNEL_8);
					break;
				case 2:
					paint_util_push_tunnel_left(height + 24, TUNNEL_8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 80, 0x20);
			break;
	}
}

/** rct2: 0x008AC104 */
void bolliger_mabillard_track_60_deg_up_to_flat_long_base(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18046, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18050, 0, 0, 32, 1, 98, height, 0, 27, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18054, 0, 0, 32, 1, 98, height, 0, 27, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18058, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 80, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18047, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18051, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18055, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18059, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 80, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18048, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18052, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18056, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18060, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18049, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18053, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18057, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18061, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(supportType, 4, 5, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height + 8, TUNNEL_6);
					break;
				case 2:
					paint_util_push_tunnel_left(height + 8, TUNNEL_6);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 40, 0x20);
			break;
	}
}

void bolliger_mabillard_track_flat_to_60_deg_down_long_base(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_flat_to_60_deg_up_long_base(rideIndex, 3 - trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_60_deg_up_to_flat_long_base122(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_60_deg_up_to_flat_long_base(rideIndex, 3 - trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_barrel_roll_up_to_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17642, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17666, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 2, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17645, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17669, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 3, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17648, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17672, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 1, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17651, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17675, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 0, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17643, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17667, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17646, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17670, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17649, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17673, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17652, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17676, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17644, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17668, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17647, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17671, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17650, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17674, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17653, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17677, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
			}
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height, TUNNEL_9);
					break;
				case 2:
					paint_util_push_tunnel_left(height, TUNNEL_9);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_barrel_roll_up_to_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17654, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17678, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 0, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17657, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17681, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 2, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17660, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17684, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 3, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17663, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17687, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					metal_a_supports_paint_setup(supportType, 1, 2, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17655, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17679, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17658, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17682, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17661, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17685, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17664, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17688, 0, 0, 32, 20, 0, height, 0, 6, height + 28);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17656, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17680, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17659, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17683, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17662, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17686, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17665, 0, 0, 32, 20, 3, height, 0, 6, height);
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17689, 0, 0, 32, 20, 0, height, 0, 6, height + 44);
					break;
			}
			switch (direction) {
				case 1:
					paint_util_push_tunnel_right(height, TUNNEL_9);
					break;
				case 2:
					paint_util_push_tunnel_left(height, TUNNEL_9);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_left_barrel_roll_down_to_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_barrel_roll_up_to_down(rideIndex, 2 - trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_right_barrel_roll_down_to_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_barrel_roll_up_to_down(rideIndex, 2 - trackSequence, (direction + 2) & 3, height, mapElement, supportType);
}

void bolliger_mabillard_track_powered_lift(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17476, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17477, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17478, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17479, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
	}
	metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

void bolliger_mabillard_track_left_large_half_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17732, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17739, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17746, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17753, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17733, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17740, 0, 0, 32, 20, 9, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17747, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17754, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17734, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17741, 0, 0, 32, 16, 0, height, 0, 0, height + 70);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17748, 0, 0, 32, 16, 0, height, 0, 16, height + 70);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17755, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 88, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17735, 0, 0, 32, 16, 3, height, 0, 0, height);
					metal_a_supports_paint_setup(supportType, 5, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17742, 0, 0, 32, 16, 0, height, 0, 0, height + 200);
					metal_a_supports_paint_setup(supportType, 6, 22, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17749, 0, 0, 32, 16, 0, height, 0, 16, height + 200);
					metal_a_supports_paint_setup(supportType, 8, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17756, 0, 0, 32, 16, 3, height, 0, 16, height);
					metal_a_supports_paint_setup(supportType, 7, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 224, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17736, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17743, 0, 0, 16, 16, 0, height, 0, 16, height + 110);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17750, 0, 0, 16, 16, 0, height, 0, 0, height + 100);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17757, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 128, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17737, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17744, 0, 0, 32, 16, 0, height, 0, 16, height + 200);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17751, 0, 0, 32, 16, 0, height, 0, 0, height + 200);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17758, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 224, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17738, 0, 0, 32, 16, 0, height, 0, 16, height + 32);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17745, 0, 0, 32, 16, 0, height, 0, 16, height + 32);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17752, 0, 0, 32, 16, 0, height, 0, 0, height + 32);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17759, 0, 0, 32, 16, 0, height, 0, 0, height + 32);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 40, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_large_half_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17781, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17774, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17767, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17760, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17782, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17775, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17768, 0, 0, 32, 20, 9, height, 0, 6, height);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17761, 0, 0, 32, 20, 3, height, 0, 6, height);
					break;
			}
			metal_a_supports_paint_setup(supportType, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17783, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17776, 0, 0, 32, 16, 0, height, 0, 16, height + 70);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17769, 0, 0, 32, 16, 0, height, 0, 0, height + 70);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17762, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 88, 0x20);
			break;
		case 3:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17784, 0, 0, 32, 16, 3, height, 0, 16, height);
					metal_a_supports_paint_setup(supportType, 8, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17777, 0, 0, 32, 16, 0, height, 0, 16, height + 200);
					metal_a_supports_paint_setup(supportType, 7, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17770, 0, 0, 32, 16, 0, height, 0, 0, height + 200);
					metal_a_supports_paint_setup(supportType, 5, 22, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17763, 0, 0, 32, 16, 3, height, 0, 0, height);
					metal_a_supports_paint_setup(supportType, 6, 20, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 224, 0x20);
			break;
		case 4:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17785, 0, 0, 16, 16, 3, height, 16, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17778, 0, 0, 16, 16, 0, height, 0, 0, height + 100);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17771, 0, 0, 16, 16, 0, height, 0, 16, height + 110);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17764, 0, 0, 16, 16, 3, height, 16, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 128, 0x20);
			break;
		case 5:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17786, 0, 0, 32, 16, 3, height, 0, 0, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17779, 0, 0, 32, 16, 0, height, 0, 0, height + 200);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17772, 0, 0, 32, 16, 0, height, 0, 16, height + 200);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17765, 0, 0, 32, 16, 3, height, 0, 16, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 224, 0x20);
			break;
		case 6:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17787, 0, 0, 32, 16, 0, height, 0, 0, height + 32);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17780, 0, 0, 32, 16, 0, height, 0, 0, height + 32);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17773, 0, 0, 32, 16, 0, height, 0, 16, height + 32);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 17766, 0, 0, 32, 16, 0, height, 0, 16, height + 32);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 40, 0x20);
			break;
	}
}

void bolliger_mabillard_track_right_large_half_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_right_large_half_loop_up(rideIndex, 6 - trackSequence, direction, height, mapElement, supportType);
}

void bolliger_mabillard_track_left_large_half_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_left_large_half_loop_up(rideIndex, 6 - trackSequence, direction, height, mapElement, supportType);
}

void bolliger_mabillard_track_90_deg_to_inverted_flat_quarter_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	switch (trackSequence) {
		case 0:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18062, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18065, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18068, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18071, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 88, 0x20);
			break;
		case 1:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18063, 0, 0, 2, 20, 31, height, -8, 6, height);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18066, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18069, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18072, 0, 0, 2, 20, 31, height, -8, 6, height);
					break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 2:
			switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18064, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18067, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18070, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
					break;
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18073, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
					break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 16, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
	}
}

void bolliger_mabillard_track_inverted_flat_to_90_deg_quarter_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement, sint32 supportType)
{
	bolliger_mabillard_track_90_deg_to_inverted_flat_quarter_loop_up(rideIndex, 2 - trackSequence, direction, height, mapElement, supportType);
}
