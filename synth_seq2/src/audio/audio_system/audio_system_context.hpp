#pragma once

#include <string>
#include <unordered_map>

#include "lib/readerwriterqueue.h"
#include "src/shared/shared_data.hpp"

struct AudioSystemContext
{
    SharedDataWrapper* sharedDataWrapper;

    unsigned long sampleCounter{0};
    unsigned long transport{0};

    unsigned sliceTime{0};
    unsigned long presentTransport{0};
    unsigned long futureTransport{0};

    bool playing{false};

    double secondsPerSample{0.0};

    bool trig{false};
    std::unordered_map<std::string, int> intData;

    double freq{0.0};
    bool quit{false};

    double getTime()
    {
        return double(sampleCounter) * secondsPerSample;
    }
};
