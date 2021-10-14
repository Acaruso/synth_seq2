#include "draw_commands.hpp"

DrawRectCommand::DrawRectCommand(Rect rect) : rect(rect) {}

void DrawRectCommand::draw(SDL_Renderer* renderer)
{
    SDL_Rect sdl_rect;
    sdl_rect.x = this->rect.x;
    sdl_rect.y = this->rect.y;
    sdl_rect.w = this->rect.w;
    sdl_rect.h = this->rect.h;

    SDL_SetRenderDrawColor(
        renderer,
        this->rect.color.r,
        this->rect.color.g,
        this->rect.color.b,
        this->rect.color.a
    );

    SDL_RenderFillRect(renderer, &sdl_rect);
}

int DrawRectCommand::getZAxis()
{
    return this->rect.z;
}

DrawImageCommand::DrawImageCommand(Image image, Coord coord) : image(image), coord(coord) {}

void DrawImageCommand::draw(SDL_Renderer* renderer)
{
    SDL_Rect sdlRect;
    sdlRect.x = this->coord.x;
    sdlRect.y = this->coord.y;
    sdlRect.w = this->image.w;
    sdlRect.h = this->image.h;

    SDL_RenderCopy(renderer, this->image.p_texture, NULL, &sdlRect);
}

int DrawImageCommand::getZAxis()
{
    return this->coord.z;
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
    return this->coord.z;
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
    return this->start.z;
}
