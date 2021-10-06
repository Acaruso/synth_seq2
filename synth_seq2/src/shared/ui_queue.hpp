#pragma once

#include <string>
#include <variant>

#include "src/shared/messages.hpp"
#include "src/lib/readerwriterqueue.h"

using UIQueue = moodycamel::ReaderWriterQueue<Message>;
