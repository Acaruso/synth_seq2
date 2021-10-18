#pragma once

#include <functional>
#include <vector>

#include "lib/readerwriterqueue.h"

#include "src/audio/audio_system/sample_buffer.hpp"
#include "src/audio/wasapi_wrapper/wasapi_wrapper.hpp"
#include "src/shared/messages.hpp"
#include "src/shared/shared.hpp"

class AudioSystem
{
public:
    MessageQueue* toAudioQueue;
    MessageQueue* toMainQueue;

    AudioSystem(
        MessageQueue* toAudioQueue,
        MessageQueue* toMainQueue
    );

    void playAudio();
    ~AudioSystem();

private:
    WasapiWrapper wasapiWrapper;
    SampleBuffer sampleBuffer;
    unsigned bufferSizeBytes;
    unsigned bufferSizeFrames;
    unsigned periodSizeFrames;

    // from context /////////////////////////////

    unsigned long sampleCounter{0};
    unsigned long transport{0};

    unsigned sliceTime{0};
    unsigned leadTime{0};
    unsigned long presentTransport{0};
    unsigned long futureTransport{0};

    bool playing{false};

    double secondsPerSample{0.0};

    bool trig{false};
    SynthSettings synthSettings;

    EventMap eventMap;

    int numTracks{4};
    std::vector<bool> trigs;
    std::vector<SynthSettings> vSynthSettings;

    bool quit{false};

    double getTime()
    {
        return double(sampleCounter) * secondsPerSample;
    }

    /////////////////////////////////////////////

    double audioCallback();
    void handleMessagesFromMainThread();
    void sendMessagesToMainThread();
    void setTrigs();
    void unsetTrigs();
    void fillSampleBuffer(size_t numSamplesToWrite);
};
