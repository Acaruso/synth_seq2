#pragma once

#include <string>
#include <unordered_map>
#include <vector>

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
    Selected selected;
    bool playing{false};
    int step{0};
    int numSteps{16};
    int samplesPerStep{10000};

    int curPulse{0};
    int PPQN{24};
    int samplesPerPulse{0};

    unsigned long prevTransport{0};
    unsigned long transport{0};
    int octave{4};
    int bpm{120};
    int sampleRate{44100};

    Sequencer();
    bool isPlaying();
    void play();
    void stop();
    SequencerMode getMode();
    void setMode(SequencerMode);
    Track& getSelectedTrack();
    Cell& getCell(int row, int col);
    Cell& getSelectedCell();
    Selected getSelected();
    SynthSettings& getSynthSettings();
    void toggleCell(int row, int col);
    void selectCell(int row, int col);
    int getBpm();
    void setBpm(int newBpm);
    void updateTransport(unsigned newTransport);
    int getStep(int transport);
    EventMap getEventMap();
    void addTrack();
    void nextState();
};
