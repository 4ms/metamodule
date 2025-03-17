#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "patch_play/text_display.hh"

namespace MetaModule
{

inline bool redraw_text(lv_obj_t *obj, std::string_view text) {
	bool is_label = lv_obj_has_class(obj, &lv_label_class);
	if (is_label) {
		if (text != lv_label_get_text(obj)) {
			lv_label_set_text(obj, text.data());
			return true;
		}
	}
	return false;
}

inline bool
redraw_text_display(DrawnElement &drawn_el,
					unsigned this_module_id,
					std::array<WatchedTextDisplay, TextDisplayWatcher::MaxDisplaysToWatch> &watch_displays) {

	bool was_redrawn = false;
	if (drawn_el.element.index() == Element{DynamicTextDisplay{}}.index()) {

		// Scan all watch_displays to find a match
		for (auto &d : watch_displays) {
			if (!d.is_active())
				continue;
			if (d.module_id != this_module_id)
				continue;
			if (d.light_id != drawn_el.gui_element.idx.light_idx)
				continue;

			was_redrawn = redraw_text(drawn_el.gui_element.obj, d.text);
			break;
		}
	}
	return was_redrawn;
}

} // namespace MetaModule
