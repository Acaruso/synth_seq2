#pragma once

#include <vector>

struct Cell
{
    bool on{false};
};

inline int getStep(int transport)
{
    int sampsPerSec = 44100;
    int t = transport / 10000;
    t = t % 16;
    return t;
}

struct Sequencer
{
    bool playing{false};
    int step{0};
    unsigned long transport{0};
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

    void update()
    {
        if (playing) {
            step = getStep(transport);
        }
    }
};
