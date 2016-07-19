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
#include "../interface/viewport.h"
#include "../interface/widget.h"
#include "../interface/window.h"
#include "../localisation/localisation.h"
#include "../peep/peep.h"
#include "../peep/staff.h"
#include "../sprites.h"
#include "../world/footpath.h"
#include "../world/sprite.h"
#include "../world/scenery.h"
#include "../input.h"
#include "dropdown.h"
#include "error.h"
#include "../interface/themes.h"

#define WW 190
#define WH 180

enum WINDOW_STAFF_PAGE {
	WINDOW_STAFF_OVERVIEW,
	WINDOW_STAFF_OPTIONS,
	WINDOW_STAFF_STATISTICS,
};

enum WINDOW_STAFF_WIDGET_IDX {
	WIDX_BACKGROUND,
	WIDX_TITLE,
	WIDX_CLOSE,
	WIDX_RESIZE,
	WIDX_TAB_1,
	WIDX_TAB_2,
	WIDX_TAB_3,
	WIDX_TAB_4,
	WIDX_VIEWPORT,
	WIDX_BTM_LABEL,
	WIDX_PICKUP,
	WIDX_PATROL,
	WIDX_RENAME,
	WIDX_LOCATE,
	WIDX_FIRE,

	WIDX_CHECKBOX_1 = 8,
	WIDX_CHECKBOX_2,
	WIDX_CHECKBOX_3,
	WIDX_CHECKBOX_4,
	WIDX_COSTUME_BOX,
	WIDX_COSTUME_BTN,
};

rct_widget window_staff_overview_widgets[] = {
	{ WWT_FRAME,	0, 0,		WW - 1,		0,			WH - 1,	0xFFFFFFFF,				STR_NONE },				// Panel / Background
	{ WWT_CAPTION,	0, 1,		WW - 2,		1,			14,		STR_STRINGID,			STR_WINDOW_TITLE_TIP }, // Title
	{ WWT_CLOSEBOX, 0, WW - 13, WW - 3,		2,			13,		STR_CLOSE_X,			STR_CLOSE_WINDOW_TIP }, // Close x button
	{ WWT_RESIZE,	1, 0,		WW - 1,		43,			WH - 1,	0xFFFFFFFF,				STR_NONE },				// Resize
	{ WWT_TAB,		1, 3,		33,			17,			43,		0x20000000 | SPR_TAB,	STR_STAFF_OVERVIEW_TIP },// Tab 1
	{ WWT_TAB,		1, 34,		64,			17,			43,		0x20000000 | SPR_TAB,	STR_STAFF_OPTIONS_TIP},	// Tab 2
	{ WWT_TAB,		1, 65,		95,			17,			43,		0x20000000 | SPR_TAB,	STR_STAFF_STATS_TIP},	// Tab 3
	{ WWT_TAB,		1, 96,		126,		17,			43,		0x20000000 | SPR_TAB,	STR_NONE},				// Tab 4
	{ WWT_VIEWPORT,	1, 3,		WW - 26,	47,			WH - 14,0xFFFFFFFF,				STR_NONE},				// Viewport
	{ WWT_12,		1, 3,		WW - 26,	WH - 13,	WH - 3,	0xFFFFFFFF,				STR_NONE },				// Label at bottom of viewport
	{ WWT_FLATBTN,	1, WW - 25,	WW - 2,		45,			68,		SPR_PICKUP_BTN,			STR_PICKUP_TIP},		// Pickup Button
	{ WWT_FLATBTN,	1, WW - 25,	WW - 2,		69,			92,		SPR_PATROL_BTN,			STR_SET_PATROL_TIP},	// Patrol Button
	{ WWT_FLATBTN,	1, WW - 25,	WW - 2,		93,			116,	SPR_RENAME,				STR_NAME_STAFF_TIP},	// Rename Button
	{ WWT_FLATBTN,	1, WW - 25,	WW - 2,		117,		140,	SPR_LOCATE,				STR_LOCATE_SUBJECT_TIP},// Locate Button
	{ WWT_FLATBTN,	1, WW - 25,	WW - 2,		141,		164,	SPR_DEMOLISH,			STR_FIRE_STAFF_TIP},	// Fire Button
	{ WIDGETS_END },
};

//0x9AF910
rct_widget window_staff_options_widgets[] = {
	{ WWT_FRAME,			0, 0,		WW - 1,	0,		WH - 1,	0xFFFFFFFF,				STR_NONE },				// Panel / Background
	{ WWT_CAPTION,			0, 1,		WW - 2,	1,		14,		STR_STRINGID,			STR_WINDOW_TITLE_TIP }, // Title
	{ WWT_CLOSEBOX,			0, WW - 13, WW - 3,	2,		13,		STR_CLOSE_X,			STR_CLOSE_WINDOW_TIP }, // Close x button
	{ WWT_RESIZE,			1, 0,		WW - 1,	43,		WH - 1,	0xFFFFFFFF,				STR_NONE },				// Resize
	{ WWT_TAB,				1, 3,		33,		17,		43,		0x20000000 | SPR_TAB,	STR_STAFF_OVERVIEW_TIP },// Tab 1
	{ WWT_TAB,				1, 34,		64,		17,		43,		0x20000000 | SPR_TAB,	STR_STAFF_OPTIONS_TIP},	// Tab 2
	{ WWT_TAB,				1, 65,		95,		17,		43,		0x20000000 | SPR_TAB,	STR_STAFF_STATS_TIP},	// Tab 3
	{ WWT_TAB,				1, 96,		126,	17,		43,		0x20000000 | SPR_TAB,	STR_NONE},				// Tab 4
	{ WWT_CHECKBOX,			1, 5,		WW - 6,	50,		61,		0xFFFFFFFF,				STR_NONE},				// Checkbox 1
	{ WWT_CHECKBOX,			1, 5,		WW - 6,	67,		78,		0xFFFFFFFF,				STR_NONE },				// Checkbox 2
	{ WWT_CHECKBOX,			1, 5,		WW - 6,	84,		95,		0xFFFFFFFF,				STR_NONE},				// Checkbox 3
	{ WWT_CHECKBOX,			1, 5,		WW - 6,	101,	112,	0xFFFFFFFF,				STR_NONE},				// Checkbox 4
	{ WWT_DROPDOWN,			1, 5,		WW - 6,	50,		61,		0xFFFFFFFF,				STR_NONE},				// Costume Dropdown
	{ WWT_DROPDOWN_BUTTON,	1, WW - 17,	WW - 7,	51,		60,		STR_DROPDOWN_GLYPH,	STR_SELECT_COSTUME_TIP},// Costume Dropdown Button
	{ WIDGETS_END },
};

