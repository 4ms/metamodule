#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/element_setters.hh"
#include "VCV-adaptor/app/Menu.hpp"
#include "VCV-adaptor/app/SvgPanel.hpp"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/plugin/Model.hpp"
#include "VCV-adaptor/widget_convert/widget_element_convert.hh"
#include <functional>
#include <string_view>
// #include "pr_dbg.hh"

namespace rack
{

namespace engine
{
struct Module;
}


template<typename T>
T *createElement(math::Vec pos, MetaModule::Coords coord_ref) {
	auto *o = new T;
	pos.x = MetaModule::ModuleInfoBase::to_mm(pos.x);
	pos.y = MetaModule::ModuleInfoBase::to_mm(pos.y);
	o->element = typename ElementConvert<T>::ElementType{pos.x, pos.y, coord_ref};
	return o;
}

template<class TWidget>
TWidget *createWidget(math::Vec pos) {
	return createElement<TWidget>(pos, MetaModule::Coords::TopLeft);
}

template<class TWidget>
TWidget *createWidgetCentered(math::Vec pos) {
	return createElement<TWidget>(pos, MetaModule::Coords::Center);
}

inline app::SvgPanel *createPanel(std::string_view svgPath) {
	return nullptr;
}

template<class TParamWidget>
TParamWidget *createParam(math::Vec pos, engine::Module *module, int paramId) {
	auto o = createElement<TParamWidget>(pos, MetaModule::Coords::TopLeft);
	o->paramId = paramId;
	return o;
}

template<class TParamWidget>
TParamWidget *createParamCentered(math::Vec pos, engine::Module *module, int paramId) {
	auto o = createElement<TParamWidget>(pos, MetaModule::Coords::Center);
	o->paramId = paramId;
	return o;
}

template<class TPortWidget>
TPortWidget *createInput(math::Vec pos, engine::Module *module, int inputId) {
	auto o = createElement<TPortWidget>(pos, MetaModule::Coords::TopLeft);
	o->portId = inputId;
	return o;
}

template<class TPortWidget>
TPortWidget *createInputCentered(math::Vec pos, engine::Module *module, int inputId) {
	auto o = createElement<TPortWidget>(pos, MetaModule::Coords::Center);
	o->portId = inputId;
	return o;
}

template<class TPortWidget>
TPortWidget *createOutput(math::Vec pos, engine::Module *module, int outputId) {
	auto o = createElement<TPortWidget>(pos, MetaModule::Coords::TopLeft);
	o->portId = outputId;
	return o;
}

template<class TPortWidget>
TPortWidget *createOutputCentered(math::Vec pos, engine::Module *module, int outputId) {
	auto o = createElement<TPortWidget>(pos, MetaModule::Coords::Center);
	o->portId = outputId;
	return o;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLight(math::Vec pos, engine::Module *module, int firstLightId) {
	auto o = createElement<TModuleLightWidget>(pos, MetaModule::Coords::TopLeft);
	o->firstLightId = firstLightId;
	return o;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLightCentered(math::Vec pos, engine::Module *module, int firstLightId) {
	auto o = createElement<TModuleLightWidget>(pos, MetaModule::Coords::Center);
	o->firstLightId = firstLightId;
	return o;
}

template<class TParamWidget>
TParamWidget *createLightParam(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	auto param = createElement<TParamWidget>(pos, MetaModule::Coords::TopLeft);
	param->paramId = paramId;

	// TODO: how to do this?
	// param->getLight()->firstLightId = firstLightId;

	return param;
}

template<class TParamWidget>
TParamWidget *createLightParamCentered(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	auto param = createElement<TParamWidget>(pos, MetaModule::Coords::Center);
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
