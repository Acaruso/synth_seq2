#include "sin.hpp"

#include <cmath>

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
    double envSig = env.get(t);

    // double sinSig = sin(twoPi * freq * t + theta);

    // int i = (int)floor(size * freq * t + theta) % size;
    double d = size * freq * t + theta;
    double dSize = (double)size;

    // % size
    while (d >= dSize) {
        d -= dSize;
    }

    int i = (int)floor(d);

    // if (env.on) {
    //     printf("i: %d \n", i);
    // }

    double sinSig = wavetable[i];

    double outSig = sinSig * envSig;

    
    return outSig;
}
