#include "app.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "lib/readerwriterqueue.h"

#include "src/audio/audio_entrypoint.hpp"

App::App(
    std::function<void(AppContext& context)> setup,
    std::function<void(AppContext& context)> callback
)
    : setup(setup), callback(callback)
{
    toAudioQueue = MessageQueue(16);
    toMainQueue = MessageQueue(16);

    context.toAudioQueue = &toAudioQueue;
    context.toMainQueue = &toMainQueue;
    context.sequencer = &sequencer;
}

void App::run()
{
    std::thread audioThread(
        &audioEntrypoint,
        &toAudioQueue,
        &toMainQueue
    );

    setup(context);

    while (!context.inputSystem.uiState.quit) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        handleMessagesFromAudioThread();

        context.graphicsWrapper.clearWindow();
        context.inputSystem.run();

        callback(context);

        EventMap eventMap = sequencer.getEventMap();
        sendMessagesToAudioThread(eventMap);

        context.graphicsWrapper.render();

        nextState();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        Uint32 dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        Uint32 time_to_delay = dur > frameTimeMs ? 0 : frameTimeMs - dur;
        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_delay));
    }

    std::cout << "main thread: quitting" << std::endl;

    toAudioQueue.enqueue(QuitMessage());

    audioThread.join();

    context.graphicsWrapper.destroyWindow();
    context.graphicsWrapper.quit();
}

void App::handleMessagesFromAudioThread()
{
    Message message;

    while (toMainQueue.try_dequeue(message)) {
        if (IntMessage* p = std::get_if<IntMessage>(&message)) {
            if (p->key == "futureTransport") {
                sequencer.prevTransport = sequencer.transport;
                sequencer.transport = p->value;
                getEventMap = true;
            }
        }
    }
}

void App::sendMessagesToAudioThread(EventMap& eventMap)
{
    EventMapMessage message(eventMap);

    if (getEventMap) {
        toAudioQueue.enqueue(message);
    }
}

void App::nextState()
{
    context.eltId = 0;
    context.inputSystem.nextState();
    getEventMap = false;
}
