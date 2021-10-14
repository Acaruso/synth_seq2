#include "transport_elt.hpp"

#include "src/main/ui_elements/advanced/rect_button_elt.hpp"
#include "src/main/ui_elements/advanced/text_elt.hpp"

void transportElt(EltParams& params)
{
    auto& context = params.ctx;
    Coord coord = params.coord;

    EltParams textParams(context, coord);
    textParams.label = "play";
    textElt(textParams);

    EltParams p(context);
    p.rect = Rect(coord.x, coord.y + 20, 50, 50);
    p.color = white;
    p.displayColor = context.sequencer->playing ? blue : white;
    p.onClickColor = blue;

    p.onClick = [&]() {
        context.sequencer->playing = !context.sequencer->playing;
        context.sequencer->transport = 0;

        if (context.sequencer->playing) {
            context.toAudioQueue->enqueue(PlayMessage());
        }
        else {
            context.toAudioQueue->enqueue(StopMessage());
        }
    };

    p.onHold = [&]() { p.displayColor = p.onClickColor; };

    rectButtonElt(p);
}
