#include "synth_settings_elt.hpp"

#include "src/main/ui_elements/advanced/number_elt.hpp"
#include "src/main/util.hpp"

void _numberElt(AppContext& context, std::string label, Coord coord, std::string key);

void synthSettingsElt(EltParams& params)
{
    AppContext& context = params.ctx;
    Coord numCoord = params.coord;

    int numXPadding = 150;

    _numberElt(
        context,
        "volume",
        numCoord,
        "volume"
    );

    numCoord.x += numXPadding;
    _numberElt(
        context,
        "mod amount",
        numCoord,
        "modAmount"
    );

    numCoord.x += numXPadding;
    _numberElt(
        context,
        "attack",
        numCoord,
        "attack"
    );

    numCoord.x += numXPadding;
    _numberElt(
        context,
        "hold",
        numCoord,
        "hold"
    );

    numCoord.x += numXPadding;
    _numberElt(
        context,
        "release",
        numCoord,
        "release"
    );

    numCoord = Coord{100 + numXPadding * 2, 400};
    _numberElt(
        context,
        "mod attack",
        numCoord,
        "modAttack"
    );

    numCoord.x += numXPadding;
    _numberElt(
        context,
        "mod hold",
        numCoord,
        "modHold"
    );

    numCoord.x += numXPadding;
    _numberElt(
        context,
        "mod release",
        numCoord,
        "modRelease"
    );

    numCoord.x += numXPadding;
    _numberElt(
        context,
        "freq",
        numCoord,
        "freq"
    );
}

void _numberElt(AppContext& context, std::string label, Coord coord, std::string key)
{
    auto& synthSettings = context.sequencer->mode == Normal
        ? (*context.synthSettings)
        : context.sequencer->getCurrentCell().synthSettings;

    std::string fontName = "dos";
    Font& font = context.graphicsWrapper.getFont(fontName);
    int data = synthSettings[key];

    context.graphicsWrapper.drawText(label, fontName, coord);

    EltParams p(context);

    p.coord = Coord{
        coord.x,
        coord.y + font.lineHeight
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
        synthSettings[key] += context.getDragAmount() / 2;
        synthSettings[key] = clamp(synthSettings[key], p.min, p.max);
    };

    numberElt(p);
}
