#include "audio_entrypoint.hpp"

#include <comdef.h>
#include <iostream>
#include <string>

#include "src/audio/audio_system/audio_system.hpp"
#include "src/audio/synthesis/audio_callback.hpp"

int audioEntrypoint(SharedDataWrapper* sharedDataWrapper)
{
    // initialize COM
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    try {
        AudioSystem audioSystem(audioCallback, sharedDataWrapper);

        // begin main loop
        audioSystem.playAudio();
    }
    catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
