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
#include "../audio/audio.h"
#include "../cursors.h"
#include "../drawing/drawing.h"
#include "../editor.h"
#include "../game.h"
#include "../input.h"
#include "../localisation/localisation.h"
#include "../localisation/string_ids.h"
#include "../platform/platform.h"
#include "../world/map.h"
#include "../world/sprite.h"
#include "viewport.h"
#include "widget.h"
#include "window.h"

#define RCT2_FIRST_WINDOW		(g_window_list)
#define RCT2_LAST_WINDOW		(gWindowNextSlot - 1)
#define RCT2_NEW_WINDOW			(gWindowNextSlot)

rct_window g_window_list[MAX_WINDOW_COUNT];
rct_window * gWindowFirst;
rct_window * gWindowNextSlot;

uint16 TextInputDescriptionArgs[4];
widget_identifier gCurrentTextBox = { { 255, 0 }, 0 };
char gTextBoxInput[512] = { 0 };
int gMaxTextBoxInputLength = 0;
int gTextBoxFrameNo = 0;
bool gUsingWidgetTextBox = 0;
bool gLoadSaveTitleSequenceSave = 0;

uint8 gToolbarDirtyFlags;
uint16 gWindowMapFlashingFlags;

// converted from uint16 values at 0x009A41EC - 0x009A4230
// these are percentage coordinates of the viewport to center to, if a window is obscuring a location, the next is tried
float window_scroll_locations[][2] = {
	{0.5f,		0.5f},
	{0.75f,		0.5f},
	{0.25f,		0.5f},
	{0.5f,		0.75f},
	{0.5f,		0.25f},
	{0.75f,		0.75f},
	{0.75f,		0.25f},
	{0.25f,		0.75f},
	{0.25f,		0.25f},
	{0.125f,	0.5f},
	{0.875f,	0.5f},
	{0.5f,		0.125f},
	{0.5f,		0.875f},
	{0.875f,	0.125f},
	{0.875f,	0.875f},
	{0.125f,	0.875f},
	{0.125f,	0.125f},
};

static bool sub_6EA95D(int x, int y, int width, int height);
static void window_all_wheel_input();
static int window_draw_split(rct_drawpixelinfo *dpi, rct_window *w, int left, int top, int right, int bottom);
static void window_draw_single(rct_drawpixelinfo *dpi, rct_window *w, int left, int top, int right, int bottom);

int window_get_widget_index(rct_window *w, rct_widget *widget)
{
	int i = 0;
	for (rct_widget *widget2 = w->widgets; widget2->type != WWT_LAST; widget2++, i++)
		if (widget == widget2)
			return i;
	return -1;
}

int window_get_scroll_index(rct_window *w, int targetWidgetIndex)
{
	if (w->widgets[targetWidgetIndex].type != WWT_SCROLL)
		return -1;

	int scrollIndex = 0;
	int widgetIndex = 0;
	for (rct_widget *widget = w->widgets; widget->type != WWT_LAST; widget++, widgetIndex++) {
		if (widgetIndex == targetWidgetIndex)
			break;
		if (widget->type == WWT_SCROLL)
			scrollIndex++;
	}

	return scrollIndex;
}

int window_get_scroll_index_from_widget(rct_window *w, rct_widget *widget)
{
	if (widget->type != WWT_SCROLL)
		return -1;

	int scrollIndex = 0;
	for (rct_widget *widget2 = w->widgets; widget2->type != WWT_LAST; widget2++) {
		if (widget2 == widget)
			break;
		if (widget2->type == WWT_SCROLL)
			scrollIndex++;
	}

	return scrollIndex;
}

rct_widget *window_get_scroll_widget(rct_window *w, int scrollIndex)
{
	for (rct_widget *widget = w->widgets; widget->type != WWT_LAST; widget++) {
		if (widget->type != WWT_SCROLL)
			continue;

		if (scrollIndex == 0)
			return widget;
		scrollIndex--;
	}

	return NULL;
}

/**
 *
 *  rct2: 0x006ED7B0
 */
void window_dispatch_update_all()
{
	// gTooltipNotShownTicks++;
	for (rct_window *w = RCT2_LAST_WINDOW; w >= g_window_list; w--)
		window_event_update_call(w);
}

void window_update_all_viewports()
{
	for (rct_window *w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->viewport != NULL && window_is_visible(w))
			viewport_update_position(w);
}

/**
 *
 *  rct2: 0x006E77A1
 */
void window_update_all()
{
	RCT2_GLOBAL(0x009E3CD8, sint32)++;

	// gfx_draw_all_dirty_blocks();
	// window_update_all_viewports();
	// gfx_draw_all_dirty_blocks();

	// 1000 tick update
	RCT2_GLOBAL(RCT2_ADDRESS_WINDOW_UPDATE_TICKS, sint16) += gTicksSinceLastUpdate;
	if (RCT2_GLOBAL(RCT2_ADDRESS_WINDOW_UPDATE_TICKS, sint16) >= 1000) {
		RCT2_GLOBAL(RCT2_ADDRESS_WINDOW_UPDATE_TICKS, sint16) = 0;
		for (rct_window* w = RCT2_LAST_WINDOW; w >= g_window_list; w--)
			window_event_unknown_07_call(w);
	}

	// Border flash invalidation
	for (rct_window* w = RCT2_LAST_WINDOW; w >= g_window_list; w--) {
		if (w->flags & WF_WHITE_BORDER_MASK) {
			w->flags -= WF_WHITE_BORDER_ONE;
			if (!(w->flags & WF_WHITE_BORDER_MASK))
				window_invalidate(w);
		}
	}

	window_all_wheel_input();
}

/**
 *
 *  rct2: 0x006E78E3
 */
static void window_scroll_wheel_input(rct_window *w, int scrollIndex, int wheel)
{
	rct_scroll *scroll = &w->scrolls[scrollIndex];
	rct_widget *widget = window_get_scroll_widget(w, scrollIndex);
	int widgetIndex = window_get_widget_index(w, widget);

	if (scroll->flags & VSCROLLBAR_VISIBLE) {
		int size = widget->bottom - widget->top - 1;
		if (scroll->flags & HSCROLLBAR_VISIBLE)
			size -= 11;
		size = max(0, scroll->v_bottom - size);
		scroll->v_top = min(max(0, scroll->v_top + wheel), size);
	} else {
		int size = widget->right - widget->left - 1;
		if (scroll->flags & VSCROLLBAR_VISIBLE)
			size -= 11;
		size = max(0, scroll->h_right - size);
		scroll->h_left = min(max(0, scroll->h_left + wheel), size);
	}

	widget_scroll_update_thumbs(w, widgetIndex);
	widget_invalidate(w, widgetIndex);
}

/**
 *
 *  rct2: 0x006E793B
 */
static int window_wheel_input(rct_window *w, int wheel)
{
	int i = 0;
	for (rct_widget *widget = w->widgets; widget->type != WWT_LAST; widget++) {
		if (widget->type != WWT_SCROLL)
			continue;

		// Originally always checked first scroll view, bug maybe?
		rct_scroll *scroll = &w->scrolls[i];
		if (scroll->flags & (HSCROLLBAR_VISIBLE | VSCROLLBAR_VISIBLE)) {
			window_scroll_wheel_input(w, i, wheel);
			return 1;
		}
		i++;
	}

	return 0;
}

/**
 *
 *  rct2: 0x006E79FB
 */
static void window_viewport_wheel_input(rct_window *w, int wheel)
{
	if (gScreenFlags & 9)
		return;

	if (wheel < 0)
		window_zoom_in(w);
	else if (wheel > 0)
		window_zoom_out(w);
}

static bool window_other_wheel_input(rct_window *w, int widgetIndex, int wheel)
{
	// HACK: Until we have a new window system that allows us to add new events like mouse wheel easily,
	//       this selective approach will have to do.

	// Allow mouse wheel scrolling to increment or decrement the land tool size for various windows
	int previewWidgetIndex;
	switch (w->classification) {
	case WC_WATER:
	case WC_CLEAR_SCENERY:
	case WC_LAND_RIGHTS:
		previewWidgetIndex = 3;
		break;
	case WC_LAND:
		previewWidgetIndex = 5;
		break;
	case WC_MAP:
		previewWidgetIndex = 13;
		break;
	default:
		return false;
	}

	// Preview / Increment / Decrement
	if (widgetIndex >= previewWidgetIndex && widgetIndex < previewWidgetIndex + 3) {
		int buttonWidgetIndex = wheel < 0 ? previewWidgetIndex + 2 : previewWidgetIndex + 1;
		window_event_mouse_up_call(w, buttonWidgetIndex);
		return true;
	}

	return false;
}

/**
 *
 *  rct2: 0x006E7868
 */
