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

/** rct2: 0x008A4ABC */
static void mini_rc_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19044, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19045, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19046, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19047, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18738, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18739, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

static void mini_rc_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	static const uint32 imageIds[4][3] = {
		{ 18746, 18742, SPR_STATION_BASE_A_SW_NE },
		{ 18747, 18743, SPR_STATION_BASE_A_NW_SE },
		{ 18746, 18742, SPR_STATION_BASE_A_SW_NE },
		{ 18747, 18743, SPR_STATION_BASE_A_NW_SE },
	};

	if (mapElement->properties.track.type == TRACK_ELEM_END_STATION) {
		sub_98197C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 1, height, 0, 6, height + 3);
	} else {
		sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 1, height, 0, 6, height + 3);
	}
	sub_98196C_rotated(direction, imageIds[direction][2] | gTrackColours[SCHEME_MISC], 0, 0, 32, 32, 1, height);
	track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], 0);
	track_paint_util_draw_station_2(rideIndex, trackSequence, direction, height, mapElement, 9, 11);
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A4ACC */
static void mini_rc_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19056, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19057, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19058, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19059, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18796, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18797, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18798, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18799, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
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

/** rct2: 0x008A4ADC */
static void mini_rc_track_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18812, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 38, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18813, 0, 0, 32, 1, 98, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 38, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18814, 0, 0, 32, 1, 98, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 38, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18815, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 38, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 56, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

/** rct2: 0x008A4AEC */
static void mini_rc_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19048, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19049, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19050, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19051, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18788, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18789, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18790, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18791, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
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

/** rct2: 0x008A4AFC */
static void mini_rc_track_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18800, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 18, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18801, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18804, 0, 0, 32, 1, 66, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 18, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18802, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18805, 0, 0, 32, 1, 66, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 18, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18803, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 18, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 72, 0x20);
}

/** rct2: 0x008A4B0C */
static void mini_rc_track_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18806, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 26, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18807, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18810, 0, 0, 32, 1, 66, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 26, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18808, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18811, 0, 0, 32, 1, 66, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 26, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18809, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 26, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 72, 0x20);
}

/** rct2: 0x008A4B1C */
static void mini_rc_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19052, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19053, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19054, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19055, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18792, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18793, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18794, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18795, 0, 0, 32, 20, 3, height, 0, 6, height);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
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

