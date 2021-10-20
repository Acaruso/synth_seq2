#pragma once

#include <Audioclient.h>
#include <iostream>
#include <mmdeviceapi.h>

class WasapiWrapper
{
public:
    IMMDeviceEnumerator* enumerator;
    IMMDevice* device;
    IAudioClient3* audioClient;
    IAudioRenderClient* renderClient;
    WAVEFORMATEXTENSIBLE waveFormat;
    HANDLE hEvent;
    HANDLE hTask;

    unsigned getBufferSizeFrames();
    unsigned getBufferSizeBytes();
    unsigned getCurrentPadding();
    unsigned getPeriodSizeFrames();
    void waitForSignal();
    unsigned getNumFramesToWrite();
    unsigned getNumSamplesToWrite();
    void writeBuffer(unsigned long* source, unsigned numFramesToWrite);
    void startPlaying();
    void stopPlaying();
};
