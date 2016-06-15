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

#include "map_element.h"
#include "../../addresses.h"
#include "../../config.h"
#include "../../game.h"
#include "../../interface/viewport.h"
#include "../../localisation/date.h"
#include "../../paint/paint.h"
#include "../../paint/supports.h"
#include "../../world/map.h"
#include "../../world/scenery.h"

static const rct_xy16 offsets[] = {
	{  3,  3 },
	{  3, 17 },
	{ 17,  3 },
	{  3,  3 }
};

static const rct_xy16 lengths[] = {
	{ 12, 26 },
	{ 26, 12 },
	{ 12, 26 },
	{ 26, 12 }
};

/**
 *
 *  rct2: 0x006DFF47
 */
void scenery_paint(uint8 direction, int height, rct_map_element* mapElement) {
	//RCT2_CALLPROC_X(0x6DFF47, 0, 0, direction, height, (int)mapElement, 0, 0); return;
	gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_SCENERY;
	rct_xyz16 boxlength;
	rct_xyz16 boxoffset;
	boxoffset.x = 0;
	boxoffset.y = 0;
	boxoffset.z = height;
	int baseImageid = 0;
	if (RCT2_GLOBAL(0x009DEA6F, uint8) & 1) {
		if (!track_design_save_contains_map_element(mapElement)) {
			baseImageid = 0x21700000;
		}
	}
	if (mapElement->flags & MAP_ELEMENT_FLAG_GHOST) {
		gPaintInteractionType = VIEWPORT_INTERACTION_ITEM_NONE;
		baseImageid = RCT2_ADDRESS(0x993CC4, uint32_t)[gConfigGeneral.construction_marker_colour];
	}
	uint32 dword_F64EB0 = baseImageid;
	
	rct_scenery_entry *entry = get_small_scenery_entry(mapElement->properties.scenery.type);
	baseImageid = entry->image + direction;
	boxlength.x = 2;
	boxlength.y = 2;
	sint8 x_offset = 0;
	sint8 y_offset = 0;
	if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_FULL_TILE) {
		if (entry->small_scenery.flags & SMALL_SCENERY_FLAG24) {
			// 6DFFE3:
			boxoffset.x = offsets[direction].x;
			boxoffset.y = offsets[direction].y;
			boxlength.x = lengths[direction].x;
			boxlength.y = lengths[direction].y;
			x_offset = 3;
			y_offset = 3;
		} else {
			x_offset = 15;
			y_offset = 15;
			if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_VOFFSET_CENTRE) {
				x_offset = 3;
				y_offset = 3;
				boxlength.x = 26;
				boxlength.y = 26;
				if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_ALLOW_WALLS) {
					x_offset = 1;
					y_offset = 1;
					boxlength.x = 30;
					boxlength.y = 30;
				}
			}
			boxoffset.x = x_offset;
			boxoffset.y = y_offset;
		}
	} else {
		// 6DFFC2:
		uint32 ecx = ((mapElement->type >> 6) + get_current_rotation()) & 3;
		x_offset = ScenerySubTileOffsets[ecx].x;
		y_offset = ScenerySubTileOffsets[ecx].y;
		boxoffset.x = x_offset;
		boxoffset.y = y_offset;
	}
	// 6E007F:
	boxlength.z = entry->small_scenery.height - 4;
	if (boxlength.z > 128) {
		boxlength.z = 128;
	}
	if (entry->small_scenery.flags & SMALL_SCENERY_FLAG6) {
		if (mapElement->properties.scenery.age >= 40) {
			baseImageid += 4;
		}
		if (mapElement->properties.scenery.age >= 55) {
			baseImageid += 4;
		}
	}
	if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_HAS_PRIMARY_COLOUR) {
		baseImageid |= ((mapElement->properties.scenery.colour_1 & 0x1F) << 19) | 0x20000000;
		if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_HAS_SECONDARY_COLOUR) {
			baseImageid |= ((mapElement->properties.scenery.colour_2 & 0x1F) << 24) | 0x80000000;
		}
	}
	if (dword_F64EB0 != 0) {
		baseImageid = (baseImageid & 0x7FFFF) | dword_F64EB0;
	}
	if (!(entry->small_scenery.flags & SMALL_SCENERY_FLAG21)) {
		sub_98197C(baseImageid, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
	}

	if (entry->small_scenery.flags & SMALL_SCENERY_FLAG10) {
		if (dword_F64EB0 == 0) {
			// Draw translucent overlay:
			int image_id = (baseImageid & 0x7FFFF) + (((mapElement->properties.scenery.colour_1 & 0x1F) + 112) << 19) + 0x40000004;
			sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
		}
	}

	if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_ANIMATED) {
		rct_drawpixelinfo* dpi = RCT2_GLOBAL(0x140E9A8, rct_drawpixelinfo*);
		if ( !(entry->small_scenery.flags & SMALL_SCENERY_FLAG21) || (dpi->zoom_level <= 1) ) {
			// 6E01A9:
			if (entry->small_scenery.flags & SMALL_SCENERY_FLAG12) {
				// 6E0512:
				int image_id = ((gCurrentTicks / 2) & 0xF) + entry->image + 4;
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
			} else
			if (entry->small_scenery.flags & SMALL_SCENERY_FLAG13) {
				// 6E043B:
				int image_id = ((gCurrentTicks / 2) & 0xF) + entry->image + 8;
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());

				image_id = direction + entry->image + 4;
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());

				image_id = ((gCurrentTicks / 2) & 0xF) + entry->image + 24;
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
			} else
			if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_IS_CLOCK) {
				// 6E035C:
				int minuteImageOffset = ((gRealTimeOfDay.minute + 6) * 17) / 256;
				int timeImageBase = gRealTimeOfDay.hour;
				while (timeImageBase >= 12) {
					timeImageBase -= 12;
				}
				timeImageBase = (timeImageBase * 4) + minuteImageOffset;
				if (timeImageBase >= 48) {
					timeImageBase -= 48;
				}
				int image_id = timeImageBase + (direction * 12);
				if (image_id >= 48) {
					image_id -= 48;
				}
				
				image_id = image_id + entry->image + 68;
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());

				image_id = gRealTimeOfDay.minute + (direction * 15);
				if (image_id >= 60) {
					image_id -= 60;
				}
				image_id = image_id + entry->image + 8;
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
			} else
			if (entry->small_scenery.flags & SMALL_SCENERY_FLAG15) {
				// 6E02F6:
				int image_id = gCurrentTicks;
				image_id += RCT2_GLOBAL(0x009DE568, sint16) / 4;
				image_id += RCT2_GLOBAL(0x009DE56C, sint16) / 4;
				image_id = (image_id / 4) & 15;
				image_id += entry->image;
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
			} else {
				if (entry->small_scenery.flags & SMALL_SCENERY_FLAG16) {
					// nothing
				}
				int esi = gCurrentTicks;
				if (!(entry->small_scenery.flags & SMALL_SCENERY_FLAG22)) {
					// 6E01F8:
					esi += ((RCT2_GLOBAL(0x9DE568, sint16) / 4) + (RCT2_GLOBAL(0x9DE56C, sint16) / 4));
					esi += (mapElement->type & 0xC0) / 16;
				}
				// 6E0222:
				uint16 cx = entry->small_scenery.var_14;
				uint8 cl = cx & 0xFF;
				esi >>= cl;
				esi &= entry->small_scenery.var_16;
				int image_id = 0;
				if (esi < entry->small_scenery.var_18) {
					image_id = ((uint8*)entry->small_scenery.var_10)[esi];
				}
				image_id = (image_id * 4) + direction + entry->image;
				if (entry->small_scenery.flags & (SMALL_SCENERY_FLAG21 | SMALL_SCENERY_FLAG17)) {
					image_id += 4;
				}
				if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_HAS_PRIMARY_COLOUR) {
					image_id |= ((mapElement->properties.scenery.colour_1 & 0x1F) << 19) | 0x20000000;
					if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_HAS_SECONDARY_COLOUR) {
						image_id |= ((mapElement->properties.scenery.colour_1 & 0x1F) << 24) | 0x80000000;
					}
				}
				if (dword_F64EB0 != 0) {
					image_id = (image_id & 0x7FFFF) | dword_F64EB0;
				}
				if (entry->small_scenery.flags & SMALL_SCENERY_FLAG21) {
					sub_98197C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
				} else {
					sub_98199C(image_id, x_offset, y_offset, boxlength.x, boxlength.y, boxlength.z - 1, height, boxoffset.x, boxoffset.y, boxoffset.z, get_current_rotation());
				}
			}
		}
	}
	// 6E0556: Draw supports:
	if (mapElement->properties.scenery.colour_1 & 0x20) {
		if (!(entry->small_scenery.flags & SMALL_SCENERY_FLAG20)) {
			int ax = 0;
			int supportHeight = height;
			if (supportHeight & 0xF) {
				supportHeight &= 0xFFFFFFF0;
				ax = 49;
			}
			uint32 supportImageColourFlags = 0x20000000;
			if (entry->small_scenery.flags & SMALL_SCENERY_FLAG26) {
				supportImageColourFlags = ((mapElement->properties.scenery.colour_1 & 0x1F) << 19) | 0x20000000;
			}
			if (dword_F64EB0 != 0) {
				supportImageColourFlags = dword_F64EB0;
			}
			if (direction & 1) {
				wooden_b_supports_paint_setup(1, ax, supportHeight, supportImageColourFlags);
			} else {
				wooden_b_supports_paint_setup(0, ax, supportHeight, supportImageColourFlags);
			}
		}
	}
	// 6E05D1:
	height += entry->small_scenery.height;
	uint16 word_F64F2A = height;
	height += 7;
	height &= 0xFFF8;
	paint_util_set_general_support_height(height, 0x20);
	// 6E05FF:
	if (entry->small_scenery.flags & SMALL_SCENERY_FLAG23) {
		height = word_F64F2A;
		if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_FULL_TILE) {
			// 6E0825:
			paint_util_set_segment_support_height(SEGMENT_C4, height, 0x20);
			if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_VOFFSET_CENTRE) {
				paint_util_set_segment_support_height(SEGMENTS_ALL & ~SEGMENT_C4, height, 0x20);
			}
			return;
		}
		if (!(entry->small_scenery.flags & SMALL_SCENERY_FLAG_VOFFSET_CENTRE)) {
			return;
		}
		// 6E075C:
		paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, get_current_rotation()), height, 0x20);
		return;
	}
	if (entry->small_scenery.flags & (SMALL_SCENERY_FLAG27 | SMALL_SCENERY_FLAG_FULL_TILE)) {
		paint_util_set_segment_support_height(SEGMENT_C4, 0xFFFF, 0);
		if (entry->small_scenery.flags & SMALL_SCENERY_FLAG_VOFFSET_CENTRE) {
			paint_util_set_segment_support_height(SEGMENTS_ALL & ~SEGMENT_C4, 0xFFFF, 0);
		}
		return;
	}
	if (!(entry->small_scenery.flags & SMALL_SCENERY_FLAG_VOFFSET_CENTRE)) {
		return;
	}
	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, get_current_rotation()), 0xFFFF, 0);
	return;
}
