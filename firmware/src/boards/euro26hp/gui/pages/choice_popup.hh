#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "src/core/lv_group.h"
#include <functional>
#include <span>
#include <string>
#include <string_view>

namespace MetaModule
{

struct ChoicePopup : ConfirmPopup {

	ChoicePopup()
		: ConfirmPopup{} {
	}

	void init(lv_obj_t *page_base, lv_group_t *current_group) {
		ConfirmPopup::init(page_base, current_group);
	}

	void show(
		auto cb, const char *message, std::string_view confirm_text, const char *options, const unsigned init_idx = 0) {
		ConfirmPopup::show(std::move(cb), message, confirm_text, "");
		lv_obj_set_width(ui_DelMapLabel, 220);

		dropdown = lv_dropdown_create(ui_DelMapPopUpPanel);
		lv_obj_move_to_index(dropdown, 1);
		lv_dropdown_clear_options(dropdown);
		lv_obj_add_style(dropdown, &Gui::dropdown_style, LV_PART_MAIN);
		lv_obj_add_style(dropdown, &Gui::dropdown_style_selected, LV_PART_SELECTED);
		lv_obj_add_style(dropdown, &Gui::focus_style, LV_STATE_FOCUS_KEY);
		lv_obj_set_style_text_line_space(lv_dropdown_get_list(dropdown), 6, LV_PART_MAIN);
		lv_obj_set_width(dropdown, 180);

		lv_show(dropdown);
		lv_dropdown_set_options(dropdown, options);
		lv_dropdown_set_selected(dropdown, init_idx);

		remove_all_event_cb(ui_CancelButton);
		lv_obj_add_event_cb(ui_CancelButton, button_callback, LV_EVENT_CLICKED, this);
		remove_all_event_cb(ui_ConfirmButton);
		lv_obj_add_event_cb(ui_ConfirmButton, button_callback, LV_EVENT_CLICKED, this);

		lv_group_remove_all_objs(group);

		lv_group_add_obj(group, dropdown);
		lv_group_add_obj(group, ui_CancelButton);
		lv_group_add_obj(group, ui_ConfirmButton);
		lv_group_focus_obj(ui_ConfirmButton);

		lv_label_set_text(ui_CancelLabel, "Cancel");
	}

	void hide() {
		ConfirmPopup::hide();
		lv_obj_set_width(ui_DelMapLabel, 180);
		lv_obj_del(dropdown);
	}

	bool is_visible() {
		return visible;
	}

	static void button_callback(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ChoicePopup *>(event->user_data);
		if (!page)
			return;

		if (page->callback) {
			if (event->target == ui_CancelButton)
				page->callback(0);

			else if (event->target == ui_ConfirmButton) {
				auto selected = lv_dropdown_get_selected(page->dropdown) + 1;
				page->callback(selected);
			}
		}

		page->hide();
	}

private:
	lv_obj_t *dropdown{};
};

} // namespace MetaModule
