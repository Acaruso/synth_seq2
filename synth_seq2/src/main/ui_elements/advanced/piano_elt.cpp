#include "piano_elt.hpp"

#include <functional>
#include <iostream>

#include "src/main/ui_elements/advanced/rect_button_elt.hpp"

namespace
{
    int buttonSize = 50;
    int padding = 10;
    int baseNote = 60;
}

Rect getWhiteKeyRect(Coord coord, int i);
Rect getBlackKeyRect(Coord coord, int i);

void whiteKey(
    AppContext& ctx,
    Rect rect,
    std::function<void()> onClick,
    int note
);

void blackKey(
    AppContext& ctx,
    Rect rect,
    std::function<void()> onClick,
    int note
);

void background(EltParams& params, Coord coord);

void pianoElt(EltParams& params)
{
    AppContext& ctx = params.ctx;
    Coord coord = params.coord;

    background(params, coord);

    int k = 0;

    for (int i = 0; i < 12; i++) {
        int note = baseNote + i;

        std::function<void()> _onClick = nullptr;

        if (ctx.sequencer->mode == Normal) {
            _onClick = [&]() {
                // ctx.sequencer->curSynthSettings["note"] = note;
                // ctx.toAudioQueue->enqueue(NoteMessage(note));
                ctx.sequencer->curSynthSettings["note"] = note;
                ctx.toAudioQueue->enqueue(
                    SynthSettingsMessage(ctx.sequencer->curSynthSettings)
                );
            };
        }
        else if (ctx.sequencer->mode == Select) {
            _onClick = [&]() {
                ctx.sequencer->getSelectedCell().synthSettings["note"] = note;
            };
        }

        if (i == 1 || i == 3 || i == 6 || i == 8 || i == 10) {
            blackKey(
                params.ctx,
                getBlackKeyRect(coord, i),
                _onClick,
                note
            );
        }
        else {
            whiteKey(
                params.ctx,
                getWhiteKeyRect(coord, k++),
                _onClick,
                note
            );
        }
    }
}

void whiteKey(
    AppContext& ctx,
    Rect rect,
    std::function<void()> onClick,
    int note
) {
    EltParams p(ctx);
    p.rect = rect;
    p.color = white;

    if (
        ctx.sequencer->mode == Select
        && ctx.sequencer->getSelectedCell().on
        && ctx.sequencer->getSelectedCell().synthSettings["note"] == note
    ) {
        p.displayColor = blue;
    }
    else {
        p.displayColor = white;
    }

    p.onClickColor = blue;
    p.onClick = onClick;
    p.onHold = [&]() { p.displayColor = p.onClickColor; };
    rectButtonElt(p);
}

void blackKey(
    AppContext& ctx,
    Rect rect,
    std::function<void()> onClick,
    int note
) {
    EltParams p(ctx);
    p.rect = rect;
    p.color = black;

    if (
        ctx.sequencer->mode == Select
        && ctx.sequencer->getSelectedCell().on
        && ctx.sequencer->getSelectedCell().synthSettings["note"] == note
    ) {
        p.displayColor = blue;
    }
    else {
        p.displayColor = black;
    }

    p.onClickColor = blue;
    p.onClick = onClick;
    p.onHold = [&]() { p.displayColor = p.onClickColor; };
    rectButtonElt(p);
}

Rect getWhiteKeyRect(Coord coord, int i)
{
    Rect newRect = {};
    newRect.x = coord.x + padding + (i * (buttonSize + padding));
    newRect.y = coord.y + buttonSize + (padding * 2);
    newRect.w = buttonSize;
    newRect.h = buttonSize;
    return newRect;
}

Rect getBlackKeyRect(Coord coord, int i)
{
    Rect newRect = {};
    newRect.y = coord.y + padding;
    newRect.w = buttonSize;
    newRect.h = buttonSize;

    int baseX = coord.x + padding + (buttonSize / 2) + (padding / 2);

    if (i == 1) {
        newRect.x = baseX;
    }
    else if (i == 3) {
        newRect.x = baseX + (buttonSize + padding);
    }
    else if (i == 6) {
        newRect.x = baseX + 3 * (buttonSize + padding);
    }
    else if (i == 8) {
        newRect.x = baseX + 4 * (buttonSize + padding);
    }
    else if (i == 10) {
        newRect.x = baseX + 5 * (buttonSize + padding);
    }

    return newRect;
}

void background(EltParams& params, Coord coord)
{
    Rect rect{
        coord.x,
        coord.y,
        -10,
        (buttonSize + padding) * 7 + padding,
        (buttonSize + padding) * 2 + padding,
        red
    };

    params.ctx.graphicsWrapper.drawRect(rect);
}
