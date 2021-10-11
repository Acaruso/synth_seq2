#pragma once

#include "src/shared/messages.hpp"
#include "src/shared/shared_data.hpp"

int audioEntrypoint(
    MessageQueue* toAudioQueue,
    MessageQueue* toMainQueue
);
