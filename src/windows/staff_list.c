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
#include "../drawing/drawing.h"
#include "../input.h"
#include "../interface/themes.h"
#include "../interface/viewport.h"
#include "../interface/widget.h"
#include "../interface/window.h"
#include "../localisation/localisation.h"
#include "../peep/peep.h"
#include "../peep/staff.h"
#include "../sprites.h"
#include "../world/footpath.h"
#include "../world/sprite.h"
#include "dropdown.h"
#include "error.h"

enum {
	WINDOW_STAFF_LIST_TAB_HANDYMEN,
	WINDOW_STAFF_LIST_TAB_MECHANICS,
	WINDOW_STAFF_LIST_TAB_SECURITY,
	WINDOW_STAFF_LIST_TAB_ENTERTAINERS
} WINDOW_STAFF_LIST_TAB;

bool _quick_fire_mode = false;

static void window_staff_list_close(rct_window *w);
static void window_staff_list_mouseup(rct_window *w, int widgetIndex);
static void window_staff_list_resize(rct_window *w);
static void window_staff_list_mousedown(int widgetIndex, rct_window*w, rct_widget* widget);
static void window_staff_list_dropdown(rct_window *w, int widgetIndex, int dropdownIndex);
static void window_staff_list_update(rct_window *w);
static void window_staff_list_tooldown(rct_window *w, int widgetIndex, int x, int y);
static void window_staff_list_toolabort(rct_window *w, int widgetIndex);
static void window_staff_list_scrollgetsize(rct_window *w, int scrollIndex, int *width, int *height);
static void window_staff_list_scrollmousedown(rct_window *w, int scrollIndex, int x, int y);
static void window_staff_list_scrollmouseover(rct_window *w, int scrollIndex, int x, int y);
static void window_staff_list_tooltip(rct_window* w, int widgetIndex, rct_string_id *stringId);
static void window_staff_list_invalidate(rct_window *w);
static void window_staff_list_paint(rct_window *w, rct_drawpixelinfo *dpi);
static void window_staff_list_scrollpaint(rct_window *w, rct_drawpixelinfo *dpi, int scrollIndex);

static rct_window_event_list window_staff_list_events = {
	window_staff_list_close,
	window_staff_list_mouseup,
	window_staff_list_resize,
	window_staff_list_mousedown,
	window_staff_list_dropdown,
	NULL,
	window_staff_list_update,
	NULL,
	NULL,
	NULL,
	window_staff_list_tooldown,
	NULL,
	NULL,
	window_staff_list_toolabort,
	NULL,
	window_staff_list_scrollgetsize,
	window_staff_list_scrollmousedown,
	NULL,
	window_staff_list_scrollmouseover,
	NULL,
	NULL,
	NULL,
	window_staff_list_tooltip,
	NULL,
	NULL,
	window_staff_list_invalidate,
	window_staff_list_paint,
	window_staff_list_scrollpaint,
};

enum WINDOW_STAFF_LIST_WIDGET_IDX {
	WIDX_STAFF_LIST_BACKGROUND,
	WIDX_STAFF_LIST_TITLE,
	WIDX_STAFF_LIST_CLOSE,
	WIDX_STAFF_LIST_TAB_CONTENT_PANEL,
	WIDX_STAFF_LIST_HANDYMEN_TAB,
	WIDX_STAFF_LIST_MECHANICS_TAB,
	WIDX_STAFF_LIST_SECURITY_TAB,
	WIDX_STAFF_LIST_ENTERTAINERS_TAB,
	WIDX_STAFF_LIST_LIST,
	WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER,
	WIDX_STAFF_LIST_HIRE_BUTTON,
	WIDX_STAFF_LIST_QUICK_FIRE,
	WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON,
	WIDX_STAFF_LIST_MAP,
};

#define WW 320
#define WH 270
#define MAX_WW 500
#define MAX_WH 450

