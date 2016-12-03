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

#include "../audio/audio.h"
#include "../audio/mixer.h"
#include "../config.h"
#include "../drawing/drawing.h"
#include "../drawing/lightfx.h"
#include "../game.h"
#include "../input.h"
#include "../interface/Cursors.h"
#include "../interface/console.h"
#include "../interface/keyboard_shortcut.h"
#include "../interface/window.h"
#include "../localisation/currency.h"
#include "../localisation/localisation.h"
#include "../openrct2.h"
#include "../rct2.h"
#include "../title.h"
#include "../util/util.h"
#include "../world/climate.h"
#include "platform.h"

typedef void(*update_palette_func)(const uint8*, int, int);

openrct2_cursor gCursorState;
const unsigned char *gKeysState;
unsigned char *gKeysPressed;
unsigned int gLastKeyPressed;
textinputbuffer gTextInput;

bool gTextInputCompositionActive;
utf8 gTextInputComposition[32];
int gTextInputCompositionStart;
int gTextInputCompositionLength;

int gNumResolutions = 0;
resolution *gResolutions = NULL;
int gResolutionsAllowAnyAspectRatio = 0;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gBufferTexture = NULL;
SDL_PixelFormat *gBufferTextureFormat = NULL;
SDL_Color gPalette[256];
uint32 gPaletteHWMapped[256];

bool gSteamOverlayActive = false;

static const int _fullscreen_modes[] = { 0, SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP };
static unsigned int _lastGestureTimestamp;
static float _gestureRadius;

static void platform_create_window();

static int resolution_sort_func(const void *pa, const void *pb)
{
	const resolution *a = (resolution*)pa;
	const resolution *b = (resolution*)pb;

	int areaA = a->width * a->height;
	int areaB = b->width * b->height;

	if (areaA == areaB) return 0;
	if (areaA < areaB) return -1;
	return 1;
}

void platform_update_fullscreen_resolutions()
{
	int i, displayIndex, numDisplayModes;
	SDL_DisplayMode mode;
	resolution *resLook, *resPlace;
	float desktopAspectRatio, aspectRatio;

	// Query number of display modes
	displayIndex = SDL_GetWindowDisplayIndex(gWindow);
	numDisplayModes = SDL_GetNumDisplayModes(displayIndex);

	// Get desktop aspect ratio
	SDL_GetDesktopDisplayMode(displayIndex, &mode);
	desktopAspectRatio = (float)mode.w / mode.h;

	if (gResolutions != NULL)
		free(gResolutions);

	// Get resolutions
	gNumResolutions = numDisplayModes;
	gResolutions = malloc(gNumResolutions * sizeof(resolution));

	gNumResolutions = 0;
	for (i = 0; i < numDisplayModes; i++) {
		SDL_GetDisplayMode(displayIndex, i, &mode);

		aspectRatio = (float)mode.w / mode.h;
		if (gResolutionsAllowAnyAspectRatio || fabs(desktopAspectRatio - aspectRatio) < 0.0001f) {
			gResolutions[gNumResolutions].width = mode.w;
			gResolutions[gNumResolutions].height = mode.h;
			gNumResolutions++;
		}
	}

	// Sort by area
	qsort(gResolutions, gNumResolutions, sizeof(resolution), resolution_sort_func);

	// Remove duplicates
	resPlace = &gResolutions[0];
	for (int i = 1; i < gNumResolutions; i++) {
		resLook = &gResolutions[i];
		if (resLook->width != resPlace->width || resLook->height != resPlace->height)
			*++resPlace = *resLook;
	}

	gNumResolutions = (int)(resPlace - &gResolutions[0]) + 1;

	// Update config fullscreen resolution if not set
	if (gConfigGeneral.fullscreen_width == -1 || gConfigGeneral.fullscreen_height == -1) {
		gConfigGeneral.fullscreen_width = gResolutions[gNumResolutions - 1].width;
		gConfigGeneral.fullscreen_height = gResolutions[gNumResolutions - 1].height;
	}
}