static void window_all_wheel_input()
{
	// Get wheel value
	int raw = gCursorState.wheel;
	int wheel = 0;
	while (1) {
		raw -= 120;
		if (raw < 0)
			break;
		wheel -= 17;
	}
	raw += 120;
	while (1) {
		raw += 120;
		if (raw > 0)
			break;
		wheel += 17;
	}
	raw -= 120;
	gCursorState.wheel = raw;

	if (wheel == 0)
		return;

	// Check window cursor is over
	if (!(gInputFlags & INPUT_FLAG_5)) {
		rct_window *w = window_find_from_point(gCursorState.x, gCursorState.y);
		if (w != NULL) {
			// Check if main window
			if (w->classification == WC_MAIN_WINDOW || w->classification == WC_VIEWPORT) {
				window_viewport_wheel_input(w, wheel);
				return;
			}

			// Check scroll view, cursor is over
			int widgetIndex = window_find_widget_from_point(w, gCursorState.x, gCursorState.y);
			if (widgetIndex != -1) {
				rct_widget *widget = &w->widgets[widgetIndex];
				if (widget->type == WWT_SCROLL) {
					rct_scroll *scroll = &w->scrolls[RCT2_GLOBAL(0x01420075, uint8)];
					if (scroll->flags & (HSCROLLBAR_VISIBLE | VSCROLLBAR_VISIBLE)) {
						window_scroll_wheel_input(w, window_get_scroll_index(w, widgetIndex), wheel);
						return;
					}
				} else {
					if (window_other_wheel_input(w, widgetIndex, wheel)) {
						return;
					}
				}

				// Check other scroll views on window
				if (window_wheel_input(w, wheel))
					return;
			}
		}
	}

	// Check windows, front to back
	for (rct_window *w = RCT2_LAST_WINDOW; w >= g_window_list; w--)
		if (window_wheel_input(w, wheel))
			return;
}

/**
 * Opens a new window.
 *  rct2: 0x006EACA4
 *
 * @param x (ax)
 * @param y (eax >> 16)
 * @param width (bx)
 * @param height (ebx >> 16)
 * @param events (edx)
 * @param flags (ch)
 * @param class (cl)
 */
rct_window *window_create(int x, int y, int width, int height, rct_window_event_list *event_handlers, rct_windowclass cls, uint16 flags)
{
	// Check if there are any window slots left
	if (RCT2_NEW_WINDOW >= &(g_window_list[MAX_WINDOW_COUNT])) {
		rct_window *w = NULL;
		// Close least recently used window
		for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
			if (!(w->flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT | WF_NO_AUTO_CLOSE)))
				break;

		window_close(w);
	}

	rct_window *w = RCT2_NEW_WINDOW;

	// Flags
	if (flags & WF_STICK_TO_BACK) {
		for (; w >= g_window_list + 1; w--) {
			if ((w - 1)->flags & WF_STICK_TO_FRONT)
				continue;
			if ((w - 1)->flags & WF_STICK_TO_BACK)
				break;
		}
	} else if (!(flags & WF_STICK_TO_FRONT)) {
		for (; w >= g_window_list + 1; w--) {
			if (!((w - 1)->flags & WF_STICK_TO_FRONT))
				break;
		}
	}

	// Move w to new window slot
	if (w != RCT2_NEW_WINDOW)
		*RCT2_NEW_WINDOW = *w;

	// Setup window
	w->classification = cls;
	w->var_4B8 = -1;
	w->var_4B9 = -1;
	w->flags = flags;

	// Play sounds and flash the window
	if (!(flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT))){
		w->flags |= WF_WHITE_BORDER_MASK;
		audio_play_sound_panned(SOUND_WINDOW_OPEN, x + (width / 2), 0, 0, 0);
	}

	w->number = 0;
	w->x = x;
	w->y = y;
	w->width = width;
	w->height = height;
	w->viewport = NULL;
	w->event_handlers = event_handlers;
	w->enabled_widgets = 0;
	w->disabled_widgets = 0;
	w->pressed_widgets = 0;
	w->hold_down_widgets = 0;
	w->viewport_focus_coordinates.var_480 = 0;
	w->viewport_focus_coordinates.x = 0;
	w->viewport_focus_coordinates.y = 0;
	w->viewport_focus_coordinates.z = 0;
	w->viewport_focus_coordinates.rotation = 0;
	w->page = 0;
	w->var_48C = 0;
	w->frame_no = 0;
	w->list_information_type = 0;
	w->var_492 = 0;
	w->selected_tab = 0;
	w->var_4AE = 0;
	RCT2_NEW_WINDOW++;

	window_invalidate(w);
	return w;
}

/**
 *
 *  rct2: 0x006EA934
 *
 * @param x (dx)
 * @param y (ax)
 * @param width (bx)
 * @param height (cx)
 */
static bool sub_6EA8EC(int x, int y, int width, int height)
{
	uint16 screenWidth = gScreenWidth;
	uint16 screenHeight = gScreenHeight;
	int unk;

	unk = -(width / 4);
	if (x < unk) return false;
	unk =  screenWidth + (unk * 2);
	if (x > unk) return false;
	if (y < 28) return false;
	unk = screenHeight - (height / 4);
	if (y > unk) return false;
	return sub_6EA95D(x, y, width, height);
}

/**
 *
 *  rct2: 0x006EA934
 *
 * @param x (dx)
 * @param y (ax)
 * @param width (bx)
 * @param height (cx)
 */
static bool sub_6EA934(int x, int y, int width, int height)
{
	if (x < 0) return false;
	if (y < 28) return false;
	if (x + width > gScreenWidth) return false;
	if (y + height > gScreenHeight) return false;
	return sub_6EA95D(x, y, width, height);
}

/**
 *
 *  rct2: 0x006EA934
 *
 * @param x (dx)
 * @param y (ax)
 * @param width (bx)
 * @param height (cx)
 */
static bool sub_6EA95D(int x, int y, int width, int height)
{
	for (rct_window *w = g_window_list; w < RCT2_LAST_WINDOW; w++) {
		if (w->flags & WF_STICK_TO_BACK)
			continue;

		if (x + width <= w->x) continue;
		if (x >= w->x + w->width) continue;
		if (y + height <= w->y) continue;
		if (y >= w->y + w->height) continue;
		return false;
	}

	return true;
}

/**
 * Opens a new window, supposedly automatically positioned
 *  rct2: 0x006EA9B1
 *
 * @param width (bx)
 * @param height (ebx >> 16)
 * @param events (edx)
 * @param flags (ch)
 * @param class (cl)
 */
rct_window *window_create_auto_pos(int width, int height, rct_window_event_list *event_handlers, rct_windowclass cls, uint16 flags)
{
	uint16 screenWidth = gScreenWidth;
	uint16 screenHeight = gScreenHeight;

	if (cls & 0x80) {
		cls &= ~0x80;
		rct_window *w = window_find_by_number(RCT2_GLOBAL(0x0013CE928, rct_windowclass), RCT2_GLOBAL(0x0013CE92A, rct_windownumber));
		if (w != NULL) {
			if (w->x > -60 && w->x < gScreenWidth - 20) {
				if (w->y < gScreenHeight - 20) {
					int x = w->x;
					if (w->x + width > gScreenWidth)
						x = gScreenWidth - 20 - width;
					int y = w->y;
					return window_create(x + 10, y + 10, width, height, event_handlers, cls, flags);
				}
			}
		}
	}

	// Place window in an empty corner of the screen
	int x = 0;
	int y = 30;
	if (sub_6EA934(x, y, width, height)) goto foundSpace;

	x = screenWidth - width;
	y = 30;
	if (sub_6EA934(x, y, width, height)) goto foundSpace;

	x = 0;
	y = screenHeight - 34 - height;
	if (sub_6EA934(x, y, width, height)) goto foundSpace;

	x = screenWidth - width;
	y = screenHeight - 34 - height;
	if (sub_6EA934(x, y, width, height)) goto foundSpace;

	// Place window next to another
	for (rct_window *w = g_window_list; w < RCT2_LAST_WINDOW; w++) {
		if (w->flags & WF_STICK_TO_BACK)
			continue;

		int x = w->x + w->width + 2;
		int y = w->y;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;

		x = w->x - w->width - 2;
		y = w->y;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;

		x = w->x;
		y = w->y + w->height + 2;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;

		x = w->x;
		y = w->y - w->height - 2;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;

		x = w->x + w->width + 2;
		y = w->y - w->height - 2;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;

		x = w->x - w->width - 2;
		y = w->y - w->height - 2;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;

		x = w->x + w->width + 2;
		y = w->y + w->height + 2;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;

		x = w->x - w->width - 2;
		y = w->y + w->height + 2;
		if (sub_6EA934(x, y, width, height)) goto foundSpace;
	}

	// Overlap
	for (rct_window *w = g_window_list; w < RCT2_LAST_WINDOW; w++) {
		if (w->flags & WF_STICK_TO_BACK)
			continue;

		int x = w->x + w->width + 2;
		int y = w->y;
		if (sub_6EA8EC(x, y, width, height)) goto foundSpace;

		x = w->x - w->width - 2;
		y = w->y;
		if (sub_6EA8EC(x, y, width, height)) goto foundSpace;

		x = w->x;
		y = w->y + w->height + 2;
		if (sub_6EA8EC(x, y, width, height)) goto foundSpace;

		x = w->x;
		y = w->y - w->height - 2;
		if (sub_6EA8EC(x, y, width, height)) goto foundSpace;
	}

	// Cascade
	x = 0;
	y = 30;
	for (rct_window *w = g_window_list; w < RCT2_LAST_WINDOW; w++) {
		if (x != w->x || y != w->y)
			continue;

		x += 5;
		y += 5;
	}

	// Clamp to inside the screen
foundSpace:
	if (x < 0)
		x = 0;
	if (x + width > screenWidth)
		x = screenWidth - width;

	return window_create(x, y, width, height, event_handlers, cls, flags);
}

