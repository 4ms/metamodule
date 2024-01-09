#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/element_strings.hh"
#include "VCV_adaptor/app/Menu.hpp"
#include "VCV_adaptor/app/SvgPanel.hpp"
#include "VCV_adaptor/engine/Module.hpp"
#include "VCV_adaptor/math.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include "VCV_adaptor/widget_convert/base.hh"
// #include "VCV_adaptor/widget_convert/widget_element_convert.hh"
#include "util/overloaded.hh"
#include <functional>
#include <span>
#include <string_view>

namespace rack
{

// Creates a Widget and makes the right Element in the Widget
template<typename T>
T *createElementWidget(math::Vec pos, MetaModule::Coords coord_ref, std::string_view name) {
	auto *o = new T;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = MetaModule::make_element<T>({pos.x, pos.y, coord_ref, name, name});
	return o;
}

// Special case for slide widgets because they sometimes offset their position
// manually in VCV Rack class constructors. Apply those manual adjustments here.
template<typename T>
T *createElementWidget(math::Vec pos, MetaModule::Coords coord_ref, std::string_view name)
	requires(std::derived_from<T, app::SvgSlider>)
{
	auto *o = new T;
	if (coord_ref == MetaModule::Coords::TopLeft) {
		pos.x += o->background->box.pos.x;
		pos.y += o->background->box.pos.y;
	}
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = MetaModule::make_element<T>({pos.x, pos.y, coord_ref, name, name});
	return o;
}

inline std::string_view getParamName(engine::Module *module, int id) {
	if (auto pq = module->getParamQuantity(id)) {
		if (pq->name.size()) {
			remove_extended_chars(pq->name);
			return pq->name;
		}
	}
	return "(Param)";
}

inline std::string_view getInputName(engine::Module *module, int id) {
	if (auto info = module->getInputInfo(id)) {
		if (info->name.size()) {
			remove_extended_chars(info->name);
			return info->name;
		}
	}
	return "(In)";
}

inline std::string_view getOutputName(engine::Module *module, int id) {
	if (auto info = module->getOutputInfo(id)) {
		if (info->name.size()) {
			remove_extended_chars(info->name);
			return info->name;
		}
	}
	return "(Out)";
}

inline std::string_view getLightName(engine::Module *module, int id) {
	if (auto info = module->getLightInfo(id)) {
		if (info->name.size()) {
			remove_extended_chars(info->name);
			return info->name;
		}
	}
	return "(Light)";
}

template<class TWidget>
TWidget *createWidget(math::Vec pos) {
	return createElementWidget<TWidget>(pos, MetaModule::Coords::TopLeft, "Unknown");
}

template<class TWidget>
TWidget *createWidgetCentered(math::Vec pos) {
	return createElementWidget<TWidget>(pos, MetaModule::Coords::Center, "Unknown");
}

inline app::SvgPanel *createPanel(std::string_view svgPath) {
	return nullptr;
}

inline void set_labels(std::span<std::string_view> pos_names, std::vector<std::string> &labels) {
	for (unsigned i = 0; auto &label : labels) {
		if (i >= pos_names.size())
			break;
		pos_names[i++] = label;
	}
}

template<class TParamWidget>
requires(std::derived_from<TParamWidget, app::ParamWidget>)
TParamWidget *createParamImpl(MetaModule::Coords coords, math::Vec pos, engine::Module *module, int paramId) {
	using namespace MetaModule;
	auto name = getParamName(module, paramId);
	auto widget = createElementWidget<TParamWidget>(pos, coords, name);
	widget->module = module;
	widget->paramId = paramId;
	if (auto pq = widget->getParamQuantity()) {
		pq->name = name;

		// Switches with strings for each position
		if (pq->labels.size() > 0) {
			std::visit(overloaded{
						   [](BaseElement &) {},
						   [&pq](FlipSwitch &el) {
							   el.num_pos = std::clamp<unsigned>(pq->maxValue - pq->minValue + 1, 2, 3);
							   set_labels(el.pos_names, pq->labels);
						   },
						   [&pq](SlideSwitch &el) {
							   el.num_pos = std::clamp<unsigned>(pq->maxValue - pq->minValue + 1, 2, 8);
							   set_labels(el.pos_names, pq->labels);
						   },
					   },
					   widget->element);
		}
	}
	return widget;
}

template<class TParamWidget>
TParamWidget *createParam(math::Vec pos, engine::Module *module, int paramId) {
	return createParamImpl<TParamWidget>(MetaModule::Coords::TopLeft, pos, module, paramId);
}

template<class TParamWidget>
TParamWidget *createParamCentered(math::Vec pos, engine::Module *module, int paramId) {
	return createParamImpl<TParamWidget>(MetaModule::Coords::Center, pos, module, paramId);
}

template<class TPortWidget>
TPortWidget *createInput(math::Vec pos, engine::Module *module, int inputId) {
	auto name = getInputName(module, inputId);
	auto *o = new TPortWidget;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = MetaModule::make_element_input<TPortWidget>({pos.x, pos.y, MetaModule::Coords::TopLeft, name, name});
	o->portId = inputId;
	if (o->getPortInfo())
		o->getPortInfo()->name = name;
	return o;
}

template<class TPortWidget>
TPortWidget *createInputCentered(math::Vec pos, engine::Module *module, int inputId) {
	auto name = getInputName(module, inputId);
	auto *o = new TPortWidget;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = MetaModule::make_element_input<TPortWidget>({pos.x, pos.y, MetaModule::Coords::Center, name, name});
	o->portId = inputId;
	if (o->getPortInfo())
		o->getPortInfo()->name = name;
	return o;
}

template<class TPortWidget>
TPortWidget *createOutput(math::Vec pos, engine::Module *module, int outputId) {
	auto name = getOutputName(module, outputId);
	auto *o = new TPortWidget;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = MetaModule::make_element_output<TPortWidget>({pos.x, pos.y, MetaModule::Coords::TopLeft, name, name});
	o->portId = outputId;
	if (o->getPortInfo())
		o->getPortInfo()->name = name;
	return o;
}

template<class TPortWidget>
TPortWidget *createOutputCentered(math::Vec pos, engine::Module *module, int outputId) {
	auto name = getOutputName(module, outputId);
	auto *o = new TPortWidget;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = MetaModule::make_element_output<TPortWidget>({pos.x, pos.y, MetaModule::Coords::Center, name, name});
	o->portId = outputId;
	if (o->getPortInfo())
		o->getPortInfo()->name = name;
	return o;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLight(math::Vec pos, engine::Module *module, int firstLightId) {
	auto name = getLightName(module, firstLightId);
	auto o = createElementWidget<TModuleLightWidget>(pos, MetaModule::Coords::TopLeft, name);
	o->firstLightId = firstLightId;
	return o;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLightCentered(math::Vec pos, engine::Module *module, int firstLightId) {
	auto name = getLightName(module, firstLightId);
	auto o = createElementWidget<TModuleLightWidget>(pos, MetaModule::Coords::Center, name);
	o->firstLightId = firstLightId;
	return o;
}

template<class TParamWidget>
TParamWidget *createLightParam(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	auto name = getParamName(module, paramId);
	auto param = createElementWidget<TParamWidget>(pos, MetaModule::Coords::TopLeft, name);
	param->paramId = paramId;

	// TODO: how to do this?
	// param->getLight()->firstLightId = firstLightId;

	return param;
}

template<class TParamWidget>
TParamWidget *createLightParamCentered(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	auto name = getParamName(module, paramId);
	auto param = createElementWidget<TParamWidget>(pos, MetaModule::Coords::Center, name);
	param->paramId = paramId;

	// TODO: how to do this?
	// param->getLight()->firstLightId = firstLightId;

	return param;
}

template<class TMenu = ui::Menu>
TMenu *createMenu() {
	return nullptr;
}

template<class TMenuLabel = ui::MenuLabel>
TMenuLabel *createMenuLabel(std::string_view text) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
TMenuItem *createMenuItem(std::string_view text, std::string_view rightText = "") {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
TMenuItem *createMenuItem(std::string_view text,
						  std::string_view rightText,
						  std::function<void()> action,
						  bool disabled = false,
						  bool alwaysConsume = false) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createCheckMenuItem(std::string_view text,
								  std::string_view rightText,
								  std::function<bool()> checked,
								  std::function<void()> action,
								  bool disabled = false,
								  bool alwaysConsume = false) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createBoolMenuItem(std::string_view text,
								 std::string_view rightText,
								 std::function<bool()> getter,
								 std::function<void(bool state)> setter,
								 bool disabled = false,
								 bool alwaysConsume = false) {
	return nullptr;
}

template<typename T>
ui::MenuItem *createBoolPtrMenuItem(std::string_view text, std::string_view rightText, T *ptr) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createSubmenuItem(std::string_view text,
								std::string_view rightText,
								std::function<void(ui::Menu *menu)> createMenu,
								bool disabled = false) {
	return nullptr;
}

template<class TMenuItem = ui::MenuItem>
ui::MenuItem *createIndexSubmenuItem(std::string_view text,
									 std::vector<std::string> labels,
									 std::function<size_t()> getter,
									 std::function<void(size_t val)> setter,
									 bool disabled = false,
									 bool alwaysConsume = false) {
	return nullptr;
}

template<typename T>
ui::MenuItem *createIndexPtrSubmenuItem(std::string_view text, std::vector<std::string_view> labels, T *ptr) {
	return nullptr;
}

} // namespace rack
