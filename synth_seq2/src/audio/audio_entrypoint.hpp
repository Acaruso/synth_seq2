#pragma once

#include "src/shared/messages.hpp"

int audioEntrypoint(
    MessageQueue* toAudioQueue,
    MessageQueue* toMainQueue
);
