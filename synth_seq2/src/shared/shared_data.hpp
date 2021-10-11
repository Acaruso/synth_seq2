#pragma once

#include <atomic>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "lib/readerwriterqueue.h"

#include "src/shared/sequencer/sequencer.hpp"
#include "src/shared/messages.hpp"

struct SharedData
{
    std::unordered_map<std::string, int> intData;
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

        intData["note"] = 60;
    }
};

class SharedDataWrapper
{
public:
    // moodycamel::ReaderWriterQueue<Message> toAudioQueue;
    // moodycamel::ReaderWriterQueue<Message> toMainQueue;

    SharedData sharedData;

    SharedDataWrapper()
    {
        // toAudioQueue = moodycamel::ReaderWriterQueue<Message>(16);
        // toMainQueue = moodycamel::ReaderWriterQueue<Message>(16);
    }
};