static rct_widget window_staff_list_widgets[] = {
	{ WWT_FRAME,			0,	0,			319,		0,		269,	0xFFFFFFFF,			STR_NONE },							// panel / background
	{ WWT_CAPTION,			0,	1,			318,		1,		14,		STR_STAFF,				STR_WINDOW_TITLE_TIP },				// title bar
	{ WWT_CLOSEBOX,			0,	307,		317,		2,		13,		STR_CLOSE_X,			STR_CLOSE_WINDOW_TIP },				// close button
	{ WWT_RESIZE,			1,	0,			319,		43,		269,	0xFFFFFFFF,			STR_NONE },							// tab content panel
	{ WWT_TAB,				1,	3,			33,			17,		43,		0x20000000 | SPR_TAB,	STR_STAFF_HANDYMEN_TAB_TIP },		// handymen tab
	{ WWT_TAB,				1,	34,			64,			17,		43,		0x20000000 | SPR_TAB,	STR_STAFF_MECHANICS_TAB_TIP },		// mechanics tab
	{ WWT_TAB,				1,	65,			95,			17,		43,		0x20000000 | SPR_TAB,	STR_STAFF_SECURITY_TAB_TIP },		// security guards tab
	{ WWT_TAB,				1,	96,			126,		17,		43,		0x20000000 | SPR_TAB,	STR_STAFF_ENTERTAINERS_TAB_TIP },	// entertainers tab
	{ WWT_SCROLL,			1,	3,			316,		72,		266,	SCROLL_BOTH,			STR_NONE },							// staff list
	{ WWT_COLOURBTN,		1,	130,		141,		58,		69,		STR_NONE,				STR_UNIFORM_COLOUR_TIP },			// uniform colour picker
	{ WWT_DROPDOWN_BUTTON,	0,	WW - 155,	WW - 11,	17,		29,		STR_NONE,				STR_HIRE_STAFF_TIP },				// hire button
	{ WWT_FLATBTN,			1,	WW - 77,	WW - 54,	46,		69,		SPR_DEMOLISH,			STR_QUICK_FIRE_STAFF },				// quick fire staff
	{ WWT_FLATBTN,			1,	WW - 53,	WW - 30,	46,		69,		SPR_PATROL_BTN,			STR_SHOW_PATROL_AREA_TIP },			// show staff patrol area tool
	{ WWT_FLATBTN,			1,	WW - 29,	WW - 6,		46,		69,		SPR_MAP,				STR_SHOW_STAFF_ON_MAP_TIP },		// show staff on map button
	{ WIDGETS_END },
};

static uint16 _window_staff_list_selected_type_count = 0;
static int _windowStaffListHighlightedIndex;
static int _windowStaffListSelectedTab;

typedef struct staff_naming_convention
{
	rct_string_id plural;
	rct_string_id singular;
	rct_string_id action_hire;
} staff_naming_convention;

static const staff_naming_convention StaffNamingConvention[] = {
	{ STR_HANDYMAN_PLURAL,			STR_HANDYMAN_SINGULAR,			STR_HIRE_HANDYMAN },
	{ STR_MECHANIC_PLURAL,			STR_MECHANIC_SINGULAR,			STR_HIRE_MECHANIC },
	{ STR_SECURITY_GUARD_PLURAL,	STR_SECURITY_GUARD_SINGULAR,	STR_HIRE_SECURITY_GUARD },
	{ STR_ENTERTAINER_PLURAL,		STR_ENTERTAINER_SINGULAR,		STR_HIRE_ENTERTAINER },
};

/*
* rct2: 0x006BD39C
**/
void window_staff_list_init_vars()
{
	_windowStaffListSelectedTab = WINDOW_STAFF_LIST_TAB_HANDYMEN;
}

