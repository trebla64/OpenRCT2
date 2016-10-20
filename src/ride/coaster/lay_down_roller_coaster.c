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

/** rct2: 0x0082491C */
static void lay_down_rc_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16226, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16227, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16228, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16229, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16224, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16225, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26557, 0, 0, 32, 20, 1, height + 24, 0, 6, height + 22);
				break;
			case 1:
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26558, 0, 0, 32, 20, 1, height + 24, 0, 6, height + 22);
				break;
			}
		} else {
			switch (direction) {
			case 0:
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26555, 0, 0, 32, 20, 1, height + 24, 0, 6, height + 22);
				break;
			case 1:
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26556, 0, 0, 32, 20, 1, height + 24, 0, 6, height + 22);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x00824B8C, 0x00824B9C, 0x00824BAC */
static void lay_down_rc_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (track_element_is_inverted(mapElement)) {
		static const uint32 imageIds[4][3] = {
			{ SPR_STATION_BASE_C_SW_NE, 26557, SPR_STATION_INVERTED_BAR_A_SW_NE },
			{ SPR_STATION_BASE_C_NW_SE, 26558, SPR_STATION_INVERTED_BAR_A_NW_SE },
			{ SPR_STATION_BASE_C_SW_NE, 26557, SPR_STATION_INVERTED_BAR_A_SW_NE },
			{ SPR_STATION_BASE_C_NW_SE, 26558, SPR_STATION_INVERTED_BAR_A_NW_SE },
		};

		sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_MISC], 0, 0, 32, 28, 1, height, 0, 2, height);
		sub_98197C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
		sub_98199C_rotated(direction, imageIds[direction][2] | gTrackColours[SCHEME_SUPPORTS], 0, 6, 32, 20, 1, height + 24, 0, 6, height + 24);
		track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], 11);
		track_paint_util_draw_station_inverted(rideIndex, trackSequence, direction, height, mapElement, STATION_VARIANT_1);
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_9);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		static const uint32 imageIds[4][3] = {
			{ 16236, 16232, SPR_STATION_BASE_A_SW_NE },
			{ 16237, 16233, SPR_STATION_BASE_A_NW_SE },
			{ 16236, 16232, SPR_STATION_BASE_A_SW_NE },
			{ 16237, 16233, SPR_STATION_BASE_A_NW_SE },
		};

		if (mapElement->properties.track.type == TRACK_ELEM_END_STATION) {
			sub_98197C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 1, height, 0, 6, height + 3);
		} else {
			sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 1, height, 0, 6, height + 3);
		}
		sub_98196C_rotated(direction, imageIds[direction][2] | gTrackColours[SCHEME_MISC], 0, 0, 32, 32, 1, height);
		track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], 11);
		track_paint_util_draw_station_2(rideIndex, trackSequence, direction, height, mapElement, 9, 11);
	}
}

/** rct2: 0x0082492C */
static void lay_down_rc_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16314, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16315, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16316, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16317, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16286, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16287, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16288, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16289, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
	} else {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26621, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26622, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26623, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26624, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26569, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26570, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26571, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26572, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 40);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 51, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 51, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 51, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 51, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_2);
		}
		paint_util_set_general_support_height(height + 56, 0x20);
	}
}

/** rct2: 0x0082493C */
static void lay_down_rc_track_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16330, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16331, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16332, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16333, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 32, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16302, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16303, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16304, 0, 0, 32, 1, 98, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16305, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 32, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 56, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26585, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 88);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26586, 0, 0, 32, 2, 81, height + 24, 0, 4, height + 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26587, 0, 0, 32, 2, 81, height + 24, 0, 4, height + 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26588, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 88);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 56, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
	}
}

/** rct2: 0x0082494C */
static void lay_down_rc_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16306, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16307, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16308, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16309, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16278, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16279, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16280, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16281, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26613, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26614, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26615, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26616, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26561, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26562, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26563, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26564, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
	}
}

/** rct2: 0x0082495C */
static void lay_down_rc_track_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16318, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16319, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16322, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16320, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16323, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16321, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16290, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16291, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16294, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16292, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16295, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16293, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26573, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26577, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26574, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26578, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26575, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26576, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
	}
}

/** rct2: 0x0082496C */
static void lay_down_rc_track_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16324, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16325, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16328, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16326, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16329, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16327, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16296, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16297, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16300, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16298, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16301, 0, 0, 32, 1, 66, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16299, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26579, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26583, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26580, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26584, 0, 0, 32, 10, 49, height + 24, 0, 10, height + 6);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26581, 0, 0, 32, 2, 49, height + 24, 0, 4, height + 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26582, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 56);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 65, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 65, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 65, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 65, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 24, TUNNEL_2);
		}
		paint_util_set_general_support_height(height + 72, 0x20);
	}
}

/** rct2: 0x0082497C */
static void lay_down_rc_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16310, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16311, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16312, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16313, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16282, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16283, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16284, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16285, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			}
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	} else {
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26617, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26618, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26619, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26620, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26565, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26566, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26567, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26568, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
		}
		paint_util_set_general_support_height(height + 40, 0x20);
	}
}

/** rct2: 0x0082498C */
static void lay_down_rc_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x0082499C */
static void lay_down_rc_track_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008249AC */
static void lay_down_rc_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008249BC */
static void lay_down_rc_track_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_60_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008249CC */
static void lay_down_rc_track_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_25_deg_up_to_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008249DC */
static void lay_down_rc_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008249EC */
static void lay_down_rc_track_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16343, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16348, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16353, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16338, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16342, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16347, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16352, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16337, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16341, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16346, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16351, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16336, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16340, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16345, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16350, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16335, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16339, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16344, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16349, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16334, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26694, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26699, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26704, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26689, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26693, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26698, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26703, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26688, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26692, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26697, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26702, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26687, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26691, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26696, 0, 0, 16, 32, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26701, 0, 0, 16, 32, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26686, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26690, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26695, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26700, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26685, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x008249FC */
static void lay_down_rc_track_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	lay_down_rc_track_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824A0C */
static void lay_down_rc_track_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16238, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16246, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16239, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16247, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16240, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16241, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26657, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26658, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26659, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26660, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x00824A1C */
static void lay_down_rc_track_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16242, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16243, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16244, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16248, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16245, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16249, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26661, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26662, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26663, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26664, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x00824A2C */
static void lay_down_rc_track_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16244, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16248, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16245, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16249, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16242, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16243, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26663, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26664, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26661, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26662, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x00824A3C */
static void lay_down_rc_track_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16240, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16241, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16238, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16246, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16239, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16247, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26659, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26660, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26657, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26658, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x00824A4C */
static void lay_down_rc_track_banked_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16363, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16374, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16368, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16373, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16358, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16362, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16367, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16372, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16357, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16361, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16366, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16371, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16356, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16360, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16365, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16370, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16355, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16359, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16364, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16369, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16375, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16354, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26738, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26743, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26748, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26733, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26737, 0, 0, 32, 16, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26742, 0, 0, 32, 16, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26747, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26732, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26736, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26741, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26746, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26731, 0, 0, 16, 16, 3, height + 24);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26735, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26740, 0, 0, 16, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26745, 0, 0, 16, 32, 3, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26730, 0, 0, 16, 32, 3, height + 24, 16, 0, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26734, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26739, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26744, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26729, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824A5C */
static void lay_down_rc_track_banked_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	lay_down_rc_track_banked_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824A6C */
static void lay_down_rc_track_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16250, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16254, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16251, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16255, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16252, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16253, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26665, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26666, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26667, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26668, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
	}
}

