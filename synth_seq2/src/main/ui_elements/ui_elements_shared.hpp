#pragma once

#include <functional>

#include "src/main/ui_elements/elt_params.hpp"

using Elt = std::function<void(EltParams& params)>;
using UnboundDecorator = std::function<Elt(EltParams&, Elt)>;
using Decorator = std::function<Elt(Elt)>;
