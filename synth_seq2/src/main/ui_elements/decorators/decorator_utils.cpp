#include "decorator_utils.hpp"

// UnboundDecorator is a function that takes EltParams and Elt as input,
// but in order to compose decorators, we need to get rid of EltParams so that
// decorator just takes one argument.
// So we need to "bind" the EltParams argument.
// This is the same as partial application but just C++ style.
// We're partially applying the EltParams argument.
// note that we don't actually call the lambda here, we just create it and return it.

Decorator bindDecorator(EltParams& p, UnboundDecorator unboundDecorator)
{
    Decorator decorator = [&p, unboundDecorator](Elt elt) { return unboundDecorator(p, elt); };
    return decorator;
}

Elt decorate(
    std::vector<UnboundDecorator> unboundDecorators,
    EltParams& params,
    Elt elt
) {
    Elt accumulator = elt;

    // compose decorators
    for (auto& unboundDecorator : unboundDecorators) {
        Decorator decorator = bindDecorator(params, unboundDecorator);
        accumulator = decorator(accumulator);
    }

    return accumulator;
}