/*
* rct2: 0x006BD3CC
**/
void window_staff_list_open()
{
	rct_window* window;

	// Check if window is already open
	window = window_bring_to_front_by_class(WC_STAFF_LIST);
	if (window != NULL)
		return;

	window = window_create_auto_pos(WW, WH, &window_staff_list_events, WC_STAFF_LIST, WF_10 | WF_RESIZABLE);
	window->widgets = window_staff_list_widgets;
	window->enabled_widgets =
		(1 << WIDX_STAFF_LIST_CLOSE) |
		(1 << WIDX_STAFF_LIST_HANDYMEN_TAB) |
		(1 << WIDX_STAFF_LIST_MECHANICS_TAB) |
		(1 << WIDX_STAFF_LIST_SECURITY_TAB) |
		(1 << WIDX_STAFF_LIST_ENTERTAINERS_TAB) |
		(1 << WIDX_STAFF_LIST_HIRE_BUTTON) |
		(1 << WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER) |
		(1 << WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON) |
		(1 << WIDX_STAFF_LIST_MAP) |
		(1 << WIDX_STAFF_LIST_QUICK_FIRE);

	window_init_scroll_widgets(window);
	_windowStaffListHighlightedIndex = -1;
	window->list_information_type = 0;

	window_staff_list_widgets[WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER].type = WWT_EMPTY;
	window->min_width = WW;
	window->min_height = WH;
	window->max_width = MAX_WW;
	window->max_height = MAX_WH;
	_quick_fire_mode = false;
}

void window_staff_list_cancel_tools(rct_window *w) {
	if (gInputFlags & INPUT_FLAG_TOOL_ACTIVE)
		if (w->classification == gCurrentToolWidget.window_classification && w->number == gCurrentToolWidget.window_number)
			tool_cancel();
}

/*
* rct2: 0x006BD9B1
**/
void window_staff_list_close(rct_window *w)
{
	window_staff_list_cancel_tools(w);
}

/**
*
*  rct2: 0x006BD94C
*/
static void window_staff_list_mouseup(rct_window *w, int widgetIndex)
{
	uint16 newStaffId;

	switch (widgetIndex) {
	case WIDX_STAFF_LIST_CLOSE:
		window_close(w);
		break;
	case WIDX_STAFF_LIST_HIRE_BUTTON:
		newStaffId = hire_new_staff_member(_windowStaffListSelectedTab);

		if (newStaffId == 0xFFFF) {
			rct_window* window = window_find_by_class(WC_STAFF_LIST);
			window_invalidate(window);
		} else {
			window_staff_open(&g_sprite_list[newStaffId].peep);
		}

		break;
	case WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON:
		if (!tool_set(w, WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON, 12)) {
			show_gridlines();
			gStaffDrawPatrolAreas = _windowStaffListSelectedTab | 0x8000;
			gfx_invalidate_screen();
		}
		break;
	case WIDX_STAFF_LIST_MAP:
		window_map_open();
		break;
	case WIDX_STAFF_LIST_QUICK_FIRE:
		_quick_fire_mode ^= 1;
		window_invalidate(w);
		break;
	}
}

/**
*
*  rct2: 0x006BDD5D
*/
static void window_staff_list_resize(rct_window *w)
{
	w->min_width = WW;
	w->min_height = WH;
	if (w->width < w->min_width) {
		w->width = w->min_width;
		window_invalidate(w);
	}
	if (w->height < w->min_height) {
		w->height = w->min_height;
		window_invalidate(w);
	}
}


/**
*
*  rct2: 0x006BD971
*/
static void window_staff_list_mousedown(int widgetIndex, rct_window* w, rct_widget* widget)
{
	short newSelectedTab;

	switch (widgetIndex) {
	case WIDX_STAFF_LIST_HANDYMEN_TAB:
	case WIDX_STAFF_LIST_MECHANICS_TAB:
	case WIDX_STAFF_LIST_SECURITY_TAB:
	case WIDX_STAFF_LIST_ENTERTAINERS_TAB:
		newSelectedTab = widgetIndex - WIDX_STAFF_LIST_HANDYMEN_TAB;;
		if (_windowStaffListSelectedTab == newSelectedTab)
			break;
		_windowStaffListSelectedTab = (uint8)newSelectedTab;
		window_invalidate(w);
		w->scrolls[0].v_top = 0;
		window_staff_list_cancel_tools(w);
		break;
	case WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER:
		window_dropdown_show_colour(w, widget, w->colours[1], gStaffColours[_windowStaffListSelectedTab]);
		break;
	}


}