void platform_get_closest_resolution(int inWidth, int inHeight, int *outWidth, int *outHeight)
{
	int i, destinationArea, areaDiff, closestAreaDiff, closestWidth = 640, closestHeight = 480;

	closestAreaDiff = -1;
	destinationArea = inWidth * inHeight;
	for (i = 0; i < gNumResolutions; i++) {
		// Check if exact match
		if (gResolutions[i].width == inWidth && gResolutions[i].height == inHeight) {
			closestWidth = gResolutions[i].width;
			closestHeight = gResolutions[i].height;
			closestAreaDiff = 0;
			break;
		}

		// Check if area is closer to best match
		areaDiff = abs((gResolutions[i].width * gResolutions[i].height) - destinationArea);
		if (closestAreaDiff == -1 || areaDiff < closestAreaDiff) {
			closestAreaDiff = areaDiff;
			closestWidth = gResolutions[i].width;
			closestHeight = gResolutions[i].height;
		}
	}

	if (closestAreaDiff != -1) {
		*outWidth = closestWidth;
		*outHeight = closestHeight;
	} else {
		*outWidth = 640;
		*outHeight = 480;
	}
}

void platform_draw()
{
	if (!gOpenRCT2Headless) {
		drawing_engine_draw();
	}
}

static void platform_resize(int width, int height)
{
	uint32 flags;
	int dst_w = (int)(width / gConfigGeneral.window_scale);
	int dst_h = (int)(height / gConfigGeneral.window_scale);

	gScreenWidth = dst_w;
	gScreenHeight = dst_h;

	drawing_engine_resize();

	flags = SDL_GetWindowFlags(gWindow);

	if ((flags & SDL_WINDOW_MINIMIZED) == 0) {
		window_resize_gui(dst_w, dst_h);
		window_relocate_windows(dst_w, dst_h);
	}

	title_fix_location();
	gfx_invalidate_screen();

	// Check if the window has been resized in windowed mode and update the config file accordingly
	// This is called in rct2_update and is only called after resizing a window has finished
	const int nonWindowFlags =
		SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (!(flags & nonWindowFlags)) {
		if (width != gConfigGeneral.window_width || height != gConfigGeneral.window_height) {
			gConfigGeneral.window_width = width;
			gConfigGeneral.window_height = height;
			config_save_default();
		}
	}
}

/**
 * @brief platform_trigger_resize
 * Helper function to set various render target features.
 *
 * Does not get triggered on resize, but rather manually on config changes.
 */
void platform_trigger_resize()
{
	char scale_quality_buffer[4]; // just to make sure we can hold whole uint8
	uint8 scale_quality = gConfigGeneral.scale_quality;
	if (gConfigGeneral.use_nn_at_integer_scales && gConfigGeneral.window_scale == floor(gConfigGeneral.window_scale)) {
		scale_quality = 0;
	}
	snprintf(scale_quality_buffer, sizeof(scale_quality_buffer), "%u", scale_quality);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scale_quality_buffer);

	int w, h;
	SDL_GetWindowSize(gWindow, &w, &h);
	platform_resize(w, h);
}

static uint8 soft_light(uint8 a, uint8 b)
{
	float fa = a / 255.0f;
	float fb = b / 255.0f;
	float fr;
	if (fb < 0.5f) {
		fr = (2 * fa * fb) + ((fa * fa) * (1 - (2 * fb)));
	} else {
		fr = (2 * fa * (1 - fb)) + (sqrtf(fa) * ((2 * fb) - 1));
	}
	return (uint8)(clamp(0.0f, fr, 1.0f) * 255.0f);
}

static uint8 lerp(uint8 a, uint8 b, float t)
{
	if (t <= 0) return a;
	if (t >= 1) return b;

	int range = b - a;
	int amount = (int)(range * t);
	return (uint8)(a + amount);
}

void platform_update_palette(const uint8* colours, int start_index, int num_colours)
{
	colours += start_index * 4;

	for (int i = start_index; i < num_colours + start_index; i++) {
		uint8 r = colours[2];
		uint8 g = colours[1];
		uint8 b = colours[0];

#ifdef __ENABLE_LIGHTFX__
		lightfx_apply_palette_filter(i, &r, &g, &b);
#else
		float night = gDayNightCycle;
		if (night >= 0 && gClimateLightningFlash == 0) {
			r = lerp(r, soft_light(r, 8), night);
			g = lerp(g, soft_light(g, 8), night);
			b = lerp(b, soft_light(b, 128), night);
		}
#endif

		gPalette[i].r = r;
		gPalette[i].g = g;
		gPalette[i].b = b;
		gPalette[i].a = 0;
		colours += 4;
		if (gBufferTextureFormat != NULL) {
			gPaletteHWMapped[i] = SDL_MapRGB(gBufferTextureFormat, gPalette[i].r, gPalette[i].g, gPalette[i].b);
		}
	}

	if (!gOpenRCT2Headless) {
		drawing_engine_set_palette(gPalette);
	}
}

