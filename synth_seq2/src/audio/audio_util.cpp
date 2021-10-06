#include "audio_util.hpp"

#include <stdlib.h>

const unsigned scale = (1 << 23) - 1;

unsigned scaleSignal(double sig)
{
    double f = sig * scale;
    unsigned u = (unsigned)f << 8;
    return u;
}

unsigned mstosamps(double ms)
{
    return (unsigned)(ms * 44.1);
}

// see: https://musicinformationretrieval.com/midi_conversion_table.html
const std::unordered_map<int, double> mtofMap({
    { 60, 261.63 },
    { 61, 277.18 },
    { 62, 293.66 },
    { 63, 311.13 },
    { 64, 329.63 },
    { 65, 349.23 },
    { 66, 369.99 },
    { 67, 392 },
    { 68, 415.3 },
    { 69, 440 },
    { 70, 466.16 },
    { 71, 493.88 },
    { 72, 523.25 }
});

double mtof(int m)
{
    return mtofMap.at(m);
}

double getRand()
{
    return rand() / (RAND_MAX + 1.);
}
