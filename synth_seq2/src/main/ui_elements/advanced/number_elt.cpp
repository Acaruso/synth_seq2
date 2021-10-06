#include "number_elt.hpp"

#include <string>
#include <vector>

#include "src/main/graphics/color.hpp"
#include "src/main/ui_elements/decorators/base_decorator.hpp"
#include "src/main/ui_elements/decorators/decorator_utils.hpp"

void numberEltInner(EltParams& params)
{
    std::string fontName = params.fontName;
    std::string displayText = params.getDisplayText();

    Coord innerCoord;
    innerCoord.x = params.coord.x + 1;
    innerCoord.y = params.coord.y + 1;

    Font& font = params.ctx.graphicsWrapper.getFont(fontName);

    int maxNumDigits = (int)std::to_string(params.max).size();

    Rect rect{
        innerCoord.x,
        innerCoord.y,
        -1,
        maxNumDigits * font.width + 1,
        font.height - 1,
        red
    };

    params.ctx.graphicsWrapper.drawRect(rect);

    Coord textCoord = innerCoord;
    textCoord.x += 1;
    params.ctx.graphicsWrapper.drawText(displayText, fontName, textCoord);

    Rect outerRect{
        params.coord.x,
        params.coord.y,
        -2,
        rect.w + 2,
        rect.h + 2,
        black
    };

    params.ctx.graphicsWrapper.drawRect(outerRect);
}

void numberElt(EltParams& params)
{
    std::vector<UnboundDecorator> decorators{baseDecorator};
    Elt res = decorate(decorators, params, numberEltInner);
    res(params);
}
