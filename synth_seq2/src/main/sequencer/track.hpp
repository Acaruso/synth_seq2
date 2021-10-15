#pragma once

#include <vector>

#include "src/shared/shared.hpp"

struct Track
{
    SynthSettings synthSettings;
    std::vector<Row> rows;

    Track()
    {
        synthSettings = getDefaultSynthSettings();
    }
};