rct_window *window_create_centred(int width, int height, rct_window_event_list *event_handlers, rct_windowclass cls, uint16 flags)
{
	int x, y;

	x = (gScreenWidth - width) / 2;
	y = max(28, (gScreenHeight - height) / 2);
	return window_create(x, y, width, height, event_handlers, cls, flags);
}

/**
 * Closes the specified window.
 *  rct2: 0x006ECD4C
 *
 * @param window The window to close (esi).
 */
void window_close(rct_window* window)
{
	int num_windows;

	if (window == NULL)
		return;

	// Make a copy of the window class and number in case
	// the window order is changed by the close event.
	rct_windowclass cls = window->classification;
	rct_windownumber number = window->number;

	window_event_close_call(window);

	window = window_find_by_number(cls, number);
	if (window == NULL)
		return;

	// Remove viewport
	if (window->viewport != NULL) {
		window->viewport->width = 0;
		window->viewport = NULL;
	}

	// Invalidate the window (area)
	window_invalidate(window);

	// Remove window from list and reshift all windows
	RCT2_NEW_WINDOW--;
	num_windows = (RCT2_NEW_WINDOW - window);
	if (num_windows > 0)
		memmove(window, window + 1, num_windows * sizeof(rct_window));

	viewport_update_pointers();
}

/**
 * Closes all windows with the specified window class.
 *  rct2: 0x006ECCF4
 * @param cls (cl) with bit 15 set
 */
void window_close_by_class(rct_windowclass cls)
{
	for (rct_window *w = g_window_list; w < RCT2_NEW_WINDOW; w++) {
		if (w->classification == cls) {
			window_close(w);
			w = g_window_list - 1;
		}
	}
}

/**
 * Closes all windows with specified window class and number.
 *  rct2: 0x006ECCF4
 * @param cls (cl) without bit 15 set
 * @param number (dx)
 */
void window_close_by_number(rct_windowclass cls, rct_windownumber number)
{
	for (rct_window* w = g_window_list; w < RCT2_NEW_WINDOW; w++) {
		if (w->classification == cls && w->number == number) {
			window_close(w);
			w = g_window_list - 1;
		}
	}
}

/**
 * Finds the first window with the specified window class.
 *  rct2: 0x006EA8A0
 * @param cls (cl) with bit 15 set
 * @returns the window or NULL if no window was found.
 */
rct_window *window_find_by_class(rct_windowclass cls)
{
	for (rct_window *w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->classification == cls)
			return w;

	return NULL;
}

/**
 * Finds the first window with the specified window class and number.
 *  rct2: 0x006EA8A0
 * @param cls (cl) without bit 15 set
 * @param number (dx)
 * @returns the window or NULL if no window was found.
 */
rct_window *window_find_by_number(rct_windowclass cls, rct_windownumber number)
{
	rct_window *w;

	for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->classification == cls && w->number == number)
			return w;

	return NULL;
}

/**
 * Closes the top-most window
 *
 *  rct2: 0x006E403C
 */
void window_close_top()
{
	rct_window* w;

	window_close_by_class(WC_DROPDOWN);

	if (gScreenFlags & 2)
		if (gS6Info->editor_step != EDITOR_STEP_LANDSCAPE_EDITOR)
			return;

	for (w = RCT2_NEW_WINDOW - 1; w >= g_window_list; w--) {
		if (!(w->flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT))) {
			window_close(w);
			return;
		}
	}
}

/**
 * Closes all open windows
 *
 *  rct2: 0x006EE927
 */
void window_close_all() {
	rct_window* w;

	window_close_by_class(WC_DROPDOWN);

	for (w = g_window_list; w < RCT2_LAST_WINDOW; w++){
		if (!(w->flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT))) {
			window_close(w);
			w = g_window_list;
		}
	}
}

void window_close_all_except_class(rct_windowclass cls) {
	rct_window* w;

	window_close_by_class(WC_DROPDOWN);

	for (w = g_window_list; w < RCT2_LAST_WINDOW; w++){
		if (w->classification != cls && !(w->flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT))) {
			window_close(w);
			w = g_window_list;
		}
	}
}

/**
 *
 *  rct2: 0x006EA845
 */
rct_window *window_find_from_point(int x, int y)
{
	rct_window *w;
	rct_widget *widget;
	int widget_index;

	for (w = RCT2_LAST_WINDOW; w >= g_window_list; w--) {
		if (x < w->x || x >= w->x + w->width || y < w->y || y >= w->y + w->height)
			continue;

		if (w->flags & WF_NO_BACKGROUND) {
			widget_index = window_find_widget_from_point(w, x, y);
			if (widget_index == -1)
				continue;

			widget = &w->widgets[widget_index];
		}

		return w;
	}

	return NULL;
}

/**
 *
 *  rct2: 0x006EA594
 * x (ax)
 * y (bx)
 * returns widget_index (edx)
 * EDI NEEDS TO BE SET TO w->widgets[widget_index] AFTER
 */
int window_find_widget_from_point(rct_window *w, int x, int y)
{
	rct_widget *widget;
	int i, widget_index;

	// Invalidate the window
	window_event_invalidate_call(w);

	// Find the widget at point x, y
	widget_index = -1;
	RCT2_GLOBAL(0x01420074, uint8) = -1;
	for (i = 0;; i++) {
		widget = &w->widgets[i];
		if (widget->type == WWT_LAST) {
			break;
		} else if (widget->type != WWT_EMPTY) {
			if (widget->type == WWT_SCROLL)
				RCT2_GLOBAL(0x01420074, uint8)++;

			if (x >= w->x + widget->left && x <= w->x + widget->right &&
				y >= w->y + widget->top && y <= w->y + widget->bottom
			) {
				widget_index = i;
				RCT2_GLOBAL(0x01420075, uint8) = RCT2_GLOBAL(0x01420074, uint8);
			}
		}
	}

	// Return next widget if a dropdown
	if (widget_index != -1)
		if (w->widgets[widget_index].type == WWT_DROPDOWN)
			widget_index++;

	// Return the widget index
	return widget_index;
}

/**
 * Invalidates the specified window.
 *  rct2: 0x006EB13A
 *
 * @param window The window to invalidate (esi).
 */
void window_invalidate(rct_window *window)
{
	if (window != NULL)
		gfx_set_dirty_blocks(window->x, window->y, window->x + window->width, window->y + window->height);
}

/**
 * Invalidates all windows with the specified window class.
 *  rct2: 0x006EC3AC
 * @param cls (al) with bit 14 set
 */
void window_invalidate_by_class(rct_windowclass cls)
{
	rct_window* w;

	for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->classification == cls)
			window_invalidate(w);
}

/**
 * Invalidates all windows with the specified window class and number.
 *  rct2: 0x006EC3AC
 * @param (ah) widget index
 * @param cls (al) without bit 14 set
 * @param number (bx)
 */
void window_invalidate_by_number(rct_windowclass cls, rct_windownumber number)
{
	rct_window* w;

	for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->classification == cls && w->number == number)
			window_invalidate(w);
}

/**
 * Invalidates all windows.
 */
void window_invalidate_all()
{
	rct_window* w;

	for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		window_invalidate(w);
}

/**
 * Invalidates the specified widget of a window.
 *  rct2: 0x006EC402
 */
void widget_invalidate(rct_window *w, int widgetIndex)
{
	rct_widget* widget;

	assert(w != NULL);
	widget = &w->widgets[widgetIndex];
	if (widget->left == -2)
		return;

	gfx_set_dirty_blocks(w->x + widget->left, w->y + widget->top, w->x + widget->right + 1, w->y + widget->bottom + 1);
}

/**
 * Invalidates the specified widget of all windows that match the specified window class.
 */
void widget_invalidate_by_class(rct_windowclass cls, int widgetIndex)
{
	rct_window* w;

	for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->classification == cls)
			widget_invalidate(w, widgetIndex);
}

/**
 * Invalidates the specified widget of all windows that match the specified window class and number.
 *  rct2: 0x006EC3AC
 * @param (ah) widget index
 * @param cls (al) with bit 15 set
 * @param number (bx)
 */
void widget_invalidate_by_number(rct_windowclass cls, rct_windownumber number, int widgetIndex)
{
	rct_window* w;

	for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->classification == cls && w->number == number)
			widget_invalidate(w, widgetIndex);
}

/**
 * Initialises scroll widgets to their virtual size.
 *  rct2: 0x006EAEB8
 *
 * @param window The window (esi).
 */
void window_init_scroll_widgets(rct_window *w)
{
	rct_widget* widget;
	rct_scroll* scroll;
	int widget_index, scroll_index;
	int width, height;

	widget_index = 0;
	scroll_index = 0;
	for (widget = w->widgets; widget->type != WWT_LAST; widget++) {
		if (widget->type != WWT_SCROLL) {
			widget_index++;
			continue;
		}

		scroll = &w->scrolls[scroll_index];
		scroll->flags = 0;
		width = 0;
		height = 0;
		window_get_scroll_size(w, scroll_index, &width, &height);
		scroll->h_left = 0;
		scroll->h_right = width + 1;
		scroll->v_top = 0;
		scroll->v_bottom = height + 1;

		if (widget->content & SCROLL_HORIZONTAL)
			scroll->flags |= HSCROLLBAR_VISIBLE;
		if (widget->content & SCROLL_VERTICAL)
			scroll->flags |= VSCROLLBAR_VISIBLE;

		widget_scroll_update_thumbs(w, widget_index);

		widget_index++;
		scroll_index++;
	}
}

