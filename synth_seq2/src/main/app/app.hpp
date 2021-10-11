#pragma once

#include <functional>
#include <unordered_map>

#include "lib/readerwriterqueue.h"

#include "app_context.hpp"
#include "src/shared/messages.hpp"
#include "src/main/sequencer/sequencer.hpp"

class App
{
public:
    AppContext context;
    MessageQueue toAudioQueue;
    MessageQueue toMainQueue;
    Sequencer sequencer;
    std::unordered_map<std::string, int> synthSettings;

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
