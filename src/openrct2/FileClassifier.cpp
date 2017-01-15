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

#include "core/FileStream.hpp"
#include "FileClassifier.h"

extern "C"
{
    #include "scenario/scenario.h"
    #include "util/sawyercoding.h"
}

static bool TryClassifyAsS6(IStream * stream, ClassifiedFile * result);
static bool TryClassifyAsS4(IStream * stream, ClassifiedFile * result);
static bool TryClassifyAsTD4_TD6(IStream * stream, ClassifiedFile * result);
static bool sawyercoding_try_read_chunk(void * dst, size_t expectedSize, IStream * stream);

bool TryClassifyFile(const std::string &path, ClassifiedFile * result)
{
    try
    {
        auto fs = FileStream(path, FILE_MODE_OPEN);
        return TryClassifyFile(&fs, result);
    }
    catch (Exception)
    {
        return false;
    }
}

bool TryClassifyFile(IStream * stream, ClassifiedFile * result)
{
    // TODO Currently track designs get classified as SC4s because they use the
    //      same checksum algorithm. The only way after to tell the difference
    //      between them is to decode it. Decoding however is currently not protected
    //      against invalid compression data for that decoding algorithm and will crash.

    // S6 detection
    if (TryClassifyAsS6(stream, result))
    {
        return true;
    }

    // S4 detection
    if (TryClassifyAsS4(stream, result))
    {
        return true;
    }

    // TD6 detection
    if (TryClassifyAsTD4_TD6(stream, result))
    {
        return true;
    }

    return false;
}

static bool TryClassifyAsS6(IStream * stream, ClassifiedFile * result)
{
    rct_s6_header s6Header;
    if (sawyercoding_try_read_chunk(&s6Header, sizeof(rct_s6_header), stream))
    {
        if (s6Header.type == S6_TYPE_SAVEDGAME)
        {
            result->Type = FILE_TYPE::SAVED_GAME;
        }
        else if (s6Header.type == S6_TYPE_SCENARIO)
        {
            result->Type = FILE_TYPE::SCENARIO;
        }
        result->Version = s6Header.version;
        return true;
    }

    return false;
}

static bool TryClassifyAsS4(IStream * stream, ClassifiedFile * result)
{
    uint64 originalPosition = stream->GetPosition();
    size_t dataLength = (size_t)stream->GetLength();
    uint8 * data = stream->ReadArray<uint8>(dataLength);
    stream->SetPosition(originalPosition);
    sint32 fileTypeVersion = sawyercoding_detect_file_type(data, dataLength);
    Memory::Free(data);

    sint32 type = fileTypeVersion & FILE_TYPE_MASK;
    sint32 version = fileTypeVersion & FILE_VERSION_MASK;

    if (type == FILE_TYPE_SV4)
    {
        result->Type = FILE_TYPE::SAVED_GAME;
        result->Version = version;
        return true;
    }
    else if (type == FILE_TYPE_SC4)
    {
        result->Type = FILE_TYPE::SCENARIO;
        result->Version = version;
        return true;
    }
    
    return false;
}

static bool TryClassifyAsTD4_TD6(IStream * stream, ClassifiedFile * result)
{
    bool success = false;
    uint64 originalPosition = stream->GetPosition();
    size_t dataLength = (size_t)stream->GetLength();
    uint8 * data = stream->ReadArray<uint8>(dataLength);
    stream->SetPosition(originalPosition);

    if (sawyercoding_validate_track_checksum(data, dataLength))
    {
        uint8 * td6data = Memory::Allocate<uint8>(0x10000);
        size_t td6len = sawyercoding_decode_td6(data, td6data, dataLength);
        if (td6data != nullptr && td6len >= 8)
        {
            uint8 version = (td6data[7] >> 2) & 3;
            if (version <= 2)
            {
                result->Type = FILE_TYPE::TRACK_DESIGN;
                result->Version = version;
                success = true;
            }
        }
        Memory::Free(td6data);
    }
    Memory::Free(data);

    return success;
}

static bool sawyercoding_try_read_chunk(void * dst, size_t expectedSize, IStream * stream)
{
    uint64 originalPosition = stream->GetPosition();

    bool success = false;
    auto header = stream->ReadValue<sawyercoding_chunk_header>();
    switch (header.encoding) {
    case CHUNK_ENCODING_NONE:
    case CHUNK_ENCODING_RLE:
    case CHUNK_ENCODING_RLECOMPRESSED:
    case CHUNK_ENCODING_ROTATE:
        uint8 * compressedData = Memory::Allocate<uint8>(header.length);
        if (stream->TryRead(compressedData, header.length) == header.length)
        {
            size_t uncompressedLength = sawyercoding_read_chunk_buffer((uint8 *)dst, compressedData, header, expectedSize);
            if (uncompressedLength == expectedSize)
            {
                success = true;
            }
        }
        Memory::Free(compressedData);
        break;
    }

    stream->SetPosition(originalPosition);
    return success;
}