//0x9AF9F4
rct_widget window_staff_stats_widgets[] = {
	{ WWT_FRAME,	0, 0,		WW - 1,	0,	WH - 1,	0xFFFFFFFF,				STR_NONE },				// Panel / Background
	{ WWT_CAPTION,	0, 1,		WW - 2,	1,	14,		STR_STRINGID,			STR_WINDOW_TITLE_TIP }, // Title
	{ WWT_CLOSEBOX, 0, WW - 13, WW - 3,	2,	13,		STR_CLOSE_X,			STR_CLOSE_WINDOW_TIP }, // Close x button
	{ WWT_RESIZE,	1, 0,		WW - 1,	43,	WH - 1,	0xFFFFFFFF,				STR_NONE },				// Resize
	{ WWT_TAB,		1, 3,		33,		17,	43,		0x20000000 | SPR_TAB,	STR_STAFF_OVERVIEW_TIP },// Tab 1
	{ WWT_TAB,		1, 34,		64,		17,	43,		0x20000000 | SPR_TAB,	STR_STAFF_OPTIONS_TIP},	// Tab 2
	{ WWT_TAB,		1, 65,		95,		17,	43,		0x20000000 | SPR_TAB,	STR_STAFF_STATS_TIP},	// Tab 3
	{ WWT_TAB,		1, 96,		126,	17,	43,		0x20000000 | SPR_TAB,	STR_NONE},				// Tab 4
	{ WIDGETS_END },
};

rct_widget *window_staff_page_widgets[] = {
	window_staff_overview_widgets,
	window_staff_options_widgets,
	window_staff_stats_widgets
};

void window_staff_set_page(rct_window* w, int page);
void window_staff_disable_widgets(rct_window* w);
void window_staff_unknown_05(rct_window *w);
void window_staff_viewport_init(rct_window* w);

void window_staff_overview_close(rct_window *w);
void window_staff_overview_mouseup(rct_window *w, int widgetIndex);
void window_staff_overview_resize(rct_window *w);
void window_staff_overview_mousedown(int widgetIndex, rct_window* w, rct_widget* widget);
void window_staff_overview_dropdown(rct_window *w, int widgetIndex, int dropdownIndex);
void window_staff_overview_update(rct_window* w);
void window_staff_overview_invalidate(rct_window *w);
void window_staff_overview_paint(rct_window *w, rct_drawpixelinfo *dpi);
void window_staff_overview_tab_paint(rct_window* w, rct_drawpixelinfo* dpi);
void window_staff_overview_tool_update(rct_window* w, int widgetIndex, int x, int y);
void window_staff_overview_tool_down(rct_window* w, int widgetIndex, int x, int y);
void window_staff_overview_tool_abort(rct_window *w, int widgetIndex);
void window_staff_overview_text_input(rct_window *w, int widgetIndex, char *text);
void window_staff_overview_unknown_14(rct_window *w);

void window_staff_options_mouseup(rct_window *w, int widgetIndex);
void window_staff_options_update(rct_window* w);
void window_staff_options_invalidate(rct_window *w);
void window_staff_options_paint(rct_window *w, rct_drawpixelinfo *dpi);
void window_staff_options_tab_paint(rct_window* w, rct_drawpixelinfo* dpi);
void window_staff_options_mousedown(int widgetIndex, rct_window* w, rct_widget* widget);
void window_staff_options_dropdown(rct_window *w, int widgetIndex, int dropdownIndex);

void window_staff_stats_mouseup(rct_window *w, int widgetIndex);
void window_staff_stats_resize(rct_window *w);
void window_staff_stats_update(rct_window* w);
void window_staff_stats_invalidate(rct_window *w);
void window_staff_stats_paint(rct_window *w, rct_drawpixelinfo *dpi);
void window_staff_stats_tab_paint(rct_window* w, rct_drawpixelinfo* dpi);

void window_staff_set_colours();

// 0x992AEC
static rct_window_event_list window_staff_overview_events = {
	window_staff_overview_close,
	window_staff_overview_mouseup,
	window_staff_overview_resize,
	window_staff_overview_mousedown,
	window_staff_overview_dropdown,
	NULL,
	window_staff_overview_update,
	NULL,
	NULL,
	window_staff_overview_tool_update,
	window_staff_overview_tool_down,
	NULL,
	NULL,
	window_staff_overview_tool_abort,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	window_staff_overview_text_input,
	window_staff_overview_unknown_14,
	NULL,
	NULL,
	NULL,
	NULL,
	window_staff_overview_invalidate, //Invalidate
	window_staff_overview_paint, //Paint
	NULL
};

// 0x992B5C
static rct_window_event_list window_staff_options_events = {
	NULL,
	window_staff_options_mouseup,
	window_staff_stats_resize,
	window_staff_options_mousedown,
	window_staff_options_dropdown,
	window_staff_unknown_05,
	window_staff_options_update,
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
	window_staff_options_invalidate, //Invalidate
	window_staff_options_paint, //Paint
	NULL
};

// 0x992BCC
static rct_window_event_list window_staff_stats_events = {
	NULL,
	window_staff_stats_mouseup,
	window_staff_stats_resize,
	NULL,
	NULL,
	window_staff_unknown_05,
	window_staff_stats_update,
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
	window_staff_stats_invalidate, //Invalidate
	window_staff_stats_paint, //Paint
	NULL
};

static rct_window_event_list *window_staff_page_events[] = {
	&window_staff_overview_events,
	&window_staff_options_events,
	&window_staff_stats_events
};

uint32 window_staff_page_enabled_widgets[] = {
	(1 << WIDX_CLOSE) |
	(1 << WIDX_TAB_1) |
	(1 << WIDX_TAB_2) |
	(1 << WIDX_TAB_3) |
	(1 << WIDX_PICKUP) |
	(1 << WIDX_PATROL) |
	(1 << WIDX_RENAME) |
	(1 << WIDX_LOCATE) |
	(1 << WIDX_FIRE),

	(1 << WIDX_CLOSE) |
	(1 << WIDX_TAB_1) |
	(1 << WIDX_TAB_2) |
	(1 << WIDX_TAB_3) |
	(1 << WIDX_CHECKBOX_1) |
	(1 << WIDX_CHECKBOX_2) |
	(1 << WIDX_CHECKBOX_3) |
	(1 << WIDX_CHECKBOX_4) |
	(1 << WIDX_COSTUME_BTN),

	(1 << WIDX_CLOSE) |
	(1 << WIDX_TAB_1) |
	(1 << WIDX_TAB_2) |
	(1 << WIDX_TAB_3)
};

