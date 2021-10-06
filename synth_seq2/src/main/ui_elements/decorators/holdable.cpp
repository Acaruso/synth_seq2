#include "holdable.hpp"

#include <iostream>

#include "src/main/util.hpp"

Elt holdable(EltParams& params, Elt elt)
{
    bool isInside = isCoordInsideRect(
        params.ctx.inputSystem.uiState.mousePos,
        params.rect
    );

    bool isHeld = (
        isInside
        && params.ctx.inputSystem.uiState.click
    );

    if (isHeld) {
        params.onHold();
    }

    return elt;
}
