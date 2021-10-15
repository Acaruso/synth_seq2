#include "sequencer.hpp"

#include <iostream>

Sequencer::Sequencer()
{
    Track track;

    int numCells = 16;
    for (int i = 0; i < numCells; i++) {
        track.cells.push_back(Cell());
    }

    tracks.push_back(track);
}

bool Sequencer::isPlaying()
{
    return playing;
}

SequencerMode Sequencer::getMode()
{
    return mode;
}

void Sequencer::setMode(SequencerMode mode_)
{
    mode = mode_;
}

Track& Sequencer::getSelectedTrack()
{
    return tracks[selected.row];
}

Cell& Sequencer::getCell(int row, int col)
{
    return tracks[row].cells[col];
}

Cell& Sequencer::getSelectedCell()
{
    return tracks[selected.row].cells[selected.col];
}

Selected Sequencer::getSelected()
{
    return selected;
}

SynthSettings& Sequencer::getSynthSettings()
{
    Track& track = getSelectedTrack();
    Cell& cell = getSelectedCell();

    if (mode == Normal) {
        return track.getSynthSettings();
    }
    else {
        if (cell.on) {
            return cell.getSynthSettings();
        }
        else {
            return track.getSynthSettings();
        }
    }
}

void Sequencer::toggleCell(int row, int col)
{
    mode = Select;
    selected = { row, col };

    Cell& cell = getSelectedCell();
    Track& track = getSelectedTrack();

    if (!cell.on) {
        cell.on = true;
        cell.synthSettings = track.getSynthSettings();
    }
    else {
        cell.on = false;
    }
}

void Sequencer::selectCell(int row, int col)
{
    if (
        selected.row == row
        && selected.col == col
        && mode == Select
    ) {
        mode = Normal;
    }
    else {
        mode = Select;
        selected.row = row;
        selected.col = col;
    }
}

void Sequencer::updateTransport(unsigned newTransport)
{
    prevTransport = transport;
    transport = newTransport;
    step = getStep(transport);
}

int Sequencer::getStep(int transport)
{
    int t = transport / samplesPerStep;
    t = t % 16;
    return t;
}

EventMap Sequencer::getEventMap()
{
    EventMap map;

    unsigned sample = 0;

    if (prevTransport == 0) {
        sample = 0;
    }
    else {
        sample = prevTransport + (samplesPerStep - (prevTransport % samplesPerStep));
    }

    for (; sample < transport; sample += samplesPerStep) {
        int step = getStep(sample);

        Cell& cell = tracks[0].cells[step];

        if (cell.on) {
            map[sample] = cell.synthSettings;
        }
    }

    return map;
}