static const uint32 staffCostumeNames[] = {
	STR_STAFF_OPTION_COSTUME_PANDA,
	STR_STAFF_OPTION_COSTUME_TIGER,
	STR_STAFF_OPTION_COSTUME_ELEPHANT,
	STR_STAFF_OPTION_COSTUME_ROMAN,
	STR_STAFF_OPTION_COSTUME_GORILLA,
	STR_STAFF_OPTION_COSTUME_SNOWMAN,
	STR_STAFF_OPTION_COSTUME_KNIGHT,
	STR_STAFF_OPTION_COSTUME_ASTRONAUT,
	STR_STAFF_OPTION_COSTUME_BANDIT,
	STR_STAFF_OPTION_COSTUME_SHERIFF,
	STR_STAFF_OPTION_COSTUME_PIRATE,
};

/**
*
*  rct2: 0x006BEE98
*/
rct_window *window_staff_open(rct_peep* peep)
{
	rct_window* w = window_bring_to_front_by_number(WC_PEEP, peep->sprite_index);
	if (w == NULL) {
		w = window_create_auto_pos(WW, WH, &window_staff_overview_events, WC_PEEP, WF_10 | WF_RESIZABLE);

		w->number = peep->sprite_index;
		w->page = 0;
		w->viewport_focus_coordinates.y = 0;
		w->frame_no = 0;
		w->highlighted_item = 0;

		window_staff_disable_widgets(w);

		w->min_width = WW;
		w->min_height = WH;
		w->max_width = 500;
		w->max_height = 450;
	}
	w->page = 0;
	window_invalidate(w);

	w->widgets = window_staff_overview_widgets;
	w->enabled_widgets = window_staff_page_enabled_widgets[0];
	w->hold_down_widgets = 0;
	w->event_handlers = window_staff_page_events[0];
	w->pressed_widgets = 0;
	window_staff_disable_widgets(w);
	window_init_scroll_widgets(w);
	window_staff_viewport_init(w);
	if (get_sprite(w->number)->peep.state == PEEP_STATE_PICKED)
		window_event_mouse_up_call(w, WIDX_CHECKBOX_3);

	return w;
}

/**
* rct2: 0x006BED21
* Disable the staff pickup if not in pickup state.
*/
void window_staff_disable_widgets(rct_window* w)
{
	rct_peep* peep = &get_sprite(w->number)->peep;
	uint64 disabled_widgets = (1 << WIDX_TAB_4);

	if (peep->staff_type == STAFF_TYPE_SECURITY){
		disabled_widgets |= (1 << WIDX_TAB_2);
	}

	if (w->page == WINDOW_STAFF_OVERVIEW){
		if (peep_can_be_picked_up(peep)){
			if (w->disabled_widgets & (1 << WIDX_PICKUP))
				window_invalidate(w);
		}
		else{
			disabled_widgets |= (1 << WIDX_PICKUP);
			if (!(w->disabled_widgets & (1 << WIDX_PICKUP)))
				window_invalidate(w);
		}
	}

	w->disabled_widgets = disabled_widgets;
}

/**
 * Same as window_peep_overview_close.
 *  rct2: 0x006BDFF8
 */
void window_staff_overview_close(rct_window *w)
{
	if (gInputFlags & INPUT_FLAG_TOOL_ACTIVE){
		if (w->classification == gCurrentToolWidget.window_classification &&
			w->number == gCurrentToolWidget.window_number)
			tool_cancel();
	}
}

/**
 * Mostly similar to window_peep_set_page.
 *  rct2: 0x006BE023
 */
void window_staff_set_page(rct_window* w, int page)
{
	if (gInputFlags & INPUT_FLAG_TOOL_ACTIVE)
	{
		if(w->number == gCurrentToolWidget.window_number &&
		   w->classification == gCurrentToolWidget.window_classification)
			tool_cancel();

	}

	int listen = 0;
	if (page == WINDOW_STAFF_OVERVIEW && w->page == WINDOW_STAFF_OVERVIEW && w->viewport){
		if (!(w->viewport->flags & VIEWPORT_FLAG_SOUND_ON))
			listen = 1;
	}


	w->page = page;
	w->frame_no = 0;

	rct_viewport* viewport = w->viewport;
	w->viewport = 0;
	if (viewport){
		viewport->width = 0;
	}

	w->enabled_widgets = window_staff_page_enabled_widgets[page];
	w->hold_down_widgets = 0;
	w->event_handlers = window_staff_page_events[page];
	w->pressed_widgets = 0;
	w->widgets = window_staff_page_widgets[page];

	window_staff_disable_widgets(w);
	window_invalidate(w);

	window_event_resize_call(w);
	window_event_invalidate_call(w);

	window_init_scroll_widgets(w);
	window_invalidate(w);

	if (listen && w->viewport) w->viewport->flags |= VIEWPORT_FLAG_SOUND_ON;
}

/**
 *
 *  rct2: 0x006BDF55
 */
void window_staff_overview_mouseup(rct_window *w, int widgetIndex)
{
	rct_peep* peep = GET_PEEP(w->number);

	switch (widgetIndex) {
	case WIDX_CLOSE:
		window_close(w);
		break;
	case WIDX_TAB_1:
	case WIDX_TAB_2:
	case WIDX_TAB_3:
		window_staff_set_page(w, widgetIndex - WIDX_TAB_1);
		break;
	case WIDX_LOCATE:
		window_scroll_to_viewport(w);
		break;
	case WIDX_PICKUP:
		if (tool_set(w, widgetIndex, 7)) {
			return;
		}

		w->picked_peep_old_x = peep->x;

		remove_peep_from_ride(peep);
		invalidate_sprite_2((rct_sprite*)peep);

		sprite_move( 0x8000, peep->y, peep->z, (rct_sprite*)peep);
		peep_decrement_num_riders(peep);
		peep->state = PEEP_STATE_PICKED;
		peep_window_state_update(peep);
		break;
	case WIDX_FIRE:
		window_staff_fire_prompt_open(peep);
		break;
	case WIDX_RENAME:
		window_text_input_open(w, widgetIndex, STR_STAFF_TITLE_STAFF_MEMBER_NAME, STR_STAFF_PROMPT_ENTER_NAME, peep->name_string_idx, peep->id, 32);
		break;
	}
}

/**
 *
 *  rct2: 0x006BE558
 */
void window_staff_overview_resize(rct_window *w)
{
	window_staff_disable_widgets(w);

	w->min_width = WW;
	w->max_width = 500;
	w->min_height = WH;
	w->max_height = 450;

	if (w->width < w->min_width) {
		w->width = w->min_width;
		window_invalidate(w);
	}

	if (w->width > w->max_width) {
		window_invalidate(w);
		w->width = w->max_width;
	}

	if (w->height < w->min_height) {
		w->height = w->min_height;
		window_invalidate(w);
	}

	if (w->height > w->max_height) {
		window_invalidate(w);
		w->height = w->max_height;
	}

	rct_viewport* viewport = w->viewport;

	if (viewport) {
		int new_width = w->width - 30;
		int new_height = w->height - 62;

		// Update the viewport size
		if (viewport->width != new_width || viewport->height != new_height) {
			viewport->width = new_width;
			viewport->height = new_height;
			viewport->view_width = new_width << viewport->zoom;
			viewport->view_height = new_height << viewport->zoom;
		}
	}

	window_staff_viewport_init(w);
}

