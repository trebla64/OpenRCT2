/*****************************************************************************
 * Copyright (c) 2014 Ted John
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

#include <SDL_keycode.h>
#include "addresses.h"
#include "audio/audio.h"
#include "config.h"
#include "cursors.h"
#include "game.h"
#include "input.h"
#include "interface/chat.h"
#include "interface/console.h"
#include "interface/keyboard_shortcut.h"
#include "interface/viewport.h"
#include "interface/widget.h"
#include "interface/window.h"
#include "localisation/localisation.h"
#include "platform/platform.h"
#include "ride/ride_data.h"
#include "scenario.h"
#include "windows/tooltip.h"
#include "windows/dropdown.h"
#include "world/banner.h"
#include "world/map.h"
#include "world/sprite.h"
#include "world/scenery.h"
#include "openrct2.h"

enum {
	MOUSE_STATE_RELEASED,
	MOUSE_STATE_LEFT_PRESS,
	MOUSE_STATE_LEFT_RELEASE,
	MOUSE_STATE_RIGHT_PRESS,
	MOUSE_STATE_RIGHT_RELEASE
};

typedef struct {
	uint32 x;
	uint32 y;
	uint32 state;
} rct_mouse_data;

static rct_mouse_data _mouseInputQueue[64];
static uint8 _mouseInputQueueReadIndex = 0;
static uint8 _mouseInputQueueWriteIndex = 0;

static uint32 _ticksSinceDragStart;
static widget_ref _dragWidget;
static uint8 _dragScrollIndex;
static sint32 _originalWindowWidth;
static sint32 _originalWindowHeight;

static uint8 _currentScrollIndex;
static uint8 _currentScrollArea;

uint8 gInputState;
uint8 gInputFlags;
uint8 gInputPlaceObjectModifier;

sint32 gInputDragLastX;
sint32 gInputDragLastY;

widget_ref gHoverWidget;
widget_ref gPressedWidget;

uint16 gTooltipNotShownTicks;
uint16 gTooltipTimeout;
widget_ref gTooltipWidget;
sint32 gTooltipCursorX;
sint32 gTooltipCursorY;

static void game_get_next_input(int *x, int *y, int *state);
static void input_widget_over(int x, int y, rct_window *w, int widgetIndex);
static void input_widget_over_change_check(rct_windowclass windowClass, rct_windownumber windowNumber, int widgetIndex);
static void input_widget_over_flatbutton_invalidate();
void process_mouse_over(int x, int y);
void process_mouse_tool(int x, int y);
void invalidate_scroll();
static rct_mouse_data* get_mouse_input();
void map_element_right_click(int type, rct_map_element *mapElement, int x, int y);
int sub_6EDE88(int x, int y, rct_map_element **mapElement, int *outX, int *outY);
int get_next_key();
static void game_handle_input_mouse(int x, int y, int state);
void game_handle_edge_scroll();
void game_handle_key_scroll();
static void input_widget_left(int x, int y, rct_window *w, int widgetIndex);
void input_state_widget_pressed(int x, int y, int state, int widgetIndex, rct_window* w, rct_widget* widget);
void sub_6ED990(char cursor_id);
static void input_window_position_continue(rct_window *w, int lastX, int lastY, int newX, int newY);
static void input_window_position_end(rct_window *w, int x, int y);
static void input_window_resize_begin(rct_window *w, int widgetIndex, int x, int y);
static void input_window_resize_continue(rct_window *w, int x, int y);
static void input_window_resize_end();
static void input_viewport_drag_begin(rct_window *w, int x, int y);
static void input_viewport_drag_continue();
static void input_viewport_drag_end();
static void input_scroll_begin();
static void input_scroll_continue(rct_window *w, int widgetIndex, int state, int x, int y);
static void input_scroll_end();
static void input_scroll_part_update_hthumb(rct_window *w, int widgetIndex, int x, int scroll_id);
static void input_scroll_part_update_hleft(rct_window *w, int widgetIndex, int scroll_id);
static void input_scroll_part_update_hright(rct_window *w, int widgetIndex, int scroll_id);
static void input_scroll_part_update_vthumb(rct_window *w, int widgetIndex, int y, int scroll_id);
static void input_scroll_part_update_vtop(rct_window *w, int widgetIndex, int scroll_id);
static void input_scroll_part_update_vbottom(rct_window *w, int widgetIndex, int scroll_id);
static void input_update_tooltip(rct_window *w, int widgetIndex, int x, int y);

#pragma region Mouse input

/**
 *
 *  rct2: 0x006EA627
 */
void game_handle_input()
{
	rct_window *w;
	int x, y, state;

	if (RCT2_GLOBAL(0x009DEA64, uint16) & 2) {
		RCT2_GLOBAL(0x009DEA64, uint16) &= ~2;
		game_do_command(0, 1, 0, 0, GAME_COMMAND_LOAD_OR_QUIT, 2, 0);
	}

	if (RCT2_GLOBAL(0x009ABDF2, uint8) != 0) {
		for (w = g_window_list; w < RCT2_GLOBAL(RCT2_ADDRESS_NEW_WINDOW_PTR, rct_window*); w++)
			window_event_unknown_07_call(w);

		sub_6EA73F();

		for (;;) {
			game_get_next_input(&x, &y, &state);
			if (state == 0) {
				break;
			}

			game_handle_input_mouse(x, y, state & 0xFF);
		}

		if (gInputFlags & INPUT_FLAG_5) {
			game_handle_input_mouse(x, y, state);
		}
		else if (x != 0x80000000) {
			x = clamp(0, x, RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_WIDTH, uint16) - 1);
			y = clamp(0, y, RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_HEIGHT, uint16) - 1);

			game_handle_input_mouse(x, y, state);
			process_mouse_over(x, y);
			process_mouse_tool(x, y);
		}
	}

	for (w = g_window_list; w < RCT2_GLOBAL(RCT2_ADDRESS_NEW_WINDOW_PTR, rct_window*); w++)
		window_event_unknown_08_call(w);
}

/**
 *
 *  rct2: 0x006E83C7
*/
static void game_get_next_input(int *x, int *y, int *state)
{
	rct_mouse_data *input = get_mouse_input();
	if (input == NULL) {
		*x = gCursorState.x;
		*y = gCursorState.y;
		*state = 0;
	} else {
		*x = input->x;
		*y = input->y;
		*state = input->state;
	}
}

/**
 *
 *  rct2: 0x00407074
 */
static rct_mouse_data *get_mouse_input()
{
	// Check if that location has been written to yet
	if (_mouseInputQueueReadIndex == _mouseInputQueueWriteIndex) {
		return NULL;
	} else {
		rct_mouse_data *result = &_mouseInputQueue[_mouseInputQueueReadIndex];
		_mouseInputQueueReadIndex = (_mouseInputQueueReadIndex + 1) % countof(_mouseInputQueue);
		return result;
	}
}

/**
 *
 *  rct2: 0x006E957F
 */
static void input_scroll_drag_begin(int x, int y, rct_window* w, rct_widget* widget, int widgetIndex)
{
	gInputState = INPUT_STATE_SCROLL_RIGHT;
	gInputDragLastX = x;
	gInputDragLastY = y;
	_dragWidget.window_classification = w->classification;
	_dragWidget.window_number = w->number;
	_dragWidget.widget_index = widgetIndex;
	_ticksSinceDragStart = 0;

	_dragScrollIndex = window_get_scroll_data_index(w, widgetIndex);
	platform_hide_cursor();
}

