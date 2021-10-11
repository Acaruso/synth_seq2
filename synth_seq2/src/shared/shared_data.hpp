#pragma once

#include <atomic>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "src/shared/messages.hpp"

struct SharedData
{
    std::unordered_map<std::string, int> intData;

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

        intData["note"] = 60;
    }
};

class SharedDataWrapper
{
public:
    SharedData sharedData;
    SharedDataWrapper() {}
};