void platform_process_messages()
{
	SDL_Event e;

	gLastKeyPressed = 0;
	// gCursorState.wheel = 0;
	gCursorState.left &= ~CURSOR_CHANGED;
	gCursorState.middle &= ~CURSOR_CHANGED;
	gCursorState.right &= ~CURSOR_CHANGED;
	gCursorState.old = 0;
	gCursorState.touch = false;

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
// 			rct2_finish();
			rct2_quit();
			break;
		case SDL_WINDOWEVENT:
			// HACK: Fix #2158, OpenRCT2 does not draw if it does not think that the window is
			//                  visible - due a bug in SDL2.0.3 this hack is required if the
			//                  window is maximised, minimised and then restored again.
			if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
				if (SDL_GetWindowFlags(gWindow) & SDL_WINDOW_MAXIMIZED) {
					SDL_RestoreWindow(gWindow);
					SDL_MaximizeWindow(gWindow);
				}
				if ((SDL_GetWindowFlags(gWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) {
					SDL_RestoreWindow(gWindow);
					SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
			}

			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				platform_resize(e.window.data1, e.window.data2);
			if (gConfigSound.audio_focus && gConfigSound.sound_enabled) {
				if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
					Mixer_SetVolume(1);
				}
				if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
					Mixer_SetVolume(0);
				}
			}
			break;
		case SDL_MOUSEMOTION:
			gCursorState.x = (int)(e.motion.x / gConfigGeneral.window_scale);
			gCursorState.y = (int)(e.motion.y / gConfigGeneral.window_scale);
			break;
		case SDL_MOUSEWHEEL:
			if (gConsoleOpen) {
				console_scroll(e.wheel.y);
				break;
			}
			gCursorState.wheel += e.wheel.y * 128;
			break;
		case SDL_MOUSEBUTTONDOWN:
		{
			int x = (int)(e.button.x / gConfigGeneral.window_scale);
			int y = (int)(e.button.y / gConfigGeneral.window_scale);
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				store_mouse_input(MOUSE_STATE_LEFT_PRESS, x, y);
				gCursorState.left = CURSOR_PRESSED;
				gCursorState.old = 1;
				break;
			case SDL_BUTTON_MIDDLE:
				gCursorState.middle = CURSOR_PRESSED;
				break;
			case SDL_BUTTON_RIGHT:
				store_mouse_input(MOUSE_STATE_RIGHT_PRESS, x, y);
				gCursorState.right = CURSOR_PRESSED;
				gCursorState.old = 2;
				break;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			int x = (int)(e.button.x / gConfigGeneral.window_scale);
			int y = (int)(e.button.y / gConfigGeneral.window_scale);
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				store_mouse_input(MOUSE_STATE_LEFT_RELEASE, x, y);
				gCursorState.left = CURSOR_RELEASED;
				gCursorState.old = 3;
				break;
			case SDL_BUTTON_MIDDLE:
				gCursorState.middle = CURSOR_RELEASED;
				break;
			case SDL_BUTTON_RIGHT:
				store_mouse_input(MOUSE_STATE_RIGHT_RELEASE, x, y);
				gCursorState.right = CURSOR_RELEASED;
				gCursorState.old = 4;
				break;
			}
			break;
		}
