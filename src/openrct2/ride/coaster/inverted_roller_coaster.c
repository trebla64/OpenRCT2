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

/** rct2: 0x008A92E8 */
static void inverted_rc_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27131, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27132, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}
	} else {
		switch (direction) {
		case 0:
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27129, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27130, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A9558, 0x008A9568, 0x008A9578 */
static void inverted_rc_track_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	static const uint32 imageIds[4][3] = {
		{ SPR_STATION_BASE_C_SW_NE, 27131, SPR_STATION_INVERTED_BAR_C_SW_NE },
		{ SPR_STATION_BASE_C_NW_SE, 27132, SPR_STATION_INVERTED_BAR_C_NW_SE },
		{ SPR_STATION_BASE_C_SW_NE, 27131, SPR_STATION_INVERTED_BAR_C_SW_NE },
		{ SPR_STATION_BASE_C_NW_SE, 27132, SPR_STATION_INVERTED_BAR_C_NW_SE },
	};

	sub_98197C_rotated(direction, imageIds[direction][0] | gTrackColours[SCHEME_MISC], 0, 0, 32, 28, 1, height, 0, 2, height);
	sub_98197C_rotated(direction, imageIds[direction][1] | gTrackColours[SCHEME_TRACK], 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
	sub_98199C_rotated(direction, imageIds[direction][2] | gTrackColours[SCHEME_SUPPORTS], 0, 6, 32, 20, 3, height + 29, 0, 6, height + 29);
	track_paint_util_draw_station_metal_supports_2(direction, height, gTrackColours[SCHEME_SUPPORTS], 3);
	track_paint_util_draw_station_inverted(rideIndex, trackSequence, direction, height, mapElement, STATION_VARIANT_TALL);
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_9);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A92F8 */
static void inverted_rc_track_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27249, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27250, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27251, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27252, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27221, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27222, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27223, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27224, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9308 */
static void inverted_rc_track_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27237, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 93);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27238, 0, 0, 32, 2, 81, height + 29, 0, 4, height + 11);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27239, 0, 0, 32, 2, 81, height + 29, 0, 4, height + 11);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27240, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 93);
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

/** rct2: 0x008A9318 */
static void inverted_rc_track_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27241, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27242, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27243, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27244, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27213, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27214, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27215, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27216, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9328 */
static void inverted_rc_track_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27225, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27229, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27226, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27230, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27227, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27228, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
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