/** rct2: 0x00824A7C */
static void lay_down_rc_track_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16256, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16257, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16258, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16260, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16259, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16261, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 3, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26669, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26670, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26671, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26672, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_2);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
	}
}

/** rct2: 0x00824A8C */
static void lay_down_rc_track_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16262, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16266, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16263, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16267, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16264, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16265, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26673, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26674, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26675, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26676, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
		}
		paint_util_set_general_support_height(height + 40, 0x20);
	}
}

/** rct2: 0x00824A9C */
static void lay_down_rc_track_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16268, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16269, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16270, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16272, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16271, 0, 0, 32, 20, 3, height, 0, 6, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16273, 0, 0, 32, 1, 34, height, 0, 27, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26677, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26678, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26679, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26680, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 32);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 6, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 8, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 7, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 5, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_0);
		} else {
			paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_12);
		}
		paint_util_set_general_support_height(height + 40, 0x20);
	}
}

/** rct2: 0x00824AAC */
static void lay_down_rc_track_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_25_deg_up_to_right_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x00824ABC */
static void lay_down_rc_track_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_25_deg_up_to_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x00824ACC */
static void lay_down_rc_track_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_right_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x00824ADC */
static void lay_down_rc_track_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_left_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x00824AEC */
static void lay_down_rc_track_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16274, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16275, 0, 0, 32, 1, 26, height, 0, 27, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16276, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16277, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26681, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26682, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26683, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26684, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x00824AFC */
static void lay_down_rc_track_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x00824B0C */
static void lay_down_rc_track_left_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16510, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16515, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16520, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16525, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16511, 0, 0, 32, 16, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16516, 0, 0, 32, 16, 3, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16521, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16526, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16512, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16517, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16522, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16527, 0, 0, 16, 16, 3, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16513, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16518, 0, 0, 16, 32, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16523, 0, 0, 16, 32, 3, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16528, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16514, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16519, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16524, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16529, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 3:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26949, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26954, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26959, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26964, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26950, 0, 0, 32, 16, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26955, 0, 0, 32, 16, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26960, 0, 16, 32, 16, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26965, 0, 16, 32, 16, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26951, 0, 16, 16, 16, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26956, 16, 16, 16, 16, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26961, 16, 0, 16, 16, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26966, 0, 0, 16, 16, 3, height + 24);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26952, 16, 0, 16, 32, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26957, 0, 0, 16, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26962, 0, 0, 16, 32, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26967, 16, 0, 16, 32, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26953, 6, 0, 20, 32, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26958, 6, 0, 20, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26963, 6, 0, 20, 32, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26968, 6, 0, 20, 32, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 3:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824B1C */
static void lay_down_rc_track_right_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16490, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16495, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16500, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16505, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16491, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16496, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16501, 0, 0, 32, 16, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16506, 0, 0, 32, 16, 3, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16492, 0, 0, 16, 16, 3, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16497, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16502, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16507, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16493, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16498, 0, 0, 16, 32, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16503, 0, 0, 16, 32, 3, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16508, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16494, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16499, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16504, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16509, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26929, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26934, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26939, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26944, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26930, 0, 16, 32, 16, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26935, 0, 16, 32, 16, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26940, 0, 0, 32, 16, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26945, 0, 0, 32, 16, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26931, 0, 0, 16, 16, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26936, 16, 0, 16, 16, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26941, 16, 16, 16, 16, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26946, 0, 16, 16, 16, 3, height + 24);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26932, 16, 0, 16, 32, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26937, 0, 0, 16, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26942, 0, 0, 16, 32, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26947, 16, 0, 16, 32, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26933, 6, 0, 20, 32, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26938, 6, 0, 20, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26943, 6, 0, 20, 32, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26948, 6, 0, 20, 32, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 43, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824B2C */
static void lay_down_rc_track_left_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	lay_down_rc_track_right_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x00824B3C */
static void lay_down_rc_track_right_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	lay_down_rc_track_left_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824B4C */
static void lay_down_rc_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16402, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16406, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16405, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16409, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16403, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16407, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16404, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16408, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16404, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16408, 0, 0, 32, 26, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16403, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16407, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 6, 1, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16405, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16409, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16402, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16406, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26641, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26645, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26644, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26648, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26642, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26646, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26643, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26647, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 5, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 6, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26643, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26647, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26642, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26646, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			switch (direction) {
			case 2:
				metal_a_supports_paint_setup(11, 5, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 6, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26644, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26648, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26641, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26645, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824B5C */
static void lay_down_rc_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16410, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16414, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16413, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16417, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16411, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16415, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16412, 0, 0, 32, 26, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16416, 0, 0, 32, 26, 3, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16412, 0, 0, 32, 26, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16416, 0, 0, 32, 26, 3, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16411, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16415, 0, 0, 32, 26, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16413, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16417, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16410, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16414, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26649, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26653, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26652, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26656, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26650, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26654, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26651, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26655, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 8, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 7, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26651, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26655, 0, 0, 32, 26, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26650, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26654, 0, 0, 32, 26, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 2:
				metal_a_supports_paint_setup(11, 8, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 7, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26652, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26656, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26649, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26653, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824B6C */
static void lay_down_rc_track_left_vertical_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16562, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16570, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16569, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16577, 0, 6, 32, 20, 7, height);
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16563, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16571, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16568, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16576, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16564, 16, 0, 3, 16, 119, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16572, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16567, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16575, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16565, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16573, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16566, 0, 16, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16574, 0, 16, 32, 16, 3, height + 32);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16566, 0, 16, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16574, 0, 16, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16565, 0, 0, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16573, 0, 0, 32, 16, 3, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16567, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16575, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16564, 16, 0, 3, 16, 119, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16572, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 8:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16568, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16576, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16563, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16571, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 9:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16569, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16577, 0, 6, 32, 20, 7, height);
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16562, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16570, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height - 8, TUNNEL_1);
				break;
			case 2:
				paint_util_push_tunnel_left(height - 8, TUNNEL_1);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16562, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16570, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16569, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16577, 0, 6, 32, 20, 7, height);
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16563, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16571, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16568, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16576, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16564, 16, 0, 3, 16, 119, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16572, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16567, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16575, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16565, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16573, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16566, 0, 16, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16574, 0, 16, 32, 16, 3, height + 32);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16566, 0, 16, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16574, 0, 16, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16565, 0, 0, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16573, 0, 0, 32, 16, 3, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16567, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16575, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16564, 16, 0, 3, 16, 119, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16572, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 8:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16568, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16576, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16563, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16571, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 9:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16569, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16577, 0, 6, 32, 20, 7, height);
				metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16562, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16570, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height - 8, TUNNEL_1);
				break;
			case 2:
				paint_util_push_tunnel_left(height - 8, TUNNEL_1);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824B7C */
