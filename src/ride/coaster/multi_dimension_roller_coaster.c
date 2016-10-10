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

static void multi_dimension_rc_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15808, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15809, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15806, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15807, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26227, 0, 0, 32, 20, 1, height + 24, 0, 6, height + 22);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26228, 0, 0, 32, 20, 1, height + 24, 0, 6, height + 22);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	static const uint32 imageIds[4][3] = {
		{ 15810, 15812, SPR_STATION_INVERTED_BAR_A_SW_NE },
		{ 15811, 15813, SPR_STATION_INVERTED_BAR_A_NW_SE },
		{ 15810, 15812, SPR_STATION_INVERTED_BAR_A_SW_NE },
		{ 15811, 15813, SPR_STATION_INVERTED_BAR_A_NW_SE },
	};

	if (mapElement->properties.track.type == TRACK_ELEM_END_STATION) {
		sub_98197C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 26, 1, height, 0, 3, height + 3);
	} else {
		sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 26, 1, height, 0, 3, height + 3);
	}
	track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], 11);
	
	rct_ride * ride = get_ride(rideIndex);
	const rct_ride_entrance_definition * entranceStyle = &RideEntranceDefinitions[ride->entrance_style];
	if (direction == 0 || direction == 2) {
		track_paint_util_draw_station_covers(EDGE_NW, false, entranceStyle, direction, height);
	} else {
		track_paint_util_draw_station_covers(EDGE_NE, false, entranceStyle, direction, height);
	}

	if (direction == 0 || direction == 2) {
		track_paint_util_draw_station_covers(EDGE_SE, false, entranceStyle, direction, height);
	} else {
		track_paint_util_draw_station_covers(EDGE_SW, false, entranceStyle, direction, height);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

static void multi_dimension_rc_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15908, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15909, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15910, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15911, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15880, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15881, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15882, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15883, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_8);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26253, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26254, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26255, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26256, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
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
}

static void multi_dimension_rc_track_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15896, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15897, 0, 0, 32, 1, 98, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15898, 0, 0, 32, 1, 98, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15899, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 24, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 56, TUNNEL_8);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26269, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 88);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26270, 0, 0, 32, 2, 81, height + 24, 0, 4, height + 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26271, 0, 0, 32, 2, 81, height + 24, 0, 4, height + 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26272, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 88);
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
}

static void multi_dimension_rc_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15900, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15901, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15902, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15903, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15872, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15873, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15874, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15875, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26245, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26246, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26247, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26248, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);
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
}

static void multi_dimension_rc_track_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15884, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15885, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15888, 0, 0, 32, 1, 66, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15886, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15889, 0, 0, 32, 1, 66, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15887, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_8);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26257, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26261, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26258, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26262, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26259, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26260, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
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
}

static void multi_dimension_rc_track_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15890, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15891, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15894, 0, 0, 32, 1, 66, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15892, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15895, 0, 0, 32, 1, 66, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15893, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_8);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26263, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 68, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26267, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26264, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 68, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26268, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26265, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 68, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26266, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 68, gTrackColours[SCHEME_SUPPORTS]);
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
}

static void multi_dimension_rc_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15904, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15905, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15906, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15907, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15876, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15877, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15878, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15879, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26249, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26250, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26251, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26252, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
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
}

static void multi_dimension_rc_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_60_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_25_deg_up_to_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15921, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15926, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15931, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15916, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15920, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15925, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15930, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15915, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15919, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15924, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15929, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15914, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15918, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15923, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15928, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15913, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15917, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15922, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15927, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15912, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26310, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26315, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26320, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26305, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26309, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26314, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26319, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26304, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26308, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26313, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26318, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26303, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26307, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26312, 0, 0, 16, 32, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26317, 0, 0, 16, 32, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26302, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26306, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26311, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26316, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26301, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	multi_dimension_rc_track_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15832, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15840, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15833, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15841, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15834, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15835, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26273, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26274, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26275, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26276, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15836, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15837, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15838, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15842, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15839, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15843, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26277, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26278, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26279, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26280, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15838, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15842, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15839, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15843, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15836, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15837, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26279, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26280, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26277, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26278, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15834, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15835, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15832, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15840, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15833, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15841, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26275, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26276, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26273, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26274, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_banked_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15941, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15952, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15946, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15951, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15936, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15940, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15945, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15950, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15935, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15939, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15944, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15949, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15934, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15938, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15943, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15948, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15933, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15937, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15942, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15947, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15953, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15932, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26354, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26359, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26364, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26349, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26353, 0, 0, 32, 16, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26358, 0, 0, 32, 16, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26363, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26348, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26352, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26357, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26362, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26347, 0, 0, 16, 16, 3, height + 24);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26351, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26356, 0, 0, 16, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26361, 0, 0, 16, 32, 3, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26346, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26350, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26355, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26360, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26345, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_banked_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	multi_dimension_rc_track_banked_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15844, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15848, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15845, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15849, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15846, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15847, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26281, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26282, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26283, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26284, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	}
}