// Apple sends touchscreen events for trackpads, so ignore these events on macOS
#ifndef __MACOSX__
		case SDL_FINGERMOTION:
			gCursorState.x = (int)(e.tfinger.x * gScreenWidth);
			gCursorState.y = (int)(e.tfinger.y * gScreenHeight);
			break;
		case SDL_FINGERDOWN:
		{
			int x = (int)(e.tfinger.x * gScreenWidth);
			int y = (int)(e.tfinger.y * gScreenHeight);

			gCursorState.touchIsDouble = (!gCursorState.touchIsDouble
				&& e.tfinger.timestamp - gCursorState.touchDownTimestamp < TOUCH_DOUBLE_TIMEOUT);

			if (gCursorState.touchIsDouble) {
				store_mouse_input(MOUSE_STATE_RIGHT_PRESS, x, y);
				gCursorState.right = CURSOR_PRESSED;
				gCursorState.old = 2;
			} else {
				store_mouse_input(MOUSE_STATE_LEFT_PRESS, x, y);
				gCursorState.left = CURSOR_PRESSED;
				gCursorState.old = 1;
			}
			gCursorState.touch = true;
			gCursorState.touchDownTimestamp = e.tfinger.timestamp;
			break;
		}
		case SDL_FINGERUP:
		{
			int x = (int)(e.tfinger.x * gScreenWidth);
			int y = (int)(e.tfinger.y * gScreenHeight);

			if (gCursorState.touchIsDouble) {
				store_mouse_input(MOUSE_STATE_RIGHT_RELEASE, x, y);
				gCursorState.left = CURSOR_RELEASED;
				gCursorState.old = 4;
			} else {
				store_mouse_input(MOUSE_STATE_LEFT_RELEASE, x, y);
				gCursorState.left = CURSOR_RELEASED;
				gCursorState.old = 3;
			}
			gCursorState.touch = true;
			break;
		}
#endif
		case SDL_KEYDOWN:
			if (gTextInputCompositionActive) break;

			if (e.key.keysym.sym == SDLK_KP_ENTER){
				// Map Keypad enter to regular enter.
				e.key.keysym.scancode = SDL_SCANCODE_RETURN;
			}

			gLastKeyPressed = e.key.keysym.sym;
			gKeysPressed[e.key.keysym.scancode] = 1;

			// Text input
			if (gTextInput.buffer == NULL) break;

			// Clear the input on <CTRL>Backspace (Windows/Linux) or <MOD>Backspace (macOS)
			if (e.key.keysym.sym == SDLK_BACKSPACE && (e.key.keysym.mod & KEYBOARD_PRIMARY_MODIFIER)) {
				textinputbuffer_clear(&gTextInput);
				console_refresh_caret();
				window_update_textbox();
			}

			// If backspace and we have input text with a cursor position none zero
			if (e.key.keysym.sym == SDLK_BACKSPACE) {
				if (gTextInput.selection_offset > 0) {
					size_t endOffset = gTextInput.selection_offset;
					textinputbuffer_cursor_left(&gTextInput);
					gTextInput.selection_size = endOffset - gTextInput.selection_offset;
					textinputbuffer_remove_selected(&gTextInput);

					console_refresh_caret();
					window_update_textbox();
				}
			}
			if (e.key.keysym.sym == SDLK_HOME) {
				textinputbuffer_cursor_home(&gTextInput);
				console_refresh_caret();
			}
			if (e.key.keysym.sym == SDLK_END) {
				textinputbuffer_cursor_end(&gTextInput);
				console_refresh_caret();
			}
			if (e.key.keysym.sym == SDLK_DELETE) {
				size_t startOffset = gTextInput.selection_offset;
				textinputbuffer_cursor_right(&gTextInput);
				gTextInput.selection_size = gTextInput.selection_offset - startOffset;
				gTextInput.selection_offset = startOffset;
				textinputbuffer_remove_selected(&gTextInput);
				console_refresh_caret();
				window_update_textbox();
			}
			if (e.key.keysym.sym == SDLK_RETURN) {
				window_cancel_textbox();
			}
			if (e.key.keysym.sym == SDLK_LEFT) {
				textinputbuffer_cursor_left(&gTextInput);
				console_refresh_caret();
			}
			else if (e.key.keysym.sym == SDLK_RIGHT) {
				textinputbuffer_cursor_right(&gTextInput);
				console_refresh_caret();
			}
			else if (e.key.keysym.sym == SDLK_v && (SDL_GetModState() & KEYBOARD_PRIMARY_MODIFIER)) {
				if (SDL_HasClipboardText()) {
					utf8* text = SDL_GetClipboardText();

					utf8_remove_formatting(text, false);
					textinputbuffer_insert(&gTextInput, text);

					SDL_free(text);

					window_update_textbox();
				}
			}
			break;
		case SDL_MULTIGESTURE:
			if (e.mgesture.numFingers == 2) {
				if (e.mgesture.timestamp > _lastGestureTimestamp + 1000)
					_gestureRadius = 0;
				_lastGestureTimestamp = e.mgesture.timestamp;
				_gestureRadius += e.mgesture.dDist;

				// Zoom gesture
				const int tolerance = 128;
				int gesturePixels = (int)(_gestureRadius * gScreenWidth);
				if (gesturePixels > tolerance) {
					_gestureRadius = 0;
					keyboard_shortcut_handle_command(SHORTCUT_ZOOM_VIEW_IN);
				} else if (gesturePixels < -tolerance) {
					_gestureRadius = 0;
					keyboard_shortcut_handle_command(SHORTCUT_ZOOM_VIEW_OUT);
				}
			}
			break;
		case SDL_TEXTEDITING:
			// When inputting Korean characters, `e.edit.length` is always Zero.
			safe_strcpy(gTextInputComposition, e.edit.text, sizeof(gTextInputComposition));
			gTextInputCompositionStart = e.edit.start;
			gTextInputCompositionLength = e.edit.length;
			gTextInputCompositionActive = ((e.edit.length != 0 || strlen(e.edit.text) != 0) && gTextInputComposition[0] != 0);
			break;
		case SDL_TEXTINPUT:
			// will receive an `SDL_TEXTINPUT` event when a composition is committed.
			// so, set gTextInputCompositionActive to false.
			gTextInputCompositionActive = false;

			if (gTextInput.buffer == NULL) break;

			// HACK ` will close console, so don't input any text
			if (e.text.text[0] == '`' && gConsoleOpen) {
				break;
			}

			utf8* newText = e.text.text;

			utf8_remove_formatting(newText, false);
			textinputbuffer_insert(&gTextInput, newText);

			console_refresh_caret();
			window_update_textbox();
			break;
		default:
			break;
		}
	}

	gCursorState.any = gCursorState.left | gCursorState.middle | gCursorState.right;

	// Updates the state of the keys
	int numKeys = 256;
	gKeysState = SDL_GetKeyboardState(&numKeys);
}

