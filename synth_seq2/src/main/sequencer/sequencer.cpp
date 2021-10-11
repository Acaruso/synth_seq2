#include "sequencer.hpp"

#include <iostream>

Sequencer::Sequencer()
{
    int size = 16;
    for (int i = 0; i < size; i++) {
        row.push_back(Cell());
    }
}

Sequencer::Sequencer(int size)
{
    for (int i = 0; i < size; i++) {
        row.push_back(Cell());
    }
}

Cell& Sequencer::getSelectedCell()
{
    return row[selected];
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
