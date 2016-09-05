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
#include "../sprites.h"
#include "../world/map.h"
#include "dropdown.h"
#include "../interface/themes.h"

#define MINIMUM_TOOL_SIZE 1
#define MAXIMUM_TOOL_SIZE 64

enum WINDOW_LAND_WIDGET_IDX {
	WIDX_BACKGROUND,
	WIDX_TITLE,
	WIDX_CLOSE,
	WIDX_MOUNTAINMODE,
	WIDX_PAINTMODE,
	WIDX_PREVIEW,
	WIDX_DECREMENT,
	WIDX_INCREMENT,
	WIDX_FLOOR,
	WIDX_WALL,
};

static rct_widget window_land_widgets[] = {
	{ WWT_FRAME,	0,	0,	97,	0,	159,		0xFFFFFFFF,								STR_NONE },						// panel / background
	{ WWT_CAPTION,	0,	1,	96,	1,	14,			STR_LAND,								STR_WINDOW_TITLE_TIP },			// title bar
	{ WWT_CLOSEBOX,	0,	85,	95,	2,	13,			STR_CLOSE_X,							STR_CLOSE_WINDOW_TIP },			// close x button

	{ WWT_FLATBTN,  1,	19,	42,	19,	42,			SPR_RIDE_CONSTRUCTION_SLOPE_UP,			STR_ENABLE_MOUNTAIN_TOOL_TIP },	// mountain mode
	{ WWT_FLATBTN,  1,	55,	78,	19,	42,			SPR_PAINTBRUSH,							STR_DISABLE_ELEVATION },		// paint mode

	{ WWT_IMGBTN,	0,	27,	70,	48,	79,			SPR_LAND_TOOL_SIZE_0,					STR_NONE },						// preview box
	{ WWT_TRNBTN,	1,	28,	43,	49,	64,			0x20000000 | SPR_LAND_TOOL_DECREASE,	STR_ADJUST_SMALLER_LAND_TIP },	// decrement size
	{ WWT_TRNBTN,	1,	54,	69,	63,	78,			0x20000000 | SPR_LAND_TOOL_INCREASE,	STR_ADJUST_LARGER_LAND_TIP },	// increment size

	{ WWT_FLATBTN,	1,	2,	48,	106,	141,	0xFFFFFFFF,								STR_CHANGE_BASE_LAND_TIP },		// floor texture
	{ WWT_FLATBTN,	1,	49,	95,	106,	141,	0xFFFFFFFF,								STR_CHANGE_VERTICAL_LAND_TIP },	// wall texture
	{ WIDGETS_END },
};

static void window_land_close(rct_window *w);
static void window_land_mouseup(rct_window *w, int widgetIndex);
static void window_land_mousedown(int widgetIndex, rct_window*w, rct_widget* widget);
static void window_land_dropdown(rct_window *w, int widgetIndex, int dropdownIndex);
static void window_land_update(rct_window *w);
static void window_land_invalidate(rct_window *w);
static void window_land_paint(rct_window *w, rct_drawpixelinfo *dpi);
static void window_land_textinput(rct_window *w, int widgetIndex, char *text);
static void window_land_inputsize(rct_window *w);

static rct_window_event_list window_land_events = {
	window_land_close,
	window_land_mouseup,
	NULL,
	window_land_mousedown,
	window_land_dropdown,
	NULL,
	window_land_update,
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
	window_land_textinput,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	window_land_invalidate,
	window_land_paint,
	NULL
};

static char window_land_floor_texture_order[] = {
	TERRAIN_SAND_DARK, TERRAIN_SAND_LIGHT,  TERRAIN_DIRT,      TERRAIN_GRASS_CLUMPS, TERRAIN_GRASS,
	TERRAIN_ROCK,      TERRAIN_SAND,        TERRAIN_MARTIAN,   TERRAIN_CHECKERBOARD, TERRAIN_ICE,
	TERRAIN_GRID_RED,  TERRAIN_GRID_YELLOW, TERRAIN_GRID_BLUE, TERRAIN_GRID_GREEN
};

static char window_land_wall_texture_order[] = {
	TERRAIN_EDGE_ROCK,       TERRAIN_EDGE_WOOD_RED,
	TERRAIN_EDGE_WOOD_BLACK, TERRAIN_EDGE_ICE,
	0, 0
};

int _selectedFloorTexture;
int _selectedWallTexture;

/**
 *
 *  rct2: 0x00663E7D
 */