/**
 * Handle the dropdown of patrol button.
 *  rct2: 0x006BDF98
 */
void window_staff_overview_mousedown(int widgetIndex, rct_window* w, rct_widget* widget)
{
	if (widgetIndex != WIDX_PATROL) {
		return;
	}

	// Dropdown names
	gDropdownItemsFormat[0] = STR_SET_PATROL_AREA;
	gDropdownItemsFormat[1] = STR_CLEAR_PATROL_AREA;

	int x = widget->left + w->x;
	int y = widget->top + w->y;
	int extray = widget->bottom - widget->top + 1;
	window_dropdown_show_text(x, y, extray, w->colours[1], 0, 2);
	gDropdownDefaultIndex = 0;

	rct_peep* peep = GET_PEEP(w->number);

	// Disable clear patrol area if no area is set.
	if (!(RCT2_ADDRESS(RCT2_ADDRESS_STAFF_MODE_ARRAY, uint8)[peep->staff_id] & 2)) {
		gDropdownItemsDisabled |= (1ULL << 1);
	}
}

/**
 *
 *  rct2: 0x006BDFA3
 */
void window_staff_overview_dropdown(rct_window *w, int widgetIndex, int dropdownIndex)
{
	if (widgetIndex != WIDX_PATROL) {
		return;
	}

	// Clear patrol
	if (dropdownIndex == 1) {
		rct_peep* peep = GET_PEEP(w->number);

		for (int i = 0; i < 128; i++)
		{
			RCT2_ADDRESS(RCT2_ADDRESS_STAFF_PATROL_AREAS + (peep->staff_id * 512), uint32)[i] = 0;
		}
		RCT2_ADDRESS(RCT2_ADDRESS_STAFF_MODE_ARRAY, uint8)[peep->staff_id] &= ~2;

		gfx_invalidate_screen();
		staff_update_greyed_patrol_areas();
	}
	else {
		if (!tool_set(w, widgetIndex, 22)) {
			show_gridlines();
			gStaffDrawPatrolAreas = w->number;
			gfx_invalidate_screen();
		}
	}
}

/**
 * Update the animation frame of the tab icon.
 *  rct2: 0x6BE602
 */
void window_staff_overview_update(rct_window* w)
{
	int var_496 = RCT2_GLOBAL((int)w + 0x496, uint16);
	var_496++;
	if (var_496 >= 24) {
		var_496 = 0;
	}
	RCT2_GLOBAL((int)w + 0x496, uint16) = var_496;
	widget_invalidate(w, WIDX_TAB_1);
}

/**
 *
 *  rct2: 0x006BE814
 */
static void window_staff_set_order(rct_window* w, int order_id)
{
	rct_peep* peep = GET_PEEP(w->number);

	int ax = peep->staff_orders ^ (1 << order_id);
	int flags = (ax << 8) | 1;

	game_do_command(peep->x, flags, peep->y, w->number, GAME_COMMAND_SET_STAFF_ORDER, (int)peep, 0);
}

/**
 *
 *  rct2: 0x006BE7DB
 */
void window_staff_options_mouseup(rct_window *w, int widgetIndex)
{
	switch (widgetIndex) {
	case WIDX_CLOSE:
		window_close(w);
		break;
	case WIDX_TAB_1:
	case WIDX_TAB_2:
	case WIDX_TAB_3:
		window_staff_set_page(w, widgetIndex - WIDX_TAB_1);
		break;
	case WIDX_CHECKBOX_1:
	case WIDX_CHECKBOX_2:
	case WIDX_CHECKBOX_3:
	case WIDX_CHECKBOX_4:
		window_staff_set_order(w, widgetIndex - WIDX_CHECKBOX_1);
		break;
	}
}

/**
 *
 *  rct2: 0x006BE960
 */
void window_staff_options_update(rct_window* w)
{
	w->frame_no++;
	widget_invalidate(w, WIDX_TAB_2);
}

/**
 *
 *  rct2: 0x006BEBCF
 */
void window_staff_stats_mouseup(rct_window *w, int widgetIndex)
{
	switch (widgetIndex) {
	case WIDX_CLOSE:
		window_close(w);
		break;
	case WIDX_TAB_1:
	case WIDX_TAB_2:
	case WIDX_TAB_3:
		window_staff_set_page(w, widgetIndex - WIDX_TAB_1);
		break;
	}
}

/**
 *
 *  rct2: 0x006BEC1B, 0x006BE975
 */
void window_staff_stats_resize(rct_window *w)
{
	w->min_width = 190;
	w->max_width = 190;
	w->min_height = 119;
	w->max_height = 119;

	if (w->width < w->min_width) {
		w->width = w->min_width;
		window_invalidate(w);
	}

	if (w->width > w->max_width) {
		window_invalidate(w);
		w->width = w->max_width;
	}

	if (w->height < w->min_height) {
		w->height = w->min_height;
		window_invalidate(w);
	}

	if (w->height > w->max_height) {
		window_invalidate(w);
		w->height = w->max_height;
	}
}

/**
 *
 *  rct2: 0x006BEBEA
 */
void window_staff_stats_update(rct_window* w)
{
	w->frame_no++;
	widget_invalidate(w, WIDX_TAB_3);

	rct_peep* peep = GET_PEEP(w->number);
	if (peep->window_invalidate_flags & PEEP_INVALIDATE_STAFF_STATS) {
		peep->window_invalidate_flags &= ~PEEP_INVALIDATE_STAFF_STATS;
		window_invalidate(w);
	}
}

/**
 *
 *  rct2: 0x6BEC80, 0x6BE9DA
 */
void window_staff_unknown_05(rct_window *w)
{
	widget_invalidate(w, WIDX_TAB_1);
}

/**
 *
 *  rct2: 0x006BE9E9
 */
