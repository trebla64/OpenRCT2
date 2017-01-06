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

#include <speex/speex_resampler.h>
#include "../common.h"
#include "AudioFormat.h"
#include "AudioMixer.h"

interface IAudioSource;

/**
 * Represents an audio channel that represents an audio source
 * and a number of properties such as volume, pan and loop information.
 */
interface IAudioChannel
{
    virtual ~IAudioChannel() = default;

    virtual IAudioSource * GetSource() const abstract;

    virtual SpeexResamplerState * GetResampler() const abstract;
    virtual void SetResampler(SpeexResamplerState * value) abstract;

    virtual int     GetGroup() const abstract;
    virtual void    SetGroup(int group) abstract;

    virtual double  GetRate() const abstract;
    virtual void    SetRate(double rate) abstract;

    virtual uint64  GetOffset() const abstract;
    virtual bool    SetOffset(uint64 offset) abstract;

    virtual int     GetLoop() const abstract;
    virtual void    SetLoop(int value) abstract;

    virtual int     GetVolume() const abstract;
    virtual float   GetVolumeL() const abstract;
    virtual float   GetVolumeR() const abstract;
    virtual float   GetOldVolumeL() const abstract;
    virtual float   GetOldVolumeR() const abstract;
    virtual int     GetOldVolume() const abstract;
    virtual void    SetVolume(int volume) abstract;

    virtual float   GetPan() const abstract;
    virtual void    SetPan(float pan) abstract;

    virtual bool IsStopping() const abstract;
    virtual void SetStopping(bool value) abstract;

    virtual bool IsDone() const abstract;
    virtual void SetDone(bool value) abstract;

    virtual bool DeleteOnDone() const abstract;
    virtual void SetDeleteOnDone(bool value) abstract;

    virtual void SetDeleteSourceOnDone(bool value) abstract;

    virtual bool IsPlaying() const abstract;

    virtual void Play(IAudioSource * source, int loop = MIXER_LOOP_NONE) abstract;
    virtual void UpdateOldVolume() abstract;

    virtual AudioFormat GetFormat() const abstract;
    virtual size_t Read(void * dst, size_t len) abstract;
};

namespace AudioChannel
{
    IAudioChannel * Create();
}
