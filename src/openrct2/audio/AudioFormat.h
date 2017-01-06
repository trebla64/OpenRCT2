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
#include <SDL.h>

/**
 * Represents the size, frequency and number of channels for
 * an audio stream or buffer.
 */
struct AudioFormat
{
    int             freq;
    SDL_AudioFormat format;
    int             channels;

    int BytesPerSample() const
    {
        return (SDL_AUDIO_BITSIZE(format)) / 8;
    }

    int GetByteRate() const
    {
        return BytesPerSample() * channels;
    }
};

inline bool operator ==(const AudioFormat& lhs, const AudioFormat& rhs)
{
    return lhs.freq == rhs.freq &&
            lhs.format == rhs.format &&
            lhs.channels == rhs.channels;
}

inline bool operator !=(const AudioFormat& lhs, const AudioFormat& rhs)
{
    return !(lhs == rhs);
}
