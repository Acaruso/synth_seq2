#pragma once

#include <cstring>
#include <stdint.h>

class SampleBuffer
{
public:
    uint32_t* buffer;
    unsigned numSamples;

    SampleBuffer() {}

    SampleBuffer(unsigned bufferSizeBytes) {
        numSamples = bufferSizeBytes / sizeof(uint32_t);
        buffer = new uint32_t[numSamples];
    }

    void zero()
    {
        memset(buffer, 0, numSamples * sizeof(uint32_t));
    }

    void cleanUp()
    {
        delete[] buffer;
    }
};

// class SampleBuffer
// {
// public:
//     unsigned long* buffer;
//     unsigned numSamples;

//     SampleBuffer() {}

//     SampleBuffer(unsigned bufferSizeBytes) {
//         this->numSamples = bufferSizeBytes / sizeof(unsigned long);
//         this->buffer = new unsigned long[this->numSamples];
//     }

//     void zero()
//     {
//         memset(buffer, 0, numSamples * sizeof(unsigned long));
//     }

//     void cleanUp()
//     {
//         delete[] buffer;
//     }
// };
