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

#ifndef _PAINT_MAP_ELEMENT_H
#define _PAINT_MAP_ELEMENT_H

#include "../../common.h"
#include "../../world/map.h"

void map_element_paint_setup(int x, int y);

void entrance_paint(uint8 direction, int height, rct_map_element* map_element);
void banner_paint(uint8 direction, int height, rct_map_element* map_element);
void surface_paint(uint8 direction, uint16 height, rct_map_element *mapElement);
void path_paint(uint8 direction, uint16 height, rct_map_element *mapElement);
void scenery_paint(uint8 direction, int height, rct_map_element* mapElement);
void fence_paint(uint8 direction, int height, rct_map_element* mapElement);
void scenery_multiple_paint(uint8 direction, uint16 height, rct_map_element *mapElement);
void track_paint(uint8 direction, int height, rct_map_element *mapElement);

#endif
