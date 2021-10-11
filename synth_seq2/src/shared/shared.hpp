#pragma once

#include <unordered_map>

using SynthSettings = std::unordered_map<std::string, int>;

inline SynthSettings getDefaultSynthSettings()
{
    SynthSettings synthSettings;

    synthSettings["volume"] = 100;
    synthSettings["modAmount"] = 0;
    synthSettings["attack"] = 0;
    synthSettings["hold"] = 80;
    synthSettings["release"] = 100;
    synthSettings["modAttack"] = 0;
    synthSettings["modHold"] = 80;
    synthSettings["modRelease"] = 100;
    synthSettings["note"] = 60;

    return synthSettings;
}

// key = sample location
using EventMap = std::unordered_map<unsigned, SynthSettings>;
