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

#include "../core/Exception.hpp"
#include "IDrawingContext.h"
#include "IDrawingEngine.h"
#include "NewDrawing.h"

extern "C"
{
    #include "../config.h"
    #include "../drawing/drawing.h"
    #include "../interface/screenshot.h"
    #include "../localisation/string_ids.h"
    #include "../platform/platform.h"
}

static sint32           _drawingEngineType  = DRAWING_ENGINE_SOFTWARE;
static IDrawingEngine * _drawingEngine      = nullptr;

extern "C"
{
    rct_string_id DrawingEngineStringIds[] =
    {
        STR_DRAWING_ENGINE_SOFTWARE,
        STR_DRAWING_ENGINE_SOFTWARE_WITH_HARDWARE_DISPLAY,
        STR_DRAWING_ENGINE_OPENGL,
    };
}

extern "C"
{
    void drawing_engine_init()
    {
        assert(_drawingEngine == nullptr);

        _drawingEngineType = gConfigGeneral.drawing_engine;
        switch (_drawingEngineType) {
        case DRAWING_ENGINE_SOFTWARE:
            _drawingEngine = DrawingEngineFactory::CreateSoftware();
            break;
        case DRAWING_ENGINE_SOFTWARE_WITH_HARDWARE_DISPLAY:
            _drawingEngine = DrawingEngineFactory::CreateSoftwareWithHardwareDisplay();
            break;
        case DRAWING_ENGINE_OPENGL:
            _drawingEngine = DrawingEngineFactory::CreateOpenGL();
            break;
        }

        if (_drawingEngine == nullptr)
        {
            if (_drawingEngineType == DRAWING_ENGINE_SOFTWARE)
            {
                _drawingEngineType = DRAWING_ENGINE_NONE;
                log_fatal("Unable to create a drawing engine.");
                exit(-1);
            }
            else
            {
                log_error("Unable to create drawing engine. Falling back to software.");

                // Fallback to software
                gConfigGeneral.drawing_engine = DRAWING_ENGINE_SOFTWARE;
                config_save_default();
                drawing_engine_init();
            }
        }
        else
        {
            try
            {
                _drawingEngine->Initialise(gWindow);
                _drawingEngine->SetUncappedFrameRate(gConfigGeneral.uncap_fps == 1);
            }
            catch (Exception ex)
            {
                delete _drawingEngine;
                _drawingEngine = nullptr;
                if (_drawingEngineType == DRAWING_ENGINE_SOFTWARE)
                {
                    _drawingEngineType = DRAWING_ENGINE_NONE;
                    log_fatal("Unable to initialise a drawing engine.");
                    exit(-1);
                }
                else
                {
                    log_error("Unable to initialise drawing engine. Falling back to software.");

                    // Fallback to software
                    gConfigGeneral.drawing_engine = DRAWING_ENGINE_SOFTWARE;
                    config_save_default();
                    drawing_engine_init();
                }
            }
        }
    }

    void drawing_engine_resize()
    {
        if (_drawingEngine == nullptr)
        {
            drawing_engine_init();
        }
        _drawingEngine->Resize(gScreenWidth, gScreenHeight);
    }

    void drawing_engine_set_palette(SDL_Color * colours)
    {
        _drawingEngine->SetPalette(colours);
    }

    void drawing_engine_draw()
    {
        _drawingEngine->Draw();
    }

    void drawing_engine_copy_rect(int x, int y, int width, int height, int dx, int dy)
    {
        if (_drawingEngine != nullptr)
        {
            _drawingEngine->CopyRect(x, y, width, height, dx, dy);
        }
    }

    void drawing_engine_dispose()
    {
        delete _drawingEngine;
        _drawingEngine = nullptr;
    }

    rct_drawpixelinfo * drawing_engine_get_dpi()
    {
        assert(_drawingEngine != nullptr);
        return _drawingEngine->GetDrawingPixelInfo();
    }

    bool drawing_engine_has_dirty_optimisations()
    {
        bool result = false;
        if (_drawingEngine != nullptr)
        {
            result = (_drawingEngine->GetFlags() & DEF_DIRTY_OPTIMISATIONS);
        }
        return result;
    }

    void drawing_engine_invalidate_image(uint32 image)
    {
        if (_drawingEngine != nullptr)
        {
            _drawingEngine->InvalidateImage(image);
        }
    }

    void drawing_engine_set_fps_uncapped(bool uncapped)
    {
        if (_drawingEngine != nullptr)
        {
            _drawingEngine->SetUncappedFrameRate(uncapped);
        }
    }

    void gfx_set_dirty_blocks(sint16 left, sint16 top, sint16 right, sint16 bottom)
    {
        if (_drawingEngine != nullptr)
        {
            _drawingEngine->Invalidate(left, top, right, bottom);
        }
    }

    void gfx_draw_all_dirty_blocks()
    {
    }

    void gfx_clear(rct_drawpixelinfo * dpi, uint32 colour)
    {
        if (_drawingEngine != nullptr)
        {
            IDrawingContext * dc = _drawingEngine->GetDrawingContext(dpi);
            dc->Clear(colour);
        }
    }

    void gfx_fill_rect(rct_drawpixelinfo * dpi, int left, int top, int right, int bottom, int colour)
    {
        if (_drawingEngine != nullptr)
        {
            IDrawingContext * dc = _drawingEngine->GetDrawingContext(dpi);
            dc->FillRect(colour, left, top, right, bottom);
        }
    }

    void gfx_draw_line(rct_drawpixelinfo *dpi, int x1, int y1, int x2, int y2, int colour)
    {
        if (_drawingEngine != nullptr)
        {
            IDrawingContext * dc = _drawingEngine->GetDrawingContext(dpi);
            dc->DrawLine(colour, x1, y1, x2, y2);
        }
    }

    void FASTCALL gfx_draw_sprite(rct_drawpixelinfo * dpi, int image, int x, int y, uint32 tertiary_colour)
    {
        if (_drawingEngine != nullptr)
        {
            IDrawingContext * dc = _drawingEngine->GetDrawingContext(dpi);
            dc->DrawSprite(image, x, y, tertiary_colour);
        }
    }

    void FASTCALL gfx_draw_glpyh(rct_drawpixelinfo * dpi, int image, int x, int y, uint8 * palette)
    {
        if (_drawingEngine != nullptr)
        {
            IDrawingContext * dc = _drawingEngine->GetDrawingContext(dpi);
            dc->DrawGlyph(image, x, y, palette);
        }
    }

    void FASTCALL gfx_draw_sprite_raw_masked(rct_drawpixelinfo * dpi, int x, int y, int maskImage, int colourImage)
    {
        if (_drawingEngine != nullptr)
        {
            IDrawingContext * dc = _drawingEngine->GetDrawingContext(dpi);
            dc->DrawSpriteRawMasked(x, y, maskImage, colourImage);
        }
    }

    void FASTCALL gfx_draw_sprite_solid(rct_drawpixelinfo * dpi, int image, int x, int y, uint8 colour)
    {
        if (_drawingEngine != nullptr)
        {
            IDrawingContext * dc = _drawingEngine->GetDrawingContext(dpi);
            dc->DrawSpriteSolid(image, x, y, colour);
        }
    }

    int screenshot_dump()
    {
        if (_drawingEngine != nullptr)
        {
            return _drawingEngine->Screenshot();
        }
        return false;
    }
}
