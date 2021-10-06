#include "audio_system.hpp"

#include <iostream>
#include <string>

#include "src/audio/audio_util.hpp"
#include "src/audio/wasapi_wrapper/init.hpp"
#include "src/shared/messages.hpp"

AudioSystem::AudioSystem(
    std::function<double(AudioSystemContext& context)> callback,
    SharedDataWrapper* sharedDataWrapper
)
    : callback(callback)
{
    context.sharedDataWrapper = sharedDataWrapper;

    wasapiWrapper = {};
    init(wasapiWrapper);

    unsigned long samplesPerSecond = wasapiWrapper.waveFormat.Format.nSamplesPerSec;
    context.secondsPerSample = 1.0 / (double)samplesPerSecond;

    bufferSizeBytes = wasapiWrapper.getBufferSizeBytes();
    sampleBuffer = SampleBuffer(bufferSizeBytes);

    bufferSizeFrames = wasapiWrapper.getBufferSizeFrames();
}

void AudioSystem::playAudio()
{
    sampleBuffer.zero();

    wasapiWrapper.writeBuffer(sampleBuffer.buffer, bufferSizeFrames);

    wasapiWrapper.startPlaying();

    // main loop:
    while (!context.quit) {
        WaitForSingleObject(wasapiWrapper.hEvent, INFINITE);

        handleMessagesFromMainThread();

        unsigned numPaddingFrames = wasapiWrapper.getCurrentPadding();

        // recall that each elt of buffer stores 1 sample
        // frame is 2 samples -> 1 for each channel
        // so numSamplesToWrite = (2 * numFramesToWrite)

        unsigned numFramesToWrite = bufferSizeFrames - numPaddingFrames;

        unsigned numSamplesToWrite = numFramesToWrite * 2;

        fillSampleBuffer(numSamplesToWrite);

        wasapiWrapper.writeBuffer(sampleBuffer.buffer, numFramesToWrite);
    }

    wasapiWrapper.stopPlaying();
}

void AudioSystem::handleMessagesFromMainThread()
{
    Message message;

    while (context.sharedDataWrapper->toAudioQueue.try_dequeue(message)) {
        if (std::get_if<QuitMessage>(&message)) {
            std::cout << "audio thread: quitting" << std::endl;
            context.quit = true;
            break;
        }
        else if (NoteMessage* p = std::get_if<NoteMessage>(&message)) {
            context.freq = mtof(p->note);
            context.trig = true;
        }
    }
}

void AudioSystem::fillSampleBuffer(size_t numSamplesToWrite)
{
    unsigned numChannels = 2;

    for (int i = 0; i < numSamplesToWrite; i += numChannels) {
        double sig = callback(context);

        unsigned samp = scaleSignal(sig);

        sampleBuffer.buffer[i] = samp;       // L
        sampleBuffer.buffer[i + 1] = samp;   // R

        ++context.sampleCounter;

        // need to unset trigs each sample
        // only want trig to be on for 1 sample
        context.trig = false;
    }
}

AudioSystem::~AudioSystem()
{
    cleanUp(wasapiWrapper);
    sampleBuffer.cleanUp();
}