static void lay_down_rc_track_right_vertical_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16593, 0, 6, 32, 20, 7, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16585, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16586, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16578, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16592, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16584, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16587, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16579, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16591, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16583, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16588, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16580, 16, 0, 2, 16, 119, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16590, 0, 16, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16582, 0, 16, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16589, 0, 0, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16581, 0, 0, 32, 16, 3, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16589, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16581, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16590, 0, 16, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16582, 0, 16, 32, 16, 3, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16588, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16580, 16, 0, 2, 16, 119, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16591, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16583, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 8:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16587, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16579, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16592, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16584, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 9:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16586, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16578, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16593, 0, 6, 32, 20, 7, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16585, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height - 8, TUNNEL_1);
				break;
			case 2:
				paint_util_push_tunnel_left(height - 8, TUNNEL_1);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16593, 0, 6, 32, 20, 7, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16585, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16586, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16578, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16592, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16584, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16587, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16579, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16591, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16583, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16588, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16580, 16, 0, 2, 16, 119, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16590, 0, 16, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16582, 0, 16, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16589, 0, 0, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16581, 0, 0, 32, 16, 3, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16589, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16581, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16590, 0, 16, 32, 16, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16582, 0, 16, 32, 16, 3, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16588, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16580, 16, 0, 2, 16, 119, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16591, 16, 16, 2, 16, 119, height, 16, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16583, 10, 16, 4, 16, 119, height, 10, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 8:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16587, 0, 14, 32, 2, 63, height);
				metal_a_supports_paint_setup(11, 4, 12, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16579, 0, 0, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16592, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16584, 0, 6, 32, 26, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 9:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16586, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16578, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16593, 0, 6, 32, 20, 7, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16585, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height - 8, TUNNEL_1);
				break;
			case 2:
				paint_util_push_tunnel_left(height - 8, TUNNEL_1);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824BBC */
static void lay_down_rc_track_left_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16381, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16384, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16387, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16378, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16380, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16383, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16386, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16377, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16379, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16382, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16385, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16376, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26710, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26713, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26716, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26707, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26709, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26712, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26715, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26706, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26708, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26711, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26714, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26705, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824BCC */
static void lay_down_rc_track_right_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	lay_down_rc_track_left_quarter_turn_3(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824BDC */
static void lay_down_rc_track_left_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16393, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16400, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16396, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16399, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16390, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16392, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16395, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16398, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16389, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16391, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16394, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16397, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16401, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16388, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
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
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26722, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26725, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26728, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26719, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26721, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26724, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26727, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26718, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26720, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26723, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26726, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26717, 0, 0, 20, 32, 3, height + 24, 6, 0, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824BEC */
static void lay_down_rc_track_right_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	lay_down_rc_track_left_quarter_turn_3_bank(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824BFC */
static void lay_down_rc_track_left_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16541, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16543, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16545, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16539, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16540, 6, 0, 20, 32, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16542, 6, 0, 20, 32, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16544, 6, 0, 20, 32, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16538, 6, 0, 20, 32, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 3:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26924, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26926, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26928, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26922, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26923, 6, 0, 20, 32, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26925, 6, 0, 20, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26927, 6, 0, 20, 32, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26921, 6, 0, 20, 32, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 3:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C0C */
static void lay_down_rc_track_right_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16530, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16532, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16534, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16536, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16531, 6, 0, 20, 32, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16533, 6, 0, 20, 32, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16535, 6, 0, 20, 32, 3, height);
				metal_a_supports_paint_setup(11, 4, 10, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16537, 6, 0, 20, 32, 3, height);
				metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26913, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26915, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26917, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26919, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26914, 6, 0, 20, 32, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26916, 6, 0, 20, 32, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26918, 6, 0, 20, 32, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26920, 6, 0, 20, 32, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 41, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_2);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_2);
				break;
			}
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C1C */
static void lay_down_rc_track_left_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	lay_down_rc_track_right_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x00824C2C */
static void lay_down_rc_track_right_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	lay_down_rc_track_left_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824C9C */
static void lay_down_rc_track_left_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16481, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16488, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16484, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16487, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16478, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16480, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16483, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16486, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16477, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16479, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16482, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16485, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16489, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16476, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16478, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16481, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16488, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16484, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16487, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16477, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16480, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16483, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16486, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16476, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16479, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16482, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16485, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16489, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16481, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16488, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16484, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16487, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16478, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16480, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16483, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16486, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16477, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16479, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16482, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16485, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16489, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16476, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16478, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16481, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16488, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16484, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16487, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16477, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16480, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16483, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16486, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16476, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16479, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16482, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16485, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16489, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824CAC */
static void lay_down_rc_track_right_half_banked_helix_up_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16462, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16465, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16468, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16471, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16475, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16463, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16466, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16469, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16472, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16464, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16467, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16474, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16470, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16473, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16465, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16468, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16471, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16475, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16462, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16466, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16469, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16472, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16463, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16467, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16474, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16470, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16473, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16464, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16462, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16465, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16468, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16471, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16475, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16463, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16466, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16469, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16472, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16464, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16467, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16474, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16470, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16473, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16465, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16468, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16471, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16475, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16462, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 2, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16466, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16469, 0, 0, 16, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16472, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16463, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 7:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16467, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16474, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16470, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16473, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16464, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 6, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824CBC */
static void lay_down_rc_track_left_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	lay_down_rc_track_right_half_banked_helix_up_small(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x00824CCC */
static void lay_down_rc_track_right_half_banked_helix_down_small(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 4) {
		trackSequence -= 4;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	lay_down_rc_track_left_half_banked_helix_up_small(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824CDC */
static void lay_down_rc_track_left_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16449, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16460, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16454, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16459, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16444, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16448, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16453, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16458, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16443, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16447, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16452, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16457, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16442, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16446, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16451, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16456, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16441, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16445, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16450, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16455, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16461, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16440, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16444, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16449, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16460, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16454, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16459, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16443, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16448, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16453, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16458, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16442, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16447, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16452, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16457, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16441, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16446, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16451, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16456, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16440, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16445, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16450, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16455, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16461, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16449, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16460, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16454, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16459, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16444, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16448, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16453, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16458, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16443, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16447, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16452, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16457, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16442, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16446, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16451, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16456, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16441, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16445, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16450, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16455, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16461, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16440, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16444, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16449, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16460, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16454, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16459, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16443, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16448, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16453, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16458, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16442, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16447, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16452, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16457, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16441, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16446, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16451, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16456, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16440, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16445, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16450, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16455, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16461, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824CEC */
static void lay_down_rc_track_right_half_banked_helix_up_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16418, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16423, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16428, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16433, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16439, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16419, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16424, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16429, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16434, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16420, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16425, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16430, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16435, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16421, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16426, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16431, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16436, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16422, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16427, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16438, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16432, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16437, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16423, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16428, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16433, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16439, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16418, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16424, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16429, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16434, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16419, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16425, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16430, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16435, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16420, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16426, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16431, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16436, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16421, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16427, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16438, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16432, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16437, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16422, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16418, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16423, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16428, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16433, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16439, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16419, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16424, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16429, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16434, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16420, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16425, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16430, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16435, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16421, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16426, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16431, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16436, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 6:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16422, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16427, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16438, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16432, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16437, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16423, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16428, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16433, 0, 0, 20, 32, 3, height, 6, 0, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16439, 0, 0, 1, 32, 26, height, 27, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16418, 0, 0, 20, 32, 3, height, 6, 0, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 1, height, gTrackColours[SCHEME_SUPPORTS]);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16424, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16429, 0, 0, 16, 32, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16434, 0, 0, 16, 32, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16419, 0, 0, 16, 32, 3, height, 16, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 10:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16425, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16430, 0, 0, 16, 16, 1, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16435, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16420, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16426, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16431, 0, 0, 32, 16, 1, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16436, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16421, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 13:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16427, 0, 0, 32, 20, 3, height, 0, 6, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16438, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16432, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16437, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16422, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 7, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824CFC */
static void lay_down_rc_track_left_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction - 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	lay_down_rc_track_right_half_banked_helix_up_large(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x00824D0C */
static void lay_down_rc_track_right_half_banked_helix_down_large(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (trackSequence >= 7) {
		trackSequence -= 7;
		direction = (direction + 1) & 3;
	}
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	lay_down_rc_track_left_half_banked_helix_up_large(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824D3C */
static void lay_down_rc_track_left_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16555, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16559, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16556, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16560, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16557, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16561, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16554, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16558, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		}
		switch (direction) {
		case 0:
			paint_util_push_tunnel_left(height - 8, TUNNEL_2);
			break;
		case 2:
			paint_util_push_tunnel_right(height + 56, TUNNEL_1);
			break;
		case 3:
			paint_util_push_tunnel_right(height - 8, TUNNEL_1);
			paint_util_push_tunnel_left(height + 56, TUNNEL_1);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26910, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26906, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26911, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26907, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26912, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26908, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26909, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26905, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		}
		switch (direction) {
		case 0:
			paint_util_push_tunnel_left(height - 8, TUNNEL_2);
			break;
		case 2:
			paint_util_push_tunnel_right(height + 56, TUNNEL_1);
			break;
		case 3:
			paint_util_push_tunnel_right(height - 8, TUNNEL_1);
			paint_util_push_tunnel_left(height + 56, TUNNEL_1);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
	}
}

/** rct2: 0x00824D1C */
static void lay_down_rc_track_right_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16546, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16550, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16547, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16551, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16548, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16552, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16549, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16553, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		}
		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 56, TUNNEL_1);
			paint_util_push_tunnel_left(height - 8, TUNNEL_1);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 56, TUNNEL_2);
			break;
		case 3:
			paint_util_push_tunnel_right(height - 8, TUNNEL_1);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26901, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26897, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26902, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26898, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26903, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26899, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26904, 0, 0, 28, 28, 3, height, 2, 2, height);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26900, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
			break;
		}
		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 56, TUNNEL_1);
			paint_util_push_tunnel_left(height - 8, TUNNEL_1);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 56, TUNNEL_2);
			break;
		case 3:
			paint_util_push_tunnel_right(height - 8, TUNNEL_1);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 104, 0x20);
	}
}

