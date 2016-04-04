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

#include <time.h>
#include "../addresses.h"
#include "../config.h"
#include "../game.h"
#include "../editor.h"
#include "../interface/widget.h"
#include "../interface/window.h"
#include "../localisation/localisation.h"
#include "../network/network.h"
#include "../scenario.h"
#include "../title.h"
#include "../windows/error.h"
#include "../interface/themes.h"
#include "../interface/title_sequences.h"
#include "../util/util.h"

#pragma region Widgets

#define WW 340
#define WH 400

enum {
	WIDX_BACKGROUND,
	WIDX_TITLE,
	WIDX_CLOSE,
	WIDX_UP,
	WIDX_NEW,
	WIDX_SORT_NAME,
	WIDX_SORT_DATE,
	WIDX_SCROLL,
	WIDX_BROWSE,
};

// 0x9DE48C
static rct_widget window_loadsave_widgets[] = {
	{ WWT_FRAME,		0,		0,					WW - 1,			0,			WH - 1,		STR_NONE,			STR_NONE },
	{ WWT_CAPTION,		0,		1,					WW - 2,			1,			14,			STR_NONE,			STR_WINDOW_TITLE_TIP },
	{ WWT_CLOSEBOX,		0,		WW - 13,			WW - 3,			2,			13,			STR_CLOSE_X,		STR_CLOSE_WINDOW_TIP }, //Window close button
	{ WWT_CLOSEBOX,		0,		4,					104,			36,			47,			2718,				STR_NONE},	// Up
	{ WWT_CLOSEBOX,		0,		105,				205,			36,			47,			2719,				STR_NONE},	// New
	{ WWT_CLOSEBOX,		0,		4,					(WW - 5) / 2,	50,			61,			STR_NONE,			STR_NONE },	// Name
	{ WWT_CLOSEBOX,		0,		(WW - 5) / 2 + 1,	WW - 5 - 1,		50,			61,			STR_NONE,			STR_NONE },	// Date
	{ WWT_SCROLL,		0,		4,					WW - 5,			61,			WH - 40,	2,					STR_NONE },	// File list
	{ WWT_CLOSEBOX,		0,		4,					200,			WH - 36,	WH - 18,	2707,				STR_NONE }, // Use native browser
	{ WIDGETS_END }
};

#pragma endregion

#pragma region Events

static void window_loadsave_close(rct_window *w);
static void window_loadsave_mouseup(rct_window *w, int widgetIndex);
static void window_loadsave_scrollgetsize(rct_window *w, int scrollIndex, int *width, int *height);
static void window_loadsave_scrollmousedown(rct_window *w, int scrollIndex, int x, int y);
static void window_loadsave_scrollmouseover(rct_window *w, int scrollIndex, int x, int y);
static void window_loadsave_textinput(rct_window *w, int widgetIndex, char *text);
static void window_loadsave_tooltip(rct_window* w, int widgetIndex, rct_string_id *stringId);
static void window_loadsave_invalidate(rct_window *w);
static void window_loadsave_paint(rct_window *w, rct_drawpixelinfo *dpi);
static void window_loadsave_scrollpaint(rct_window *w, rct_drawpixelinfo *dpi, int scrollIndex);

static rct_window_event_list window_loadsave_events = {
	window_loadsave_close,
	window_loadsave_mouseup,
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
	window_loadsave_scrollgetsize,
	window_loadsave_scrollmousedown,
	NULL,
	window_loadsave_scrollmouseover,
	window_loadsave_textinput,
	NULL,
	NULL,
	window_loadsave_tooltip,
	NULL,
	NULL,
	window_loadsave_invalidate,
	window_loadsave_paint,
	window_loadsave_scrollpaint
};

#pragma endregion

enum {
	TYPE_DIRECTORY,
	TYPE_FILE,
};

typedef struct {
	char name[256];
	char path[MAX_PATH];
	time_t date_modified;
	uint8 type;
} loadsave_list_item;

modal_callback gLoadSaveCallback;

int _listItemsCount = 0;
loadsave_list_item *_listItems = NULL;
char _directory[MAX_PATH];
char _shortenedDirectory[MAX_PATH];
static char _parentDirectory[MAX_PATH];
char _extension[32];
char _defaultName[MAX_PATH];
int _loadsaveType;
int _type;

static void window_loadsave_populate_list(rct_window *w, int includeNewItem, const char *directory, const char *extension);
static void window_loadsave_select(rct_window *w, const char *path);
static void window_loadsave_sort_list(int index, int endIndex);

static int has_extension(char *path, char *extension);

static rct_window *window_overwrite_prompt_open(const char *name, const char *path);

