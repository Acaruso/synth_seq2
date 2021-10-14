#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "src/main/graphics/color.hpp"
#include "src/main/graphics/coord.hpp"
#include "src/main/graphics/graphics_wrapper.hpp"
#include "src/main/graphics/rect.hpp"
#include "src/main/input_system/input_system.hpp"
#include "src/main/sequencer/sequencer.hpp"
#include "src/main/ui_elements/new/base_elt.hpp"
#include "src/main/ui_elements/new/rect_button_oop_elt.hpp"
#include "src/main/ui_elements/new/text_oop_elt.hpp"
#include "src/main/util.hpp"
#include "src/shared/messages.hpp"

class TransportOopElt : public BaseElt
{
public:
    TransportOopElt() {}

    TransportOopElt(
        Coord coord,
        GraphicsWrapper* graphicsWrapper,
        InputSystem* inputSystem,
        Sequencer* sequencer,
        MessageQueue* toAudioQueue
    )
        : coord(coord)
        , graphicsWrapper(graphicsWrapper)
        , inputSystem(inputSystem)
        , sequencer(sequencer)
        , toAudioQueue(toAudioQueue)
    {
        auto onClick = [=]() {
            sequencer->playing = !sequencer->playing;
            sequencer->transport = 0;

            if (sequencer->playing) {
                toAudioQueue->enqueue(PlayMessage());
            }
            else {
                toAudioQueue->enqueue(StopMessage());
            }
        };

        // TODO: figure out onHold
        auto onHold = [&]() { displayColor = onClickColor; };

        color = white;
        onClickColor = blue;

        children.push_back(new TextOopElt(coord, graphicsWrapper, "play"));

        Rect rect(coord.x, coord.y + 20, 50, 50);

        children.push_back(
            new RectButtonOopElt(
                coord,
                graphicsWrapper,
                inputSystem,
                rect,
                onClick,
                onHold
            )
        );
    }

    void run() override
    {
        for (auto& child : children) {
            child->run();
        }
    }

private:
    Coord coord;
    GraphicsWrapper* graphicsWrapper;
    InputSystem* inputSystem;
    Sequencer* sequencer;
    MessageQueue* toAudioQueue;
    Color color;
    Color displayColor;
    Color onClickColor;
    std::vector<BaseElt*> children;
};
