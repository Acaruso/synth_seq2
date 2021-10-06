#pragma once

#include <vector>

struct Cell
{
    bool on{false};
};

struct Sequencer
{
    bool playing{false};
    int step{0};
    std::vector<Cell> row;

    Sequencer()
    {
        int size = 16;
        for (int i = 0; i < size; i++) {
            row.push_back(Cell());
        }
    }

    Sequencer(int size)
    {
        for (int i = 0; i < size; i++) {
            row.push_back(Cell());
        }
    }
};