rct_window *window_loadsave_open(int type, char *defaultName)
{
	gLoadSaveCallback = NULL;
	gLoadSaveTitleSequenceSave = false;
	char path[MAX_PATH], *ch;
	int includeNewItem;
	rct_window* w;
	_type = type;
	_defaultName[0] = '\0';

	if (!str_is_null_or_empty(defaultName)) {
		safe_strcpy(_defaultName, defaultName, sizeof(_defaultName));
	}

	w = window_bring_to_front_by_class(WC_LOADSAVE);
	if (w == NULL) {
		w = window_create_centred(WW, WH, &window_loadsave_events, WC_LOADSAVE, WF_STICK_TO_FRONT);
		w->widgets = window_loadsave_widgets;
		w->enabled_widgets = (1 << WIDX_CLOSE) | (1 << WIDX_UP) | (1 << WIDX_NEW) | (1 << WIDX_SORT_NAME) | (1 << WIDX_SORT_DATE) | (1 << WIDX_BROWSE);
		w->colours[0] = 7;
		w->colours[1] = 7;
		w->colours[2] = 7;
	}

	_loadsaveType = type;
	switch (type & 0x0F) {
	case (LOADSAVETYPE_LOAD | LOADSAVETYPE_GAME):
		w->widgets[WIDX_TITLE].image = STR_FILE_DIALOG_TITLE_LOAD_GAME;
		break;
	case (LOADSAVETYPE_SAVE | LOADSAVETYPE_GAME) :
		w->widgets[WIDX_TITLE].image = STR_FILE_DIALOG_TITLE_SAVE_GAME;
		break;
	case (LOADSAVETYPE_LOAD | LOADSAVETYPE_LANDSCAPE) :
		w->widgets[WIDX_TITLE].image = STR_FILE_DIALOG_TITLE_LOAD_LANDSCAPE;
		break;
	case (LOADSAVETYPE_SAVE | LOADSAVETYPE_LANDSCAPE) :
		w->widgets[WIDX_TITLE].image = STR_FILE_DIALOG_TITLE_SAVE_LANDSCAPE;
		break;
	case (LOADSAVETYPE_SAVE | LOADSAVETYPE_SCENARIO) :
		w->widgets[WIDX_TITLE].image = STR_FILE_DIALOG_TITLE_SAVE_SCENARIO;
		break;
	case (LOADSAVETYPE_LOAD | LOADSAVETYPE_TRACK) :
		w->widgets[WIDX_TITLE].image = STR_FILE_DIALOG_TITLE_INSTALL_NEW_TRACK_DESIGN;
		break;
	default:
		log_error("Unsupported load / save type: %d", type & 0x0F);
		return NULL;
	}

	w->no_list_items = 0;
	w->selected_list_item = -1;

	includeNewItem = (type & 0x01) == LOADSAVETYPE_SAVE;
	switch (type & 0x0E) {
	case LOADSAVETYPE_GAME:
		platform_get_user_directory(path, "save");
		if (!platform_ensure_directory_exists(path)) {
			log_error("Unable to create save directory.");
			window_close(w);
			return NULL;
		}

		window_loadsave_populate_list(w, includeNewItem, path, ".sv6");
		break;
	case LOADSAVETYPE_LANDSCAPE:
		platform_get_user_directory(path, "landscape");
		if (!platform_ensure_directory_exists(path)) {
			log_error("Unable to create landscapes directory.");
			window_close(w);
			return NULL;
		}

		window_loadsave_populate_list(w, includeNewItem, path, ".sc6");
		break;
	case LOADSAVETYPE_SCENARIO:
		platform_get_user_directory(path, "scenario");
		if (!platform_ensure_directory_exists(path)) {
			log_error("Unable to create scenarios directory.");
			window_close(w);
			return NULL;
		}

		window_loadsave_populate_list(w, includeNewItem, path, ".sc6");
		break;
	case LOADSAVETYPE_TRACK:
		/*
		Uncomment when user tracks are separated

		platform_get_user_directory(path, "tracks");
		if (!platform_ensure_directory_exists(path)) {
		log_error("Unable to create tracks directory.");
		window_close(w);
		return NULL;
		}
		*/

		safe_strcpy(path, RCT2_ADDRESS(RCT2_ADDRESS_TRACKS_PATH, char), MAX_PATH);
		ch = strchr(path, '*');
		if (ch != NULL)
			*ch = 0;

		window_loadsave_populate_list(w, includeNewItem, path, ".td?");
		break;
	}
	w->no_list_items = _listItemsCount;
	window_init_scroll_widgets(w);
	return w;
}

static void window_loadsave_close(rct_window *w)
{
	if (_listItems != NULL) {
		free(_listItems);
		_listItems = NULL;
	}

	window_close_by_class(WC_LOADSAVE_OVERWRITE_PROMPT);
}

