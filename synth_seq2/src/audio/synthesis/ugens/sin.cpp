#include "sin.hpp"

#include <cmath>
#include <cstdio>

#include "src/audio/synthesis/consts.hpp"

void Sin::trigger(
    double a,
    double h,
    double r,
    double freq
) {
    this->freq = freq;
    env.trigger(a, h, r);
}

double Sin::get(double t)
{
    double envSig = env.get(t);

    double sinSig = sin(twoPi * freq * t);
    double outSig = sinSig * envSig;
    return outSig;
}

double Sin::get(double theta, double t)
{
    double envSig = env.get(t);

    double sinSig = sin(twoPi * freq * t + theta);
    double outSig = sinSig * envSig;
    return outSig;
}

SinWT::SinWT()
{
    double phase = 0.0;
    double delta = 1.0 / (double)size;

    // phase ranges from 0 to 1
    // multiply by twoPi to make it range from 0 to twoPi

    for (unsigned i = 0; i < size; i++) {
        wavetable.push_back(sin(phase * twoPi));
        phase += delta;
    }
}

SinWT::SinWT(double secondsPerSample)
    : secondsPerSample(secondsPerSample)
{
    double phase = 0.0;
    double delta = 1.0 / (double)size;

    for (unsigned i = 0; i < size; i++) {
        wavetable.push_back(sin(phase * twoPi));
        phase += delta;
    }
}

void SinWT::trigger(
    double a,
    double h,
    double r,
    double freq
) {
    this->freq = freq;
    env.trigger(a, h, r);
}

double SinWT::get(double t)
{
    double envSig = env.get(t);

    // double sinSig = sin(twoPi * freq * t);

    // instead of scaling by twoPi, scale by size of wavetable
    int i = (int)floor(size * freq * t) % size;
    double sinSig = wavetable[i];

    double outSig = sinSig * envSig;
    return outSig;
}

double SinWT::get(double theta, double t)
{
    int i = (int)floor(phase);
    double sinSig = wavetable[i];
    double envSig = env.get(t);
    double outSig = sinSig * envSig;

    // get next phase
    double phaseInc = ((double)size * freq * secondsPerSample) + theta;
    phase += phaseInc;

    // phase = phase mod size
    double dSize = (double)size;
    while (phase >= dSize) {
        phase -= dSize;
    }

    return outSig;
}