/**
*
*  rct2: 0x006BD9A6
*/
static void window_staff_list_dropdown(rct_window *w, int widgetIndex, int dropdownIndex)
{
	if (widgetIndex == WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER && dropdownIndex != -1) {
		update_staff_colour(_windowStaffListSelectedTab, dropdownIndex);
	}
}

/**
*
*  rct2: 0x006BDCEA
*/
void window_staff_list_update(rct_window *w)
{
	int spriteIndex;
	rct_peep *peep;

	w->list_information_type++;
	if (w->list_information_type >= 24) {
		w->list_information_type = 0;
	} else {
		widget_invalidate(w, WIDX_STAFF_LIST_HANDYMEN_TAB + _windowStaffListSelectedTab);
		gWindowMapFlashingFlags |= (1 << 2);
		FOR_ALL_STAFF(spriteIndex, peep) {
			peep->flags &= ~(SPRITE_FLAGS_PEEP_FLASHING);

			if (peep->staff_type == _windowStaffListSelectedTab) {
				peep->flags |= SPRITE_FLAGS_PEEP_FLASHING;
			}
		}
	}
}

/**
 *
 *  rct2: 0x006BD990
 */
static void window_staff_list_tooldown(rct_window *w, int widgetIndex, int x, int y)
{
	int direction, distance, closestPeepDistance, selectedPeepType;
	rct_map_element *mapElement;
	rct_peep *peep, *closestPeep;
	uint16 spriteIndex;

	if (widgetIndex == WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON) {
		selectedPeepType = _windowStaffListSelectedTab;

		footpath_get_coordinates_from_pos(x, y, &x, &y, &direction, &mapElement);
		if (x == 0x8000)
			return;

		bool isPatrolAreaSet = staff_is_patrol_area_set(200 + selectedPeepType, x, y);

		closestPeep = NULL;
		closestPeepDistance = INT_MAX;
		FOR_ALL_STAFF(spriteIndex, peep) {
			if (peep->staff_type != selectedPeepType)
				continue;

			if (isPatrolAreaSet) {
				if (!(gStaffModes[peep->staff_id] & 2)) {
					continue;
				}
				if (!staff_is_location_in_patrol(peep, x, y)) {
					continue;
				}
			}

			if (peep->x == (sint16)0x8000) {
				continue;
			}

			distance = abs(x - peep->x) + abs(y - peep->y);
			if (distance < closestPeepDistance) {
				closestPeepDistance = distance;
				closestPeep = peep;
			}
		}

		if (closestPeep != NULL) {
			tool_cancel();
			rct_window *staffWindow = window_staff_open(closestPeep);
			window_event_dropdown_call(staffWindow, 11, 0);
		} else {
			set_format_arg(0, rct_string_id, StaffNamingConvention[selectedPeepType].plural);
			window_error_open(STR_NO_THING_IN_PARK_YET, STR_NONE);
		}
	}
}

/**
*
*  rct2: 0x006BD99B
*/
void window_staff_list_toolabort(rct_window *w, int widgetIndex)
{
	if (widgetIndex == WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON) {
		hide_gridlines();
		tool_cancel();
		gStaffDrawPatrolAreas = 0xFFFF;
		gfx_invalidate_screen();
	}
}

/**
*
*  rct2: 0x006BDBE6
*/
void window_staff_list_scrollgetsize(rct_window *w, int scrollIndex, int *width, int *height)
{
	int i, spriteIndex;
	rct_peep *peep;

	uint16 staffCount = 0;
	FOR_ALL_STAFF(spriteIndex, peep) {
		if (peep->staff_type == _windowStaffListSelectedTab)
			staffCount++;
	}

	_window_staff_list_selected_type_count = staffCount;

	if (_windowStaffListHighlightedIndex != -1) {
		_windowStaffListHighlightedIndex = -1;
		window_invalidate(w);
	}

	*height = staffCount * 10;
	i = *height - window_staff_list_widgets[WIDX_STAFF_LIST_LIST].bottom + window_staff_list_widgets[WIDX_STAFF_LIST_LIST].top + 21;
	if (i < 0)
		i = 0;
	if (i < w->scrolls[0].v_top) {
		w->scrolls[0].v_top = i;
		window_invalidate(w);
	}

	*width = 420;
}

