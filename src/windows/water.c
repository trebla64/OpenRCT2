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

#include "../input.h"
#include "../interface/widget.h"
#include "../interface/window.h"
#include "../localisation/localisation.h"
#include "../rct2.h"
#include "../sprites.h"
#include "../world/map.h"
#include "../interface/themes.h"

#define MINIMUM_TOOL_SIZE 1
#define MAXIMUM_TOOL_SIZE 64

enum WINDOW_WATER_WIDGET_IDX {
	WIDX_BACKGROUND,
	WIDX_TITLE,
	WIDX_CLOSE,
	WIDX_PREVIEW,
	WIDX_DECREMENT,
	WIDX_INCREMENT
};

static rct_widget window_water_widgets[] = {
	{ WWT_FRAME,	0,	0,	75,	0,	76,	0xFFFFFFFF,								STR_NONE },							// panel / background
	{ WWT_CAPTION,	0,	1,	74,	1,	14,	STR_WATER,								STR_WINDOW_TITLE_TIP },				// title bar
	{ WWT_CLOSEBOX,	0,	63,	73,	2,	13,	STR_CLOSE_X,							STR_CLOSE_WINDOW_TIP },				// close x button
	{ WWT_IMGBTN,	0,	16,	59,	17,	48,	SPR_LAND_TOOL_SIZE_0,					STR_NONE },							// preview box
	{ WWT_TRNBTN,	2,	17,	32,	18,	33,	0x20000000 | SPR_LAND_TOOL_DECREASE,	STR_ADJUST_SMALLER_WATER_TIP },		// decrement size
	{ WWT_TRNBTN,	2,	43,	58,	32,	47,	0x20000000 | SPR_LAND_TOOL_INCREASE,	STR_ADJUST_LARGER_WATER_TIP },		// increment size
	{ WIDGETS_END },
};

static int window_water_should_close();

static void window_water_close(rct_window *w);
static void window_water_mouseup(rct_window *w, int widgetIndex);
static void window_water_update(rct_window *w);
static void window_water_invalidate(rct_window *w);
static void window_water_paint(rct_window *w, rct_drawpixelinfo *dpi);
static void window_water_textinput(rct_window *w, int widgetIndex, char *text);
static void window_water_inputsize(rct_window *w);

static rct_window_event_list window_water_events = {
	window_water_close,
	window_water_mouseup,
	NULL,
	NULL,
	NULL,
	NULL,
	window_water_update,
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
	window_water_textinput,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	window_water_invalidate,
	window_water_paint,
	NULL
};

/**
 *
 *  rct2: 0x006E6A40
 */
void window_water_open()
{
	rct_window* window;

	// Check if window is already open
	if (window_find_by_class(WC_WATER) != NULL)
		return;

	window = window_create(
		gScreenWidth - 76,
		29,
		76,
		77,
		&window_water_events,
		WC_WATER,
		0
	);
	window->widgets = window_water_widgets;
	window->enabled_widgets = (1 << WIDX_CLOSE) | (1 << WIDX_DECREMENT) | (1 << WIDX_INCREMENT) | (1 << WIDX_PREVIEW);
	window_init_scroll_widgets(window);
	window_push_others_below(window);

	gWaterToolRaiseCost = MONEY32_UNDEFINED;
	gWaterToolLowerCost = MONEY32_UNDEFINED;
}

/**
 *
 *  rct2: 0x006E6B65
 */
static void window_water_close(rct_window *w)
{
	// If the tool wasn't changed, turn tool off
	if (!window_water_should_close())
		tool_cancel();
}

/**
 *
 *  rct2: 0x006E6B4E
 */
static void window_water_mouseup(rct_window *w, int widgetIndex)
{
	switch (widgetIndex) {
	case WIDX_CLOSE:
		window_close(w);
		break;
	case WIDX_DECREMENT:
		// Decrement land tool size
		gLandToolSize = max(MINIMUM_TOOL_SIZE, gLandToolSize-1);

		// Invalidate the window
		window_invalidate(w);
		break;
	case WIDX_INCREMENT:
		// Increment land tool size
		gLandToolSize = min(MAXIMUM_TOOL_SIZE, gLandToolSize+1);

		// Invalidate the window
		window_invalidate(w);
		break;
	case WIDX_PREVIEW:
		window_water_inputsize(w);
		break;
	}
}

