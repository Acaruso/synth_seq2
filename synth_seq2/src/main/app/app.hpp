#pragma once

#include <functional>

#include "lib/readerwriterqueue.h"

#include "app_context.hpp"
#include "src/shared/messages.hpp"

class App
{
public:
    AppContext context;
    MessageQueue toAudioQueue;
    MessageQueue toMainQueue;

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
    void sendMessagesToAudioThread(EventMap& eventMap);
    void nextState();
};
