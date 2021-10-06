#include "poly_sin.hpp"

PolySin::PolySin(int size)
{
    for (int i = 0; i < size; i++) {
        oscs.push_back(Sin());
    }
}

void PolySin::trigger(
    double a,
    double h,
    double r,
    double freq
) {
    for (auto& osc : oscs) {
        if (!osc.env.on) {
            osc.trigger(a, h, r, freq);
            return;
        }
    }
}

double PolySin::get(double t)
{
    double out = 0.0;
    for (auto& osc : oscs) {
        out += osc.get(t);
    }
    return out;
}
