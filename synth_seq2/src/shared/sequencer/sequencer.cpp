#include "sequencer.hpp"

#include <iostream>

#include "src/shared/shared_data.hpp"

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

    // std::cout << "nextStep: " << nextStep << std::endl;

    while (nextStep < transport) {
        // std::cout << "nextStep: " << nextStep << std::endl;
        int step = getStep(nextStep);
        std::cout << "step: " << step << std::endl;

        if (row[step].on) {
            map[nextStep] = row[step].intData;
            std::cout << "add step to map at: " << nextStep << std::endl;
            printMap(map[nextStep]);
        }

        nextStep += samplesPerStep;
    }

    return map;
}