/**
 * Based on (heavily changed)
 *  rct2: 0x006E9E0E,  0x006E9ED0
 */
static void input_scroll_drag_continue(int x, int y, rct_window* w)
{
	rct_widgetindex widgetIndex = _dragWidget.widget_index;
	uint8 scrollIndex = _dragScrollIndex;

	rct_widget* widget = &w->widgets[widgetIndex];
	rct_scroll* scroll = &w->scrolls[scrollIndex];

	int dx, dy;
	dx = x - gInputDragLastX;
	dy = y - gInputDragLastY;

	if (scroll->flags & HSCROLLBAR_VISIBLE) {
		sint16 size = widget->right - widget->left - 1;
		if (scroll->flags & VSCROLLBAR_VISIBLE)
			size -= 11;
		size = max(0, scroll->h_right - size);
		scroll->h_left = min(max(0, scroll->h_left + dx), size);
	}

	if (scroll->flags & VSCROLLBAR_VISIBLE) {
		sint16 	size = widget->bottom - widget->top - 1;
		if (scroll->flags & HSCROLLBAR_VISIBLE)
			size -= 11;
		size = max(0, scroll->v_bottom - size);
		scroll->v_top = min(max(0, scroll->v_top + dy), size);
	}

	widget_scroll_update_thumbs(w, widgetIndex);
	window_invalidate_by_number(w->classification, w->number);
	platform_set_cursor_position(gInputDragLastX, gInputDragLastY);
}

/**
 *
 *  rct2: 0x006E8ACB
 */
static void input_scroll_right(int x, int y, int state)
{
	rct_window* w = window_find_by_number(_dragWidget.window_classification, _dragWidget.window_number);
	if (w == NULL) {
		platform_show_cursor();
		gInputState = INPUT_STATE_RESET;
		return;
	}

	switch (state) {
	case MOUSE_STATE_RELEASED:
		_ticksSinceDragStart += RCT2_GLOBAL(RCT2_ADDRESS_TICKS_SINCE_LAST_UPDATE, sint16);
		if (x != 0 || y != 0) {
			_ticksSinceDragStart = 1000;
			input_scroll_drag_continue(x, y, w);
		}
		break;
	case MOUSE_STATE_RIGHT_RELEASE:
		gInputState = INPUT_STATE_RESET;
		platform_show_cursor();
		break;
	}
}

/**
 *
 *  rct2: 0x006E8655
 */
static void game_handle_input_mouse(int x, int y, int state)
{
	rct_window *w;
	rct_widget *widget;
	int widgetIndex;

	// Get window and widget under cursor position
	w = window_find_from_point(x, y);
	widgetIndex = w == NULL ? -1 : window_find_widget_from_point(w, x, y);
	widget = widgetIndex == -1 ? 0 : &w->widgets[widgetIndex];

	switch (gInputState) {
	case INPUT_STATE_RESET:
		window_tooltip_reset(x, y);
		// fall-through
	case INPUT_STATE_NORMAL:
		switch (state) {
		case MOUSE_STATE_RELEASED:
			input_widget_over(x, y, w, widgetIndex);
			break;
		case MOUSE_STATE_LEFT_PRESS:
			input_widget_left(x, y, w, widgetIndex);
			break;
		case MOUSE_STATE_RIGHT_PRESS:
			window_close_by_class(WC_TOOLTIP);

			if (w != NULL) {
				w = window_bring_to_front(w);
			}

			if (widgetIndex != -1) {
				switch (widget->type) {
				case WWT_VIEWPORT:
					if (!(RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_FLAGS, uint8) & (SCREEN_FLAGS_TRACK_MANAGER | SCREEN_FLAGS_TITLE_DEMO))) {
						input_viewport_drag_begin(w, x, y);
					}
					break;
				case WWT_SCROLL:
					input_scroll_drag_begin(x, y, w, widget, widgetIndex);
					break;
				}
			}
			break;
		}
		break;
	case INPUT_STATE_WIDGET_PRESSED:
		input_state_widget_pressed(x, y, state, widgetIndex, w, widget);
		break;
	case INPUT_STATE_POSITIONING_WINDOW:
		w = window_find_by_number(_dragWidget.window_classification, _dragWidget.window_number);
		if (w == NULL) {
			gInputState = INPUT_STATE_RESET;
		} else {
			input_window_position_continue(w, gInputDragLastX, gInputDragLastY, x, y);
			if (state == MOUSE_STATE_LEFT_RELEASE) {
				input_window_position_end(w, x, y);
			}
		}
		break;
	case INPUT_STATE_VIEWPORT_RIGHT:
		if (state == MOUSE_STATE_RELEASED) {
			input_viewport_drag_continue();
		} else if (state == MOUSE_STATE_RIGHT_RELEASE) {
			input_viewport_drag_end();
			if (_ticksSinceDragStart < 500) {
				// If the user pressed the right mouse button for less than 500 ticks, interpret as right click
				viewport_interaction_right_click(x, y);
			}
		}
		break;
	case INPUT_STATE_DROPDOWN_ACTIVE:
		input_state_widget_pressed(x, y, state, widgetIndex, w, widget);
		break;
	case INPUT_STATE_VIEWPORT_LEFT:
		w = window_find_by_number(_dragWidget.window_classification, _dragWidget.window_number);
		if (w == NULL) {
			gInputState = INPUT_STATE_RESET;
			break;
		}

		switch (state) {
		case MOUSE_STATE_RELEASED:
			if (w->viewport == NULL) {
				gInputState = INPUT_STATE_RESET;
				break;
			}

			if (w->classification != _dragWidget.window_classification ||
				w->number != _dragWidget.window_number ||
				!(gInputFlags & INPUT_FLAG_TOOL_ACTIVE)
			) {
				break;
			}

			w = window_find_by_number(
				RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWCLASS, rct_windowclass),
				RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWNUMBER, rct_windownumber)
			);
			if (w == NULL) {
				break;
			}

			window_event_tool_drag_call(w, RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WIDGETINDEX, uint16), x, y);
			break;
		case MOUSE_STATE_LEFT_RELEASE:
			gInputState = INPUT_STATE_RESET;
			if (RCT2_GLOBAL(0x009DE52E, rct_windownumber) == w->number) {
				if ((gInputFlags & INPUT_FLAG_TOOL_ACTIVE)) {
					w = window_find_by_number(
						RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWCLASS, rct_windowclass),
						RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWNUMBER, rct_windownumber)
						);
					if (w != NULL) {
						window_event_tool_up_call(w, RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WIDGETINDEX, uint16), x, y);
					}
				} else if (!(gInputFlags & INPUT_FLAG_4)) {
					viewport_interaction_left_click(x, y);
				}
			}
			break;
		}
		break;
	case INPUT_STATE_SCROLL_LEFT:
		switch (state) {
		case MOUSE_STATE_RELEASED:
			input_scroll_continue(w, widgetIndex, state, x, y);
			break;
		case MOUSE_STATE_LEFT_RELEASE:
			input_scroll_end();
			break;
		}
		break;
	case INPUT_STATE_RESIZING:
		w = window_find_by_number(_dragWidget.window_classification, _dragWidget.window_number);
		if (w == NULL) {
			gInputState = INPUT_STATE_RESET;
		} else {
			if (state == MOUSE_STATE_LEFT_RELEASE) {
				input_window_resize_end();
			}
			if (state == MOUSE_STATE_RELEASED || state == MOUSE_STATE_LEFT_RELEASE) {
				input_window_resize_continue(w, x, y);
			}
		}
		break;
	case INPUT_STATE_SCROLL_RIGHT:
		input_scroll_right(x, y, state);
		break;
	}
}

