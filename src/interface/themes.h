/*****************************************************************************
* Copyright (c) 2014 Ted John, Peter Hill, Duncan Frost
* OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
*
* This file is part of OpenRCT2.
*
* OpenRCT2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef _THEMES_H_
#define _THEMES_H_

#include "../common.h"
#include "window.h"

enum {
    UITHEME_FLAG_PREDEFINED                            = 1 << 0,
    UITHEME_FLAG_USE_LIGHTS_RIDE                       = 1 << 1,
    UITHEME_FLAG_USE_LIGHTS_PARK                       = 1 << 2,
    UITHEME_FLAG_USE_ALTERNATIVE_SCENARIO_SELECT_FONT  = 1 << 3,
};

void colour_scheme_update(rct_window *window);
void colour_scheme_update_by_class(rct_window *window, rct_windowclass classification);

void         theme_manager_initialise();
void         theme_manager_load_available_themes();
size_t       theme_manager_get_num_available_themes();
const utf8 * theme_manager_get_available_theme_path(size_t index);
const utf8 * theme_manager_get_available_theme_name(size_t index);
size_t       theme_manager_get_active_available_theme_index();
void         theme_manager_set_active_available_theme(size_t index);

colour_t theme_get_colour(rct_windowclass wc, uint8 index);
void     theme_set_colour(rct_windowclass wc, uint8 index, colour_t colour);
uint8    theme_get_flags();
void     theme_set_flags(uint8 flags);
void     theme_save();
void     theme_rename(const utf8 * name);
void     theme_duplicate(const utf8 * name);
void     theme_delete();

uint8         theme_desc_get_num_colours(rct_windowclass wc);
rct_string_id theme_desc_get_name(rct_windowclass wc);

#endif
