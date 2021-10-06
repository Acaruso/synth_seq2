#pragma once

#include <vector>

#include "sin.hpp"

struct Operator
{
    Sin carrier;
    Sin modulator;
    double modAmount;

    Operator() {}

    bool isOn()
    {
        return (carrier.env.on || modulator.env.on);
    }

    void trigger(
        double a,
        double h,
        double r,
        double ma,
        double mh,
        double mr,
        double modAmount,
        double freq
    ) {
        this->modAmount = modAmount;
        carrier.trigger(a, h, r, freq);
        modulator.trigger(ma, mh, mr, freq);
    }

    double get(double t)
    {
        double modSig = modulator.get(t) * modAmount * 4;
        double carSig = carrier.get(modSig, t);
        return carSig;
    }
};

struct PolyFmSin
{
    std::vector<Operator> oscs;

    PolyFmSin(int size);

    void trigger(
        double a,
        double h,
        double r,
        double ma,
        double mh,
        double mr,
        double modAmount,
        double freq
    );

    double get(double t);
};