static void window_loadsave_mouseup(rct_window *w, int widgetIndex)
{
	int result = 0;
	char path[MAX_PATH], filter[MAX_PATH];

	switch (widgetIndex){
	case WIDX_CLOSE:
		window_close(w);
		break;
	case WIDX_UP:
	{
		char directory[MAX_PATH];
		int includeNewItem = (_type & 1) == LOADSAVETYPE_SAVE;
		
		safe_strcpy(directory, _parentDirectory, sizeof(directory));
		window_loadsave_populate_list(w, includeNewItem, directory, _extension);
		window_init_scroll_widgets(w);
		w->no_list_items = _listItemsCount;
		break;
	}
	case WIDX_NEW:
	{		
		rct_string_id templateStringId = 3165;
		char *templateString;
		
		templateString = (char *)language_get_string(templateStringId);
		strcpy(templateString, _defaultName);
		window_text_input_open(w, WIDX_NEW, STR_NONE, 2710, templateStringId, 0, 64);
		break;
	}
	case WIDX_BROWSE:
		safe_strcpy(path, _directory, MAX_PATH);
		if (_type & LOADSAVETYPE_SAVE) {
			strcat(path, _defaultName);
		}

		memset(filter, '\0', MAX_PATH);
		safe_strcpy(filter, "*", MAX_PATH);
		strncat(filter, _extension, MAX_PATH - strnlen(filter, MAX_PATH) - 1);

		file_dialog_desc desc;
		memset(&desc, 0, sizeof(desc));
		desc.initial_directory = _directory;
		if (_type & LOADSAVETYPE_SAVE) {
			desc.default_filename = path;
		}

		switch (_type) {
		case (LOADSAVETYPE_LOAD | LOADSAVETYPE_GAME) :
			desc.type = FD_OPEN;
			desc.title = language_get_string(STR_FILE_DIALOG_TITLE_LOAD_GAME);
			desc.filters[0].name = language_get_string(STR_OPENRCT2_SAVED_GAME);
			desc.filters[0].pattern = "*.sv4;*.sv6";
			break;
		case (LOADSAVETYPE_SAVE | LOADSAVETYPE_GAME) :
			desc.type = FD_SAVE;
			desc.title = language_get_string(STR_FILE_DIALOG_TITLE_SAVE_GAME);
			desc.filters[0].name = language_get_string(STR_OPENRCT2_SAVED_GAME);
			desc.filters[0].pattern = "*.sv6";
			break;
		case (LOADSAVETYPE_LOAD | LOADSAVETYPE_LANDSCAPE) :
			desc.type = FD_OPEN;
			desc.title = language_get_string(STR_FILE_DIALOG_TITLE_LOAD_LANDSCAPE);
			desc.filters[0].name = language_get_string(STR_OPENRCT2_LANDSCAPE_FILE);
			desc.filters[0].pattern = "*.sc4;*.sv4;*.sc6;*.sv6";
			break;
		case (LOADSAVETYPE_SAVE | LOADSAVETYPE_LANDSCAPE) :
			desc.type = FD_SAVE;
			desc.title = language_get_string(STR_FILE_DIALOG_TITLE_SAVE_LANDSCAPE);
			desc.filters[0].name = language_get_string(STR_OPENRCT2_LANDSCAPE_FILE);
			desc.filters[0].pattern = "*.sc6";
			break;
		case (LOADSAVETYPE_SAVE | LOADSAVETYPE_SCENARIO) :
			desc.type = FD_SAVE;
			desc.title = language_get_string(STR_FILE_DIALOG_TITLE_SAVE_SCENARIO);
			desc.filters[0].name = language_get_string(STR_OPENRCT2_SCENARIO_FILE);
			desc.filters[0].pattern = "*.sc6";
			break;
		case (LOADSAVETYPE_LOAD | LOADSAVETYPE_TRACK) :
			desc.type = FD_OPEN;
			desc.title = language_get_string(STR_FILE_DIALOG_TITLE_INSTALL_NEW_TRACK_DESIGN);
			desc.filters[0].name = language_get_string(STR_OPENRCT2_TRACK_DESIGN_FILE);
			desc.filters[0].pattern = "*.td4;*.td6";
			break;
		}

		result = platform_open_common_file_dialog(path, &desc);
		if (result) {
			window_loadsave_select(w, path);
		}
		break;
	case WIDX_SORT_NAME:
		if (gConfigGeneral.load_save_sort == SORT_NAME_ASCENDING){
			gConfigGeneral.load_save_sort = SORT_NAME_DESCENDING;
		} else {
			gConfigGeneral.load_save_sort = SORT_NAME_ASCENDING;
		}
		config_save_default();
		window_loadsave_sort_list(0, _listItemsCount - 1);
		window_invalidate(w);
		break;
	case WIDX_SORT_DATE:
		if (gConfigGeneral.load_save_sort == SORT_DATE_DESCENDING){
			gConfigGeneral.load_save_sort = SORT_DATE_ASCENDING;
		} else {
			gConfigGeneral.load_save_sort = SORT_DATE_DESCENDING;
		}
		config_save_default();
		window_loadsave_sort_list(0, _listItemsCount - 1);
		window_invalidate(w);
		break;
	}
}

