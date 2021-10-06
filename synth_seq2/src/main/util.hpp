#pragma once

#include <string>

#include "src/main/graphics/coord.hpp"
#include "src/main/graphics/rect.hpp"

bool isCoordInsideRect(Coord coord, Rect rect);

int clamp(int x, int min, int max);

std::string pad(int digits, std::string in);
