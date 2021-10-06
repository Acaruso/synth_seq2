#include "clickable.hpp"

#include "src/main/util.hpp"

Elt clickable(EltParams& params, Elt elt)
{
    AppContext& ctx = params.ctx;
    Rect& rect = params.rect;
    UiState& uiState = ctx.inputSystem.uiState;
    UiState& prevUiState = ctx.inputSystem.prevUiState;

    bool isClicked = (
        isCoordInsideRect(uiState.mousePos, rect)
        && uiState.click
        && !prevUiState.click
    );

    if (isClicked) {
        params.onClick();
    }

    return elt;
}
