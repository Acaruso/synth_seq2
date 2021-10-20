#pragma once

#include <iostream>

#include "src/main/ui_elements/elt_params.hpp"

inline void rectOutlineElt(EltParams& params)
{
    auto& gfx = params.ctx.graphicsWrapper;
    Rect r = params.rect;

    Coord topLeft{r.x, r.y};
    Coord topRight{r.x + r.w, r.y};
    Coord bottomLeft{r.x, r.y + r.h};
    Coord bottomRight{r.x + r.w, r.y + r.h};

    gfx.drawLine(topLeft, topRight);
    gfx.drawLine(topRight, bottomRight);
    gfx.drawLine(bottomRight, bottomLeft);
    gfx.drawLine(bottomLeft, topLeft);

    // for (int i = 0; i < params.lineWidth; i++) {
    //     std::cout << i << std::endl;
    //     Coord topLeft{r.x, r.y};
    //     Coord topRight{r.x + r.w, r.y};
    //     Coord bottomLeft{r.x, r.y + r.h};
    //     Coord bottomRight{r.x + r.w, r.y + r.h};

    //     gfx.drawLine(topLeft, topRight);
    //     gfx.drawLine(topRight, bottomRight);
    //     gfx.drawLine(bottomRight, bottomLeft);
    //     gfx.drawLine(bottomLeft, topLeft);
    // }
}