/** rct2: 0x00824D2C */
static void lay_down_rc_track_left_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_right_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x00824D4C */
static void lay_down_rc_track_right_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_left_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x00824D5C */
static void lay_down_rc_track_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16230, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16231, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		}
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26559, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26560, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

/** rct2: 0x00824D6C */
static void lay_down_rc_track_on_ride_photo(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16224, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 1:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16225, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 2:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16224, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		case 3:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16225, 0, 0, 32, 20, 0, height, 0, 6, height + 3);
			break;
		}
		track_paint_util_onride_photo_paint(direction, height + 3, mapElement);
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
	} else {
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26555, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 1:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26556, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 2:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26555, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 3:
			sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
			metal_a_supports_paint_setup(11, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			metal_a_supports_paint_setup(11, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26556, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		}
		track_paint_util_onride_photo_paint(direction, height + 3, mapElement);
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
	}
}

/** rct2: 0x00824D8C */
static void lay_down_rc_track_left_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16740, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16744, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16748, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16752, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16741, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16745, 0, 0, 34, 16, 3, height, 0, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16749, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16753, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16742, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16746, 0, 0, 16, 16, 3, height, 16, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16750, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16754, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16743, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16747, 0, 0, 16, 18, 3, height, 0, 16, height);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16751, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16755, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26765, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26769, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26773, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26777, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26766, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26770, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26774, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26778, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26767, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26771, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26775, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26779, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26768, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26772, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26776, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26780, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824D9C */
static void lay_down_rc_track_right_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16724, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16728, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16732, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16736, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16725, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16729, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16733, 0, 0, 34, 16, 3, height, 0, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16737, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16726, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16730, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16734, 0, 0, 28, 28, 3, height, 4, 4, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16738, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16727, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16731, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16735, 0, 0, 16, 18, 3, height, 0, 16, height);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16739, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26749, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26753, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26757, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26761, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26750, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26754, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26758, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26762, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26751, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26755, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26759, 0, 0, 28, 28, 3, height + 24, 4, 4, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26763, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26752, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26756, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26760, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26764, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824DAC */
static void lay_down_rc_track_left_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	lay_down_rc_track_right_eighth_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x00824DBC */
static void lay_down_rc_track_right_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	lay_down_rc_track_left_eighth_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