/**
 *
 *  rct2: 0x006EAE4E
 *
 * @param w The window (esi).
 */
void window_update_scroll_widgets(rct_window *w)
{
	int widgetIndex, scrollIndex, width, height, scrollPositionChanged;
	rct_scroll *scroll;
	rct_widget *widget;

	widgetIndex = 0;
	scrollIndex = 0;
	assert(w != NULL);
	for (widget = w->widgets; widget->type != WWT_LAST; widget++, widgetIndex++) {
		if (widget->type != WWT_SCROLL)
			continue;

		scroll = &w->scrolls[scrollIndex];
		width = 0;
		height = 0;
		window_get_scroll_size(w, scrollIndex, &width, &height);
		if (height == 0){
			scroll->v_top = 0;
		}
		else if (width == 0){
			scroll->h_left = 0;
		}
		width++;
		height++;

		scrollPositionChanged = 0;
		if ((widget->content & SCROLL_HORIZONTAL) && width != scroll->h_right) {
			scrollPositionChanged = 1;
			scroll->h_right = width;
		}

		if ((widget->content & SCROLL_VERTICAL) && height != scroll->v_bottom) {
			scrollPositionChanged = 1;
			scroll->v_bottom = height;
		}

		if (scrollPositionChanged) {
			widget_scroll_update_thumbs(w, widgetIndex);
			window_invalidate(w);
		}
		scrollIndex++;
	}
}

int window_get_scroll_data_index(rct_window *w, int widget_index)
{
	int i, result;

	result = 0;
	assert(w != NULL);
	for (i = 0; i < widget_index; i++) {
		if (w->widgets[i].type == WWT_SCROLL)
			result++;
	}
	return result;
}

/**
 *
 *  rct2: 0x006ECDA4
 */
rct_window *window_bring_to_front(rct_window *w)
{
	int i;
	rct_window* v, t;

	if (w->flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT))
		return w;

	for (v = RCT2_LAST_WINDOW; v >= g_window_list; v--)
		if (!(v->flags & WF_STICK_TO_FRONT))
			break;

	if (v >= g_window_list && w != v) {
		do {
			t = *w;
			*w = *(w + 1);
			*(w + 1) = t;
			w++;
		} while (w != v);

		window_invalidate(w);
	}

	if (w->x + w->width < 20) {
		i = 20 - w->x;
		w->x += i;
		if (w->viewport != NULL)
			w->viewport->x += i;
		window_invalidate(w);
	}

	return w;
}

rct_window *window_bring_to_front_by_class(rct_windowclass cls)
{
	rct_window* w;

	w = window_find_by_class(cls);
	if (w != NULL) {
		w->flags |= WF_WHITE_BORDER_MASK;
		window_invalidate(w);
		w = window_bring_to_front(w);
	}

	return w;
}

/**
 *
 *  rct2: 0x006ED78A
 * cls (cl)
 * number (dx)
 */
rct_window *window_bring_to_front_by_number(rct_windowclass cls, rct_windownumber number)
{
	rct_window* w;

	w = window_find_by_number(cls, number);
	if (w != NULL) {
		w->flags |= WF_WHITE_BORDER_MASK;
		window_invalidate(w);
		w = window_bring_to_front(w);
	}

	return w;
}

/**
 *
 *  rct2: 0x006EE65A
 */
void window_push_others_right(rct_window* window)
{
	for (rct_window* w = g_window_list; w < gWindowNextSlot; w++) {
		if (w == window)
			continue;
		if (w->flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT))
			continue;
		if (w->x >= window->x + window->width)
			continue;
		if (w->x + w->width <= window->x)
			continue;
		if (w->y >= window->y + window->height)
			continue;
		if (w->y + w->height <= window->y)
			continue;

		window_invalidate(w);
		if (window->x + window->width + 13 >= gScreenWidth)
			continue;
		uint16 push_amount = window->x + window->width - w->x + 3;
		w->x += push_amount;
		window_invalidate(w);
		if (w->viewport != NULL)
			w->viewport->x += push_amount;
	}
}

/**
 *
 *  rct2: 0x006EE6EA
 */
void window_push_others_below(rct_window *w1)
{
	int push_amount;
	rct_window* w2;

	// Enumerate through all other windows
	for (w2 = g_window_list; w2 < RCT2_NEW_WINDOW; w2++) {
		if (w1 == w2)
			continue;

		// ?
		if (w2->flags & (WF_STICK_TO_BACK | WF_STICK_TO_FRONT))
			continue;

		// Check if w2 intersects with w1
		if (w2->x > (w1->x + w1->width) || w2->x + w2->width < w1->x)
			continue;
		if (w2->y > (w1->y + w1->height) || w2->y + w2->height < w1->y)
			continue;

		// Check if there is room to push it down
		if (w1->y + w1->height + 80 >= gScreenHeight)
			continue;

		// Invalidate the window's current area
		window_invalidate(w2);

		push_amount = w1->y + w1->height - w2->y + 3;
		w2->y += push_amount;

		// Invalidate the window's new area
		window_invalidate(w2);

		// Update viewport position if necessary
		if (w2->viewport != NULL)
			w2->viewport->y += push_amount;
	}
}


/**
 *
 *  rct2: 0x006EE2E4
 */
rct_window *window_get_main()
{
	rct_window* w;

	for (w = g_window_list; w < RCT2_NEW_WINDOW; w++)
		if (w->classification == WC_MAIN_WINDOW)
			return w;

	return NULL;
}

/**
 * Based on
 *  rct2: 0x696ee9, 0x66842F, 0x006AF3B3
 */
void window_scroll_to_viewport(rct_window *w)
{
	int x, y, z;
	rct_window *mainWindow;
	assert(w != NULL);
	// In original checked to make sure x and y were not -1 as well.
	if (w->viewport == NULL || w->viewport_focus_coordinates.y == -1)
		return;

	if (w->viewport_focus_sprite.type & VIEWPORT_FOCUS_TYPE_SPRITE) {
		rct_sprite *sprite = &(g_sprite_list[w->viewport_focus_sprite.sprite_id]);
		x = sprite->unknown.x;
		y = sprite->unknown.y;
		z = sprite->unknown.z;
	} else {
		x = w->viewport_focus_coordinates.x;
		y = w->viewport_focus_coordinates.y & VIEWPORT_FOCUS_Y_MASK;
		z = w->viewport_focus_coordinates.z;
	}

	mainWindow = window_get_main();
	if (mainWindow != NULL)
		window_scroll_to_location(mainWindow, x, y, z);
}

/**
*
*  rct2: 0x006E7C9C
* @param w (esi)
* @param x (eax)
* @param y (ecx)
* @param z (edx)
*/
void window_scroll_to_location(rct_window *w, int x, int y, int z)
{
	rct_xyz16 location_3d = {
		.x = x,
		.y = y,
		.z = z
	};

	assert(w != NULL);
	if (w->viewport) {
		sint16 height = map_element_height(x, y);
		if (z < height - 16) {
			if (!(w->viewport->flags & 1 << 0)) {
				w->viewport->flags |= 1 << 0;
				window_invalidate(w);
			}
		} else {
			if (w->viewport->flags & 1 << 0) {
				w->viewport->flags &= ~(1 << 0);
				window_invalidate(w);
			}
		}

		rct_xy16 map_coordinate = coordinate_3d_to_2d(&location_3d, get_current_rotation());

		int i = 0;
		if (!(gScreenFlags & SCREEN_FLAGS_TITLE_DEMO)) {
			int found = 0;
			while (!found) {
				sint16 x2 = w->viewport->x + (sint16)(w->viewport->width * window_scroll_locations[i][0]);
				sint16 y2 = w->viewport->y + (sint16)(w->viewport->height * window_scroll_locations[i][1]);
				rct_window* w2 = w;
				while (1) {
					w2++;
					if (w2 >= gWindowNextSlot) {
						found = 1;
						break;
					}
					sint16 x1 = w2->x - 10;
					sint16 y1 = w2->y - 10;
					if (x2 >= x1 && x2 <= w2->width + x1 + 20) {
						if (y2 >= y1 && y2 <= w2->height + y1 + 20) {
							// window is covering this area, try the next one
							i++;
							found = 0;
							break;
						}
					}
				}
				if (i >= countof(window_scroll_locations)) {
					i = 0;
					found = 1;
				}
			}
		}
		// rct2: 0x006E7C76
		if (w->viewport_target_sprite == -1) {
			if (!(w->flags & WF_NO_SCROLLING)) {
				w->saved_view_x = map_coordinate.x - (sint16)(w->viewport->view_width * window_scroll_locations[i][0]);
				w->saved_view_y = map_coordinate.y - (sint16)(w->viewport->view_height * window_scroll_locations[i][1]);
				w->flags |= WF_SCROLLING_TO_LOCATION;
			}
		}
	}
}

/**
 *
 *  rct2: 0x00688956
 */
void sub_688956()
{
	rct_window *w;

	for (w = RCT2_NEW_WINDOW - 1; w >= g_window_list; w--)
		window_event_unknown_14_call(w);
}

/**
 *
 *  rct2: 0x0068881A
 * direction can be used to alter the camera rotation:
 *		1: clockwise
 *		-1: anti-clockwise
 */
