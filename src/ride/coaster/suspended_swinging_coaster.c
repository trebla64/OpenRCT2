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

/** rct2: 0x008A8958 */
static void suspended_swinging_rc_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25963, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25964, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25961, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25962, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A8AA8, 0x008A8AB8, 0x008A8AC8 */
static void suspended_swinging_rc_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	static const uint32 imageIds[4][3] = {
		{ SPR_STATION_BASE_C_SW_NE, 25963, SPR_STATION_INVERTED_BAR_D_SW_NE },
		{ SPR_STATION_BASE_C_NW_SE, 25964, SPR_STATION_INVERTED_BAR_D_NW_SE },
		{ SPR_STATION_BASE_C_SW_NE, 25963, SPR_STATION_INVERTED_BAR_D_SW_NE },
		{ SPR_STATION_BASE_C_NW_SE, 25964, SPR_STATION_INVERTED_BAR_D_NW_SE },
	};

	sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_MISC], 0, 0, 32, 28, 1, height, 0, 2, height);
	sub_98197C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
	sub_98199C_rotated(direction, imageIds[direction][2] | gTrackColours[SCHEME_SUPPORTS], 0, 6, 32, 20, 3, height + 29, 0, 6, height + 29);
	track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], 0);
	track_paint_util_draw_station_inverted(rideIndex, trackSequence, direction, height, mapElement, STATION_VARIANT_TALL);
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_9);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A8968 */
static void suspended_swinging_rc_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26001, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26002, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26003, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26004, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25973, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25974, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25975, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25976, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
	}

	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_5);
	}
	paint_util_set_general_support_height(height + 72, 0x20);
}

/** rct2: 0x008A8978 */
static void suspended_swinging_rc_track_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25989, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 93);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25990, 0, 0, 32, 2, 81, height + 29, 0, 4, height + 11);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25991, 0, 0, 32, 2, 81, height + 29, 0, 4, height + 11);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25992, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 93);
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 56, TUNNEL_5);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 120, 0x20);
}

/** rct2: 0x008A8988 */
static void suspended_swinging_rc_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25993, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25994, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25995, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25996, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25965, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25966, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25967, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25968, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 6, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 8, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 7, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 5, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
	}

	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_5);
	}
	paint_util_set_general_support_height(height + 64, 0x20);
}

/** rct2: 0x008A8998 */
static void suspended_swinging_rc_track_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25977, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25981, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25978, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25982, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25979, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25980, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_5);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 88, 0x20);
}

/** rct2: 0x008A89A8 */
static void suspended_swinging_rc_track_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25983, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25987, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26090, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25988, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25985, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25986, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25983, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25987, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25984, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25988, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25985, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25986, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 6, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 8, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 7, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 5, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
	}

	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_5);
	}
	paint_util_set_general_support_height(height + 88, 0x20);
}