/** rct2: 0x00824DCC */
static void lay_down_rc_track_left_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16772, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16776, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16780, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16784, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16773, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16777, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16781, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16785, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16774, 0, 0, 16, 16, 3, height, 0, 16, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16778, 0, 0, 16, 16, 0, height, 16, 16, height + 27);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16782, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16786, 0, 0, 16, 16, 3, height, 0, 0, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16775, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16779, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16783, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16787, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26853, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26857, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26861, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26865, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26854, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26858, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26862, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26866, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26855, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26859, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26863, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26867, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26856, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26860, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26864, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26868, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824DDC */
static void lay_down_rc_track_right_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16756, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16760, 0, 0, 32, 20, 3, height, 0, 6, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16764, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16768, 0, 0, 32, 1, 26, height, 0, 27, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16757, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16761, 0, 0, 32, 16, 3, height, 0, 16, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16765, 0, 0, 34, 16, 0, height, 0, 0, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16769, 0, 0, 32, 16, 3, height, 0, 0, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16758, 0, 0, 16, 16, 3, height, 0, 0, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16762, 0, 0, 16, 16, 3, height, 16, 0, height);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16766, 0, 0, 28, 28, 0, height, 4, 4, height + 27);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16770, 0, 0, 16, 16, 3, height, 0, 16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16759, 0, 0, 16, 16, 3, height, 16, 0, height);
				metal_a_supports_paint_setup(11, 1, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16763, 0, 0, 16, 16, 3, height, 0, 0, height);
				metal_a_supports_paint_setup(11, 0, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16767, 0, 0, 16, 18, 0, height, 0, 16, height + 27);
				metal_a_supports_paint_setup(11, 2, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16771, 0, 0, 16, 16, 3, height, 16, 16, height);
				metal_a_supports_paint_setup(11, 3, 0, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26837, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26841, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26845, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26849, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26838, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26842, 0, 0, 32, 16, 3, height + 24, 0, 16, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26846, 0, 0, 34, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26850, 0, 0, 32, 16, 3, height + 24, 0, 0, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26839, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26843, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26847, 0, 0, 28, 28, 3, height + 24, 4, 4, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26851, 0, 0, 16, 16, 3, height + 24, 0, 16, height + 22);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26840, 0, 0, 16, 16, 3, height + 24, 16, 0, height + 22);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26844, 0, 0, 16, 16, 3, height + 24, 0, 0, height + 22);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26848, 0, 0, 16, 18, 3, height + 24, 0, 16, height + 22);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26852, 0, 0, 16, 16, 3, height + 24, 16, 16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824DEC */
static void lay_down_rc_track_left_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	lay_down_rc_track_right_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x00824DFC */
static void lay_down_rc_track_right_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	lay_down_rc_track_left_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

