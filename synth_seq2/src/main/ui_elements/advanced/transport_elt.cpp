#include "transport_elt.hpp"

#include "src/main/sequencer/sequencer.hpp"
#include "src/main/ui_elements/advanced/number_with_label_elt.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"
#include "src/main/ui_elements/advanced/text_elt.hpp"
#include "src/main/util.hpp"

void playButtonElt(EltParams& params);
void bpmElt(EltParams& params);

void transportElt(EltParams& params)
{
    playButtonElt(params);
    bpmElt(params);
}

void playButtonElt(EltParams& params)
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

void bpmElt(EltParams& params)
{
    auto& context = params.ctx;
    auto& sequencer = context.sequencer;
    EltParams p(context);
    p.coord = params.coord;
    p.coord.x += 60;
    p.coord.y += 20;
    p.label = "bpm";

    p.min = 0;
    p.max = 999;

    int maxNumDigits = (int)std::to_string(p.max).size();

    int& data = sequencer->bpm;

    p.displayText = pad(maxNumDigits, std::to_string(data));

    p.onDrag = [&]() {
        int drag = context.getDragAmount();
        data = (drag == 1 || drag == -1) ? data + drag : data + (drag / 2);
        data = clamp(data, p.min, p.max);
    };

    numberWithLabelElt(p);
}