/** rct2: 0x008A9338 */
static void inverted_rc_track_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27231, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27235, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27232, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27236, 0, 0, 32, 10, 49, height + 29, 0, 10, height + 11);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27233, 0, 0, 32, 2, 49, height + 29, 0, 4, height + 11);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27234, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 61);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 76, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9348 */
static void inverted_rc_track_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	if (track_element_is_lift_hill(mapElement)) {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27245, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27246, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27247, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27248, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	} else {
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27217, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27218, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27219, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27220, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
			break;
		}
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9358 */
static void inverted_rc_track_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9368 */
static void inverted_rc_track_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9378 */
static void inverted_rc_track_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9388 */
static void inverted_rc_track_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_60_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9398 */
static void inverted_rc_track_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_to_60_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A93A8 */
static void inverted_rc_track_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_flat_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A93B8 */
static void inverted_rc_track_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27142, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27147, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27152, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27137, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27141, 0, 0, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27146, 0, 0, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27151, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27136, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27140, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27145, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27150, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27135, 0, 0, 16, 16, 3, height + 29);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27139, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27144, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27149, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27134, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27138, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27143, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27148, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27133, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A93C8 */
static void inverted_rc_track_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	inverted_rc_track_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A93D8 */
static void inverted_rc_track_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27269, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27270, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27271, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27272, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A93E8 */
static void inverted_rc_track_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27273, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27274, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27275, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27276, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A93F8 */
static void inverted_rc_track_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27275, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27276, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27273, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27274, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A9408 */
static void inverted_rc_track_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27271, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27272, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27269, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27270, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A9418 */
static void inverted_rc_track_banked_left_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27162, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27167, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27172, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27157, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27161, 0, 0, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27166, 0, 0, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27171, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27156, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27160, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27165, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27170, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27155, 0, 0, 16, 16, 3, height + 29);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27159, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27164, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27169, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27154, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27158, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27163, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27168, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27153, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9428 */
static void inverted_rc_track_banked_right_quarter_turn_5(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	inverted_rc_track_banked_left_quarter_turn_5(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A9438 */
static void inverted_rc_track_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27277, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27278, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27279, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27280, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9448 */
static void inverted_rc_track_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27281, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27282, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27283, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27284, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9458 */
static void inverted_rc_track_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27285, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27286, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27287, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27288, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9468 */
static void inverted_rc_track_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27289, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27290, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27291, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27292, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9478 */
static void inverted_rc_track_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_to_right_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9488 */
static void inverted_rc_track_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_to_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9498 */
static void inverted_rc_track_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A94A8 */
static void inverted_rc_track_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_bank_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A94B8 */
static void inverted_rc_track_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27293, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27294, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27295, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27296, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A94C8 */
static void inverted_rc_track_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_bank(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A94D8 */
static void inverted_rc_track_left_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27317, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27322, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27327, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27332, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27318, 0, 0, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27323, 0, 0, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27328, 0, 16, 32, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27333, 0, 16, 32, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27319, 0, 16, 16, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27324, 16, 16, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27329, 16, 0, 16, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27334, 0, 0, 16, 16, 3, height + 29);
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27320, 16, 0, 16, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27325, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27330, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27335, 16, 0, 16, 32, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27321, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27326, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27331, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27336, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A94E8 */
static void inverted_rc_track_right_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27297, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27302, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27307, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27312, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27298, 0, 16, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27303, 0, 16, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27308, 0, 0, 32, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27313, 0, 0, 32, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27299, 0, 0, 16, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27304, 16, 0, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27309, 16, 16, 16, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27314, 0, 16, 16, 16, 3, height + 29);
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27300, 16, 0, 16, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27305, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27310, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27315, 16, 0, 16, 32, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27301, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27306, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27311, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27316, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A94F8 */
static void inverted_rc_track_left_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	inverted_rc_track_right_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A9508 */
static void inverted_rc_track_right_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	inverted_rc_track_left_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A9518 */
static void inverted_rc_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27253, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27257, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27256, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27260, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27254, 0, 0, 32, 26, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27258, 0, 0, 32, 26, 3, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27255, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27259, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27255, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27259, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27254, 0, 0, 32, 26, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27258, 0, 0, 32, 26, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27256, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27260, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27253, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27257, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9528 */
static void inverted_rc_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27261, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27265, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27264, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27268, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27262, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27266, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27263, 0, 0, 32, 26, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27267, 0, 0, 32, 26, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27263, 0, 0, 32, 26, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27267, 0, 0, 32, 26, 3, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27262, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27266, 0, 0, 32, 26, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27264, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27268, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27261, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27265, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9538 */
static void inverted_rc_track_left_vertical_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27355, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27363, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27362, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27370, 0, 6, 32, 10, 7, height + 29, 0, 6, height + 45);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27356, 0, 0, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27364, 0, 14, 32, 2, 63, height + 29, 0, 29, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27361, 0, 6, 32, 2, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27369, 0, 6, 2, 2, 3, height + 29, 29, 20, height + 29);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27357, 16, 0, 5, 2, 119, height + 2, 16, 29, height + 2);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27365, 12, 0, 32, 2, 119, height + 2, 0, -6, height + 2);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27360, 10, 16, 4, 2, 119, height + 2, 10, 0, height + 2);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27368, 16, 16, 2, 2, 119, height + 2, 29, 29, height + 2);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 168, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27358, 0, 0, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27366, 0, 0, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27359, 0, 16, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27367, 0, 16, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 5:
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27359, 0, 16, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27367, 0, 16, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27358, 0, 0, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27366, 0, 0, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27360, 10, 16, 4, 2, 119, height + 2, 10, 0, height + 2);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27368, 16, 16, 2, 2, 119, height + 2, 29, 29, height + 2);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27357, 16, 0, 5, 2, 119, height + 2, 16, 29, height + 2);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27365, 12, 0, 32, 2, 119, height + 2, 0, -6, height + 2);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 168, 0x20);
		break;
	case 8:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27361, 0, 6, 32, 2, 3, height + 29, 0, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27369, 0, 6, 2, 2, 3, height + 29, 29, 20, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27356, 0, 0, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27364, 0, 14, 32, 2, 63, height + 29, 0, 29, height + 29);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 9:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27362, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27370, 0, 6, 32, 10, 7, height + 29, 0, 6, height + 45);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27355, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27363, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height - 8, TUNNEL_4);
			break;
		case 2:
			paint_util_push_tunnel_left(height - 8, TUNNEL_4);
			break;
		}
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A9548 */
static void inverted_rc_track_right_vertical_loop(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27386, 0, 6, 32, 10, 7, height + 29, 0, 6, height + 45);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27378, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27379, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27371, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27385, 0, 6, 2, 2, 3, height + 29, 29, 20, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27377, 0, 6, 32, 2, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27380, 0, 14, 32, 2, 63, height + 29, 0, 29, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27372, 0, 0, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27384, 16, 16, 2, 2, 119, height + 2, 29, 29, height + 2);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27376, 10, 16, 4, 2, 119, height + 2, 10, 0, height + 2);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27381, 12, 0, 32, 2, 119, height + 2, 0, -6, height + 2);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27373, 16, 0, 5, 2, 119, height + 2, 16, 29, height + 2);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 168, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27383, 0, 16, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27375, 0, 16, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27382, 0, 0, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27374, 0, 0, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 4:
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 5:
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27382, 0, 0, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27374, 0, 0, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27383, 0, 16, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27375, 0, 16, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 7:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27381, 12, 0, 32, 2, 119, height + 2, 0, -6, height + 2);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27373, 16, 0, 5, 2, 119, height + 2, 16, 29, height + 2);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27384, 16, 16, 2, 2, 119, height + 2, 29, 29, height + 2);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27376, 10, 16, 4, 2, 119, height + 2, 10, 0, height + 2);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 168, 0x20);
		break;
	case 8:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27380, 0, 14, 32, 2, 63, height + 29, 0, 29, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27372, 0, 0, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27385, 0, 6, 2, 2, 3, height + 29, 29, 20, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27377, 0, 6, 32, 2, 3, height + 29, 0, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 9:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27379, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27371, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27386, 0, 6, 32, 10, 7, height + 29, 0, 6, height + 45);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27378, 0, 6, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 55, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height - 8, TUNNEL_4);
			break;
		case 2:
			paint_util_push_tunnel_left(height - 8, TUNNEL_4);
			break;
		}
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A9588 */
static void inverted_rc_track_left_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27392, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27395, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27398, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27389, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27391, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27394, 0, 0, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27397, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27388, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27390, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27393, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27396, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27387, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9598 */
static void inverted_rc_track_right_quarter_turn_3(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	inverted_rc_track_left_quarter_turn_3(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A95A8 */
static void inverted_rc_track_left_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27404, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27407, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27410, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27401, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27403, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27406, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27409, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27400, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27402, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27405, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27408, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27399, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A95B8 */
static void inverted_rc_track_right_quarter_turn_3_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	inverted_rc_track_left_quarter_turn_3_bank(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A95C8 */
static void inverted_rc_track_left_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27422, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27424, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27426, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27420, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27421, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27423, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27425, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27419, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A95D8 */
static void inverted_rc_track_right_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27411, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27413, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27415, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27417, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27412, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27414, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27416, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27418, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A95E8 */
static void inverted_rc_track_left_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	inverted_rc_track_right_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A95F8 */
static void inverted_rc_track_right_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	inverted_rc_track_left_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A9608 */
static void inverted_rc_track_left_twist_down_to_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27427, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27433, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27432, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27438, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27428, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27434, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27431, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27437, 0, 6, 32, 20, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27429, 0, 6, 32, 20, 3, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27435, 0, 6, 32, 20, 3, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27430, 0, 6, 32, 20, 3, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27436, 0, 6, 32, 20, 3, height);
			break;
		}
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 2:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9618 */
static void inverted_rc_track_right_twist_down_to_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27439, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27445, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27444, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27450, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27440, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27446, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27443, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27449, 0, 6, 32, 20, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27441, 0, 6, 32, 20, 3, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27447, 0, 6, 32, 20, 3, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27442, 0, 6, 32, 20, 3, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27448, 0, 6, 32, 20, 3, height);
			break;
		}
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 1:
			paint_util_push_tunnel_right(height, TUNNEL_3);
			break;
		case 2:
			paint_util_push_tunnel_left(height, TUNNEL_3);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9628 */
