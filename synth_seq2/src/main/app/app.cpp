#include "app.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "src/lib/readerwriterqueue.h"

#include "src/audio/audio_entrypoint.hpp"

int getStep(int transport);

App::App(
    std::function<void(AppContext& context)> setup,
    std::function<void(AppContext& context)> callback
)
    : setup(setup), callback(callback)
{
    context.graphicsWrapper.init();
}

void App::run()
{
    std::thread audioThread(
        &audioEntrypoint,
        &(context.sharedDataWrapper)
    );

    setup(context);

    while (!context.inputSystem.uiState.quit) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        handleMessagesFromAudioThread();

        context.graphicsWrapper.clearWindow();
        context.inputSystem.run();

        callback(context);

        context.graphicsWrapper.render();

        nextState();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        Uint32 dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        Uint32 time_to_delay = dur > 10 ? 0 : 10 - dur;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_delay));
    }

    std::cout << "main thread: quitting" << std::endl;

    context.sharedDataWrapper.toAudioQueue.enqueue(QuitMessage());

    audioThread.join();

    context.graphicsWrapper.destroyWindow();
    context.graphicsWrapper.quit();
}

void App::handleMessagesFromAudioThread()
{
    auto& sequencer = context.sharedDataWrapper.getBackBuffer().sequencer;

    Message message;

    while (context.sharedDataWrapper.toMainQueue.try_dequeue(message)) {
        if (IntMessage* p = std::get_if<IntMessage>(&message)) {
            if (p->key == "transport") {
                sequencer.transport = p->value;
            }
        }
    }

    if (sequencer.playing) {
        sequencer.step = getStep(sequencer.transport);
    }
}

void App::nextState()
{
    context.eltId = 0;
    context.inputSystem.nextState();
    context.sharedDataWrapper.nextState();
}

int getStep(int transport)
{
    int sampsPerSec = 44100;
    int t = transport / 10000;
    t = t % 16;
    return t;
}
