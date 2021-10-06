#pragma once

#include <functional>

#include "app_context.hpp"

class App
{
public:
    AppContext context;

    std::function<void(AppContext& context)> setup;
    std::function<void(AppContext& context)> callback;

    App(
        std::function<void(AppContext& context)> setup,
        std::function<void(AppContext& context)> callback
    );

    void run();

private:
    void handleMessagesFromAudioThread();
    void sendMessagesToAudioThread();
    void nextState();
};
