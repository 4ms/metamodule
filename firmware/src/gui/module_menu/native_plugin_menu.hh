#pragma once
#include "gui/module_menu/base_plugin_menu.hh"

namespace MetaModule
{

// Not implemented yet, just placeholder to demonstrate support for multiple plugin types
struct NativeModuleMenu : BasePluginModuleMenu {

	NativeModuleMenu() = default;
	~NativeModuleMenu() override = default;

	std::vector<std::string> get_items() override {
		return {};
	}

	void back_event() override {
	}

	void click_item(unsigned idx) override {
	}

	bool is_done() override {
		return true;
	}
};

} // namespace MetaModule
