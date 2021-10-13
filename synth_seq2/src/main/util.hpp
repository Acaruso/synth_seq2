#pragma once

#include <iostream>
#include <string>

#include "src/main/graphics/coord.hpp"
#include "src/main/graphics/rect.hpp"

bool isCoordInsideRect(Coord coord, Rect rect);

int clamp(int x, int min, int max);

std::string pad(int digits, std::string in);

template <typename T>
inline void printMap(T t)
{
    for (auto& elt : t) {
        std::cout << elt.first << " " << elt.second << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
inline void printKeys(T t)
{
    for (auto& elt : t) {
        std::cout << elt.first << std::endl;
    }
    std::cout << std::endl;
}