/**
*
*  rct2: 0x006BDC9A
*/
void window_staff_list_scrollmousedown(rct_window *w, int scrollIndex, int x, int y)
{
	int i, spriteIndex;
	rct_peep *peep;

	i = y / 10;
	FOR_ALL_STAFF(spriteIndex, peep) {
		if (peep->staff_type != _windowStaffListSelectedTab)
			continue;

		if (i == 0) {
			if (_quick_fire_mode)
				game_do_command(peep->x, 1, peep->y, spriteIndex, GAME_COMMAND_FIRE_STAFF_MEMBER, 0, 0);
			else
				window_staff_open(peep);
			break;
		}

		i--;
	}
}

/**
*
*  rct2: 0x006BDC6B
*/
void window_staff_list_scrollmouseover(rct_window *w, int scrollIndex, int x, int y)
{
	int i;

	i = y / 10;
	if (i != _windowStaffListHighlightedIndex) {
		_windowStaffListHighlightedIndex = i;
		window_invalidate(w);
	}
}

/**
*
*  rct2: 0x006BDC90
*/
void window_staff_list_tooltip(rct_window* w, int widgetIndex, rct_string_id *stringId)
{
	set_format_arg(0, uint16, STR_LIST);
}

/**
*
*  rct2: 0x006BD477
*/
void window_staff_list_invalidate(rct_window *w)
{
	colour_scheme_update(w);

	int pressed_widgets = w->pressed_widgets & 0xFFFFFF0F;
	uint8 tabIndex = _windowStaffListSelectedTab;
	uint8 widgetIndex = tabIndex + 4;

	w->pressed_widgets = pressed_widgets | (1ULL << widgetIndex);
	window_staff_list_widgets[WIDX_STAFF_LIST_HIRE_BUTTON].text = StaffNamingConvention[tabIndex].action_hire;
	window_staff_list_widgets[WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER].type = WWT_EMPTY;

	if (tabIndex < 3) {
		window_staff_list_widgets[WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER].type = WWT_COLOURBTN;
		window_staff_list_widgets[WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER].image =
			((uint32)gStaffColours[tabIndex] << 19) | 0x60000000 | SPR_PALETTE_BTN;
	}
	if (_quick_fire_mode)
		w->pressed_widgets |= (1ULL << WIDX_STAFF_LIST_QUICK_FIRE);
	else
		w->pressed_widgets &= ~(1ULL << WIDX_STAFF_LIST_QUICK_FIRE);

	window_staff_list_widgets[WIDX_STAFF_LIST_BACKGROUND].right = w->width - 1;
	window_staff_list_widgets[WIDX_STAFF_LIST_BACKGROUND].bottom = w->height - 1;
	window_staff_list_widgets[WIDX_STAFF_LIST_TAB_CONTENT_PANEL].right = w->width - 1;
	window_staff_list_widgets[WIDX_STAFF_LIST_TAB_CONTENT_PANEL].bottom = w->height - 1;
	window_staff_list_widgets[WIDX_STAFF_LIST_TITLE].right = w->width - 2;
	window_staff_list_widgets[WIDX_STAFF_LIST_CLOSE].left = w->width - 2 - 11;
	window_staff_list_widgets[WIDX_STAFF_LIST_CLOSE].right = w->width - 2 - 11 + 10;
	window_staff_list_widgets[WIDX_STAFF_LIST_LIST].right = w->width - 4;
	window_staff_list_widgets[WIDX_STAFF_LIST_LIST].bottom = w->height - 15;
	window_staff_list_widgets[WIDX_STAFF_LIST_QUICK_FIRE].left = w->width - 77;
	window_staff_list_widgets[WIDX_STAFF_LIST_QUICK_FIRE].right = w->width - 54;
	window_staff_list_widgets[WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON].left = w->width - 53;
	window_staff_list_widgets[WIDX_STAFF_LIST_SHOW_PATROL_AREA_BUTTON].right = w->width - 30;
	window_staff_list_widgets[WIDX_STAFF_LIST_MAP].left = w->width - 29;
	window_staff_list_widgets[WIDX_STAFF_LIST_MAP].right = w->width - 6;
	window_staff_list_widgets[WIDX_STAFF_LIST_HIRE_BUTTON].left = w->width - 155;
	window_staff_list_widgets[WIDX_STAFF_LIST_HIRE_BUTTON].right = w->width - 11;
}