static int has_extension(char *path, char *extension)
{
	int extensionLength = strlen(extension);
	int pathLength = strlen(path);
	for (int u = 0; u < extensionLength; u++) {
		if (tolower(path[pathLength - extensionLength + u]) != tolower(extension[u]))
			return 0;
	}
	return 1;
}

static void window_loadsave_scrollgetsize(rct_window *w, int scrollIndex, int *width, int *height)
{
	*height = w->no_list_items * 10;
}

static void window_loadsave_scrollmousedown(rct_window *w, int scrollIndex, int x, int y)
{
	int selectedItem;

	selectedItem = y / 10;
	if (selectedItem >= w->no_list_items)
		return;
	if (_listItems[selectedItem].type == TYPE_DIRECTORY){
		// The selected item is a folder
		int includeNewItem;

		w->no_list_items = 0;
		w->selected_list_item = -1;
		includeNewItem = (_type & 1) == LOADSAVETYPE_SAVE;

		char directory[MAX_PATH];
		safe_strcpy(directory, _listItems[selectedItem].path, sizeof(directory));

		window_loadsave_populate_list(w, includeNewItem, directory, _extension);
		window_init_scroll_widgets(w);

		w->no_list_items = _listItemsCount;
	} else {
		// TYPE_FILE
		// Load or overwrite
		if ((_loadsaveType & 0x01) == LOADSAVETYPE_SAVE)
			window_overwrite_prompt_open(_listItems[selectedItem].name, _listItems[selectedItem].path);
		else
			window_loadsave_select(w, _listItems[selectedItem].path);
	}
}

static void window_loadsave_scrollmouseover(rct_window *w, int scrollIndex, int x, int y)
{
	int selectedItem;

	selectedItem = y / 10;
	if (selectedItem >= w->no_list_items)
		return;

	w->selected_list_item = selectedItem;

	window_invalidate(w);
}

static void window_loadsave_textinput(rct_window *w, int widgetIndex, char *text)
{
	char path[MAX_PATH];
	int i, overwrite;

	if (text == NULL || text[0] == 0)
		return;

	if (gLoadSaveTitleSequenceSave) {
		if (filename_valid_characters(text)) {
			if (!title_sequence_save_exists(gCurrentTitleSequence, text)) {
				title_sequence_add_save(gCurrentTitleSequence, path, text);
			}
			else {
				window_error_open(5404, STR_NONE);
			}
		}
		else {
			window_error_open(5243, STR_NONE);
		}
		return;
	}

	safe_strcpy(path, _directory, sizeof(path));
	strncat(path, text, sizeof(path) - strnlen(path, MAX_PATH) - 1);
	strncat(path, _extension, sizeof(path) - strnlen(path, MAX_PATH) - 1);

	overwrite = 0;
	for (i = 0; i < _listItemsCount; i++) {
		if (_stricmp(_listItems[i].path, path) == 0) {
			overwrite = 1;
			break;
		}
	}

	if (overwrite)
		window_overwrite_prompt_open(text, path);
	else
		window_loadsave_select(w, path);
}

static void window_loadsave_tooltip(rct_window* w, int widgetIndex, rct_string_id *stringId)
{
	RCT2_GLOBAL(RCT2_ADDRESS_COMMON_FORMAT_ARGS, uint16) = STR_LIST;
}

static void window_loadsave_invalidate(rct_window *w)
{
	colour_scheme_update(w);
}