void window_land_open()
{
	rct_window* window;

	// Check if window is already open
	if (window_find_by_class(WC_LAND) != NULL)
		return;

	window = window_create(gScreenWidth - 98, 29, 98, 160, &window_land_events, WC_LAND, 0);
	window->widgets = window_land_widgets;
	window->enabled_widgets =
		(1 << WIDX_CLOSE) |
		(1 << WIDX_DECREMENT) |
		(1 << WIDX_INCREMENT) |
		(1 << WIDX_FLOOR) |
		(1 << WIDX_WALL) |
		(1 << WIDX_MOUNTAINMODE) |
		(1 << WIDX_PAINTMODE) |
		(1 << WIDX_PREVIEW);
	window_init_scroll_widgets(window);
	window_push_others_below(window);

	gLandToolTerrainSurface = 255;
	gLandToolTerrainEdge = 255;
	gLandMountainMode = false;
	gLandPaintMode = false;
	_selectedFloorTexture = 0;
	_selectedWallTexture = 0;
	gLandToolRaiseCost = MONEY32_UNDEFINED;
	gLandToolLowerCost = MONEY32_UNDEFINED;
}

/**
 *
 *  rct2: 0x006640A5
 */
static void window_land_close(rct_window *w)
{
	// If the tool wasn't changed, turn tool off
	if (land_tool_is_active())
		tool_cancel();
}

/**
 *
 *  rct2: 0x00664064
 */
static void window_land_mouseup(rct_window *w, int widgetIndex)
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
	case WIDX_MOUNTAINMODE:
		gLandMountainMode ^= 1;
		gLandPaintMode = 0;
		window_invalidate(w);
		break;
	case WIDX_PAINTMODE:
		gLandMountainMode = 0;
		gLandPaintMode ^= 1;
		window_invalidate(w);
		break;
	case WIDX_PREVIEW:
		window_land_inputsize(w);
		break;
	}
}

/**
 *
 *  rct2: 0x0066407B
 */
static void window_land_mousedown(int widgetIndex, rct_window*w, rct_widget* widget)
{
	int i;
	int defaultIndex = -1;
	switch (widgetIndex) {
	case WIDX_FLOOR:
		for (i = 0; i < 14; i++) {
			gDropdownItemsFormat[i] = -1;
			gDropdownItemsArgs[i] = SPR_FLOOR_TEXTURE_GRASS + window_land_floor_texture_order[i];
			if (window_land_floor_texture_order[i] == _selectedFloorTexture)
				defaultIndex = i;
		}
		window_dropdown_show_image(
			w->x + widget->left, w->y + widget->top,
			widget->bottom - widget->top,
			w->colours[2],
			0,
			14,
			47, 36,
			gAppropriateImageDropdownItemsPerRow[14]
		);
		gDropdownDefaultIndex = defaultIndex;
		break;
	case WIDX_WALL:
		for (i = 0; i < 4; i++) {
			gDropdownItemsFormat[i] = -1;
			gDropdownItemsArgs[i] = SPR_WALL_TEXTURE_ROCK + window_land_wall_texture_order[i];
			if (window_land_wall_texture_order[i] == _selectedWallTexture)
				defaultIndex = i;
		}
		window_dropdown_show_image(
			w->x + widget->left, w->y + widget->top,
			widget->bottom - widget->top,
			w->colours[2],
			0,
			4,
			47, 36,
			gAppropriateImageDropdownItemsPerRow[4]
		);
		gDropdownDefaultIndex = defaultIndex;
		break;
	case WIDX_PREVIEW:
		window_land_inputsize(w);
		break;
	}
}

/**
 *
 *  rct2: 0x00664090
 */
static void window_land_dropdown(rct_window *w, int widgetIndex, int dropdownIndex)
{
	int type;

	switch (widgetIndex) {
	case WIDX_FLOOR:
		if (dropdownIndex == -1)
			dropdownIndex = gDropdownHighlightedIndex;

		type = (dropdownIndex == -1) ?
			_selectedFloorTexture :
			(uint32)gDropdownItemsArgs[dropdownIndex] - SPR_FLOOR_TEXTURE_GRASS;

		if (gLandToolTerrainSurface == type) {
			gLandToolTerrainSurface = 255;
		} else {
			gLandToolTerrainSurface = type;
			_selectedFloorTexture = type;
		}
		window_invalidate(w);
		break;
	case WIDX_WALL:
		if (dropdownIndex == -1)
			dropdownIndex = gDropdownHighlightedIndex;

		type = (dropdownIndex == -1) ?
			_selectedWallTexture :
			(uint32)gDropdownItemsArgs[dropdownIndex] - SPR_WALL_TEXTURE_ROCK;

		if (gLandToolTerrainEdge == type) {
			gLandToolTerrainEdge = 255;
		} else {
			gLandToolTerrainEdge = type;
			_selectedWallTexture = type;
		}
		window_invalidate(w);
		break;
	}
}

