#include "sin.hpp"

#include <math.h>

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
