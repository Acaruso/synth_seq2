#pragma once

#include "src/main/graphics/color.hpp"

struct Rect
{
    int x{0};
    int y{0};
    int z{0};
    int w{0};
    int h{0};
    Color color;

    Rect() {}

    Rect(int x, int y, int w, int h)
        : x(x), y(y), w(w), h(h)
    {}

    Rect(int x, int y, int z, int w, int h)
        : x(x), y(y), z(z), w(w), h(h)
    {}

    Rect(int x, int y, int w, int h, Color color)
        : x(x), y(y), w(w), h(h), color(color)
    {}

    Rect(int x, int y, int z, int w, int h, Color color)
        : x(x), y(y), z(z), w(w), h(h), color(color)
    {}
};
