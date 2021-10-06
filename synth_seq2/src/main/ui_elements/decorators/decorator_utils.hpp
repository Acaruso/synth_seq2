#pragma once

#include <functional>
#include <vector>

#include "src/main/ui_elements/elt_params.hpp"
#include "src/main/ui_elements/ui_elements_shared.hpp"

Decorator bindDecorator(EltParams& p, UnboundDecorator unboundDecorator);

Elt decorate(
    std::vector<UnboundDecorator> unboundDecorators,
    EltParams& params,
    Elt elt
);
