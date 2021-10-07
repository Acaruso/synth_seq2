#include "sequencer_elt.hpp"

#include "src/shared/sequencer/sequencer.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"

void _clock(AppContext& ctx, Coord coord, int i);
Rect _getClockRect(Coord coord, int i);
void _cell(AppContext& ctx, Cell& cell, Coord coord, int i);
Rect _getCellRect(Coord coord, int i);

namespace
{
    int cellWidth = 50;
    int cellHeight = 50;
    int clockCellWidth = 50;
    int clockCellHeight = 20;
    int padding = 10;
}

void sequencerElt(EltParams& params)
{
    Sequencer& sequencer = params.ctx.sharedDataWrapper.getBackBuffer().sequencer;
    Coord coord = params.coord;

    for (int i = 0; i < sequencer.row.size(); i++) {
        Cell& cell = sequencer.row[i];
        _clock(params.ctx, coord, i);
        _cell(params.ctx, cell, coord, i);
    }
}

void _clock(AppContext& ctx, Coord coord, int i)
{
    Sequencer& sequencer = ctx.sharedDataWrapper.getBackBuffer().sequencer;
    EltParams p(ctx);
    p.rect = _getClockRect(coord, i);
    p.color = white;

    if (sequencer.playing == false) {
        p.displayColor = white;
    }
    else {
        p.displayColor = sequencer.step == i ? blue : white;
    }

    rectButtonElt(p);
}

Rect _getClockRect(Coord coord, int i)
{
    return Rect(
        coord.x + ((clockCellWidth + padding) * i),
        coord.y,
        clockCellWidth,
        clockCellHeight
    );
}

void _cell(AppContext& ctx, Cell& cell, Coord coord, int i)
{
    EltParams p(ctx);
    p.rect = _getCellRect(coord, i);
    p.color = white;
    p.displayColor = cell.on ? blue : white;
    p.onClickColor = blue;
    p.onClick = [&]() { cell.on = !cell.on; };
    p.onHold = [&]() { p.displayColor = p.onClickColor; };
    rectButtonElt(p);
}

Rect _getCellRect(Coord coord, int i)
{
    int buttonSize = 50;
    int padding = 10;

    return Rect(
        coord.x + ((cellWidth + padding) * i),
        coord.y + clockCellHeight + padding,
        cellWidth,
        cellHeight
    );
}