static void window_loadsave_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	window_draw_widgets(w, dpi);

	if (_shortenedDirectory[0] == '\0') {
		shorten_path(_shortenedDirectory, sizeof(_shortenedDirectory), _directory, w->width - 8);
	}

	utf8 buffer[256];

	// Format text
	utf8 *ch = buffer;
	ch = utf8_write_codepoint(ch, FORMAT_MEDIUMFONT);
	ch = utf8_write_codepoint(ch, FORMAT_BLACK);
	safe_strcpy(ch, _shortenedDirectory, sizeof(buffer) - (ch - buffer));

	// Draw shadow
	gfx_draw_string(dpi, buffer, 0, w->x + 4, w->y + 20);
	rct_string_id id = STR_NONE;
	// Name button text
	if (gConfigGeneral.load_save_sort == SORT_NAME_ASCENDING)
		id = STR_UP;
	else if (gConfigGeneral.load_save_sort == SORT_NAME_DESCENDING)
		id = STR_DOWN;
	gfx_draw_string_centred_clipped(dpi, STR_NAME, &id, 1, w->x + 4 + (w->width - 8) / 4, w->y + 50, (w->width - 8) / 2);
	// Date button text
	if (gConfigGeneral.load_save_sort == SORT_DATE_ASCENDING)
		id = STR_UP;
	else if (gConfigGeneral.load_save_sort == SORT_DATE_DESCENDING)
		id = STR_DOWN;
	else
		id = STR_NONE;
	gfx_draw_string_centred_clipped(dpi, STR_DATE, &id, 1, w->x + 4 + (w->width - 8) * 3 / 4, w->y + 50, (w->width - 8) / 2);
}

static void window_loadsave_scrollpaint(rct_window *w, rct_drawpixelinfo *dpi, int scrollIndex)
{
	int i, y;
	rct_string_id stringId, templateStringId = 3165;
	char *templateString;

	gfx_fill_rect(dpi, dpi->x, dpi->y, dpi->x + dpi->width - 1, dpi->y + dpi->height - 1, ColourMapA[w->colours[1]].mid_light);

	templateString = (char*)language_get_string(templateStringId);
	for (i = 0; i < w->no_list_items; i++) {
		y = i * 10;
		if (y > dpi->y + dpi->height)
			break;

		if (y + 10 < dpi->y)
			continue;

		stringId = STR_BLACK_STRING;
		if (i == w->selected_list_item) {
			stringId = STR_WINDOW_COLOUR_2_STRING;
			gfx_fill_rect(dpi, 0, y, 800, y + 9, 0x2000031);
		}

		strcpy(templateString, _listItems[i].name);
		gfx_draw_string_left(dpi, stringId, &templateStringId, 0, 0, y - 1);
	}
}

static int list_item_sort(const void *a, const void *b)
{
	const loadsave_list_item *itemA = (loadsave_list_item*)a;
	const loadsave_list_item *itemB = (loadsave_list_item*)b;

	if (itemA->type != itemB->type)
		return itemA->type - itemB->type;

	switch (gConfigGeneral.load_save_sort){
	case SORT_NAME_ASCENDING:
		return strcicmp(itemA->name, itemB->name);
	case SORT_NAME_DESCENDING:
		return -strcicmp(itemA->name, itemB->name);
	case SORT_DATE_DESCENDING:
		return (int) -difftime(itemA->date_modified, itemB->date_modified);
	case SORT_DATE_ASCENDING:
		return (int) difftime(itemA->date_modified, itemB->date_modified);
	default:
		return strcicmp(itemA->name, itemB->name);
	}
}

static void window_loadsave_sort_list(int index, int endIndex)
{
	int count = endIndex - index + 1;
	if (count < 0)
		return;

	qsort(_listItems + index, count, sizeof(loadsave_list_item), list_item_sort);
}

