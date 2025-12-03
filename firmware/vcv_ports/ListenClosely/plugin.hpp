#pragma once
#include <rack.hpp>
//

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelListenClosely;

struct _9mmKnob : RoundKnob {
    _9mmKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/9mm_knob.svg")));
    }
};

struct Davies1900hBlack : RoundKnob {
    Davies1900hBlack() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/Davies1900hBlack.svg")));
    }
};

struct Davies_large : RoundKnob {
    Davies_large() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/Davies_large.svg")));
    }
};

struct _2Pos : SvgSwitch {
    _2Pos() {
        momentary = false; // true for momentary behavior
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_0.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_2.svg")));
    }
};

struct _2PosHorizontal : SvgSwitch {
    _2PosHorizontal() {
        momentary = false; // true for momentary behavior
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_0.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_2.svg")));
    }
};

struct _3Pos : SvgSwitch {
    _3Pos() {
        momentary = false; // true for momentary behavior
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_0.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_1.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_2.svg")));
    }
};

struct _3PosHorizontal : SvgSwitch {
    _3PosHorizontal() {
        momentary = false; // true for momentary behavior
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_0.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_1.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_2.svg")));
    }
};