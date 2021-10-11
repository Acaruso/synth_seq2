#include "audio_entrypoint.hpp"

#include <comdef.h>
#include <iostream>
#include <string>

#include "src/audio/audio_system/audio_system.hpp"

int audioEntrypoint(
    MessageQueue* toAudioQueue,
    MessageQueue* toMainQueue
) {
    // initialize COM
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    try {
        AudioSystem audioSystem(toAudioQueue, toMainQueue);

        // begin main loop
        audioSystem.playAudio();
    }
    catch(std::exception& ex) {
        std::cout << "Audio error: " << ex.what() << std::endl;
    }

    return 0;
}