void window_staff_stats_invalidate(rct_window *w)
{
	colour_scheme_update_by_class(w, (rct_windowclass)WC_STAFF);

	if (window_staff_page_widgets[w->page] != w->widgets){
		w->widgets = window_staff_page_widgets[w->page];
		window_init_scroll_widgets(w);
	}

	w->pressed_widgets |= 1ULL << (w->page + WIDX_TAB_1);

	rct_peep* peep = GET_PEEP(w->number);

	set_format_arg(0, uint16, peep->name_string_idx);
	set_format_arg(2, uint32, peep->id);

	window_staff_stats_widgets[WIDX_BACKGROUND].right = w->width - 1;
	window_staff_stats_widgets[WIDX_BACKGROUND].bottom = w->height - 1;

	window_staff_stats_widgets[WIDX_RESIZE].right = w->width - 1;
	window_staff_stats_widgets[WIDX_RESIZE].bottom = w->height - 1;

	window_staff_stats_widgets[WIDX_TITLE].right = w->width - 2;

	window_staff_stats_widgets[WIDX_CLOSE].left = w->width - 13;
	window_staff_stats_widgets[WIDX_CLOSE].right = w->width - 3;

	window_align_tabs(w, WIDX_TAB_1, WIDX_TAB_3);
}


/**
 *
 *  rct2: 0x006BE62B
 */
void window_staff_options_invalidate(rct_window *w)
{
	colour_scheme_update_by_class(w, (rct_windowclass)WC_STAFF);

	if (window_staff_page_widgets[w->page] != w->widgets){
		w->widgets = window_staff_page_widgets[w->page];
		window_init_scroll_widgets(w);
	}

	w->pressed_widgets |= 1ULL << (w->page + WIDX_TAB_1);

	rct_peep* peep = GET_PEEP(w->number);

	set_format_arg(0, uint16, peep->name_string_idx);
	set_format_arg(2, uint32, peep->id);

	switch (peep->staff_type){
	case STAFF_TYPE_ENTERTAINER:
		window_staff_options_widgets[WIDX_CHECKBOX_1].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_CHECKBOX_2].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_CHECKBOX_3].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_CHECKBOX_4].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_COSTUME_BOX].type = WWT_DROPDOWN;
		window_staff_options_widgets[WIDX_COSTUME_BTN].type = WWT_DROPDOWN_BUTTON;
		window_staff_options_widgets[WIDX_COSTUME_BOX].text = staffCostumeNames[peep->sprite_type - 4];
		break;
	case STAFF_TYPE_HANDYMAN:
		window_staff_options_widgets[WIDX_CHECKBOX_1].type = WWT_CHECKBOX;
		window_staff_options_widgets[WIDX_CHECKBOX_1].text = STR_STAFF_OPTION_SWEEP_FOOTPATHS;
		window_staff_options_widgets[WIDX_CHECKBOX_2].type = WWT_CHECKBOX;
		window_staff_options_widgets[WIDX_CHECKBOX_2].text = STR_STAFF_OPTION_WATER_GARDENS;
		window_staff_options_widgets[WIDX_CHECKBOX_3].type = WWT_CHECKBOX;
		window_staff_options_widgets[WIDX_CHECKBOX_3].text = STR_STAFF_OPTION_EMPTY_LITTER;
		window_staff_options_widgets[WIDX_CHECKBOX_4].type = WWT_CHECKBOX;
		window_staff_options_widgets[WIDX_CHECKBOX_4].text = STR_STAFF_OPTION_MOW_GRASS;
		window_staff_options_widgets[WIDX_COSTUME_BOX].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_COSTUME_BTN].type = WWT_EMPTY;
		w->pressed_widgets &= ~((1 << WIDX_CHECKBOX_1) | (1 << WIDX_CHECKBOX_2) | (1 << WIDX_CHECKBOX_3) | (1 << WIDX_CHECKBOX_4));
		w->pressed_widgets |= peep->staff_orders << WIDX_CHECKBOX_1;
		break;
	case STAFF_TYPE_MECHANIC:
		window_staff_options_widgets[WIDX_CHECKBOX_1].type = WWT_CHECKBOX;
		window_staff_options_widgets[WIDX_CHECKBOX_1].text = STR_INSPECT_RIDES;
		window_staff_options_widgets[WIDX_CHECKBOX_2].type = WWT_CHECKBOX;
		window_staff_options_widgets[WIDX_CHECKBOX_2].text = STR_FIX_RIDES;
		window_staff_options_widgets[WIDX_CHECKBOX_3].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_CHECKBOX_4].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_COSTUME_BOX].type = WWT_EMPTY;
		window_staff_options_widgets[WIDX_COSTUME_BTN].type = WWT_EMPTY;
		w->pressed_widgets &= ~((1 << WIDX_CHECKBOX_1) | (1 << WIDX_CHECKBOX_2));
		w->pressed_widgets |= peep->staff_orders << WIDX_CHECKBOX_1;
		break;
	case STAFF_TYPE_SECURITY:
		// Security guards don't have an options screen.
		break;
	}

	window_staff_options_widgets[WIDX_BACKGROUND].right = w->width - 1;
	window_staff_options_widgets[WIDX_BACKGROUND].bottom = w->height - 1;

	window_staff_options_widgets[WIDX_RESIZE].right = w->width - 1;
	window_staff_options_widgets[WIDX_RESIZE].bottom = w->height - 1;

	window_staff_options_widgets[WIDX_TITLE].right = w->width - 2;

	window_staff_options_widgets[WIDX_CLOSE].left = w->width - 13;
	window_staff_options_widgets[WIDX_CLOSE].right = w->width - 3;

	window_align_tabs(w, WIDX_TAB_1, WIDX_TAB_3);
}

/**
 *
 *  rct2: 0x006BDD91
 */
void window_staff_overview_invalidate(rct_window *w)
{
	colour_scheme_update_by_class(w, (rct_windowclass)WC_STAFF);

	if (window_staff_page_widgets[w->page] != w->widgets){
		w->widgets = window_staff_page_widgets[w->page];
		window_init_scroll_widgets(w);
	}

	w->pressed_widgets |= 1ULL << (w->page + WIDX_TAB_1);

	rct_peep* peep = GET_PEEP(w->number);

	set_format_arg(0, uint16, peep->name_string_idx);
	set_format_arg(2, uint32, peep->id);

	window_staff_overview_widgets[WIDX_BACKGROUND].right = w->width - 1;
	window_staff_overview_widgets[WIDX_BACKGROUND].bottom = w->height - 1;

	window_staff_overview_widgets[WIDX_RESIZE].right = w->width - 1;
	window_staff_overview_widgets[WIDX_RESIZE].bottom = w->height - 1;

	window_staff_overview_widgets[WIDX_TITLE].right = w->width - 2;

	window_staff_overview_widgets[WIDX_VIEWPORT].right = w->width - 26;
	window_staff_overview_widgets[WIDX_VIEWPORT].bottom = w->height - 14;

	window_staff_overview_widgets[WIDX_BTM_LABEL].right = w->width - 26;
	window_staff_overview_widgets[WIDX_BTM_LABEL].top = w->height - 13;
	window_staff_overview_widgets[WIDX_BTM_LABEL].bottom = w->height - 3;

	window_staff_overview_widgets[WIDX_CLOSE].left = w->width - 13;
	window_staff_overview_widgets[WIDX_CLOSE].right = w->width - 3;

	window_staff_overview_widgets[WIDX_PICKUP].left = w->width - 25;
	window_staff_overview_widgets[WIDX_PICKUP].right = w->width - 2;

	window_staff_overview_widgets[WIDX_PATROL].left = w->width - 25;
	window_staff_overview_widgets[WIDX_PATROL].right = w->width - 2;

	window_staff_overview_widgets[WIDX_RENAME].left = w->width - 25;
	window_staff_overview_widgets[WIDX_RENAME].right = w->width - 2;

	window_staff_overview_widgets[WIDX_LOCATE].left = w->width - 25;
	window_staff_overview_widgets[WIDX_LOCATE].right = w->width - 2;

	window_staff_overview_widgets[WIDX_FIRE].left = w->width - 25;
	window_staff_overview_widgets[WIDX_FIRE].right = w->width - 2;

	window_align_tabs(w, WIDX_TAB_1, WIDX_TAB_3);
}

