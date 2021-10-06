#pragma once

#include <vector>

struct Cell
{
    bool on{false};
};

struct Sequencer
{
    std::vector<Cell> row;
    int step{0};

    Sequencer() {}

    Sequencer(int size)
    {
        for (int i = 0; i < size; i++) {
            row.push_back(Cell());
        }
    }
};
