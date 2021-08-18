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
	void step() override
	{
		text = "Module " + std::to_string(moduleId) + " Param " + std::to_string(paramId);
		MenuLabel::step();
	}
};

struct LevelQuantity : Quantity {
	void setValue(float value) override {}
	float getValue() override
	{
		return 0;
	}
	float getMinValue() override
	{
		return -2.0;
	}
	float getMaxValue() override
	{
		return 2.0;
	}
	float getDefaultValue() override
	{
		return 0.0;
	}
	float getDisplayValue() override
	{
		return 0;
	}
	void setDisplayValue(float displayValue) override
	{
		setValue(std::log2(displayValue / 100));
	}
	std::string getLabel() override
	{
		return "Level";
	}
	std::string getUnit() override
	{
		return "";
	}
};

struct OffsetQuantity : Quantity {
	void setValue(float value) override {}
	float getValue() override
	{
		return 0;
	}
	float getMinValue() override
	{
		return -2.0;
	}
	float getMaxValue() override
	{
		return 2.0;
	}
	float getDefaultValue() override
	{
		return 0.0;
	}
	float getDisplayValue() override
	{
		return 0;
	}
	void setDisplayValue(float displayValue) override
	{
		setValue(std::log2(displayValue / 100));
	}
	std::string getLabel() override
	{
		return "Offset";
	}
	std::string getUnit() override
	{
		return "";
	}
};

struct LevelField : ui::Slider {
	LevelField()
	{
		quantity = new LevelQuantity;
	}
	~LevelField()
	{
		delete quantity;
	}
};

struct OffsetField : ui::Slider {
	OffsetField()
	{
		quantity = new OffsetQuantity;
	}
	~OffsetField()
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
