#pragma once
#include "pages/base.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info)
		: PageBase{info} {
		_instance = this;
	}
	static inline PatchSelectorPage *_instance;

	lv_obj_t *patch_selector;
	lv_obj_t *patch_selector_patchlist;

	static void patch_selector_event_cb(lv_obj_t *obj, lv_event_t event) {
		switch (event) {
			case LV_EVENT_VALUE_CHANGED: {
				uint16_t sel = lv_dropdown_get_selected(obj);
				if (sel != _instance->patch_list.cur_patch_index())
					_instance->start_changing_patch(sel);
			} break;

			default:
				break;
		}
	}

	void init() override {
		patch_selector = lv_obj_create(nullptr, nullptr);

		patch_selector_patchlist = lv_dropdown_create(patch_selector, nullptr);
		lv_dropdown_set_text(patch_selector_patchlist, "Select a Patch:");

		lv_dropdown_clear_options(patch_selector_patchlist);
		for (int i = 0; i < patch_list.NumPatches; i++)
			lv_dropdown_add_option(patch_selector_patchlist, patch_list.get_patch_name(i), i);

		lv_dropdown_set_max_height(patch_selector_patchlist, 200);

		//Write style LV_DROPDOWN_PART_MAIN for patch_selector_patchlist
		static lv_style_t style_patch_selector_patchlist_main;
		lv_style_reset(&style_patch_selector_patchlist_main);

		//Write style state: LV_STATE_DEFAULT for style_patch_selector_patchlist_main
		lv_style_set_radius(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_border_color(
			&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, 2);
		lv_style_set_text_color(
			&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
		lv_style_set_text_font(
			&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_14);
		lv_style_set_text_line_space(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, 20);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_MAIN, &style_patch_selector_patchlist_main);

		static lv_style_t style_patch_selector_patchlist_selected;
		lv_style_reset(&style_patch_selector_patchlist_selected);

		lv_style_set_radius(&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
		lv_style_set_border_color(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, 1);
		lv_style_set_text_color(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_text_font(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_14);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_SELECTED, &style_patch_selector_patchlist_selected);

		static lv_style_t style_patch_selector_patchlist_list;
		lv_style_reset(&style_patch_selector_patchlist_list);

		lv_style_set_radius(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_border_color(
			&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, 1);
		lv_style_set_text_color(
			&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
		lv_style_set_text_font(
			&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_14);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_LIST, &style_patch_selector_patchlist_list);
		lv_obj_set_pos(patch_selector_patchlist, 5, 20);
		lv_obj_set_width(patch_selector_patchlist, 310);

		init_bg(patch_selector);

		//Group
		lv_group_add_obj(group, patch_selector_patchlist);

		//Event callback
		lv_obj_set_event_cb(patch_selector_patchlist, patch_selector_event_cb);

		//hack: set base of dropdown1b to be our own screen:
		ui->Dropdown1b = patch_selector;
		setup_scr_Dropdown1b(ui);
	}

	void update() override {
		handle_changing_patch();
	}

	void start_changing_patch(int32_t new_patch_index) {
		if (!mbox.loading_new_patch && (new_patch_index != patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
			mbox.loading_new_patch = true;
			printf("Loading patch %s\n\r", patch_list.get_patch_name(new_patch_index).c_str());
		}
	}

	void handle_changing_patch() {
		if (mbox.loading_new_patch && mbox.audio_is_muted) {
			auto orig_patch = patch_list.cur_patch();
			patch_player.unload_patch();
			patch_list.set_cur_patch_index(mbox.new_patch_index);
			bool ok = patch_player.load_patch(patch_list.cur_patch());
			if (!ok) {
				mbox.set_message("Can't load patch");
				printf("Can't load patch\n\r");
				patch_player.unload_patch();
				patch_player.load_patch(orig_patch);
			} else
				mbox.clear_message();

			mbox.loading_new_patch = false;
		}
	}
};

} // namespace MetaModule