#pragma region Window positioning / resizing

void input_window_position_begin(rct_window *w, int widgetIndex, int x, int y)
{
	gInputState = INPUT_STATE_POSITIONING_WINDOW;
	gInputDragLastX = x - w->x;
	gInputDragLastY = y - w->y;
	_dragWidget.window_classification = w->classification;
	_dragWidget.window_number = w->number;
	_dragWidget.widget_index = widgetIndex;
}

static void input_window_position_continue(rct_window *w, int wdx, int wdy, int x, int y)
{
	int snapProximity;

	snapProximity = w->flags & WF_NO_SNAPPING ? 0 : gConfigGeneral.window_snap_proximity;
	window_move_and_snap(w, x - wdx, y - wdy, snapProximity);
}

static void input_window_position_end(rct_window *w, int x, int y)
{
	gInputState = INPUT_STATE_NORMAL;
	gTooltipTimeout = 0;
	gTooltipWidget = _dragWidget;
	window_event_moved_call(w, x, y);
}

static void input_window_resize_begin(rct_window *w, int widgetIndex, int x, int y)
{
	gInputState = INPUT_STATE_RESIZING;
	gInputDragLastX = x;
	gInputDragLastY = y;
	_dragWidget.window_classification = w->classification;
	_dragWidget.window_number = w->number;
	_dragWidget.widget_index = widgetIndex;
	_originalWindowWidth = w->width;
	_originalWindowHeight = w->height;
}

static void input_window_resize_continue(rct_window *w, int x, int y)
{
	int dx, dy, targetWidth, targetHeight;

	if (y < RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_HEIGHT, uint16) - 2) {
		dx = x - gInputDragLastX;
		dy = y - gInputDragLastY;
		targetWidth = _originalWindowWidth + dx;
		targetHeight = _originalWindowHeight + dy;

		window_resize(
			w,
			targetWidth - w->width,
			targetHeight - w->height
			);
	}
}

static void input_window_resize_end()
{
	gInputState = INPUT_STATE_NORMAL;
	gTooltipTimeout = 0;
	gTooltipWidget = _dragWidget;
}

#pragma endregion

#pragma region Viewport dragging

static void input_viewport_drag_begin(rct_window *w, int x, int y)
{
	w->flags &= ~WF_SCROLLING_TO_LOCATION;
	gInputState = INPUT_STATE_VIEWPORT_RIGHT;
	_dragWidget.window_classification = w->classification;
	_dragWidget.window_number = w->number;
	_ticksSinceDragStart = 0;
	platform_get_cursor_position(&gInputDragLastX, &gInputDragLastY);
	platform_hide_cursor();

	// gInputFlags |= INPUT_FLAG_5;
}

static void input_viewport_drag_continue()
{
	int dx, dy, newDragX, newDragY;
	rct_window *w;
	rct_viewport *viewport;

	platform_get_cursor_position(&newDragX, &newDragY);

	dx = newDragX - gInputDragLastX;
	dy = newDragY - gInputDragLastY;
	w = window_find_by_number(_dragWidget.window_classification, _dragWidget.window_number);
	assert(w != NULL);

	viewport = w->viewport;
	_ticksSinceDragStart += RCT2_GLOBAL(RCT2_ADDRESS_TICKS_SINCE_LAST_UPDATE, sint16);
	if (viewport == NULL) {
		platform_show_cursor();
		gInputState = INPUT_STATE_RESET;
	} else if (dx != 0 || dy != 0) {
		if (!(w->flags & WF_NO_SCROLLING)) {
			// User dragged a scrollable viewport

			// If the drag time is less than 500 the "drag" is usually interpreted as a right click.
			// As the user moved the mouse, don't interpret it as right click in any case.
			_ticksSinceDragStart = 1000;

			dx <<= viewport->zoom + 1;
			dy <<= viewport->zoom + 1;
			if (gConfigGeneral.invert_viewport_drag){
				w->saved_view_x -= dx;
				w->saved_view_y -= dy;
			} else {
				w->saved_view_x += dx;
				w->saved_view_y += dy;
			}
		}
	}

	platform_set_cursor_position(gInputDragLastX, gInputDragLastY);
}

static void input_viewport_drag_end()
{
	gInputState = INPUT_STATE_RESET;
	platform_show_cursor();
}

#pragma endregion

#pragma region Scroll bars

static void input_scroll_begin(rct_window *w, int widgetIndex, int x, int y)
{
	rct_widget *widget;

	widget = &w->widgets[widgetIndex];

	gInputState = INPUT_STATE_SCROLL_LEFT;
	gPressedWidget.window_classification = w->classification;
	gPressedWidget.window_number = w->number;
	gPressedWidget.widget_index = widgetIndex;
	gTooltipCursorX = x;
	gTooltipCursorY = y;

	int eax, ebx, scroll_area, scroll_id;
	scroll_id = 0; // safety
	widget_scroll_get_part(w, widget, x, y, &eax, &ebx, &scroll_area, &scroll_id);

	_currentScrollArea = scroll_area;
	_currentScrollIndex = scroll_id;
	window_event_unknown_15_call(w, scroll_id, scroll_area);
	if (scroll_area == SCROLL_PART_VIEW){
		window_event_scroll_mousedown_call(w, scroll_id, eax, ebx);
		return;
	}

	rct_widget* widg = &w->widgets[widgetIndex];
	rct_scroll* scroll = &w->scrolls[scroll_id];

	int widget_width = widg->right - widg->left - 1;
	if (scroll->flags & VSCROLLBAR_VISIBLE)
		widget_width -= 11;
	widget_width = max(scroll->h_right - widget_width, 0);

	int widget_height = widg->bottom - widg->top - 1;
	if (scroll->flags & HSCROLLBAR_VISIBLE)
		widget_height -= 11;
	widget_height = max(scroll->v_bottom - widget_height, 0);

	switch (scroll_area) {
	case SCROLL_PART_HSCROLLBAR_LEFT:
		scroll->h_left = max(scroll->h_left - 3, 0);
		break;
	case SCROLL_PART_HSCROLLBAR_RIGHT:
		scroll->h_left = min(scroll->h_left + 3, widget_width);
		break;
	case SCROLL_PART_HSCROLLBAR_LEFT_TROUGH:
		scroll->h_left = max(scroll->h_left - widget_width , 0);
		break;
	case SCROLL_PART_HSCROLLBAR_RIGHT_TROUGH:
		scroll->h_left = min(scroll->h_left + widget_width, widget_width);
		break;
	case SCROLL_PART_VSCROLLBAR_TOP:
		scroll->v_top = max(scroll->v_top - 3, 0);
		break;
	case SCROLL_PART_VSCROLLBAR_BOTTOM:
		scroll->v_top = min(scroll->v_top + 3, widget_height);
		break;
	case SCROLL_PART_VSCROLLBAR_TOP_TROUGH:
		scroll->v_top = max(scroll->v_top - widget_height, 0);
		break;
	case SCROLL_PART_VSCROLLBAR_BOTTOM_TROUGH:
		scroll->v_top = min(scroll->v_top + widget_height, widget_height);
		break;
	default:
		break;
	}
	widget_scroll_update_thumbs(w, widgetIndex);
	window_invalidate_by_number(widgetIndex, w->classification);
}