static void multi_dimension_rc_track_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15850, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15851, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15852, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15854, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15853, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15855, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26285, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26286, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26287, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26288, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_8);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	}
}

static void multi_dimension_rc_track_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15856, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15860, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15857, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15861, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15858, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15859, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26289, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26290, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26291, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26292, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	}
}

static void multi_dimension_rc_track_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15862, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15863, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15864, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15866, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15865, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15867, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26293, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26294, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26295, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26296, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			}
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_6);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_14);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	}
}

static void multi_dimension_rc_track_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_25_deg_up_to_right_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_25_deg_up_to_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_right_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_left_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15868, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15869, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15870, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15871, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26297, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26298, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26299, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26300, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15816, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15820, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15819, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15823, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15817, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15821, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15818, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15822, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15818, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15822, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15817, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15821, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15819, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15823, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15816, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15820, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26229, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26233, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26232, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26236, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26230, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 5, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26234, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 6, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26231, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26235, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26231, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26235, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26230, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 5, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26234, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 6, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26232, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26236, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26229, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26233, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
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
}

static void multi_dimension_rc_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15824, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15828, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15827, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15831, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15825, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15829, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15826, 0, 0, 32, 26, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15830, 0, 0, 32, 26, 3, height);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15826, 0, 0, 32, 26, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15830, 0, 0, 32, 26, 3, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15825, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15829, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15827, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15831, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15824, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15828, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26237, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26241, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26240, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26244, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26238, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				metal_a_supports_paint_setup(11, 8, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26242, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				metal_a_supports_paint_setup(11, 7, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26239, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26243, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26239, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26243, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26238, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				metal_a_supports_paint_setup(11, 8, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26242, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				metal_a_supports_paint_setup(11, 7, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26240, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26244, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26237, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26241, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
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
}

static void multi_dimension_rc_track_left_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15959, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15962, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15965, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15956, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15958, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15961, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15964, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15955, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15957, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15960, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15963, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15954, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26326, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26329, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26332, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26323, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26325, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26328, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26331, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26322, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26324, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26327, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26330, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26321, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	multi_dimension_rc_track_left_quarter_turn_3(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_left_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15971, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15978, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15974, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15977, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15968, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15970, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15973, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15976, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15967, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15969, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15972, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15975, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15979, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15966, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26338, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26341, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26344, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26335, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26337, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26340, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26343, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26334, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26336, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26339, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26342, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26333, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	multi_dimension_rc_track_left_quarter_turn_3_bank(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_left_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16197, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16204, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16200, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16203, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16194, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16196, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16199, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16202, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16193, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16195, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16198, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16201, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16205, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16192, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16194, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16197, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16204, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16200, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16203, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16193, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16196, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16199, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16202, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16192, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16195, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16198, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16201, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16205, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16197, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16204, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16200, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16203, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16194, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16196, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16199, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16202, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16193, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16195, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16198, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16201, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16205, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16192, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16194, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16197, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16204, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16200, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16203, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 5:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16193, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16196, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16199, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16202, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16192, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16195, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16198, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16201, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16205, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16178, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16181, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16184, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16187, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16191, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16179, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16182, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16185, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16188, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16180, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16183, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16190, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16186, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16189, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16181, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16184, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16187, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16191, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16178, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16182, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16185, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16188, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16179, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16183, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16190, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16186, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16189, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16180, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16178, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16181, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16184, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16187, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16191, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16179, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16182, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16185, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16188, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16180, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16183, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16190, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16186, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16189, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 4:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16181, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16184, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16187, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16191, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16178, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16182, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16185, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16188, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16179, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16183, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16190, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16186, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16189, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16180, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_left_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	multi_dimension_rc_track_right_half_banked_helix_up_small(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_right_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	multi_dimension_rc_track_left_half_banked_helix_up_small(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_left_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16165, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16176, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16170, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16175, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16160, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16164, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16169, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16174, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16159, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16163, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16168, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16173, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16158, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16162, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16167, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16172, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16157, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16161, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16166, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16171, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16177, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16156, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16160, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16165, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16176, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16170, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16175, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 8:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 9:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16159, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16164, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16169, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16174, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16158, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16163, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16168, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16173, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16157, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16162, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16167, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16172, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16156, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16161, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16166, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16171, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16177, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16165, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16176, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16170, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16175, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16160, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16164, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16169, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16174, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16159, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16163, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16168, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16173, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16158, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16162, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16167, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16172, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16157, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16161, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16166, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16171, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16177, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16156, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16160, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16165, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16176, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16170, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16175, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 8:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 9:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16159, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16164, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16169, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16174, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16158, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16163, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16168, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16173, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16157, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16162, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16167, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16172, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16156, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16161, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16166, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16171, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16177, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16134, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16139, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16144, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16149, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16155, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16135, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16140, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16145, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16150, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16136, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16141, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16146, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16151, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16137, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16142, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16147, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16152, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16138, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16143, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16154, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16148, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16153, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16139, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16144, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16149, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16155, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16134, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16140, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16145, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16150, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16135, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16141, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16146, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16151, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16136, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16142, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16147, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16152, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16137, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16143, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16154, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16148, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16153, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16138, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16134, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16139, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16144, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16149, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16155, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16135, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16140, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16145, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16150, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16136, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16141, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16146, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16151, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16137, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16142, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16147, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16152, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16138, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16143, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16154, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16148, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16153, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_6);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16139, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16144, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16149, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16155, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16134, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16140, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16145, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16150, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16135, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16141, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16146, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16151, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16136, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16142, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16147, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16152, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16137, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16143, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16154, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16148, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16153, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16138, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_left_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	multi_dimension_rc_track_right_half_banked_helix_up_large(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_right_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	multi_dimension_rc_track_left_half_banked_helix_up_large(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

static void multi_dimension_rc_track_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16218, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16219, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26549, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26550, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_on_ride_photo(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15806, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 1:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15807, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 2:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15806, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 3:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15807, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		}
		track_paint_util_onride_photo_paint(direction, height + 3, mapElement);
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26227, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 1:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26228, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 2:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26227, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 3:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26228, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		}
		track_paint_util_onride_photo_paint(direction, height + 3, mapElement);
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
	}
}

static void multi_dimension_rc_track_90_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16130, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16131, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16132, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16133, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			}
			paint_util_set_vertical_tunnel(height + 32);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26533, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26534, 0, 0, 32, 2, 31, height + 24, 0, 4, height + 6);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26535, 0, 0, 32, 2, 31, height + 24, 0, 4, height + 6);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26536, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
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
}

static void multi_dimension_rc_track_90_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_90_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_60_deg_up_to_90_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16122, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16123, 0, 0, 2, 20, 55, height, 24, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16124, 0, 0, 2, 20, 55, height, 24, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16125, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_7);
			}
			paint_util_set_vertical_tunnel(height + 48);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26525, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 80);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26526, 0, 0, 32, 2, 55, height + 24, 0, 4, height + 6);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26527, 0, 0, 32, 2, 55, height + 24, 0, 4, height + 6);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26528, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 80);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
			}
			paint_util_set_vertical_tunnel(height + 48);
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			break;
		}
	}
}

