#pragma once
#include "knob_map.hpp"
#include "plugin.hpp"

struct MapFieldLabel : ui::MenuLabel {
	ParamWidget *paramWidget;
	void step() override
	{
		text = paramWidget->paramQuantity->getString();
		MenuLabel::step();
	}
};

// struct HubKnobAliasNameMenuField : ui::TextField {
// 	KnobMap *knobmap = nullptr;

// 	HubKnobAliasNameMenuField(KnobMap *km)
// 		: knobmap{km}
// 	{
// 		text = knobmap->alias_name;
// 	}

// 	void step() override
// 	{
// 		// Keep selected
// 		APP->event->setSelected(this);
// 		TextField::step();
// 	}

// 	void onSelectKey(const event::SelectKey &e) override
// 	{
// 		if (e.action == GLFW_PRESS && (e.key == GLFW_KEY_ENTER || e.key == GLFW_KEY_KP_ENTER)) {
// 			if (knobmap) {
// 				knobmap->set_alias_name(text);
// 			}

// 			// Close menu when user presses Enter:
// 			ui::MenuOverlay *overlay = getAncestorOfType<ui::MenuOverlay>();
// 			overlay->requestDelete();
// 			e.consume(this);
// 		}

// 		if (!e.getTarget())
// 			TextField::onSelectKey(e);
// 	}
// };

struct MapFieldEntry : ui::MenuLabel {
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
	LabelButtonID const &_dst_id;

public:
	MappedRangeQuantity(std::string label, LabelButtonID const &modknob_id)
		: _label{label}
		, _dst_id{modknob_id}
	{}
	void setValue(float value) override
	{
		_val = MathTools::constrain(value, 0.0f, 1.0f);
		if constexpr (MINMAX == RangePart::Min)
			centralData->setMapRangeMin(_dst_id, _val);
		else
			centralData->setMapRangeMax(_dst_id, _val);
	}
	// clang-format off
	float getValue() override { return _val; }
	float getMinValue() override { return 0; }
	float getMaxValue() override { return 1; }
	float getDefaultValue() override { return 0.0; }
	float getDisplayValue() override { return getValue() * 100.f; }
	void setDisplayValue(float displayValue) override { setValue(displayValue / 100.f); }
	std::string getLabel() override { return _label; }
	std::string getUnit() override { return "%"; }
	// clang-format on
};

struct PercentRefQuantity : Quantity {
private:
	float &_levelValue;
	std::string _label;

public:
	PercentRefQuantity(float &inRange, std::string label)
		: _levelValue{inRange}
		, _label{label}
	{}
	// clang-format off
	void setValue(float value) override { _levelValue = MathTools::constrain(value, 0.0f, 1.0f); }
	float getValue() override { return _levelValue; }
	float getMinValue() override { return 0; }
	float getMaxValue() override { return 1; }
	float getDefaultValue() override { return 0.0; }
	float getDisplayValue() override { return getValue() * 100.f; }
	void setDisplayValue(float displayValue) override { setValue(displayValue / 100.f); }
	std::string getLabel() override { return _label; }
	std::string getUnit() override { return "%"; }
	// clang-format on
};

struct MinField : ui::Slider {
public:
	MinField(std::pair<float, float> &inRange)
	{
		quantity = new PercentRefQuantity(inRange.first, "Minimum");
	}
	~MinField()
	{
		delete quantity;
	}
};

struct MaxField : ui::Slider {
public:
	MaxField(std::pair<float, float> &inRange)
	{
		quantity = new PercentRefQuantity(inRange.second, "Maximum");
	}
	~MaxField()
	{
		delete quantity;
	}
};

struct MapField : ui::TextField {
	ParamWidget *paramWidget;

	void step() override
	{
		// Keep selected
		APP->event->setSelected(this);
		TextField::step();
	}

	void setParamWidget(ParamWidget *paramWidget)
	{
		this->paramWidget = paramWidget;
		if (paramWidget->paramQuantity)
			text = paramWidget->paramQuantity->getDisplayValueString();
		selectAll();
	}

	void onSelectKey(const event::SelectKey &e) override
	{
		if (e.action == GLFW_PRESS && (e.key == GLFW_KEY_ENTER || e.key == GLFW_KEY_KP_ENTER)) {
			float oldValue = paramWidget->paramQuantity->getValue();
			if (paramWidget->paramQuantity)
				paramWidget->paramQuantity->setDisplayValueString(text);
			float newValue = paramWidget->paramQuantity->getValue();

			if (oldValue != newValue) {
				// Push ParamChange history action
				history::ParamChange *h = new history::ParamChange;
				h->moduleId = paramWidget->paramQuantity->module->id;
				h->paramId = paramWidget->paramQuantity->paramId;
				h->oldValue = oldValue;
				h->newValue = newValue;
				APP->history->push(h);
			}

			ui::MenuOverlay *overlay = getAncestorOfType<ui::MenuOverlay>();
			overlay->requestDelete();
			e.consume(this);
		}

		if (!e.getTarget())
			TextField::onSelectKey(e);
	}
};
