#include "callback.hpp"

#include <iostream>

#include "src/main/ui_elements/advanced/piano_elt.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"
#include "src/main/ui_elements/advanced/sequencer_elt.hpp"
#include "src/main/ui_elements/advanced/synth_settings_elt.hpp"
#include "src/main/ui_elements/advanced/text_elt.hpp"
#include "src/main/ui_elements/advanced/transport_elt.hpp"
#include "src/main/ui_elements/elt_params.hpp"

void setup(AppContext& context)
{
    try {
        context.graphicsWrapper.loadFont(
            "dos",
            "fonts/Perfect-DOS-VGA-437.ttf",
            16,
            9,
            20
        );

        context.graphicsWrapper.loadFont(
            "inconsolata",
            "fonts/Inconsolata-Regular.ttf",
            16,
            8,
            20
        );
    }
    catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
    }
}

void callback(AppContext& context)
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
        EltParams p(context, Coord(1200, 500));
        transportElt(p);
    }
}
