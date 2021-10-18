#pragma once

#include <sstream>
#include <string>
#include <unordered_map>

using SynthSettings = std::unordered_map<std::string, int>;

inline SynthSettings getDefaultSynthSettings()
{
    SynthSettings synthSettings;

    synthSettings["volume"] = 100;
    synthSettings["modAmount"] = 0;
    synthSettings["attack"] = 2;
    synthSettings["hold"] = 20;
    synthSettings["release"] = 10;
    synthSettings["modAttack"] = 2;
    synthSettings["modHold"] = 20;
    synthSettings["modRelease"] = 10;
    synthSettings["note"] = 60;

    return synthSettings;
}

struct Event
{
    unsigned sample;
    int track;
    SynthSettings synthSettings;
};

inline std::string getEventKey(unsigned sample, int track)
{
    return std::to_string(sample) + "," + std::to_string(track);
}

using EventMap = std::unordered_map<std::string, Event>;
