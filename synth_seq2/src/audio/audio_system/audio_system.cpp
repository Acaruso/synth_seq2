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
    std::cout << "buffer size frames: " << bufferSizeFrames << std::endl;

    unsigned padding = wasapiWrapper.getCurrentPadding();
    std::cout << "padding: " << padding << std::endl;

    context.sliceTime = bufferSizeFrames * 4;
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

        std::cout << "padding loop: " << numPaddingFrames << std::endl;

        // recall that each elt of buffer stores 1 sample
        // frame is 2 samples -> 1 for each channel
        // so numSamplesToWrite = (2 * numFramesToWrite)

        unsigned numFramesToWrite = bufferSizeFrames - numPaddingFrames;

        std::cout << "bufferSizeFrames: " << bufferSizeFrames << std::endl;

        std::cout << "numFramesToWrite: " << numFramesToWrite << std::endl;

        unsigned numSamplesToWrite = numFramesToWrite * 2;

        fillSampleBuffer(numSamplesToWrite);

        wasapiWrapper.writeBuffer(sampleBuffer.buffer, numFramesToWrite);

        // std::cout << "samp counter" << context.sampleCounter << std::endl;
        sendMessagesToMainThread();
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
        else if (std::get_if<PlayMessage>(&message)) {
            context.playing = true;
        }
        else if (std::get_if<StopMessage>(&message)) {
            context.playing = false;
        }
        else if (NoteMessage* p = std::get_if<NoteMessage>(&message)) {
            context.freq = mtof(p->note);
            context.trig = true;
        }
    }
}

void AudioSystem::sendMessagesToMainThread()
{
    auto& sequencer = context.sharedDataWrapper->getFrontBuffer().sequencer;

    // std::cout << "audio futureTransport: " << context.futureTransport << std::endl;
    // std::cout << "audio sliceTime: " << context.sliceTime << std::endl;
    // std::cout << "audio: " << context.futureTransport % context.sliceTime << std::endl;
    // std::cout << "audio: " << context.sliceTime << std::endl;

    if (context.playing && context.futureTransport % context.sliceTime == 0) {
        std::cout << "audio sending message" << std::endl;
        context.sharedDataWrapper->toMainQueue.enqueue(
            IntMessage("futureTransport", context.futureTransport)
        );
    }
}

void AudioSystem::fillSampleBuffer(size_t numSamplesToWrite)
{
    auto& sequencer = context.sharedDataWrapper->getFrontBuffer().sequencer;

    unsigned numChannels = 2;

    for (int i = 0; i < numSamplesToWrite; i += numChannels) {
        setTrigs();

        // std::cout << "fill sample buffer:" << std::endl;
        // printMap(context.intData);

        double sig = callback(context);

        unsigned samp = scaleSignal(sig);

        sampleBuffer.buffer[i] = samp;       // L
        sampleBuffer.buffer[i + 1] = samp;   // R

        ++context.sampleCounter;

        if (sequencer.playing) {
            if (context.futureTransport >= (context.sliceTime * 2)) {
                ++context.presentTransport;
            }
            ++context.futureTransport;
        }
        else {
            context.futureTransport = 0;
            context.presentTransport = 0;
        }

        // need to unset trigs each sample
        // only want trig to be on for 1 sample
        unsetTrigs();
    }
}

void AudioSystem::setTrigs()
{
    auto& sequencer = context.sharedDataWrapper->getFrontBuffer().sequencer;

    int step = sequencer.getStep(context.transport);

    if (
        sequencer.playing
        && context.transport % sequencer.samplesPerStep == 0
        && sequencer.row[step].on
    ) {
        context.trig = true;
        // printMap(sequencer.row[step].intData);
        context.intData = sequencer.row[step].intData;
        // std::cout << "set trigs:" << std::endl;
        // printMap(context.intData);
    }
}

void AudioSystem::unsetTrigs()
{
    context.trig = false;
}

AudioSystem::~AudioSystem()
{
    cleanUp(wasapiWrapper);
    sampleBuffer.cleanUp();
}
