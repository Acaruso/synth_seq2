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
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

// vscode
// static Color black = Color(0x1E, 0x1E, 0x1E, 0xFF);
// static Color white = Color(0x9C, 0xDC, 0xFE, 0xFF);
// static Color blue  = Color(0x56, 0x9C, 0xCC, 0xFF);
// static Color red   = Color(0xAC, 0x91, 0x6A, 0xFF);
// static Color green = Color(0x44, 0xC9, 0x94, 0xFF);

// web
static Color black      = Color(0x47, 0x47, 0x49, 0xFF);
static Color white      = Color(0xFF, 0xFB, 0xEF, 0xFF);
static Color offWhite   = Color(0xF2, 0xEE, 0xE3, 0xFF);
// static Color blue       = Color(0x95, 0xD8, 0xE9, 0xFF);
static Color blue       = Color(0x74, 0xA8, 0xB5, 0xFF);

static Color red        = Color(0xF1, 0x82, 0x5B, 0xFF);
static Color green      = Color(0x1F, 0xBA, 0xA8, 0xFF);
static Color lightGreen = Color(0x2A, 0xFF, 0xE6, 0xFF);
static Color darkGreen  = Color(0x12, 0x6D, 0x62, 0xFF);

// original
// static Color black = Color(0x00, 0x00, 0x00, 0xFF);
// static Color white = Color(0xFF, 0xFF, 0xFF, 0xFF);
// static Color blue = Color(0x7B, 0x99, 0xC9, 0xFF);
// static Color red = Color(0xF7, 0x8F, 0x8F, 0xFF);
// static Color green = Color(0x38, 0xff, 0xdb, 0xFF);
