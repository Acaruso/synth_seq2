#include "audio_callback.hpp"

#include <iostream>

#include "src/audio/audio_util.hpp"
#include "src/audio/synthesis/ugens/poly_fm_sin.hpp"
#include "src/audio/synthesis/ugens/poly_sin.hpp"
#include "src/audio/synthesis/ugens/smooth.hpp"

PolyFmSin polyFmSin(8);
Smooth smooth(32);

double audioCallback(AudioSystemContext& context)
{
    auto& intData = context.intData;

    double t = context.getTime();
    double volume = ((double)intData["volume"]) / 100.0;

    if (context.trig) {
        // double freq = context.freq;
        // printMap(context.intData);
        double freq = mtof(intData["note"]);

        double modAmount = ((double)intData["modAmount"]) / 100.0;

        polyFmSin.trigger(
            (double)intData["attack"] * 2,
            (double)intData["hold"] * 20,
            (double)intData["release"] * 20,
            (double)intData["modAttack"] * 2,
            (double)intData["modHold"] * 20,
            (double)intData["modRelease"] * 20,
            modAmount,
            freq
        );
    }

    double sig = polyFmSin.get(t);

    sig = sig * volume * 0.1;

    return sig;
}
