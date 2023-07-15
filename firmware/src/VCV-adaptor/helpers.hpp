#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/element_setters.hh"
#include "VCV-adaptor/app/Menu.hpp"
#include "VCV-adaptor/app/SvgPanel.hpp"
#include "VCV-adaptor/element_creator.hh"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/plugin/Model.hpp"
#include <functional>
#include <string_view>

namespace rack
{

namespace engine
{
struct Module;
}

/** Creates a Widget subclass with its top-left at a position. */
template<class TWidget>
TWidget *createWidget(math::Vec pos) {
	return nullptr;
}

/** Creates a Widget subclass with its center at a position. */
template<class TWidget>
TWidget *createWidgetCentered(math::Vec pos) {
	return nullptr;
}

inline app::SvgPanel *createPanel(std::string_view svgPath) {
	return nullptr;
}

template<class TParamWidget>
TParamWidget *createParam(math::Vec pos, engine::Module *module, int paramId) {
	using namespace MetaModule;
	auto *o = new TParamWidget;
	o->element = create_element<TParamWidget>();
	o->paramId = paramId;
	MetaModule::set_pos(o->element, ModuleInfoBase::to_mm(pos.x), ModuleInfoBase::to_mm(pos.y), Coords::TopLeft);
	return o;
}

template<class TParamWidget>
TParamWidget *createParamCentered(math::Vec pos, engine::Module *module, int paramId) {
	using namespace MetaModule;
	auto *o = createParam<TParamWidget>(pos, module, paramId);
	MetaModule::set_pos(o->element, ModuleInfoBase::to_mm(pos.x), ModuleInfoBase::to_mm(pos.y), Coords::Center);
	return o;
}

template<class TPortWidget>
TPortWidget *createInput(math::Vec pos, engine::Module *module, int inputId) {
	return nullptr;
}

template<class TPortWidget>
TPortWidget *createInputCentered(math::Vec pos, engine::Module *module, int inputId) {
	return nullptr;
}

template<class TPortWidget>
TPortWidget *createOutput(math::Vec pos, engine::Module *module, int outputId) {
	return nullptr;
}

template<class TPortWidget>
TPortWidget *createOutputCentered(math::Vec pos, engine::Module *module, int outputId) {
	return nullptr;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLight(math::Vec pos, engine::Module *module, int firstLightId) {
	return nullptr;
}

template<class TModuleLightWidget>
TModuleLightWidget *createLightCentered(math::Vec pos, engine::Module *module, int firstLightId) {
	return nullptr;
}

template<class TParamWidget>
TParamWidget *createLightParam(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	return nullptr;
}

template<class TParamWidget>
TParamWidget *createLightParamCentered(math::Vec pos, engine::Module *module, int paramId, int firstLightId) {
	return nullptr;
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
