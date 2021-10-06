#pragma once

#include <string>
#include <variant>

#include "src/lib/readerwriterqueue.h"
#include "src/shared/messages.hpp"

using AudioQueue = moodycamel::ReaderWriterQueue<Message>;
