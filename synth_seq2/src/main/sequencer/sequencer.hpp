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

    Cell()
    {
        synthSettings = getDefaultSynthSettings();
    }
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

    Sequencer();
    Sequencer(int size);

    Cell& getSelectedCell();
    void update();
    int getStep(int transport);
    EventMap getEventMap();
};
