#pragma once

#include <functional>

#include "lib/readerwriterqueue.h"

#include "src/audio/audio_system/audio_system_context.hpp"
#include "src/audio/audio_system/sample_buffer.hpp"
#include "src/audio/wasapi_wrapper/wasapi_wrapper.hpp"
#include "src/shared/shared_data.hpp"

class AudioSystem
{
public:
    AudioSystemContext context;

    std::function<double(AudioSystemContext& context)> callback;

    AudioSystem(
        std::function<double(AudioSystemContext& context)> callback,
        SharedDataWrapper* sharedDataWrapper
    );

    void playAudio();
    void handleMessagesFromMainThread();
    void sendMessagesToMainThread();
    ~AudioSystem();

private:
    WasapiWrapper wasapiWrapper;
    SampleBuffer sampleBuffer;
    unsigned bufferSizeBytes;
    unsigned bufferSizeFrames;

    void setTrigs();
    void unsetTrigs();
    void fillSampleBuffer(size_t numSamplesToWrite);
};