static void input_scroll_continue(rct_window *w, int widgetIndex, int state, int x, int y)
{
	rct_widget *widget;
	int scroll_part, scroll_id;
	int x2, y2;

	assert(w != NULL);

	widget = &w->widgets[widgetIndex];
	if (w->classification != gPressedWidget.window_classification ||
		w->number != gPressedWidget.window_number ||
		widgetIndex != gPressedWidget.widget_index
	) {
		invalidate_scroll();
		return;
	}

	widget_scroll_get_part(w, widget, x, y, &x2, &y2, &scroll_part, &scroll_id);

	if (_currentScrollArea == SCROLL_PART_HSCROLLBAR_THUMB){
		int originalTooltipCursorX = gTooltipCursorX;
		gTooltipCursorX = x;
		input_scroll_part_update_hthumb(w, widgetIndex, x - originalTooltipCursorX, scroll_id);
		return;
	}

	if (_currentScrollArea == SCROLL_PART_VSCROLLBAR_THUMB){
		int originalTooltipCursorY = gTooltipCursorY;
		gTooltipCursorY = y;
		input_scroll_part_update_vthumb(w, widgetIndex, y - originalTooltipCursorY, scroll_id);
		return;
	}

	x = x2;
	y = y2;

	if (scroll_part != _currentScrollArea) {
		invalidate_scroll();
		return;
	}

	switch (scroll_part){
	case SCROLL_PART_VIEW:
		window_event_scroll_mousedrag_call(w, scroll_id, x, y);
		break;
	case SCROLL_PART_HSCROLLBAR_LEFT:
		input_scroll_part_update_hleft(w, widgetIndex, scroll_id);
		break;
	case SCROLL_PART_HSCROLLBAR_RIGHT:
		input_scroll_part_update_hright(w, widgetIndex, scroll_id);
		break;
	case SCROLL_PART_HSCROLLBAR_THUMB:
	case SCROLL_PART_VSCROLLBAR_TOP:
		input_scroll_part_update_vtop(w, widgetIndex, scroll_id);
		break;
	case SCROLL_PART_VSCROLLBAR_BOTTOM:
		input_scroll_part_update_vbottom(w, widgetIndex, scroll_id);
		break;
	}
}

static void input_scroll_end()
{
	gInputState = INPUT_STATE_RESET;
	invalidate_scroll();
}

/**
 *
 *  rct2: 0x006E98F2
 */
static void input_scroll_part_update_hthumb(rct_window *w, int widgetIndex, int x, int scroll_id)
{
	rct_widget *widget = &w->widgets[widgetIndex];
	int newLeft;

	if (window_find_by_number(w->classification, w->number)) {
		newLeft = w->scrolls[scroll_id].h_right;
		newLeft *= x;
		x = widget->right - widget->left - 21;
		if (w->scrolls[scroll_id].flags & VSCROLLBAR_VISIBLE)
			x -= 11;
		newLeft /= x;
		x = newLeft;
		w->scrolls[scroll_id].flags |= HSCROLLBAR_THUMB_PRESSED;
		newLeft = w->scrolls[scroll_id].h_left;
		newLeft += x;
		if (newLeft < 0)
			newLeft = 0;
		x = widget->right - widget->left - 1;
		if (w->scrolls[scroll_id].flags & VSCROLLBAR_VISIBLE)
			x -= 11;
		x *= -1;
		x += w->scrolls[scroll_id].h_right;
		if (x < 0)
			x = 0;
		if (newLeft > x)
			newLeft = x;
		w->scrolls[scroll_id].h_left = newLeft;
		widget_scroll_update_thumbs(w, widgetIndex);
		widget_invalidate_by_number(w->classification, w->number, widgetIndex);
	}
}

/**
 *
 *  rct2: 0x006E99A9
 */
static void input_scroll_part_update_vthumb(rct_window *w, int widgetIndex, int y, int scroll_id)
{
	assert(w != NULL);
	rct_widget *widget = &w->widgets[widgetIndex];
	int newTop;

	if (window_find_by_number(w->classification, w->number)) {
		newTop = w->scrolls[scroll_id].v_bottom;
		newTop *= y;
		y = widget->bottom - widget->top - 21;
		if (w->scrolls[scroll_id].flags & HSCROLLBAR_VISIBLE)
			y -= 11;
		newTop /= y;
		y = newTop;
		w->scrolls[scroll_id].flags |= VSCROLLBAR_THUMB_PRESSED;
		newTop = w->scrolls[scroll_id].v_top;
		newTop += y;
		if (newTop < 0)
			newTop = 0;
		y = widget->bottom - widget->top - 1;
		if (w->scrolls[scroll_id].flags & HSCROLLBAR_VISIBLE)
			y -= 11;
		y *= -1;
		y += w->scrolls[scroll_id].v_bottom;
		if (y < 0)
			y = 0;
		if (newTop > y)
			newTop = y;
		w->scrolls[scroll_id].v_top = newTop;
		widget_scroll_update_thumbs(w, widgetIndex);
		widget_invalidate_by_number(w->classification, w->number, widgetIndex);
	}
}

/**
 *
 *  rct2: 0x006E9A60
 */
static void input_scroll_part_update_hleft(rct_window *w, int widgetIndex, int scroll_id)
{
	assert(w != NULL);
	if (window_find_by_number(w->classification, w->number)) {
		w->scrolls[scroll_id].flags |= HSCROLLBAR_LEFT_PRESSED;
		if (w->scrolls[scroll_id].h_left < 0)
			w->scrolls[scroll_id].h_left = 0;
		else if (w->scrolls[scroll_id].h_left >= 3)
			w->scrolls[scroll_id].h_left -= 3;
		widget_scroll_update_thumbs(w, widgetIndex);
		widget_invalidate_by_number(w->classification, w->number, widgetIndex);
	}
}

/**
 *
 *  rct2: 0x006E9ABF
 */
static void input_scroll_part_update_hright(rct_window *w, int widgetIndex, int scroll_id)
{
	assert(w != NULL);
	rct_widget *widget = &w->widgets[widgetIndex];
	if (window_find_by_number(w->classification, w->number)) {
		w->scrolls[scroll_id].flags |= HSCROLLBAR_RIGHT_PRESSED;
		w->scrolls[scroll_id].h_left += 3;
		int newLeft = widget->right - widget->left - 1;
		if (w->scrolls[scroll_id].flags & VSCROLLBAR_VISIBLE)
			newLeft -= 11;
		newLeft *= -1;
		newLeft += w->scrolls[scroll_id].h_right;
		if (newLeft < 0)
			newLeft = 0;
		if (w->scrolls[scroll_id].h_left > newLeft)
			w->scrolls[scroll_id].h_left = newLeft;
		widget_scroll_update_thumbs(w, widgetIndex);
		widget_invalidate_by_number(w->classification, w->number, widgetIndex);
	}
}

/**
 *
 *  rct2: 0x006E9C37
 */
