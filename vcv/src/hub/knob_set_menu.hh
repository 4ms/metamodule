#pragma once
#include "hub/hub_module.hh"
#include <rack.hpp>

struct KnobSetNameTextBox : rack::ui::TextField {
	using CallbackT = std::function<void(unsigned, std::string const &)>;
	CallbackT onChangeCb;
	unsigned idx;

	KnobSetNameTextBox(CallbackT onChangeCallback, unsigned knobSetIdx)
		: onChangeCb{onChangeCallback}
		, idx{knobSetIdx} {
	}

	void onChange(const rack::event::Change &e) override {
		onChangeCb(idx, text);
	}
};

struct KnobSetNameMenuItem : rack::widget::Widget {
	KnobSetNameTextBox *txt;

	KnobSetNameMenuItem(KnobSetNameTextBox::CallbackT onChangeCallback,
						unsigned knobSetIdx,
						std::string_view initialText) {
		box.pos = {0, 0};
		box.size = {120, BND_WIDGET_HEIGHT};
		txt = new KnobSetNameTextBox{onChangeCallback, knobSetIdx};
		txt->box.pos = {45, 0};
		txt->box.size = {120 - txt->box.pos.x, BND_WIDGET_HEIGHT};
		txt->text = initialText;
		addChild(txt);
	}

	void draw(const DrawArgs &args) override {
		bndMenuLabel(args.vg, 0.0, 0.0, box.size.x, box.size.y, -1, "Name:");
		Widget::draw(args);
	}
};
