#pragma once

#include <string>

#include "lib/readerwriterqueue.h"

#include "src/main/graphics/graphics_wrapper.hpp"
#include "src/main/input_system/input_system.hpp"
#include "src/shared/shared_data.hpp"

struct AppContext
{
    GraphicsWrapper graphicsWrapper;
    InputSystem inputSystem;

    MessageQueue* toAudioQueue;
    MessageQueue* toMainQueue;
    Sequencer* sequencer;
    std::unordered_map<std::string, int>* synthSettings;

    int eltId{0};
    int curEltId{0};

    SharedDataWrapper sharedDataWrapper;

    void registerElt()
    {
        eltId++;
    }

    int getEltId()
    {
        return eltId;
    }

    int getDragAmount()
    {
        return inputSystem.prevUiState.mousePos.y - inputSystem.uiState.mousePos.y;
    }

    UiState& getUiState()
    {
        return inputSystem.uiState;
    }
};
