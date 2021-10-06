#include "app.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "src/lib/readerwriterqueue.h"

#include "src/audio/audio_entrypoint.hpp"
#include "src/shared/audio_queue.hpp"
#include "src/shared/messages.hpp"

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
        &(context.audioQueue),
        &(context.uiQueue)
    );

    setup(context);

    while (!context.inputSystem.uiState.quit) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        handleMessagesFromAudioThread();

        context.graphicsWrapper.clearWindow();
        context.inputSystem.run();

        callback(context);

        sendMessagesToAudioThread();

        context.graphicsWrapper.render();

        nextState();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        Uint32 dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        Uint32 time_to_delay = dur > 10 ? 0 : 10 - dur;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_delay));
    }

    std::cout << "main thread: quitting" << std::endl;

    context.audioQueue.enqueue(QuitMessage());

    audioThread.join();

    context.graphicsWrapper.destroyWindow();
    context.graphicsWrapper.quit();
}

void App::handleMessagesFromAudioThread()
{
    Message message;

    while (context.uiQueue.try_dequeue(message)) {
        if (IntMessage* p = std::get_if<IntMessage>(&message)) {
            context.sharedData.intData[p->key] = p->value;
        }
        else if (BoolMessage* p = std::get_if<BoolMessage>(&message)) {
            context.sharedData.boolData[p->key] = p->value;
        }
    }

    if (context.sharedData.boolData["playing"]) {
        // std::cout << context.sharedData.intData["transport"] << std::endl;

        int t = getStep(context.sharedData.intData["transport"]);
        // std::cout << t << std::endl;

        context.sharedData.sequencer.step = t;
    }

}

void App::sendMessagesToAudioThread()
{
    auto& intData = context.sharedData.intData;

    for (const auto& key : context.sharedData.dirtyInts) {
        IntMessage message(key, intData[key]);
        context.audioQueue.enqueue(message);
    }

    context.sharedData.dirtyInts.clear();

    auto& boolData = context.sharedData.boolData;

    for (const auto& key : context.sharedData.dirtyBools) {
        BoolMessage message(key, boolData[key]);
        context.audioQueue.enqueue(message);
    }

    context.sharedData.dirtyBools.clear();
}

void App::nextState()
{
    context.eltId = 0;
    context.inputSystem.nextState();
}

int getStep(int transport)
{
    int sampsPerSec = 44100;
    int t = transport / sampsPerSec;
    t = t % 16;
    return t;
}
