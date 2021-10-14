#pragma once

#include <functional>
#include <iostream>
#include <string>

#include "src/main/graphics/color.hpp"
#include "src/main/graphics/coord.hpp"
#include "src/main/graphics/graphics_wrapper.hpp"
#include "src/main/graphics/rect.hpp"
#include "src/main/input_system/input_system.hpp"
#include "src/main/sequencer/sequencer.hpp"
#include "src/main/ui_elements/new/base_elt.hpp"
#include "src/main/util.hpp"
#include "src/shared/messages.hpp"

class TransportOopElt : public BaseElt
{
public:
    TransportOopElt() {}

    TransportOopElt(
        GraphicsWrapper* graphicsWrapper,
        InputSystem* inputSystem,
        Sequencer* sequencer,
        MessageQueue* toAudioQueue
    )
        : graphicsWrapper(graphicsWrapper)
        , inputSystem(inputSystem)
        , sequencer(sequencer)
        , toAudioQueue(toAudioQueue)
    {
        onClick = [=]() {
            sequencer->playing = !sequencer->playing;
            sequencer->transport = 0;

            if (sequencer->playing) {
                toAudioQueue->enqueue(PlayMessage());
            }
            else {
                toAudioQueue->enqueue(StopMessage());
            }
        };

        onHold = [&]() { displayColor = onClickColor; };

        color = white;
        onClickColor = blue;
    }

    void run(Coord coord)
    {
        // text ///////////////////////
        std::string label = "play";

        graphicsWrapper->drawText(
            label,
            "inconsolata",
            coord
        );

        // rect button ////////////////
        Rect rect(coord.x, coord.y + 20, 50, 50);

        handleUserInput(rect);

        Rect innerRect{
            rect.x + 2,
            rect.y + 2,
            rect.z + 1,
            rect.w - 4,
            rect.h - 4
        };

        rect.color = black;
        graphicsWrapper->drawRect(rect);

        displayColor = sequencer->playing ? blue : white;

        innerRect.color = displayColor;
        graphicsWrapper->drawRect(innerRect);
    }

private:
    GraphicsWrapper* graphicsWrapper;
    InputSystem* inputSystem;
    Sequencer* sequencer;
    MessageQueue* toAudioQueue;
    std::function<void()> onClick;
    std::function<void()> onHold;
    Color color;
    Color displayColor;
    Color onClickColor;

    void handleUserInput(Rect rect)
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
