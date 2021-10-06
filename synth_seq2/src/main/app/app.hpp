#pragma once

#include <functional>

#include "app_context.hpp"

class App
{
public:
    AppContext context;

    App(
        std::function<void(AppContext& context)> setup,
        std::function<void(AppContext& context)> callback
    );

    void run();

private:
    std::function<void(AppContext& context)> setup;
    std::function<void(AppContext& context)> callback;

    void handleMessagesFromAudioThread();
    void nextState();
};