/**
 *
 *  rct2: 0x6BDEAF
 */
void window_staff_overview_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	window_draw_widgets(w, dpi);
	window_staff_overview_tab_paint(w, dpi);
	window_staff_options_tab_paint(w, dpi);
	window_staff_stats_tab_paint(w, dpi);


	// Draw the viewport no sound sprite
	if (w->viewport){
		window_draw_viewport(dpi, w);
		rct_viewport* viewport = w->viewport;
		if (viewport->flags & VIEWPORT_FLAG_SOUND_ON){
			gfx_draw_sprite(dpi, SPR_HEARING_VIEWPORT, w->x + 2, w->y + 2, 0);
		}
	}

	// Draw the centered label
	uint32 argument1, argument2;
	rct_peep* peep = GET_PEEP(w->number);
	get_arguments_from_action(peep, &argument1, &argument2);
	set_format_arg(0, uint32, argument1);
	set_format_arg(4, uint32, argument2);
	rct_widget* widget = &w->widgets[WIDX_BTM_LABEL];
	int x = (widget->left + widget->right) / 2 + w->x;
	int y = w->y + widget->top;
	int width = widget->right - widget->left;
	gfx_draw_string_centred_clipped(dpi, STR_BLACK_STRING, gCommonFormatArgs, 0, x, y, width);
}

/**
 *
 *  rct2: 0x6BEC8F
 */
void window_staff_options_tab_paint(rct_window* w, rct_drawpixelinfo* dpi)
{
	if (w->disabled_widgets & (1 << WIDX_TAB_2)) return;

	rct_widget* widget = &w->widgets[WIDX_TAB_2];
	int x = widget->left + w->x;
	int y = widget->top + w->y;

	int image_id = SPR_TAB_STAFF_OPTIONS_0;

	if (w->page == WINDOW_STAFF_OPTIONS){
		image_id += (w->frame_no / 2) % 7;
	}

	gfx_draw_sprite(dpi, image_id, x, y, 0);
}

/**
 *
 *  rct2: 0x6BECD3
 */
void window_staff_stats_tab_paint(rct_window* w, rct_drawpixelinfo* dpi)
{
	if (w->disabled_widgets & (1 << WIDX_TAB_3)) return;

	rct_widget* widget = &w->widgets[WIDX_TAB_3];
	int x = widget->left + w->x;
	int y = widget->top + w->y;

	int image_id = SPR_TAB_STATS_0;

	if (w->page == WINDOW_STAFF_STATISTICS){
		image_id += (w->frame_no / 4) % 7;
	}

	gfx_draw_sprite(dpi, image_id, x, y, 0);
}

/**
* Based on rct2: 0x6983dd in window_guest to be remerged into one when peep file added.
*/
void window_staff_overview_tab_paint(rct_window* w, rct_drawpixelinfo* dpi)
{
	if (w->disabled_widgets & (1 << WIDX_TAB_1))
		return;

	rct_widget* widget = &w->widgets[WIDX_TAB_1];
	int width = widget->right - widget->left - 1;
	int height = widget->bottom - widget->top - 1;
	int x = widget->left + 1 + w->x;
	int y = widget->top + 1 + w->y;
	if (w->page == WINDOW_STAFF_OVERVIEW) height++;

	rct_drawpixelinfo clip_dpi;
	if (!clip_drawpixelinfo(&clip_dpi, dpi, x, y, width, height)) {
		return;
	}

	x = 14;
	y = 20;

	rct_peep* peep = GET_PEEP(w->number);

	if (peep->type == PEEP_TYPE_STAFF && peep->staff_type == STAFF_TYPE_ENTERTAINER)
		y++;

	int ebx = g_sprite_entries[peep->sprite_type].sprite_image->base_image + 1;

	int eax = 0;

	if (w->page == WINDOW_STAFF_OVERVIEW){
		eax = w->highlighted_item >> 16;
		eax &= 0xFFFC;
	}
	ebx += eax;

	int sprite_id = ebx | (peep->tshirt_colour << 19) | (peep->trousers_colour << 24) | 0xA0000000;
	gfx_draw_sprite(&clip_dpi, sprite_id, x, y, 0);

	// If holding a balloon
	if (ebx >= 0x2A1D && ebx < 0x2A3D){
		ebx += 32;
		ebx |= (peep->balloon_colour << 19) | 0x20000000;
		gfx_draw_sprite(&clip_dpi, ebx, x, y, 0);
	}

	// If holding umbrella
	if (ebx >= 0x2BBD && ebx < 0x2BDD){
		ebx += 32;
		ebx |= (peep->umbrella_colour << 19) | 0x20000000;
		gfx_draw_sprite(&clip_dpi, ebx, x, y, 0);
	}

	// If wearing hat
	if (ebx >= 0x29DD && ebx < 0x29FD){
		ebx += 32;
		ebx |= (peep->hat_colour << 19) | 0x20000000;
		gfx_draw_sprite(&clip_dpi, ebx, x, y, 0);
	}
}

/**
 *
 *  rct2: 0x6BE7C6
 */
void window_staff_options_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	window_draw_widgets(w, dpi);
	window_staff_overview_tab_paint(w, dpi);
	window_staff_options_tab_paint(w, dpi);
	window_staff_stats_tab_paint(w, dpi);
}

/**
 *
 *  rct2: 0x6BEA86
 */
