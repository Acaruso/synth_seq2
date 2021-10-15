#include "sequencer.hpp"

#include <iostream>

Sequencer::Sequencer()
{
    // curSynthSettings = getDefaultSynthSettings();

    // int size = 16;
    // for (int i = 0; i < size; i++) {
    //     row.push_back(Cell());
    // }

    int rid = rows.addRow();
    int tid = tracks.addTrack(rid);

    int size = 16;
    for (int i = 0; i < size; i++) {
        rows.get(rid).push_back(Cell());
    }
}

Sequencer::Sequencer(int size)
{
    // curSynthSettings = getDefaultSynthSettings();

    // for (int i = 0; i < size; i++) {
    //     row.push_back(Cell());
    // }

    int rid = rows.addRow();
    int tid = tracks.addTrack(rid);

    for (int i = 0; i < size; i++) {
        rows.get(rid).push_back(Cell());
    }
}

Cell& Sequencer::getCell(int i)
{
    // return row[i];
    int rid = tracks.get(0).rowId;
    auto row = rows.get(rid);
    return row[i];
}

Cell& Sequencer::getSelectedCell()
{
    return row[selected];
}

SynthSettings& Sequencer::getSynthSettings()
{
    if (mode == Normal) {
        return curSynthSettings;
    }
    else {
        auto& cell = getSelectedCell();
        if (cell.on) {
            return cell.synthSettings;
        }
        else {
            return curSynthSettings;
        }
    }
}

void Sequencer::toggleCell(int i)
{
    mode = Select;

    Cell& cell = getCell(i);

    if (!cell.on) {
        cell.on = true;
        cell.synthSettings = curSynthSettings;
    }
    else {
        cell.on = false;
    }
    selected = i;
}

void Sequencer::selectCell(int i)
{
    if (selected == i && mode == Select) {
        mode = Normal;
    }
    else {
        mode = Select;
        selected = i;
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

        if (row[step].on) {
            map[sample] = row[step].synthSettings;
        }
    }

    return map;
}
