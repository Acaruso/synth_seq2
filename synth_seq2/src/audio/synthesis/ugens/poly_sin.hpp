#pragma once

#include <vector>

#include "sin.hpp"

struct PolySin
{
    std::vector<Sin> oscs;

    PolySin(int size);

    void trigger(
        double a,
        double h,
        double r,
        double freq
    );

    double get(double t);
};