void window_staff_stats_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	window_draw_widgets(w, dpi);
	window_staff_overview_tab_paint(w, dpi);
	window_staff_options_tab_paint(w, dpi);
	window_staff_stats_tab_paint(w, dpi);

	rct_peep* peep = GET_PEEP(w->number);

	int x = w->x + window_staff_stats_widgets[WIDX_RESIZE].left + 4;
	int y = w->y + window_staff_stats_widgets[WIDX_RESIZE].top + 4;

	if (!(gParkFlags & PARK_FLAGS_NO_MONEY)) {
		set_format_arg(0, uint32, RCT2_ADDRESS(0x00992A00, uint16)[peep->staff_type]);
		gfx_draw_string_left(dpi, STR_STAFF_STAT_WAGES, gCommonFormatArgs, 0, x, y);
		y += 10;
	}

	gfx_draw_string_left(dpi, STR_STAFF_STAT_EMPLOYED_FOR, (void*)&peep->time_in_park, 0, x, y);
	y += 10;

	switch (peep->staff_type){
	case STAFF_TYPE_HANDYMAN:
		gfx_draw_string_left(dpi, STR_STAFF_STAT_LAWNS_MOWN, (void*)&peep->staff_lawns_mown, 0, x, y);
		y += 10;
		gfx_draw_string_left(dpi, STR_STAFF_STAT_GARDENS_WATERED, (void*)&peep->staff_gardens_watered, 0, x, y);
		y += 10;
		gfx_draw_string_left(dpi, STR_STAFF_STAT_LITTER_SWEPT, (void*)&peep->staff_litter_swept, 0, x, y);
		y += 10;
		gfx_draw_string_left(dpi, STR_STAFF_STAT_BINS_EMPTIED, (void*)&peep->staff_bins_emptied, 0, x, y);
		break;
	case STAFF_TYPE_MECHANIC:
		gfx_draw_string_left(dpi, STR_STAFF_STAT_RIDES_INSPECTED, (void*)&peep->staff_rides_inspected, 0, x, y);
		y += 10;
		gfx_draw_string_left(dpi, STR_STAFF_STAT_RIDES_FIXED, (void*)&peep->staff_rides_fixed, 0, x, y);
		break;
	}
}

/**
 *
 *  rct2: 0x006BDFD8
 */
void window_staff_overview_tool_update(rct_window* w, int widgetIndex, int x, int y)
{
	if (widgetIndex != WIDX_PICKUP)
		return;

	map_invalidate_selection_rect();

	gMapSelectFlags &= ~MAP_SELECT_FLAG_ENABLE;

	int map_x, map_y;
	footpath_get_coordinates_from_pos(x, y + 16, &map_x, &map_y, NULL, NULL);
	if (map_x != (sint16)0x8000) {
		gMapSelectFlags |= MAP_SELECT_FLAG_ENABLE;
		gMapSelectType = MAP_SELECT_TYPE_FULL;
		gMapSelectPositionA.x = map_x;
		gMapSelectPositionB.x = map_x;
		gMapSelectPositionA.y = map_y;
		gMapSelectPositionB.y = map_y;
		map_invalidate_selection_rect();
	}

	gPickupPeepImage = UINT32_MAX;

	int interactionType;
	get_map_coordinates_from_pos(x, y, VIEWPORT_INTERACTION_MASK_NONE, NULL, NULL, &interactionType, NULL, NULL);
	if (interactionType == VIEWPORT_INTERACTION_ITEM_NONE)
		return;

	x--;
	y += 16;
	gPickupPeepX = x;
	gPickupPeepY = y;
	w->picked_peep_frame++;
	if (w->picked_peep_frame >= 48) {
		w->picked_peep_frame = 0;
	}

	rct_peep* peep;
	peep = GET_PEEP(w->number);

	uint32 imageId = g_sprite_entries[peep->sprite_type].sprite_image[11].base_image;
	imageId += w->picked_peep_frame >> 2;

	imageId |= (peep->tshirt_colour << 19) | (peep->trousers_colour << 24) | 0xA0000000;
	gPickupPeepImage = imageId;
}

/**
 *
 *  rct2: 0x006BDFC3
 */
void window_staff_overview_tool_down(rct_window* w, int widgetIndex, int x, int y)
{
	if (widgetIndex == WIDX_PICKUP) {
		int dest_x, dest_y;
		rct_map_element *mapElement;
		footpath_get_coordinates_from_pos(x, y + 16, &dest_x, &dest_y, NULL, &mapElement);

		if (dest_x == (sint16)0x8000)return;

		// Set the coordinate of destination to be exactly
		// in the middle of a tile.
		dest_x += 16;
		dest_y += 16;
		// Set the tile coordinate to top left of tile
		int tile_y = dest_y & 0xFFE0;
		int tile_x = dest_x & 0xFFE0;

		int dest_z = mapElement->base_height * 8 + 16;

		if (!map_is_location_owned(tile_x, tile_y, dest_z)){
			window_error_open(STR_ERR_CANT_PLACE_PERSON_HERE, STR_NONE);
			return;
		}

		if (!map_can_construct_at(tile_x, tile_y, dest_z / 8, (dest_z / 8) + 1, 15)){
			if (gGameCommandErrorText != STR_RAISE_OR_LOWER_LAND_FIRST){
				if (gGameCommandErrorText != STR_FOOTPATH_IN_THE_WAY){
					window_error_open(STR_ERR_CANT_PLACE_PERSON_HERE, STR_NONE);
					return;
				}
			}
		}

		rct_peep* peep = GET_PEEP(w->number);
		sprite_move(dest_x, dest_y, dest_z, (rct_sprite*)peep);
		invalidate_sprite_2((rct_sprite*)peep);
		peep_decrement_num_riders(peep);
		peep->state = PEEP_STATE_FALLING;
		peep_window_state_update(peep);
		peep->action = 0xFF;
		peep->special_sprite = 0;
		peep->action_sprite_image_offset = 0;
		peep->action_sprite_type = 0;
		peep->var_C4 = 0;

		tool_cancel();
		gPickupPeepImage = UINT32_MAX;
	}
	else if (widgetIndex == WIDX_PATROL){
		int dest_x, dest_y;
		footpath_get_coordinates_from_pos(x, y, &dest_x, &dest_y, NULL, NULL);

		if (dest_x == (sint16)0x8000)return;

		game_do_command(dest_x, 1, dest_y, w->number, GAME_COMMAND_SET_STAFF_PATROL, 0, 0);
	}
}

/**
 *
 *  rct2: 0x6BDFAE
 */
