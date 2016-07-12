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

#include "../core/IStream.hpp"
#include "../core/Memory.hpp"
#include "LargeSceneryObject.h"

extern "C"
{
    #include "../drawing/drawing.h"
    #include "../localisation/localisation.h"
}

enum OBJ_STRING_ID
{
    OBJ_STRING_ID_NAME,
};

LargeSceneryObject::~LargeSceneryObject()
{
    Memory::Free(_3dFont);
    Memory::Free(_tiles);
}

void LargeSceneryObject::ReadLegacy(IReadObjectContext * context, IStream * stream)
{
    stream->Seek(6, STREAM_SEEK_CURRENT);
    _legacyType.large_scenery.tool_id = stream->ReadValue<uint8>();
    _legacyType.large_scenery.flags = stream->ReadValue<uint8>();
    _legacyType.large_scenery.price = stream->ReadValue<sint16>();
    _legacyType.large_scenery.removal_price = stream->ReadValue<sint16>();
    stream->Seek(5, STREAM_SEEK_CURRENT);
    _legacyType.large_scenery.scenery_tab_id = 0xFF;
    _legacyType.large_scenery.var_11 = stream->ReadValue<uint8>();
    stream->Seek(4, STREAM_SEEK_CURRENT);

    GetStringTable()->Read(context, stream, OBJ_STRING_ID_NAME);

    rct_object_entry sgEntry = stream->ReadValue<rct_object_entry>();
    SetPrimarySceneryGroup(&sgEntry);

    if (_legacyType.large_scenery.flags & (1 << 2))
    {
        _3dFont = Memory::Allocate<rct_large_scenery_text>();
        stream->Read(_3dFont);
        _legacyType.large_scenery.text = _3dFont;
    }

    _tiles = ReadTiles(stream);

    GetImageTable()->Read(context, stream);

    // Validate properties
    if (_legacyType.large_scenery.price <= 0)
    {
        context->LogError(OBJECT_ERROR_INVALID_PROPERTY, "Price can not be free or negative.");
    }
    if (_legacyType.large_scenery.removal_price <= 0)
    {
        // Make sure you don't make a profit when placing then removing.
        money16 reimbursement = _legacyType.large_scenery.removal_price;
        if (reimbursement > _legacyType.large_scenery.price)
        {
            context->LogError(OBJECT_ERROR_INVALID_PROPERTY, "Sell price can not be more than buy price.");
        }
    }
}

void LargeSceneryObject::Load()
{
    GetStringTable()->Sort();
    _legacyType.name = language_allocate_object_string(GetName());
    _baseImageId = gfx_object_allocate_images(GetImageTable()->GetImages(), GetImageTable()->GetCount());
    _legacyType.image = _baseImageId;

    _legacyType.large_scenery.tiles = _tiles;

    if (_legacyType.large_scenery.flags & (1 << 2))
    {
        _legacyType.large_scenery.text_image = _legacyType.image;
        if (_3dFont->var_C & (1 << 0))
        {
            _legacyType.image += (_3dFont->var_C >> 8) * 2;
        }
        else
        {
            _legacyType.image += (_3dFont->var_C >> 8) * 4;
        }
    }
}

void LargeSceneryObject::Unload()
{
    language_free_object_string(_legacyType.name);
    gfx_object_free_images(_baseImageId, GetImageTable()->GetCount());

    _legacyType.name = 0;
    _legacyType.image = 0;
}

void LargeSceneryObject::DrawPreview(rct_drawpixelinfo * dpi, sint32 width, sint32 height) const
{
    sint32 x = width / 2;
    sint32 y = (height / 2) - 39;

    uint32 imageId = 0xB2D00000 | _legacyType.image;
    gfx_draw_sprite(dpi, imageId, x, y, 0);
}

rct_large_scenery_tile * LargeSceneryObject::ReadTiles(IStream * stream)
{
    auto tiles = std::vector<rct_large_scenery_tile>();

    uint16 tilesEndMarker;
    while ((tilesEndMarker = stream->ReadValue<uint16>()) != 0xFFFF)
    {
        stream->Seek(-2, STREAM_SEEK_CURRENT);
        auto tile = stream->ReadValue<rct_large_scenery_tile>();
        tiles.push_back(tile);
    }
    tiles.push_back({ -1, -1, -1, 255, 0xFFFF });

    return Memory::DuplicateArray(tiles.data(), tiles.size());
}