/** rct2: 0x00824D7C */
static void lay_down_rc_track_diag_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16699, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16637, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16696, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16634, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16698, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16636, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16697, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16635, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26812, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26784, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26809, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26781, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26811, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26783, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26810, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			} else {
				switch (direction) {
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26782, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
					break;
				}
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E2C */
static void lay_down_rc_track_diag_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16711, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16649, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16708, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16646, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16710, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16648, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16709, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16647, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26824, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26796, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26821, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26793, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26823, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26795, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26822, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			} else {
				switch (direction) {
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26794, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
					break;
				}
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E8C */
static void lay_down_rc_track_diag_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16723, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16661, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16720, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16658, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16722, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16660, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 32, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16721, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 36, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 32, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 36, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 32, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16659, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 36, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 32, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 36, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26808, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26805, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26807, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26806, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 32, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_b_supports_paint_setup(11, 0, 36, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 32, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 36, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E0C */
static void lay_down_rc_track_diag_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16703, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16641, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16700, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16638, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16702, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16640, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16701, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16639, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26816, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26788, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26813, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26785, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26815, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26787, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26814, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26786, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E6C */
static void lay_down_rc_track_diag_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16715, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16653, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16712, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16650, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16714, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16652, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16713, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16651, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 16, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26800, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26797, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26799, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26798, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 16, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_b_supports_paint_setup(11, 0, 16, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 16, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 16, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E7C */
static void lay_down_rc_track_diag_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16719, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16657, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16716, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16654, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16718, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16656, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16717, -16, -16, 16, 16, 3, height, 0, 0, height);
					metal_b_supports_paint_setup(11, 0, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16655, -16, -16, 16, 16, 3, height, 0, 0, height);
					metal_b_supports_paint_setup(11, 0, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 21, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26804, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26801, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26803, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26802, -16, -16, 16, 16, 3, height + 24, 0, 0, height + 56);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 21, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_b_supports_paint_setup(11, 0, 21, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 21, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 21, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E1C */
static void lay_down_rc_track_diag_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16707, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16645, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16704, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16642, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16706, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16644, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16705, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16643, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26820, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26792, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26817, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26789, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26819, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26791, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26818, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			} else {
				switch (direction) {
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26790, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
					break;
				}
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E5C */
static void lay_down_rc_track_diag_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16709, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16647, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16710, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16648, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16708, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16646, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16711, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16649, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26794, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26795, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26793, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26796, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 40);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 45, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824EBC */
static void lay_down_rc_track_diag_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16721, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16659, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16722, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16660, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16720, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16658, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 24, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16723, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 28, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 24, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 28, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 24, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16661, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 28, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 24, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 28, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26806, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26807, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26805, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26808, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 88);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 24, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_b_supports_paint_setup(11, 0, 28, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 24, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 28, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 104, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E3C */
static void lay_down_rc_track_diag_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16705, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16643, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16706, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16644, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16704, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16642, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16707, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16645, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26790, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26791, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26789, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26792, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E9C */
static void lay_down_rc_track_diag_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16717, -16, -16, 16, 16, 3, height, 0, 0, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16655, -16, -16, 16, 16, 3, height, 0, 0, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16718, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16656, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16716, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16654, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16719, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					metal_b_supports_paint_setup(11, 1, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16657, -16, -16, 32, 32, 3, height, -16, -16, height);
					metal_b_supports_paint_setup(11, 0, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 2:
					metal_b_supports_paint_setup(11, 2, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 3:
					metal_b_supports_paint_setup(11, 3, 17, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				}
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26802, -16, -16, 16, 16, 3, height + 24, 0, 0, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26803, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26801, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26804, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 17, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_b_supports_paint_setup(11, 0, 17, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 17, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 17, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824EAC */
static void lay_down_rc_track_diag_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16713, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16651, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16714, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16652, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16712, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16650, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					metal_b_supports_paint_setup(11, 1, 8, height, gTrackColours[SCHEME_SUPPORTS]);
					break;
				case 1:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16715, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16653, -16, -16, 32, 32, 3, height, -16, -16, height);
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
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26798, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26799, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26797, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26800, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 56);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_b_supports_paint_setup(11, 1, 8, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_b_supports_paint_setup(11, 0, 8, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_b_supports_paint_setup(11, 2, 8, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_b_supports_paint_setup(11, 3, 8, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824E4C */
static void lay_down_rc_track_diag_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			if (track_element_is_lift_hill(mapElement)) {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16701, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 3:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16639, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16702, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 0:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16640, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16700, -16, -16, 32, 32, 3, height, -16, -16, height);
					break;
				}
			} else {
				switch (direction) {
				case 2:
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16638, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16703, -16, -16, 32, 32, 3, height, -16, -16, height);
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
					sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16641, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26786, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26787, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26785, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26788, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824EEC */
static void lay_down_rc_track_diag_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16669, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16666, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16670, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16668, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16667, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26876, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26873, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26875, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26874, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824EFC */
static void lay_down_rc_track_diag_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16674, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16671, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16673, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16675, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16672, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26880, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26877, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26879, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26878, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F0C */
static void lay_down_rc_track_diag_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16672, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16673, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16675, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16671, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16674, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26878, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26879, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26877, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26880, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F1C */
static void lay_down_rc_track_diag_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16667, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16668, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16666, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16670, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16669, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26874, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26875, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26873, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26876, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F4C */
static void lay_down_rc_track_diag_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16689, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16686, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16690, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16688, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16687, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26892, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26889, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26891, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26890, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F5C */
static void lay_down_rc_track_diag_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16694, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16691, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16693, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16695, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16692, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26896, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26893, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26895, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26894, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F2C */
static void lay_down_rc_track_diag_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16679, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16676, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16680, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16678, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16677, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26884, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26881, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26883, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26882, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F3C */
static void lay_down_rc_track_diag_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16684, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16681, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16683, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16685, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16682, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26888, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26885, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26887, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26886, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F6C */
static void lay_down_rc_track_diag_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16682, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16683, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16685, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16681, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16684, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26886, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26887, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26885, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26888, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F7C */
static void lay_down_rc_track_diag_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16677, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16678, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16676, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16680, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16679, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26882, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26883, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26881, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26884, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 39, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F8C */
static void lay_down_rc_track_diag_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16692, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16693, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16695, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16691, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16694, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26894, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26895, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26893, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26896, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824F9C */
static void lay_down_rc_track_diag_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16687, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16688, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16686, -16, -16, 32, 32, 3, height, -16, -16, height);
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16690, -16, -16, 32, 32, 0, height, -16, -16, height + 35);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16689, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26890, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26891, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26889, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26892, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 32);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 37, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824ECC */
static void lay_down_rc_track_diag_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16665, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16662, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16664, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16663, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26872, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26869, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26871, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26870, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824EDC */
static void lay_down_rc_track_diag_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16663, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16664, -16, -16, 32, 32, 3, height, -16, -16, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16662, -16, -16, 32, 32, 0, height, -16, -16, height + 27);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16665, -16, -16, 32, 32, 3, height, -16, -16, height);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26870, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26871, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26869, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 3:
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26872, -16, -16, 32, 32, 3, height + 24, -16, -16, height + 22);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
			switch (direction) {
			case 0:
				metal_a_supports_paint_setup(11, 1, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				metal_a_supports_paint_setup(11, 0, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				metal_a_supports_paint_setup(11, 2, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				metal_a_supports_paint_setup(11, 3, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}

			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824FAC */
static void lay_down_rc_track_left_flyer_twist_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26972, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26978, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26971, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26977, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26973, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26979, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26970, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26976, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26974, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26980, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26969, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26975, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26972, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26978, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26971, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26977, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26973, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26979, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26970, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26976, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26974, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26980, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26969, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26975, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824FBC */
static void lay_down_rc_track_right_flyer_twist_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26984, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26990, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26983, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26989, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26985, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26991, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26982, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26988, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26986, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26992, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26981, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26987, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26984, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26990, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26983, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26989, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26985, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26991, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26982, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26988, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26986, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26992, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26981, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26987, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824FCC */
static void lay_down_rc_track_left_flyer_twist_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26969, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26975, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26974, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26980, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26970, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26976, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26973, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26979, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26971, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26977, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26972, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26978, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26969, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26975, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26974, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26980, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26970, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26976, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26973, 0, 6, 32, 20, 3, height + 24, 0, 6, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26979, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26971, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26977, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26972, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26978, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824FDC */
static void lay_down_rc_track_right_flyer_twist_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26981, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26987, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26986, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26992, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26982, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26988, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26985, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26991, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26983, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26989, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26984, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26990, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
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
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26981, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26987, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26986, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26992, 0, 6, 32, 20, 3, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26982, 0, 6, 32, 20, 3, height + 24);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26988, 0, 6, 32, 20, 3, height + 24);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26985, 0, 6, 32, 20, 3, height + 24);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26991, 0, 6, 32, 20, 3, height + 24);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26983, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26989, 0, 6, 32, 20, 3, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26984, 0, 6, 32, 20, 3, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26990, 0, 6, 32, 20, 3, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 1:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 2:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 32, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C3C */
static void lay_down_rc_track_flyer_half_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16594, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16602, 0, 6, 32, 20, 11, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16601, 0, 6, 32, 20, 9, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16609, 0, 6, 32, 20, 7, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16595, 0, 0, 32, 20, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16603, 0, 14, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16600, 0, 6, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16608, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16596, 16, 0, 2, 16, 119, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16604, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16599, 10, 16, 4, 12, 119, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16607, 16, 16, 2, 16, 119, height, 15, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16597, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16605, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16598, 0, 16, 32, 12, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16606, 0, 16, 32, 12, 3, height + 32);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16594, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16602, 0, 6, 32, 20, 11, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16601, 0, 6, 32, 20, 9, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16609, 0, 6, 32, 20, 7, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16595, 0, 0, 32, 20, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16603, 0, 14, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16600, 0, 6, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16608, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16596, 16, 0, 2, 16, 119, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16604, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16599, 10, 16, 4, 12, 119, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16607, 16, 16, 2, 16, 119, height, 15, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16597, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16605, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16598, 0, 16, 32, 12, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16606, 0, 16, 32, 12, 3, height + 32);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C4C */
static void lay_down_rc_track_flyer_half_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16597, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16605, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16598, 0, 16, 32, 12, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16606, 0, 16, 32, 12, 3, height + 32);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16596, 16, 0, 2, 16, 119, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16604, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16599, 10, 16, 4, 12, 119, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16607, 16, 16, 2, 16, 119, height, 15, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16595, 0, 0, 32, 20, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16603, 0, 14, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16600, 0, 6, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16608, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16594, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16602, 0, 6, 32, 20, 11, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16601, 0, 6, 32, 20, 9, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16609, 0, 6, 32, 20, 7, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16597, 0, 0, 32, 16, 3, height + 32);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16605, 0, 0, 32, 16, 3, height + 32);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16598, 0, 16, 32, 12, 3, height + 32);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16606, 0, 16, 32, 12, 3, height + 32);
				break;
			}
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16596, 16, 0, 2, 16, 119, height);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16604, 12, 0, 3, 16, 119, height, 12, 0, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16599, 10, 16, 4, 12, 119, height);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16607, 16, 16, 2, 16, 119, height, 15, 6, height);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 168, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16595, 0, 0, 32, 20, 3, height, 0, 6, height);
				metal_a_supports_paint_setup(11, 4, 20, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16603, 0, 14, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 15, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16600, 0, 6, 3, 20, 63, height, 28, 6, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16608, 0, 6, 32, 20, 3, height);
				metal_a_supports_paint_setup(11, 4, 16, height, gTrackColours[SCHEME_SUPPORTS]);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 3:
			switch (direction) {
			case 0:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16594, 0, 6, 32, 20, 3, height);
				break;
			case 1:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16602, 0, 6, 32, 20, 11, height);
				break;
			case 2:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16601, 0, 6, 32, 20, 9, height);
				break;
			case 3:
				sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16609, 0, 6, 32, 20, 7, height);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 8, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_1);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 56, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C5C */