static void inverted_rc_track_left_twist_up_to_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27430, 0, 6, 32, 20, 3, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27436, 0, 6, 32, 20, 3, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27429, 0, 6, 32, 20, 3, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27435, 0, 6, 32, 20, 3, height);
			break;
		}
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27431, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27437, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27428, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27434, 0, 6, 32, 20, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27432, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27438, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27427, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27433, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9638 */
static void inverted_rc_track_right_twist_up_to_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27442, 0, 6, 32, 20, 3, height);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27448, 0, 6, 32, 20, 3, height);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27441, 0, 6, 32, 20, 3, height);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27447, 0, 6, 32, 20, 3, height);
			break;
		}
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27443, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27449, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27440, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27446, 0, 6, 32, 20, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27444, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27450, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27439, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27445, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9648 */
static void inverted_rc_track_half_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27451, 0, 6, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27459, 0, 6, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27458, 0, 6, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27466, 0, 6, 32, 20, 3, height + 29, 0, 6, height + 45);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27452, 0, 0, 32, 2, 3, height + 29, 0, 29, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27460, 0, 14, 32, 2, 63, height + 29, 0, 29, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27457, 0, 6, 32, 2, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27465, 0, 6, 2, 2, 3, height + 29, 29, 20, height + 29);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27453, 16, 0, 5, 2, 119, height + 2, 16, 29, height + 2);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27461, 12, 0, 32, 2, 119, height + 2, 0, -6, height + 2);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27456, 10, 16, 4, 2, 119, height + 2, 10, 0, height + 2);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27464, 16, 16, 2, 2, 119, height + 2, 29, 29, height + 2);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 168, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27454, 0, 0, 32, 20, 3, height + 34, 0, 6, height + 34);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27462, 0, 0, 2, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27455, 0, 16, 32, 2, 3, height + 34, 0, 0, height - 6);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27463, 0, 16, 32, 20, 3, height + 34, 0, 6, height + 34);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 32, TUNNEL_3);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A9658 */
static void inverted_rc_track_half_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_half_loop_up(rideIndex, 3 - trackSequence, direction, height, mapElement);
}

/** rct2: 0x008A9668 */
static void inverted_rc_track_left_corkscrew_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27467, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27470, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27473, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27476, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27468, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27471, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27474, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27477, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27469, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27472, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27475, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27478, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		}
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 28, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 2:
			paint_util_push_tunnel_right(height + 40, TUNNEL_3);
			break;
		case 3:
			paint_util_push_tunnel_left(height + 40, TUNNEL_3);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A9678 */
static void inverted_rc_track_right_corkscrew_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27479, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27482, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27485, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27488, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 33);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27480, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27483, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27486, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27489, 0, 0, 20, 20, 3, height + 14, 6, 6, height + 24);
			break;
		}
		paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27481, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27484, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27487, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27490, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 39);
			break;
		}
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 28, gTrackColours[SCHEME_SUPPORTS]);
		switch (direction) {
		case 0:
			paint_util_push_tunnel_right(height + 40, TUNNEL_3);
			break;
		case 1:
			paint_util_push_tunnel_left(height + 40, TUNNEL_3);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A9688 */
static void inverted_rc_track_left_corkscrew_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_corkscrew_up(rideIndex, 2 - trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A9698 */
static void inverted_rc_track_right_corkscrew_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_corkscrew_up(rideIndex, 2 - trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A96D8 */
static void inverted_rc_track_left_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27352, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27348, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27353, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27349, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27354, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27350, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27351, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27347, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	}
	track_paint_util_left_quarter_turn_1_tile_tunnel(direction, height, -8, TUNNEL_4, +56, TUNNEL_5);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

/** rct2: 0x008A96B8 */
static void inverted_rc_track_right_quarter_turn_1_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27343, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27339, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27344, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27340, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27345, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27341, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27346, 0, 0, 28, 28, 3, height, 2, 2, height);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27342, 0, 0, 28, 28, 1, height, 2, 2, height + 99);
		break;
	}
	track_paint_util_right_quarter_turn_1_tile_tunnel(direction, height, -8, TUNNEL_4, +56, TUNNEL_5);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 104, 0x20);
}

/** rct2: 0x008A96C8 */
static void inverted_rc_track_left_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A96E8 */
static void inverted_rc_track_right_quarter_turn_1_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_quarter_turn_1_60_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A96A8 */
static void inverted_rc_track_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27337, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27338, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A96F8 */
static void inverted_rc_track_left_quarter_banked_helix_large_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27202, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27207, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27212, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27197, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27201, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27206, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27211, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27196, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27200, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27205, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27210, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27195, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27199, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27204, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27209, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27194, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27198, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27203, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27208, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27193, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9708 */
static void inverted_rc_track_right_quarter_banked_helix_large_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27173, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27178, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27183, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27188, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27174, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27179, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27184, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27189, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27175, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27180, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27185, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27190, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27176, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27181, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27186, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27191, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27177, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27182, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27187, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27192, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9718 */
static void inverted_rc_track_left_quarter_banked_helix_large_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27182, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27187, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27192, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27177, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27181, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27186, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27191, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27176, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27180, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27185, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27190, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27175, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27179, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27184, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27189, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27174, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27178, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27183, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27188, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27173, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9728 */
static void inverted_rc_track_right_quarter_banked_helix_large_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27193, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27198, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27203, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27208, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 43);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 58, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27194, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27199, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27204, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27209, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27195, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27200, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27205, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27210, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 43);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27196, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27201, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27206, 0, 0, 16, 32, 3, height + 29, 0, 0, height + 43);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27211, 0, 0, 16, 32, 3, height + 29, 16, 0, height + 43);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27197, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27202, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27207, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27212, 0, 0, 20, 32, 3, height + 29, 6, 0, height + 35);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 46, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9A38 */
static void inverted_rc_track_25_deg_up_left_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27711, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27712, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27713, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27714, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9A48 */
static void inverted_rc_track_25_deg_up_right_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27715, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27716, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27717, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27718, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9738 */
static void inverted_rc_track_on_ride_photo(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27129, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27130, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 2:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27129, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 3:
		sub_98196C_rotated(direction, 0x20000000 | 22432, 0, 0, 32, 32, 1, height);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height, gTrackColours[SCHEME_SUPPORTS]);
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27130, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}
	track_paint_util_onride_photo_paint(direction, height + 3, mapElement);
	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_segment_support_height(SEGMENTS_ALL, 0xFFFF, 0);
	paint_util_set_general_support_height(height + 64, 0x20);
}

