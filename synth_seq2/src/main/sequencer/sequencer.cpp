#include "sequencer.hpp"

#include <iostream>

Sequencer::Sequencer()
{
    Track track;

    int numCells = 16;
    for (int i = 0; i < numCells; i++) {
        track.cells.push_back(Cell());
    }
}

Cell& Sequencer::getCell(int row, int col)
{
    return tracks[row].cells[col];
}

// Cell& Sequencer::getSelectedCell()
// {
//     return row[selected];
// }

// SynthSettings& Sequencer::getSynthSettings()
// {
//     if (mode == Normal) {
//         return curSynthSettings;
//     }
//     else {
//         auto& cell = getSelectedCell();
//         if (cell.on) {
//             return cell.synthSettings;
//         }
//         else {
//             return curSynthSettings;
//         }
//     }
// }

void Sequencer::toggleCell(int row, int col)
{
    mode = Select;

    Cell& cell = getCell(row, col);

    if (!cell.on) {
        cell.on = true;
        // cell.synthSettings = curSynthSettings;
    }
    else {
        cell.on = false;
    }

    selected = { row, col };
}

void Sequencer::selectCell(int row, int col)
{
    // todo fix this
    // if (selected == i && mode == Select) {
    //     mode = Normal;
    // }
    // else {
    //     mode = Select;
    //     selected = i;
    // }
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

// EventMap Sequencer::getEventMap()
// {
//     EventMap map;

//     unsigned sample = 0;

//     if (prevTransport == 0) {
//         sample = 0;
//     }
//     else {
//         sample = prevTransport + (samplesPerStep - (prevTransport % samplesPerStep));
//     }

//     for (; sample < transport; sample += samplesPerStep) {
//         int step = getStep(sample);

//         if (row[step].on) {
//             map[sample] = row[step].synthSettings;
//         }
//     }

//     return map;
// }
