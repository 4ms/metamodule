#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/element_strings.hh"
#include "VCV_adaptor/app/Menu.hpp"
#include "VCV_adaptor/app/SvgPanel.hpp"
#include "VCV_adaptor/engine/Module.hpp"
#include "VCV_adaptor/make_element.hh"
#include "VCV_adaptor/math.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include "util/overloaded.hh"
#include <functional>
#include <span>
#include <string_view>

namespace rack
{

template<typename T>
T *createElementWidget(math::Vec pos, MetaModule::Coords coord_ref, std::string_view name) {
	auto *widget = new T;
	widget->element = MetaModule::make_element(widget, {pos.x, pos.y, coord_ref, name, name});
	return widget;
}

// Creates a Widget and makes the right Element in the Widget
template<typename T>
T *createElementParamWidget(
	math::Vec pos, MetaModule::Coords coord_ref, std::string_view name, engine::Module *module, int paramId) {
	auto *widget = new T;
	widget->module = module;
	widget->paramId = paramId;
	widget->element = MetaModule::make_element(widget, {pos.x, pos.y, coord_ref, name, name});
	widget->box.pos = coord_ref == MetaModule::Coords::TopLeft ? pos : pos.minus(widget->box.size.div(2));
	return widget;
}

// Special case for slide widgets because
// 1) They sometimes offset their position manually in VCV Rack class constructors. Apply those manual adjustments here.
// 2) If it's a slider with snapEnabled == true, then the element should be a switch, not a slider
template<typename T>
T *createElementParamWidget(
	math::Vec pos, MetaModule::Coords coord_ref, std::string_view name, engine::Module *module, int paramId)
	requires(std::derived_from<T, app::SvgSlider>)
{
	auto *widget = new T;
	widget->module = module;
	widget->paramId = paramId;
	engine::ParamQuantity *pq = widget->getParamQuantity();

	// Slide switch is SvgSlider type in VCV, so we need to disambiguiate
	if (pq && pq->snapEnabled)
		widget->element = MetaModule::make_element_slideswitch(widget, {pos.x, pos.y, coord_ref, name, name});
	else
		widget->element = MetaModule::make_element(widget, {pos.x, pos.y, coord_ref, name, name});

	if (coord_ref == MetaModule::Coords::TopLeft) {
		widget->box.pos = pos + widget->background->box.pos;
	} else {
		widget->box.pos = pos.minus(widget->background->box.size.div(2));
	}

	return widget;
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

template<class TPanel = app::SvgPanel>
TPanel *createPanel(std::string svgPath) {
	auto *panel = new TPanel;
	panel->setBackground(window::Svg::load(svgPath));
	return panel;
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
	auto widget = createElementParamWidget<TParamWidget>(pos, coords, name, module, paramId);

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
	auto widget = createParamImpl<TParamWidget>(MetaModule::Coords::TopLeft, pos, module, paramId);
	return widget;
}

template<class TParamWidget>
TParamWidget *createParamCentered(math::Vec pos, engine::Module *module, int paramId) {
	auto widget = createParamImpl<TParamWidget>(MetaModule::Coords::Center, pos, module, paramId);
	return widget;
}

template<class TPortWidget>
TPortWidget *createInput(math::Vec pos, engine::Module *module, int inputId) {
	auto name = getInputName(module, inputId);
	auto *widget = new TPortWidget;
	widget->box.pos = pos;
	widget->element = MetaModule::make_element_input(widget, {pos.x, pos.y, MetaModule::Coords::TopLeft, name, name});
	widget->portId = inputId;
	if (widget->getPortInfo())
		widget->getPortInfo()->name = name;
	return widget;
}

template<class TPortWidget>
TPortWidget *createInputCentered(math::Vec pos, engine::Module *module, int inputId) {
	auto name = getInputName(module, inputId);
	auto *widget = new TPortWidget;
	widget->box.pos = pos.minus(widget->box.size.div(2));
	widget->element = MetaModule::make_element_input(widget, {pos.x, pos.y, MetaModule::Coords::Center, name, name});
	widget->portId = inputId;
	if (widget->getPortInfo())
		widget->getPortInfo()->name = name;
	return widget;
}

template<class TPortWidget>
TPortWidget *createOutput(math::Vec pos, engine::Module *module, int outputId) {
	auto name = getOutputName(module, outputId);
	auto *widget = new TPortWidget;
	widget->box.pos = pos;
	widget->element = MetaModule::make_element_output(widget, {pos.x, pos.y, MetaModule::Coords::TopLeft, name, name});
	widget->portId = outputId;
	if (widget->getPortInfo())
		widget->getPortInfo()->name = name;
	return widget;
}

template<class TPortWidget>
TPortWidget *createOutputCentered(math::Vec pos, engine::Module *module, int outputId) {
	auto name = getOutputName(module, outputId);
	auto *widget = new TPortWidget;
	widget->box.pos = pos.minus(widget->box.size.div(2));
	widget->element = MetaModule::make_element_output(widget, {pos.x, pos.y, MetaModule::Coords::Center, name, name});
	widget->portId = outputId;
	if (widget->getPortInfo())
		widget->getPortInfo()->name = name;
	return widget;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLight(math::Vec pos, engine::Module *module, int firstLightId) {
	auto name = getLightName(module, firstLightId);
	auto widget = createElementWidget<TModuleLightWidget>(pos, MetaModule::Coords::TopLeft, name);
	widget->box.pos = pos;
	widget->firstLightId = firstLightId;
	return widget;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLightCentered(math::Vec pos, engine::Module *module, int firstLightId) {
	auto name = getLightName(module, firstLightId);
	auto widget = createElementWidget<TModuleLightWidget>(pos, MetaModule::Coords::Center, name);
	widget->box.pos = pos.minus(widget->box.size.div(2));
	widget->firstLightId = firstLightId;
	return widget;
}

template<class TParamWidget>
TParamWidget *createLightParam(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	auto name = getParamName(module, paramId);
	auto widget = createElementWidget<TParamWidget>(pos, MetaModule::Coords::TopLeft, name);
	widget->box.pos = pos;
	widget->paramId = paramId;

	// TODO: how to do this?
	// param->getLight()->firstLightId = firstLightId;

	return widget;
}

template<class TParamWidget>
TParamWidget *createLightParamCentered(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	auto name = getParamName(module, paramId);
	auto widget = createElementWidget<TParamWidget>(pos, MetaModule::Coords::Center, name);
	widget->box.pos = pos.minus(widget->box.size.div(2));
	widget->paramId = paramId;

	// TODO: how to do this?
	// param->getLight()->firstLightId = firstLightId;

	return widget;
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
