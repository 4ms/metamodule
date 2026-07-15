#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "gui/module_menu/base_plugin_menu.hh"
#include <memory>

namespace MetaModule
{

// Not implemented yet, just placeholder to demonstrate support for multiple plugin types
struct NativeModuleMenu : BasePluginModuleMenu {

	NativeModuleMenu(CoreProcessor *module) {
	}

	~NativeModuleMenu() override = default;

	std::vector<std::string> get_items() override {
		return {};
	}

	void back_event() override {
	}

	std::optional<SliderEdit> click_item(unsigned idx) override {
		return std::nullopt;
	}

	std::string set_slider_value(float scaled_value) override {
		return {};
	}

	void end_slider_edit() override {
	}

	bool is_done() override {
		return true;
	}

	void close() override {
	}
};

} // namespace MetaModule
