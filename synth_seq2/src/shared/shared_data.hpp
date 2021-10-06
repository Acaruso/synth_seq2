#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "src/shared/sequencer/sequencer.hpp"

struct SharedData
{
    std::unordered_map<std::string, int> intData;
    std::unordered_map<std::string, double> doubleData;
    std::unordered_map<std::string, bool> boolData;
    std::unordered_map<std::string, std::string> stringData;
    std::unordered_set<std::string> dirtyInts;
    std::unordered_set<std::string> dirtyBools;

    Sequencer sequencer;

    SharedData()
    {
        intData["volume"] = 100;
        intData["modAmount"] = 0;

        intData["attack"] = 0;
        intData["hold"] = 80;
        intData["release"] = 100;

        intData["modAttack"] = 0;
        intData["modHold"] = 80;
        intData["modRelease"] = 100;

        intData["freq"] = 100;

        doubleData["env"] = 0.0;

        boolData["playing"] = false;
        intData["transport"] = 0;

        sequencer = Sequencer(16);
    }

    void setInt(std::string key, int value)
    {
        intData[key] = value;
        dirtyInts.insert(key);
    }

    void setBool(std::string key, bool value)
    {
        boolData[key] = value;
        dirtyBools.insert(key);
    }
};