static void lay_down_rc_track_left_flyer_corkscrew_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16610, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16613, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16616, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16619, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			}

			if (direction == 2) {
				paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction != 2) {
				paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			}

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16611, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16614, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16617, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16620, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16612, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16615, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16618, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16621, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height + 8, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height + 8, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16610, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16613, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16616, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16619, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			}

			if (direction == 2) {
				paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction != 2) {
				paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			}

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16611, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16614, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16617, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16620, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16612, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16615, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16618, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16621, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height + 8, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height + 8, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C6C */
static void lay_down_rc_track_right_flyer_corkscrew_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16622, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16625, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16628, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16631, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16623, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16626, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16629, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16632, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16624, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16627, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16630, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16633, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_0);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16622, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16625, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16628, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16631, 0, 0, 32, 20, 3, height, 0, 6, height + 4);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16623, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16626, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16629, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16632, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16624, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16627, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16630, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16633, 0, 0, 20, 32, 3, height, 6, 0, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			switch (direction) {
			case 0:
				paint_util_push_tunnel_right(height + 8, TUNNEL_0);
				break;
			case 1:
				paint_util_push_tunnel_left(height + 8, TUNNEL_0);
				break;
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C7C */
static void lay_down_rc_track_left_flyer_corkscrew_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16627, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16630, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16633, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16624, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16626, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16629, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16632, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16623, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16625, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16628, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16631, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16622, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	} else {
		switch (trackSequence) {
		case 0:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16627, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16630, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16633, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16624, 0, 0, 32, 20, 3, height, 0, 6, height + 24);
				break;
			}

			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
			metal_a_supports_paint_setup(11, 4, 0, height + 35, gTrackColours[SCHEME_SUPPORTS]);

			if (direction == 0 || direction == 3) {
				paint_util_push_tunnel_rotated(direction, height + 8, TUNNEL_0);
			}
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		case 1:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16626, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16629, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16632, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16623, 0, 0, 20, 20, 3, height, 6, 6, height + 10);
				break;
			}
			paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
			paint_util_set_general_support_height(height + 72, 0x20);
			break;
		case 2:
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16625, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16628, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16631, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16622, 0, 0, 20, 32, 3, height, 6, 0, height + 4);
				break;
			}
			metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
			switch (direction) {
			case 2:
				paint_util_push_tunnel_right(height, TUNNEL_0);
				break;
			case 3:
				paint_util_push_tunnel_left(height, TUNNEL_0);
				break;
			}
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
			paint_util_set_general_support_height(height + 48, 0x20);
			break;
		}
	}
}

/** rct2: 0x00824C8C */
static void lay_down_rc_track_right_flyer_corkscrew_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	lay_down_rc_track_left_flyer_corkscrew_up(rideIndex, 2 - trackSequence, (direction + 3) % 4, height, mapElement);
}

/** rct2: 0x00824FEC */
static void lay_down_rc_track_block_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	if (!track_element_is_inverted(mapElement)) {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16232, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 16233, 0, 0, 32, 20, 3, height, 0, 6, height);
			break;
		}
		metal_a_supports_paint_setup(11, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 32, 0x20);
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26559, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 26560, 0, 0, 32, 20, 3, height + 24, 0, 6, height + 24);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
			metal_a_supports_paint_setup(11, 4, 0, height + 33, gTrackColours[SCHEME_SUPPORTS]);
		}

		paint_util_push_tunnel_rotated(direction, height, TUNNEL_0);
		paint_util_set_general_support_height(height + 32, 0x20);
	}
}

