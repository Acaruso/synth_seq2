#pragma once

#include <unordered_map>

using SynthSettings = std::unordered_map<std::string, int>;

// key = sample location
using EventMap = std::unordered_map<unsigned, SynthSettings>;