static void window_water_textinput(rct_window *w, int widgetIndex, char *text)
{
	int size;
	char* end;

	if (widgetIndex != WIDX_PREVIEW || text == NULL)
		return;

	size = strtol(text, &end, 10);
	if (*end == '\0') {
		size = max(MINIMUM_TOOL_SIZE,size);
		size = min(MAXIMUM_TOOL_SIZE,size);
		gLandToolSize = size;

		window_invalidate(w);
	}
}

static void window_water_inputsize(rct_window *w)
{
	TextInputDescriptionArgs[0] = MINIMUM_TOOL_SIZE;
	TextInputDescriptionArgs[1] = MAXIMUM_TOOL_SIZE;
	window_text_input_open(w, WIDX_PREVIEW, STR_SELECTION_SIZE, STR_ENTER_SELECTION_SIZE, STR_NONE, STR_NONE, 3);
}

/**
 *
 *  rct2: 0x006E6BCE
 */
static void window_water_update(rct_window *w)
{
	// Close window if another tool is open
	if (window_water_should_close())
		window_close(w);
}

/**
 *
 *  rct2: 0x006E6AB8
 */
static void window_water_invalidate(rct_window *w)
{
	colour_scheme_update(w);

	// Set the preview image button to be pressed down
	w->pressed_widgets |= (1 << WIDX_PREVIEW);

	// Update the preview image
	//window_water_widgets[WIDX_PREVIEW].image = SPR_LAND_TOOL_SIZE_0 + gLandToolSize;

	window_water_widgets[WIDX_PREVIEW].image = gLandToolSize <= 7 ?
		SPR_LAND_TOOL_SIZE_0 + gLandToolSize :
		0xFFFFFFFF;

}

/**
 *
 *  rct2: 0x006E6ACF
 */
static void window_water_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	int x, y;

	x = w->x + (window_water_widgets[WIDX_PREVIEW].left + window_water_widgets[WIDX_PREVIEW].right) / 2;
	y = w->y + (window_water_widgets[WIDX_PREVIEW].top + window_water_widgets[WIDX_PREVIEW].bottom) / 2;

	window_draw_widgets(w, dpi);
	// Draw number for tool sizes bigger than 7
	if (gLandToolSize > 7) {
		gfx_draw_string_centred(dpi, STR_LAND_TOOL_SIZE_VALUE, x, y - 2, COLOUR_BLACK, &gLandToolSize);
	}

	// Draw raise cost amount
	x = (window_water_widgets[WIDX_PREVIEW].left + window_water_widgets[WIDX_PREVIEW].right) / 2 + w->x;
	y = window_water_widgets[WIDX_PREVIEW].bottom + w->y + 5;
	if (gWaterToolRaiseCost != MONEY32_UNDEFINED && gWaterToolRaiseCost != 0)
		gfx_draw_string_centred(dpi, STR_RAISE_COST_AMOUNT, x, y, COLOUR_BLACK, &gWaterToolRaiseCost);
	y += 10;

	// Draw lower cost amount
	if (gWaterToolLowerCost != MONEY32_UNDEFINED && gWaterToolLowerCost != 0)
		gfx_draw_string_centred(dpi, STR_LOWER_COST_AMOUNT, x, y, COLOUR_BLACK, &gWaterToolLowerCost);


}

/**
 *
 *  rct2: 0x0066D125
 */
static int window_water_should_close()
{
	if (!(gInputFlags & INPUT_FLAG_TOOL_ACTIVE))
		return 1;
	if (gCurrentToolWidget.window_classification != WC_TOP_TOOLBAR)
		return 1;
	if (gCurrentToolWidget.widget_index != 8)
		return 1;
	return 0;
}
