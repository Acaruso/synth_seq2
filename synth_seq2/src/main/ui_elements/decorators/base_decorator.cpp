#include "base_decorator.hpp"

#include "src/main/ui_elements/decorators/clickable.hpp"
#include "src/main/ui_elements/decorators/decorator_utils.hpp"
#include "src/main/ui_elements/decorators/draggable.hpp"
#include "src/main/ui_elements/decorators/holdable.hpp"

Elt baseDecorator(EltParams& params, Elt elt)
{
    params.ctx.registerElt();

    std::vector<UnboundDecorator> decorators;

    if (params.onClick) {
        decorators.push_back(clickable);
    }

    if (params.onDrag) {
        decorators.push_back(draggable);
    }

    if (params.onHold) {
        decorators.push_back(holdable);
    }

    Elt decoratedElt = decorate(decorators, params, elt);
    return decoratedElt;
}
