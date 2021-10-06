#pragma once

#include <variant>
#include <vector>

#include "src/main/graphics/draw_commands.hpp"
#include "src/main/graphics/rect.hpp"

class DrawSystem
{
public:
    void push(DrawCommand command);
    void draw(SDL_Renderer* windowRenderer);

private:
    std::vector<DrawCommand> drawQueue;
};
