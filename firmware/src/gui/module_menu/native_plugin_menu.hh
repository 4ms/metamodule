#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "gui/module_menu/base_plugin_menu.hh"
#include "gui/styles.hh"
#include <vector>

namespace MetaModule
{

// Renders a native (CoreProcessor) module's context menu into the options roller.
// The items come from CoreProcessor::get_context_menu_items(); clicks and slider
// edits are forwarded back to the module via context_menu_action() /
// context_menu_set_value(). This is the native-module counterpart to RackModuleMenu.
struct NativeModuleMenu : BasePluginModuleMenu {

	NativeModuleMenu(CoreProcessor *module)
		: module{module} {
	}

	~NativeModuleMenu() override = default;

	std::vector<std::string> get_items() override {
		items.clear();

		if (!module)
			return {};

		items = module->get_context_menu_items();

		std::vector<std::string> item_strings;
		item_strings.reserve(items.size());

		using Type = CoreProcessor::ContextMenuItem::Type;
		for (auto const &item : items) {
			auto &str = item_strings.emplace_back();

			switch (item.type) {
				case Type::Checkbox:
					// Checkmark goes on the left, matching the VCV menu style
					if (item.checked)
						str = Gui::yellow_text(CHECKMARK);
					str += Gui::lt_grey_text(item.name);
					break;

				case Type::Label:
					str = Gui::grey_text(item.name);
					break;

				case Type::Divider:
					str = Gui::grey_text("----------");
					break;

				case Type::Slider:
				case Type::Action:
				default:
					str = Gui::lt_grey_text(item.name);
					if (item.value_text.length())
						str += " " + Gui::yellow_text(item.value_text);
					break;
			}
		}

		return item_strings;
	}

	void back_event() override {
		// Native menus are flat, so Back always closes them
		close();
	}

	std::optional<SliderEdit> click_item(unsigned idx) override {
		if (!module || idx >= items.size())
			return std::nullopt;

		auto const &item = items[idx];

		using Type = CoreProcessor::ContextMenuItem::Type;
		switch (item.type) {
			case Type::Action:
			case Type::Checkbox:
				module->context_menu_action(idx);
				break;

			case Type::Slider:
				active_slider_idx = idx;
				return SliderEdit{
					.label = item.name,
					.scaled_value = item.value,
				};

			case Type::Label:
			case Type::Divider:
			default:
				break;
		}

		return std::nullopt;
	}

	std::string set_slider_value(float scaled_value) override {
		if (!module || active_slider_idx >= items.size())
			return {};

		module->context_menu_set_value(active_slider_idx, scaled_value);

		// Re-read the item so the popup can show the module's updated value text
		auto updated = module->get_context_menu_items();
		if (active_slider_idx < updated.size())
			return updated[active_slider_idx].value_text;

		return {};
	}

	void end_slider_edit() override {
		active_slider_idx = no_slider;
	}

	bool is_done() override {
		return exited;
	}

	void close() override {
		exited = true;
	}

private:
	// Same glyph the VCV menu uses for checkmarks (CHECKMARK_STRING)
	static constexpr auto CHECKMARK = "✔";
	static constexpr unsigned no_slider = 0xFFFFFFFF;

	CoreProcessor *module{};
	std::vector<CoreProcessor::ContextMenuItem> items;
	unsigned active_slider_idx = no_slider;
	bool exited = false;
};

} // namespace MetaModule
