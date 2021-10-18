#include "poly_fm_sin.hpp"

PolyFmSin::PolyFmSin(int size, double secondsPerSample)
{
    for (int i = 0; i < size; i++) {
        oscs.push_back(Operator());
    }
}

void PolyFmSin::trigger(
        double a,
        double h,
        double r,
        double ma,
        double mh,
        double mr,
        double modAmount,
        double freq
) {
    for (auto& osc : oscs) {
        if (!osc.isOn()) {
            osc.trigger(a, h, r, ma, mh, mr, modAmount, freq);
            return;
        }
    }
}

double PolyFmSin::get(double t)
{
    double out = 0.0;
    for (auto& osc : oscs) {
        out += osc.get(t);
    }
    return out;
}