static void multi_dimension_rc_track_90_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	multi_dimension_rc_track_60_deg_up_to_90_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_90_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16126, 0, 0, 6, 20, 3, height, 0, 6, height + 2);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16127, 0, 0, 2, 20, 31, height, 39, 6, height + 8);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16128, 0, 0, 2, 20, 31, height, 39, 6, height + 8);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16129, 0, 0, 6, 20, 3, height, 0, 6, height + 2);
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
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26529, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 80);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26530, 0, 0, 32, 2, 55, height + 24, 0, 4, height + 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26531, 0, 0, 32, 2, 55, height + 24, 0, 4, height + 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26532, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 80);
			break;
		}
		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height + 48, TUNNEL_5);
			break;
		case 2:
			paint_util_push_tunnel_left(height + 48, TUNNEL_5);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 96, 0x20);
	}
}

static void multi_dimension_rc_track_60_deg_down_to_90_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16128, 0, 0, 2, 20, 31, height, 39, 6, height + 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16129, 0, 0, 6, 20, 3, height, 0, 6, height + 2);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16126, 0, 0, 6, 20, 3, height, 0, 6, height + 2);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16127, 0, 0, 2, 20, 31, height, 39, 6, height + 8);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26531, 0, 0, 32, 2, 55, height + 24, 0, 4, height + 6);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26532, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 80);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26529, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 80);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26530, 0, 0, 32, 2, 55, height + 24, 0, 4, height + 6);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 48, TUNNEL_5);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 96, 0x20);
			break;
		case 1:
			break;
		}
	}
}

