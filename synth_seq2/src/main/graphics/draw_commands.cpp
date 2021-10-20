#include "draw_commands.hpp"

void setRenderDrawColor(SDL_Renderer* renderer, Color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

SDL_Rect makeSdlRect(Rect rect)
{
    return SDL_Rect{rect.x, rect.y, rect.w, rect.h};
}

SDL_Rect makeSdlRect(int x, int y, int w, int h)
{
    return SDL_Rect{x, y, w, h};
}

DrawRectCommand::DrawRectCommand(Rect rect) : rect(rect) {}

void DrawRectCommand::draw(SDL_Renderer* renderer)
{
    SDL_Rect sdl_rect = makeSdlRect(rect);
    setRenderDrawColor(renderer, rect.color);
    SDL_RenderFillRect(renderer, &sdl_rect);
}

int DrawRectCommand::getZAxis()
{
    return rect.z;
}

DrawImageCommand::DrawImageCommand(Image image, Coord coord) : image(image), coord(coord) {}

void DrawImageCommand::draw(SDL_Renderer* renderer)
{
    SDL_Rect sdlRect = makeSdlRect(coord.x, coord.y, image.w, image.h);
    SDL_RenderCopy(renderer, image.p_texture, NULL, &sdlRect);
}

int DrawImageCommand::getZAxis()
{
    return coord.z;
}

DrawTextCommand::DrawTextCommand(std::string text, Font font, Coord coord)
    : text(text), font(font), coord(coord)
{}

void DrawTextCommand::draw(SDL_Renderer* renderer)
{
    FC_Draw(font.p_font, renderer, (float)coord.x, (float)coord.y, text.c_str());
}

int DrawTextCommand::getZAxis()
{
    return coord.z;
}

DrawLineCommand::DrawLineCommand(Coord start, Coord end)
    : start(start), end(end)
{}

void DrawLineCommand::draw(SDL_Renderer* renderer)
{
    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
}

int DrawLineCommand::getZAxis()
{
    return start.z;
}
