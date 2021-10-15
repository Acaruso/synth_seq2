#pragma once

#include <SDL.h>

struct Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color() {}

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        : r(r), g(g), b(b), a(a)
    {}
};

inline bool operator==(const Color& lhs, const Color& rhs)
{
    return (
        lhs.r == rhs.r
        && lhs.g == rhs.g
        && lhs.b == rhs.b
        && lhs.a == rhs.a
    );
}

static Color black = Color(0x00, 0x00, 0x00, 0xFF);
static Color white = Color(0xFF, 0xFF, 0xFF, 0xFF);
static Color blue = Color(0x7B, 0x99, 0xC9, 0xFF);
static Color red = Color(0xF7, 0x8F, 0x8F, 0xFF);
static Color green = Color(0x38, 0xff, 0xdb, 0xFF);