static void multi_dimension_rc_track_left_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15996, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16000, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16004, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16008, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15997, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16001, 0, 0, 34, 16, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16005, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16009, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15998, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16002, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16006, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16010, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15999, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16003, 0, 0, 16, 18, 3, height, 0, 16, height);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16007, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16011, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26405, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26409, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26413, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26417, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26406, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26410, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26414, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26418, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26407, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26411, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26415, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26419, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26408, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26412, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26416, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26420, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15980, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15984, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15988, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15992, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15981, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15985, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15989, 0, 0, 34, 16, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15993, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15982, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15986, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15990, 0, 0, 28, 28, 3, height, 4, 4, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15994, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15983, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15987, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15991, 0, 0, 16, 18, 3, height, 0, 16, height);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 15995, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26389, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26393, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26397, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26401, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26390, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26394, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26398, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26402, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26391, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26395, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26399, 0, 0, 28, 28, 3, height + 24, 4, 4, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26403, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26392, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26396, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26400, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26404, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_left_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	multi_dimension_rc_track_right_eighth_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_right_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	multi_dimension_rc_track_left_eighth_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

static void multi_dimension_rc_track_left_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16028, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16032, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16036, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16040, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16029, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16033, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16037, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16041, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16030, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16034, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16038, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16042, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16031, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16035, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16039, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16043, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26437, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26441, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26445, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26449, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26438, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26442, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26446, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26450, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26439, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26443, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26447, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26451, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26440, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26444, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26448, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26452, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16012, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16016, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16020, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16024, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16013, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16017, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16021, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16025, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16014, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16018, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16022, 0, 0, 28, 28, 0, height, 4, 4, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16026, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16015, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16019, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16023, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16027, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26421, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26425, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26429, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26433, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26422, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26426, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26430, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26434, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26423, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26427, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26431, 0, 0, 28, 28, 3, height + 24, 4, 4, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26435, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26424, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26428, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26432, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26436, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_left_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	multi_dimension_rc_track_right_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

static void multi_dimension_rc_track_right_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	multi_dimension_rc_track_left_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

