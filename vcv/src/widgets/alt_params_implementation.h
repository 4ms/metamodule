#include "rack.hpp"
#include <algorithm>

namespace MetaModule::VCVImplementation::Widget
{

struct ContinousQuantity : rack::Quantity
{
	ContinousQuantity(rack::Module &module_, std::size_t param_idx_, float minVal, float maxVal, float defaultVal)
		: module{module_}
        , param_idx(param_idx_)
		, _min(minVal)
        , _max(maxVal)
        , _default(defaultVal)
	{
		_val = module.getParam(param_idx).getValue();
	}

	void setValue(float value) override
	{
        value = std::clamp(value, _min, _max);
		if (value != _val)
		{
			_val = value;
			module.getParam(param_idx).setValue(_val);
		}
	}

	float getValue() override {
		return _val;
	}
	float getMinValue() override {
		return _min;
	}
	float getMaxValue() override {
		return _max;
	}
	float getDefaultValue() override {
		return _default;
	}

private:
	rack::Module &module;
    std::size_t param_idx;
	float _val;
    float _min;
    float _max;
    float _default;
};

struct QuantizedQuantity : rack::Quantity
{
	QuantizedQuantity(rack::Module &module_, std::size_t param_idx_, float minVal, float maxVal, float defaultVal)
		: module{module_}
        , param_idx(param_idx_)
		, _min(minVal)
        , _max(maxVal)
        , _default(defaultVal)
	{
		_val = module.getParam(param_idx).getValue();
	}

	void setValue(float value) override
	{
        value = std::clamp(value, _min, _max);
		if (value != _val)
		{
            // if (std::abs(value - _val) > 0.6f)
            // {
                _val = std::round(value);
                module.getParam(param_idx).setValue(_val);
            // }
		}
	}

	float getValue() override {
		return _val;
	}
	float getMinValue() override {
		return _min;
	}
	float getMaxValue() override {
		return _max;
	}
	float getDefaultValue() override {
		return _default;
	}

private:
	rack::Module &module;
    std::size_t param_idx;
	float _val;
    float _min;
    float _max;
    float _default;
};



struct AltParamSlider : public rack::ui::Slider
{
	AltParamSlider(rack::Quantity* quant)
    {
        quantity = quant;
	}
	~AltParamSlider() {
		delete quantity;
	}
};

struct AltParamChoiceItem : rack::ui::MenuItem
{
    AltParamChoiceItem(rack::Module* module_, std::size_t param_idx_, std::size_t choiceIndex_) : module(module_), param_idx(param_idx_), choiceIndex(choiceIndex_) {};
    void onAction(const ActionEvent& e) override
    {
        e.unconsume();

        module->getParam(param_idx).setValue(choiceIndex);
    }

private:
    rack::Module* module;
    std::size_t param_idx;
    std::size_t choiceIndex;
};

struct AltParamChoiceLabledMenu : rack::ui::MenuItem
{
    AltParamChoiceLabledMenu(rack::Module* module_, std::size_t param_idx_, AltParamChoiceLabled el) : module(module_), param_idx(param_idx_), element(el) {}

    rack::ui::Menu* createChildMenu() override
    {
        auto childMenu = new rack::ui::Menu;

        for (std::size_t i=0; i<element.num_pos; i++)
        {
            auto choiceItem = new AltParamChoiceItem(module, param_idx, i);
            auto choiceText = element.pos_names[i];
            choiceItem->text = std::string(choiceText);
            childMenu->addChild(choiceItem);
        }
        return childMenu;
    }

private:
    rack::Module* module;
    std::size_t param_idx;
    AltParamChoiceLabled element;
};

inline void do_render_to_menu(AltParamContinuous el, rack::ui::Menu* menu, Indices &indices, const WidgetContext_t &context)
{
	auto *item = new rack::ui::MenuItem;
	item->text = el.short_name;
    item->disabled = true;
	menu->addChild(item);

    auto quantity = new ContinousQuantity(*context.module, indices.param_idx, el.MinValue, el.MaxValue, el.DefaultValue);

	auto slider = new AltParamSlider{quantity};
	slider->box.size.x = 100;
	menu->addChild(slider);
}

inline void do_render_to_menu(AltParamChoiceLabled el, rack::ui::Menu* menu, Indices &indices, const WidgetContext_t &context)
{
	auto *item = new AltParamChoiceLabledMenu(context.module, indices.param_idx, el);
	item->text = el.short_name;
    item->rightText = RIGHT_ARROW;
    menu->addChild(item);
}

inline void do_render_to_menu(AltParamChoice el, rack::ui::Menu* menu, Indices &indices, const WidgetContext_t &context)
{
	auto *item = new rack::ui::MenuItem;
	item->text = el.short_name;
    item->disabled = true;
	menu->addChild(item);

    auto quantity = new QuantizedQuantity(*context.module, indices.param_idx, 0, el.num_pos, el.DefaultValue);

	auto slider = new AltParamSlider{quantity};
	slider->box.size.x = 100;
	menu->addChild(slider);
}

}