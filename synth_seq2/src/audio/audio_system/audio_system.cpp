#include "audio_system.hpp"

#include <iostream>
#include <string>

#include "src/audio/audio_util.hpp"
#include "src/audio/wasapi_wrapper/init.hpp"

AudioSystem::AudioSystem(
    MessageQueue* toAudioQueue,
    MessageQueue* toMainQueue
)
    : toAudioQueue(toAudioQueue), toMainQueue(toMainQueue)
{
    wasapiWrapper = {};
    init(wasapiWrapper);

    unsigned long samplesPerSecond = wasapiWrapper.waveFormat.Format.nSamplesPerSec;
    secondsPerSample = 1.0 / (double)samplesPerSecond;

    bufferSizeBytes = wasapiWrapper.getBufferSizeBytes();
    sampleBuffer = SampleBuffer(bufferSizeBytes);

    bufferSizeFrames = wasapiWrapper.getBufferSizeFrames();

    periodSizeFrames = wasapiWrapper.getPeriodSizeFrames();

    sliceTime = periodSizeFrames * 4;
    leadTime = sliceTime * 2;
}

void AudioSystem::playAudio()
{
    sampleBuffer.zero();

    wasapiWrapper.writeBuffer(sampleBuffer.buffer, bufferSizeFrames);

    wasapiWrapper.startPlaying();

    // main loop:
    while (!quit) {
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

        sendMessagesToMainThread();
    }

    wasapiWrapper.stopPlaying();
}

void AudioSystem::handleMessagesFromMainThread()
{
    Message message;

    while (toAudioQueue->try_dequeue(message)) {
        if (std::get_if<QuitMessage>(&message)) {
            std::cout << "audio thread: quitting" << std::endl;
            quit = true;
            break;
        }
        else if (std::get_if<PlayMessage>(&message)) {
            playing = true;
        }
        else if (std::get_if<StopMessage>(&message)) {
            playing = false;
        }
        else if (NoteMessage* p = std::get_if<NoteMessage>(&message)) {
            freq = mtof(p->note);
            trig = true;
        }
        else if (EventMapMessage* p = std::get_if<EventMapMessage>(&message)) {
            // merge maps
            eventMap.insert(p->eventMap.begin(), p->eventMap.end());
        }
    }
}

void AudioSystem::sendMessagesToMainThread()
{
    if (playing && futureTransport % sliceTime == 0) {
        toMainQueue->enqueue(
            IntMessage("futureTransport", futureTransport)
        );
    }
}

void AudioSystem::fillSampleBuffer(size_t numSamplesToWrite)
{
    unsigned numChannels = 2;

    for (int i = 0; i < numSamplesToWrite; i += numChannels) {
        setTrigs();

        double sig = audioCallback();

        unsigned samp = scaleSignal(sig);

        sampleBuffer.buffer[i] = samp;       // L
        sampleBuffer.buffer[i + 1] = samp;   // R

        ++sampleCounter;

        if (playing) {
            if (futureTransport >= leadTime) {
                ++presentTransport;
            }
            ++futureTransport;
        }
        else {
            futureTransport = 0;
            presentTransport = 0;
        }

        // need to unset trigs each sample
        // only want trig to be on for 1 sample
        unsetTrigs();
    }
}

void AudioSystem::setTrigs()
{
    // check if presentTransport is in eventMap
    if (eventMap.find(presentTransport) != eventMap.end()) {
        trig = true;
        synthSettings = eventMap[presentTransport];
        synthSettings["note"] = 60;
        eventMap.erase(presentTransport);
    }

    // auto& sequencer = sharedDataWrapper->getFrontBuffer().sequencer;
    // int step = sequencer.getStep(transport);
    // if (
    //     sequencer.playing
    //     && transport % sequencer.samplesPerStep == 0
    //     && sequencer.row[step].on
    // ) {
    //     trig = true;
    //     intData = sequencer.row[step].intData;
    // }
}

void AudioSystem::unsetTrigs()
{
    trig = false;
}

AudioSystem::~AudioSystem()
{
    cleanUp(wasapiWrapper);
    sampleBuffer.cleanUp();
}
