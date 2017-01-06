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

#include <list>
#include "../core/Guard.hpp"
#include "../core/Math.hpp"
#include "../core/Memory.hpp"
#include "../core/Util.hpp"
#include "AudioChannel.h"
#include "AudioMixer.h"
#include "AudioSource.h"

extern "C"
{
    #include "../config.h"
    #include "../localisation/localisation.h"
    #include "../OpenRCT2.h"
    #include "../platform/platform.h"
    #include "../rct2.h"
    #include "audio.h"
}

IAudioMixer * gMixer;

struct Buffer
{
private:
    void * _data = nullptr;
    size_t _capacity = 0;

public:
    void * GetData() const { return _data; }
    void * GetData() { return _data; }
    size_t GetCapacity() const { return _capacity; }

    ~Buffer()
    {
        Free();
    }

    void Free()
    {
        Memory::Free(_data);
        _data = nullptr;
        _capacity = 0;
    }

    void EnsureCapacity(size_t capacity)
    {
        if (_capacity < capacity)
        {
            _capacity = capacity;
            _data = Memory::Reallocate(_data, capacity);
        }
    }
};

class AudioMixer : public IAudioMixer
{
private:
    IAudioSource * _nullSource = nullptr;

    SDL_AudioDeviceID _deviceId = 0;
    AudioFormat _format = { 0 };
    std::list<IAudioChannel *> _channels;
    float _volume = 1.0f;
    float _adjustSoundVolume = 0.0f;
    float _adjustMusicVolume = 0.0f;
    uint8 _settingSoundVolume = 0xFF;
    uint8 _settingMusicVolume = 0xFF;

    IAudioSource * _css1Sources[SOUND_MAXID] = { nullptr };
    IAudioSource * _musicSources[PATH_ID_END] = { nullptr };

    Buffer _channelBuffer;
    Buffer _convertBuffer;
    Buffer _effectBuffer;

public:
    AudioMixer()
    {
        _nullSource = AudioSource::CreateNull();
    }

    ~AudioMixer()
    {
        Close();
        delete _nullSource;
    }

    void Init(const char* device) override
    {
        Close();

        SDL_AudioSpec want = { 0 };
        want.freq = 44100;
        want.format = AUDIO_S16SYS;
        want.channels = 2;
        want.samples = 1024;
        want.callback = [](void * arg, uint8 * dst, int length) -> void
        {
            auto mixer = static_cast<AudioMixer *>(arg);
            mixer->GetNextAudioChunk(dst, (size_t)length);
        };
        want.userdata = this;

        SDL_AudioSpec have;
        _deviceId = SDL_OpenAudioDevice(device, 0, &want, &have, 0);
        _format.format = have.format;
        _format.channels = have.channels;
        _format.freq = have.freq;

        LoadAllSounds();

        SDL_PauseAudioDevice(_deviceId, 0);
    }

    void Close() override
    {
        // Free channels
        Lock();
        for (IAudioChannel * channel : _channels)
        {
            delete channel;
        }
        _channels.clear();
        Unlock();

        SDL_CloseAudioDevice(_deviceId);

        // Free sources
        for (size_t i = 0; i < Util::CountOf(_css1Sources); i++)
        {
            if (_css1Sources[i] != _nullSource)
            {
                SafeDelete(_css1Sources[i]);
            }
        }
        for (size_t i = 0; i < Util::CountOf(_musicSources); i++)
        {
            if (_musicSources[i] != _nullSource)
            {
                SafeDelete(_musicSources[i]);
            }
        }

        // Free buffers
        _channelBuffer.Free();
        _convertBuffer.Free();
        _effectBuffer.Free();
    }

    void Lock() override
    {
        SDL_LockAudioDevice(_deviceId);
    }

    void Unlock() override
    {
        SDL_UnlockAudioDevice(_deviceId);
    }