/** rct2: 0x008A4B2C */
static void mini_rc_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4B3C */
static void mini_rc_track_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4B4C */
static void mini_rc_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4B5C */
static void mini_rc_track_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_60_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4B6C */
static void mini_rc_track_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_to_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4B7C */
static void mini_rc_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4B8C */
static void mini_rc_track_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18851, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18856, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18861, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18846, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18850, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18855, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18860, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18845, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18849, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18854, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18859, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18844, 0, 0, 16, 16, 3, height, 0, 0, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18848, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18853, 0, 0, 16, 32, 3, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18858, 0, 0, 16, 32, 3, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18843, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18847, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18852, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18857, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18842, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4B9C */
static void mini_rc_track_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4BAC */
static void mini_rc_track_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18748, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18756, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18749, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18757, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18750, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18751, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A4BBC */
static void mini_rc_track_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18752, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18753, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18754, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18758, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18755, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18759, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A4BCC */
static void mini_rc_track_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18754, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18758, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18755, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18759, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18752, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18753, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A4BDC */
static void mini_rc_track_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18750, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18751, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18748, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18756, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18749, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18757, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A4BEC */
static void mini_rc_track_banked_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18871, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18882, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18876, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18881, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18866, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18870, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18875, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18880, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18865, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18869, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18874, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18879, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18864, 0, 0, 16, 16, 3, height, 0, 0, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18868, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18873, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18878, 0, 0, 16, 32, 3, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18863, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18867, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18872, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18877, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18883, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18862, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4BFC */
static void mini_rc_track_banked_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_banked_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4C0C */
static void mini_rc_track_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18760, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18764, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18761, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18765, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18762, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18763, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A4C1C */
static void mini_rc_track_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18766, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18767, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18768, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18770, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18769, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18771, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A4C2C */
static void mini_rc_track_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18772, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18776, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18773, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18777, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18774, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18775, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x008A4C3C */
static void mini_rc_track_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18778, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18779, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18780, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18782, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18781, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18783, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x008A4C4C */
static void mini_rc_track_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_to_right_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4C5C */
static void mini_rc_track_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_to_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4C6C */
static void mini_rc_track_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_right_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4C7C */
static void mini_rc_track_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_left_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4C8C */
static void mini_rc_track_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18784, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18785, 0, 0, 32, 1, 26, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18786, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18787, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A4C9C */
static void mini_rc_track_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4CAC */
static void mini_rc_track_left_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18936, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18941, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18946, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18951, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18937, 0, 0, 32, 16, 3, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18942, 0, 0, 32, 16, 3, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18947, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18952, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18938, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18943, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18948, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18953, 0, 0, 16, 16, 3, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18939, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18944, 0, 0, 16, 32, 3, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18949, 0, 0, 16, 32, 3, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18954, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18940, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18945, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18950, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18955, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4CBC */
static void mini_rc_track_right_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18916, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18921, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18926, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18931, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18917, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18922, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18927, 0, 0, 32, 16, 3, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18932, 0, 0, 32, 16, 3, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18918, 0, 0, 16, 16, 3, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18923, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18928, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18933, 0, 0, 16, 16, 3, height, 0, 16, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18919, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18924, 0, 0, 16, 32, 3, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18929, 0, 0, 16, 32, 3, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18934, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18920, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18925, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18930, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18935, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A4CCC */
static void mini_rc_track_left_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_right_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A4CDC */
static void mini_rc_track_right_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_left_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4CEC */
static void mini_rc_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18900, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18904, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18903, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18907, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18901, 0, 0, 32, 26, 3, height);
			metal_a_supports_paint_setup(1, 5, 3, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18905, 0, 0, 32, 26, 3, height);
			metal_a_supports_paint_setup(2, 6, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18902, 0, 0, 32, 26, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18906, 0, 0, 32, 26, 3, height, 0, 6, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18902, 0, 0, 32, 26, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18906, 0, 0, 32, 26, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18901, 0, 0, 32, 26, 3, height);
			metal_a_supports_paint_setup(1, 5, 3, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18905, 0, 0, 32, 26, 3, height);
			metal_a_supports_paint_setup(2, 6, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18903, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18907, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18900, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18904, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4CFC */
static void mini_rc_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18908, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18912, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18911, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18915, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18909, 0, 0, 32, 26, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 8, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18913, 0, 0, 32, 26, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 7, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18910, 0, 0, 32, 26, 3, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18914, 0, 0, 32, 26, 3, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18910, 0, 0, 32, 26, 3, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18914, 0, 0, 32, 26, 3, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18909, 0, 0, 32, 26, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 8, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18913, 0, 0, 32, 26, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 7, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18911, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18915, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18908, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18912, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4D3C */
static void mini_rc_track_left_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18821, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18824, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18827, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18818, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18820, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18823, 0, 0, 16, 16, 3, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18826, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18817, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18819, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18822, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18825, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18816, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4D4C */
static void mini_rc_track_right_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_left_quarter_turn_3(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4D5C */
static void mini_rc_track_left_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18833, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18840, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18836, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18839, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18830, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18832, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18835, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18838, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18829, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18831, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18834, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18837, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18841, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18828, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4D6C */
static void mini_rc_track_right_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_left_quarter_turn_3_bank(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4D7C */
static void mini_rc_track_left_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18967, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18969, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18971, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18965, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18966, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18968, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18970, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18964, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A4D8C */
static void mini_rc_track_right_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18956, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18958, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18960, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18962, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18957, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18959, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18961, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(2, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18963, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A4D9C */
static void mini_rc_track_left_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_right_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A4DAC */
static void mini_rc_track_right_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_left_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4DBC */
static void mini_rc_track_left_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18991, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18998, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18994, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18997, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18988, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18990, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18993, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18996, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18987, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18989, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18992, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18995, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18999, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18986, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18988, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18991, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18998, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18994, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18997, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18987, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18990, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18993, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18996, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18986, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18989, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18992, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18995, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18999, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4DCC */
static void mini_rc_track_right_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18972, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18975, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18978, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18981, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18985, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 11, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18973, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18976, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18979, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18982, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18974, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18977, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18984, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18980, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18983, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
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
	case 4:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18975, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18978, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18981, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18985, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 11, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18972, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18976, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18979, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18982, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18973, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18977, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18984, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18980, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18983, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18974, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A4DDC */
static void mini_rc_track_left_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_right_half_banked_helix_up_small(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A4DEC */
static void mini_rc_track_right_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_left_half_banked_helix_up_small(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4DFC */
static void mini_rc_track_left_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19031, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19042, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19036, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19041, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19026, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19030, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19035, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19040, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19025, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19029, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19034, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19039, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19024, 0, 0, 16, 16, 3, height, 0, 0, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19028, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19033, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19038, 0, 0, 16, 32, 3, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19023, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19027, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19032, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19037, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19043, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19022, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19026, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19031, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19042, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19036, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19041, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19025, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19030, 0, 0, 16, 32, 3, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19035, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19040, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 10:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19024, 0, 0, 16, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19029, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19034, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19039, 0, 0, 16, 16, 3, height, 0, 16, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19023, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19028, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19033, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19038, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 13:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19022, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19027, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19032, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19037, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19043, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4E0C */
static void mini_rc_track_right_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19000, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19005, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19010, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19015, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19021, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19001, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19006, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19011, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19016, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19002, 0, 0, 16, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19007, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19012, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19017, 0, 0, 16, 16, 3, height, 0, 16, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19003, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19008, 0, 0, 16, 32, 3, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19013, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19018, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19004, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19009, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19020, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19014, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19019, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19005, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19010, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19015, 0, 0, 20, 32, 3, height, 6, 0, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19021, 0, 0, 1, 32, 26, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19000, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19006, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19011, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19016, 0, 0, 16, 32, 3, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19001, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 10:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19007, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19012, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19017, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19002, 0, 0, 16, 16, 3, height, 0, 0, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19008, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19013, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19018, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19003, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 13:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19009, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19020, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19014, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19019, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19004, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 13, height, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A4E1C */
static void mini_rc_track_left_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_right_half_banked_helix_up_large(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A4E2C */
static void mini_rc_track_right_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_left_half_banked_helix_up_large(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4E5C */
static void mini_rc_track_left_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18893, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18897, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18894, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18898, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18895, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18899, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18892, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18896, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	}
	switch (direction) {
	case 0:
		paint_util_push_tunnel_left(height - 8, TUNNEL_8);
		break;
	case 2:
		paint_util_push_tunnel_right(height + 56, TUNNEL_7);
		break;
	case 3:
		paint_util_push_tunnel_right(height - 8, TUNNEL_7);
		paint_util_push_tunnel_left(height + 56, TUNNEL_7);
		break;
	}
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

/** rct2: 0x008A4E3C */
static void mini_rc_track_right_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18884, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18888, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18885, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18889, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18886, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18890, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18887, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18891, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	}
	switch (direction) {
	case 0:
		paint_util_push_tunnel_right(height + 56, TUNNEL_7);
		paint_util_push_tunnel_left(height - 8, TUNNEL_7);
		break;
	case 1:
		paint_util_push_tunnel_left(height + 56, TUNNEL_8);
		break;
	case 3:
		paint_util_push_tunnel_right(height - 8, TUNNEL_7);
		break;
	}
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

/** rct2: 0x008A4E4C */
static void mini_rc_track_left_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_right_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A4E6C */
static void mini_rc_track_right_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_left_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A4E7C */
static void mini_rc_track_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18740, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18741, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A50CC */
static void mini_rc_track_25_deg_up_left_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19222, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19223, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19224, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19225, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x008A50DC */
static void mini_rc_track_25_deg_up_right_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19226, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19227, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19228, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19229, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x008A4E8C */
static void mini_rc_track_on_ride_photo(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(1, 5, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(1, 8, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18738, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
		break;
	case 1:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(2, 6, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(2, 7, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18739, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
		break;
	case 2:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(1, 5, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(1, 8, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18738, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
		break;
	case 3:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(2, 6, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(2, 7, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18739, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
		break;
	}
	track_paint_util_onride_photo_paint(direction, height + 3, mapElement);
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A50EC */
static void mini_rc_track_25_deg_down_left_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_right_banked(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A50FC */
static void mini_rc_track_25_deg_down_right_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_left_banked(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4EAC */
static void mini_rc_track_left_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19076, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19080, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19084, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19088, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19077, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19081, 0, 0, 34, 16, 3, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19085, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19089, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19078, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19082, 0, 0, 16, 16, 3, height, 16, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19086, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19090, 0, 0, 16, 16, 3, height, 0, 0, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19079, 0, 0, 16, 16, 3, height, 16, 16, height);
			metal_a_supports_paint_setup(1, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19083, 0, 0, 16, 18, 3, height, 0, 16, height);
			metal_a_supports_paint_setup(2, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19087, 0, 0, 16, 16, 3, height, 0, 0, height);
			metal_a_supports_paint_setup(1, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19091, 0, 0, 16, 16, 3, height, 16, 0, height);
			metal_a_supports_paint_setup(2, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4EBC */
static void mini_rc_track_right_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19060, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19064, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19068, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19072, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19061, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19065, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19069, 0, 0, 34, 16, 3, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19073, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19062, 0, 0, 16, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19066, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19070, 0, 0, 28, 28, 3, height, 4, 4, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19074, 0, 0, 16, 16, 3, height, 0, 16, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19063, 0, 0, 16, 16, 3, height, 16, 0, height);
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19067, 0, 0, 16, 16, 3, height, 0, 0, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19071, 0, 0, 16, 18, 3, height, 0, 16, height);
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19075, 0, 0, 16, 16, 3, height, 16, 16, height);
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4ECC */
static void mini_rc_track_left_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	mini_rc_track_right_eighth_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4EDC */
static void mini_rc_track_right_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	mini_rc_track_left_eighth_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

/** rct2: 0x008A4EEC */
static void mini_rc_track_left_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19108, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19112, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19116, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19120, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19109, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19113, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19117, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19121, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19110, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19114, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19118, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19122, 0, 0, 16, 16, 3, height, 0, 0, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19111, 0, 0, 16, 16, 3, height, 16, 16, height);
			metal_a_supports_paint_setup(1, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19115, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
			metal_a_supports_paint_setup(2, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19119, 0, 0, 16, 16, 3, height, 0, 0, height);
			metal_a_supports_paint_setup(1, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19123, 0, 0, 16, 16, 3, height, 16, 0, height);
			metal_a_supports_paint_setup(2, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4EFC */
static void mini_rc_track_right_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19092, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19096, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19100, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19104, 0, 0, 32, 1, 26, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19093, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19097, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19101, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19105, 0, 0, 32, 16, 3, height, 0, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19094, 0, 0, 16, 16, 3, height, 0, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19098, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19102, 0, 0, 28, 28, 0, height, 4, 4, height + 27);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19106, 0, 0, 16, 16, 3, height, 0, 16, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19095, 0, 0, 16, 16, 3, height, 16, 0, height);
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19099, 0, 0, 16, 16, 3, height, 0, 0, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19103, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19107, 0, 0, 16, 16, 3, height, 16, 16, height);
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4F0C */
static void mini_rc_track_left_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	mini_rc_track_right_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A4F1C */
static void mini_rc_track_right_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	mini_rc_track_left_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

/** rct2: 0x008A4E9C */
static void mini_rc_track_diag_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19189, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19127, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19186, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19124, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19188, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19126, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19187, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19125, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4F4C */
static void mini_rc_track_diag_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19201, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19139, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19198, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19136, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19200, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19138, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				metal_b_supports_paint_setup(1, 1, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19199, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(1, 1, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19137, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A4FAC */
static void mini_rc_track_diag_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19151, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19148, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19150, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 38, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19149, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 42, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 38, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 42, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	}
}

/** rct2: 0x008A4F2C */
static void mini_rc_track_diag_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19193, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19131, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19190, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19128, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19192, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19130, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19191, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19129, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A4F8C */
static void mini_rc_track_diag_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19143, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19140, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19142, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 22, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19141, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 22, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 22, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 22, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A4F9C */
static void mini_rc_track_diag_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19147, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19144, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19146, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19145, -16, -16, 16, 16, 3, height, 0, 0, height);
			metal_b_supports_paint_setup(2, 0, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A4F3C */
static void mini_rc_track_diag_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19197, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19135, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19194, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19132, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19196, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19134, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19195, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19133, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A4F7C */
static void mini_rc_track_diag_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19199, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19137, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19200, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19138, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19198, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19136, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				metal_b_supports_paint_setup(1, 1, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19201, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(1, 1, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19139, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 14, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A4FDC */
static void mini_rc_track_diag_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19149, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19150, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19148, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 30, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19151, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 34, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 30, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 34, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
		break;
	}
}

/** rct2: 0x008A4F5C */
static void mini_rc_track_diag_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19195, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19133, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19196, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19134, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19194, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19132, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19197, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19135, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A4FBC */
static void mini_rc_track_diag_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19145, -16, -16, 16, 16, 3, height, 0, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19146, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19144, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 23, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19147, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 23, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 23, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 23, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A4FCC */
static void mini_rc_track_diag_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19141, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19142, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19140, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19143, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A4F6C */
static void mini_rc_track_diag_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19191, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19129, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19192, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19130, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19190, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19128, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19193, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19131, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A500C */
static void mini_rc_track_diag_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19159, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19156, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19160, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19158, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19157, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A501C */
static void mini_rc_track_diag_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19164, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19161, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19163, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19165, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19162, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A502C */
static void mini_rc_track_diag_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19162, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19163, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19165, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19161, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19164, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A503C */
static void mini_rc_track_diag_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19157, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19158, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19156, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19160, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19159, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A506C */
static void mini_rc_track_diag_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19179, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19176, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19180, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19178, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19177, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A507C */
static void mini_rc_track_diag_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19184, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19181, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19183, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19185, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19182, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A504C */
static void mini_rc_track_diag_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19169, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19166, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19170, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19168, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19167, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A505C */
static void mini_rc_track_diag_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19174, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19171, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19173, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19175, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19172, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A508C */
static void mini_rc_track_diag_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19172, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19173, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19175, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19171, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19174, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A509C */
static void mini_rc_track_diag_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19167, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19168, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19166, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19170, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19169, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 10, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	}
}

/** rct2: 0x008A50AC */
static void mini_rc_track_diag_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19182, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19183, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19185, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19181, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19184, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A50BC */
static void mini_rc_track_diag_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19177, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19178, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19176, -16, -16, 32, 32, 3, height, -16, -16, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19180, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19179, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_b_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A4FEC */
static void mini_rc_track_diag_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19155, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19152, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19154, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19153, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A4FFC */
static void mini_rc_track_diag_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19153, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19154, -16, -16, 32, 32, 3, height, -16, -16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19152, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(1, 1, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19155, -16, -16, 32, 32, 3, height, -16, -16, height);
			metal_a_supports_paint_setup(2, 0, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(1, 2, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(2, 3, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
		break;
	}
}

/** rct2: 0x008A530C */
static void mini_rc_track_block_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18742, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 18743, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x008A510C */
static void mini_rc_track_left_banked_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19317, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19319, 0, 6, 32, 1, 34, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19321, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19315, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19316, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19318, 6, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19320, 6, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19314, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A511C */
static void mini_rc_track_right_banked_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19306, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19308, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19310, 0, 6, 32, 1, 34, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19312, 0, 6, 32, 20, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19307, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19309, 6, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19311, 6, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19313, 6, 0, 20, 32, 3, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A512C */
static void mini_rc_track_left_banked_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_right_banked_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A513C */
static void mini_rc_track_right_banked_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	mini_rc_track_left_banked_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A514C */
static void mini_rc_track_left_banked_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19286, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19291, 0, 0, 32, 1, 34, height, 0, 27, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19296, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19301, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19287, 0, 0, 32, 16, 3, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19292, 0, 0, 1, 1, 34, height, 30, 30, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19297, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19302, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19288, 0, 0, 16, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19293, 0, 0, 1, 1, 34, height, 30, 30, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19298, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19303, 0, 0, 16, 16, 3, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19289, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19294, 0, 0, 1, 1, 34, height, 30, 30, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19299, 0, 0, 1, 32, 34, height, 27, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19304, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19290, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19295, 0, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19300, 0, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19305, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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

/** rct2: 0x008A515C */
static void mini_rc_track_right_banked_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19266, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19271, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19276, 0, 0, 32, 1, 34, height, 0, 27, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19281, 0, 0, 32, 20, 3, height, 0, 6, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19267, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19272, 0, 0, 32, 16, 3, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19277, 0, 0, 1, 1, 34, height, 30, 30, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19282, 0, 0, 32, 16, 3, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19268, 0, 0, 16, 16, 3, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19273, 0, 0, 16, 16, 3, height, 16, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19278, 0, 0, 1, 1, 34, height, 30, 30, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19283, 0, 0, 16, 16, 3, height, 0, 16, height);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19269, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19274, 0, 0, 1, 32, 34, height, 27, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19279, 0, 0, 1, 1, 34, height, 30, 30, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19284, 0, 0, 16, 32, 3, height, 16, 0, height);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19270, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19275, 0, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19280, 0, 0, 1, 32, 34, height, 27, 0, height);
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19285, 0, 0, 20, 32, 3, height, 6, 0, height);
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A516C */
static void mini_rc_track_left_banked_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_right_banked_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A517C */
static void mini_rc_track_right_banked_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	mini_rc_track_left_banked_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A518C */
static void mini_rc_track_25_deg_up_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19230, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19231, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19238, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19232, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19233, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x008A519C */
static void mini_rc_track_25_deg_up_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19234, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19235, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19236, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19239, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19237, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x008A51AC */
static void mini_rc_track_left_banked_25_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19240, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19241, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19248, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19242, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19243, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x008A51BC */
static void mini_rc_track_right_banked_25_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19244, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19245, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19246, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19249, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19247, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 14, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 56, 0x20);
}

/** rct2: 0x008A51CC */
static void mini_rc_track_25_deg_down_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_right_banked_25_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A51DC */
static void mini_rc_track_25_deg_down_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_left_banked_25_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A51EC */
static void mini_rc_track_left_banked_25_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A51FC */
static void mini_rc_track_right_banked_25_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_25_deg_up_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A520C */
static void mini_rc_track_left_banked_flat_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19250, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19251, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19252, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19253, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A521C */
static void mini_rc_track_right_banked_flat_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19254, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19255, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19256, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19257, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A524C */
static void mini_rc_track_left_banked_25_deg_up_to_left_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19258, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19259, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19260, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19261, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x008A525C */
static void mini_rc_track_right_banked_25_deg_up_to_right_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19262, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19263, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19264, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19265, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x008A526C */
static void mini_rc_track_left_banked_flat_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_right_banked_25_deg_up_to_right_banked_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A527C */
static void mini_rc_track_right_banked_flat_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_left_banked_25_deg_up_to_left_banked_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A522C */
static void mini_rc_track_left_banked_25_deg_down_to_left_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_right_banked_flat_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A523C */
static void mini_rc_track_right_banked_25_deg_down_to_right_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_left_banked_flat_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A528C */
static void mini_rc_track_flat_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19202, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19203, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19210, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19204, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19205, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A529C */
static void mini_rc_track_flat_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19206, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19207, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19208, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19211, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19209, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 9, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A52AC */
static void mini_rc_track_left_banked_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19212, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19213, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19220, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19214, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19215, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x008A52BC */
static void mini_rc_track_right_banked_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19216, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19217, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19218, 0, 0, 32, 20, 3, height, 0, 6, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19221, 0, 0, 32, 1, 34, height, 0, 27, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(1, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 19219, 0, 0, 32, 20, 3, height, 0, 6, height);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(2, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		break;
	}
	if (direction == 0 || direction == 3) {
		paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
	} else {
		paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 40, 0x20);
}

/** rct2: 0x008A52CC */
static void mini_rc_track_flat_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_right_banked_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A52DC */
static void mini_rc_track_flat_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_left_banked_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A52EC */
static void mini_rc_track_left_banked_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_flat_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A52FC */
static void mini_rc_track_right_banked_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	mini_rc_track_flat_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

TRACK_PAINT_FUNCTION get_track_paint_function_mini_rc(int trackType, int direction)
{
	switch (trackType) {
	case TRACK_ELEM_FLAT:
		return mini_rc_track_flat;
	case TRACK_ELEM_END_STATION:
	case TRACK_ELEM_BEGIN_STATION:
	case TRACK_ELEM_MIDDLE_STATION:
		return mini_rc_track_station;
	case TRACK_ELEM_25_DEG_UP:
		return mini_rc_track_25_deg_up;
	case TRACK_ELEM_60_DEG_UP:
		return mini_rc_track_60_deg_up;
	case TRACK_ELEM_FLAT_TO_25_DEG_UP:
		return mini_rc_track_flat_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_60_DEG_UP:
		return mini_rc_track_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_60_DEG_UP_TO_25_DEG_UP:
		return mini_rc_track_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_FLAT:
		return mini_rc_track_25_deg_up_to_flat;
	case TRACK_ELEM_25_DEG_DOWN:
		return mini_rc_track_25_deg_down;
	case TRACK_ELEM_60_DEG_DOWN:
		return mini_rc_track_60_deg_down;
	case TRACK_ELEM_FLAT_TO_25_DEG_DOWN:
		return mini_rc_track_flat_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_60_DEG_DOWN:
		return mini_rc_track_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_60_DEG_DOWN_TO_25_DEG_DOWN:
		return mini_rc_track_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_FLAT:
		return mini_rc_track_25_deg_down_to_flat;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES:
		return mini_rc_track_left_quarter_turn_5;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES:
		return mini_rc_track_right_quarter_turn_5;
	case TRACK_ELEM_FLAT_TO_LEFT_BANK:
		return mini_rc_track_flat_to_left_bank;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANK:
		return mini_rc_track_flat_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_FLAT:
		return mini_rc_track_left_bank_to_flat;
	case TRACK_ELEM_RIGHT_BANK_TO_FLAT:
		return mini_rc_track_right_bank_to_flat;
	case TRACK_ELEM_BANKED_LEFT_QUARTER_TURN_5_TILES:
		return mini_rc_track_banked_left_quarter_turn_5;
	case TRACK_ELEM_BANKED_RIGHT_QUARTER_TURN_5_TILES:
		return mini_rc_track_banked_right_quarter_turn_5;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_UP:
		return mini_rc_track_left_bank_to_25_deg_up;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_UP:
		return mini_rc_track_right_bank_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_LEFT_BANK:
		return mini_rc_track_25_deg_up_to_left_bank;
	case TRACK_ELEM_25_DEG_UP_TO_RIGHT_BANK:
		return mini_rc_track_25_deg_up_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_DOWN:
		return mini_rc_track_left_bank_to_25_deg_down;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_DOWN:
		return mini_rc_track_right_bank_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_LEFT_BANK:
		return mini_rc_track_25_deg_down_to_left_bank;
	case TRACK_ELEM_25_DEG_DOWN_TO_RIGHT_BANK:
		return mini_rc_track_25_deg_down_to_right_bank;
	case TRACK_ELEM_LEFT_BANK:
		return mini_rc_track_left_bank;
	case TRACK_ELEM_RIGHT_BANK:
		return mini_rc_track_right_bank;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return mini_rc_track_left_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return mini_rc_track_right_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return mini_rc_track_left_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return mini_rc_track_right_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_S_BEND_LEFT:
		return mini_rc_track_s_bend_left;
	case TRACK_ELEM_S_BEND_RIGHT:
		return mini_rc_track_s_bend_right;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
		return mini_rc_track_left_quarter_turn_3;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
		return mini_rc_track_right_quarter_turn_3;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_BANK:
		return mini_rc_track_left_quarter_turn_3_bank;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_BANK:
		return mini_rc_track_right_quarter_turn_3_bank;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return mini_rc_track_left_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return mini_rc_track_right_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return mini_rc_track_left_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return mini_rc_track_right_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_SMALL:
		return mini_rc_track_left_half_banked_helix_up_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_SMALL:
		return mini_rc_track_right_half_banked_helix_up_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_SMALL:
		return mini_rc_track_left_half_banked_helix_down_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_SMALL:
		return mini_rc_track_right_half_banked_helix_down_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_LARGE:
		return mini_rc_track_left_half_banked_helix_up_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_LARGE:
		return mini_rc_track_right_half_banked_helix_up_large;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_LARGE:
		return mini_rc_track_left_half_banked_helix_down_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_LARGE:
		return mini_rc_track_right_half_banked_helix_down_large;
	case TRACK_ELEM_LEFT_QUARTER_TURN_1_TILE_60_DEG_UP:
		return mini_rc_track_left_quarter_turn_1_60_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_1_TILE_60_DEG_UP:
		return mini_rc_track_right_quarter_turn_1_60_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_1_TILE_60_DEG_DOWN:
		return mini_rc_track_left_quarter_turn_1_60_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_1_TILE_60_DEG_DOWN:
		return mini_rc_track_right_quarter_turn_1_60_deg_down;
	case TRACK_ELEM_BRAKES:
		return mini_rc_track_brakes;
	case TRACK_ELEM_25_DEG_UP_LEFT_BANKED:
		return mini_rc_track_25_deg_up_left_banked;
	case TRACK_ELEM_25_DEG_UP_RIGHT_BANKED:
		return mini_rc_track_25_deg_up_right_banked;
	case TRACK_ELEM_ON_RIDE_PHOTO:
		return mini_rc_track_on_ride_photo;
	case TRACK_ELEM_25_DEG_DOWN_LEFT_BANKED:
		return mini_rc_track_25_deg_down_left_banked;
	case TRACK_ELEM_25_DEG_DOWN_RIGHT_BANKED:
		return mini_rc_track_25_deg_down_right_banked;
	case TRACK_ELEM_LEFT_EIGHTH_TO_DIAG:
		return mini_rc_track_left_eighth_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_DIAG:
		return mini_rc_track_right_eighth_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_TO_ORTHOGONAL:
		return mini_rc_track_left_eighth_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_ORTHOGONAL:
		return mini_rc_track_right_eighth_to_orthogonal;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_DIAG:
		return mini_rc_track_left_eighth_bank_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_DIAG:
		return mini_rc_track_right_eighth_bank_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_ORTHOGONAL:
		return mini_rc_track_left_eighth_bank_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_ORTHOGONAL:
		return mini_rc_track_right_eighth_bank_to_orthogonal;
	case TRACK_ELEM_DIAG_FLAT:
		return mini_rc_track_diag_flat;
	case TRACK_ELEM_DIAG_25_DEG_UP:
		return mini_rc_track_diag_25_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP:
		return mini_rc_track_diag_60_deg_up;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_UP:
		return mini_rc_track_diag_flat_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_60_DEG_UP:
		return mini_rc_track_diag_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP_TO_25_DEG_UP:
		return mini_rc_track_diag_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_FLAT:
		return mini_rc_track_diag_25_deg_up_to_flat;
	case TRACK_ELEM_DIAG_25_DEG_DOWN:
		return mini_rc_track_diag_25_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN:
		return mini_rc_track_diag_60_deg_down;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_DOWN:
		return mini_rc_track_diag_flat_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_60_DEG_DOWN:
		return mini_rc_track_diag_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN_TO_25_DEG_DOWN:
		return mini_rc_track_diag_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_FLAT:
		return mini_rc_track_diag_25_deg_down_to_flat;
	case TRACK_ELEM_DIAG_FLAT_TO_LEFT_BANK:
		return mini_rc_track_diag_flat_to_left_bank;
	case TRACK_ELEM_DIAG_FLAT_TO_RIGHT_BANK:
		return mini_rc_track_diag_flat_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_FLAT:
		return mini_rc_track_diag_left_bank_to_flat;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_FLAT:
		return mini_rc_track_diag_right_bank_to_flat;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_UP:
		return mini_rc_track_diag_left_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_UP:
		return mini_rc_track_diag_right_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_LEFT_BANK:
		return mini_rc_track_diag_25_deg_up_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_RIGHT_BANK:
		return mini_rc_track_diag_25_deg_up_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_DOWN:
		return mini_rc_track_diag_left_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_DOWN:
		return mini_rc_track_diag_right_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_LEFT_BANK:
		return mini_rc_track_diag_25_deg_down_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_RIGHT_BANK:
		return mini_rc_track_diag_25_deg_down_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK:
		return mini_rc_track_diag_left_bank;
	case TRACK_ELEM_DIAG_RIGHT_BANK:
		return mini_rc_track_diag_right_bank;
	case TRACK_ELEM_BLOCK_BRAKES:
		return mini_rc_track_block_brakes;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_3_TILE_25_DEG_UP:
		return mini_rc_track_left_banked_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_3_TILE_25_DEG_UP:
		return mini_rc_track_right_banked_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_3_TILE_25_DEG_DOWN:
		return mini_rc_track_left_banked_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_3_TILE_25_DEG_DOWN:
		return mini_rc_track_right_banked_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_5_TILE_25_DEG_UP:
		return mini_rc_track_left_banked_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_5_TILE_25_DEG_UP:
		return mini_rc_track_right_banked_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_5_TILE_25_DEG_DOWN:
		return mini_rc_track_left_banked_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_5_TILE_25_DEG_DOWN:
		return mini_rc_track_right_banked_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_25_DEG_UP_TO_LEFT_BANKED_25_DEG_UP:
		return mini_rc_track_25_deg_up_to_left_banked_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_RIGHT_BANKED_25_DEG_UP:
		return mini_rc_track_25_deg_up_to_right_banked_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_UP_TO_25_DEG_UP:
		return mini_rc_track_left_banked_25_deg_up_to_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_UP_TO_25_DEG_UP:
		return mini_rc_track_right_banked_25_deg_up_to_25_deg_up;
	case TRACK_ELEM_25_DEG_DOWN_TO_LEFT_BANKED_25_DEG_DOWN:
		return mini_rc_track_25_deg_down_to_left_banked_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_RIGHT_BANKED_25_DEG_DOWN:
		return mini_rc_track_25_deg_down_to_right_banked_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_DOWN_TO_25_DEG_DOWN:
		return mini_rc_track_left_banked_25_deg_down_to_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_DOWN_TO_25_DEG_DOWN:
		return mini_rc_track_right_banked_25_deg_down_to_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_FLAT_TO_LEFT_BANKED_25_DEG_UP:
		return mini_rc_track_left_banked_flat_to_left_banked_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_FLAT_TO_RIGHT_BANKED_25_DEG_UP:
		return mini_rc_track_right_banked_flat_to_right_banked_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_UP_TO_LEFT_BANKED_FLAT:
		return mini_rc_track_left_banked_25_deg_up_to_left_banked_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_UP_TO_RIGHT_BANKED_FLAT:
		return mini_rc_track_right_banked_25_deg_up_to_right_banked_flat;
	case TRACK_ELEM_LEFT_BANKED_FLAT_TO_LEFT_BANKED_25_DEG_DOWN:
		return mini_rc_track_left_banked_flat_to_left_banked_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_FLAT_TO_RIGHT_BANKED_25_DEG_DOWN:
		return mini_rc_track_right_banked_flat_to_right_banked_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_DOWN_TO_LEFT_BANKED_FLAT:
		return mini_rc_track_left_banked_25_deg_down_to_left_banked_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_DOWN_TO_RIGHT_BANKED_FLAT:
		return mini_rc_track_right_banked_25_deg_down_to_right_banked_flat;
	case TRACK_ELEM_FLAT_TO_LEFT_BANKED_25_DEG_UP:
		return mini_rc_track_flat_to_left_banked_25_deg_up;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANKED_25_DEG_UP:
		return mini_rc_track_flat_to_right_banked_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_UP_TO_FLAT:
		return mini_rc_track_left_banked_25_deg_up_to_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_UP_TO_FLAT:
		return mini_rc_track_right_banked_25_deg_up_to_flat;
	case TRACK_ELEM_FLAT_TO_LEFT_BANKED_25_DEG_DOWN:
		return mini_rc_track_flat_to_left_banked_25_deg_down;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANKED_25_DEG_DOWN:
		return mini_rc_track_flat_to_right_banked_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_DOWN_TO_FLAT:
		return mini_rc_track_left_banked_25_deg_down_to_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_DOWN_TO_FLAT:
		return mini_rc_track_right_banked_25_deg_down_to_flat;
	}
	return NULL;
}
