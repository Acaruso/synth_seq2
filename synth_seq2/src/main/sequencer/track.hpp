#pragma once

#include <vector>

#include "src/shared/shared.hpp"

struct Cell
{
    bool on{false};
    SynthSettings synthSettings;

    Cell()
    {
        synthSettings = getDefaultSynthSettings();
    }
};

struct Track
{
    SynthSettings synthSettings;
    std::vector<Cell> cells;

    Track()
    {
        synthSettings = getDefaultSynthSettings();
    }
};
