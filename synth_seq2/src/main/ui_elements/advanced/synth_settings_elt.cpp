#include "synth_settings_elt.hpp"

#include "src/main/ui_elements/advanced/number_with_label_elt.hpp"

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
    EltParams p(context);
    p.label = label;
    p.coord = coord;
    p.key = key;
    numberWithLabelElt(p);
}