static void window_loadsave_populate_list(rct_window *w, int includeNewItem, const char *directory, const char *extension)
{
	int i;
	int sortStartIndex = 0;
	int listItemCapacity = 8;
	loadsave_list_item *listItem;
	char filter[MAX_PATH];
	
	safe_strcpy(_directory, directory, sizeof(_directory));
	if (_extension != extension) {
		safe_strcpy(_extension, extension, sizeof(_extension));
		_extension[sizeof(_extension) - 1] = '\0';
	}
	_shortenedDirectory[0] = '\0';

	safe_strcpy(filter, directory, sizeof(filter));
	strncat(filter, "*", sizeof(filter) - strnlen(filter, MAX_PATH) - 1);
	strncat(filter, extension, sizeof(filter) - strnlen(filter, MAX_PATH) - 1);

	if (_listItems != NULL)
		free(_listItems);
	_listItems = (loadsave_list_item*)malloc(listItemCapacity * sizeof(loadsave_list_item));
	_listItemsCount = 0;
	
	window_loadsave_widgets[WIDX_NEW].type = includeNewItem?WWT_CLOSEBOX:WWT_EMPTY; // Hide/Show "new" button
	if(directory[0]=='\0' && platform_get_drives()!=0) // List Windows drives
	{
		w->disabled_widgets |= (1<<WIDX_NEW) | (1<<WIDX_UP);
		for (int x = 0; x < 32; x++){
			if (listItemCapacity <= _listItemsCount) {
				listItemCapacity *= 2;
				_listItems = realloc(_listItems, listItemCapacity * sizeof(loadsave_list_item));
			}

			if (platform_get_drives() & (1 << (x))){
				listItem = &_listItems[_listItemsCount];
				memset(listItem->path, '\0', MAX_PATH);
				listItem->path[0] = 'A' + x;
				listItem->path[1] = ':';
				listItem->path[2] = platform_get_path_separator();
				strcpy(listItem->name, listItem->path);
				listItem->type = TYPE_DIRECTORY;
				_listItemsCount++;
			}
		}
	}
	else
	{
		//Get parent directory
		int directoryLength = strlen(directory);
		char separator = platform_get_path_separator();
		for(i = directoryLength-2; i>=0; i--)
		{
			if(directory[i]==separator)
				break;
		}
		safe_strcpy(_parentDirectory, directory, sizeof(_parentDirectory));
		_parentDirectory[i+1] = '\0';
		if(_parentDirectory[0]=='\0' && platform_get_drives()==0)
			w->disabled_widgets |= (1<<WIDX_UP);
		else
			w->disabled_widgets &= ~(1<<WIDX_UP);
		w->disabled_widgets &= ~(1<<WIDX_NEW);
		file_info fileInfo;
		int fileEnumHandle;
		const char *src;
		char *dst;
		char *last_dot_in_filename;
		char subDir[MAX_PATH];
		
		fileEnumHandle = platform_enumerate_directories_begin(directory);
		while (platform_enumerate_directories_next(fileEnumHandle, subDir)){
			if (listItemCapacity <= _listItemsCount) {
				listItemCapacity *= 2;
				_listItems = realloc(_listItems, listItemCapacity * sizeof(loadsave_list_item));
			}

			listItem = &_listItems[_listItemsCount];
			memset(listItem->path, '\0', MAX_PATH);
			safe_strcpy(listItem->path, directory, MAX_PATH);
			strncat(listItem->path, subDir, MAX_PATH - strnlen(listItem->path, MAX_PATH) - 1);
			safe_strcpy(listItem->name, subDir, sizeof(listItem->name));
			listItem->type = TYPE_DIRECTORY;
			_listItemsCount++;
		}
		platform_enumerate_files_end(fileEnumHandle);

		fileEnumHandle = platform_enumerate_files_begin(filter);
		while (platform_enumerate_files_next(fileEnumHandle, &fileInfo)) {
			if (listItemCapacity <= _listItemsCount) {
				listItemCapacity *= 2;
				_listItems = realloc(_listItems, listItemCapacity * sizeof(loadsave_list_item));
			}

			listItem = &_listItems[_listItemsCount];
			safe_strcpy(listItem->path, directory, sizeof(listItem->path));
			strncat(listItem->path, fileInfo.path, sizeof(listItem->path) - strnlen(listItem->path, MAX_PATH) - 1);
			listItem->type = TYPE_FILE;
			listItem->date_modified = platform_file_get_modified_time(listItem->path);

			src = fileInfo.path;
			dst = listItem->name;
			last_dot_in_filename = strrchr(fileInfo.path, '.');
			assert(last_dot_in_filename != NULL);
			i = 0;
			while (src < last_dot_in_filename && i < sizeof(listItem->name) - 1) {
				*dst++ = *src++;
				i++;
			}
			*dst = '\0';

			_listItemsCount++;
		}
		platform_enumerate_files_end(fileEnumHandle);
		window_loadsave_sort_list(sortStartIndex, _listItemsCount - 1);
	}
}

static void window_loadsave_invoke_callback(int result)
{
	if (gLoadSaveCallback != NULL) {
		gLoadSaveCallback(result);
	}
}