static void input_scroll_part_update_vtop(rct_window *w, int widgetIndex, int scroll_id)
{
	assert(w != NULL);
	if (window_find_by_number(w->classification, w->number)) {
		w->scrolls[scroll_id].flags |= VSCROLLBAR_UP_PRESSED;
		if (w->scrolls[scroll_id].v_top < 0)
			w->scrolls[scroll_id].v_top = 0;
		else if (w->scrolls[scroll_id].v_top >= 3)
			w->scrolls[scroll_id].v_top -= 3;
		widget_scroll_update_thumbs(w, widgetIndex);
		widget_invalidate_by_number(w->classification, w->number, widgetIndex);
	}
}

/**
 *
 *  rct2: 0x006E9C96
 */
static void input_scroll_part_update_vbottom(rct_window *w, int widgetIndex, int scroll_id)
{
	assert(w != NULL);
	rct_widget *widget = &w->widgets[widgetIndex];
	if (window_find_by_number(w->classification, w->number)) {
		w->scrolls[scroll_id].flags |= VSCROLLBAR_DOWN_PRESSED;
		w->scrolls[scroll_id].v_top += 3;
		int newTop = widget->bottom - widget->top - 1;
		if (w->scrolls[scroll_id].flags & HSCROLLBAR_VISIBLE)
			newTop -= 11;
		newTop *= -1;
		newTop += w->scrolls[scroll_id].v_bottom;
		if (newTop < 0)
			newTop = 0;
		if (w->scrolls[scroll_id].v_top > newTop)
			w->scrolls[scroll_id].v_top = newTop;
		widget_scroll_update_thumbs(w, widgetIndex);
		widget_invalidate_by_number(w->classification, w->number, widgetIndex);
	}
}

#pragma endregion

#pragma region Widgets

/**
 *
 *  rct2: 0x006E9253
 */
static void input_widget_over(int x, int y, rct_window *w, int widgetIndex)
{
	rct_windowclass windowClass = 255;
	rct_windownumber windowNumber = 0;
	rct_widget *widget = NULL;

	if (w != NULL) {
		windowClass = w->classification;
		windowNumber = w->number;
		widget = &w->widgets[widgetIndex];
	}

	input_widget_over_change_check(windowClass, windowNumber, widgetIndex);

	if (w != NULL && widgetIndex != -1 && widget->type == WWT_SCROLL) {
		int eax, ebx, ecx, edx;
		widget_scroll_get_part(w, widget, x, y, &eax, &ebx, &ecx, &edx);

		if (ecx < 0)
			input_update_tooltip(w, widgetIndex, x, y);
		else if (ecx == 0) {
			window_event_scroll_mouseover_call(w, edx, eax, ebx);
			input_update_tooltip(w, widgetIndex, x, y);
		}
	}
	else {
		input_update_tooltip(w, widgetIndex, x, y);
	}

	gTooltipTimeout = 0;
	gTooltipCursorX = x;
	gTooltipCursorY = y;
}

/**
 *
 *  rct2: 0x006E9269
 */
static void input_widget_over_change_check(rct_windowclass windowClass, rct_windownumber windowNumber, int widgetIndex)
{
	// Prevents invalid widgets being clicked source of bug is elsewhere
	if (widgetIndex == -1)
		return;

	// Check if the widget that the cursor was over, has changed
	if (windowClass != gHoverWidget.window_classification ||
		windowNumber != gHoverWidget.window_number ||
		widgetIndex != gHoverWidget.widget_index
	) {
		// Invalidate last widget cursor was on if widget is a flat button
		input_widget_over_flatbutton_invalidate();

		// Set new cursor over widget
		gHoverWidget.window_classification = windowClass;
		gHoverWidget.window_number = windowNumber;
		gHoverWidget.widget_index = widgetIndex;

		// Invalidate new widget cursor is on if widget is a flat button
		if (windowClass != 255)
			input_widget_over_flatbutton_invalidate();
	}
}

/**
 * Used to invalidate flat button widgets when the mouse leaves and enters them. This should be generalised so that all widgets
 * can use this in the future.
 */
static void input_widget_over_flatbutton_invalidate()
{
	rct_window *w = window_find_by_number(gHoverWidget.window_classification, gHoverWidget.window_number);
	if (w != NULL) {
		window_event_invalidate_call(w);
		if (w->widgets[gHoverWidget.widget_index].type == WWT_FLATBTN) {
			widget_invalidate_by_number(
				gHoverWidget.window_classification,
				gHoverWidget.window_number,
				gHoverWidget.widget_index
			);
		}
	}
}

/**
 *
 *  rct2: 0x006E95F9
 */
static void input_widget_left(int x, int y, rct_window *w, int widgetIndex)
{
	rct_windowclass windowClass = 255;
	rct_windownumber windowNumber = 0;
	rct_widget *widget;

	if (w != NULL) {
		windowClass = w->classification;
		windowNumber = w->number;
	}

	window_close_by_class(WC_ERROR);
	window_close_by_class(WC_TOOLTIP);

	// Window might have changed position in the list, therefore find it again
	w = window_find_by_number(windowClass, windowNumber);
	if (w == NULL)
		return;

	w = window_bring_to_front(w);
	if (widgetIndex == -1)
		return;

	if (windowClass != gCurrentTextBox.window.classification ||
		windowNumber != gCurrentTextBox.window.number ||
		widgetIndex != gCurrentTextBox.widget_index) {
		window_cancel_textbox();
	}

	widget = &w->widgets[widgetIndex];

	switch (widget->type) {
	case WWT_FRAME:
	case WWT_RESIZE:
		if (window_can_resize(w) && (x >= w->x + w->width - 19 && y >= w->y + w->height - 19))
			input_window_resize_begin(w, widgetIndex, x, y);
		break;
	case WWT_VIEWPORT:
		gInputState = INPUT_STATE_VIEWPORT_LEFT;
		gInputDragLastX = x;
		gInputDragLastY = y;
		_dragWidget.window_classification = windowClass;
		_dragWidget.window_number = windowNumber;
		if (gInputFlags & INPUT_FLAG_TOOL_ACTIVE) {
			w = window_find_by_number(
				RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWCLASS, rct_windowclass),
				RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWNUMBER, rct_windownumber)
				);
			if (w != NULL) {
				window_event_tool_down_call(w, RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WIDGETINDEX, uint16), x, y);
				gInputFlags |= INPUT_FLAG_4;
			}
		}
		break;
	case WWT_CAPTION:
		input_window_position_begin(w, widgetIndex, x, y);
		break;
	case WWT_SCROLL:
		input_scroll_begin(w, widgetIndex, x, y);
		break;
	default:
		if (widget_is_enabled(w, widgetIndex) && !widget_is_disabled(w, widgetIndex)) {
			audio_play_sound_panned(SOUND_CLICK_1, w->x + (widget->left + widget->right) / 2, 0, 0, 0);

			// Set new cursor down widget
			gPressedWidget.window_classification = windowClass;
			gPressedWidget.window_number = windowNumber;
			gPressedWidget.widget_index = widgetIndex;
			gInputFlags |= INPUT_FLAG_WIDGET_PRESSED;
			gInputState = INPUT_STATE_WIDGET_PRESSED;
			RCT2_GLOBAL(0x009DE528, uint16) = 1;

			widget_invalidate_by_number(windowClass, windowNumber, widgetIndex);
			window_event_mouse_down_call(w, widgetIndex);
		}
		break;
	}
}

#pragma endregion

/**
 *
*  rct2: 0x006ED833
 */
