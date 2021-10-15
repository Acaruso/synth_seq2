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

struct Selected
{
    int row{0};
    int col{0};
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

    Selected selected;

    unsigned long transport{0};
    unsigned long prevTransport{0};

    int samplesPerStep{10000};

    Sequencer();

    bool isPlaying();
    SequencerMode getMode();
    void setMode(SequencerMode);
    Track& getSelectedTrack();
    Cell& getCell(int row, int col);
    Cell& getSelectedCell();
    Selected getSelected();
    // SynthSettings& getSynthSettings();
    void toggleCell(int row, int col);
    void selectCell(int row, int col);
    void updateTransport(unsigned newTransport);
    int getStep(int transport);
    // EventMap getEventMap();
};