static void multi_dimension_rc_track_diag_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16109, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16047, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16106, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16044, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16108, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16046, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16107, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16045, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26484, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26456, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26481, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26453, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26483, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26455, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
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
					metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26482, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26454, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16121, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16059, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16118, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16056, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16120, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16058, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16119, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16057, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26496, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26468, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26493, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26465, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26495, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26467, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
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
					metal_a_supports_paint_setup(11, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26494, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					metal_a_supports_paint_setup(11, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_a_supports_paint_setup(11, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26466, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					metal_a_supports_paint_setup(11, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16071, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16068, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16070, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 32, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16069, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 36, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 32, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 36, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26480, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26477, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26479, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 32, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26478, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 24);
				metal_b_supports_paint_setup(11, 0, 36, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 32, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 36, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16113, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16051, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16110, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16048, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16112, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16050, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16111, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16049, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26488, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26460, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26485, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26457, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26487, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26459, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					metal_a_supports_paint_setup(11, 1, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26486, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					metal_a_supports_paint_setup(11, 0, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_a_supports_paint_setup(11, 1, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26458, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					metal_a_supports_paint_setup(11, 0, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16063, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16060, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16062, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16061, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26472, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26469, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26471, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 16, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26470, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				metal_b_supports_paint_setup(11, 0, 16, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 16, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 16, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16067, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16064, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16066, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 21, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16065, -16, -16, 16, 16, 3, height, 0, 0, height);
				metal_b_supports_paint_setup(11, 0, 21, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 21, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 21, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26476, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26473, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26475, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 21, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26474, -16, -16, 16, 16, 3, height + 24, 0, 0, height + 56);
				metal_b_supports_paint_setup(11, 0, 21, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 21, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 21, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16117, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16055, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16114, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16052, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16116, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16054, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16115, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16053, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26492, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26464, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26489, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26461, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26491, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26463, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					metal_a_supports_paint_setup(11, 1, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26490, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					metal_a_supports_paint_setup(11, 0, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_a_supports_paint_setup(11, 1, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26462, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					metal_a_supports_paint_setup(11, 0, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_a_supports_paint_setup(11, 2, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_a_supports_paint_setup(11, 3, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16119, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16057, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16120, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16058, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16118, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16056, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16121, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16059, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26466, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26467, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26465, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26468, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				metal_a_supports_paint_setup(11, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16069, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16070, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16068, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 24, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16071, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 28, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 24, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 28, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26478, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26479, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26477, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 24, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26480, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				metal_b_supports_paint_setup(11, 0, 28, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 24, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 28, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16115, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16053, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16116, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16054, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16114, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16052, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16117, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16055, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26462, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26463, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26461, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26464, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16065, -16, -16, 16, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16066, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16064, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 17, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16067, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 17, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 17, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 17, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26474, -16, -16, 16, 16, 3, height + 24, 0, 0, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26475, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26473, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 17, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26476, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				metal_b_supports_paint_setup(11, 0, 17, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 17, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 17, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16061, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16062, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16060, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16063, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26470, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26471, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26469, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 8, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26472, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				metal_b_supports_paint_setup(11, 0, 8, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 8, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 8, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16111, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16049, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16112, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16050, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16110, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16048, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16113, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16051, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26458, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26459, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26457, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26460, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16079, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16076, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16080, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16078, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16077, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26504, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26501, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26503, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26502, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16084, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16081, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16083, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16085, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16082, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26508, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26505, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26507, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26506, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16082, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16083, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16085, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16081, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16084, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26506, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26507, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26505, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26508, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16077, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16078, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16076, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16080, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16079, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26502, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26503, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26501, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26504, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16099, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16096, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16100, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16098, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16097, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26520, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26517, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26519, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26518, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16104, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16101, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16103, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16105, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16102, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26524, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26521, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26523, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26522, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16089, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16086, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16090, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16088, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16087, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26512, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26509, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26511, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26510, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16094, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16091, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16093, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16095, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16092, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26516, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26513, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26515, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26514, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16092, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16093, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16095, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16091, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16094, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26514, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26515, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26513, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26516, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16087, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16088, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16086, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16090, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16089, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 4, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26510, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26511, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26509, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26512, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 42, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16102, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16103, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16105, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16101, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16104, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26522, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26523, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26521, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26524, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16097, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16098, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16096, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16100, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16099, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_b_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26518, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26519, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26517, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26520, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				metal_a_supports_paint_setup(11, 0, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 40, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16075, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16072, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16074, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16073, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26500, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26497, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26499, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26498, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_diag_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16073, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16074, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16072, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16075, -16, -16, 32, 32, 3, height, -16, -16, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26498, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26499, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26497, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26500, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				metal_a_supports_paint_setup(11, 0, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_left_flyer_twist_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26368, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26374, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26367, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26373, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26369, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26375, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26366, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26372, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26370, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26376, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26365, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26371, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26368, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26374, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26367, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26373, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26369, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26375, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26366, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26372, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26370, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26376, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26365, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26371, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_flyer_twist_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26380, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26386, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26379, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26385, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26381, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26387, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26378, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26384, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26382, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26388, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26377, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26383, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26380, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26386, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26379, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26385, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26381, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26387, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26378, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26384, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26382, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26388, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26377, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26383, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_left_flyer_twist_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26365, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26371, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26370, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26376, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26366, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26372, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26369, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26375, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26367, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26373, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26368, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26374, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26365, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26371, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26370, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26376, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26366, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26372, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26369, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26375, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26367, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26373, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26368, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26374, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_right_flyer_twist_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26377, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26383, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26382, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26388, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26378, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26384, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26381, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26387, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26379, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26385, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26380, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26386, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26377, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26383, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26382, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26388, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26378, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26384, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26381, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26387, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26379, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26385, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26380, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26386, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_6);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_6);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_multidim_inverted_flat_to_90_deg_quarter_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26539, 0, 0, 32, 20, 3, height + 16, 0, 6, height + 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26542, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26545, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26548, 0, 0, 32, 20, 3, height + 16, 0, 6, height + 16);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 32, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26538, 0, 0, 2, 20, 31, height + 16, 24, 6, height + 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26541, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26544, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26547, 0, 0, 2, 20, 31, height + 16, 24, 6, height + 16);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 80, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26537, 0, 0, 2, 20, 31, height + 16, 28, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26540, 0, 0, 2, 20, 31, height + 16, 0, 6, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26543, 0, 0, 2, 20, 31, height + 16, 0, 6, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26546, 0, 0, 2, 20, 31, height + 16, 29, 6, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16208, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16211, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16214, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16217, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 16, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16207, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16210, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16213, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16216, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16206, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16209, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16212, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16215, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 88, 0x20);
			break;
		case 3:
			break;
		}
	}
}

static void multi_dimension_rc_track_block_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16220, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16221, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26551, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26552, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 36, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

static void multi_dimension_rc_track_multidim_90_deg_up_to_inverted_flat_quarter_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16206, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16209, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16212, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16215, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 88, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16207, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16210, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16213, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16216, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16208, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16211, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16214, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16217, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 16, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26537, 0, 0, 2, 20, 31, height - 16, 28, 6, height - 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26540, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26543, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26546, 0, 0, 2, 20, 31, height - 16, 28, 6, height - 8);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26538, 0, 0, 2, 20, 31, height - 16, 24, 6, height - 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26541, 0, 0, 2, 20, 63, height - 16, 0, 6, height - 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26544, 0, 0, 2, 20, 63, height - 16, 0, 6, height - 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26547, 0, 0, 2, 20, 31, height - 16, 24, 6, height - 16);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26539, 0, 0, 32, 20, 3, height - 16, 0, 6, height - 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26542, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26545, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26548, 0, 0, 32, 20, 3, height - 16, 0, 6, height - 16);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

static void multi_dimension_rc_track_multidim_flat_to_90_deg_down_quarter_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26539, 0, 0, 32, 20, 3, height + 16, 0, 6, height + 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26542, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26545, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26548, 0, 0, 32, 20, 3, height + 16, 0, 6, height + 16);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 32, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26538, 0, 0, 2, 20, 31, height + 16, 24, 6, height + 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26541, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26544, 0, 0, 2, 20, 3, height + 16, 0, 6, height + 18);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26547, 0, 0, 2, 20, 31, height + 16, 24, 6, height + 16);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 80, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26537, 0, 0, 2, 20, 31, height + 16, 28, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26540, 0, 0, 2, 20, 31, height + 16, 0, 6, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26543, 0, 0, 2, 20, 31, height + 16, 0, 6, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26546, 0, 0, 2, 20, 31, height + 16, 29, 6, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16208, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16211, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16214, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16217, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 16, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16207, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16210, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16213, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16216, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16206, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16209, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16212, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16215, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 88, 0x20);
			break;
		case 3:
			break;
		}
	}
}

static void multi_dimension_rc_track_elem_255(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16206, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16209, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16212, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16215, 0, 0, 2, 20, 31, height, 4, 6, height + 8);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 88, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16207, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16210, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16213, 0, 0, 2, 20, 63, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16216, 0, 0, 2, 20, 31, height, -8, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 64, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16208, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16211, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16214, 0, 0, 2, 20, 31, height, 24, 6, height + 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16217, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 16, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26537, 0, 0, 2, 20, 31, height - 16, 28, 6, height - 8);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26540, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26543, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26546, 0, 0, 2, 20, 31, height - 16, 28, 6, height - 8);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26538, 0, 0, 2, 20, 31, height - 16, 24, 6, height - 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26541, 0, 0, 2, 20, 63, height - 16, 0, 6, height - 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26544, 0, 0, 2, 20, 63, height - 16, 0, 6, height - 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26547, 0, 0, 2, 20, 31, height - 16, 24, 6, height - 16);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26539, 0, 0, 32, 20, 3, height - 16, 0, 6, height - 16);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26542, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26545, 0, 0, 2, 20, 31, height - 16, 0, 6, height - 8);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26548, 0, 0, 32, 20, 3, height - 16, 0, 6, height - 16);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_6);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

