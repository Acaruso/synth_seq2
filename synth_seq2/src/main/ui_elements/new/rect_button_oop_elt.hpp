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
    RectButtonOopElt() {}

    RectButtonOopElt(
        Coord coord,
        GraphicsWrapper* graphicsWrapper,
        InputSystem* inputSystem,
        // TODO: remove sequencer
        Sequencer* sequencer,
        Rect rect,
        std::function<void()> onClick,
        std::function<void()> onHold
    )
        : coord(coord)
        , graphicsWrapper(graphicsWrapper)
        , inputSystem(inputSystem)
        , sequencer(sequencer)
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

        // displayColor = sequencer->playing ? blue : white;
        displayColor = white;

        innerRect.color = displayColor;
        graphicsWrapper->drawRect(innerRect);
    }

private:
    Coord coord;

    GraphicsWrapper* graphicsWrapper;
    InputSystem* inputSystem;
    Sequencer* sequencer;
    Rect rect;

    std::function<void()> onClick;
    std::function<void()> onHold;

    Color color;
    Color displayColor;
    Color onClickColor;

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

        if (isClicked) {
            onClick();
        }

        // on hold ////////////////////
        bool isInside = isCoordInsideRect(
            uiState.mousePos,
            rect
        );

        bool isHeld = (isInside && uiState.click);

        if (isHeld) {
            onHold();
        }
    }

};
