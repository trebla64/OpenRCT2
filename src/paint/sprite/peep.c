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

#include "../../world/sprite.h"
#include "../../interface/viewport.h"
#include "../../peep/peep.h"
#include "../paint.h"

/**
 *
 *  rct2: 0x0068F0FB
 */
void peep_paint(rct_peep * peep, int imageDirection)
{
	rct_drawpixelinfo * dpi = unk_140E9A8;
	if (dpi->zoom_level > 2) {
		return;
	}

	if (gCurrentViewportFlags & VIEWPORT_FLAG_INVISIBLE_PEEPS) {
		return;
	}

	rct_sprite_entry sprite = g_sprite_entries[peep->sprite_type];

	uint8 spriteType = peep->action_sprite_type;
	uint8 imageOffset = peep->action_sprite_image_offset;

	if (peep->action == PEEP_ACTION_NONE_1) {
		spriteType = peep->next_action_sprite_type;
		imageOffset = 0;
	}

	uint32 baseImageId = (imageDirection >> 3) + sprite.sprite_image[spriteType].base_image + imageOffset * 4;
	uint32 imageId = baseImageId | peep->tshirt_colour << 19 | peep->trousers_colour << 24 | 0xA0000000;
	sub_98197C(imageId, 0, 0, 1, 1, 11, peep->z, 0, 0, peep->z + 3, get_current_rotation());

	if (baseImageId >= 10717 && baseImageId < 10749) {
		imageId = (baseImageId + 32) | peep->hat_colour << 19 | 0x20000000;
		sub_98199C(imageId, 0, 0, 1, 1, 11, peep->z, 0, 0, peep->z + 3, get_current_rotation());
		return;
	}

	if (baseImageId >= 10781 && baseImageId < 10813) {
		imageId = (baseImageId + 32) | peep->balloon_colour << 19 | 0x20000000;
		sub_98199C(imageId, 0, 0, 1, 1, 11, peep->z, 0, 0, peep->z + 3, get_current_rotation());
		return;
	}

	if (baseImageId >= 11197 && baseImageId < 11229) {
		imageId = (baseImageId + 32) | peep->umbrella_colour << 19 | 0x20000000;
		sub_98199C(imageId, 0, 0, 1, 1, 11, peep->z, 0, 0, peep->z + 3, get_current_rotation());
		return;
	}
}
