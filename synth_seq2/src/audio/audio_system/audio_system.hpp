#pragma once

#include <functional>

#include "src/lib/readerwriterqueue.h"

#include "src/audio/audio_system/audio_system_context.hpp"
#include "src/audio/audio_system/sample_buffer.hpp"
#include "src/audio/wasapi_wrapper/wasapi_wrapper.hpp"
#include "src/shared/audio_queue.hpp"
#include "src/shared/ui_queue.hpp"

class AudioSystem
{
public:
    AudioSystemContext context;

    std::function<double(AudioSystemContext& context)> callback;

    AudioSystem(
        std::function<double(AudioSystemContext& context)> callback,
        AudioQueue* audioQueue,
        UIQueue* uiQueue
    );

    void playAudio();
    ~AudioSystem();

private:
    WasapiWrapper wasapiWrapper;
    SampleBuffer sampleBuffer;
    unsigned bufferSizeBytes;
    unsigned bufferSizeFrames;

    void handleMessagesFromMainThread();
    void sendMessagesToMainThread();
    void fillSampleBuffer(size_t numSamplesToWrite);
};