/**
*
*  rct2: 0x006BD533
*/
void window_staff_list_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	int i;
	uint8 selectedTab;

	// Widgets
	window_draw_widgets(w, dpi);

	selectedTab = _windowStaffListSelectedTab;

	// Handymen tab image
	i = (selectedTab == 0 ? (w->list_information_type & ~3) : 0);
	i += RCT2_ADDRESS(RCT2_GLOBAL(0x00982710, int), int)[0] + 1;
	i |= 0x20000000;
	i |= gStaffHandymanColour << 19;
	gfx_draw_sprite(
		dpi,
		i,
		(window_staff_list_widgets[WIDX_STAFF_LIST_HANDYMEN_TAB].left + window_staff_list_widgets[WIDX_STAFF_LIST_HANDYMEN_TAB].right) / 2 + w->x,
		window_staff_list_widgets[WIDX_STAFF_LIST_HANDYMEN_TAB].bottom - 6 + w->y, 0
		);

	// Mechanic tab image
	i = (selectedTab == 1 ? (w->list_information_type & ~3) : 0);
	i += RCT2_ADDRESS(RCT2_GLOBAL(0x00982718, int), int)[0] + 1;
	i |= 0x20000000;
	i |= gStaffMechanicColour << 19;
	gfx_draw_sprite(
		dpi,
		i,
		(window_staff_list_widgets[WIDX_STAFF_LIST_MECHANICS_TAB].left + window_staff_list_widgets[WIDX_STAFF_LIST_MECHANICS_TAB].right) / 2 + w->x,
		window_staff_list_widgets[WIDX_STAFF_LIST_MECHANICS_TAB].bottom - 6 + w->y, 0
		);

	// Security tab image
	i = (selectedTab == 2 ? (w->list_information_type & ~3) : 0);
	i += RCT2_ADDRESS(RCT2_GLOBAL(0x00982720, int), int)[0] + 1;
	i |= 0x20000000;
	i |= gStaffSecurityColour << 19;
	gfx_draw_sprite(
		dpi,
		i,
		(window_staff_list_widgets[WIDX_STAFF_LIST_SECURITY_TAB].left + window_staff_list_widgets[WIDX_STAFF_LIST_SECURITY_TAB].right) / 2 + w->x,
		window_staff_list_widgets[WIDX_STAFF_LIST_SECURITY_TAB].bottom - 6 + w->y, 0
	);

	rct_drawpixelinfo sprite_dpi;
	if (clip_drawpixelinfo(
		&sprite_dpi,
		dpi,
		window_staff_list_widgets[WIDX_STAFF_LIST_ENTERTAINERS_TAB].left + w->x + 1,
		window_staff_list_widgets[WIDX_STAFF_LIST_ENTERTAINERS_TAB].top + w->y + 1,
		window_staff_list_widgets[WIDX_STAFF_LIST_ENTERTAINERS_TAB].right - window_staff_list_widgets[WIDX_STAFF_LIST_ENTERTAINERS_TAB].left - 1,
		window_staff_list_widgets[WIDX_STAFF_LIST_ENTERTAINERS_TAB].bottom - window_staff_list_widgets[WIDX_STAFF_LIST_ENTERTAINERS_TAB].top - 1
	)) {
		// Entertainers tab image
		i = (selectedTab == 3 ? (w->list_information_type & ~3) : 0);
		i += RCT2_ADDRESS(RCT2_GLOBAL(0x00982738, int), int)[0] + 1;
		gfx_draw_sprite(&sprite_dpi, i, 0x0F, 0x17, 0);
	}

	if (!(gParkFlags & PARK_FLAGS_NO_MONEY)) {
		set_format_arg(0, uint32, RCT2_ADDRESS(0x00992A00, uint16)[selectedTab]);
		gfx_draw_string_left(dpi, STR_COST_PER_MONTH, gCommonFormatArgs, 0, w->x + w->width - 155, w->y + 0x20);
	}

	if (selectedTab < 3) {
		gfx_draw_string_left(dpi, STR_UNIFORM_COLOUR, w, 0, w->x + 6, window_staff_list_widgets[WIDX_STAFF_LIST_UNIFORM_COLOUR_PICKER].top + w->y + 1);
	}

	int staffTypeStringId = StaffNamingConvention[selectedTab].plural;
	// If the number of staff for a given type is 1, we use the singular forms of the names
	if (_window_staff_list_selected_type_count == 1) {
		staffTypeStringId = StaffNamingConvention[selectedTab].singular;
	}

	set_format_arg(0, uint16, _window_staff_list_selected_type_count);
	set_format_arg(2, uint16, staffTypeStringId);

	gfx_draw_string_left(dpi, STR_STAFF_LIST_COUNTER, gCommonFormatArgs, 0, w->x + 4, window_staff_list_widgets[WIDX_STAFF_LIST_LIST].bottom + w->y + 2);
}

