#pragma once

#include <functional>
#include <string>

#include "src/main/graphics/graphics_wrapper.hpp"
#include "src/main/graphics/rect.hpp"
#include "src/main/input_system/input_system.hpp"
#include "src/main/sequencer/sequencer.hpp"
#include "src/main/ui_elements/new/base_elt.hpp"
#include "src/main/util.hpp"

class RectButtonOopElt : public BaseElt
{
public:
    std::function<void()> onClick;
    std::function<void()> onHold;
    Color color{white};
    Color displayColor{white};
    Color onClickColor{blue};

    RectButtonOopElt() {}

    RectButtonOopElt(
        Coord coord,
        GraphicsWrapper* graphicsWrapper,
        InputSystem* inputSystem,
        Rect rect,
        std::function<void()> onClick = nullptr,
        std::function<void()> onHold = nullptr
    )
        : coord(coord)
        , graphicsWrapper(graphicsWrapper)
        , inputSystem(inputSystem)
        , rect(rect)
        , onClick(onClick)
        , onHold(onHold)
    {}

    void run() override
    {
        handleUserInput();

        Rect innerRect{
            rect.x + 2,
            rect.y + 2,
            rect.z + 1,
            rect.w - 4,
            rect.h - 4
        };

        rect.color = black;
        graphicsWrapper->drawRect(rect);

        innerRect.color = displayColor;
        graphicsWrapper->drawRect(innerRect);
    }

private:
    Coord coord;

    GraphicsWrapper* graphicsWrapper;
    InputSystem* inputSystem;
    Rect rect;

    void handleUserInput()
    {
        UiState& uiState = inputSystem->uiState;
        UiState& prevUiState = inputSystem->prevUiState;

        // on click ///////////////////
        bool isClicked = (
            isCoordInsideRect(uiState.mousePos, rect)
            && uiState.click
            && !prevUiState.click
        );

        if (isClicked && onClick) {
            onClick();
        }

        // on hold ////////////////////
        bool isInside = isCoordInsideRect(
            uiState.mousePos,
            rect
        );

        bool isHeld = (isInside && uiState.click);

        if (isHeld && onHold) {
            onHold();
        }
    }
};