/** rct2: 0x008A9A58 */
static void inverted_rc_track_25_deg_down_left_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_right_banked(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9A68 */
static void inverted_rc_track_25_deg_down_right_banked(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_left_banked(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9748 */
static void inverted_rc_track_left_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27507, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27511, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27515, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27519, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27508, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27512, 0, 0, 34, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27516, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27520, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27509, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27513, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27517, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27521, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27510, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27514, 0, 0, 16, 18, 3, height + 29, 0, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27518, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27522, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9758 */
static void inverted_rc_track_right_eighth_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27491, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27495, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27499, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27503, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27492, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27496, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27500, 0, 0, 34, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27504, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27493, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27497, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27501, 0, 0, 28, 28, 3, height + 29, 4, 4, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27505, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27494, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27498, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27502, 0, 0, 16, 18, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27506, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9768 */
static void inverted_rc_track_left_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	inverted_rc_track_right_eighth_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9778 */
static void inverted_rc_track_right_eighth_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	inverted_rc_track_left_eighth_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

/** rct2: 0x008A9938 */
static void inverted_rc_track_left_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27539, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27543, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27547, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27551, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27540, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27544, 0, 0, 34, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27548, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27552, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27541, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27545, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27549, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27553, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27542, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27546, 0, 0, 16, 18, 3, height + 29, 0, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27550, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27554, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9948 */
static void inverted_rc_track_right_eighth_bank_to_diag(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27523, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27527, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27531, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27535, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);

		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
		}
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27524, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27528, 0, 0, 32, 16, 3, height + 29, 0, 16, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27532, 0, 0, 34, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27536, 0, 0, 32, 16, 3, height + 29, 0, 0, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27525, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27529, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27533, 0, 0, 28, 28, 3, height + 29, 4, 4, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27537, 0, 0, 16, 16, 3, height + 29, 0, 16, height + 29);
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
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27526, 0, 0, 16, 16, 3, height + 29, 16, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27530, 0, 0, 16, 16, 3, height + 29, 0, 0, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27534, 0, 0, 16, 18, 3, height + 29, 0, 16, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27538, 0, 0, 16, 16, 3, height + 29, 16, 16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9958 */
static void inverted_rc_track_left_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	inverted_rc_track_right_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9968 */
static void inverted_rc_track_right_eighth_bank_to_orthogonal(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
	inverted_rc_track_left_eighth_bank_to_diag(rideIndex, trackSequence, (direction + 3) & 3, height, mapElement);
}

/** rct2: 0x008A9788 */
static void inverted_rc_track_diag_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27614, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27558, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27611, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27555, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27613, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27557, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27612, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27556, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A97B8 */
static void inverted_rc_track_diag_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27626, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27570, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27623, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27567, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27625, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27569, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27624, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27568, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A9818 */
static void inverted_rc_track_diag_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27582, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27579, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27581, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27580, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 32, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 36, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 32, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 36, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	}
}

/** rct2: 0x008A9798 */
static void inverted_rc_track_diag_flat_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27618, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27562, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27615, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27559, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27617, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27561, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27616, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27560, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A97F8 */
static void inverted_rc_track_diag_25_deg_up_to_60_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27574, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27571, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27573, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27572, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 16, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A9808 */
static void inverted_rc_track_diag_60_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27578, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27575, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27577, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27576, -16, -16, 16, 16, 3, height + 29, 0, 0, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 21, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A97A8 */
static void inverted_rc_track_diag_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27622, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27566, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27619, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27563, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27621, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27565, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27620, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27564, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A97E8 */
static void inverted_rc_track_diag_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27624, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27568, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27625, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27569, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27623, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27567, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27626, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27570, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 45);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 56, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A9848 */
static void inverted_rc_track_diag_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27580, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27581, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27579, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27582, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 93);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 24, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 28, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 24, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 28, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 120, 0x20);
		break;
	}
}

/** rct2: 0x008A97C8 */
static void inverted_rc_track_diag_flat_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27620, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27564, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 1:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27621, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27565, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		break;
	case 2:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27619, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27563, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 3:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27622, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27566, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		break;
	}

	paint_util_set_general_support_height(height + 72, 0x20);
}

/** rct2: 0x008A9828 */
static void inverted_rc_track_diag_25_deg_down_to_60_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27576, -16, -16, 16, 16, 3, height + 29, 0, 0, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27577, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27575, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27578, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 17, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A9838 */
static void inverted_rc_track_diag_60_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27572, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27573, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27571, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27574, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 61);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_b_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 8, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	}
}

/** rct2: 0x008A97D8 */
static void inverted_rc_track_diag_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		if (track_element_is_lift_hill(mapElement)) {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27616, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 3:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27560, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27617, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 0:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27561, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27615, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 2:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27559, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
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
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27618, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		} else {
			switch (direction) {
			case 1:
				sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27562, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
				break;
			}
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A9878 */
static void inverted_rc_track_diag_flat_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27590, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27587, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27589, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27588, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9888 */
static void inverted_rc_track_diag_flat_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27594, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27591, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27593, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27592, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9898 */
static void inverted_rc_track_diag_left_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27592, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27593, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27591, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27594, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A98A8 */
static void inverted_rc_track_diag_right_bank_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27588, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27589, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27587, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27590, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A98D8 */
static void inverted_rc_track_diag_left_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27606, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27603, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27605, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27604, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A98E8 */
static void inverted_rc_track_diag_right_bank_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27610, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27607, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27609, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27608, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A98B8 */
static void inverted_rc_track_diag_25_deg_up_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27598, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27595, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27597, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27596, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A98C8 */
static void inverted_rc_track_diag_25_deg_up_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27602, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27599, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27601, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27600, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	}
}

/** rct2: 0x008A98F8 */
static void inverted_rc_track_diag_left_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27600, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27601, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27599, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27602, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		break;
	}

	paint_util_set_general_support_height(height + 72, 0x20);
}

/** rct2: 0x008A9908 */
static void inverted_rc_track_diag_right_bank_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27596, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27597, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27595, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27598, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 50, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		break;
	}

	paint_util_set_general_support_height(height + 72, 0x20);
}

/** rct2: 0x008A9918 */
static void inverted_rc_track_diag_25_deg_down_to_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27608, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27609, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27607, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27610, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A9928 */
static void inverted_rc_track_diag_25_deg_down_to_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27604, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27605, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27603, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27606, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 37);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 48, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 64, 0x20);
		break;
	}
}

/** rct2: 0x008A9858 */
static void inverted_rc_track_diag_left_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27586, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27583, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27585, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27584, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9868 */
static void inverted_rc_track_diag_right_bank(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27584, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27585, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 2:
		switch (direction) {
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27583, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	case 3:
		switch (direction) {
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27586, -16, -16, 32, 32, 3, height + 29, -16, -16, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 1, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 0, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 2, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 3, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}

		paint_util_set_general_support_height(height + 48, 0x20);
		break;
	}
}

/** rct2: 0x008A9978 */
static void inverted_rc_track_left_large_half_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27639, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27646, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27653, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27660, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27640, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27647, 0, 0, 32, 20, 9, height, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27654, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27661, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27641, 0, 0, 24, 16, 3, height, 8, 0, height + 40);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27648, 0, 0, 32, 16, 0, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27655, 0, 0, 32, 16, 0, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27662, 0, 0, 2, 16, 3, height, 30, 16, height + 70);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27642, 0, 0, 8, 16, 3, height, 24, 0, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27649, 0, 0, 32, 16, 0, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27656, 0, 0, 32, 16, 0, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27663, 0, 0, 2, 16, 3, height, 30, 16, height + 100);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 224, 0x20);
		break;
	case 4:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27643, 0, 0, 2, 2, 3, height, 30, 30, height + 80);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27650, 0, 0, 16, 16, 0, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27657, 0, 0, 16, 16, 0, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27664, 0, 0, 2, 16, 3, height, 30, 0, height + 90);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 128, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27644, 0, 0, 2, 16, 3, height, 30, 16, height);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27651, 0, 0, 32, 16, 0, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27658, 0, 0, 32, 16, 0, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27665, 0, 0, 2, 16, 3, height, 30, 0, height + 140);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 224, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27645, 0, 0, 32, 16, 0, height, 0, 16, height + 32);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27652, 0, 0, 32, 16, 0, height, 0, 16, height);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27659, 0, 0, 32, 16, 0, height, 0, 0, height);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 25, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27666, 0, 0, 32, 16, 0, height, 0, 0, height + 32);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 32, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
		break;
	}
}