static void window_land_textinput(rct_window *w, int widgetIndex, char *text)
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

static void window_land_inputsize(rct_window *w)
{
	TextInputDescriptionArgs[0] = MINIMUM_TOOL_SIZE;
	TextInputDescriptionArgs[1] = MAXIMUM_TOOL_SIZE;
	window_text_input_open(w, WIDX_PREVIEW, STR_SELECTION_SIZE, STR_ENTER_SELECTION_SIZE, STR_NONE, STR_NONE, 3);
}

/**
 *
 *  rct2: 0x00664272
 */
static void window_land_update(rct_window *w)
{
	if (!land_tool_is_active())
		window_close(w);
}

/**
 *
 *  rct2: 0x00663F20
 */
static void window_land_invalidate(rct_window *w)
{
	colour_scheme_update(w);

	w->pressed_widgets = (1 << WIDX_PREVIEW);
	if (gLandToolTerrainSurface != 255)
		w->pressed_widgets |= (1 << WIDX_FLOOR);
	if (gLandToolTerrainEdge != 255)
		w->pressed_widgets |= (1 << WIDX_WALL);
	if (gLandMountainMode)
		w->pressed_widgets |= (1 << WIDX_MOUNTAINMODE);
	if (gLandPaintMode)
		w->pressed_widgets |= (1 << WIDX_PAINTMODE);

	window_land_widgets[WIDX_FLOOR].image = SPR_FLOOR_TEXTURE_GRASS + _selectedFloorTexture;
	window_land_widgets[WIDX_WALL].image = SPR_WALL_TEXTURE_ROCK + _selectedWallTexture;
	// Update the preview image (for tool sizes up to 7)
	window_land_widgets[WIDX_PREVIEW].image = gLandToolSize <= 7 ?
		SPR_LAND_TOOL_SIZE_0 + gLandToolSize :
		0xFFFFFFFF;
}

/**
 *
 *  rct2: 0x00663F7C
 */
static void window_land_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	int x, y, numTiles;
	money32 price;
	rct_widget *previewWidget = &window_land_widgets[WIDX_PREVIEW];

	window_draw_widgets(w, dpi);

	// Draw number for tool sizes bigger than 7
	if (gLandToolSize > 7) {
		x = w->x + (previewWidget->left + previewWidget->right) / 2;
		y = w->y + (previewWidget->top + previewWidget->bottom) / 2;
		gfx_draw_string_centred(dpi, STR_LAND_TOOL_SIZE_VALUE, x, y - 2, 0, &gLandToolSize);
	} else if (gLandMountainMode) {
		x = w->x + previewWidget->left;
		y = w->y + previewWidget->top;
		gfx_draw_sprite(dpi, SPR_LAND_TOOL_SIZE_0, x, y, 0);
	}

	x = w->x + (previewWidget->left + previewWidget->right) / 2;
	y = w->y + previewWidget->bottom + 5;

	// Draw raise cost amount
	if (gLandToolRaiseCost != MONEY32_UNDEFINED && gLandToolRaiseCost != 0)
		gfx_draw_string_centred(dpi, STR_RAISE_COST_AMOUNT, x, y, 0, &gLandToolRaiseCost);
	y += 10;

	// Draw lower cost amount
	if (gLandToolLowerCost != MONEY32_UNDEFINED && gLandToolLowerCost != 0)
		gfx_draw_string_centred(dpi, STR_LOWER_COST_AMOUNT, x, y, 0, &gLandToolLowerCost);
	y += 50;

	// Draw paint price
	numTiles = gLandToolSize * gLandToolSize;
	price = 0;
	if (gLandToolTerrainSurface != 255)
		price += numTiles * TerrainPricing[gLandToolTerrainSurface];
	if (gLandToolTerrainEdge != 255)
		price += numTiles * 100;

	if (price != 0 && !(gParkFlags & PARK_FLAGS_NO_MONEY)) {
		set_format_arg(0, money32, price);
		gfx_draw_string_centred(dpi, STR_COST_AMOUNT, x, y, 0, gCommonFormatArgs);
	}
}
