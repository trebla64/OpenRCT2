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

#include "../addresses.h"
#include "../config.h"
#include "../game.h"
#include "../sprites.h"
#include "../localisation/localisation.h"
#include "../interface/widget.h"
#include "../interface/window.h"
#include "../interface/themes.h"
#include "../intro.h"

static rct_widget window_title_exit_widgets[] = {
	{ WWT_IMGBTN, 2, 0, 39, 0, 63, SPR_MENU_EXIT, STR_EXIT },
	{ WIDGETS_END },
};

static void window_title_exit_paint(rct_window *w, rct_drawpixelinfo *dpi);
static void window_title_exit_mouseup(rct_window *w, int widgetIndex);
static void window_title_exit_invalidate(rct_window *w);

static rct_window_event_list window_title_exit_events = {
	NULL,
	window_title_exit_mouseup,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	window_title_exit_invalidate,
	window_title_exit_paint,
	NULL
};

/**
 * Creates the window containing the exit button on the title screen.
 *  rct2: 0x0066B624 (part of 0x0066B3E8)
 */
void window_title_exit_open()
{
	rct_window* window;

	window = window_create(
		gScreenWidth - 40, gScreenHeight - 64,
		40, 64,
		&window_title_exit_events,
		WC_TITLE_EXIT,
		WF_STICK_TO_BACK | WF_TRANSPARENT
	);
	window->widgets = window_title_exit_widgets;
	window->enabled_widgets |= 1;
	window_init_scroll_widgets(window);
}

/**
*
*  rct2: 0x0066B83C
*/
static void window_title_exit_mouseup(rct_window *w, int widgetIndex)
{
	if (gIntroState != INTRO_STATE_NONE)
		return;

	if (widgetIndex == 0)
		rct2_quit();
// 		game_do_command(0, 1, 0, 0, 5, 3, 0);
}

/**
*
*  rct2: 0x0066B836
*/
static void window_title_exit_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	window_draw_widgets(w, dpi);
}

static void window_title_exit_invalidate(rct_window *w)
{
	colour_scheme_update(w);
}
