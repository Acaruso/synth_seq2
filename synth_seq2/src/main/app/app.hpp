#pragma once

#include <functional>
#include <unordered_map>

#include "lib/readerwriterqueue.h"

#include "app_context.hpp"
#include "src/main/sequencer/sequencer.hpp"
#include "src/main/ui_elements/new/base_elt.hpp"
#include "src/main/ui_elements/new/transport_oop_elt.hpp"
#include "src/shared/messages.hpp"
#include "src/shared/shared.hpp"

class App
{
public:
    AppContext context;
    MessageQueue toAudioQueue;
    MessageQueue toMainQueue;
    Sequencer sequencer;
    BaseElt* transportOopElt;

    App(
        std::function<void(AppContext& context)> setup,
        std::function<void(AppContext& context)> callback
    );

    void run();

private:
    unsigned frameTimeMs{10};
    bool getEventMap{false};
    std::function<void(AppContext& context)> setup;
    std::function<void(AppContext& context)> callback;

    void handleMessagesFromAudioThread();
    void sendMessagesToAudioThread();
    void nextState();
};
