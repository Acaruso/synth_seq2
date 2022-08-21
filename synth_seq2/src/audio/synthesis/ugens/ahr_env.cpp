#include "ahr_env.hpp"

#include "src/audio/audio_util.hpp"

void AHREnv::trigger(double a, double h, double r)
{
    this->a = a;
    this->h = h;
    this->r = r;
    on = true;
    sig = 0.0;
    timer = 0;
}

double AHREnv::get(double t)
{
    if (on) {
        a = a == 0 ? 1 : a;
        h = h == 0 ? 1 : h;
        r = r == 0 ? 1 : r;

        unsigned attackSamps = mstosamps(a);
        unsigned holdSamps = mstosamps(h);
        unsigned releaseSamps = mstosamps(r);

        double attackDelta = 1.0 / (double)attackSamps;
        double releaseDelta = 1.0 / (double)releaseSamps;

        if (timer < attackSamps) {
            sig += attackDelta;
        }
        else if (timer < attackSamps + holdSamps) {
            sig = 1.0;
        }
        else if (timer < attackSamps + holdSamps + releaseSamps) {
            sig -= releaseDelta;
        }
        else {
            sig = 0.0;
            on = false;
        }

        timer += 1;
    }

    return sig;
}
