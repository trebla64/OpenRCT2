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

/** rct2: 0x006FE5B4 */
static void bobsleigh_rc_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14576, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14578, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14577, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14579, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14572, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14574, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14573, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14575, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

static void bobsleigh_rc_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	static const uint32 imageIds[4][2] = {
		{ 14580, SPR_STATION_BASE_B_SW_NE },
		{ 14581, SPR_STATION_BASE_B_NW_SE },
		{ 14580, SPR_STATION_BASE_B_SW_NE },
		{ 14581, SPR_STATION_BASE_B_NW_SE },
	};

	sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 1, height, 0, 6, height + 3);
	sub_98196C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_MISC], 0, 0, 32, 32, 1, height);
	track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], 0);
	track_paint_util_draw_station(rideIndex, trackSequence, direction, height, mapElement);
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x006FE5C4 */
static void bobsleigh_rc_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14634, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14638, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14635, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14639, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14636, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14640, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14637, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14641, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14610, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14614, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14611, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14615, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14612, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14616, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14613, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14617, 0, 0, 32, 1, 50, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_2);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x006FE5D4 */
static void bobsleigh_rc_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14618, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14622, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14619, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14623, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14620, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14624, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14621, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14625, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14594, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14598, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14595, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14599, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14596, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14600, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14597, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14601, 0, 0, 32, 1, 42, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x006FE5E4 */
static void bobsleigh_rc_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14626, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14630, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14627, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14631, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14628, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14632, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14629, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14633, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14602, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14606, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14603, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14607, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14604, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14608, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14605, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14609, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x006FE5F4 */
static void bobsleigh_rc_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE604 */
static void bobsleigh_rc_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE614 */
static void bobsleigh_rc_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE624 */
static void bobsleigh_rc_track_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14707, 0, 2, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14727, 0, 2, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14712, 0, 2, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14732, 0, 2, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14717, 0, 2, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14737, 0, 2, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14702, 0, 2, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14722, 0, 2, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14706, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14726, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14711, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14731, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14716, 0, 16, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14736, 0, 16, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14701, 0, 16, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14721, 0, 16, 32, 16, 0, height, 0, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14705, 0, 16, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14725, 0, 16, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14710, 16, 16, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14730, 16, 16, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14715, 16, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14735, 16, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14700, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14720, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14704, 16, 0, 16, 34, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14724, 16, 0, 16, 34, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14709, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14729, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14714, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14734, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14699, 16, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14719, 16, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14703, 2, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14723, 2, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14708, 2, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14728, 2, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14713, 2, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14733, 2, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14698, 2, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14718, 2, 0, 30, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE634 */
static void bobsleigh_rc_track_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bobsleigh_rc_track_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x006FE644 */
static void bobsleigh_rc_track_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14642, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14646, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14643, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14647, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14644, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14648, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14645, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14649, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x006FE654 */
static void bobsleigh_rc_track_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14650, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14654, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14651, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14655, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14652, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14656, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14653, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14657, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x006FE664 */
static void bobsleigh_rc_track_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14652, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14656, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14653, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14657, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14650, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14654, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14651, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14655, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x006FE674 */
static void bobsleigh_rc_track_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14644, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14648, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14645, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14649, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14642, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14646, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14643, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14647, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x006FE684 */
static void bobsleigh_rc_track_banked_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14747, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14767, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14752, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14772, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14757, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14777, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14742, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14762, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14746, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14766, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14751, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14771, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14756, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14776, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14741, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14761, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14745, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14765, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14750, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14770, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14755, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14775, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14740, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14760, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14744, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14764, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14749, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14769, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14754, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14774, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14739, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14759, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14743, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14763, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14748, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14768, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14753, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14773, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14738, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14758, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE694 */
static void bobsleigh_rc_track_banked_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bobsleigh_rc_track_banked_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x006FE6A4 */
static void bobsleigh_rc_track_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14674, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14678, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14675, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14679, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14676, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14680, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14677, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14681, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x006FE6B4 */
static void bobsleigh_rc_track_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14682, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14686, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14683, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14687, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14684, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14688, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14685, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14689, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x006FE6C4 */
static void bobsleigh_rc_track_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14658, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14662, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14659, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14663, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14660, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14664, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14661, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14665, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x006FE6D4 */
static void bobsleigh_rc_track_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14666, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14670, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14667, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14671, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14668, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14672, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14669, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14673, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x006FE6E4 */
static void bobsleigh_rc_track_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_25_deg_up_to_right_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE6F4 */
static void bobsleigh_rc_track_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_25_deg_up_to_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE704 */
static void bobsleigh_rc_track_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_right_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE714 */
static void bobsleigh_rc_track_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_left_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE724 */
static void bobsleigh_rc_track_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14690, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14694, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14691, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14695, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14692, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14696, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14693, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14697, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x006FE734 */
static void bobsleigh_rc_track_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	bobsleigh_rc_track_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x006FE744 */
static void bobsleigh_rc_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14826, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14842, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14830, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14846, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14829, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14845, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14833, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14849, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14827, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14843, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			metal_a_supports_paint_setup(0, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14831, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14847, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			metal_a_supports_paint_setup(0, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14828, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14844, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14832, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14848, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14828, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14844, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14832, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14848, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14827, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14843, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			metal_a_supports_paint_setup(0, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14831, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14847, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			metal_a_supports_paint_setup(0, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14829, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14845, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14833, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14849, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14826, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14842, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14830, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14846, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 2:
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE754 */
static void bobsleigh_rc_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14834, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14850, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14838, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14854, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14837, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14853, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14841, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14857, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14835, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14851, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			metal_a_supports_paint_setup(0, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14839, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14855, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			metal_a_supports_paint_setup(0, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14836, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14852, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14840, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14856, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14836, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14852, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14840, 0, 0, 32, 26, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14856, 0, 0, 32, 26, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14835, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14851, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			metal_a_supports_paint_setup(0, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14839, 0, 0, 32, 26, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14855, 0, 0, 32, 26, 0, height, 0, 6, height + 27);
			metal_a_supports_paint_setup(0, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14837, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14853, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14841, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14857, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14834, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14850, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14838, 0, 0, 32, 27, 2, height, 0, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14854, 0, 0, 32, 27, 0, height, 0, 2, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 2:
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE794 */
static void bobsleigh_rc_track_left_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14783, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14795, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14786, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14798, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14789, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14801, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14780, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14792, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14782, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14794, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14785, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14797, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14788, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14800, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14779, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14791, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14781, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14793, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14784, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14796, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14787, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14799, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14778, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14790, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE7A4 */
static void bobsleigh_rc_track_right_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bobsleigh_rc_track_left_quarter_turn_3(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x006FE7B4 */
static void bobsleigh_rc_track_left_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14807, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14819, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14810, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14822, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14813, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14825, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14804, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14816, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14806, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14818, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14809, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14821, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14812, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14824, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14803, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14815, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14805, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14817, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14808, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14820, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14811, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14823, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14802, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14814, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE7C4 */
static void bobsleigh_rc_track_right_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bobsleigh_rc_track_left_quarter_turn_3_bank(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x006FE7D4 */
static void bobsleigh_rc_track_left_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14887, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14899, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14890, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14902, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14893, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14905, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14884, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14896, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14886, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14898, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14889, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14901, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14892, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14904, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14883, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14895, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14885, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14897, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14888, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14900, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14891, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14903, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14882, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14894, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height + 8, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height + 8, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 4:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14884, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14896, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14887, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14899, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14890, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14902, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14893, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14905, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 1:
			paint_util_push_tunnel_left(height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14883, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14895, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14886, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14898, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14889, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14901, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14892, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14904, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14882, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14894, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14885, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14897, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14888, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14900, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14891, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14903, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE7E4 */
static void bobsleigh_rc_track_right_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14858, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14870, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14861, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14873, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14864, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14876, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14867, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14879, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14859, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14871, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14862, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14874, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14865, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14877, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14868, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14880, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14860, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14872, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14863, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14875, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14866, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14878, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14869, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14881, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 8, TUNNEL_0);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 8, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 4:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14861, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14873, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14864, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14876, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14867, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14879, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14858, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14870, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14862, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14874, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14865, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14877, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14868, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14880, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14859, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14871, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14863, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14875, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14866, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14878, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14869, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14881, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14860, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14872, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE7F4 */
static void bobsleigh_rc_track_left_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bobsleigh_rc_track_right_half_banked_helix_up_small(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x006FE804 */
static void bobsleigh_rc_track_right_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	bobsleigh_rc_track_left_half_banked_helix_up_small(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x006FE814 */
static void bobsleigh_rc_track_left_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14955, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14975, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14960, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14980, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14965, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14985, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14950, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14970, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14954, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14974, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14959, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14979, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14964, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14984, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14949, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14969, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14953, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14973, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14958, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14978, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14963, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14983, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14948, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14968, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14952, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14972, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14957, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14977, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14962, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14982, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14947, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14967, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14951, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14971, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14956, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14976, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14961, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14981, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14946, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14966, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height + 8, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height + 8, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14950, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14970, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14955, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14975, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14960, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14980, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14965, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14985, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 1:
			paint_util_push_tunnel_left(height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14949, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14969, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14954, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14974, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14959, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14979, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14964, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14984, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 10:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14948, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14968, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14953, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14973, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14958, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14978, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14963, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14983, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14947, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14967, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14952, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14972, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14957, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14977, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14962, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14982, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 13:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14946, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14966, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14951, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14971, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14956, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14976, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14961, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14981, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE824 */
static void bobsleigh_rc_track_right_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14906, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14926, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14911, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14931, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14916, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14936, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14921, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14941, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14907, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14927, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14912, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14932, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14917, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14937, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14922, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14942, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14908, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14928, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14913, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14933, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14918, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14938, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14923, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14943, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14909, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14929, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14914, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14934, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14919, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14939, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14924, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14944, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14910, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14930, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14915, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14935, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14920, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14940, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14925, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14945, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 8, TUNNEL_0);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 8, TUNNEL_0);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14911, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14931, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14916, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14936, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14921, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14941, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14906, 0, 0, 20, 32, 2, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14926, 0, 0, 20, 32, 0, height, 6, 0, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_0);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_0);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14912, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14932, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14917, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14937, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14922, 0, 0, 16, 32, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14942, 0, 0, 16, 32, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14907, 0, 0, 16, 32, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14927, 0, 0, 16, 32, 0, height, 16, 0, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 10:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14913, 0, 0, 16, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14933, 0, 0, 16, 16, 0, height, 0, 16, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14918, 0, 0, 16, 16, 2, height, 16, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14938, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14923, 0, 0, 16, 16, 2, height, 16, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14943, 0, 0, 16, 16, 0, height, 16, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14908, 0, 0, 16, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14928, 0, 0, 16, 16, 0, height, 0, 0, height + 27);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14914, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14934, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14919, 0, 0, 32, 16, 2, height, 0, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14939, 0, 0, 32, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14924, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14944, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14909, 0, 0, 32, 16, 2, height, 0, 16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14929, 0, 0, 32, 16, 0, height, 0, 16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 13:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14915, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14935, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14920, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14940, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14925, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14945, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14910, 0, 0, 32, 20, 2, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14930, 0, 0, 32, 20, 0, height, 0, 6, height + 27);
			break;
		}
		metal_a_supports_paint_setup(0, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x006FE834 */
static void bobsleigh_rc_track_left_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bobsleigh_rc_track_right_half_banked_helix_up_large(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x006FE844 */
static void bobsleigh_rc_track_right_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	bobsleigh_rc_track_left_half_banked_helix_up_large(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x006FE854 */
static void bobsleigh_rc_track_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14582, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14584, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14583, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14585, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x006FE864 */
static void bobsleigh_rc_track_block_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14586, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14590, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14587, 0, 0, 32, 20, 2, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 14591, 0, 0, 32, 1, 26, height, 0, 27, height);
		break;
	}
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

TRACK_PAINT_FUNCTION get_track_paint_function_bobsleigh_rc(int trackType, int direction)
{
	switch (trackType) {
	case TRACK_ELEM_FLAT:
		return bobsleigh_rc_track_flat;
	case TRACK_ELEM_END_STATION:
	case TRACK_ELEM_BEGIN_STATION:
	case TRACK_ELEM_MIDDLE_STATION:
		return bobsleigh_rc_track_station;
	case TRACK_ELEM_25_DEG_UP:
		return bobsleigh_rc_track_25_deg_up;
	case TRACK_ELEM_FLAT_TO_25_DEG_UP:
		return bobsleigh_rc_track_flat_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_FLAT:
		return bobsleigh_rc_track_25_deg_up_to_flat;
	case TRACK_ELEM_25_DEG_DOWN:
		return bobsleigh_rc_track_25_deg_down;
	case TRACK_ELEM_FLAT_TO_25_DEG_DOWN:
		return bobsleigh_rc_track_flat_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_FLAT:
		return bobsleigh_rc_track_25_deg_down_to_flat;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES:
		return bobsleigh_rc_track_left_quarter_turn_5;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES:
		return bobsleigh_rc_track_right_quarter_turn_5;
	case TRACK_ELEM_FLAT_TO_LEFT_BANK:
		return bobsleigh_rc_track_flat_to_left_bank;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANK:
		return bobsleigh_rc_track_flat_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_FLAT:
		return bobsleigh_rc_track_left_bank_to_flat;
	case TRACK_ELEM_RIGHT_BANK_TO_FLAT:
		return bobsleigh_rc_track_right_bank_to_flat;
	case TRACK_ELEM_BANKED_LEFT_QUARTER_TURN_5_TILES:
		return bobsleigh_rc_track_banked_left_quarter_turn_5;
	case TRACK_ELEM_BANKED_RIGHT_QUARTER_TURN_5_TILES:
		return bobsleigh_rc_track_banked_right_quarter_turn_5;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_UP:
		return bobsleigh_rc_track_left_bank_to_25_deg_up;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_UP:
		return bobsleigh_rc_track_right_bank_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_LEFT_BANK:
		return bobsleigh_rc_track_25_deg_up_to_left_bank;
	case TRACK_ELEM_25_DEG_UP_TO_RIGHT_BANK:
		return bobsleigh_rc_track_25_deg_up_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_DOWN:
		return bobsleigh_rc_track_left_bank_to_25_deg_down;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_DOWN:
		return bobsleigh_rc_track_right_bank_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_LEFT_BANK:
		return bobsleigh_rc_track_25_deg_down_to_left_bank;
	case TRACK_ELEM_25_DEG_DOWN_TO_RIGHT_BANK:
		return bobsleigh_rc_track_25_deg_down_to_right_bank;
	case TRACK_ELEM_LEFT_BANK:
		return bobsleigh_rc_track_left_bank;
	case TRACK_ELEM_RIGHT_BANK:
		return bobsleigh_rc_track_right_bank;
	case TRACK_ELEM_S_BEND_LEFT:
		return bobsleigh_rc_track_s_bend_left;
	case TRACK_ELEM_S_BEND_RIGHT:
		return bobsleigh_rc_track_s_bend_right;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
		return bobsleigh_rc_track_left_quarter_turn_3;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
		return bobsleigh_rc_track_right_quarter_turn_3;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_BANK:
		return bobsleigh_rc_track_left_quarter_turn_3_bank;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_BANK:
		return bobsleigh_rc_track_right_quarter_turn_3_bank;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_SMALL:
		return bobsleigh_rc_track_left_half_banked_helix_up_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_SMALL:
		return bobsleigh_rc_track_right_half_banked_helix_up_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_SMALL:
		return bobsleigh_rc_track_left_half_banked_helix_down_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_SMALL:
		return bobsleigh_rc_track_right_half_banked_helix_down_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_LARGE:
		return bobsleigh_rc_track_left_half_banked_helix_up_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_LARGE:
		return bobsleigh_rc_track_right_half_banked_helix_up_large;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_LARGE:
		return bobsleigh_rc_track_left_half_banked_helix_down_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_LARGE:
		return bobsleigh_rc_track_right_half_banked_helix_down_large;
	case TRACK_ELEM_BRAKES:
		return bobsleigh_rc_track_brakes;
	case TRACK_ELEM_BLOCK_BRAKES:
		return bobsleigh_rc_track_block_brakes;
	}
	return NULL;
}