void window_rotate_camera(rct_window *w, int direction)
{
	rct_viewport *viewport = w->viewport;
	if (viewport == NULL)
		return;

	sint16 x = (viewport->width >> 1) + viewport->x;
	sint16 y = (viewport->height >> 1) + viewport->y;
	sint16 z;

	//has something to do with checking if middle of the viewport is obstructed
	rct_viewport *other;
	screen_get_map_xy(x, y, &x, &y, &other);

	// other != viewport probably triggers on viewports in ride or guest window?
	// x is 0x8000 if middle of viewport is obstructed by another window?
	if (x == SPRITE_LOCATION_NULL || other != viewport) {
		x = (viewport->view_width >> 1) + viewport->view_x;
		y = (viewport->view_height >> 1) + viewport->view_y;

		sub_689174(&x, &y, &z);
	}
	else {
		z = map_element_height(x, y);
	}

	gCurrentRotation = (get_current_rotation() + direction) & 3;

	int new_x, new_y;
	center_2d_coordinates(x, y, z, &new_x, &new_y, viewport);

	w->saved_view_x = new_x;
	w->saved_view_y = new_y;
	viewport->view_x = new_x;
	viewport->view_y = new_y;

	window_invalidate(w);

	sub_688956();
	reset_all_sprite_quadrant_placements();
}

void window_zoom_set(rct_window *w, int zoomLevel)
{
	rct_viewport* v = w->viewport;

	zoomLevel = clamp(0, zoomLevel, 3);
	if (v->zoom == zoomLevel)
		return;

	// Zoom in
	while (v->zoom > zoomLevel) {
		v->zoom--;
		w->saved_view_x += v->view_width / 4;
		w->saved_view_y += v->view_height / 4;
		v->view_width /= 2;
		v->view_height /= 2;
	}

	// Zoom out
	while (v->zoom < zoomLevel) {
		v->zoom++;
		w->saved_view_x -= v->view_width / 2;
		w->saved_view_y -= v->view_height / 2;
		v->view_width *= 2;
		v->view_height *= 2;
	}

	// HACK: Prevents the redraw from failing when there is
	// a window on top of the viewport.
	window_bring_to_front(w);
	window_invalidate(w);
}

/**
 *
 *  rct2: 0x006887A6
 */
void window_zoom_in(rct_window *w)
{
	window_zoom_set(w, w->viewport->zoom - 1);
}

/**
 *
 *  rct2: 0x006887E0
 */
void window_zoom_out(rct_window *w)
{
	window_zoom_set(w, w->viewport->zoom + 1);
}

/**
 * Draws a window that is in the specified region.
 *  rct2: 0x006E756C
 * left (ax)
 * top (bx)
 * right (dx)
 * bottom (bp)
 */
void window_draw(rct_drawpixelinfo *dpi, rct_window *w, int left, int top, int right, int bottom)
{
	if (!window_is_visible(w)) return;

	// Split window into only the regions that require drawing
	if (window_draw_split(dpi, w, left, top, right, bottom))
		return;

	// Clamp region
	left = max(left, w->x);
	top = max(top, w->y);
	right = min(right, w->x + w->width);
	bottom = min(bottom, w->y + w->height);
	if (left >= right) return;
	if (top >= bottom) return;

	// Draw the window in this region
	for (rct_window *v = w; v < RCT2_NEW_WINDOW; v++) {
		// Don't draw overlapping opaque windows, they won't have changed
		if ((w == v || (v->flags & WF_TRANSPARENT)) && window_is_visible(v)) {
			window_draw_single(dpi, v, left, top, right, bottom);
		}
	}
}

/**
 * Splits a drawing of a window into regions that can be seen and are not hidden
 * by other opaque overlapping windows.
 */
static int window_draw_split(rct_drawpixelinfo *dpi, rct_window *w, int left, int top, int right, int bottom)
{
	rct_window* topwindow;

	// Divide the draws up for only the visible regions of the window recursively
	for (topwindow = w + 1; topwindow < RCT2_NEW_WINDOW; topwindow++) {
		// Check if this window overlaps w
		if (topwindow->x >= right || topwindow->y >= bottom)
			continue;
		if (topwindow->x + topwindow->width <= left || topwindow->y + topwindow->height <= top)
			continue;
		if (topwindow->flags & WF_TRANSPARENT)
			continue;

		// A window overlaps w, split up the draw into two regions where the window starts to overlap
		if (topwindow->x > left) {
			// Split draw at topwindow.left
			window_draw(dpi, w, left, top, topwindow->x, bottom);
			window_draw(dpi, w, topwindow->x, top, right, bottom);
		} else if (topwindow->x + topwindow->width < right) {
			// Split draw at topwindow.right
			window_draw(dpi, w, left, top, topwindow->x + topwindow->width, bottom);
			window_draw(dpi, w, topwindow->x + topwindow->width, top, right, bottom);
		} else if (topwindow->y > top) {
			// Split draw at topwindow.top
			window_draw(dpi, w, left, top, right, topwindow->y);
			window_draw(dpi, w, left, topwindow->y, right, bottom);
		} else if (topwindow->y + topwindow->height < bottom) {
			// Split draw at topwindow.bottom
			window_draw(dpi, w, left, top, right, topwindow->y + topwindow->height);
			window_draw(dpi, w, left, topwindow->y + topwindow->height, right, bottom);
		}

		// Drawing for this region should be done now, exit
		return 1;
	}

	// No windows overlap
	return 0;
}

static void window_draw_single(rct_drawpixelinfo *dpi, rct_window *w, int left, int top, int right, int bottom)
{
	// Copy dpi so we can crop it
	rct_drawpixelinfo copy = *dpi;
	dpi = &copy;

	// Clamp left to 0
	int overflow = left - dpi->x;
	if (overflow > 0) {
		dpi->x += overflow;
		dpi->width -= overflow;
		if (dpi->width <= 0)
			return;
		dpi->pitch += overflow;
		dpi->bits += overflow;
	}

	// Clamp width to right
	overflow = dpi->x + dpi->width - right;
	if (overflow > 0) {
		dpi->width -= overflow;
		if (dpi->width <= 0)
			return;
		dpi->pitch += overflow;
	}

	// Clamp top to 0
	overflow = top - dpi->y;
	if (overflow > 0) {
		dpi->y += overflow;
		dpi->height -= overflow;
		if (dpi->height <= 0)
			return;
		dpi->bits += (dpi->width + dpi->pitch) * overflow;
	}

	// Clamp height to bottom
	overflow = dpi->y + dpi->height - bottom;
	if (overflow > 0) {
		dpi->height -= overflow;
		if (dpi->height <= 0)
			return;
	}

	RCT2_GLOBAL(0x01420070, sint32) = w->x;

	// Invalidate modifies the window colours so first get the correct
	// colour before setting the global variables for the string painting
	window_event_invalidate_call(w);

	// Text colouring
	RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_WINDOW_COLOUR_1, uint8) = w->colours[0] & 0x7F;
	RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_WINDOW_COLOUR_2, uint8) = w->colours[1] & 0x7F;
	RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_WINDOW_COLOUR_3, uint8) = w->colours[2] & 0x7F;
	RCT2_GLOBAL(RCT2_ADDRESS_CURRENT_WINDOW_COLOUR_4, uint8) = w->colours[3] & 0x7F;

	window_event_paint_call(w, dpi);
}

/**
 *
 *  rct2: 0x006EB15C
 *
 * @param window (esi)
 * @param dpi (edi)
 */
void window_draw_widgets(rct_window *w, rct_drawpixelinfo *dpi)
{
	rct_widget *widget;
	int widgetIndex;

	if ((w->flags & WF_TRANSPARENT) && !(w->flags & WF_NO_BACKGROUND))
		gfx_fill_rect(dpi, w->x, w->y, w->x + w->width - 1, w->y + w->height - 1, 0x2000000 | 51);

	//todo: some code missing here? Between 006EB18C and 006EB260

	widgetIndex = 0;
	for (widget = w->widgets; widget->type != WWT_LAST; widget++) {
		// Check if widget is outside the draw region
		if (w->x + widget->left < dpi->x + dpi->width && w->x + widget->right >= dpi->x)
			if (w->y + widget->top < dpi->y + dpi->height && w->y + widget->bottom >= dpi->y)
				widget_draw(dpi, w, widgetIndex);

		widgetIndex++;
	}

	//todo: something missing here too? Between 006EC32B and 006EC369

	if (w->flags & WF_WHITE_BORDER_MASK) {
		gfx_fill_rect_inset(dpi, w->x, w->y, w->x + w->width - 1, w->y + w->height - 1, 2, 0x10);
	}
}

/**
 *
 *  rct2: 0x00685BE1
 *
 * @param dpi (edi)
 * @param w (esi)
 */
void window_draw_viewport(rct_drawpixelinfo *dpi, rct_window *w)
{
	viewport_render(dpi, w->viewport, dpi->x, dpi->y, dpi->x + dpi->width, dpi->y + dpi->height);
}

void window_set_position(rct_window *w, int x, int y)
{
	window_move_position(w, x - w->x, y - w->y);
}

void window_move_position(rct_window *w, int dx, int dy)
{
	if (dx == 0 && dy == 0)
		return;

	// Invalidate old region
	window_invalidate(w);

	// Translate window and viewport
	w->x += dx;
	w->y += dy;
	if (w->viewport != NULL) {
		w->viewport->x += dx;
		w->viewport->y += dy;
	}

	// Invalidate new region
	window_invalidate(w);
}

