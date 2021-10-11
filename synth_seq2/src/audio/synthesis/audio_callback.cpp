#include "src/audio/audio_system/audio_system.hpp"

#include <iostream>

#include "src/audio/audio_util.hpp"
#include "src/audio/synthesis/ugens/poly_fm_sin.hpp"
#include "src/audio/synthesis/ugens/poly_sin.hpp"
#include "src/audio/synthesis/ugens/smooth.hpp"

PolyFmSin polyFmSin(8);
Smooth smooth(32);

double AudioSystem::audioCallback()
{
    double t = getTime();
    double volume = ((double)synthSettings["volume"]) / 100.0;

    if (trig) {
        double freq = mtof(synthSettings["note"]);

        double modAmount = ((double)synthSettings["modAmount"]) / 100.0;

        polyFmSin.trigger(
            (double)synthSettings["attack"] * 2,
            (double)synthSettings["hold"] * 20,
            (double)synthSettings["release"] * 20,
            (double)synthSettings["modAttack"] * 2,
            (double)synthSettings["modHold"] * 20,
            (double)synthSettings["modRelease"] * 20,
            modAmount,
            freq
        );
    }

    double sig = polyFmSin.get(t);

    sig = sig * volume * 0.1;

    return sig;
}
