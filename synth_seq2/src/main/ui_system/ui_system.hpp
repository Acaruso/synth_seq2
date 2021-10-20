#pragma once

#include "src/main/app/app_context.hpp"

class UiSystem
{
public:
    // UiSystem();
    UiSystem(AppContext& context);

private:
    AppContext& context;
};
