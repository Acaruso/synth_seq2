#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "src/shared/shared.hpp"

enum SequencerMode
{
    Normal,
    Select
};

struct Cell
{
    bool on{false};
    SynthSettings synthSettings;
};

class Sequencer
{
public:
    bool playing{false};
    int step{0};
    SequencerMode mode{Normal};
    int selected{0};
    unsigned long transport{0};
    unsigned long prevTransport{0};
    int samplesPerStep{10000};

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

    Cell& getCurrentCell()
    {
        return row[selected];
    }

    void update()
    {
        if (playing) {
            step = getStep(transport);
        }
    }

    int getStep(int transport)
    {
        int t = transport / samplesPerStep;
        t = t % 16;
        return t;
    }

    EventMap getEventMap();
};
