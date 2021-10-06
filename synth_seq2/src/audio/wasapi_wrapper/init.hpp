#pragma once

#include <sstream>

#include "wasapi_wrapper.hpp"

void init(WasapiWrapper& wasapiWrapper);

void cleanUp(WasapiWrapper& wasapiWrapper);

template <typename T>
inline std::string toHex(const T& t)
{
    std::stringstream ss;
    ss <<"0x" << std::hex << t;
    return ss.str();
}
