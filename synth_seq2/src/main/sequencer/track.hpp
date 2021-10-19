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
        synthSettings = makeSynthSettings();
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
        synthSettings = makeSynthSettings();
        int numCells = 16;
        cells = std::vector<Cell>(numCells, Cell());
    }

    SynthSettings& getSynthSettings()
    {
        return synthSettings;
    }
};
