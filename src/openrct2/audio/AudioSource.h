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

#pragma once

#include "../common.h"
#include "AudioFormat.h"
#include "AudioMixer.h"

/**
 * Represents a readable source of audio PCM data.
 */
interface IAudioSource
{
    virtual ~IAudioSource() = default;

    virtual uint64 GetLength() abstract;
    virtual AudioFormat GetFormat() abstract;
    virtual size_t Read(void * dst, uint64 offset, size_t len) abstract;
};

namespace AudioSource
{
    IAudioSource * CreateNull();
    IAudioSource * CreateMemoryFromCSS1(const utf8 * path, size_t index, const AudioFormat * targetFormat = nullptr);
    IAudioSource * CreateMemoryFromWAV(const utf8 * path, const AudioFormat * targetFormat = nullptr);
    IAudioSource * CreateStreamFromWAV(SDL_RWops * rw);
}
