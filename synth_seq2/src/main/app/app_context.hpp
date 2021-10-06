#pragma once

#include <string>

#include "src/lib/readerwriterqueue.h"

#include "src/main/graphics/graphics_wrapper.hpp"
#include "src/main/input_system/input_system.hpp"
#include "src/shared/audio_queue.hpp"
#include "src/shared/ui_queue.hpp"
#include "src/shared/shared_data.hpp"

struct AppContext
{
    GraphicsWrapper graphicsWrapper;
    InputSystem inputSystem;

    AudioQueue audioQueue;
    UIQueue uiQueue;

    int eltId{0};
    int curEltId{0};

    SharedDataWrapper sharedDataWrapper;

    AppContext()
    {
        audioQueue = AudioQueue(16);
        uiQueue = UIQueue(16);
    }

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
};
