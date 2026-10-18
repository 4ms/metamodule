#pragma once
#include "CoreModules/elements/elements.hh"
#include "CoreModules/moduleFactory.hh"
#include "gui/helpers/module_name.hh"
#include "gui/pages/page_args.hh"
#include "patch/patch_data.hh"
#include <optional>
#include <string>

namespace MetaModule
{

// A graphic display that the module view lists and can show full-screen, and so can be a
// screensaver. Tiny displays are treated as lights (see ModView::is_light_only), and
// unnamed elements are not listed.
inline DynamicGraphicDisplay const *fullscreen_display(Element const &el) {
	auto display = std::get_if<DynamicGraphicDisplay>(&el);
	if (display && (display->width_mm >= 5 || display->height_mm >= 5) && display->short_name.size())
		return display;
	return nullptr;
}

inline unsigned count_fullscreen_displays(ModuleInfoView const &info) {
	unsigned count = 0;
	for (auto const &el : info.elements) {
		if (fullscreen_display(el))
			count++;
	}
	return count;
}

inline std::string screensaver_set_message(PatchData const &pd, uint16_t module_id, Element const &el) {
	using namespace std::literals;
	auto name = base_element(el).short_name;
	name = name.substr(0, name.find_first_of("\n\0"sv));

	std::string msg = "Screensaver set to ";
	if (name.size())
		msg += "'" + std::string{name} + "' on ";
	return msg + module_display_name(pd, module_id);
}

// Page arguments to show the patch's screensaver display on the FullscreenGraphic page,
// or nullopt if it has none, or it no longer matches a display of that module
inline std::optional<PageArguments> screensaver_page_args(PatchData const &patch, PatchLocHash patch_loc_hash) {
	auto ss = patch.find_screensaver_display();
	if (!ss || ss->module_id >= patch.module_slugs.size())
		return std::nullopt;

	auto info = ModuleFactory::getModuleInfo(patch.module_slugs[ss->module_id]);

	for (auto i = 0u; i < info.elements.size() && i < info.indices.size(); i++) {
		if (info.indices[i].light_idx != ss->light_id)
			continue;

		auto display = fullscreen_display(info.elements[i]);
		if (!display)
			return std::nullopt;

		return PageArguments{
			.patch_loc_hash = patch_loc_hash,
			.module_id = ss->module_id,
			.element_indices = info.indices[i],
			.element_mm = std::pair<float, float>{display->width_mm, display->height_mm},
			.screensaver_mode = true,
		};
	}

	return std::nullopt;
}

} // namespace MetaModule