/**
*
*  rct2: 0x006BD785
*/
void window_staff_list_scrollpaint(rct_window *w, rct_drawpixelinfo *dpi, int scrollIndex)
{
	int spriteIndex, y, i, staffOrderIcon_x, staffOrders, staffOrderSprite;
	uint32 argument_1, argument_2;
	uint8 selectedTab;
	rct_peep *peep;

	gfx_fill_rect(dpi, dpi->x, dpi->y, dpi->x + dpi->width - 1, dpi->y + dpi->height - 1, ColourMapA[w->colours[1]].mid_light);

	y = 0;
	i = 0;
	selectedTab = _windowStaffListSelectedTab;
	FOR_ALL_STAFF(spriteIndex, peep) {
		if (peep->staff_type == selectedTab) {
			if (y > dpi->y + dpi->height) {
				break;
			}

			if (y + 11 >= dpi->y) {
				int format = (_quick_fire_mode ? STR_RED_STRINGID : STR_BLACK_STRING);

				if (i == _windowStaffListHighlightedIndex) {
					gfx_fill_rect(dpi, 0, y, 800, y + 9, 0x2000031);
					format = (_quick_fire_mode ? STR_LIGHTPINK_STRINGID : STR_WINDOW_COLOUR_2_STRINGID);
				}

				set_format_arg(0, uint16, peep->name_string_idx);
				set_format_arg(2, uint32, peep->id);
				gfx_draw_string_left_clipped(dpi, format, gCommonFormatArgs, 0, 0, y - 1, 107);

				get_arguments_from_action(peep, &argument_1, &argument_2);
				set_format_arg(0, uint32, argument_1);
				set_format_arg(4, uint32, argument_2);
				gfx_draw_string_left_clipped(dpi, format, gCommonFormatArgs, 0, 175, y - 1, 305);

				// True if a patrol path is set for the worker
				if (RCT2_ADDRESS(RCT2_ADDRESS_STAFF_MODE_ARRAY, uint8)[peep->staff_id] & 2) {
					gfx_draw_sprite(dpi, 0x13FD, 110, y - 1, 0);
				}

				staffOrderIcon_x = 0x7D;
				if (peep->staff_type != 3) {
					staffOrders = peep->staff_orders;
					staffOrderSprite = RCT2_ADDRESS(0x00992A08, uint32)[selectedTab];

					while (staffOrders != 0) {
						if (staffOrders & 1) {
							gfx_draw_sprite(dpi, staffOrderSprite, staffOrderIcon_x, y - 1, 0);
						}
						staffOrders = staffOrders >> 1;
						staffOrderIcon_x += 9;
						staffOrderSprite++;
					}
				} else {
					gfx_draw_sprite(dpi, peep->sprite_type - 4 + 0x13FE, staffOrderIcon_x, y - 1, 0);
				}
			}

			y += 10;
			i++;
		}
	}
}
