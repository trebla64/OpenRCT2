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

#include "../paint.h"
#include "../../addresses.h"
#include "../../config.h"
#include "../../game.h"
#include "../../interface/viewport.h"
#include "../../localisation/localisation.h"
#include "../../world/banner.h"
#include "../../world/scenery.h"

/**
 *
 *  rct2: 0x006B9CC4
 */
void banner_paint(uint8 direction, int height, rct_map_element* map_element)
{
	uint16 boundBoxOffsetX, boundBoxOffsetY, boundBoxOffsetZ;
	rct_drawpixelinfo* dpi = unk_140E9A8;

	gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_BANNER;

	if (dpi->zoom_level > 1 || RCT2_GLOBAL(0x9DEA6F, uint8_t) & 1) return;

	height -= 16;

	rct_scenery_entry* banner_scenery = get_banner_entry(gBanners[map_element->properties.banner.index].type);

	direction += map_element->properties.banner.position;
	direction &= 3;

	boundBoxOffsetX = RCT2_ADDRESS(0x98D884, uint16)[direction * 4];
	boundBoxOffsetY = RCT2_ADDRESS(0x98D884 + 2, uint16)[direction * 4];
	boundBoxOffsetZ = height + 2;

	uint32 base_id = (direction << 1) + banner_scenery->image;
	uint32 image_id = base_id;

	if (map_element->flags & MAP_ELEMENT_FLAG_GHOST)//if being placed
	{
		gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_NONE;
		image_id |= construction_markers[gConfigGeneral.construction_marker_colour];
	}
	else{
		image_id |=
			(gBanners[map_element->properties.banner.index].colour << 19) |
			0x20000000;
	}

	sub_98197C(image_id, 0, 0, 1, 1, 0x15, height, boundBoxOffsetX, boundBoxOffsetY, boundBoxOffsetZ, get_current_rotation());
	boundBoxOffsetX = RCT2_ADDRESS(0x98D888, uint16)[direction * 4];
	boundBoxOffsetY = RCT2_ADDRESS(0x98D888 + 2, uint16)[direction * 4];

	image_id++;
	sub_98197C(image_id, 0, 0, 1, 1, 0x15, height, boundBoxOffsetX, boundBoxOffsetY, boundBoxOffsetZ, get_current_rotation());

	// Opposite direction
	direction ^= 2;
	direction--;
	// If text not showing / ghost
	if (direction >= 2 || (map_element->flags & MAP_ELEMENT_FLAG_GHOST)) return;

	uint16 scrollingMode = banner_scenery->banner.scrolling_mode;
	scrollingMode += direction;

	set_format_arg(0, uint32, 0);
	set_format_arg(4, uint32_t, 0);

	rct_string_id string_id = STR_NO_ENTRY;
	if (!(gBanners[map_element->properties.banner.index].flags & BANNER_FLAG_NO_ENTRY))
	{
		set_format_arg(0, uint16, gBanners[map_element->properties.banner.index].string_idx);
		string_id = STR_BANNER_TEXT_FORMAT;
	}
	if (gConfigGeneral.upper_case_banners) {
		format_string_to_upper(RCT2_ADDRESS(RCT2_ADDRESS_COMMON_STRING_FORMAT_BUFFER, char), string_id, gCommonFormatArgs);
	} else {
		format_string(RCT2_ADDRESS(RCT2_ADDRESS_COMMON_STRING_FORMAT_BUFFER, char), string_id, gCommonFormatArgs);
	}

	gCurrentFontSpriteBase = FONT_SPRITE_BASE_TINY;

	uint16 string_width = gfx_get_string_width(RCT2_ADDRESS(RCT2_ADDRESS_COMMON_STRING_FORMAT_BUFFER, char));
	uint16 scroll = (gCurrentTicks / 2) % string_width;

	sub_98199C(scrolling_text_setup(string_id, scroll, scrollingMode), 0, 0, 1, 1, 0x15, height + 22, boundBoxOffsetX, boundBoxOffsetY, boundBoxOffsetZ, get_current_rotation());
}
