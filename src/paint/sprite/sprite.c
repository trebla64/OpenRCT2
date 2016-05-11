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

#include "sprite.h"
#include "../paint.h"
#include "../../drawing/drawing.h"
#include "../../world/sprite.h"
#include "../../ride/ride_data.h"
#include "../../interface/viewport.h"
#include "../../ride/vehicle_paint.h"

/**
 * Paint Quadrant
 *  rct2: 0x0069E8B0
 */
void sprite_paint_setup(const uint16 eax, const uint16 ecx) {
	rct_drawpixelinfo* dpi;

	if ((eax & 0xe000) | (ecx & 0xe000)) return;

	const int idx = ((eax << 3) & 0xff00) | (ecx >> 5);
	int sprite_idx = RCT2_ADDRESS(0xF1EF60, uint16)[idx];
	if (sprite_idx == SPRITE_INDEX_NULL) return;

	if (RCT2_GLOBAL(0x9DEA6F, uint8) & 1) return;


	if (gCurrentViewportFlags & VIEWPORT_FLAG_INVISIBLE_SPRITES) return;

	dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);
	if (dpi->zoom_level > 2) return;


	for (rct_sprite* spr = &g_sprite_list[sprite_idx]; sprite_idx != SPRITE_INDEX_NULL; sprite_idx = spr->unknown.next_in_quadrant) {
		spr = &g_sprite_list[sprite_idx];
		dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);

		if (dpi->y + dpi->height <= spr->unknown.sprite_top) continue;
		if (spr->unknown.sprite_bottom <= dpi->y)continue;
		if (dpi->x + dpi->width <= spr->unknown.sprite_left)continue;
		if (spr->unknown.sprite_right <= dpi->x)continue;

		int image_direction = get_current_rotation();
		image_direction <<= 3;
		image_direction += spr->unknown.sprite_direction;
		image_direction &= 0x1F;

		RCT2_GLOBAL(0x9DE578, uint32) = (uint32)spr;

		RCT2_GLOBAL(0x9DE568, sint16) = spr->unknown.x;
		RCT2_GLOBAL(RCT2_ADDRESS_PAINT_SETUP_CURRENT_TYPE, uint8) = VIEWPORT_INTERACTION_ITEM_SPRITE;
		RCT2_GLOBAL(0x9DE56C, sint16) = spr->unknown.y;

		switch (spr->unknown.sprite_identifier) {
		case SPRITE_IDENTIFIER_VEHICLE:
			vehicle_paint((rct_vehicle*)spr, image_direction);
			break;
		case SPRITE_IDENTIFIER_PEEP:
			peep_paint((rct_peep*)spr, image_direction);
			break;
		case SPRITE_IDENTIFIER_MISC:
			misc_paint(spr, image_direction);
			break;
		case SPRITE_IDENTIFIER_LITTER:
			litter_paint((rct_litter*)spr, image_direction);
			break;
		default:
			assert(false);
			break;
		}
	}
}
