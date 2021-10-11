#include "sequencer.hpp"

#include <iostream>

Sequencer::Sequencer()
{
    curSynthSettings = getDefaultSynthSettings();

    int size = 16;
    for (int i = 0; i < size; i++) {
        row.push_back(Cell());
    }
}

Sequencer::Sequencer(int size)
{
    curSynthSettings = getDefaultSynthSettings();

    for (int i = 0; i < size; i++) {
        row.push_back(Cell());
    }
}

Cell& Sequencer::getCell(int i)
{
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

void Sequencer::update()
{
    if (playing) {
        step = getStep(transport);
    }
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

    // nextStep = next step's location in samples
    unsigned nextStep = 0;

    if (prevTransport == 0) {
        nextStep = 0;
    }
    else {
        nextStep = prevTransport + (samplesPerStep - (prevTransport % samplesPerStep));
    }

    while (nextStep < transport) {
        int step = getStep(nextStep);

        if (row[step].on) {
            map[nextStep] = row[step].synthSettings;
        }

        nextStep += samplesPerStep;
    }

    return map;
}
