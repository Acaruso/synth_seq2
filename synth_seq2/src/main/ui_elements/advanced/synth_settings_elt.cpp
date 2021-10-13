#include "synth_settings_elt.hpp"

#include "src/main/ui_elements/advanced/number_elt.hpp"
#include "src/main/ui_elements/basic/rect_outline_elt.hpp"
#include "src/main/util.hpp"

void _numberElt(AppContext& context, std::string label, Coord coord, std::string key);

void synthSettingsElt(EltParams& params)
{
    AppContext& context = params.ctx;
    Font& font = context.graphicsWrapper.getFont(params.fontName);
    Coord numCoord = params.coord;

    int numXPadding = 200;
    int numYPadding = 6;

    // col 1
    _numberElt(
        context,
        "volume",
        numCoord,
        "volume"
    );

    numCoord.y += font.lineHeight + numYPadding;
    _numberElt(
        context,
        "mod amount",
        numCoord,
        "modAmount"
    );

    // col 2
    numCoord.x += numXPadding;
    numCoord.y = params.coord.y;
    _numberElt(
        context,
        "attack",
        numCoord,
        "attack"
    );

    numCoord.y += font.lineHeight + numYPadding;
    _numberElt(
        context,
        "hold",
        numCoord,
        "hold"
    );

    numCoord.y += font.lineHeight + numYPadding;
    _numberElt(
        context,
        "release",
        numCoord,
        "release"
    );

    // col3
    numCoord.x += numXPadding;
    numCoord.y = params.coord.y;
    _numberElt(
        context,
        "mod attack",
        numCoord,
        "modAttack"
    );

    numCoord.y += font.lineHeight + numYPadding;
    _numberElt(
        context,
        "mod hold",
        numCoord,
        "modHold"
    );

    numCoord.y += font.lineHeight + numYPadding;
    _numberElt(
        context,
        "mod release",
        numCoord,
        "modRelease"
    );
}

void _numberElt(AppContext& context, std::string label, Coord coord, std::string key)
{
    auto& synthSettings = context.sequencer->getSynthSettings();

    int& data = synthSettings[key];

    std::string fontName = "inconsolata";
    Font& font = context.graphicsWrapper.getFont(fontName);

    context.graphicsWrapper.drawText(label, fontName, coord);

    EltParams p(context);

    p.coord = Coord{
        coord.x + 100,
        coord.y
    };

    p.min = 0;
    p.max = 100;

    int maxNumDigits = (int)std::to_string(p.max).size();

    p.fontName = fontName;

    p.rect = Rect{
        p.coord.x,
        p.coord.y,
        maxNumDigits * font.width,
        font.height
    },

    p.getDisplayText = [&]() {
        return pad(maxNumDigits, std::to_string(data));
    };

    p.onDrag = [&]() {
        data += context.getDragAmount() / 2;
        data = clamp(data, p.min, p.max);
    };

    numberElt(p);

    Rect outerRect{
        coord.x - 2,
        coord.y,
        102,
        18
    };

    EltParams p2(context);
    p2.rect = outerRect;
    rectOutlineElt(p2);
}
