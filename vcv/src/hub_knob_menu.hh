#pragma once
#include "plugin.hpp"

struct MapFieldLabel : ui::MenuLabel {
	ParamWidget *paramWidget;
	void step() override
	{
		text = paramWidget->paramQuantity->getString();
		MenuLabel::step();
	}
};

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

		text = moduleName + /*" (ID#" + std::to_string(moduleId) + ") ,*/ " knob: " + paramName;
		MenuLabel::step();
	}
};

struct PercentQuantity : Quantity {
private:
	float &_levelValue;
	std::string _label;

public:
	PercentQuantity(float &inRange, std::string label)
		: _levelValue{inRange}
		, _label{label}
	{}
	void setValue(float value) override
	{
		_levelValue = MathTools::constrain(value, 0.0f, 1.0f);
	}
	float getValue() override
	{
		return _levelValue;
	}
	float getMinValue() override
	{
		return 0;
	}
	float getMaxValue() override
	{
		return 1;
	}
	float getDefaultValue() override
	{
		return 0.0;
	}
	float getDisplayValue() override
	{
		return getValue() * 100.f;
	}
	void setDisplayValue(float displayValue) override
	{
		setValue(displayValue / 100.f);
	}
	std::string getLabel() override
	{
		return _label;
	}
	std::string getUnit() override
	{
		return "%";
	}
};

struct MinField : ui::Slider {
public:
	MinField(std::pair<float, float> &inRange)
	{
		quantity = new PercentQuantity(inRange.first, "Minimum");
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
		quantity = new PercentQuantity(inRange.second, "Maximum");
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

struct ParamResetItem : ui::MenuItem {
	ParamWidget *paramWidget;
	void onAction(const event::Action &e) override
	{
		paramWidget->resetAction();
	}
};

struct ParamFineItem : ui::MenuItem {};

struct ParamUnmapItem : ui::MenuItem {
	ParamWidget *paramWidget;
	void onAction(const event::Action &e) override
	{
		engine::ParamHandle *paramHandle =
			APP->engine->getParamHandle(paramWidget->paramQuantity->module->id, paramWidget->paramQuantity->paramId);
		if (paramHandle) {
			APP->engine->updateParamHandle(paramHandle, -1, 0);
		}
	}
};
