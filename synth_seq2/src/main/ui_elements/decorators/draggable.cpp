#include "draggable.hpp"

#include "src/main/app/app_context.hpp"
#include "src/main/graphics/coord.hpp"
#include "src/main/input_system/input_system.hpp"
#include "src/main/util.hpp"

Elt draggable(EltParams& params, Elt elt)
{
    AppContext& ctx = params.ctx;
    Coord& coord = params.coord;
    Rect& rect = params.rect;
    UiState& uiState = ctx.inputSystem.uiState;
    UiState& prevUiState = ctx.inputSystem.prevUiState;

    bool isClicked = (
        isCoordInsideRect(uiState.mousePos, rect)
        && uiState.click
        && !prevUiState.click
    );

    bool isDragging = (
        uiState.click
        && uiState.curEltId == ctx.getEltId()
    );

    if (isClicked) {
        // set curEltId
        uiState.curEltId = ctx.getEltId();
    }

    if (isDragging) {
        params.onDrag();
    }

    return elt;
}
