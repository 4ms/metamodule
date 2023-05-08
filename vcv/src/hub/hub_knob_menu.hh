#pragma once
#include "../mapping/central_data.hh"

struct KnobNameMenuLabel : ui::MenuLabel {
	ParamQuantity *paramQty;
	void step() override
	{
		text = paramQty->getLabel();
		MenuLabel::step();
	}
};


struct MappedKnobMenuLabel : ui::MenuLabel {
	int64_t moduleId;
	int paramId;
	std::string moduleName;
	std::string paramName;

	void step() override
	{
		if (moduleName.empty())
			moduleName = std::to_string(moduleId);
		if (paramName.empty())
			paramName = std::to_string(paramId);

		text = "Mapped to: " + moduleName + " " + paramName;
		MenuLabel::step();
	}
};




struct KnobValueTextBox : ui::TextField {
	ParamQuantity *paramQuantity;
	KnobValueTextBox(ParamQuantity *paramQ)
		: paramQuantity{paramQ}
	{
		if (paramQuantity)
			text = paramQuantity->getDisplayValueString();
		selectAll();
	}

	void onChange(const event::Change &e) override
	{
		if (paramQuantity) {
			float oldValue = paramQuantity->getValue();
			paramQuantity->setDisplayValueString(text);
			float newValue = paramQuantity->getValue();

			if (oldValue != newValue) {
				// Push ParamChange history action
				history::ParamChange *h = new history::ParamChange;
				h->moduleId = paramQuantity->module->id;
				h->paramId = paramQuantity->paramId;
				h->oldValue = oldValue;
				h->newValue = newValue;
				APP->history->push(h);
			}
		}
	}
};

struct KnobValueMenuItem : widget::Widget {
	KnobValueTextBox *txt;

	KnobValueMenuItem(float width, float relative_width, ParamQuantity *paramQ)
	{
		box.pos = {0, 0};
		box.size = {width, BND_WIDGET_HEIGHT};
		txt = new KnobValueTextBox{paramQ};
		txt->box.pos = {relative_width * width, 0};
		txt->box.size = {(1.f - relative_width) * width, BND_WIDGET_HEIGHT};
		addChild(txt);
	}

	void draw(const DrawArgs &args) override
	{
		bndMenuLabel(args.vg, 0.0, 0.0, box.size.x, box.size.y, -1, "Value:");
		Widget::draw(args);
	}
};
