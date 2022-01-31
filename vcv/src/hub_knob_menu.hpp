#pragma once
#include "knob_map.hpp"
#include "plugin.hpp"

struct MapFieldLabel : ui::MenuLabel {
	ParamQuantity *paramQty;
	void step() override
	{
		text = paramQty->getString();
		MenuLabel::step();
	}
};

struct HubKnobAliasNameMenuField : ui::TextField {
	LabelButtonID _src;

	HubKnobAliasNameMenuField(LabelButtonID src)
		: _src{src}
	{
		text = centralData->getMapAliasName(_src);
	}

	void step() override
	{
		// Keep selected
		APP->event->setSelected(this);
		TextField::step();
	}

	void onSelectKey(const event::SelectKey &e) override
	{
		if (e.action == GLFW_PRESS && (e.key == GLFW_KEY_ENTER || e.key == GLFW_KEY_KP_ENTER)) {
			centralData->setMapAliasName(_src, text);

			// Close menu when user presses Enter:
			ui::MenuOverlay *overlay = getAncestorOfType<ui::MenuOverlay>();
			overlay->requestDelete();
			e.consume(this);
		}

		if (!e.getTarget())
			TextField::onSelectKey(e);
	}
};

struct MappedKnobMenuLabel : ui::MenuLabel {
	int moduleId;
	int paramId;
	std::string moduleName;
	std::string paramName;

	void step() override
	{
		if (moduleName.empty())
			moduleName = std::to_string(moduleId);
		if (paramName.empty())
			paramName = std::to_string(paramId);

		text = moduleName + ": " + paramName;
		MenuLabel::step();
	}
};

enum class RangePart { Min, Max };
template<RangePart MINMAX>
struct MappedRangeQuantity : Quantity {
private:
	float _val{0.f};
	std::string _label;
	LabelButtonID const _dst_id;

public:
	MappedRangeQuantity(std::string label, LabelButtonID const knobLabelID)
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
	MinSlider(LabelButtonID const knobLabelID)
	{
		quantity = new MappedRangeQuantity<RangePart::Min>{"Min: ", knobLabelID};
	}
	~MinSlider()
	{
		delete quantity;
	}
};

struct MaxSlider : ui::Slider {
public:
	MaxSlider(LabelButtonID const knobLabelID)
	{
		quantity = new MappedRangeQuantity<RangePart::Max>{"Max: ", knobLabelID};
	}
	~MaxSlider()
	{
		delete quantity;
	}
};

struct MapField : ui::TextField {
	ParamQuantity *paramQuantity;

	void step() override
	{
		// Keep selected
		APP->event->setSelected(this);
		TextField::step();
	}

	void setParamQuantity(ParamQuantity *paramQ)
	{
		paramQuantity = paramQ;
		if (paramQuantity)
			text = paramQuantity->getDisplayValueString();
		selectAll();
	}

	void onSelectKey(const event::SelectKey &e) override
	{
		if (e.action == GLFW_PRESS && (e.key == GLFW_KEY_ENTER || e.key == GLFW_KEY_KP_ENTER)) {
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

			ui::MenuOverlay *overlay = getAncestorOfType<ui::MenuOverlay>();
			overlay->requestDelete();
			e.consume(this);
		}

		if (!e.getTarget())
			TextField::onSelectKey(e);
	}
};