    IAudioChannel * Play(IAudioSource * source, int loop, bool deleteondone, bool deletesourceondone) override
    {
        Lock();
        IAudioChannel * channel = AudioChannel::Create();
        if (channel != nullptr)
        {
            channel->Play(source, loop);
            channel->SetDeleteOnDone(deleteondone);
            channel->SetDeleteSourceOnDone(deletesourceondone);
            _channels.push_back(channel);
        }
        Unlock();
        return channel;
    }

    void Stop(IAudioChannel * channel) override
    {
        Lock();
        channel->SetStopping(true);
        Unlock();
    }

    bool LoadMusic(size_t pathId) override
    {
        bool result = false;
        if (pathId < Util::CountOf(_musicSources))
        {
            IAudioSource * source = _musicSources[pathId];
            if (source == nullptr)
            {
                const utf8 * path = get_file_path((int)pathId);
                source = AudioSource::CreateMemoryFromWAV(path, &_format);
                if (source == nullptr)
                {
                    source = _nullSource;
                }
                _musicSources[pathId] = source;
            }
            result = source != _nullSource;
        }
        return result;
    }

    void SetVolume(float volume) override
    {
        _volume = volume;
    }

    IAudioSource * GetSoundSource(int id) override
    {
        return _css1Sources[id];
    }

    IAudioSource * GetMusicSource(int id) override
    {
        return _musicSources[id];
    }

private:
    void LoadAllSounds()
    {
        const utf8 * css1Path = get_file_path(PATH_ID_CSS1);
        for (size_t i = 0; i < Util::CountOf(_css1Sources); i++)
        {
            auto source = AudioSource::CreateMemoryFromCSS1(css1Path, i, &_format);
            if (source == nullptr)
            {
                source = _nullSource;
            }
            _css1Sources[i] = source;
        }
    }

