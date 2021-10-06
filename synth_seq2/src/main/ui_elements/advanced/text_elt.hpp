#pragma once

#include "src/main/ui_elements/elt_params.hpp"

inline void textElt(EltParams& params)
{
    params.ctx.graphicsWrapper.drawText(
        params.label,
        params.fontName,
        params.coord
    );
}
