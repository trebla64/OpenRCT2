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

#ifndef _INTERFACE_KEYBOARD_SHORTCUT_H_
#define _INTERFACE_KEYBOARD_SHORTCUT_H_

#include "../common.h"

#define SHORTCUT_UNDEFINED 0xFFFF

/** The current shortcut being changed. */
extern uint8 gKeyboardShortcutChangeId;

void keyboard_shortcut_set(sint32 key);
void keyboard_shortcut_handle(sint32 key);
void keyboard_shortcut_handle_command(sint32 shortcutIndex);
void keyboard_shortcut_format_string(char *buffer, size_t size, uint16 shortcutKey);

#endif
