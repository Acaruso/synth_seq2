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
        for (int i = 0; i < numCells; i++) {
            cells.push_back(Cell());
        }
    }

    SynthSettings& getSynthSettings()
    {
        return synthSettings;
    }
};
