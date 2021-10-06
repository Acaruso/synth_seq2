#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_FontCache.h>
#include <SDL_ttf.h>

#include "src/main/graphics/draw_system.hpp"
#include "src/main/graphics/font.hpp"
#include "src/main/graphics/image.hpp"
#include "src/main/graphics/coord.hpp"
#include "src/main/graphics/rect.hpp"

class GraphicsWrapper
{
public:
    std::string windowTitle;

    int screenWidth;
    int screenHeight;

    SDL_Window* window;
    SDL_Surface* windowSurface;
    SDL_Renderer* windowRenderer;

    std::unordered_map<std::string, Image> images;
    std::unordered_map<std::string, Font> fonts;

    DrawSystem drawSystem;

    GraphicsWrapper() {}

    void init();
    void clearWindow();

    void drawRect(Rect rect);
    void drawImage(std::string name, Coord coord);
    void drawText(std::string text, std::string fontName, Coord coord);

    void loadImage(std::string name, std::string path);

    void loadFont(
        std::string name,
        std::string path,
        int height,
        int width,
        int lineHeight
    );

    Font& getFont(std::string name);

    void render();
    void destroyWindow();
    void quit();
};
