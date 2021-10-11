#include "callback.hpp"

#include <iostream>

#include "src/main/ui_elements/advanced/piano_elt.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"
#include "src/main/ui_elements/advanced/sequencer_elt.hpp"
#include "src/main/ui_elements/advanced/synth_settings_elt.hpp"
#include "src/main/ui_elements/advanced/text_elt.hpp"
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
    }
    catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
    }
}

void callback(AppContext& context)
{
    auto& sequencer = context.sharedDataWrapper.sharedData.sequencer;

    sequencer.update();

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
        p.rect = Rect(coord.x, coord.y + 20, 50, 50);
        p.color = white;
        p.displayColor = sequencer.playing ? blue : white;
        p.onClickColor = blue;

        p.onClick = [&]() {
            sequencer.playing = !sequencer.playing;
            sequencer.transport = 0;

            if (sequencer.playing) {
                context.toAudioThread(PlayMessage());
            }
            else {
                context.toAudioThread(StopMessage());
            }
        };

        p.onHold = [&]() { p.displayColor = p.onClickColor; };

        rectButtonElt(p);
    }
}
