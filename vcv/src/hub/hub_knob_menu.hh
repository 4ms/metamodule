#pragma once
#include "plugin.hh"

struct KnobNameMenuLabel : ui::MenuLabel {
	ParamQuantity *paramQty;
	void step() override
	{
		text = paramQty->getLabel();
		MenuLabel::step();
	}
};

struct KnobAliasTextBox : ui::TextField {
	MappableObj _src;
	KnobAliasTextBox(MappableObj src)
		: _src{src}
	{}

	void onChange(const event::Change &e) override { centralData->setMapAliasName(_src, text); }
};

struct KnobAliasMenuItem : widget::Widget {
	MappableObj _src;
	KnobAliasTextBox *txt;

	KnobAliasMenuItem(MappableObj src)
		: _src{src}
	{
		box.pos = {0, 0};
		box.size = {120, BND_WIDGET_HEIGHT};
		txt = new KnobAliasTextBox{src};
		txt->box.pos = {45, 0};
		txt->box.size = {120 - txt->box.pos.x, BND_WIDGET_HEIGHT};
		txt->text = centralData->getMapAliasName(_src);
		addChild(txt);
	}

	void draw(const DrawArgs &args) override
	{
		bndMenuLabel(args.vg, 0.0, 0.0, box.size.x, box.size.y, -1, "Alias:");
		Widget::draw(args);
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

enum class RangePart { Min, Max };
template<RangePart MINMAX>
struct MappedRangeQuantity : Quantity {
private:
	float _val{0.f};
	std::string _label;
	MappableObj const _dst_id;

public:
	MappedRangeQuantity(std::string label, MappableObj const knobLabelID)
		: _label{label}
		, _dst_id{knobLabelID}
	{}
	void setValue(float value) override
	{
		_val = MathTools::constrain(value, 0.0f, 1.0f);
		if constexpr (MINMAX == RangePart::Min)
			centralData->setMapRangeMin(_dst_id, _val);
		else
			centralData->setMapRangeMax(_dst_id, _val);
	}
	float getValue() override
	{
		float val;
		if constexpr (MINMAX == RangePart::Min)
			val = centralData->getMapRange(_dst_id).first;
		else
			val = centralData->getMapRange(_dst_id).second;
		return val;
	}
	// clang-format off
	float getMinValue() override { return 0; }
	float getMaxValue() override { return 1; }
	float getDefaultValue() override { return 0.0; }
	float getDisplayValue() override { return getValue() * 100.f; }
	void setDisplayValue(float displayValue) override { setValue(displayValue / 100.f); }
	std::string getLabel() override { return _label; }
	std::string getUnit() override { return "%"; }
	// clang-format on
};

struct MinSlider : ui::Slider {
public:
	MinSlider(MappableObj const knobLabelID)
	{
		quantity = new MappedRangeQuantity<RangePart::Min>{"Min: ", knobLabelID};
	}
	~MinSlider() { delete quantity; }
};

struct MaxSlider : ui::Slider {
public:
	MaxSlider(MappableObj const knobLabelID)
	{
		quantity = new MappedRangeQuantity<RangePart::Max>{"Max: ", knobLabelID};
	}
	~MaxSlider() { delete quantity; }
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
