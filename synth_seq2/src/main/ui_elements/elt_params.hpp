#pragma once

#include <functional>
#include <string>
#include <variant>

#include "src/main/app/app_context.hpp"
#include "src/main/graphics/color.hpp"
#include "src/main/graphics/coord.hpp"
#include "src/main/graphics/rect.hpp"

struct EltParams
{
    AppContext& ctx;
    Coord coord;
    Rect rect;
    Color color;
    Color onClickColor;
    Color displayColor;
    int min{0};
    int max{100};
    std::string label;
    std::string fontName{"inconsolata"};

    std::function<void()> onClick{nullptr};
    std::function<void()> onDrag{nullptr};
    std::function<void()> onHold{nullptr};

    std::function<std::string()> getDisplayText{nullptr};

    EltParams(AppContext& ctx) : ctx(ctx) {}
    EltParams(AppContext& ctx, Coord coord) : ctx(ctx), coord(coord) {}
};