/** rct2: 0x008A89B8 */
static void suspended_swinging_rc_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25997, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25998, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25999, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26000, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25969, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25970, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25971, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 25972, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
	}

	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_3);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_13);
	}
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x008A89C8 */
static void suspended_swinging_rc_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	suspended_swinging_rc_track_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A89D8 */
static void suspended_swinging_rc_track_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	suspended_swinging_rc_track_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A89E8 */
static void suspended_swinging_rc_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	suspended_swinging_rc_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A89F8 */
static void suspended_swinging_rc_track_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	suspended_swinging_rc_track_60_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A8A08 */
static void suspended_swinging_rc_track_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	suspended_swinging_rc_track_25_deg_up_to_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A8A18 */
static void suspended_swinging_rc_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	suspended_swinging_rc_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A8A28 */
static void suspended_swinging_rc_track_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26014, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26019, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26024, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26009, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26013, 0, 0, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26018, 0, 0, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26023, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26008, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26012, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26017, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26022, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26007, 0, 0, 16, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26011, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26016, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26021, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26006, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26010, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26015, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26020, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26005, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8A38 */
static void suspended_swinging_rc_track_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	suspended_swinging_rc_track_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A8A48 */
static void suspended_swinging_rc_track_left_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26097, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26102, 0, 6, 32, 20, 11, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26107, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26112, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26098, 0, 0, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26103, 0, 0, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26108, 0, 16, 32, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26113, 0, 16, 32, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26099, 0, 16, 16, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26104, 16, 16, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26109, 16, 0, 16, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26114, 0, 0, 16, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 80, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26100, 16, 0, 16, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26105, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26110, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26115, 16, 0, 16, 32, 3, height + 29, 16, 0, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26101, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26106, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26111, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26116, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height + 8, TUNNEL_5);
			break;
		case 3:
			paint_util_push_tunnel_left(height + 8, TUNNEL_5);
			break;
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8A58 */
static void suspended_swinging_rc_track_right_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26077, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26082, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26087, 0, 6, 32, 20, 11, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26092, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26078, 0, 16, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26083, 0, 16, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26088, 0, 0, 32, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26093, 0, 0, 32, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26079, 0, 0, 16, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26084, 16, 0, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26089, 16, 16, 16, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26094, 0, 16, 16, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 80, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26080, 16, 0, 16, 32, 3, height + 29, 16, 0, height + 37);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26085, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26090, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26095, 16, 0, 16, 32, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26081, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26086, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26091, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26096, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 8, TUNNEL_5);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 8, TUNNEL_5);
			break;
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8A68 */
static void suspended_swinging_rc_track_left_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	suspended_swinging_rc_track_right_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A8A78 */
static void suspended_swinging_rc_track_right_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	suspended_swinging_rc_track_left_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A8A88 */
static void suspended_swinging_rc_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26139, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26146, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26142, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26143, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26140, 0, 0, 32, 26, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26145, 0, 0, 32, 26, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26141, 0, 6, 32, 26, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26144, 0, 6, 32, 26, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26141, 0, 6, 32, 26, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26144, 0, 6, 32, 26, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26140, 0, 0, 32, 26, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26145, 0, 0, 32, 26, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 2:
			metal_a_supports_paint_setup(0, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26142, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26143, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26139, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26146, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 2:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8A98 */
static void suspended_swinging_rc_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26135, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26150, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26138, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26147, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26136, 0, 6, 32, 26, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26149, 0, 6, 32, 26, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26137, 0, 0, 32, 26, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26148, 0, 0, 32, 26, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26137, 0, 0, 32, 26, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26148, 0, 0, 32, 26, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26136, 0, 6, 32, 26, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26149, 0, 6, 32, 26, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 2:
			metal_a_supports_paint_setup(0, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26138, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26147, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26135, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26150, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 2:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8AD8 */
static void suspended_swinging_rc_track_left_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26070, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26073, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26076, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26067, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26069, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26072, 0, 0, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26075, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26066, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26068, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26071, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26074, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26065, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8AE8 */
static void suspended_swinging_rc_track_right_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	suspended_swinging_rc_track_left_quarter_turn_3(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A8AF8 */
static void suspended_swinging_rc_track_left_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26130, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26132, 0, 6, 32, 20, 11, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26134, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26128, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26129, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26131, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26133, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26127, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height + 8, TUNNEL_5);
			break;
		case 3:
			paint_util_push_tunnel_left(height + 8, TUNNEL_5);
			break;
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8B08 */
static void suspended_swinging_rc_track_right_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26119, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26121, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26123, 0, 6, 32, 20, 11, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26125, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26120, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26122, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26124, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26126, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 8, TUNNEL_5);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 8, TUNNEL_5);
			break;
		}
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8B18 */
static void suspended_swinging_rc_track_left_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	suspended_swinging_rc_track_right_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A8B28 */
static void suspended_swinging_rc_track_right_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	suspended_swinging_rc_track_left_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A8B38 */
static void suspended_swinging_rc_track_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26117, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26118, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A8B48 */
static void suspended_swinging_rc_track_left_quarter_helix_large_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26054, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26059, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26064, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26049, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26053, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26058, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26063, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26048, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26052, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26057, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26062, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26047, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26051, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26056, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26061, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26046, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26050, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26055, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26060, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26045, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height + 16, TUNNEL_3);
			break;
		case 3:
			paint_util_push_tunnel_left(height + 16, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8B58 */
static void suspended_swinging_rc_track_right_quarter_helix_large_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26025, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26030, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26035, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26040, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26026, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26031, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26036, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26041, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26027, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26032, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26037, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26042, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26028, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26033, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26038, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26043, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26029, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26034, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26039, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26044, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 16, TUNNEL_3);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 16, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8B68 */
static void suspended_swinging_rc_track_left_quarter_helix_large_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26034, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26039, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26044, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26029, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 16, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26033, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26038, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26043, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26028, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26032, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26037, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26042, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26027, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26031, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26036, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26041, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26026, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26030, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26035, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26040, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26025, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 3:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8B78 */
static void suspended_swinging_rc_track_right_quarter_helix_large_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26045, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26050, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26055, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26060, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 16, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26046, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26051, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26056, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26061, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26047, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26052, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26057, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26062, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26048, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26053, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26058, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26063, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26049, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26054, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26059, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26064, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 1:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8B88 */
static void suspended_swinging_rc_track_left_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26167, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26171, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26175, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26179, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26168, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26172, 0, 0, 34, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26176, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26180, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26169, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26173, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26177, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26181, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 4:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26170, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26174, 0, 0, 16, 18, 3, height + 29, 0, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26178, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26182, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8B98 */
static void suspended_swinging_rc_track_right_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26151, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26155, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26159, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26163, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26152, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26156, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26160, 0, 0, 34, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26164, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26153, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26157, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26161, 0, 0, 28, 28, 3, height + 29, 4, 4, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26165, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 4:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26154, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26158, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26162, 0, 0, 16, 18, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26166, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8BA8 */
static void suspended_swinging_rc_track_left_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	suspended_swinging_rc_track_right_eighth_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A8BB8 */
static void suspended_swinging_rc_track_right_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	suspended_swinging_rc_track_left_eighth_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