void process_mouse_over(int x, int y)
{
	rct_window* window;
	rct_window* subWindow;

	int widgetId;
	int cursorId;
	int ebx, esi, edi, ebp;

	cursorId = CURSOR_ARROW;
	RCT2_GLOBAL(RCT2_ADDRESS_MAP_TOOLTIP_ARGS, sint16) = -1;
	window = window_find_from_point(x, y);

	if (window != NULL) {
		widgetId = window_find_widget_from_point(window, x, y);
		RCT2_GLOBAL(0x1420046, sint16) = (widgetId & 0xFFFF);
		if (widgetId != -1) {
			switch (window->widgets[widgetId].type){

			case WWT_VIEWPORT:
				if (!(gInputFlags & INPUT_FLAG_TOOL_ACTIVE)) {
					if (viewport_interaction_left_over(x, y)) {
						sub_6ED990(CURSOR_HAND_POINT);
						return;
					}
					break;
				}
				cursorId = RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_TOOL, uint8);
				subWindow = window_find_by_number(
					RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWCLASS, rct_windowclass),
					RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWNUMBER, rct_windownumber)
					);
				ebp = (int)subWindow;
				if (subWindow == NULL)
					break;

				ebx = 0;
				edi = cursorId;
				esi = (int)subWindow;
				// Not sure what this is for, no windows actually implement a handler
				// RCT2_CALLFUNC_X(subWindow->event_handlers[WE_UNKNOWN_0E], &eax, &ebx, &ecx, &edx, &esi, &edi, &ebp);
				cursorId = edi;
				if ((ebx & 0xFF) != 0)
				{
					sub_6ED990(cursorId);
					return;
				}
				break;

			case WWT_FRAME:
			case WWT_RESIZE:
				if (!(window->flags & 0x100))
					break;

				if (window->min_width == window->max_width && window->min_height == window->max_height)
					break;

				if (x < window->x + window->width - 0x13)
					break;

				if (y < window->y + window->height - 0x13)
					break;

				cursorId = CURSOR_DIAGONAL_ARROWS;
				break;

			case WWT_SCROLL:
				RCT2_GLOBAL(0x9DE558, uint16) = x;
				RCT2_GLOBAL(0x9DE55A, uint16) = y;
				int output_scroll_area, scroll_id;
				int scroll_x, scroll_y;
				widget_scroll_get_part(window, &window->widgets[widgetId], x, y, &scroll_x, &scroll_y, &output_scroll_area, &scroll_id);
				cursorId = scroll_id;
				if (output_scroll_area != SCROLL_PART_VIEW)
				{
					cursorId = CURSOR_ARROW;
					break;
				}
				// Same as default but with scroll_x/y
				cursorId = window_event_cursor_call(window, widgetId, scroll_x, scroll_y);
				if (cursorId == -1)
					cursorId = CURSOR_ARROW;
				break;
			default:
				cursorId = window_event_cursor_call(window, widgetId, x, y);
				if (cursorId == -1)
					cursorId = CURSOR_ARROW;
				break;
			}
		}
	}

	viewport_interaction_right_over(x, y);
	sub_6ED990(cursorId);
}

/**
 *
 *  rct2: 0x006ED801
 */
void process_mouse_tool(int x, int y)
{
	if (gInputFlags & INPUT_FLAG_TOOL_ACTIVE)
	{
		rct_window* w = window_find_by_number(
			RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWCLASS, rct_windowclass),
			RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WINDOWNUMBER, rct_windownumber)
			);

		if (!w)
			tool_cancel();
		else
			window_event_tool_update_call(w, RCT2_GLOBAL(RCT2_ADDRESS_TOOL_WIDGETINDEX, uint16), x, y);

	}
}

/**
 *
 *  rct2: 0x006E8DA7
 */
void input_state_widget_pressed(int x, int y, int state, int widgetIndex, rct_window *w, rct_widget *widget)
{
	RCT2_GLOBAL(0x1420054, uint16) = x;
	RCT2_GLOBAL(0x1420056, uint16) = y;

	rct_windowclass cursor_w_class;
	rct_windownumber cursor_w_number;
	cursor_w_class = gPressedWidget.window_classification;
	cursor_w_number = gPressedWidget.window_number;
	int cursor_widgetIndex = gPressedWidget.widget_index;

	rct_window *cursor_w = window_find_by_number(cursor_w_class, cursor_w_number);
	if (cursor_w == NULL) {
		gInputState = INPUT_STATE_RESET;
		return;
	}

	switch (state) {
	case MOUSE_STATE_RELEASED:
		if (!w || cursor_w_class != w->classification || cursor_w_number != w->number || widgetIndex != cursor_widgetIndex)
			break;

		if (w->disabled_widgets & (1ULL << widgetIndex))
			break;

		if (RCT2_GLOBAL(0x009DE528, uint16) != 0)
			RCT2_GLOBAL(0x009DE528, uint16)++;

		if (w->hold_down_widgets & (1ULL << widgetIndex) &&
			RCT2_GLOBAL(0x009DE528, uint16) >= 16 &&
			!(RCT2_GLOBAL(0x009DE528, uint16) & 3)
			) {
			window_event_mouse_down_call(w, widgetIndex);
		}

		if (gInputFlags & INPUT_FLAG_WIDGET_PRESSED) return;

		gInputFlags |= INPUT_FLAG_WIDGET_PRESSED;
		widget_invalidate_by_number(cursor_w_class, cursor_w_number, widgetIndex);
		return;
	case MOUSE_STATE_LEFT_RELEASE:
	case MOUSE_STATE_RIGHT_PRESS:
		if (gInputState == INPUT_STATE_DROPDOWN_ACTIVE) {
			if (w) {
				int dropdown_index = 0;

				if (w->classification == WC_DROPDOWN) {
					dropdown_index = dropdown_index_from_point(x, y, w);
					if (dropdown_index == -1) {
						goto dropdown_cleanup;
					}

					if (dropdown_index < 64 && gDropdownItemsDisabled & (1ULL << dropdown_index)) {
						goto dropdown_cleanup;
					}

					if (gDropdownItemsFormat[dropdown_index] == 0) {
						goto dropdown_cleanup;
					}
				}
				else {
					if (cursor_w_class != w->classification || cursor_w_number != w->number || widgetIndex != cursor_widgetIndex)
						goto dropdown_cleanup;
					dropdown_index = -1;
					if (gInputFlags & INPUT_FLAG_DROPDOWN_STAY_OPEN){
						if (!(gInputFlags & INPUT_FLAG_DROPDOWN_MOUSE_UP)){
							gInputFlags |= INPUT_FLAG_DROPDOWN_MOUSE_UP;
							return;
						}
					}
				}

				window_close_by_class(WC_DROPDOWN);
				cursor_w = window_find_by_number(cursor_w_class, cursor_w_number);
				if (gInputFlags & INPUT_FLAG_WIDGET_PRESSED) {
					gInputFlags &= ~INPUT_FLAG_WIDGET_PRESSED;
					widget_invalidate_by_number(cursor_w_class, cursor_w_number, cursor_widgetIndex);
				}

				gInputState = INPUT_STATE_NORMAL;
				gTooltipTimeout = 0;
				gTooltipWidget.widget_index = cursor_widgetIndex;
				gTooltipWidget.window_classification = cursor_w_class;
				gTooltipWidget.window_number = cursor_w_number;
				window_event_dropdown_call(cursor_w, cursor_widgetIndex, dropdown_index);
			}
		dropdown_cleanup:
			window_close_by_class(WC_DROPDOWN);
		}
		if (state == MOUSE_STATE_RIGHT_PRESS) {
			return;
		}

		gInputState = INPUT_STATE_NORMAL;
		gTooltipTimeout = 0;
		gTooltipWidget.widget_index = cursor_widgetIndex;

		if (!w)
			break;

		if (!widget)
			break;

		int mid_point_x = (widget->left + widget->right) / 2 + w->x;
		audio_play_sound_panned(5, mid_point_x, 0, 0, 0);
		if (cursor_w_class != w->classification || cursor_w_number != w->number || widgetIndex != cursor_widgetIndex)
			break;

		if (w->disabled_widgets & (1ULL << widgetIndex))
			break;

		widget_invalidate_by_number(cursor_w_class, cursor_w_number, widgetIndex);
		window_event_mouse_up_call(w, widgetIndex);
	default:
		return;
	}

	RCT2_GLOBAL(0x009DE528, uint16) = 0;
	if (gInputState != INPUT_STATE_DROPDOWN_ACTIVE){
		// Hold down widget and drag outside of area??
		if (gInputFlags & INPUT_FLAG_WIDGET_PRESSED){
			gInputFlags &= ~INPUT_FLAG_WIDGET_PRESSED;
			widget_invalidate_by_number(cursor_w_class, cursor_w_number, cursor_widgetIndex);
		}
		return;
	}

	if (!w) return;

	if (w->classification == WC_DROPDOWN){
		int dropdown_index = dropdown_index_from_point(x, y, w);

		if (dropdown_index == -1) return;

		if (gDropdownIsColour && gDropdownLastColourHover != dropdown_index) {
			gDropdownLastColourHover = dropdown_index;
			window_tooltip_close();
			window_tooltip_show(STR_COLOUR_NAMES_START + dropdown_index, x, y);
		}

		if (dropdown_index < 64 && gDropdownItemsDisabled & (1ULL << dropdown_index)) {
			return;
		}

		if (gDropdownItemsFormat[dropdown_index] == 0) {
			return;
		}

		gDropdownHighlightedIndex = dropdown_index;
		window_invalidate_by_class(WC_DROPDOWN);
	} else {
		gDropdownLastColourHover = -1;
		window_tooltip_close();
	}
}

