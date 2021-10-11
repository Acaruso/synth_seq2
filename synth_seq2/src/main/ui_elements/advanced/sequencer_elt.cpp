#include "sequencer_elt.hpp"

#include "src/main/sequencer/sequencer.hpp"
#include "src/main/ui_elements/advanced/rect_button_elt.hpp"

void _clock(AppContext& ctx, Coord coord, int i);
Rect _getClockRect(Coord coord, int i);
void _cell(AppContext& ctx, Cell& cell, Coord coord, int i);
Rect _getCellRect(Coord coord, int i);
void _drawSelectedRect(AppContext& ctx, Rect rect);

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
    Sequencer& sequencer = params.ctx.sharedDataWrapper.sharedData.sequencer;
    Coord coord = params.coord;

    for (int i = 0; i < sequencer.row.size(); i++) {
        Cell& cell = sequencer.row[i];
        _clock(params.ctx, coord, i);
        _cell(params.ctx, cell, coord, i);
    }
}

void _clock(AppContext& ctx, Coord coord, int i)
{
    Sequencer& sequencer = ctx.sharedDataWrapper.sharedData.sequencer;
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
    auto& sharedData = ctx.sharedDataWrapper.sharedData;
    auto& sequencer = sharedData.sequencer;
    auto& uiState = ctx.getUiState();

    EltParams p(ctx);
    p.rect = _getCellRect(coord, i);
    p.color = white;
    p.displayColor = cell.on ? blue : white;
    p.onClickColor = blue;

    p.onClick = [&]() {
        sequencer.mode = Select;

        if (!uiState.lshift) {
            if (!cell.on) {
                cell.on = true;
                cell.intData = sharedData.intData;
            }
            else {
                cell.on = false;
            }
            sequencer.selected = i;
        }
        else if (uiState.lshift) {
            if (sequencer.selected == i) {
                sequencer.mode = Normal;
            }
            else {
                sequencer.selected = i;
            }
        }
    };

    p.onHold = [&]() {
        if (!uiState.lshift) {
            p.displayColor = p.onClickColor;
        }
    };

    if (sequencer.mode == Select && sequencer.selected == i) {
        _drawSelectedRect(ctx, p.rect);
    }

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

void _drawSelectedRect(AppContext& ctx, Rect rect)
{
    int borderWidth = 4;

    Rect selectedRect(
        rect.x - borderWidth,
        rect.y - borderWidth,
        -2,
        rect.w + (2 * borderWidth),
        rect.h + (2 * borderWidth),
        red
    );

    Rect whiteRect(
        rect.x - 1,
        rect.y - 1,
        -1,
        rect.w + 2,
        rect.h + 2,
        white
    );

    ctx.graphicsWrapper.drawRect(whiteRect);
    ctx.graphicsWrapper.drawRect(selectedRect);
}
