#include "transport_elt.hpp"

#include "src/main/sequencer/sequencer.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"
#include "src/main/ui_elements/advanced/text_elt.hpp"

void transportElt(EltParams& params)
{
    auto& context = params.ctx;
    Coord coord = params.coord;
    Sequencer* sequencer = context.sequencer;

    EltParams textParams(context, coord);
    textParams.label = "play";
    textElt(textParams);

    EltParams p(context);
    p.rect = Rect(coord.x, coord.y + 20, 50, 50);
    p.color = white;
    p.displayColor = sequencer->isPlaying() ? blue : white;
    p.onClickColor = blue;

    p.onClick = [&]() {
        if (!context.sequencer->playing) {
            sequencer->play();
            context.toAudioQueue->enqueue(PlayMessage());
        }
        else {
            sequencer->stop();
            context.toAudioQueue->enqueue(StopMessage());
        }
    };

    p.onHold = [&]() { p.displayColor = p.onClickColor; };

    rectButtonElt(p);
}