static void window_loadsave_select(rct_window *w, const char *path)
{
	SDL_RWops* rw;
	switch (_loadsaveType & 0x0F) {
	case (LOADSAVETYPE_LOAD | LOADSAVETYPE_GAME) :
		if (gLoadSaveTitleSequenceSave) {
			utf8 newName[MAX_PATH];
			char *extension = (char*)path_get_extension(path);
			safe_strcpy(newName, path_get_filename(path), MAX_PATH);
			if (_stricmp(extension, ".sv6") != 0 && _stricmp(extension, ".sc6") != 0)
				strcat(newName, ".sv6");
			if (title_sequence_save_exists(gCurrentTitleSequence, newName)) {
				RCT2_GLOBAL(RCT2_ADDRESS_COMMON_FORMAT_ARGS + 0, uint32) = (uint32)&_listItems[w->selected_list_item].name;
				window_text_input_open(w, WIDX_SCROLL, 5435, 5404, 1170, (uint32)_listItems[w->selected_list_item].name, TITLE_SEQUENCE_MAX_SAVE_LENGTH - 1);
			}
			else {
				title_sequence_add_save(gCurrentTitleSequence, path, newName);
				window_close(w);
			}
			window_loadsave_invoke_callback(MODAL_RESULT_OK);
		} else if (game_load_save(path)) {
			safe_strcpy(gScenarioSavePath, path, MAX_PATH);
			gFirstTimeSave = 0;

			window_close(w);
			gfx_invalidate_screen();
			window_loadsave_invoke_callback(MODAL_RESULT_OK);
		} else {
			// 1050, not the best message...
			window_error_open(STR_LOAD_GAME, 1050);
			window_loadsave_invoke_callback(MODAL_RESULT_FAIL);
		}
		break;
	case (LOADSAVETYPE_SAVE | LOADSAVETYPE_GAME) :
		rw = SDL_RWFromFile(path, "wb+");
		if (rw != NULL) {
			int success = scenario_save(rw, gConfigGeneral.save_plugin_data ? 1 : 0);
			SDL_RWclose(rw);
			if (success) {
				safe_strcpy(gScenarioSavePath, path, MAX_PATH);
				gFirstTimeSave = 0;

				window_close_by_class(WC_LOADSAVE);
				gfx_invalidate_screen();

				window_loadsave_invoke_callback(MODAL_RESULT_OK);
			} else {
				window_error_open(STR_SAVE_GAME, 1047);
				window_loadsave_invoke_callback(MODAL_RESULT_FAIL);
			}
		} else {
			window_error_open(STR_SAVE_GAME, 1047);
			window_loadsave_invoke_callback(MODAL_RESULT_FAIL);
		}
		break;
	case (LOADSAVETYPE_LOAD | LOADSAVETYPE_LANDSCAPE) :
		if (editor_load_landscape(path)) {
			gfx_invalidate_screen();
			window_loadsave_invoke_callback(MODAL_RESULT_OK);
		} else {
			// 1050, not the best message...
			window_error_open(STR_LOAD_LANDSCAPE, 1050);
			window_loadsave_invoke_callback(MODAL_RESULT_FAIL);
		}
		break;
	case (LOADSAVETYPE_SAVE | LOADSAVETYPE_LANDSCAPE) :
		rw = SDL_RWFromFile(path, "wb+");
		if (rw != NULL) {
			scenario_set_filename(path);
			int success = scenario_save(rw, gConfigGeneral.save_plugin_data ? 3 : 2);
			SDL_RWclose(rw);
			if (success) {
				window_close_by_class(WC_LOADSAVE);
				gfx_invalidate_screen();
				window_loadsave_invoke_callback(MODAL_RESULT_OK);
			} else {
				window_error_open(STR_SAVE_LANDSCAPE, 1049);
				window_loadsave_invoke_callback(MODAL_RESULT_FAIL);
			}
		} else {
			window_error_open(STR_SAVE_LANDSCAPE, 1049);
			window_loadsave_invoke_callback(MODAL_RESULT_FAIL);
		}
		break;
	case (LOADSAVETYPE_SAVE | LOADSAVETYPE_SCENARIO) :
	{
		rct_s6_info *s6Info = (rct_s6_info*)0x0141F570;
		int parkFlagsBackup = RCT2_GLOBAL(RCT2_ADDRESS_PARK_FLAGS, uint32);
		RCT2_GLOBAL(RCT2_ADDRESS_PARK_FLAGS, uint32) &= ~PARK_FLAGS_18;
		s6Info->editor_step = 255;
		rw = SDL_RWFromFile(path, "wb+");
		int success = 0;
		if (rw != NULL) {
			scenario_set_filename(path);
			success = scenario_save(rw, gConfigGeneral.save_plugin_data ? 3 : 2);
			SDL_RWclose(rw);
		}
		RCT2_GLOBAL(RCT2_ADDRESS_PARK_FLAGS, uint32) = parkFlagsBackup;

		if (success) {
			window_close_by_class(WC_LOADSAVE);
			window_loadsave_invoke_callback(MODAL_RESULT_OK);
			title_load();
		} else {
			window_error_open(STR_FILE_DIALOG_TITLE_SAVE_SCENARIO, STR_SCENARIO_SAVE_FAILED);
			s6Info->editor_step = EDITOR_STEP_OBJECTIVE_SELECTION;
			window_loadsave_invoke_callback(MODAL_RESULT_FAIL);
		}
		break;
	}
	case (LOADSAVETYPE_LOAD | LOADSAVETYPE_TRACK) :
		window_install_track_open(path);
		window_close_by_class(WC_LOADSAVE);
		window_loadsave_invoke_callback(MODAL_RESULT_OK);
		break;
	}
}

