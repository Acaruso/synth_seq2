#include "number_with_label_elt.hpp"

#include <string>

#include "src/main/ui_elements/advanced/number_elt.hpp"
#include "src/main/ui_elements/basic/rect_outline_elt.hpp"
#include "src/main/util.hpp"

void numberWithLabelElt(EltParams& params)
{
    auto& context = params.ctx;
    std::string label = params.label;
    std::string key = params.key;
    Coord coord = params.coord;

    // label //////////////////////////
    auto& synthSettings = context.sequencer->getSynthSettings();

    std::string fontName = "inconsolata";
    Font& font = context.graphicsWrapper.getFont(fontName);
    Coord labelCoord = coord;
    labelCoord.x += 4;
    context.graphicsWrapper.drawText(label, fontName, labelCoord);

    // number rect ////////////////////
    EltParams p(context);

    p.coord = Coord{
        coord.x + 100,
        coord.y
    };

    p.min = 0;
    p.max = 100;

    int maxNumDigits = (int)std::to_string(p.max).size();

    p.fontName = fontName;

    p.rect = Rect{
        p.coord.x,
        p.coord.y,
        maxNumDigits * font.width,
        font.height
    };

    int& data = synthSettings[key];

    p.getDisplayText = [&]() {
        return pad(maxNumDigits, std::to_string(data));
    };

    p.onDrag = [&]() {
        data += context.getDragAmount() / 2;
        data = clamp(data, p.min, p.max);
    };

    numberElt(p);

    // outline rect ///////////////////
    Rect outerRect{
        coord.x,
        coord.y,
        100,
        18
    };

    EltParams p2(context);
    p2.rect = outerRect;
    rectOutlineElt(p2);
}
