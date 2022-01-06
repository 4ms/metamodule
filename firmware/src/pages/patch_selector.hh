#pragma once
#include "pages/base.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info)
		: PageBase{info} {
		_instance = this;
		_init_styles();
	}

	void init() override {
		LVGLMemory::print_mem_usage("PatchSel::init 0");

		patchsel_screen = lv_obj_create(nullptr, nullptr);

		patch_selector_patchlist = lv_dropdown_create(patchsel_screen, nullptr);
		lv_dropdown_set_text(patch_selector_patchlist, "Select a Patch:");

		lv_dropdown_clear_options(patch_selector_patchlist);
		for (int i = 0; i < patch_list.NumPatches; i++)
			lv_dropdown_add_option(patch_selector_patchlist, patch_list.get_patch_name(i).data(), i);

		lv_dropdown_set_max_height(patch_selector_patchlist, 200);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_MAIN, &style_patchlist);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_SELECTED, &style_patchlist_selected);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_LIST, &style_patchlist_list);
		lv_obj_set_pos(patch_selector_patchlist, 5, 20);
		lv_obj_set_width(patch_selector_patchlist, 310);

		init_bg(patchsel_screen);

		//Group
		lv_group_add_obj(group, patch_selector_patchlist);

		//Event callback
		lv_obj_set_event_cb(patch_selector_patchlist, patch_selector_event_cb);

		setup_popup();
	}

	void setup_popup() {
		LVGLMemory::print_mem_usage("PatchSel::setup_popup 0");
		// Container
		// TODO: better to hide/show a full-screen container? Or use a separate screen?
		// Separate screen:
		// popup_cont = lv_obj_create(nullptr, nullptr);
		// Full-screen container:
		popup_cont = lv_cont_create(patchsel_screen, nullptr);
		lv_obj_add_style(popup_cont, LV_CONT_PART_MAIN, &style_popup_cont);
		lv_cont_set_layout(popup_cont, LV_LAYOUT_OFF);
		lv_cont_set_fit(popup_cont, LV_FIT_PARENT);

		popup_patchname = lv_label_create(popup_cont, nullptr);
		lv_obj_add_style(popup_patchname, LV_LABEL_PART_MAIN, &style_popup_patchname);

		popup_desc = lv_label_create(popup_cont, nullptr);
		lv_label_set_long_mode(popup_desc, LV_LABEL_LONG_BREAK);
		lv_label_set_align(popup_desc, LV_LABEL_ALIGN_LEFT);
		lv_obj_add_style(popup_desc, LV_LABEL_PART_MAIN, &style_popup_desc);

		//Play button
		popup_playbut = lv_btn_create(popup_cont, nullptr);
		lv_obj_add_style(popup_playbut, LV_BTN_PART_MAIN, &style_popup_buttons);
		popup_playbut_label = lv_label_create(popup_playbut, nullptr);
		lv_label_set_text(popup_playbut_label, "Play");

		// Explore button
		popup_explorebut = lv_btn_create(popup_cont, popup_playbut);
		lv_obj_add_style(popup_explorebut, LV_BTN_PART_MAIN, &style_popup_buttons);
		popup_explorebut_label = lv_label_create(popup_explorebut, nullptr);
		lv_label_set_text(popup_explorebut_label, "Explore...");

		//Back image button
		popup_backbut = lv_imgbtn_create(popup_cont, nullptr);
		lv_obj_add_style(popup_backbut, LV_IMGBTN_PART_MAIN, &style_popup_backbut);
		lv_imgbtn_set_src(popup_backbut, LV_BTN_STATE_RELEASED, &back_but_orange_neg_57x100);
		lv_imgbtn_set_checkable(popup_backbut, false);

		// Layout

		// Patchname: center top
		lv_obj_set_pos(popup_patchname, 0, 0);
		lv_obj_align(popup_patchname, popup_cont, LV_ALIGN_IN_TOP_MID, 0, 0);
		lv_obj_set_size(popup_patchname, 320, 10);

		// Patch Desc: centered below patchname
		lv_obj_align(popup_desc, popup_patchname, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
		// lv_obj_set_pos(popup_desc, 0, 25);
		lv_obj_set_size(popup_desc, 320, 10);

		// Back Button: bottom left corner
		// Play button: to the right of Back, top-aligned
		// Explore button: below Play
		lv_obj_set_size(popup_backbut, 57, 100);
		lv_obj_align(popup_backbut, popup_cont, LV_ALIGN_IN_BOTTOM_LEFT, 10, -20);
		lv_obj_align(popup_playbut, popup_backbut, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
		lv_obj_align(popup_explorebut, popup_playbut, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

		// group
		popup_group = lv_group_create();
		lv_group_set_wrap(popup_group, true);
		lv_group_add_obj(popup_group, popup_playbut);
		lv_group_add_obj(popup_group, popup_explorebut);
		lv_group_add_obj(popup_group, popup_backbut);
		lv_obj_set_event_cb(popup_backbut, patch_selector_event_cb);
		lv_obj_set_event_cb(popup_playbut, patch_selector_event_cb);
		lv_obj_set_event_cb(popup_explorebut, patch_selector_event_cb);

		hide_popup();
	}

	void show_popup() {
		LVGLMemory::print_mem_usage("PatchSel::show_popup 0");
		lv_indev_set_group(lv_indev_get_next(nullptr), popup_group);
		lv_group_set_editing(popup_group, false);
		//Popup is a container:
		lv_obj_set_hidden(popup_cont, false);
		// Popup is a screen:
		//	lv_scr_load(popup_cont);
		LVGLMemory::print_mem_usage("PatchSel::show_popup 1");
	}

	void hide_popup() {
		LVGLMemory::print_mem_usage("PatchSel::hide_popup 0");
		//Popup is a container:
		lv_obj_set_hidden(popup_cont, true);
		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_set_editing(group, true);
		// Popup is a screen:
		// focus(PageChangeDirection::Jump);
		LVGLMemory::print_mem_usage("PatchSel::hide_popup 1");
	}

	void update() override {
		handle_changing_patch();
	}

	void blur() override {
		hide_popup();
	}

	static void patch_selector_event_cb(lv_obj_t *obj, lv_event_t event) {
		switch (event) {
			case LV_EVENT_VALUE_CHANGED: {
				if (obj == _instance->patch_selector_patchlist) {
					selected_patch = lv_dropdown_get_selected(obj);
					lv_label_set_text(_instance->popup_patchname, _instance->patch_list.get_patch_name(selected_patch));
					lv_label_set_text(_instance->popup_desc, "TODO: Patch descriptions...");
					lv_obj_realign(_instance->popup_patchname);
					lv_obj_realign(_instance->popup_desc);
					_instance->show_popup();
					printf("Event obj is patch_selector_patchlist\n");

					// } else if (obj == _instance->popup_playbut) {
					// 	printf("C Play\n\r");
					// } else if (obj == _instance->popup_explorebut) {
					// 	printf("Clicked Explore\n\r");
					// } else if (obj == _instance->popup_backbut) {
					// 	printf("Clicked Back\n\r");
				} else
					printf("Event obj not known\n\r");

			} break;

			case LV_EVENT_CLICKED: {
				if (obj == _instance->popup_explorebut) {
					printf("Clicked Explore\n\r");

				} else if (obj == _instance->popup_playbut) {
					printf("Clicked Play: playing patch# %d\n\r", selected_patch);
					_instance->start_changing_patch(selected_patch);
					_instance->hide_popup();

				} else if (obj == _instance->popup_backbut) {
					printf("Clicked Back\n\r");
					_instance->hide_popup();
				}
			} break;

			default:
				// printf("Event = %s, obj.coords = {%d, %d}, {%d, %d}. obj=%p\n\r",
				// 	   LVGLStrings::Events[event].data(),
				// 	   obj->coords.x1,
				// 	   obj->coords.y1,
				// 	   obj->coords.x2,
				// 	   obj->coords.y2,
				// 	   obj);
				break;
		}
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

private:
	static inline PatchSelectorPage *_instance;
	static inline uint32_t selected_patch = 0;

	lv_group_t *popup_group;

	lv_obj_t *patchsel_screen;
	lv_obj_t *patch_selector_patchlist;

	lv_obj_t *popup_cont;
	lv_obj_t *popup_patchname;
	lv_obj_t *popup_desc;
	lv_obj_t *popup_backbut;
	lv_obj_t *popup_playbut;
	lv_obj_t *popup_explorebut;
	lv_obj_t *popup_playbut_label;
	lv_obj_t *popup_explorebut_label;

	lv_style_t style_patchlist;
	lv_style_t style_patchlist_selected;
	lv_style_t style_patchlist_list;
	lv_style_t style_popup_cont;
	lv_style_t style_popup_buttons;
	lv_style_t style_popup_backbut;
	lv_style_t style_popup_desc;
	lv_style_t style_popup_patchname;

	void _init_styles() {
		// Patch list styles
		lv_style_init(&style_patchlist);
		lv_style_set_radius(&style_patchlist, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(&style_patchlist, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_border_color(&style_patchlist, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patchlist, LV_STATE_DEFAULT, 2);
		lv_style_set_text_color(&style_patchlist, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
		lv_style_set_text_font(&style_patchlist, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_14);
		lv_style_set_text_line_space(&style_patchlist, LV_STATE_DEFAULT, 20);

		lv_style_init(&style_patchlist_selected);
		lv_style_set_radius(&style_patchlist_selected, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(&style_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
		lv_style_set_border_color(&style_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patchlist_selected, LV_STATE_DEFAULT, 1);
		lv_style_set_text_color(&style_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_text_font(&style_patchlist_selected, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_14);

		lv_style_init(&style_patchlist_list);
		lv_style_set_radius(&style_patchlist_list, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(&style_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_border_color(&style_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patchlist_list, LV_STATE_DEFAULT, 1);
		lv_style_set_text_color(&style_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
		lv_style_set_text_font(&style_patchlist_list, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_14);

		// Popup styles:
		lv_style_init(&style_popup_cont);
		lv_style_set_radius(&style_popup_cont, LV_STATE_DEFAULT, 0);
		lv_style_set_bg_color(&style_popup_cont, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
		lv_style_set_bg_opa(&style_popup_cont, LV_STATE_DEFAULT, 255);
		//lv_style_set_border_color(&style_popup_cont, LV_STATE_DEFAULT, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_border_width(&style_popup_cont, LV_STATE_DEFAULT, 0);
		lv_style_set_border_opa(&style_popup_cont, LV_STATE_DEFAULT, 0);
		lv_style_set_pad_inner(&style_popup_cont, LV_STATE_DEFAULT, 10);
		lv_style_set_pad_right(&style_popup_cont, LV_STATE_DEFAULT, 4);
		lv_style_set_pad_left(&style_popup_cont, LV_STATE_DEFAULT, 4);
		lv_style_set_pad_top(&style_popup_cont, LV_STATE_DEFAULT, 4);
		lv_style_set_pad_bottom(&style_popup_cont, LV_STATE_DEFAULT, 4);

		lv_style_init(&style_popup_buttons);
		lv_style_set_radius(&style_popup_buttons, LV_STATE_DEFAULT, 8);
		lv_style_set_bg_color(&style_popup_buttons, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_color(&style_popup_buttons, LV_STATE_FOCUSED, lv_color_make(0xd6, 0xdd, 0x53));
		lv_style_set_bg_color(&style_popup_buttons, LV_STATE_PRESSED, lv_color_make(0xf6, 0xdd, 0x53));
		lv_style_set_bg_opa(&style_popup_buttons, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(&style_popup_buttons, LV_STATE_DEFAULT, lv_color_make(0x32, 0x32, 0x32));
		lv_style_set_border_width(&style_popup_buttons, LV_STATE_DEFAULT, 2);
		lv_style_set_text_color(&style_popup_buttons, LV_STATE_DEFAULT, lv_color_make(0x32, 0x32, 0x32));
		lv_style_set_pad_inner(&style_popup_buttons, LV_STATE_DEFAULT, 8);
		lv_style_set_pad_hor(&style_popup_buttons, LV_STATE_DEFAULT, 4);
		lv_style_set_pad_ver(&style_popup_buttons, LV_STATE_DEFAULT, 4);
		lv_style_set_margin_hor(&style_popup_buttons, LV_STATE_DEFAULT, 8);
		lv_style_set_margin_ver(&style_popup_buttons, LV_STATE_DEFAULT, 8);

		lv_style_init(&style_popup_backbut);
		lv_style_set_pad_left(&style_popup_backbut, LV_STATE_DEFAULT, 5);
		lv_style_set_pad_right(&style_popup_backbut, LV_STATE_DEFAULT, 5);
		lv_style_set_pad_top(&style_popup_backbut, LV_STATE_DEFAULT, 5);
		lv_style_set_pad_bottom(&style_popup_backbut, LV_STATE_DEFAULT, 5);
		lv_style_set_image_opa(&style_popup_backbut, LV_STATE_DEFAULT, 255);
		lv_style_set_margin_hor(&style_popup_backbut, LV_STATE_DEFAULT, 8);

		lv_style_init(&style_popup_desc);
		lv_style_set_radius(&style_popup_desc, LV_STATE_DEFAULT, 0);
		lv_style_set_bg_color(&style_popup_desc, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_opa(&style_popup_desc, LV_STATE_DEFAULT, 255);
		lv_style_set_text_color(&style_popup_desc, LV_STATE_DEFAULT, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_text_font(&style_popup_desc, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_500_16);
		lv_style_set_text_letter_space(&style_popup_desc, LV_STATE_DEFAULT, 0);
		lv_style_set_text_line_space(&style_popup_desc, LV_STATE_DEFAULT, 12);
		lv_style_set_pad_left(&style_popup_desc, LV_STATE_DEFAULT, 4);
		lv_style_set_pad_right(&style_popup_desc, LV_STATE_DEFAULT, 4);
		lv_style_set_pad_top(&style_popup_desc, LV_STATE_DEFAULT, 3);
		lv_style_set_pad_bottom(&style_popup_desc, LV_STATE_DEFAULT, 2);

		lv_style_init(&style_popup_patchname);
		lv_style_set_radius(&style_popup_patchname, LV_STATE_DEFAULT, 0);
		lv_style_set_bg_color(&style_popup_patchname, LV_STATE_DEFAULT, lv_color_make(0xa0, 0xa0, 0xa0));
		lv_style_set_bg_opa(&style_popup_patchname, LV_STATE_DEFAULT, 255);
		lv_style_set_text_color(&style_popup_patchname, LV_STATE_DEFAULT, lv_color_make(0x1c, 0x1c, 0x1c));
		lv_style_set_text_font(&style_popup_patchname, LV_STATE_DEFAULT, &lv_font_MuseoSansRounded_700_17);
		lv_style_set_text_letter_space(&style_popup_patchname, LV_STATE_DEFAULT, 1);
		lv_style_set_pad_left(&style_popup_patchname, LV_STATE_DEFAULT, 6);
		lv_style_set_pad_right(&style_popup_patchname, LV_STATE_DEFAULT, 6);
		lv_style_set_pad_top(&style_popup_patchname, LV_STATE_DEFAULT, 4);
		lv_style_set_pad_bottom(&style_popup_patchname, LV_STATE_DEFAULT, 2);
	}
};

} // namespace MetaModule
