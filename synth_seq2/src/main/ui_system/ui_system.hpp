#pragma once

#include "src/main/app/app_context.hpp"

class UiSystem
{
public:
    UiSystem(AppContext& context);
    void draw();
    void handleUiEvents();

private:
    AppContext& context;
};
