#pragma once

#include "src/lib/readerwriterqueue.h"
#include "src/shared/shared_data.hpp"

struct AudioSystemContext
{
    SharedDataWrapper* sharedDataWrapper;

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
