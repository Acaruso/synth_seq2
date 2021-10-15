#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "src/main/sequencer/row.hpp"
#include "src/main/sequencer/track.hpp"
#include "src/shared/shared.hpp"

enum SequencerMode
{
    Normal,
    Select
};

class Sequencer
{
public:
    std::vector<Track> tracks;
    SequencerMode mode{Normal};

    // todo change this
    SynthSettings curSynthSettings;

    bool playing{false};
    int step{0};

    // todo change this
    int selected{0};

    unsigned long transport{0};
    unsigned long prevTransport{0};

    int samplesPerStep{10000};

    Sequencer();
    Sequencer(int size);

    Cell& getCell(int i);
    Cell& getSelectedCell();
    SynthSettings& getSynthSettings();
    void toggleCell(int i);
    void selectCell(int i);
    void updateTransport(unsigned newTransport);
    int getStep(int transport);
    EventMap getEventMap();
};