/** rct2: 0x008A9988 */
static void inverted_rc_track_right_large_half_loop_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27688, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27681, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27674, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27667, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height - 8, TUNNEL_4);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 56, 0x20);
		break;
	case 1:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27689, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27682, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27675, 0, 0, 32, 20, 19, height, 0, 6, height + 29);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27668, 0, 0, 32, 20, 3, height, 0, 6, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 72, 0x20);
		break;
	case 2:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27690, 0, 0, 32, 16, 3, height, 0, 16, height + 70);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27683, 0, 0, 32, 16, 0, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27676, 0, 0, 32, 16, 0, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27669, 0, 0, 32, 16, 3, height, 0, 0, height + 70);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27691, 0, 0, 32, 16, 3, height, 0, 16, height + 100);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27684, 0, 0, 32, 16, 0, height, 0, 16, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27677, 0, 0, 32, 16, 0, height, 0, 0, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27670, 0, 0, 32, 16, 3, height, 0, 0, height + 100);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 224, 0x20);
		break;
	case 4:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27692, 0, 0, 16, 16, 3, height, 16, 0, height + 90);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27685, 0, 0, 16, 16, 0, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27678, 0, 0, 16, 16, 0, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27671, 0, 0, 2, 16, 3, height, 30, 16, height + 110);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 128, 0x20);
		break;
	case 5:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27693, 0, 0, 2, 16, 3, height, 30, 0, height + 140);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27686, 0, 0, 32, 16, 0, height, 0, 0, height);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27679, 0, 0, 32, 16, 0, height, 0, 16, height);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27672, 0, 0, 2, 16, 3, height, 30, 16, height + 140);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 224, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27694, 0, 0, 32, 16, 0, height, 0, 0, height + 32);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27687, 0, 0, 32, 16, 0, height, 0, 0, height);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 25, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27680, 0, 0, 32, 16, 0, height, 0, 16, height);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27673, 0, 0, 32, 16, 0, height, 0, 16, height + 32);
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 27, height, gTrackColours[SCHEME_SUPPORTS]);
			break;
		}
		if (direction == 0 || direction == 3) {
			paint_util_push_tunnel_rotated(direction, height + 32, TUNNEL_6);
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 40, 0x20);
		break;
	}
}

/** rct2: 0x008A9998 */
static void inverted_rc_track_right_large_half_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_large_half_loop_up(rideIndex, 6 - trackSequence, direction, height, mapElement);
}

/** rct2: 0x008A99A8 */
static void inverted_rc_track_left_large_half_loop_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_large_half_loop_up(rideIndex, 6 - trackSequence, direction, height, mapElement);
}

/** rct2: 0x008A96A8 */
static void inverted_rc_track_block_brakes(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27337, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	case 1:
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27338, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 29);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 44, gTrackColours[SCHEME_SUPPORTS]);
	}

	paint_util_push_tunnel_rotated(direction, height, TUNNEL_3);
	paint_util_set_general_support_height(height + 48, 0x20);
}

/** rct2: 0x008A9A78 */
static void inverted_rc_track_left_banked_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27762, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27764, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27766, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27760, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27761, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27763, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27765, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27759, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9A88 */
static void inverted_rc_track_right_banked_quarter_turn_3_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27751, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27753, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27755, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27757, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27752, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27754, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27756, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27758, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9A98 */
static void inverted_rc_track_left_banked_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	inverted_rc_track_right_banked_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A9AA8 */
static void inverted_rc_track_right_banked_quarter_turn_3_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
	inverted_rc_track_left_banked_quarter_turn_3_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A9BB8 */
static void inverted_rc_track_left_banked_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27787, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27792, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27797, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27802, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27788, 0, 0, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27793, 0, 0, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27798, 0, 16, 32, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27803, 0, 16, 32, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27789, 0, 16, 16, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27794, 16, 16, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27799, 16, 0, 16, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27804, 0, 0, 16, 16, 3, height + 29);
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27790, 16, 0, 16, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27795, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27800, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27805, 16, 0, 16, 32, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27791, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27796, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27801, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27806, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9BC8 */
static void inverted_rc_track_right_banked_quarter_turn_5_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (trackSequence) {
	case 0:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27767, 0, 6, 32, 20, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27772, 0, 6, 32, 20, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27777, 0, 6, 32, 20, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27782, 0, 6, 32, 20, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27768, 0, 16, 32, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27773, 0, 16, 32, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27778, 0, 0, 32, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27783, 0, 0, 32, 16, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 3:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27769, 0, 0, 16, 16, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27774, 16, 0, 16, 16, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27779, 16, 16, 16, 16, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27784, 0, 16, 16, 16, 3, height + 29);
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
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27770, 16, 0, 16, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27775, 0, 0, 16, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27780, 0, 0, 16, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27785, 16, 0, 16, 32, 3, height + 29);
			break;
		}
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
		paint_util_set_general_support_height(height + 88, 0x20);
		break;
	case 6:
		switch (direction) {
		case 0:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27771, 6, 0, 20, 32, 3, height + 29);
			break;
		case 1:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27776, 6, 0, 20, 32, 3, height + 29);
			break;
		case 2:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27781, 6, 0, 20, 32, 3, height + 29);
			break;
		case 3:
			sub_98196C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27786, 6, 0, 20, 32, 3, height + 29);
			break;
		}

		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
		metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 4, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);

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

/** rct2: 0x008A9BD8 */
static void inverted_rc_track_left_banked_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	inverted_rc_track_right_banked_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction + 1) & 3, height, mapElement);
}

/** rct2: 0x008A9BE8 */
static void inverted_rc_track_right_banked_quarter_turn_5_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
	inverted_rc_track_left_banked_quarter_turn_5_25_deg_up(rideIndex, trackSequence, (direction - 1) & 3, height, mapElement);
}

