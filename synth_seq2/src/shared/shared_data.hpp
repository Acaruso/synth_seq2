#pragma once

#include <atomic>
#include <unordered_map>
#include <vector>

#include "src/lib/readerwriterqueue.h"

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
    }
};

class SharedDataWrapper
{
public:
    moodycamel::ReaderWriterQueue<Message> toAudioQueue;
    moodycamel::ReaderWriterQueue<Message> toMainQueue;

    std::vector<SharedData> sharedDataVector;
    std::atomic<std::uint64_t> counter;

    SharedDataWrapper()
    {
        toAudioQueue = moodycamel::ReaderWriterQueue<Message>(16);
        toMainQueue = moodycamel::ReaderWriterQueue<Message>(16);

        sharedDataVector.push_back(SharedData());
        sharedDataVector.push_back(SharedData());
    }

    SharedData& getStable()
    {
        return sharedDataVector[getStableIndex()];
    }

    SharedData& getVolatile()
    {
        return sharedDataVector[getVolatileIndex()];
    }

    void nextState()
    {
        int oldVolatileIndex = getVolatileIndex();
        counter++;
        sharedDataVector[getVolatileIndex()] = sharedDataVector[oldVolatileIndex];
    }

private:
    int getStableIndex()
    {
        return counter % 2;
    }

    int getVolatileIndex()
    {
        return (counter + 1) % 2;
    }
};
