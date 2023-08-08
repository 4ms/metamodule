#pragma once
#include "hub/hub_module.hh"
#include <rack.hpp>

struct KnobSetNameTextBox : rack::ui::TextField {
	MetaModuleHubBase *hub;
	unsigned idx;

	KnobSetNameTextBox(MetaModuleHubBase *hub, unsigned knobSetIdx)
		: hub{hub}
		, idx{knobSetIdx} {
	}

	void onChange(const rack::event::Change &e) override {
		hub->mappings.setKnobSetName(idx, text);
	}
};

struct KnobSetNameMenuItem : rack::widget::Widget {
	MetaModuleHubBase *hub;
	KnobSetNameTextBox *txt;

	KnobSetNameMenuItem(MetaModuleHubBase *hub, unsigned knobSetIdx)
		: hub{hub} {
		box.pos = {0, 0};
		box.size = {120, BND_WIDGET_HEIGHT};
		txt = new KnobSetNameTextBox{hub, knobSetIdx};
		txt->box.pos = {45, 0};
		txt->box.size = {120 - txt->box.pos.x, BND_WIDGET_HEIGHT};
		txt->text = "";
		txt->text = hub->mappings.getKnobSetName(knobSetIdx);
		addChild(txt);
	}

	void draw(const DrawArgs &args) override {
		bndMenuLabel(args.vg, 0.0, 0.0, box.size.x, box.size.y, -1, "Name:");
		Widget::draw(args);
	}
};