/** rct2: 0x008A8BC8 */
static void suspended_swinging_rc_track_diag_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26214, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26186, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26211, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26183, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26213, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26185, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26212, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26184, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A8BF8 */
static void suspended_swinging_rc_track_diag_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26226, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26198, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26223, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26195, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26225, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26197, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26224, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26196, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 1, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A8C58 */
static void suspended_swinging_rc_track_diag_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26210, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26207, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26209, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26208, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(0, 1, 32, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(0, 0, 36, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(0, 2, 32, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(0, 3, 36, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	}
}

/** rct2: 0x008A8BD8 */
static void suspended_swinging_rc_track_diag_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26218, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26190, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26215, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26187, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26217, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26189, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26216, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26188, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A8C38 */
static void suspended_swinging_rc_track_diag_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26202, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26199, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26201, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26200, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(0, 1, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(0, 0, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(0, 2, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(0, 3, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8C48 */
static void suspended_swinging_rc_track_diag_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26206, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26203, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26205, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26204, -16, -16, 16, 16, 3, height + 29, 0, 0, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(0, 1, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(0, 0, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(0, 2, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(0, 3, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8BE8 */
static void suspended_swinging_rc_track_diag_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26222, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26194, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26219, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26191, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26221, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26193, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26220, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26192, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(0, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A8C28 */
static void suspended_swinging_rc_track_diag_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26224, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26196, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26225, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26197, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26223, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26195, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26226, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26198, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 1, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A8C88 */
static void suspended_swinging_rc_track_diag_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26208, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26209, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26207, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26210, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	}
}

/** rct2: 0x008A8C08 */
static void suspended_swinging_rc_track_diag_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26220, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26192, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 1:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26221, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26193, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		break;
	case 2:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26219, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26191, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26222, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26194, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		break;
	}

	paint_util_set_general_support_height(height + 72, 0x20);
}

/** rct2: 0x008A8C68 */
static void suspended_swinging_rc_track_diag_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26204, -16, -16, 16, 16, 3, height + 29, 0, 0, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26205, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26203, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26206, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(0, 1, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(0, 0, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(0, 2, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(0, 3, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8C78 */
static void suspended_swinging_rc_track_diag_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26200, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26201, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26199, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26202, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(0, 1, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(0, 0, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(0, 2, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(0, 3, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A8C18 */
static void suspended_swinging_rc_track_diag_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26216, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26188, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26217, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26189, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26215, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26187, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26218, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26190, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(0, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(0, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(0, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(0, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A8B38 */
static void suspended_swinging_rc_track_block_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26117, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26118, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(0, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

TRACK_PAINT_FUNCTION get_track_paint_function_suspended_swinging_rc(int trackType, int direction)
{
	switch (trackType) {
	case TRACK_ELEM_FLAT:
		return suspended_swinging_rc_track_flat;
	case TRACK_ELEM_END_STATION:
	case TRACK_ELEM_BEGIN_STATION:
	case TRACK_ELEM_MIDDLE_STATION:
		return suspended_swinging_rc_track_station;
	case TRACK_ELEM_25_DEG_UP:
		return suspended_swinging_rc_track_25_deg_up;
	case TRACK_ELEM_60_DEG_UP:
		return suspended_swinging_rc_track_60_deg_up;
	case TRACK_ELEM_FLAT_TO_25_DEG_UP:
		return suspended_swinging_rc_track_flat_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_60_DEG_UP:
		return suspended_swinging_rc_track_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_60_DEG_UP_TO_25_DEG_UP:
		return suspended_swinging_rc_track_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_FLAT:
		return suspended_swinging_rc_track_25_deg_up_to_flat;
	case TRACK_ELEM_25_DEG_DOWN:
		return suspended_swinging_rc_track_25_deg_down;
	case TRACK_ELEM_60_DEG_DOWN:
		return suspended_swinging_rc_track_60_deg_down;
	case TRACK_ELEM_FLAT_TO_25_DEG_DOWN:
		return suspended_swinging_rc_track_flat_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_60_DEG_DOWN:
		return suspended_swinging_rc_track_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_60_DEG_DOWN_TO_25_DEG_DOWN:
		return suspended_swinging_rc_track_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_FLAT:
		return suspended_swinging_rc_track_25_deg_down_to_flat;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES:
		return suspended_swinging_rc_track_left_quarter_turn_5;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES:
		return suspended_swinging_rc_track_right_quarter_turn_5;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return suspended_swinging_rc_track_left_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return suspended_swinging_rc_track_right_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return suspended_swinging_rc_track_left_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return suspended_swinging_rc_track_right_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_S_BEND_LEFT:
		return suspended_swinging_rc_track_s_bend_left;
	case TRACK_ELEM_S_BEND_RIGHT:
		return suspended_swinging_rc_track_s_bend_right;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
		return suspended_swinging_rc_track_left_quarter_turn_3;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
		return suspended_swinging_rc_track_right_quarter_turn_3;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return suspended_swinging_rc_track_left_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return suspended_swinging_rc_track_right_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return suspended_swinging_rc_track_left_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return suspended_swinging_rc_track_right_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_BRAKES:
		return suspended_swinging_rc_track_brakes;
	case TRACK_ELEM_LEFT_QUARTER_HELIX_LARGE_UP:
		return suspended_swinging_rc_track_left_quarter_helix_large_up;
	case TRACK_ELEM_RIGHT_QUARTER_HELIX_LARGE_UP:
		return suspended_swinging_rc_track_right_quarter_helix_large_up;
	case TRACK_ELEM_LEFT_QUARTER_HELIX_LARGE_DOWN:
		return suspended_swinging_rc_track_left_quarter_helix_large_down;
	case TRACK_ELEM_RIGHT_QUARTER_HELIX_LARGE_DOWN:
		return suspended_swinging_rc_track_right_quarter_helix_large_down;
	case TRACK_ELEM_LEFT_EIGHTH_TO_DIAG:
		return suspended_swinging_rc_track_left_eighth_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_DIAG:
		return suspended_swinging_rc_track_right_eighth_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_TO_ORTHOGONAL:
		return suspended_swinging_rc_track_left_eighth_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_ORTHOGONAL:
		return suspended_swinging_rc_track_right_eighth_to_orthogonal;
	case TRACK_ELEM_DIAG_FLAT:
		return suspended_swinging_rc_track_diag_flat;
	case TRACK_ELEM_DIAG_25_DEG_UP:
		return suspended_swinging_rc_track_diag_25_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP:
		return suspended_swinging_rc_track_diag_60_deg_up;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_UP:
		return suspended_swinging_rc_track_diag_flat_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_60_DEG_UP:
		return suspended_swinging_rc_track_diag_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP_TO_25_DEG_UP:
		return suspended_swinging_rc_track_diag_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_FLAT:
		return suspended_swinging_rc_track_diag_25_deg_up_to_flat;
	case TRACK_ELEM_DIAG_25_DEG_DOWN:
		return suspended_swinging_rc_track_diag_25_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN:
		return suspended_swinging_rc_track_diag_60_deg_down;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_DOWN:
		return suspended_swinging_rc_track_diag_flat_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_60_DEG_DOWN:
		return suspended_swinging_rc_track_diag_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN_TO_25_DEG_DOWN:
		return suspended_swinging_rc_track_diag_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_FLAT:
		return suspended_swinging_rc_track_diag_25_deg_down_to_flat;
	case TRACK_ELEM_BLOCK_BRAKES:
		return suspended_swinging_rc_track_block_brakes;
	}
	return NULL;
}
