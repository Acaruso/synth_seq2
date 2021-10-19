#pragma once

#include <algorithm>
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

    SynthSettings& getSynthSettings()
    {
        return synthSettings;
    }
};

struct Track
{
    SynthSettings synthSettings;
    std::vector<Cell> cells;

    Track()
    {
        synthSettings = getDefaultSynthSettings();
        int numCells = 16;
        cells = std::vector<Cell>(numCells, Cell());
    }

    SynthSettings& getSynthSettings()
    {
        return synthSettings;
    }
};
