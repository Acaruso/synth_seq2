#pragma once

#include "src/lib/readerwriterqueue.h"
#include "src/shared/audio_queue.hpp"
#include "src/shared/ui_queue.hpp"
#include "src/shared/shared_data.hpp"

struct AudioSystemContext
{
    AudioQueue* audioQueue;
    UIQueue* uiQueue;
    SharedData sharedData;

    unsigned long sampleCounter{0};
    double secondsPerSample{0.0};
    bool trig{false};
    double freq{0.0};
    bool quit{false};

    double getTime()
    {
        return double(sampleCounter) * secondsPerSample;
    }
};
