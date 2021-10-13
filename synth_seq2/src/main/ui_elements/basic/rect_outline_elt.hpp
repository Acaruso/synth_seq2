#pragma once

#include "src/main/ui_elements/elt_params.hpp"

inline void rectOutlineElt(EltParams& params)
{
    Coord topLeft{
        params.rect.x,
        params.rect.y
    };

    Coord topRight{
        params.rect.x + params.rect.w,
        params.rect.y
    };

    Coord bottomLeft{
        params.rect.x,
        params.rect.y + params.rect.h
    };

    Coord bottomRight{
        params.rect.x + params.rect.w,
        params.rect.y + params.rect.h
    };

    auto& gfx = params.ctx.graphicsWrapper;

    gfx.drawLine(topLeft, topRight);
    gfx.drawLine(topRight, bottomRight);
    gfx.drawLine(bottomRight, bottomLeft);
    gfx.drawLine(bottomLeft, topLeft);
}