/** rct2: 0x008A9AB8 */
static void inverted_rc_track_25_deg_up_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27719, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27720, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27721, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27722, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9AC8 */
static void inverted_rc_track_25_deg_up_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27723, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27724, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27725, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27726, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9AD8 */
static void inverted_rc_track_left_banked_25_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27727, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27728, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27729, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27730, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9AE8 */
static void inverted_rc_track_right_banked_25_deg_up_to_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27731, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27732, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27733, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27734, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 45);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 62, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9AF8 */
static void inverted_rc_track_25_deg_down_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_banked_25_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9B08 */
static void inverted_rc_track_25_deg_down_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_banked_25_deg_up_to_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9B18 */
static void inverted_rc_track_left_banked_25_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9B28 */
static void inverted_rc_track_right_banked_25_deg_down_to_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_25_deg_up_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9B38 */
static void inverted_rc_track_left_banked_flat_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27735, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27736, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27737, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27738, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9B48 */
static void inverted_rc_track_right_banked_flat_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27739, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27740, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27741, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27742, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9B58 */
static void inverted_rc_track_left_banked_25_deg_up_to_left_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27743, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27744, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27745, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27746, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9B68 */
static void inverted_rc_track_right_banked_25_deg_up_to_right_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27747, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27748, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27749, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27750, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A9B78 */
static void inverted_rc_track_left_banked_flat_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_banked_25_deg_up_to_right_banked_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9B88 */
static void inverted_rc_track_right_banked_flat_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_banked_25_deg_up_to_left_banked_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9B98 */
static void inverted_rc_track_left_banked_25_deg_down_to_left_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_banked_flat_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9BA8 */
static void inverted_rc_track_right_banked_25_deg_down_to_right_banked_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_banked_flat_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A99B8 */
static void inverted_rc_track_flat_to_left_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27695, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27696, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27697, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27698, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A99C8 */
static void inverted_rc_track_flat_to_right_banked_25_deg_up(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27699, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27700, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27701, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27702, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 54, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A99D8 */
static void inverted_rc_track_left_banked_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27703, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27704, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27705, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27706, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A99E8 */
static void inverted_rc_track_right_banked_25_deg_up_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	switch (direction) {
	case 0:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27707, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 1:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27708, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 2:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27709, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	case 3:
		sub_98197C_rotated(direction, gTrackColours[SCHEME_TRACK] | 27710, 0, 0, 32, 20, 3, height + 29, 0, 6, height + 37);
		break;
	}

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0, direction), 0xFFFF, 0);
	if (track_paint_util_should_paint_supports(gPaintMapPosition)) {
		switch (direction) {
		case 0:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 6, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 1:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 8, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 2:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 7, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
			break;
		case 3:
			metal_a_supports_paint_setup(METAL_SUPPORTS_BOXED, 5, 0, height + 52, gTrackColours[SCHEME_SUPPORTS]);
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

/** rct2: 0x008A99F8 */
static void inverted_rc_track_flat_to_left_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_right_banked_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9A08 */
static void inverted_rc_track_flat_to_right_banked_25_deg_down(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_left_banked_25_deg_up_to_flat(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9A18 */
static void inverted_rc_track_left_banked_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_flat_to_right_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

/** rct2: 0x008A9A28 */
static void inverted_rc_track_right_banked_25_deg_down_to_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, sint32 height, rct_map_element * mapElement)
{
	inverted_rc_track_flat_to_left_banked_25_deg_up(rideIndex, trackSequence, (direction + 2) & 3, height, mapElement);
}

TRACK_PAINT_FUNCTION get_track_paint_function_inverted_rc(sint32 trackType, sint32 direction)
{
	switch (trackType) {
	case TRACK_ELEM_FLAT:
		return inverted_rc_track_flat;
	case TRACK_ELEM_END_STATION:
	case TRACK_ELEM_BEGIN_STATION:
	case TRACK_ELEM_MIDDLE_STATION:
		return inverted_rc_track_station;
	case TRACK_ELEM_25_DEG_UP:
		return inverted_rc_track_25_deg_up;
	case TRACK_ELEM_60_DEG_UP:
		return inverted_rc_track_60_deg_up;
	case TRACK_ELEM_FLAT_TO_25_DEG_UP:
		return inverted_rc_track_flat_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_60_DEG_UP:
		return inverted_rc_track_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_60_DEG_UP_TO_25_DEG_UP:
		return inverted_rc_track_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_FLAT:
		return inverted_rc_track_25_deg_up_to_flat;
	case TRACK_ELEM_25_DEG_DOWN:
		return inverted_rc_track_25_deg_down;
	case TRACK_ELEM_60_DEG_DOWN:
		return inverted_rc_track_60_deg_down;
	case TRACK_ELEM_FLAT_TO_25_DEG_DOWN:
		return inverted_rc_track_flat_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_60_DEG_DOWN:
		return inverted_rc_track_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_60_DEG_DOWN_TO_25_DEG_DOWN:
		return inverted_rc_track_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_FLAT:
		return inverted_rc_track_25_deg_down_to_flat;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES:
		return inverted_rc_track_left_quarter_turn_5;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES:
		return inverted_rc_track_right_quarter_turn_5;
	case TRACK_ELEM_FLAT_TO_LEFT_BANK:
		return inverted_rc_track_flat_to_left_bank;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANK:
		return inverted_rc_track_flat_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_FLAT:
		return inverted_rc_track_left_bank_to_flat;
	case TRACK_ELEM_RIGHT_BANK_TO_FLAT:
		return inverted_rc_track_right_bank_to_flat;
	case TRACK_ELEM_BANKED_LEFT_QUARTER_TURN_5_TILES:
		return inverted_rc_track_banked_left_quarter_turn_5;
	case TRACK_ELEM_BANKED_RIGHT_QUARTER_TURN_5_TILES:
		return inverted_rc_track_banked_right_quarter_turn_5;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_UP:
		return inverted_rc_track_left_bank_to_25_deg_up;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_UP:
		return inverted_rc_track_right_bank_to_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_LEFT_BANK:
		return inverted_rc_track_25_deg_up_to_left_bank;
	case TRACK_ELEM_25_DEG_UP_TO_RIGHT_BANK:
		return inverted_rc_track_25_deg_up_to_right_bank;
	case TRACK_ELEM_LEFT_BANK_TO_25_DEG_DOWN:
		return inverted_rc_track_left_bank_to_25_deg_down;
	case TRACK_ELEM_RIGHT_BANK_TO_25_DEG_DOWN:
		return inverted_rc_track_right_bank_to_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_LEFT_BANK:
		return inverted_rc_track_25_deg_down_to_left_bank;
	case TRACK_ELEM_25_DEG_DOWN_TO_RIGHT_BANK:
		return inverted_rc_track_25_deg_down_to_right_bank;
	case TRACK_ELEM_LEFT_BANK:
		return inverted_rc_track_left_bank;
	case TRACK_ELEM_RIGHT_BANK:
		return inverted_rc_track_right_bank;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return inverted_rc_track_left_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_UP:
		return inverted_rc_track_right_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return inverted_rc_track_left_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES_25_DEG_DOWN:
		return inverted_rc_track_right_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_S_BEND_LEFT:
		return inverted_rc_track_s_bend_left;
	case TRACK_ELEM_S_BEND_RIGHT:
		return inverted_rc_track_s_bend_right;
	case TRACK_ELEM_LEFT_VERTICAL_LOOP:
		return inverted_rc_track_left_vertical_loop;
	case TRACK_ELEM_RIGHT_VERTICAL_LOOP:
		return inverted_rc_track_right_vertical_loop;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
		return inverted_rc_track_left_quarter_turn_3;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
		return inverted_rc_track_right_quarter_turn_3;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_BANK:
		return inverted_rc_track_left_quarter_turn_3_bank;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_BANK:
		return inverted_rc_track_right_quarter_turn_3_bank;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return inverted_rc_track_left_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_UP:
		return inverted_rc_track_right_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return inverted_rc_track_left_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES_25_DEG_DOWN:
		return inverted_rc_track_right_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_LEFT_TWIST_DOWN_TO_UP:
		return inverted_rc_track_left_twist_down_to_up;
	case TRACK_ELEM_RIGHT_TWIST_DOWN_TO_UP:
		return inverted_rc_track_right_twist_down_to_up;
	case TRACK_ELEM_LEFT_TWIST_UP_TO_DOWN:
		return inverted_rc_track_left_twist_up_to_down;
	case TRACK_ELEM_RIGHT_TWIST_UP_TO_DOWN:
		return inverted_rc_track_right_twist_up_to_down;
	case TRACK_ELEM_HALF_LOOP_UP:
		return inverted_rc_track_half_loop_up;
	case TRACK_ELEM_HALF_LOOP_DOWN:
		return inverted_rc_track_half_loop_down;
	case TRACK_ELEM_LEFT_CORKSCREW_UP:
		return inverted_rc_track_left_corkscrew_up;
	case TRACK_ELEM_RIGHT_CORKSCREW_UP:
		return inverted_rc_track_right_corkscrew_up;
	case TRACK_ELEM_LEFT_CORKSCREW_DOWN:
		return inverted_rc_track_left_corkscrew_down;
	case TRACK_ELEM_RIGHT_CORKSCREW_DOWN:
		return inverted_rc_track_right_corkscrew_down;
	case TRACK_ELEM_LEFT_QUARTER_TURN_1_TILE_60_DEG_UP:
		return inverted_rc_track_left_quarter_turn_1_60_deg_up;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_1_TILE_60_DEG_UP:
		return inverted_rc_track_right_quarter_turn_1_60_deg_up;
	case TRACK_ELEM_LEFT_QUARTER_TURN_1_TILE_60_DEG_DOWN:
		return inverted_rc_track_left_quarter_turn_1_60_deg_down;
	case TRACK_ELEM_RIGHT_QUARTER_TURN_1_TILE_60_DEG_DOWN:
		return inverted_rc_track_right_quarter_turn_1_60_deg_down;
	case TRACK_ELEM_BRAKES:
		return inverted_rc_track_brakes;
	case TRACK_ELEM_LEFT_QUARTER_BANKED_HELIX_LARGE_UP:
		return inverted_rc_track_left_quarter_banked_helix_large_up;
	case TRACK_ELEM_RIGHT_QUARTER_BANKED_HELIX_LARGE_UP:
		return inverted_rc_track_right_quarter_banked_helix_large_up;
	case TRACK_ELEM_LEFT_QUARTER_BANKED_HELIX_LARGE_DOWN:
		return inverted_rc_track_left_quarter_banked_helix_large_down;
	case TRACK_ELEM_RIGHT_QUARTER_BANKED_HELIX_LARGE_DOWN:
		return inverted_rc_track_right_quarter_banked_helix_large_down;
	case TRACK_ELEM_25_DEG_UP_LEFT_BANKED:
		return inverted_rc_track_25_deg_up_left_banked;
	case TRACK_ELEM_25_DEG_UP_RIGHT_BANKED:
		return inverted_rc_track_25_deg_up_right_banked;
	case TRACK_ELEM_ON_RIDE_PHOTO:
		return inverted_rc_track_on_ride_photo;
	case TRACK_ELEM_25_DEG_DOWN_LEFT_BANKED:
		return inverted_rc_track_25_deg_down_left_banked;
	case TRACK_ELEM_25_DEG_DOWN_RIGHT_BANKED:
		return inverted_rc_track_25_deg_down_right_banked;
	case TRACK_ELEM_LEFT_EIGHTH_TO_DIAG:
		return inverted_rc_track_left_eighth_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_DIAG:
		return inverted_rc_track_right_eighth_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_TO_ORTHOGONAL:
		return inverted_rc_track_left_eighth_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_TO_ORTHOGONAL:
		return inverted_rc_track_right_eighth_to_orthogonal;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_DIAG:
		return inverted_rc_track_left_eighth_bank_to_diag;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_DIAG:
		return inverted_rc_track_right_eighth_bank_to_diag;
	case TRACK_ELEM_LEFT_EIGHTH_BANK_TO_ORTHOGONAL:
		return inverted_rc_track_left_eighth_bank_to_orthogonal;
	case TRACK_ELEM_RIGHT_EIGHTH_BANK_TO_ORTHOGONAL:
		return inverted_rc_track_right_eighth_bank_to_orthogonal;
	case TRACK_ELEM_DIAG_FLAT:
		return inverted_rc_track_diag_flat;
	case TRACK_ELEM_DIAG_25_DEG_UP:
		return inverted_rc_track_diag_25_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP:
		return inverted_rc_track_diag_60_deg_up;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_UP:
		return inverted_rc_track_diag_flat_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_60_DEG_UP:
		return inverted_rc_track_diag_25_deg_up_to_60_deg_up;
	case TRACK_ELEM_DIAG_60_DEG_UP_TO_25_DEG_UP:
		return inverted_rc_track_diag_60_deg_up_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_FLAT:
		return inverted_rc_track_diag_25_deg_up_to_flat;
	case TRACK_ELEM_DIAG_25_DEG_DOWN:
		return inverted_rc_track_diag_25_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN:
		return inverted_rc_track_diag_60_deg_down;
	case TRACK_ELEM_DIAG_FLAT_TO_25_DEG_DOWN:
		return inverted_rc_track_diag_flat_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_60_DEG_DOWN:
		return inverted_rc_track_diag_25_deg_down_to_60_deg_down;
	case TRACK_ELEM_DIAG_60_DEG_DOWN_TO_25_DEG_DOWN:
		return inverted_rc_track_diag_60_deg_down_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_FLAT:
		return inverted_rc_track_diag_25_deg_down_to_flat;
	case TRACK_ELEM_DIAG_FLAT_TO_LEFT_BANK:
		return inverted_rc_track_diag_flat_to_left_bank;
	case TRACK_ELEM_DIAG_FLAT_TO_RIGHT_BANK:
		return inverted_rc_track_diag_flat_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_FLAT:
		return inverted_rc_track_diag_left_bank_to_flat;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_FLAT:
		return inverted_rc_track_diag_right_bank_to_flat;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_UP:
		return inverted_rc_track_diag_left_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_UP:
		return inverted_rc_track_diag_right_bank_to_25_deg_up;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_LEFT_BANK:
		return inverted_rc_track_diag_25_deg_up_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_UP_TO_RIGHT_BANK:
		return inverted_rc_track_diag_25_deg_up_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK_TO_25_DEG_DOWN:
		return inverted_rc_track_diag_left_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_RIGHT_BANK_TO_25_DEG_DOWN:
		return inverted_rc_track_diag_right_bank_to_25_deg_down;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_LEFT_BANK:
		return inverted_rc_track_diag_25_deg_down_to_left_bank;
	case TRACK_ELEM_DIAG_25_DEG_DOWN_TO_RIGHT_BANK:
		return inverted_rc_track_diag_25_deg_down_to_right_bank;
	case TRACK_ELEM_DIAG_LEFT_BANK:
		return inverted_rc_track_diag_left_bank;
	case TRACK_ELEM_DIAG_RIGHT_BANK:
		return inverted_rc_track_diag_right_bank;
	case TRACK_ELEM_LEFT_LARGE_HALF_LOOP_UP:
		return inverted_rc_track_left_large_half_loop_up;
	case TRACK_ELEM_RIGHT_LARGE_HALF_LOOP_UP:
		return inverted_rc_track_right_large_half_loop_up;
	case TRACK_ELEM_RIGHT_LARGE_HALF_LOOP_DOWN:
		return inverted_rc_track_right_large_half_loop_down;
	case TRACK_ELEM_LEFT_LARGE_HALF_LOOP_DOWN:
		return inverted_rc_track_left_large_half_loop_down;
	case TRACK_ELEM_BLOCK_BRAKES:
		return inverted_rc_track_block_brakes;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_3_TILE_25_DEG_UP:
		return inverted_rc_track_left_banked_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_3_TILE_25_DEG_UP:
		return inverted_rc_track_right_banked_quarter_turn_3_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_3_TILE_25_DEG_DOWN:
		return inverted_rc_track_left_banked_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_3_TILE_25_DEG_DOWN:
		return inverted_rc_track_right_banked_quarter_turn_3_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_5_TILE_25_DEG_UP:
		return inverted_rc_track_left_banked_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_5_TILE_25_DEG_UP:
		return inverted_rc_track_right_banked_quarter_turn_5_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_QUARTER_TURN_5_TILE_25_DEG_DOWN:
		return inverted_rc_track_left_banked_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_QUARTER_TURN_5_TILE_25_DEG_DOWN:
		return inverted_rc_track_right_banked_quarter_turn_5_25_deg_down;
	case TRACK_ELEM_25_DEG_UP_TO_LEFT_BANKED_25_DEG_UP:
		return inverted_rc_track_25_deg_up_to_left_banked_25_deg_up;
	case TRACK_ELEM_25_DEG_UP_TO_RIGHT_BANKED_25_DEG_UP:
		return inverted_rc_track_25_deg_up_to_right_banked_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_UP_TO_25_DEG_UP:
		return inverted_rc_track_left_banked_25_deg_up_to_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_UP_TO_25_DEG_UP:
		return inverted_rc_track_right_banked_25_deg_up_to_25_deg_up;
	case TRACK_ELEM_25_DEG_DOWN_TO_LEFT_BANKED_25_DEG_DOWN:
		return inverted_rc_track_25_deg_down_to_left_banked_25_deg_down;
	case TRACK_ELEM_25_DEG_DOWN_TO_RIGHT_BANKED_25_DEG_DOWN:
		return inverted_rc_track_25_deg_down_to_right_banked_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_DOWN_TO_25_DEG_DOWN:
		return inverted_rc_track_left_banked_25_deg_down_to_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_DOWN_TO_25_DEG_DOWN:
		return inverted_rc_track_right_banked_25_deg_down_to_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_FLAT_TO_LEFT_BANKED_25_DEG_UP:
		return inverted_rc_track_left_banked_flat_to_left_banked_25_deg_up;
	case TRACK_ELEM_RIGHT_BANKED_FLAT_TO_RIGHT_BANKED_25_DEG_UP:
		return inverted_rc_track_right_banked_flat_to_right_banked_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_UP_TO_LEFT_BANKED_FLAT:
		return inverted_rc_track_left_banked_25_deg_up_to_left_banked_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_UP_TO_RIGHT_BANKED_FLAT:
		return inverted_rc_track_right_banked_25_deg_up_to_right_banked_flat;
	case TRACK_ELEM_LEFT_BANKED_FLAT_TO_LEFT_BANKED_25_DEG_DOWN:
		return inverted_rc_track_left_banked_flat_to_left_banked_25_deg_down;
	case TRACK_ELEM_RIGHT_BANKED_FLAT_TO_RIGHT_BANKED_25_DEG_DOWN:
		return inverted_rc_track_right_banked_flat_to_right_banked_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_DOWN_TO_LEFT_BANKED_FLAT:
		return inverted_rc_track_left_banked_25_deg_down_to_left_banked_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_DOWN_TO_RIGHT_BANKED_FLAT:
		return inverted_rc_track_right_banked_25_deg_down_to_right_banked_flat;
	case TRACK_ELEM_FLAT_TO_LEFT_BANKED_25_DEG_UP:
		return inverted_rc_track_flat_to_left_banked_25_deg_up;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANKED_25_DEG_UP:
		return inverted_rc_track_flat_to_right_banked_25_deg_up;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_UP_TO_FLAT:
		return inverted_rc_track_left_banked_25_deg_up_to_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_UP_TO_FLAT:
		return inverted_rc_track_right_banked_25_deg_up_to_flat;
	case TRACK_ELEM_FLAT_TO_LEFT_BANKED_25_DEG_DOWN:
		return inverted_rc_track_flat_to_left_banked_25_deg_down;
	case TRACK_ELEM_FLAT_TO_RIGHT_BANKED_25_DEG_DOWN:
		return inverted_rc_track_flat_to_right_banked_25_deg_down;
	case TRACK_ELEM_LEFT_BANKED_25_DEG_DOWN_TO_FLAT:
		return inverted_rc_track_left_banked_25_deg_down_to_flat;
	case TRACK_ELEM_RIGHT_BANKED_25_DEG_DOWN_TO_FLAT:
		return inverted_rc_track_right_banked_25_deg_down_to_flat;
	}
	return NULL;
}
