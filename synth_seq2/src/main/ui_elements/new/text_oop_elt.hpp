#pragma once

#include <string>

#include "src/main/ui_elements/new/base_elt.hpp"
#include "src/main/graphics/graphics_wrapper.hpp"

class TextOopElt : public BaseElt
{
public:
    TextOopElt() {}

    TextOopElt(
        Coord coord,
        GraphicsWrapper* graphicsWrapper,
        std::string label
    )
        : coord(coord)
        , graphicsWrapper(graphicsWrapper)
        , label(label)
    {}

    void run() override
    {
        graphicsWrapper->drawText(
            label,
            "inconsolata",
            coord
        );
    }

private:
    Coord coord;
    GraphicsWrapper* graphicsWrapper;
    std::string label;
};
