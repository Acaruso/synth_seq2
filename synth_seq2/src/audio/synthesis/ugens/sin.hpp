#pragma once

#include "src/audio/synthesis/ugens/ahr_env.hpp"

struct Sin
{
    AHREnv env;
    double freq;

    Sin() {};

    void trigger(
        double a,
        double h,
        double r,
        double freq
    );

    double get(double t);

    double get(double theta, double t);
};