void window_staff_overview_tool_abort(rct_window *w, int widgetIndex)
{
	if (widgetIndex == WIDX_PICKUP) {
		rct_peep* peep = GET_PEEP(w->number);
		if (peep->state != PEEP_STATE_PICKED) return;

		sprite_move(w->picked_peep_old_x, peep->y, peep->z + 8, (rct_sprite*)peep);
		invalidate_sprite_2((rct_sprite*)peep);

		if (peep->x != (sint16)0x8000){
			peep_decrement_num_riders(peep);
			peep->state = PEEP_STATE_FALLING;
			peep_window_state_update(peep);
			peep->action = 0xFF;
			peep->special_sprite = 0;
			peep->action_sprite_image_offset = 0;
			peep->action_sprite_type = 0;
			peep->var_C4 = 0;
		}

		gPickupPeepImage = UINT32_MAX;
	}
	else if (widgetIndex == WIDX_PATROL){
		hide_gridlines();
		gStaffDrawPatrolAreas = 0xFFFF;
		gfx_invalidate_screen();
	}
}

/* rct2: 0x6BDFED */
void window_staff_overview_text_input(rct_window *w, int widgetIndex, char *text)
{
	if (widgetIndex != WIDX_RENAME)
		return;

	if (text == NULL)
		return;

	gGameCommandErrorTitle = STR_STAFF_ERROR_CANT_NAME_STAFF_MEMBER;
	game_do_command(1, GAME_COMMAND_FLAG_APPLY, w->number, *((int*)(text + 0)), GAME_COMMAND_SET_STAFF_NAME, *((int*)(text + 8)), *((int*)(text + 4)));
	game_do_command(2, GAME_COMMAND_FLAG_APPLY, w->number, *((int*)(text + 12)), GAME_COMMAND_SET_STAFF_NAME, *((int*)(text + 20)), *((int*)(text + 16)));
	game_do_command(0, GAME_COMMAND_FLAG_APPLY, w->number, *((int*)(text + 24)), GAME_COMMAND_SET_STAFF_NAME, *((int*)(text + 32)), *((int*)(text + 28)));
}

/**
 *
 *  rct2: 0x006BE5FC
 */
void window_staff_overview_unknown_14(rct_window *w)
{
	window_staff_viewport_init(w);
}

/**
 *
 *  rct2: 0x006BEDA3
 */
void window_staff_viewport_init(rct_window* w){
	if (w->page != WINDOW_STAFF_OVERVIEW) return;

	sprite_focus focus = { 0 };

	focus.sprite_id = w->number;

	rct_peep* peep = GET_PEEP(w->number);

	if (peep->state == PEEP_STATE_PICKED){
		focus.sprite_id = -1;
	}
	else{
		focus.type |= VIEWPORT_FOCUS_TYPE_SPRITE | VIEWPORT_FOCUS_TYPE_COORDINATE;
		focus.rotation = get_current_rotation();
	}

	uint16 viewport_flags;

	if (w->viewport){
		//Check all combos, for now skipping y and rot
		if (focus.sprite_id == w->viewport_focus_sprite.sprite_id &&
			focus.type == w->viewport_focus_sprite.type &&
			focus.rotation == w->viewport_focus_sprite.rotation)
			return;

		viewport_flags = w->viewport->flags;
		w->viewport->width = 0;
		w->viewport = 0;

		viewport_update_pointers();
	}
	else{
		viewport_flags = 0;
		if (RCT2_GLOBAL(RCT2_ADDRESS_CONFIG_FLAGS, uint8) & 0x1)
			viewport_flags |= VIEWPORT_FLAG_GRIDLINES;
	}

	window_event_invalidate_call(w);

	w->viewport_focus_sprite.sprite_id = focus.sprite_id;
	w->viewport_focus_sprite.type = focus.type;
	w->viewport_focus_sprite.rotation = focus.rotation;

	if (peep->state != PEEP_STATE_PICKED){
		if (!(w->viewport)){
			rct_widget* view_widget = &w->widgets[WIDX_VIEWPORT];

			int x = view_widget->left + 1 + w->x;
			int y = view_widget->top + 1 + w->y;
			int width = view_widget->right - view_widget->left - 1;
			int height = view_widget->bottom - view_widget->top - 1;

			viewport_create(w, x, y, width, height, 0, 0, 0, 0, focus.type & VIEWPORT_FOCUS_TYPE_MASK, focus.sprite_id);
			w->flags |= WF_NO_SCROLLING;
			window_invalidate(w);
		}
	}

	if (w->viewport)
		w->viewport->flags = viewport_flags;
	window_invalidate(w);
}

/**
* Handle the costume of staff member.
* rct2: 0x006BE802
*/
void window_staff_options_mousedown(int widgetIndex, rct_window* w, rct_widget* widget)
{
	if (widgetIndex != WIDX_COSTUME_BTN) {
		return;
	}

	init_scenery();

	int ebx = 0;
	for (int i = 0; i < 19; i++) {
		if (window_scenery_tab_entries[i][0] != -1) {
			rct_scenery_set_entry* scenery_entry = get_scenery_group_entry(i);
			ebx |= scenery_entry->var_10A;
		}
	}

	uint8* ebp = RCT2_ADDRESS(0xF4391B, uint8);
	uint16 no_entries = 0;
	for (uint8 i = 0; i < 32; ++i){
		if (ebx & (1 << i)){
			*ebp++ = i;
			no_entries++;
		}
	}
	// Save number of entrys. Not required any more.
	RCT2_GLOBAL(0xF43926, uint16) = no_entries;

	rct_peep* peep = GET_PEEP(w->number);
	int item_checked = 0;
	//This will be moved below where Items Checked is when all
	//of dropdown related functions are finished. This prevents
	//the dropdown from not working on first click.
	for (int i = 0; i < no_entries; ++i){
		int eax = RCT2_ADDRESS(0xF4391B, uint8)[i];
		if (eax == peep->sprite_type){
			item_checked = 1 << i;
		}
		gDropdownItemsArgs[i] = staffCostumeNames[eax - 4];
		gDropdownItemsFormat[i] = STR_DROPDOWN_MENU_LABEL;
	}

	//Get the dropdown box widget instead of button.
	widget--;

	int x = widget->left + w->x;
	int y = widget->top + w->y;
	int extray = widget->bottom - widget->top + 1;
	int width = widget->right - widget->left - 3;
	window_dropdown_show_text_custom_width(x, y, extray, w->colours[1], DROPDOWN_FLAG_STAY_OPEN, no_entries, width);

	// See above note.
	gDropdownItemsChecked = item_checked;
}

/**
 *
 *  rct2: 0x6BE809
 */
void window_staff_options_dropdown(rct_window *w, int widgetIndex, int dropdownIndex)
{
	if (widgetIndex != WIDX_COSTUME_BTN) {
		return;
	}

	if (dropdownIndex == -1)
		return;

	rct_peep* peep = GET_PEEP(w->number);
	int costume = (RCT2_ADDRESS(0xF4391B, uint8)[dropdownIndex] - 4) | 0x80;
	game_do_command(peep->x, (costume << 8) | 1, peep->y, w->number, GAME_COMMAND_SET_STAFF_ORDER, (int)peep, 0);
}
