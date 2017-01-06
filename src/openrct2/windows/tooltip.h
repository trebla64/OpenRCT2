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

#ifndef _WINDOW_TOOLTIP_H_
#define _WINDOW_TOOLTIP_H_

#include "../interface/window.h"

void window_tooltip_reset(int x, int y);
void window_tooltip_show(rct_string_id id, int x, int y);
void window_tooltip_open(rct_window *widgetWindow, int widgetIndex, int x, int y);
void window_tooltip_close();

#endif
