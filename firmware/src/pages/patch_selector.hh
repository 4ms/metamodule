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
	static inline lv_group_t *popup_group;

	lv_obj_t *patch_selector;
	lv_obj_t *patch_selector_patchlist;

	static void patch_selector_event_cb(lv_obj_t *obj, lv_event_t event) {
		switch (event) {
			case LV_EVENT_VALUE_CHANGED: {
				if (obj == _instance->patch_selector_patchlist) {
					uint16_t sel = lv_dropdown_get_selected(obj);
					// lv_label_set_text(ui->Dropdown1b_patch_name, _instance->patch_list.get_patch_name(sel));
					// lv_label_set_text(ui->Dropdown1b_patch_description, "TODO: Patch descriptions...");

					// lv_group_set_editing(_instance->group, false);
					// lv_obj_set_hidden(ui->Dropdown1b_cont, false);
					// lv_indev_set_group(lv_indev_get_next(nullptr), popup_group);
					// lv_group_set_editing(popup_group, true);
					// printf("Event is patch_selector_patchlist\n");

					if (sel != _instance->patch_list.cur_patch_index())
						_instance->start_changing_patch(sel);
				} else
					printf("Event not patch_selector_patchlist\n");

			} break;

			default:
				printf("Event not LV_EVENT_VALUE_CHANGED\n");
				break;
		}
	}

	void init() override {
		patch_selector = lv_obj_create(nullptr, nullptr);

		patch_selector_patchlist = lv_dropdown_create(patch_selector, nullptr);
		lv_dropdown_set_text(patch_selector_patchlist, "Select a Patch:");

		lv_dropdown_clear_options(patch_selector_patchlist);
		for (int i = 0; i < patch_list.NumPatches; i++)
			lv_dropdown_add_option(patch_selector_patchlist, patch_list.get_patch_name(i).data(), i);

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

		// Pop-up window:

		static lv_style_t style_Dropdown1b_cont;
		lv_style_reset(&style_Dropdown1b_cont);
		lv_style_set_radius(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 5);
		lv_style_set_bg_color(&style_Dropdown1b_cont, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
		lv_style_set_bg_grad_dir(&style_Dropdown1b_cont, LV_STATE_DEFAULT, LV_GRAD_DIR_NONE);
		lv_style_set_bg_opa(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_Dropdown1b_cont, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_border_width(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 2);
		lv_style_set_border_opa(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 0);
		lv_style_set_pad_left(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 0);
		lv_style_set_pad_right(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 0);
		lv_style_set_pad_top(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 0);
		lv_style_set_pad_bottom(&style_Dropdown1b_cont, LV_STATE_DEFAULT, 0);

		static lv_style_t style_Dropdown1b_main_buttons_btn;
		lv_style_reset(&style_Dropdown1b_main_buttons_btn);
		lv_style_set_radius(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, 8);
		lv_style_set_bg_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_FOCUSED, lv_color_make(0xd6, 0xdd, 0xe3));
		lv_style_set_bg_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_PRESSED, lv_color_make(0xe6, 0xdd, 0x53));
		lv_style_set_bg_opa(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(
			&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, LV_COLOR_BLACK); //lv_color_make(0xd6, 0xdd, 0xe3));
		lv_style_set_border_width(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, 2);
		lv_style_set_text_color(&style_Dropdown1b_main_buttons_btn, LV_STATE_DEFAULT, lv_color_make(0x32, 0x32, 0x32));

		static lv_style_t style_Dropdown1b_imgbtn_1_main;
		lv_style_reset(&style_Dropdown1b_imgbtn_1_main);
		lv_style_set_pad_left(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, 5);
		lv_style_set_pad_right(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, 5);
		lv_style_set_pad_top(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, 5);
		lv_style_set_pad_bottom(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, 5);
		lv_style_set_image_opa(&style_Dropdown1b_imgbtn_1_main, LV_STATE_DEFAULT, 255);

		// Container
		ui->Dropdown1b_cont = lv_cont_create(patch_selector, nullptr);
		lv_obj_add_style(ui->Dropdown1b_cont, LV_CONT_PART_MAIN, &style_Dropdown1b_cont);
		lv_obj_set_pos(ui->Dropdown1b_cont, 20, 20);
		lv_obj_set_size(ui->Dropdown1b_cont, 280, 200);
		lv_obj_set_click(ui->Dropdown1b_cont, false);
		lv_cont_set_layout(ui->Dropdown1b_cont, LV_LAYOUT_PRETTY_BOTTOM);
		lv_cont_set_fit(ui->Dropdown1b_cont, LV_FIT_NONE);

		//Back image button
		ui->Dropdown1b_imgbtn_1 = lv_imgbtn_create(ui->Dropdown1b_cont, nullptr);
		lv_obj_add_style(ui->Dropdown1b_imgbtn_1, LV_IMGBTN_PART_MAIN, &style_Dropdown1b_imgbtn_1_main);
		lv_obj_set_size(ui->Dropdown1b_imgbtn_1, 57, 100);
		//lv_obj_set_pos(ui->Dropdown1b_imgbtn_1, 28, 143);
		//lv_obj_align(ui->Dropdown1b_imgbtn_1, ui->Dropdown1b_cont, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10);
		lv_imgbtn_set_src(ui->Dropdown1b_imgbtn_1, LV_BTN_STATE_RELEASED, &back_but_orange_neg_57x100);
		lv_imgbtn_set_checkable(ui->Dropdown1b_imgbtn_1, false);

		//Play button
		ui->Dropdown1b_button_play = lv_btn_create(ui->Dropdown1b_cont, nullptr);
		lv_obj_add_style(ui->Dropdown1b_button_play, LV_BTN_PART_MAIN, &style_Dropdown1b_main_buttons_btn);
		//lv_obj_set_pos(ui->Dropdown1b_button_play, 38, 94);
		//lv_obj_set_size(ui->Dropdown1b_button_play, 241, 104);
		ui->Dropdown1b_button_play_label = lv_label_create(ui->Dropdown1b_button_play, nullptr);
		lv_label_set_text(ui->Dropdown1b_button_play_label, "Play");

		// Explore button
		ui->Dropdown1b_button_explore = lv_btn_create(ui->Dropdown1b_cont, ui->Dropdown1b_button_play);
		ui->Dropdown1b_button_explore_label = lv_label_create(ui->Dropdown1b_button_explore, nullptr);
		lv_label_set_text(ui->Dropdown1b_button_explore_label, "Explore...");

		// Popup group
		popup_group = lv_group_create();
		lv_obj_set_click(ui->Dropdown1b_imgbtn_1, true);
		lv_obj_set_click(ui->Dropdown1b_button_play, true);
		lv_obj_set_click(ui->Dropdown1b_button_explore, true);
		//lv_group_add_obj(popup_group, ui->Dropdown1b_cont);
		lv_group_add_obj(popup_group, ui->Dropdown1b_imgbtn_1);
		lv_group_add_obj(popup_group, ui->Dropdown1b_button_play);
		lv_group_add_obj(popup_group, ui->Dropdown1b_button_explore);
		lv_obj_set_event_cb(ui->Dropdown1b_imgbtn_1, patch_selector_event_cb);
		lv_obj_set_event_cb(ui->Dropdown1b_button_play, patch_selector_event_cb);
		lv_obj_set_event_cb(ui->Dropdown1b_button_explore, patch_selector_event_cb);

		lv_obj_set_hidden(ui->Dropdown1b_cont, true);
	}

	void update() override {
		handle_changing_patch();
	}

	void focus(PageChangeDirection dir) override {
		lv_obj_set_hidden(ui->Dropdown1b_cont, true);
		PageBase::focus(dir);
	}

	void start_changing_patch(int32_t new_patch_index) {
		if (!mbox.loading_new_patch && (new_patch_index != patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
			mbox.loading_new_patch = true;
			printf("Loading patch %s\n\r", patch_list.get_patch_name(new_patch_index).data());
		}
	}

	void handle_changing_patch() {
		if (mbox.loading_new_patch && mbox.audio_is_muted) {
			auto orig_patch = patch_list.cur_patch();
			patch_player.unload_patch();
			patch_list.set_cur_patch_index(mbox.new_patch_index);
			Debug::Pin1::high();
			bool ok = patch_player.load_patch(patch_list.cur_patch());
			Debug::Pin1::low();
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