static void platform_close_window()
{
	drawing_engine_dispose();
	cursors_dispose();
}

void platform_init()
{
	platform_create_window();
	gKeysPressed = malloc(sizeof(unsigned char) * 256);
	memset(gKeysPressed, 0, sizeof(unsigned char) * 256);

	// Set the highest palette entry to white.
	// This fixes a bug with the TT:rainbow road due to the
	// image not using the correct white palette entry.
	gPalette[255].a = 0;
	gPalette[255].r = 255;
	gPalette[255].g = 255;
	gPalette[255].b = 255;
}

static void platform_create_window()
{
	int width, height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		log_fatal("SDL_Init %s", SDL_GetError());
		exit(-1);
	}

	SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, gConfigGeneral.minimize_fullscreen_focus_loss ? "1" : "0");

	cursors_initialise();

	// TODO This should probably be called somewhere else. It has nothing to do with window creation and can be done as soon as
	// g1.dat is loaded.
	sub_68371D();

	// Get window size
	width = gConfigGeneral.window_width;
	height = gConfigGeneral.window_height;
	if (width == -1) width = 640;
	if (height == -1) height = 480;

	// Create window in window first rather than fullscreen so we have the display the window is on first
	gWindow = SDL_CreateWindow(
		"OpenRCT2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);

	if (!gWindow) {
		log_fatal("SDL_CreateWindow failed %s", SDL_GetError());
		exit(-1);
	}

	SDL_SetWindowGrab(gWindow, gConfigGeneral.trap_cursor ? SDL_TRUE : SDL_FALSE);
	SDL_SetWindowMinimumSize(gWindow, 720, 480);
	platform_init_window_icon();

	// Initialise the surface, palette and draw buffer
	platform_resize(width, height);

	platform_update_fullscreen_resolutions();
	platform_set_fullscreen_mode(gConfigGeneral.fullscreen_mode);

	// Check if steam overlay renderer is loaded into the process
	gSteamOverlayActive = platform_check_steam_overlay_attached();
	platform_trigger_resize();
}

