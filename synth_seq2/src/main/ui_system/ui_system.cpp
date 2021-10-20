#include "ui_system.hpp"

#include "src/main/ui_elements/advanced/piano_elt.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"
#include "src/main/ui_elements/advanced/sequencer_elt.hpp"
#include "src/main/ui_elements/advanced/synth_settings_elt.hpp"
#include "src/main/ui_elements/advanced/text_elt.hpp"
#include "src/main/ui_elements/advanced/transport_elt.hpp"
#include "src/main/ui_elements/elt_params.hpp"

UiSystem::UiSystem(AppContext& context) : context(context) {}

void UiSystem::draw()
{
    {
        EltParams p(context, Coord(100, 100));
        pianoElt(p);
    }

    {
        EltParams p(context, Coord(100, 300));
        synthSettingsElt(p);
    }

    {
        EltParams p(context, Coord(100, 500));
        sequencerElt(p);
    }

    {
        // EltParams p(context, Coord(1100, 500));
        EltParams p(context, Coord(100, 400));
        transportElt(p);
    }

    {
        Coord coord(1100, 495);
        // Coord coord(500, 400);

        EltParams textParams(context, coord);
        textParams.label = "add track";
        textElt(textParams);

        EltParams p(context, coord);
        Sequencer* sequencer = context.sequencer;

        p.rect = Rect(coord.x, coord.y + 20, 50, 50);
        p.color = inactiveColor;
        p.displayColor = inactiveColor;
        p.onClickColor = activeColor;

        p.onClick = [&]() {
            sequencer->addTrack();
        };

        p.onHold = [&]() { p.displayColor = p.onClickColor; };

        rectButtonElt(p);
    }
}

void UiSystem::handleUiEvents()
{

}