static void input_update_tooltip(rct_window *w, int widgetIndex, int x, int y)
{
	if (gTooltipWidget.window_classification == 255) {
		if (gTooltipNotShownTicks < 500 || (gTooltipCursorX == x && gTooltipCursorY == y)) {
			gTooltipTimeout = RCT2_GLOBAL(RCT2_ADDRESS_TICKS_SINCE_LAST_UPDATE, uint16);

			int time = 2000;
			if (gTooltipNotShownTicks >= 1) {
				time = 0;
			}
			if (time > gTooltipTimeout) {
				gTooltipNotShownTicks++;
				return;
			}

			window_tooltip_open(w, widgetIndex, x, y);
		}
	} else {
		if ((
				(w != NULL) &&
				(gTooltipWidget.window_classification != w->classification || gTooltipWidget.window_number != w->number)
			) ||
			gTooltipWidget.widget_index != widgetIndex
		) {
			window_tooltip_close();
		}
		gTooltipTimeout += RCT2_GLOBAL(RCT2_ADDRESS_TICKS_SINCE_LAST_UPDATE, uint16);
		if (gTooltipTimeout >= 8000) {
			window_close_by_class(WC_TOOLTIP);
		}
	}
}



#pragma endregion

#pragma region Keyboard input

/**
 *
 *  rct2: 0x006E3B43
 */
void title_handle_keyboard_input()
{
	rct_window *w;
	int key;

	if (gOpenRCT2Headless) {
		return;
	}

	if (!gConsoleOpen) {
		// Handle modifier keys and key scrolling
		gInputPlaceObjectModifier = PLACE_OBJECT_MODIFIER_NONE;
		if (RCT2_GLOBAL(0x009E2B64, uint32) != 1) {
			if (gKeysState[SDL_SCANCODE_LSHIFT] || gKeysState[SDL_SCANCODE_RSHIFT])
				gInputPlaceObjectModifier |= PLACE_OBJECT_MODIFIER_SHIFT_Z;
			if (gKeysState[SDL_SCANCODE_LCTRL] || gKeysState[SDL_SCANCODE_RCTRL])
				gInputPlaceObjectModifier |= PLACE_OBJECT_MODIFIER_COPY_Z;
			if (gKeysState[SDL_SCANCODE_LALT] || gKeysState[SDL_SCANCODE_RALT])
				gInputPlaceObjectModifier |= 4;
#ifdef __MACOSX__
			if (gKeysState[SDL_SCANCODE_LGUI] || gKeysState[SDL_SCANCODE_RGUI]) {
				gInputPlaceObjectModifier |= 8;
			}
#endif
		}
	}

	while ((key = get_next_key()) != 0) {
		if (key == 255)
			continue;

		// Reserve backtick for console
		if (key == SDL_SCANCODE_GRAVE) {
			if (gConfigGeneral.debugging_tools || gConsoleOpen) {
				window_cancel_textbox();
				console_toggle();
			}
			continue;
		} else if (gConsoleOpen) {
			console_input(key);
			continue;
		}

		key |= gInputPlaceObjectModifier << 8;

		w = window_find_by_class(WC_CHANGE_KEYBOARD_SHORTCUT);
		if (w != NULL) {
			keyboard_shortcut_set(key);
		}
		else if (key == gShortcutKeys[SHORTCUT_SCREENSHOT]) {
			keyboard_shortcut_handle_command(SHORTCUT_SCREENSHOT);
		}
	}
}

/**
 *
 *  rct2: 0x006E3B43
 */
void game_handle_keyboard_input()
{
	rct_window *w;
	int key;

	if (!gConsoleOpen) {
		// Handle mouse scrolling
		if (gInputState == INPUT_STATE_NORMAL && gConfigGeneral.edge_scrolling) {
			if (!(gInputPlaceObjectModifier & (PLACE_OBJECT_MODIFIER_SHIFT_Z | PLACE_OBJECT_MODIFIER_COPY_Z))) {
				game_handle_edge_scroll();
			}
		}

		// Handle modifier keys and key scrolling
		gInputPlaceObjectModifier = PLACE_OBJECT_MODIFIER_NONE;
		if (RCT2_GLOBAL(0x009E2B64, uint32) != 1) {
			if (gKeysState[SDL_SCANCODE_LSHIFT] || gKeysState[SDL_SCANCODE_RSHIFT]) {
				gInputPlaceObjectModifier |= PLACE_OBJECT_MODIFIER_SHIFT_Z;
			}
			if (gKeysState[SDL_SCANCODE_LCTRL] || gKeysState[SDL_SCANCODE_RCTRL]) {
				gInputPlaceObjectModifier |= PLACE_OBJECT_MODIFIER_COPY_Z;
			}
			if (gKeysState[SDL_SCANCODE_LALT] || gKeysState[SDL_SCANCODE_RALT]) {
				gInputPlaceObjectModifier |= 4;
			}
#ifdef __MACOSX__
			if (gKeysState[SDL_SCANCODE_LGUI] || gKeysState[SDL_SCANCODE_RGUI]) {
				gInputPlaceObjectModifier |= 8;
			}
#endif
			game_handle_key_scroll();
		}
	}


	// Handle key input
	while (!gOpenRCT2Headless && (key = get_next_key()) != 0) {
		if (key == 255)
			continue;

		// Reserve backtick for console
		if (key == SDL_SCANCODE_GRAVE) {
			if (gConfigGeneral.debugging_tools || gConsoleOpen) {
				window_cancel_textbox();
				console_toggle();
			}
			continue;
		} else if (gConsoleOpen) {
			console_input(key);
			continue;
		} else if (gChatOpen) {
			chat_input(key);
			continue;
		}

		key |= gInputPlaceObjectModifier << 8;

		w = window_find_by_class(WC_CHANGE_KEYBOARD_SHORTCUT);
		if (w != NULL) {
			keyboard_shortcut_set(key);
		} else {
			w = window_find_by_class(WC_TEXTINPUT);
			if (w != NULL) {
				window_text_input_key(w, key);
			} else if (!gUsingWidgetTextBox) {
				keyboard_shortcut_handle(key);
			}
		}
	}
}

