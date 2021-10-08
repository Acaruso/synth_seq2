#pragma once

#include <string>
#include <unordered_map>
#include <vector>

enum SequencerMode
{
    Normal,
    Select
};

struct Cell
{
    bool on{false};
    std::unordered_map<std::string, int> intData;
};

class Sequencer
{
public:
    bool playing{false};
    int step{0};
    SequencerMode mode{Normal};
    int selected{0};
    unsigned long transport{0};
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

    // recall that sequencer.step and sequencer.transport are only used in main thread
    // audio thread has its own, more accurate transport variable on audioContext object
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
};