void window_resize(rct_window *w, int dw, int dh)
{
	int i;
	if (dw == 0 && dh == 0)
		return;

	// Invalidate old region
	window_invalidate(w);

	// Clamp new size to minimum and maximum
	w->width = clamp(w->min_width, w->width + dw, w->max_width);
	w->height = clamp(w->min_height, w->height + dh, w->max_height);

	window_event_resize_call(w);
	window_event_invalidate_call(w);

	// Update scroll widgets
	for (i = 0; i < 3; i++) {
		w->scrolls[i].h_right = -1;
		w->scrolls[i].v_bottom = -1;
	}
	window_update_scroll_widgets(w);

	// Invalidate new region
	window_invalidate(w);
}

void window_set_resize(rct_window *w, int minWidth, int minHeight, int maxWidth, int maxHeight)
{
	w->min_width = minWidth;
	w->min_height = minHeight;
	w->max_width = maxWidth;
	w->max_height = maxHeight;

	// Clamp width and height to minimum and maximum
	if (w->width < minWidth) {
		w->width = minWidth;
		window_invalidate(w);
	}
	if (w->height < minHeight) {
		w->height = minHeight;
		window_invalidate(w);
	}
	if (w->width > maxWidth) {
		w->width = maxWidth;
		window_invalidate(w);
	}
	if (w->height > maxHeight) {
		w->height = maxHeight;
		window_invalidate(w);
	}
}

/**
 *
 *  rct2: 0x006EE212
 *
 * @param tool (al)
 * @param widgetIndex (dx)
 * @param w (esi)
 */
int tool_set(rct_window *w, int widgetIndex, int tool)
{
	if (gInputFlags & INPUT_FLAG_TOOL_ACTIVE) {
		if (
			w->classification == gCurrentToolWidget.window_classification &&
			w->number == gCurrentToolWidget.window_number &&
			widgetIndex == gCurrentToolWidget.widget_index
		) {
			tool_cancel();
			return 1;
		} else {
			tool_cancel();
		}
	}

	gInputFlags |= INPUT_FLAG_TOOL_ACTIVE;
	gInputFlags &= ~INPUT_FLAG_6;
	gCurrentToolId = tool;
	gCurrentToolWidget.window_classification = w->classification;
	gCurrentToolWidget.window_number = w->number;
	gCurrentToolWidget.widget_index = widgetIndex;
	return 0;
}

/**
 *
 *  rct2: 0x006EE281
 */
void tool_cancel()
{
	rct_window *w;

	if (gInputFlags & INPUT_FLAG_TOOL_ACTIVE) {
		gInputFlags &= ~INPUT_FLAG_TOOL_ACTIVE;

		map_invalidate_selection_rect();
		map_invalidate_map_selection_tiles();

		// Reset map selection
		gMapSelectFlags = 0;

		if (gCurrentToolWidget.widget_index != -1) {
			// Invalidate tool widget
			widget_invalidate_by_number(
				gCurrentToolWidget.window_classification,
				gCurrentToolWidget.window_number,
				gCurrentToolWidget.widget_index
			);

			// Abort tool event
			w = window_find_by_number(
				gCurrentToolWidget.window_classification,
				gCurrentToolWidget.window_number
			);
			if (w != NULL)
				window_event_tool_abort_call(w, gCurrentToolWidget.widget_index);
		}
	}
}

/**
*
*  rct2: 0x0068F083
*/
void window_guest_list_init_vars_a()
{
	gNextGuestNumber = 1;
	RCT2_GLOBAL(0x00F1AF1C, uint32) = 0xFFFFFFFF;
	RCT2_GLOBAL(0x00F1EE02, uint32) = 0xFFFFFFFF;
	RCT2_GLOBAL(RCT2_ADDRESS_WINDOW_GUEST_LIST_SELECTED_FILTER, uint8) = 0xFF;
}

/**
*
*  rct2: 0x0068F050
*/
void window_guest_list_init_vars_b()
{
	RCT2_GLOBAL(RCT2_ADDRESS_WINDOW_GUEST_LIST_SELECTED_TAB, uint8) = 0;
	RCT2_GLOBAL(RCT2_ADDRESS_WINDOW_GUEST_LIST_SELECTED_VIEW, uint8) = 0;
	RCT2_GLOBAL(0x00F1AF1C, uint32) = 0xFFFFFFFF;
	RCT2_GLOBAL(0x00F1EE02, uint32) = 0xFFFFFFFF;
	RCT2_GLOBAL(RCT2_ADDRESS_WINDOW_GUEST_LIST_SELECTED_FILTER, uint8) = 0xFF;
	RCT2_GLOBAL(0x00F1AF20, uint16) = 0;
}

void window_event_close_call(rct_window *w)
{
	if (w->event_handlers->close != NULL)
		w->event_handlers->close(w);
}

void window_event_mouse_up_call(rct_window *w, int widgetIndex)
{
	if (w->event_handlers->mouse_up != NULL)
		w->event_handlers->mouse_up(w, widgetIndex);
}

void window_event_resize_call(rct_window *w)
{
	if (w->event_handlers->resize != NULL)
		w->event_handlers->resize(w);
}

void window_event_mouse_down_call(rct_window *w, int widgetIndex)
{
	if (w->event_handlers->mouse_down != NULL)
		w->event_handlers->mouse_down(widgetIndex, w, &w->widgets[widgetIndex]);
}

void window_event_dropdown_call(rct_window *w, int widgetIndex, int dropdownIndex)
{
	if (w->event_handlers->dropdown != NULL)
		w->event_handlers->dropdown(w, widgetIndex, dropdownIndex);
}

void window_event_unknown_05_call(rct_window *w)
{
	if (w->event_handlers->unknown_05 != NULL)
		w->event_handlers->unknown_05(w);
}

void window_event_update_call(rct_window *w)
{
	if (w->event_handlers->update != NULL)
		w->event_handlers->update(w);
}

void window_event_unknown_07_call(rct_window *w)
{
	if (w->event_handlers->unknown_07 != NULL)
		w->event_handlers->unknown_07(w);
}

void window_event_unknown_08_call(rct_window *w)
{
	if (w->event_handlers->unknown_08 != NULL)
		w->event_handlers->unknown_08(w);
}

void window_event_tool_update_call(rct_window *w, int widgetIndex, int x, int y)
{
	if (w->event_handlers->tool_update != NULL)
		w->event_handlers->tool_update(w, widgetIndex, x, y);
}

void window_event_tool_down_call(rct_window *w, int widgetIndex, int x, int y)
{
	if (w->event_handlers->tool_down != NULL)
		w->event_handlers->tool_down(w, widgetIndex, x, y);
}

void window_event_tool_drag_call(rct_window *w, int widgetIndex, int x, int y)
{
	if (w->event_handlers->tool_drag != NULL)
		w->event_handlers->tool_drag(w, widgetIndex, x, y);
}

void window_event_tool_up_call(rct_window *w, int widgetIndex, int x, int y)
{
	if (w->event_handlers->tool_up != NULL)
		w->event_handlers->tool_up(w, widgetIndex, x, y);
}

void window_event_tool_abort_call(rct_window *w, int widgetIndex)
{
	if (w->event_handlers->tool_abort != NULL)
		w->event_handlers->tool_abort(w, widgetIndex);
}

void window_event_unknown_0E_call(rct_window *w)
{
	if (w->event_handlers->unknown_0E != NULL)
		w->event_handlers->unknown_0E(w);
}

void window_get_scroll_size(rct_window *w, int scrollIndex, int *width, int *height)
{
	if (w->event_handlers->get_scroll_size != NULL) {
		w->event_handlers->get_scroll_size(w, scrollIndex, width, height);
	}
}

void window_event_scroll_mousedown_call(rct_window *w, int scrollIndex, int x, int y)
{
	if (w->event_handlers->scroll_mousedown != NULL)
		w->event_handlers->scroll_mousedown(w, scrollIndex, x, y);
}

void window_event_scroll_mousedrag_call(rct_window *w, int scrollIndex, int x, int y)
{
	if (w->event_handlers->scroll_mousedrag != NULL)
		w->event_handlers->scroll_mousedrag(w, scrollIndex, x, y);
}

void window_event_scroll_mouseover_call(rct_window *w, int scrollIndex, int x, int y)
{
	if (w->event_handlers->scroll_mouseover != NULL)
		w->event_handlers->scroll_mouseover(w, scrollIndex, x, y);
}

void window_event_textinput_call(rct_window *w, int widgetIndex, char *text)
{
	if (w->event_handlers->text_input != NULL)
		w->event_handlers->text_input(w, widgetIndex, text);
}

void window_event_unknown_14_call(rct_window *w)
{
	if (w->event_handlers->unknown_14 != NULL)
		w->event_handlers->unknown_14(w);
}

void window_event_unknown_15_call(rct_window *w, int scrollIndex, int scrollAreaType)
{
	if (w->event_handlers->unknown_15 != NULL)
		w->event_handlers->unknown_15(w, scrollIndex, scrollAreaType);
}

rct_string_id window_event_tooltip_call(rct_window *w, int widgetIndex)
{
	rct_string_id result = 0;
	if (w->event_handlers->tooltip != NULL)
		w->event_handlers->tooltip(w, widgetIndex, &result);
	return result;
}