    void GetNextAudioChunk(uint8 * dst, size_t length)
    {
        UpdateAdjustedSound();

        // Zero the output buffer
        Memory::Set(dst, 0, length);

        // Mix channels onto output buffer
        std::list<IAudioChannel *>::iterator it = _channels.begin();
        while (it != _channels.end())
        {
            IAudioChannel * channel = *it;

            int group = channel->GetGroup();
            if (group != MIXER_GROUP_SOUND || gConfigSound.sound_enabled)
            {
                MixChannel(channel, dst, length);
            }
            if ((channel->IsDone() && channel->DeleteOnDone()) || channel->IsStopping())
            {
                delete channel;
                it = _channels.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    void UpdateAdjustedSound()
    {
        // Did the volume level get changed? Recalculate level in this case.
        if (_settingSoundVolume != gConfigSound.sound_volume)
        {
            _settingSoundVolume = gConfigSound.sound_volume;
            _adjustSoundVolume = powf(_settingSoundVolume / 100.f, 10.f / 6.f);
        }
        if (_settingMusicVolume != gConfigSound.ride_music_volume)
        {
            _settingMusicVolume = gConfigSound.ride_music_volume;
            _adjustMusicVolume = powf(_settingMusicVolume / 100.f, 10.f / 6.f);
        }
    }

    void MixChannel(IAudioChannel * channel, uint8 * data, size_t length)
    {
        int byteRate = _format.GetByteRate();
        int numSamples = (int)(length / byteRate);
        double rate = 1;
        if (_format.format == AUDIO_S16SYS)
        {
            rate = channel->GetRate();
        }

        bool mustConvert = false;
        SDL_AudioCVT cvt;
        cvt.len_ratio = 1;
        AudioFormat streamformat = channel->GetFormat();
        if (streamformat != _format)
        {
            if (SDL_BuildAudioCVT(&cvt, streamformat.format, streamformat.channels, streamformat.freq, _format.format, _format.channels, _format.freq) == -1)
            {
                // Unable to convert channel data
                return;
            }
            mustConvert = true;
        }

        // Read raw PCM from channel
        int readSamples = (int)(numSamples * rate);
        size_t readLength = (size_t)(readSamples / cvt.len_ratio) * byteRate;
        _channelBuffer.EnsureCapacity(readLength);
        size_t bytesRead = channel->Read(_channelBuffer.GetData(), readLength);

        // Convert data to required format if necessary
        void * buffer = nullptr;
        size_t bufferLen = 0;
        if (mustConvert)
        {
            if (Convert(&cvt, _channelBuffer.GetData(), bytesRead))
            {
                buffer = cvt.buf;
                bufferLen = cvt.len_cvt;
            }
            else
            {
                return;
            }
        }
        else
        {
            buffer = _channelBuffer.GetData();
            bufferLen = bytesRead;
        }

        // Apply effects
        if (rate != 1)
        {
            int srcSamples = (int)(bufferLen / byteRate);
            int dstSamples = numSamples;
            bufferLen = ApplyResample(channel, buffer, srcSamples, dstSamples);
            buffer = _effectBuffer.GetData();
        }

        // Apply panning and volume
        ApplyPan(channel, buffer, bufferLen, byteRate);
        int mixVolume = ApplyVolume(channel, buffer, bufferLen);

        // Finally mix on to destination buffer
        size_t dstLength = Math::Min(length, bufferLen);
        SDL_MixAudioFormat(data, (const uint8 *)buffer, _format.format, (uint32)dstLength, mixVolume);

        channel->UpdateOldVolume();
    }

    /**
     * Resample the given buffer into _effectBuffer.
     * Assumes that srcBuffer is the same format as _format.
     */
    size_t ApplyResample(IAudioChannel * channel, const void * srcBuffer, int srcSamples, int dstSamples)
    {
        int byteRate = _format.GetByteRate();

        // Create resampler
        SpeexResamplerState * resampler = channel->GetResampler();
        if (resampler == nullptr)
        {
            resampler = speex_resampler_init(_format.channels, _format.freq, _format.freq, 0, 0);
            channel->SetResampler(resampler);
        }
        speex_resampler_set_rate(resampler, srcSamples, dstSamples);

        // Ensure destination buffer is large enough
        size_t effectBufferReqLen  = dstSamples * byteRate;
        _effectBuffer.EnsureCapacity(effectBufferReqLen);

        uint32 inLen = srcSamples;
        uint32 outLen = dstSamples;
        speex_resampler_process_interleaved_int(
            resampler,
            (const spx_int16_t *)srcBuffer,
            &inLen,
            (spx_int16_t *)_effectBuffer.GetData(),
            &outLen);

        return outLen * byteRate;
    }

    void ApplyPan(const IAudioChannel * channel, void * buffer, size_t len, size_t sampleSize)
    {
        if (channel->GetPan() != 0.5f && _format.channels == 2)
        {
            switch (_format.format) {
            case AUDIO_S16SYS:
                EffectPanS16(channel, (sint16 *)buffer, (int)(len / sampleSize));
                break;
            case AUDIO_U8:
                EffectPanU8(channel, (uint8 *)buffer, (int)(len / sampleSize));
                break;
            }
        }
    }

    int ApplyVolume(const IAudioChannel * channel, void * buffer, size_t len)
    {
        float volumeAdjust = _volume;
        volumeAdjust *= (gConfigSound.master_volume / 100.0f);
        switch (channel->GetGroup()) {
        case MIXER_GROUP_SOUND:
            volumeAdjust *= _adjustSoundVolume;

            // Cap sound volume on title screen so music is more audible
            if (gScreenFlags & SCREEN_FLAGS_TITLE_DEMO)
            {
                volumeAdjust = Math::Min(volumeAdjust, 0.75f);
            }
            break;
        case MIXER_GROUP_RIDE_MUSIC:
            volumeAdjust *= _adjustMusicVolume;
            break;
        }

        int startVolume = (int)(channel->GetOldVolume() * volumeAdjust);
        int endVolume = (int)(channel->GetVolume() * volumeAdjust);
        if (channel->IsStopping())
        {
            endVolume = 0;
        }

        int mixVolume = (int)(channel->GetVolume() * volumeAdjust);
        if (startVolume != endVolume)
        {
            // Set to max since we are adjusting the volume ourselves
            mixVolume = SDL_MIX_MAXVOLUME;

            // Fade between volume levels to smooth out sound and minimize clicks from sudden volume changes
            int fadeLength = (int)len / _format.BytesPerSample();
            switch (_format.format) {
            case AUDIO_S16SYS:
                EffectFadeS16((sint16 *)buffer, fadeLength, startVolume, endVolume);
                break;
            case AUDIO_U8:
                EffectFadeU8((uint8 *)buffer, fadeLength, startVolume, endVolume);
                break;
            }
        }
        return mixVolume;
    }

    static void EffectPanS16(const IAudioChannel * channel, sint16 * data, int length)
    {
        const float dt = 1.0f / (length * 2);
        float volumeL = channel->GetOldVolumeL();
        float volumeR = channel->GetOldVolumeR();
        const float d_left = dt * (channel->GetVolumeL() - channel->GetOldVolumeL());
        const float d_right = dt * (channel->GetVolumeR() - channel->GetOldVolumeR());

        for (int i = 0; i < length * 2; i += 2)
        {
            data[i] = (sint16)(data[i] * volumeL);
            data[i + 1] = (sint16)(data[i + 1] * volumeR);
            volumeL += d_left;
            volumeR += d_right;
        }
    }

    static void EffectPanU8(const IAudioChannel * channel, uint8 * data, int length)
    {
        float volumeL = channel->GetVolumeL();
        float volumeR = channel->GetVolumeR();
        float oldVolumeL = channel->GetOldVolumeL();
        float oldVolumeR = channel->GetOldVolumeR();

        for (int i = 0; i < length * 2; i += 2)
        {
            float t = (float)i / (length * 2);
            data[i] = (uint8)(data[i] * ((1.0 - t) * oldVolumeL + t * volumeL));
            data[i + 1] = (uint8)(data[i + 1] * ((1.0 - t) * oldVolumeR + t * volumeR));
        }
    }

    static void EffectFadeS16(sint16 * data, int length, int startvolume, int endvolume)
    {
        float startvolume_f = (float)startvolume / SDL_MIX_MAXVOLUME;
        float endvolume_f = (float)endvolume / SDL_MIX_MAXVOLUME;
        for (int i = 0; i < length; i++)
        {
            float t = (float)i / length;
            data[i] = (sint16)(data[i] * ((1 - t) * startvolume_f + t * endvolume_f));
        }
    }

    static void EffectFadeU8(uint8* data, int length, int startvolume, int endvolume)
    {
        float startvolume_f = (float)startvolume / SDL_MIX_MAXVOLUME;
        float endvolume_f = (float)endvolume / SDL_MIX_MAXVOLUME;
        for (int i = 0; i < length; i++)
        {
            float t = (float)i / length;
            data[i] = (uint8)(data[i] * ((1 - t) * startvolume_f + t * endvolume_f));
        }
    }

    bool Convert(SDL_AudioCVT * cvt, const void * src, size_t len)
    {
        // tofix: there seems to be an issue with converting audio using SDL_ConvertAudio in the callback vs preconverted, can cause pops and static depending on sample rate and channels
        bool result = false;
        if (len != 0 && cvt->len_mult != 0)
        {
            size_t reqConvertBufferCapacity = len * cvt->len_mult;
            _convertBuffer.EnsureCapacity(reqConvertBufferCapacity);
            Memory::Copy(_convertBuffer.GetData(), src, len);

            cvt->len = (int)len;
            cvt->buf = (uint8 *)_convertBuffer.GetData();
            if (SDL_ConvertAudio(cvt) >= 0)
            {
                result = true;
            }
        }
        return result;
    }
};

void Mixer_Init(const char * device)
{
    if (!gOpenRCT2Headless)
    {
        gMixer = new AudioMixer();
        gMixer->Init(device);
    }
}

void * Mixer_Play_Effect(size_t id, int loop, int volume, float pan, double rate, int deleteondone)
{
    IAudioChannel * channel = nullptr;
    if (!gOpenRCT2Headless && gConfigSound.sound_enabled)
    {
        if (id >= SOUND_MAXID)
        {
            log_error("Tried to play an invalid sound id. %i", id);
        }
        else
        {
            IAudioMixer * mixer = gMixer;
            mixer->Lock();
            IAudioSource * source = mixer->GetSoundSource((int)id);
            channel = mixer->Play(source, loop, deleteondone != 0, false);
            if (channel != nullptr)
            {
                channel->SetVolume(volume);
                channel->SetPan(pan);
                channel->SetRate(rate);
            }
            mixer->Unlock();
        }
    }
    return channel;
}

void Mixer_Stop_Channel(void * channel)
{
    if (!gOpenRCT2Headless)
    {
        gMixer->Stop(static_cast<IAudioChannel*>(channel));
    }
}

void Mixer_Channel_Volume(void * channel, int volume)
{
    if (!gOpenRCT2Headless)
    {
        gMixer->Lock();
        static_cast<IAudioChannel*>(channel)->SetVolume(volume);
        gMixer->Unlock();
    }
}

void Mixer_Channel_Pan(void * channel, float pan)
{
    if (!gOpenRCT2Headless)
    {
        gMixer->Lock();
        static_cast<IAudioChannel*>(channel)->SetPan(pan);
        gMixer->Unlock();
    }
}

void Mixer_Channel_Rate(void* channel, double rate)
{
    if (!gOpenRCT2Headless)
    {
        gMixer->Lock();
        static_cast<IAudioChannel*>(channel)->SetRate(rate);
        gMixer->Unlock();
    }
}

int Mixer_Channel_IsPlaying(void * channel)
{
    bool isPlaying = false;
    if (!gOpenRCT2Headless)
    {
        isPlaying = static_cast<IAudioChannel*>(channel)->IsPlaying();
    }
    return isPlaying;
}

uint64 Mixer_Channel_GetOffset(void * channel)
{
    uint64 offset = 0;
    if (!gOpenRCT2Headless)
    {
        offset = static_cast<IAudioChannel*>(channel)->GetOffset();
    }
    return offset;
}

int Mixer_Channel_SetOffset(void * channel, uint64 offset)
{
    int result = 0;
    if (!gOpenRCT2Headless)
    {
        result = static_cast<IAudioChannel*>(channel)->SetOffset(offset);
    }
    return result;
}

void Mixer_Channel_SetGroup(void * channel, int group)
{
    if (!gOpenRCT2Headless)
    {
        static_cast<IAudioChannel *>(channel)->SetGroup(group);
    }
}

void * Mixer_Play_Music(int pathId, int loop, int streaming)
{
    IAudioChannel * channel = nullptr;
    if (!gOpenRCT2Headless)
    {
        IAudioMixer * mixer = gMixer;
        if (streaming)
        {
            const utf8 * filename = get_file_path(pathId);

            SDL_RWops* rw = SDL_RWFromFile(filename, "rb");
            if (rw != nullptr)
            {
                auto source = AudioSource::CreateStreamFromWAV(rw);
                if (source != nullptr)
                {
                    channel = mixer->Play(source, loop, false, true);
                    if (channel == nullptr)
                    {
                        delete source;
                    }
                }
            }
        }
        else
        {
            if (mixer->LoadMusic(pathId))
            {
                IAudioSource * source = mixer->GetMusicSource(pathId);
                channel = mixer->Play(source, MIXER_LOOP_INFINITE, false, false);
            }
        }
        if (channel != nullptr)
        {
            channel->SetGroup(MIXER_GROUP_RIDE_MUSIC);
        }
    }
    return channel;
}

void Mixer_SetVolume(float volume)
{
    if (!gOpenRCT2Headless)
    {
        gMixer->SetVolume(volume);
    }
}
