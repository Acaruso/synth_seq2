#pragma once

#include <functional>
#include <vector>

#include "src/main/ui_elements/elt_params.hpp"
#include "src/main/ui_elements/ui_elements_shared.hpp"

// using Elt = std::function<void(EltParams& params)>;
// using UnboundDecorator = std::function<Elt(EltParams&, Elt)>;
// using Decorator = std::function<Elt(Elt)>;

Decorator bindDecorator(EltParams& p, UnboundDecorator unboundDecorator);

Elt decorate(
    std::vector<UnboundDecorator> unboundDecorators,
    EltParams& params,
    Elt elt
);
