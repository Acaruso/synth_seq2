#include "rect_button_elt.hpp"

#include "src/main/graphics/color.hpp"
#include "src/main/ui_elements/decorators/base_decorator.hpp"
#include "src/main/ui_elements/decorators/decorator_utils.hpp"
#include "src/main/util.hpp"

void rectButtonEltInner(EltParams& params)
{
    Rect innerRect = Rect(
        params.rect.x + 2,
        params.rect.y + 2,
        params.rect.z + 1,
        params.rect.w - 4,
        params.rect.h - 4
    );

    params.rect.color = black;
    params.ctx.graphicsWrapper.drawRect(params.rect);

    innerRect.color = params.displayColor;
    params.ctx.graphicsWrapper.drawRect(innerRect);
}

void rectButtonElt(EltParams& params)
{
    std::vector<UnboundDecorator> decorators{baseDecorator};
    Elt res = decorate(decorators, params, rectButtonEltInner);
    res(params);
}
