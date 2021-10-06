#pragma once

struct AHREnv
{
    unsigned timer{0};
    bool on{false};
    double sig{0.0};
    double a;
    double h;
    double r;

    void trigger(double a, double h, double r);

    double get(double t);
};