int platform_scancode_to_rct_keycode(int sdl_key)
{
	char keycode = (char)SDL_GetKeyFromScancode((SDL_Scancode)sdl_key);

	// Until we reshufle the text files to use the new positions
	// this will suffice to move the majority to the correct positions.
	// Note any special buttons PgUp PgDwn are mapped wrong.
	if (keycode >= 'a' && keycode <= 'z')
		keycode = toupper(keycode);

	return keycode;
}

void platform_free()
{
	free(gKeysPressed);

	platform_close_window();
	SDL_Quit();

#ifdef __WINDOWS__
	platform_windows_close_console();
#endif
}

void platform_start_text_input(utf8* buffer, int max_length)
{
	// TODO This doesn't work, and position could be improved to where text entry is
	SDL_Rect rect = { 10, 10, 100, 100 };
	SDL_SetTextInputRect(&rect);

	SDL_StartTextInput();

	textinputbuffer_init(&gTextInput, buffer, max_length);
}

bool platform_is_input_active()
{
	return SDL_IsTextInputActive() && gTextInput.buffer != NULL;
}

void platform_stop_text_input()
{
	SDL_StopTextInput();
	gTextInput.buffer = NULL;
	gTextInputCompositionActive = false;
}

void platform_set_fullscreen_mode(int mode)
{
	int width, height;

	mode = _fullscreen_modes[mode];

	// HACK Changing window size when in fullscreen usually has no effect
	if (mode == SDL_WINDOW_FULLSCREEN)
		SDL_SetWindowFullscreen(gWindow, 0);

	// Set window size
	if (mode == SDL_WINDOW_FULLSCREEN) {
		platform_update_fullscreen_resolutions();
		platform_get_closest_resolution(gConfigGeneral.fullscreen_width, gConfigGeneral.fullscreen_height, &width, &height);
		SDL_SetWindowSize(gWindow, width, height);
	} else if (mode == 0) {
		SDL_SetWindowSize(gWindow, gConfigGeneral.window_width, gConfigGeneral.window_height);
	}

	if (SDL_SetWindowFullscreen(gWindow, mode)) {
		log_fatal("SDL_SetWindowFullscreen %s", SDL_GetError());
		exit(1);

		// TODO try another display mode rather than just exiting the game
	}
}

void platform_toggle_windowed_mode()
{
	int targetMode = gConfigGeneral.fullscreen_mode == 0 ? 2 : 0;
	platform_set_fullscreen_mode(targetMode);
	gConfigGeneral.fullscreen_mode = targetMode;
	config_save_default();
}

/**
 * This is not quite the same as the below function as we don't want to
 * derfererence the cursor before the function.
 *  rct2: 0x0407956
 */
void platform_set_cursor(uint8 cursor)
{
	cursors_setcurrentcursor(cursor);
}

void platform_refresh_video()
{
	int width = gScreenWidth;
	int height = gScreenHeight;

	SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, gConfigGeneral.minimize_fullscreen_focus_loss ? "1" : "0");

	drawing_engine_dispose();
	drawing_engine_init();
	drawing_engine_resize(width, height);
	drawing_engine_set_palette(gPalette);
	gfx_invalidate_screen();
}

void platform_hide_cursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}

void platform_show_cursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}

void platform_get_cursor_position(int *x, int *y)
{
	SDL_GetMouseState(x, y);
}

void platform_get_cursor_position_scaled(int *x, int *y)
{
	platform_get_cursor_position(x, y);

	// Compensate for window scaling.
	*x = (int) ceilf(*x / gConfigGeneral.window_scale);
	*y = (int) ceilf(*y / gConfigGeneral.window_scale);
}

void platform_set_cursor_position(int x, int y)
{
	SDL_WarpMouseInWindow(NULL, x, y);
}

unsigned int platform_get_ticks()
{
	return SDL_GetTicks();
}

uint8 platform_get_currency_value(const char *currCode) {
	if (currCode == NULL || strlen(currCode) < 3) {
			return CURRENCY_POUNDS;
	}

	for (int currency = 0; currency < CURRENCY_END; ++currency) {
		if (strncmp(currCode, CurrencyDescriptors[currency].isoCode, 3) == 0) {
			return currency;
		}
	}

	return CURRENCY_POUNDS;
}

void core_init()
{
	bitcount_init();
}