TRACK_PAINT_FUNCTION get_track_paint_function_multi_dimension_rc(int trackType, int direction)
{
	switch (trackType) {
	case TRACK_ELEM_FLAT:
		return multi_dimension_rc_track_flat;
	case TRACK_ELEM_END_STATION:
	case TRACK_ELEM_BEGIN_STATION:
	case TRACK_ELEM_MIDDLE_STATION:
		return multi_dimension_rc_track_station;
	case TRACK_ELEM_25_DEG_UP:
		return multi_dimension_rc_track_25_deg_up;
	case TRACK_ELEM_60_DEG_UP:
		return multi_dimension_rc_track_60_deg_up;
	case TRACK_ELEM_FLAT_TO_25_DEG_UP:
		return multi_dimension_rc_track_flat_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_60_DEG_UP:
		return multi_dimension_rc_track_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_60_DEG_UP_TO_25_DEG_UP:
		return multi_dimension_rc_track_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_FLAT:
		return multi_dimension_rc_track_25_deg_up_to_flat;
	case TRACK_ELEM_25_DEG_DOWN:
		return multi_dimension_rc_track_25_deg_down;
	case TRACK_ELEM_60_DEG_DOWN:
		return multi_dimension_rc_track_60_deg_down;
	case TRACK_ELEM_FLAT_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_flat_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_60_DEG_DOWN:
		return multi_dimension_rc_track_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_60_DEG_DOWN_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_FLAT:
		return multi_dimension_rc_track_25_deg_down_to_flat;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES:
		return multi_dimension_rc_track_left_quarter_turn_5;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES:
		return multi_dimension_rc_track_right_quarter_turn_5;
	case TRACK_ELEM_FLAT_TO_LEFT_BANK:
		return multi_dimension_rc_track_flat_to_left_bank;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANK:
		return multi_dimension_rc_track_flat_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_FLAT:
		return multi_dimension_rc_track_left_bank_to_flat;
	case TRACK_ELEM_RIGHT_BANK_TO_FLAT:
		return multi_dimension_rc_track_right_bank_to_flat;
	case TRACK_ELEM_BANKED_LEFT_QUARTER_TURN_5_TILES:
		return multi_dimension_rc_track_banked_left_quarter_turn_5;
	case TRACK_ELEM_BANKED_RIGHT_QUARTER_TURN_5_TILES:
		return multi_dimension_rc_track_banked_right_quarter_turn_5;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_UP:
		return multi_dimension_rc_track_left_bank_to_25_deg_up;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_UP:
		return multi_dimension_rc_track_right_bank_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_LEFT_BANK:
		return multi_dimension_rc_track_25_deg_up_to_left_bank;
	case TRACK_ELEM_25_DEG_UP_TO_RIGHT_BANK:
		return multi_dimension_rc_track_25_deg_up_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_left_bank_to_25_deg_down;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_right_bank_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_LEFT_BANK:
		return multi_dimension_rc_track_25_deg_down_to_left_bank;
	case TRACK_ELEM_25_DEG_DOWN_TO_RIGHT_BANK:
		return multi_dimension_rc_track_25_deg_down_to_right_bank;
	case TRACK_ELEM_LEFT_BANK:
		return multi_dimension_rc_track_left_bank;
	case TRACK_ELEM_RIGHT_BANK:
		return multi_dimension_rc_track_right_bank;
	case TRACK_ELEM_S_BEND_LEFT:
		return multi_dimension_rc_track_s_bend_left;
	case TRACK_ELEM_S_BEND_RIGHT:
		return multi_dimension_rc_track_s_bend_right;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
		return multi_dimension_rc_track_left_quarter_turn_3;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
		return multi_dimension_rc_track_right_quarter_turn_3;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_BANK:
		return multi_dimension_rc_track_left_quarter_turn_3_bank;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_BANK:
		return multi_dimension_rc_track_right_quarter_turn_3_bank;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_SMALL:
		return multi_dimension_rc_track_left_half_banked_helix_up_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_SMALL:
		return multi_dimension_rc_track_right_half_banked_helix_up_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_SMALL:
		return multi_dimension_rc_track_left_half_banked_helix_down_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_SMALL:
		return multi_dimension_rc_track_right_half_banked_helix_down_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_LARGE:
		return multi_dimension_rc_track_left_half_banked_helix_up_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_LARGE:
		return multi_dimension_rc_track_right_half_banked_helix_up_large;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_LARGE:
		return multi_dimension_rc_track_left_half_banked_helix_down_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_LARGE:
		return multi_dimension_rc_track_right_half_banked_helix_down_large;
	case TRACK_ELEM_BRAKES:
		return multi_dimension_rc_track_brakes;
	case TRACK_ELEM_ON_RIDE_PHOTO:
		return multi_dimension_rc_track_on_ride_photo;
	case TRACK_ELEM_90_DEG_UP:
		return multi_dimension_rc_track_90_deg_up;
	case TRACK_ELEM_90_DEG_DOWN:
		return multi_dimension_rc_track_90_deg_down;
	case TRACK_ELEM_60_DEG_UP_TO_90_DEG_UP:
		return multi_dimension_rc_track_60_deg_up_to_90_deg_up;
	case TRACK_ELEM_90_DEG_DOWN_TO_60_DEG_DOWN:
		return multi_dimension_rc_track_90_deg_down_to_60_deg_down;
	case TRACK_ELEM_90_DEG_UP_TO_60_DEG_UP:
		return multi_dimension_rc_track_90_deg_up_to_60_deg_up;
	case TRACK_ELEM_60_DEG_DOWN_TO_90_DEG_DOWN:
		return multi_dimension_rc_track_60_deg_down_to_90_deg_down;
	case TRACK_ELEM_LEFT_EIGHTH_TO_DIAG:
		return multi_dimension_rc_track_left_eighth_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_DIAG:
		return multi_dimension_rc_track_right_eighth_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_TO_ORTHOGONAL:
		return multi_dimension_rc_track_left_eighth_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_ORTHOGONAL:
		return multi_dimension_rc_track_right_eighth_to_orthogonal;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_DIAG:
		return multi_dimension_rc_track_left_eighth_bank_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_DIAG:
		return multi_dimension_rc_track_right_eighth_bank_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_ORTHOGONAL:
		return multi_dimension_rc_track_left_eighth_bank_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_ORTHOGONAL:
		return multi_dimension_rc_track_right_eighth_bank_to_orthogonal;
	case TRACK_ELEM_DIAG_FLAT:
		return multi_dimension_rc_track_diag_flat;
	case TRACK_ELEM_DIAG_25_DEG_UP:
		return multi_dimension_rc_track_diag_25_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP:
		return multi_dimension_rc_track_diag_60_deg_up;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_UP:
		return multi_dimension_rc_track_diag_flat_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_60_DEG_UP:
		return multi_dimension_rc_track_diag_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP_TO_25_DEG_UP:
		return multi_dimension_rc_track_diag_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_FLAT:
		return multi_dimension_rc_track_diag_25_deg_up_to_flat;
	case TRACK_ELEM_DIAG_25_DEG_DOWN:
		return multi_dimension_rc_track_diag_25_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN:
		return multi_dimension_rc_track_diag_60_deg_down;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_diag_flat_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_60_DEG_DOWN:
		return multi_dimension_rc_track_diag_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_diag_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_FLAT:
		return multi_dimension_rc_track_diag_25_deg_down_to_flat;
	case TRACK_ELEM_DIAG_FLAT_TO_LEFT_BANK:
		return multi_dimension_rc_track_diag_flat_to_left_bank;
	case TRACK_ELEM_DIAG_FLAT_TO_RIGHT_BANK:
		return multi_dimension_rc_track_diag_flat_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_FLAT:
		return multi_dimension_rc_track_diag_left_bank_to_flat;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_FLAT:
		return multi_dimension_rc_track_diag_right_bank_to_flat;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_UP:
		return multi_dimension_rc_track_diag_left_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_UP:
		return multi_dimension_rc_track_diag_right_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_LEFT_BANK:
		return multi_dimension_rc_track_diag_25_deg_up_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_RIGHT_BANK:
		return multi_dimension_rc_track_diag_25_deg_up_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_diag_left_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_DOWN:
		return multi_dimension_rc_track_diag_right_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_LEFT_BANK:
		return multi_dimension_rc_track_diag_25_deg_down_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_RIGHT_BANK:
		return multi_dimension_rc_track_diag_25_deg_down_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK:
		return multi_dimension_rc_track_diag_left_bank;
	case TRACK_ELEM_DIAG_RIGHT_BANK:
		return multi_dimension_rc_track_diag_right_bank;
	case TRACK_ELEM_LEFT_FLYER_TWIST_UP:
		return multi_dimension_rc_track_left_flyer_twist_up;
	case TRACK_ELEM_RIGHT_FLYER_TWIST_UP:
		return multi_dimension_rc_track_right_flyer_twist_up;
	case TRACK_ELEM_LEFT_FLYER_TWIST_DOWN:
		return multi_dimension_rc_track_left_flyer_twist_down;
	case TRACK_ELEM_RIGHT_FLYER_TWIST_DOWN:
		return multi_dimension_rc_track_right_flyer_twist_down;
	case TRACK_ELEM_MULTIDIM_INVERTED_FLAT_TO_90_DEG_QUARTER_LOOP_DOWN:
		return multi_dimension_rc_track_multidim_inverted_flat_to_90_deg_quarter_loop_down;
	case TRACK_ELEM_BLOCK_BRAKES:
		return multi_dimension_rc_track_block_brakes;
	case TRACK_ELEM_MULTIDIM_90_DEG_UP_TO_INVERTED_FLAT_QUARTER_LOOP:
		return multi_dimension_rc_track_multidim_90_deg_up_to_inverted_flat_quarter_loop;
	case TRACK_ELEM_MULTIDIM_FLAT_TO_90_DEG_DOWN_QUARTER_LOOP:
		return multi_dimension_rc_track_multidim_flat_to_90_deg_down_quarter_loop;
	case TRACK_ELEM_255:
		return multi_dimension_rc_track_elem_255;
	}
	return NULL;
}
