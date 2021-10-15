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
        Coord coord_,
        GraphicsWrapper* graphicsWrapper_,
        InputSystem* inputSystem_,
        Sequencer* sequencer_,
        MessageQueue* toAudioQueue_
    )
        : coord(coord_)
        , graphicsWrapper(graphicsWrapper_)
        , inputSystem(inputSystem_)
        , sequencer(sequencer_)
        , toAudioQueue(toAudioQueue_)
    {
        auto rectButton = new RectButtonOopElt(
            coord,
            graphicsWrapper,
            inputSystem,
            Rect(coord.x, coord.y + 20, 50, 50)
        );

        rectButton->onClick = [=]() {
            sequencer->playing = !sequencer->playing;
            sequencer->transport = 0;

            rectButton->displayColor = sequencer->playing
                ? rectButton->onClickColor
                : rectButton->color;

            if (sequencer->playing) {
                toAudioQueue->enqueue(PlayMessage());
            }
            else {
                toAudioQueue->enqueue(StopMessage());
            }
        };

        children.push_back(rectButton);
        children.push_back(new TextOopElt(coord, graphicsWrapper, "play"));
    }

    void run() override
    {
        for (const auto& child : children) {
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
