#pragma once

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
        for (unsigned i = 0; i < this->numSamples; i++) {
            this->buffer[i] = 0;
        }
    }

    void cleanUp()
    {
        delete[] buffer;
    }
};
