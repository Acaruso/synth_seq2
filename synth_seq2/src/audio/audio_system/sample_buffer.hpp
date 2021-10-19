#pragma once

#include <cstring>

class SampleBuffer
{
public:
    unsigned long* buffer;
    unsigned numSamples;

    SampleBuffer() {}

    SampleBuffer(unsigned bufferSizeBytes) {
        this->numSamples = bufferSizeBytes / sizeof(unsigned long);
        this->buffer = new unsigned long[this->numSamples];
    }

    void zero()
    {
        memset(buffer, 0, numSamples * sizeof(unsigned long));
    }

    void cleanUp()
    {
        delete[] buffer;
    }
};
