#include "sequencer.hpp"

#include <iostream>

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
            map[nextStep] = row[step].intData;
        }

        nextStep += samplesPerStep;
    }

    return map;
}