TRACK_PAINT_FUNCTION get_track_paint_function_lay_down_rc(int trackType, int direction)
{
	switch (trackType) {
	case TRACK_ELEM_FLAT:
		return lay_down_rc_track_flat;
	case TRACK_ELEM_END_STATION:
	case TRACK_ELEM_BEGIN_STATION:
	case TRACK_ELEM_MIDDLE_STATION:
		return lay_down_rc_track_station;
	case TRACK_ELEM_25_DEG_UP:
		return lay_down_rc_track_25_deg_up;
	case TRACK_ELEM_60_DEG_UP:
		return lay_down_rc_track_60_deg_up;
	case TRACK_ELEM_FLAT_TO_25_DEG_UP:
		return lay_down_rc_track_flat_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_60_DEG_UP:
		return lay_down_rc_track_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_60_DEG_UP_TO_25_DEG_UP:
		return lay_down_rc_track_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_FLAT:
		return lay_down_rc_track_25_deg_up_to_flat;
	case TRACK_ELEM_25_DEG_DOWN:
		return lay_down_rc_track_25_deg_down;
	case TRACK_ELEM_60_DEG_DOWN:
		return lay_down_rc_track_60_deg_down;
	case TRACK_ELEM_FLAT_TO_25_DEG_DOWN:
		return lay_down_rc_track_flat_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_60_DEG_DOWN:
		return lay_down_rc_track_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_60_DEG_DOWN_TO_25_DEG_DOWN:
		return lay_down_rc_track_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_FLAT:
		return lay_down_rc_track_25_deg_down_to_flat;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES:
		return lay_down_rc_track_left_quarter_turn_5;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES:
		return lay_down_rc_track_right_quarter_turn_5;
	case TRACK_ELEM_FLAT_TO_LEFT_BANK:
		return lay_down_rc_track_flat_to_left_bank;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANK:
		return lay_down_rc_track_flat_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_FLAT:
		return lay_down_rc_track_left_bank_to_flat;
	case TRACK_ELEM_RIGHT_BANK_TO_FLAT:
		return lay_down_rc_track_right_bank_to_flat;
	case TRACK_ELEM_BANKED_LEFT_QUARTER_TURN_5_TILES:
		return lay_down_rc_track_banked_left_quarter_turn_5;
	case TRACK_ELEM_BANKED_RIGHT_QUARTER_TURN_5_TILES:
		return lay_down_rc_track_banked_right_quarter_turn_5;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_UP:
		return lay_down_rc_track_left_bank_to_25_deg_up;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_UP:
		return lay_down_rc_track_right_bank_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_LEFT_BANK:
		return lay_down_rc_track_25_deg_up_to_left_bank;
	case TRACK_ELEM_25_DEG_UP_TO_RIGHT_BANK:
		return lay_down_rc_track_25_deg_up_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_DOWN:
		return lay_down_rc_track_left_bank_to_25_deg_down;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_DOWN:
		return lay_down_rc_track_right_bank_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_LEFT_BANK:
		return lay_down_rc_track_25_deg_down_to_left_bank;
	case TRACK_ELEM_25_DEG_DOWN_TO_RIGHT_BANK:
		return lay_down_rc_track_25_deg_down_to_right_bank;
	case TRACK_ELEM_LEFT_BANK:
		return lay_down_rc_track_left_bank;
	case TRACK_ELEM_RIGHT_BANK:
		return lay_down_rc_track_right_bank;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return lay_down_rc_track_left_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return lay_down_rc_track_right_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return lay_down_rc_track_left_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return lay_down_rc_track_right_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_S_BEND_LEFT:
		return lay_down_rc_track_s_bend_left;
	case TRACK_ELEM_S_BEND_RIGHT:
		return lay_down_rc_track_s_bend_right;
	case TRACK_ELEM_LEFT_VERTICAL_LOOP:
		return lay_down_rc_track_left_vertical_loop;
	case TRACK_ELEM_RIGHT_VERTICAL_LOOP:
		return lay_down_rc_track_right_vertical_loop;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
		return lay_down_rc_track_left_quarter_turn_3;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
		return lay_down_rc_track_right_quarter_turn_3;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_BANK:
		return lay_down_rc_track_left_quarter_turn_3_bank;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_BANK:
		return lay_down_rc_track_right_quarter_turn_3_bank;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return lay_down_rc_track_left_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return lay_down_rc_track_right_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return lay_down_rc_track_left_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return lay_down_rc_track_right_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_SMALL:
		return lay_down_rc_track_left_half_banked_helix_up_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_SMALL:
		return lay_down_rc_track_right_half_banked_helix_up_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_SMALL:
		return lay_down_rc_track_left_half_banked_helix_down_small;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_SMALL:
		return lay_down_rc_track_right_half_banked_helix_down_small;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_UP_LARGE:
		return lay_down_rc_track_left_half_banked_helix_up_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_UP_LARGE:
		return lay_down_rc_track_right_half_banked_helix_up_large;
	case TRACK_ELEM_LEFT_HALF_BANKED_HELIX_DOWN_LARGE:
		return lay_down_rc_track_left_half_banked_helix_down_large;
	case TRACK_ELEM_RIGHT_HALF_BANKED_HELIX_DOWN_LARGE:
		return lay_down_rc_track_right_half_banked_helix_down_large;
	case TRACK_ELEM_LEFT_QUARTER_TURN_1_TILE_60_DEG_UP:
		return lay_down_rc_track_left_quarter_turn_1_60_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_1_TILE_60_DEG_UP:
		return lay_down_rc_track_right_quarter_turn_1_60_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_1_TILE_60_DEG_DOWN:
		return lay_down_rc_track_left_quarter_turn_1_60_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_1_TILE_60_DEG_DOWN:
		return lay_down_rc_track_right_quarter_turn_1_60_deg_down;
	case TRACK_ELEM_BRAKES:
		return lay_down_rc_track_brakes;
	case TRACK_ELEM_ON_RIDE_PHOTO:
		return lay_down_rc_track_on_ride_photo;
	case TRACK_ELEM_LEFT_EIGHTH_TO_DIAG:
		return lay_down_rc_track_left_eighth_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_DIAG:
		return lay_down_rc_track_right_eighth_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_TO_ORTHOGONAL:
		return lay_down_rc_track_left_eighth_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_ORTHOGONAL:
		return lay_down_rc_track_right_eighth_to_orthogonal;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_DIAG:
		return lay_down_rc_track_left_eighth_bank_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_DIAG:
		return lay_down_rc_track_right_eighth_bank_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_ORTHOGONAL:
		return lay_down_rc_track_left_eighth_bank_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_ORTHOGONAL:
		return lay_down_rc_track_right_eighth_bank_to_orthogonal;
	case TRACK_ELEM_DIAG_FLAT:
		return lay_down_rc_track_diag_flat;
	case TRACK_ELEM_DIAG_25_DEG_UP:
		return lay_down_rc_track_diag_25_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP:
		return lay_down_rc_track_diag_60_deg_up;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_UP:
		return lay_down_rc_track_diag_flat_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_60_DEG_UP:
		return lay_down_rc_track_diag_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP_TO_25_DEG_UP:
		return lay_down_rc_track_diag_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_FLAT:
		return lay_down_rc_track_diag_25_deg_up_to_flat;
	case TRACK_ELEM_DIAG_25_DEG_DOWN:
		return lay_down_rc_track_diag_25_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN:
		return lay_down_rc_track_diag_60_deg_down;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_DOWN:
		return lay_down_rc_track_diag_flat_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_60_DEG_DOWN:
		return lay_down_rc_track_diag_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN_TO_25_DEG_DOWN:
		return lay_down_rc_track_diag_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_FLAT:
		return lay_down_rc_track_diag_25_deg_down_to_flat;
	case TRACK_ELEM_DIAG_FLAT_TO_LEFT_BANK:
		return lay_down_rc_track_diag_flat_to_left_bank;
	case TRACK_ELEM_DIAG_FLAT_TO_RIGHT_BANK:
		return lay_down_rc_track_diag_flat_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_FLAT:
		return lay_down_rc_track_diag_left_bank_to_flat;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_FLAT:
		return lay_down_rc_track_diag_right_bank_to_flat;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_UP:
		return lay_down_rc_track_diag_left_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_UP:
		return lay_down_rc_track_diag_right_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_LEFT_BANK:
		return lay_down_rc_track_diag_25_deg_up_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_RIGHT_BANK:
		return lay_down_rc_track_diag_25_deg_up_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_DOWN:
		return lay_down_rc_track_diag_left_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_DOWN:
		return lay_down_rc_track_diag_right_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_LEFT_BANK:
		return lay_down_rc_track_diag_25_deg_down_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_RIGHT_BANK:
		return lay_down_rc_track_diag_25_deg_down_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK:
		return lay_down_rc_track_diag_left_bank;
	case TRACK_ELEM_DIAG_RIGHT_BANK:
		return lay_down_rc_track_diag_right_bank;
	case TRACK_ELEM_LEFT_FLYER_TWIST_UP:
		return lay_down_rc_track_left_flyer_twist_up;
	case TRACK_ELEM_RIGHT_FLYER_TWIST_UP:
		return lay_down_rc_track_right_flyer_twist_up;
	case TRACK_ELEM_LEFT_FLYER_TWIST_DOWN:
		return lay_down_rc_track_left_flyer_twist_down;
	case TRACK_ELEM_RIGHT_FLYER_TWIST_DOWN:
		return lay_down_rc_track_right_flyer_twist_down;
	case TRACK_ELEM_FLYER_HALF_LOOP_UP:
		return lay_down_rc_track_flyer_half_loop_up;
	case TRACK_ELEM_FLYER_HALF_LOOP_DOWN:
		return lay_down_rc_track_flyer_half_loop_down;
	case TRACK_ELEM_LEFT_FLYER_CORKSCREW_UP:
		return lay_down_rc_track_left_flyer_corkscrew_up;
	case TRACK_ELEM_RIGHT_FLYER_CORKSCREW_UP:
		return lay_down_rc_track_right_flyer_corkscrew_up;
	case TRACK_ELEM_LEFT_FLYER_CORKSCREW_DOWN:
		return lay_down_rc_track_left_flyer_corkscrew_down;
	case TRACK_ELEM_RIGHT_FLYER_CORKSCREW_DOWN:
		return lay_down_rc_track_right_flyer_corkscrew_down;
	case TRACK_ELEM_BLOCK_BRAKES:
		return lay_down_rc_track_block_brakes;
	}
	return NULL;
}
