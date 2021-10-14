#pragma once

#include <string>

#include "src/main/ui_elements/new/base_elt.hpp"
#include "src/main/graphics/graphics_wrapper.hpp"

class TextOopElt : public BaseElt
{
public:
    TextOopElt() {}

    TextOopElt(
        GraphicsWrapper* graphicsWrapper,
        std::string label
    )
        : graphicsWrapper(graphicsWrapper)
        , label(label)
    {}

    void run(Coord coord) override
    {
        graphicsWrapper->drawText(
            label,
            "inconsolata",
            coord
        );
    }

private:
    GraphicsWrapper* graphicsWrapper;
    std::string label;
};
