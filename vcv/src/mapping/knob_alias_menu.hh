#pragma once
#include "hub/hub_module.hh"
// #include "map_marks.hh"
// #include "map_palette.hh"
// #include "mapping/range_slider.hh"
#include <rack.hpp>

struct KnobAliasTextBox : rack::ui::TextField {
	MappableObj _src;
	KnobAliasTextBox(MappableObj src)
		: _src{src} {
	}

	void onChange(const rack::event::Change &e) override {
		// centralData->setMapAliasName(_src, text);
		//TODO:
		//hub->mappings.setMapAliasName(_src, text);
	}
};

struct KnobAliasMenuItem : rack::widget::Widget {
	MappableObj _src;
	KnobAliasTextBox *txt;

	KnobAliasMenuItem(MappableObj src)
		: _src{src} {
		box.pos = {0, 0};
		box.size = {120, BND_WIDGET_HEIGHT};
		txt = new KnobAliasTextBox{src};
		txt->box.pos = {45, 0};
		txt->box.size = {120 - txt->box.pos.x, BND_WIDGET_HEIGHT};
		txt->text = "";
		// txt->text = centralData->getMapAliasName(_src);
		//TODO:
		//txt->text = hub->mappings.getMapAliasName(_src);
		addChild(txt);
	}

	void draw(const DrawArgs &args) override {
		bndMenuLabel(args.vg, 0.0, 0.0, box.size.x, box.size.y, -1, "Alias:");
		Widget::draw(args);
	}
};
