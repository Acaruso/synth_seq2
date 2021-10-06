#pragma once

#include <SDL.h>
#include <SDL_FontCache.h>
#include <SDL_ttf.h>

struct Font
{
    FC_Font* p_font;

    int height;
    int width;
    int lineHeight; // lineHeight = font height + whitespace

    Font() {}

    Font(FC_Font* p_font, int height, int width, int lineHeight)
        : p_font(p_font), height(height), width(width), lineHeight(lineHeight)
    {}
};
