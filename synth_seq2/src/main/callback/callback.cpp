#include "callback.hpp"

#include <iostream>
#include <string>

#include "src/main/ui_elements/advanced/number_elt.hpp"
#include "src/main/ui_elements/advanced/piano_elt.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"
#include "src/main/ui_elements/advanced/text_elt.hpp"
#include "src/main/ui_elements/advanced/sequencer_elt.hpp"
#include "src/main/ui_elements/advanced/synth_settings_elt.hpp"
#include "src/main/ui_elements/elt_params.hpp"
#include "src/main/util.hpp"
#include "src/shared/audio_queue.hpp"

void setup(AppContext& context)
{
    try {
        context.graphicsWrapper.loadFont(
            "dos",
            "src/fonts/Perfect-DOS-VGA-437.ttf",
            16,
            9,
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
        Coord coord(1200, 500);
        EltParams textParams(context, coord);
        textParams.label = "play";
        textElt(textParams);

        EltParams p(context);
        bool& playing = context.sharedData.boolData["playing"];
        p.rect = Rect(coord.x, coord.y + 20, 50, 50);
        p.color = white;
        p.displayColor = playing ? blue : white;
        p.onClickColor = blue;

        p.onClick = [&]() {
            context.sharedData.setBool("playing", !playing);
            context.sharedData.setInt("transport", 0);
        };

        p.onHold = [&]() { p.displayColor = p.onClickColor; };
        rectButtonElt(p);
    }
}
