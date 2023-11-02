#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/element_setters.hh"
#include "VCV_adaptor/app/Menu.hpp"
#include "VCV_adaptor/app/SvgPanel.hpp"
#include "VCV_adaptor/engine/Module.hpp"
#include "VCV_adaptor/math.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include "VCV_adaptor/widget_convert/widget_element_convert.hh"
#include <functional>
#include <string_view>
// #include "pr_dbg.hh"

namespace rack
{

// namespace engine
// {
// struct Module;
// }

// Creates a Widget that has an Element
template<typename T>
T *createElementWidget(math::Vec pos, MetaModule::Coords coord_ref, std::string_view name) {
	auto *o = new T;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = typename ElementConvert<T>::ElementType{pos.x, pos.y, coord_ref, name, name};
	return o;
}

inline std::string_view getParamName(engine::Module *module, int id) {
	if (auto pq = module->getParamQuantity(id)) {
		return pq->name;
	}
	return "(Param)";
}

inline std::string_view getInputName(engine::Module *module, int id) {
	if (auto info = module->getInputInfo(id)) {
		return info->name;
	}
	return "(In)";
}

inline std::string_view getOutputName(engine::Module *module, int id) {
	if (auto info = module->getOutputInfo(id)) {
		return info->name;
	}
	return "(Out)";
}

inline std::string_view getLightName(engine::Module *module, int id) {
	if (auto info = module->getLightInfo(id)) {
		return info->name;
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

template<class TParamWidget>
TParamWidget *createParam(math::Vec pos, engine::Module *module, int paramId) {
	auto name = getParamName(module, paramId);
	auto o = createElementWidget<TParamWidget>(pos, MetaModule::Coords::TopLeft, name);
	o->paramId = paramId;
	if (o->getParamQuantity())
		o->getParamQuantity()->name = name;
	return o;
}

template<class TParamWidget>
TParamWidget *createParamCentered(math::Vec pos, engine::Module *module, int paramId) {
	auto name = getParamName(module, paramId);
	auto o = createElementWidget<TParamWidget>(pos, MetaModule::Coords::Center, name);
	o->paramId = paramId;
	if (o->getParamQuantity())
		o->getParamQuantity()->name = name;
	return o;
}

template<class TPortWidget>
TPortWidget *createInput(math::Vec pos, engine::Module *module, int inputId) {
	auto name = getInputName(module, inputId);
	auto *o = new TPortWidget;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element =
		typename ElementConvert<TPortWidget>::ElementTypeInput{pos.x, pos.y, MetaModule::Coords::TopLeft, name, name};
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
	o->element =
		typename ElementConvert<TPortWidget>::ElementTypeInput{pos.x, pos.y, MetaModule::Coords::Center, name, name};
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
	o->element =
		typename ElementConvert<TPortWidget>::ElementTypeOutput{pos.x, pos.y, MetaModule::Coords::TopLeft, name, name};
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
	o->element =
		typename ElementConvert<TPortWidget>::ElementTypeOutput{pos.x, pos.y, MetaModule::Coords::Center, name, name};
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