int window_event_cursor_call(rct_window *w, int widgetIndex, int x, int y)
{
	int cursorId = CURSOR_ARROW;
	if (w->event_handlers->cursor != NULL)
		w->event_handlers->cursor(w, widgetIndex, x, y, &cursorId);
	return cursorId;
}

void window_event_moved_call(rct_window *w, int x, int y)
{
	if (w->event_handlers->moved != NULL)
		w->event_handlers->moved(w, x, y);
}

void window_event_invalidate_call(rct_window *w)
{
	if (w->event_handlers->invalidate != NULL)
		w->event_handlers->invalidate(w);
}

void window_event_paint_call(rct_window *w, rct_drawpixelinfo *dpi)
{
	if (w->event_handlers->paint != NULL)
		w->event_handlers->paint(w, dpi);
}

void window_event_scroll_paint_call(rct_window *w, rct_drawpixelinfo *dpi, int scrollIndex)
{
	if (w->event_handlers->scroll_paint != NULL)
		w->event_handlers->scroll_paint(w, dpi, scrollIndex);
}

/**
 * Bubbles an item one position up in the window list.  This is done by swapping
 * the two locations.
 *  rct2: New function not from rct2
 */
void window_bubble_list_item(rct_window* w, int item_position){
	char swap = w->list_item_positions[item_position];
	w->list_item_positions[item_position] = w->list_item_positions[item_position + 1];
	w->list_item_positions[item_position + 1] = swap;
}

/**
 *
 *  rct2: 0x006ED710
 * Called after a window resize to move windows if they
 * are going to be out of sight.
 */
void window_relocate_windows(int width, int height){
	int new_location = 8;
	for (rct_window* w = g_window_list; w < RCT2_NEW_WINDOW; w++){

		// Work out if the window requires moving
		if (w->x + 10 < width){
			if (w->flags&(WF_STICK_TO_BACK | WF_STICK_TO_FRONT)){
				if (w->y -22 < height)continue;
			}
			if (w->y + 10 < height)continue;
		}

		// Calculate the new locations
		int x = w->x;
		int y = w->y;
		w->x = new_location;
		w->y = new_location + 28;

		// Move the next new location so windows are not directly on top
		new_location += 8;

		// Adjust the viewport if required.
		if (w->viewport){
			w->viewport->x -= x - w->x;
			w->viewport->y -= y - w->y;
		}
	}
}

/**
* rct2: 0x0066B905
*/
void window_resize_gui(int width, int height)
{
	if (gScreenFlags & 0xE){
		window_resize_gui_scenario_editor(width, height);
		return;
	}
	rct_window *mainWind = window_get_main();
	if (mainWind != NULL) {
		rct_viewport* viewport = mainWind->viewport;
		mainWind->width = width;
		mainWind->height = height;
		RCT2_GLOBAL(0x9A9418, uint16) = width - 1;
		RCT2_GLOBAL(0x9A941C, uint16) = height - 1;
		viewport->width = width;
		viewport->height = height;
		viewport->view_width = width << viewport->zoom;
		viewport->view_height = height << viewport->zoom;
		if (mainWind->widgets != NULL && mainWind->widgets[0].type == WWT_VIEWPORT){
			mainWind->widgets[0].right = width;
			mainWind->widgets[0].bottom = height;
		}
	}

	rct_window *topWind = window_find_by_class(WC_TOP_TOOLBAR);
	if (topWind != NULL) {
		topWind->width = max(640, width);
	}

	rct_window *bottomWind = window_find_by_class(WC_BOTTOM_TOOLBAR);
	if (bottomWind != NULL) {
		bottomWind->y = height - 32;
		bottomWind->width = max(640, width);
		RCT2_GLOBAL(0x9A95D0, uint16) = width - 1;
		RCT2_GLOBAL(0x9A95E0, uint16) = width - 3;
		RCT2_GLOBAL(0x9A95DE, uint16) = width - 118;
		RCT2_GLOBAL(0x9A95CE, uint16) = width - 120;
		RCT2_GLOBAL(0x9A9590, uint16) = width - 121;
		RCT2_GLOBAL(0x9A95A0, uint16) = width - 123;
		RCT2_GLOBAL(0x9A95C0, uint16) = width - 126;
		RCT2_GLOBAL(0x9A95BE, uint16) = width - 149;
		RCT2_GLOBAL(0x9A95EE, uint16) = width - 118;
		RCT2_GLOBAL(0x9A95F0, uint16) = width - 3;
	}

	rct_window *titleWind = window_find_by_class(WC_TITLE_MENU);
	if (titleWind != NULL) {
		titleWind->x = width / 2 - 164;
		titleWind->y = height - 142;
	}

	rct_window *exitWind = window_find_by_class(WC_TITLE_EXIT);
	if (exitWind != NULL) {
		exitWind->x = width - 40;
		exitWind->y = height - 64;
	}

	rct_window *optionsWind = window_find_by_class(WC_TITLE_OPTIONS);
	if (optionsWind != NULL) {
		optionsWind->x = width - 80;
	}
}

/**
* rct2: 0x0066F0DD
*/
void window_resize_gui_scenario_editor(int width, int height)
{
	rct_window* mainWind = window_get_main();
	if (mainWind) {
		rct_viewport* viewport = mainWind->viewport;
		mainWind->width = width;
		mainWind->height = height;
		RCT2_GLOBAL(0x9A9834, uint16) = width - 1;
		RCT2_GLOBAL(0x9A9838, uint16) = height - 1;
		viewport->width = width;
		viewport->height = height;
		viewport->view_width = width << viewport->zoom;
		viewport->view_height = height << viewport->zoom;
		if (mainWind->widgets != NULL && mainWind->widgets[0].type == WWT_VIEWPORT){
			mainWind->widgets[0].right = width;
			mainWind->widgets[0].bottom = height;
		}
	}

	rct_window *topWind = window_find_by_class(WC_TOP_TOOLBAR);
	if (topWind != NULL) {
		topWind->width = max(640, width);
	}

	rct_window *bottomWind = window_find_by_class(WC_BOTTOM_TOOLBAR);
	if (bottomWind != NULL) {
		bottomWind->y = height - 32;
		bottomWind->width = max(640, width);
		RCT2_GLOBAL(0x9A997C, uint16) = bottomWind->width - 1;
		RCT2_GLOBAL(0x9A997A, uint16) = bottomWind->width - 200;
		RCT2_GLOBAL(0x9A998A, uint16) = bottomWind->width - 198;
		RCT2_GLOBAL(0x9A998C, uint16) = bottomWind->width - 3;
	}

}

/* Based on rct2: 0x6987ED and another version from window_park */
void window_align_tabs(rct_window *w, uint8 start_tab_id, uint8 end_tab_id)
{
	int i, x = w->widgets[start_tab_id].left;
	int tab_width = w->widgets[start_tab_id].right - w->widgets[start_tab_id].left;

	for (i = start_tab_id; i <= end_tab_id; i++) {
		if (!(w->disabled_widgets & (1LL << i))) {
			w->widgets[i].left = x;
			w->widgets[i].right = x + tab_width;
			x += tab_width + 1;
		}
	}
}

/**
 *
 *  rct2: 0x006CBCC3
 */
void window_close_construction_windows()
{
	window_close_by_class(WC_RIDE_CONSTRUCTION);
	window_close_by_class(WC_FOOTPATH);
	window_close_by_class(WC_TRACK_DESIGN_LIST);
	window_close_by_class(WC_TRACK_DESIGN_PLACE);
}

/**
 *
 *  rct2: 0x006EA776
 */
void window_invalidate_pressed_image_buttons(rct_window *w)
{
	int widgetIndex;
	rct_widget *widget;

	widgetIndex = 0;
	for (widget = w->widgets; widget->type != WWT_LAST; widget++, widgetIndex++) {
		if (widget->type != WWT_5 && widget->type != WWT_IMGBTN)
			continue;

		if (widget_is_pressed(w, widgetIndex) || widget_is_active_tool(w, widgetIndex))
			gfx_set_dirty_blocks(w->x, w->y, w->x + w->width, w->y + w->height);
	}
}

/**
 *
 *  rct2: 0x006EA73F
 */
void sub_6EA73F()
{
	for (rct_window *w = RCT2_LAST_WINDOW; w >= g_window_list; w--) {
		window_update_scroll_widgets(w);
		window_invalidate_pressed_image_buttons(w);
		window_event_resize_call(w);
	}
}

/**
 * Update zoom based volume attenuation for ride music and clear music list.
 *  rct2: 0x006BC348
 */
void window_update_viewport_ride_music()
{
	rct_viewport *viewport;
	rct_window *w;

	gRideMusicParamsListEnd = &gRideMusicParamsList[0];//RCT2_GLOBAL(0x009AF42C, rct_ride_music_params*) = (rct_ride_music_params*)0x009AF430;
	RCT2_GLOBAL(0x00F438A4, rct_viewport*) = (rct_viewport*)-1;

	for (w = RCT2_LAST_WINDOW; w >= g_window_list; w--) {
		viewport = w->viewport;
		if (viewport == NULL || !(viewport->flags & VIEWPORT_FLAG_SOUND_ON))
			continue;

		RCT2_GLOBAL(0x00F438A4, rct_viewport*) = viewport;
		RCT2_GLOBAL(0x00F438A8, rct_window*) = w;

		switch (viewport->zoom) {
		case 0:
			gVolumeAdjustZoom = 0;
			break;
		case 1:
			gVolumeAdjustZoom = 30;
			break;
		default:
			gVolumeAdjustZoom = 60;
			break;
		}
		break;
	}
}