#pragma region Overwrite prompt

#define OVERWRITE_WW 200
#define OVERWRITE_WH 100

enum {
	WIDX_OVERWRITE_BACKGROUND,
	WIDX_OVERWRITE_TITLE,
	WIDX_OVERWRITE_CLOSE,
	WIDX_OVERWRITE_OVERWRITE,
	WIDX_OVERWRITE_CANCEL
};

static rct_widget window_overwrite_prompt_widgets[] = {
	{ WWT_FRAME,			0, 0,					OVERWRITE_WW - 1,	0,					OVERWRITE_WH - 1,	STR_NONE,				STR_NONE },
	{ WWT_CAPTION,			0, 1,					OVERWRITE_WW - 2,	1,					14,					2709,					STR_WINDOW_TITLE_TIP },
	{ WWT_CLOSEBOX,			0, OVERWRITE_WW - 13,	OVERWRITE_WW - 3,	2,					13,					STR_CLOSE_X,			STR_CLOSE_WINDOW_TIP },
	{ WWT_DROPDOWN_BUTTON,	0, 10,					94,					OVERWRITE_WH - 20,	OVERWRITE_WH - 9,	2709,					STR_NONE },
	{ WWT_DROPDOWN_BUTTON,	0, OVERWRITE_WW - 95,	OVERWRITE_WW - 11,	OVERWRITE_WH - 20,	OVERWRITE_WH - 9,	STR_SAVE_PROMPT_CANCEL, STR_NONE },
	{ WIDGETS_END }
};

static void window_overwrite_prompt_mouseup(rct_window *w, int widgetIndex);
static void window_overwrite_prompt_invalidate(rct_window *w);
static void window_overwrite_prompt_paint(rct_window *w, rct_drawpixelinfo *dpi);

static rct_window_event_list window_overwrite_prompt_events = {
	NULL,
	window_overwrite_prompt_mouseup,
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
	window_overwrite_prompt_invalidate,
	window_overwrite_prompt_paint,
	NULL
};

static char _window_overwrite_prompt_name[256];
static char _window_overwrite_prompt_path[MAX_PATH];

static rct_window *window_overwrite_prompt_open(const char *name, const char *path)
{
	rct_window *w;

	window_close_by_class(WC_LOADSAVE_OVERWRITE_PROMPT);

	w = window_create_centred(OVERWRITE_WW, OVERWRITE_WH, &window_overwrite_prompt_events, WC_LOADSAVE_OVERWRITE_PROMPT, WF_STICK_TO_FRONT);
	w->widgets = window_overwrite_prompt_widgets;
	w->enabled_widgets = (1 << WIDX_CLOSE) | (1 << WIDX_OVERWRITE_CANCEL) | (1 << WIDX_OVERWRITE_OVERWRITE);
	window_init_scroll_widgets(w);
	w->flags |= WF_TRANSPARENT;
	w->colours[0] = 154;

	safe_strcpy(_window_overwrite_prompt_name, name, sizeof(_window_overwrite_prompt_name));
	safe_strcpy(_window_overwrite_prompt_path, path, sizeof(_window_overwrite_prompt_path));

	return w;
}

static void window_overwrite_prompt_mouseup(rct_window *w, int widgetIndex)
{
	rct_window *loadsaveWindow;

	switch (widgetIndex) {
	case WIDX_OVERWRITE_OVERWRITE:
		loadsaveWindow = window_find_by_class(WC_LOADSAVE);
		if (loadsaveWindow != NULL)
			window_loadsave_select(loadsaveWindow, _window_overwrite_prompt_path);
		// As the window_loadsave_select function can change the order of the
		// windows we can't use window_close(w).
		window_close_by_class(WC_LOADSAVE_OVERWRITE_PROMPT);
		break;
	case WIDX_OVERWRITE_CANCEL:
	case WIDX_OVERWRITE_CLOSE:
		window_close(w);
		break;
	}
}

static void window_overwrite_prompt_invalidate(rct_window *w)
{
	colour_scheme_update(w);
}

static void window_overwrite_prompt_paint(rct_window *w, rct_drawpixelinfo *dpi)
{
	window_draw_widgets(w, dpi);

	rct_string_id templateStringId = 3165;
	char *templateString;

	templateString = (char*)language_get_string(templateStringId);
	strcpy(templateString, _window_overwrite_prompt_name);

	int x = w->x + w->width / 2;
	int y = w->y + (w->height / 2) - 3;
	gfx_draw_string_centred_wrapped(dpi, &templateStringId, x, y, w->width - 4, 2708, 0);
}


#pragma endregion