/**
 *
 *  rct2: 0x00406CD2
 */
int get_next_key()
{
	int i;
	for (i = 0; i < 221; i++) {
		if (gKeysPressed[i]) {
			gKeysPressed[i] = 0;
			return i;
		}
	}

	return 0;
}

#pragma endregion

/**
*
*  rct2: 0x006ED990
*/
void sub_6ED990(char cursor_id){
	if (gInputState == INPUT_STATE_RESIZING)
	{
		cursor_id = CURSOR_DIAGONAL_ARROWS;	//resize icon
	}

	if (cursor_id == RCT2_GLOBAL(RCT2_ADDRESS_CURENT_CURSOR, uint8))
	{
		return;
	}
	RCT2_GLOBAL(RCT2_ADDRESS_CURENT_CURSOR, uint8) = cursor_id;
	RCT2_GLOBAL(0x14241BC, uint32) = 2;
	platform_set_cursor(cursor_id);
	RCT2_GLOBAL(0x14241BC, uint32) = 0;
}



/**
 *
 *  rct2: 0x006E876D
 */
void invalidate_scroll()
{
	rct_window* w = window_find_by_number(gPressedWidget.window_classification, gPressedWidget.window_number);
	if (w != NULL) {
		// Reset to basic scroll
		w->scrolls[_currentScrollIndex].flags &= 0xFF11;
		window_invalidate_by_number(gPressedWidget.window_classification, gPressedWidget.window_number);
	}
}

/**
* rct2: 0x00406C96
*/
void store_mouse_input(int state)
{
	uint32 writeIndex = _mouseInputQueueWriteIndex;
	uint32 nextWriteIndex = (writeIndex + 1) % countof(_mouseInputQueue);

	// Check if the queue is full
	if (nextWriteIndex != _mouseInputQueueReadIndex) {
		rct_mouse_data *item = &_mouseInputQueue[writeIndex];
		item->x = RCT2_GLOBAL(0x01424318, uint32);
		item->y = RCT2_GLOBAL(0x0142431C, uint32);
		item->state = state;

		_mouseInputQueueWriteIndex = nextWriteIndex;
	}
}

void game_handle_edge_scroll()
{
	rct_window *mainWindow;
	int scrollX, scrollY;

	mainWindow = window_get_main();
	if (mainWindow == NULL)
		return;
	if ((mainWindow->flags & WF_NO_SCROLLING) || (RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_FLAGS, uint8) & 9))
		return;
	if (mainWindow->viewport == NULL)
		return;

	uint32 window_flags = SDL_GetWindowFlags(gWindow);
	if ((window_flags & SDL_WINDOW_INPUT_FOCUS) == 0)
		return;

	scrollX = 0;
	scrollY = 0;

	// Scroll left / right
	if (gCursorState.x == 0)
		scrollX = -1;
	else if (gCursorState.x == RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_WIDTH, uint16) - 1)
		scrollX = 1;

	// Scroll up / down
	if (gCursorState.y == 0)
		scrollY = -1;
	else if (gCursorState.y == RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_HEIGHT, uint16) - 1)
		scrollY = 1;

	// Scroll viewport
	if (scrollX != 0) {
		mainWindow->saved_view_x += scrollX * (12 << mainWindow->viewport->zoom);
		gInputFlags |= INPUT_FLAG_VIEWPORT_SCROLLING;
	}
	if (scrollY != 0) {
		mainWindow->saved_view_y += scrollY * (12 << mainWindow->viewport->zoom);
		gInputFlags |= INPUT_FLAG_VIEWPORT_SCROLLING;
	}
}

void game_handle_key_scroll()
{
	rct_window *mainWindow;
	int scrollX, scrollY;

	mainWindow = window_get_main();
	if (mainWindow == NULL)
		return;
	if ((mainWindow->flags & WF_NO_SCROLLING) || (RCT2_GLOBAL(RCT2_ADDRESS_SCREEN_FLAGS, uint8) & 9))
		return;
	if (mainWindow->viewport == NULL)
		return;

	rct_window *textWindow;

	textWindow = window_find_by_class(WC_TEXTINPUT);
	if (textWindow || gUsingWidgetTextBox) return;

	scrollX = 0;
	scrollY = 0;

	for (int shortcutId = SHORTCUT_SCROLL_MAP_UP; shortcutId <= SHORTCUT_SCROLL_MAP_RIGHT; shortcutId++) {
		const int SHIFT = 0x100;
		const int CTRL = 0x200;
		const int ALT = 0x400;
		const int CMD = 0x800;

		uint16 shortcutKey = gShortcutKeys[shortcutId];
		uint8 scancode = shortcutKey & 0xFF;

		if (shortcutKey == 0xFFFF) continue;
		if (!gKeysState[scancode]) continue;

		if (shortcutKey & SHIFT) {
			if (!gKeysState[SDL_SCANCODE_LSHIFT] && !gKeysState[SDL_SCANCODE_RSHIFT]) continue;
		}
		if (shortcutKey & CTRL) {
			if (!gKeysState[SDL_SCANCODE_LCTRL] && !gKeysState[SDL_SCANCODE_RCTRL]) continue;
		}
		if (shortcutKey & ALT) {
			if (!gKeysState[SDL_SCANCODE_LALT] && !gKeysState[SDL_SCANCODE_RALT]) continue;
		}
#ifdef __MACOSX__
		if (shortcutKey & CMD) {
			if (!gKeysState[SDL_SCANCODE_LGUI] && !gKeysState[SDL_SCANCODE_RGUI]) continue;
		}
#endif

		switch (shortcutId) {
		case SHORTCUT_SCROLL_MAP_UP:
			scrollY = -1;
			break;
		case SHORTCUT_SCROLL_MAP_LEFT:
			scrollX = -1;
			break;
		case SHORTCUT_SCROLL_MAP_DOWN:
			scrollY = 1;
			break;
		case SHORTCUT_SCROLL_MAP_RIGHT:
			scrollX = 1;
			break;
		}
	}

	// Scroll viewport
	if (scrollX != 0) {
		mainWindow->saved_view_x += scrollX * (12 << mainWindow->viewport->zoom);
		gInputFlags |= INPUT_FLAG_VIEWPORT_SCROLLING;
	}
	if (scrollY != 0) {
		mainWindow->saved_view_y += scrollY * (12 << mainWindow->viewport->zoom);
		gInputFlags |= INPUT_FLAG_VIEWPORT_SCROLLING;
	}
}
