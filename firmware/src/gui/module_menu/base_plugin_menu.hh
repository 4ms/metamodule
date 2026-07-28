#pragma once
#include <optional>
#include <string>
#include <vector>

namespace MetaModule
{

struct BasePluginModuleMenu {
	// Returned by click_item() when the clicked row is a continuously-adjustable value
	// (e.g. a Slider) instead of an action/submenu.
	struct SliderEdit {
		std::string label;
		float scaled_value = 0.f; // 0..1
	};

	virtual ~BasePluginModuleMenu() = default;

	virtual std::vector<std::string> get_items() = 0;
	virtual void back_event() = 0;

	// Returns a SliderEdit if idx refers to a slider row, so the caller can show a
	// value-editing widget. Otherwise the click is handled internally (e.g. submenu
	// navigation or an action), and std::nullopt is returned.
	virtual std::optional<SliderEdit> click_item(unsigned idx) = 0;

	// Called continuously while the caller's value-editing widget is being adjusted.
	// Returns an updated display string for the value, or "" if there is none.
	virtual std::string set_slider_value(float scaled_value) = 0;

	// Called when the caller's value-editing widget is closed.
	virtual void end_slider_edit() = 0;

	virtual bool is_done() = 0;
	virtual void close() = 0;
};

} // namespace MetaModule