void window_snap_left(rct_window *w, int proximity)
{
	int right, rightMost, wLeftProximity, wRightProximity, wBottom;
	rct_window *mainWindow, *w2;

	mainWindow = window_get_main();

	wBottom = w->y + w->height;
	wLeftProximity = w->x - (proximity * 2);
	wRightProximity = w->x + (proximity * 2);
	rightMost = INT32_MIN;
	for (w2 = g_window_list; w2 < RCT2_NEW_WINDOW; w2++) {
		if (w2 == w || w2 == mainWindow)
			continue;

		right = w2->x + w2->width;

		if (wBottom < w2->y || w->y > w2->y + w2->height)
			continue;

		if (right < wLeftProximity || right > wRightProximity)
			continue;

		rightMost = max(rightMost, right);
	}

	if (0 >= wLeftProximity && 0 <= wRightProximity)
		rightMost = max(rightMost, 0);

	if (rightMost != INT32_MIN)
		w->x = rightMost;
}

void window_snap_top(rct_window *w, int proximity)
{
	int bottom, bottomMost, wTopProximity, wBottomProximity, wRight;
	rct_window *mainWindow, *w2;

	mainWindow = window_get_main();

	wRight = w->x + w->width;
	wTopProximity = w->y - (proximity * 2);
	wBottomProximity = w->y + (proximity * 2);
	bottomMost = INT32_MIN;
	for (w2 = g_window_list; w2 < RCT2_NEW_WINDOW; w2++) {
		if (w2 == w || w2 == mainWindow)
			continue;

		bottom = w2->y + w2->height;

		if (wRight < w2->x || w->x > w2->x + w2->width)
			continue;

		if (bottom < wTopProximity || bottom > wBottomProximity)
			continue;

		bottomMost = max(bottomMost, bottom);
	}

	if (0 >= wTopProximity && 0 <= wBottomProximity)
		bottomMost = max(bottomMost, 0);

	if (bottomMost != INT32_MIN)
		w->y = bottomMost;
}

void window_snap_right(rct_window *w, int proximity)
{
	int leftMost, wLeftProximity, wRightProximity, wRight, wBottom, screenWidth;
	rct_window *mainWindow, *w2;

	mainWindow = window_get_main();

	wRight = w->x + w->width;
	wBottom = w->y + w->height;
	wLeftProximity = wRight - (proximity * 2);
	wRightProximity = wRight + (proximity * 2);
	leftMost = INT32_MAX;
	for (w2 = g_window_list; w2 < RCT2_NEW_WINDOW; w2++) {
		if (w2 == w || w2 == mainWindow)
			continue;

		if (wBottom < w2->y || w->y > w2->y + w2->height)
			continue;

		if (w2->x < wLeftProximity || w2->x > wRightProximity)
			continue;

		leftMost = min(leftMost, w2->x);
	}

	screenWidth = gScreenWidth;
	if (screenWidth >= wLeftProximity && screenWidth <= wRightProximity)
		leftMost = min(leftMost, screenWidth);

	if (leftMost != INT32_MAX)
		w->x = leftMost - w->width;
}

void window_snap_bottom(rct_window *w, int proximity)
{
	int topMost, wTopProximity, wBottomProximity, wRight, wBottom, screenHeight;
	rct_window *mainWindow, *w2;

	mainWindow = window_get_main();

	wRight = w->x + w->width;
	wBottom = w->y + w->height;
	wTopProximity = wBottom - (proximity * 2);
	wBottomProximity = wBottom + (proximity * 2);
	topMost = INT32_MAX;
	for (w2 = g_window_list; w2 < RCT2_NEW_WINDOW; w2++) {
		if (w2 == w || w2 == mainWindow)
			continue;

		if (wRight < w2->x || w->x > w2->x + w2->width)
			continue;

		if (w2->y < wTopProximity || w2->y > wBottomProximity)
			continue;

		topMost = min(topMost, w2->y);
	}

	screenHeight = gScreenHeight;
	if (screenHeight >= wTopProximity && screenHeight <= wBottomProximity)
		topMost = min(topMost, screenHeight);

	if (topMost != INT32_MAX)
		w->y = topMost - w->height;
}

void window_move_and_snap(rct_window *w, int newWindowX, int newWindowY, int snapProximity)
{
	int originalX = w->x;
	int originalY = w->y;

	newWindowY = clamp(29, newWindowY, gScreenHeight - 34);

	if (snapProximity > 0) {
		w->x = newWindowX;
		w->y = newWindowY;

		window_snap_right(w, snapProximity);
		window_snap_bottom(w, snapProximity);
		window_snap_left(w, snapProximity);
		window_snap_top(w, snapProximity);

		if (w->x == originalX && w->y == originalY)
			return;

		newWindowX = w->x;
		newWindowY = w->y;
		w->x = originalX;
		w->y = originalY;
	}

	window_set_position(w, newWindowX, newWindowY);
}

int window_can_resize(rct_window *w)
{
	return (w->flags & WF_RESIZABLE) && (w->min_width != w->max_width || w->min_height != w->max_height);
}

/**
 *
 *  rct2: 0x006EE3C3
 */
void textinput_cancel()
{
	rct_window *w;

	// Close the new text input window
	window_close_by_class(WC_TEXTINPUT);

	if (RCT2_GLOBAL(RCT2_ADDRESS_TEXTINPUT_WINDOWCLASS, uint8) != 255) {
		w = window_find_by_number(
			RCT2_GLOBAL(RCT2_ADDRESS_TEXTINPUT_WINDOWCLASS, rct_windowclass),
			RCT2_GLOBAL(RCT2_ADDRESS_TEXTINPUT_WINDOWNUMBER, rct_windownumber)
		);
		if (w != NULL) {
			window_event_textinput_call(w, RCT2_GLOBAL(RCT2_ADDRESS_TEXTINPUT_WIDGETINDEX, uint16), NULL);
		}
	}
}

void window_start_textbox(rct_window *call_w, int call_widget, rct_string_id existing_text, uint32 existing_args, int maxLength)
{
	if (gUsingWidgetTextBox)
		window_cancel_textbox();

	gUsingWidgetTextBox = true;
	gCurrentTextBox.window.classification = call_w->classification;
	gCurrentTextBox.window.number = call_w->number;
	gCurrentTextBox.widget_index = call_widget;
	gTextBoxFrameNo = 0;

	gMaxTextBoxInputLength = maxLength;

	window_close_by_class(WC_TEXTINPUT);

	// Clear the text input buffer
	memset(gTextBoxInput, 0, maxLength);

	// Enter in the the text input buffer any existing
	// text.
	if (existing_text != STR_NONE)
		format_string(gTextBoxInput, existing_text, &existing_args);

	// In order to prevent strings that exceed the maxLength
	// from crashing the game.
	gTextBoxInput[maxLength - 1] = '\0';

	platform_start_text_input(gTextBoxInput, maxLength);
}

void window_cancel_textbox()
{
	if (gUsingWidgetTextBox) {
		rct_window *w = window_find_by_number(
			gCurrentTextBox.window.classification,
			gCurrentTextBox.window.number
			);
		window_event_textinput_call(w, gCurrentTextBox.widget_index, NULL);
		gCurrentTextBox.window.classification = 255;
		gCurrentTextBox.window.number = 0;
		platform_stop_text_input();
		gUsingWidgetTextBox = false;
		widget_invalidate(w, gCurrentTextBox.widget_index);
		gCurrentTextBox.widget_index = WWT_LAST;
	}
}

void window_update_textbox_caret()
{
	gTextBoxFrameNo++;
	if (gTextBoxFrameNo > 30)
		gTextBoxFrameNo = 0;
}

void window_update_textbox()
{
	if (gUsingWidgetTextBox) {
		gTextBoxFrameNo = 0;
		rct_window *w = window_find_by_number(
			gCurrentTextBox.window.classification,
			gCurrentTextBox.window.number
			);
		widget_invalidate(w, gCurrentTextBox.widget_index);
		window_event_textinput_call(w, gCurrentTextBox.widget_index, gTextBoxInput);
	}
}

bool window_is_visible(rct_window* w)
{
	// w->visibility is used to prevent repeat calculations within an iteration by caching the result

	if (w->visibility == VC_VISIBLE) return true;
	if (w->visibility == VC_COVERED) return false;

	// only consider viewports, consider the main window always visible
	if (w == NULL || w->viewport == NULL || w->classification == WC_MAIN_WINDOW)
	{
		// default to previous behaviour
		w->visibility = VC_VISIBLE;
		return true;
	}

	// start from the window above the current
	for (rct_window *w_other = (w+1); w_other < RCT2_NEW_WINDOW; w_other++)
	{
		// if covered by a higher window, no rendering needed
		if (w_other->x <= w->x
			&& w_other->y <= w->y
			&& w_other->x + w_other->width >= w->x + w->width
			&& w_other->y + w_other->height >= w->y + w->height)
		{
			w->visibility = VC_COVERED;
			w->viewport->visibility = VC_COVERED;
			return false;
		}
	}

	// default to previous behaviour
	w->visibility = VC_VISIBLE;
	w->viewport->visibility = VC_VISIBLE;
	return true;
}
