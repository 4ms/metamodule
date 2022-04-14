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

		patchsel_screen = lv_obj_create(nullptr);

		patch_selector_patchlist = lv_dropdown_create(patchsel_screen);
		lv_dropdown_set_text(patch_selector_patchlist, "Select a Patch:");

		refresh_patchlist();

		//lv_dropdown_set_max_height(patch_selector_patchlist, 200);
		lv_obj_set_style_max_height(patch_selector_patchlist, 200, LV_PART_MAIN);
		lv_obj_add_style(patch_selector_patchlist, &style_patchlist, LV_PART_MAIN);
		lv_obj_add_style(patch_selector_patchlist, &style_patchlist_selected, LV_PART_SELECTED);
		lv_obj_add_style(patch_selector_patchlist, &style_patchlist_list, LV_PART_ITEMS); //LV_DROPDOWN_PART_LIST,
		lv_obj_set_pos(patch_selector_patchlist, 5, 20);
		lv_obj_set_width(patch_selector_patchlist, 310);

		init_bg(patchsel_screen);

		//Group
		lv_group_add_obj(group, patch_selector_patchlist);

		//Event callback
		lv_obj_add_event_cb(patch_selector_patchlist, patchlist_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);

		setup_popup();
	}

	void refresh_patchlist() {
		lv_dropdown_clear_options(patch_selector_patchlist);
		for (unsigned i = 0; i < patch_list.num_patches(); i++)
			lv_dropdown_add_option(patch_selector_patchlist, patch_list.get_patch_name(i).data(), i);
	}

	void setup_popup() {
		LVGLMemory::print_mem_usage("PatchSel::setup_popup 0");
		// Container
		// TODO: better to hide/show a full-screen container? Or use a separate screen?
		// Separate screen:
		// popup_cont = lv_obj_create(nullptr, nullptr);
		// Full-screen container:
		popup_cont = lv_obj_create(patchsel_screen);
		lv_obj_add_style(popup_cont, &style_popup_cont, LV_PART_MAIN);
		lv_obj_set_flex_flow(popup_cont, LV_FLEX_FLOW_ROW);

		// lv_cont_set_layout(popup_cont, LV_LAYOUT_OFF);
		// lv_cont_set_fit(popup_cont, LV_FIT_PARENT);

		popup_patchname = lv_label_create(popup_cont);
		lv_obj_add_style(popup_patchname, &style_popup_patchname, LV_PART_MAIN);

		popup_desc = lv_label_create(popup_cont);
		lv_label_set_long_mode(popup_desc, LV_LABEL_LONG_DOT);
		//lv_label_set_align(popup_desc, LV_LABEL_ALIGN_LEFT);
		lv_obj_add_style(popup_desc, &style_popup_desc, LV_PART_MAIN);

		//Play button
		popup_playbut = lv_btn_create(popup_cont);
		lv_obj_add_style(popup_playbut, &style_popup_buttons, LV_PART_MAIN);

		// lv_obj_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xc3, 0x70)); //LV_STATE_FOCUSED,
		// lv_style_set_bg_color(&style_popup_buttons,  lv_color_make(0xf6, 0xdd, 0x53));//LV_STATE_PRESSED,
		popup_playbut_label = lv_label_create(popup_playbut);
		lv_label_set_text(popup_playbut_label, "Play");

		// Explore button
		popup_explorebut = lv_btn_create(popup_cont);
		lv_obj_add_style(popup_explorebut, &style_popup_buttons, LV_PART_MAIN);
		popup_explorebut_label = lv_label_create(popup_explorebut);
		lv_label_set_text(popup_explorebut_label, "Explore...");

		//Back image button
		popup_backbut = lv_btn_create(popup_cont);
		lv_obj_add_style(popup_backbut, &style_popup_backbut, LV_PART_MAIN);
		popup_backbut_label = lv_label_create(popup_backbut);
		lv_label_set_text(popup_backbut_label, "Explore...");

		// Layout

		// Patchname: center top
		// lv_obj_set_pos(popup_patchname, 0, 0);
		// lv_obj_align(popup_patchname, popup_cont, LV_ALIGN_IN_TOP_MID, 0, 0);
		// lv_obj_set_size(popup_patchname, 320, 10);

		// // Patch Desc: centered below patchname
		// lv_obj_align(popup_desc, popup_patchname, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
		// // lv_obj_set_pos(popup_desc, 0, 25);
		// lv_obj_set_size(popup_desc, 320, 10);

		// // Explore button: bottom center, up 10px
		// lv_obj_align(popup_explorebut, popup_cont, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
		// // Play button, above Explore, up 10px
		// lv_obj_align(popup_playbut, popup_explorebut, LV_ALIGN_OUT_TOP_MID, 0, -10);
		// // Back button: to the left of Play, top-aligned, 10px spacing
		// lv_obj_align(popup_backbut, popup_playbut, LV_ALIGN_OUT_LEFT_TOP, -10, 0);

		// Popup Group
		popup_group = lv_group_create();
		lv_group_set_wrap(popup_group, true);
		lv_group_add_obj(popup_group, popup_playbut);
		lv_group_add_obj(popup_group, popup_explorebut);
		lv_group_add_obj(popup_group, popup_backbut);

		lv_obj_add_event_cb(popup_backbut, popup_back_event_cb, LV_EVENT_CLICKED, nullptr);
		lv_obj_add_event_cb(popup_playbut, popup_play_event_cb, LV_EVENT_CLICKED, nullptr);
		lv_obj_add_event_cb(popup_explorebut, popup_explore_event_cb, LV_EVENT_CLICKED, nullptr);

		hide_popup();

		wait_cont = lv_obj_create(patchsel_screen);
		lv_obj_set_align(wait_cont, LV_ALIGN_CENTER);
		lv_obj_add_style(wait_cont, &style_wait_cont, LV_PART_MAIN);
		// lv_cont_set_layout(wait_cont, LV_LAYOUT_CENTER);
		// lv_cont_set_fit(wait_cont, LV_FIT_TIGHT);
		lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);

		wait_text = lv_label_create(wait_cont);
		lv_obj_add_style(wait_text, &style_popup_patchname, LV_PART_MAIN);
		lv_obj_set_align(wait_text, LV_ALIGN_CENTER);
		lv_label_set_text(wait_text, "Refreshing Patches...");

		wait_group = lv_group_create();
	}

	void show_popup() {
		LVGLMemory::print_mem_usage("PatchSel::show_popup 0");
		lv_indev_set_group(lv_indev_get_next(nullptr), popup_group);
		lv_group_set_editing(popup_group, false);
		lv_group_focus_obj(popup_backbut);
		//Popup is a container:
		lv_obj_clear_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
		// Popup is a screen:
		//	lv_scr_load(popup_cont);
		LVGLMemory::print_mem_usage("PatchSel::show_popup 1");
	}

	void hide_popup() {
		LVGLMemory::print_mem_usage("PatchSel::hide_popup 0");
		//Popup is a container:
		lv_obj_add_flag(popup_cont, LV_OBJ_FLAG_HIDDEN);
		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_set_editing(group, true);
		// Popup is a screen:
		// focus(PageChangeDirection::Jump);
		LVGLMemory::print_mem_usage("PatchSel::hide_popup 1");
	}

	void update() override {
		if (!patch_list.is_ready()) {
			if (patchlist_ready) {
				lv_indev_set_group(lv_indev_get_next(nullptr), wait_group);
				lv_obj_clear_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
				patchlist_ready = false;
			}
			return;
		}

		if (!patchlist_ready) {
			lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
			// Hide the popup as well:
			lv_obj_add_flag(popup_cont, LV_OBJ_FLAG_HIDDEN);
			lv_indev_set_group(lv_indev_get_next(nullptr), group);
			lv_group_set_editing(group, true);
			patchlist_ready = true;
		}

		handle_changing_patch();
		if (mbox.patchlist_updated) {
			refresh_patchlist();
			mbox.patchlist_updated = false;
		}
	}

	void blur() override {
		hide_popup();
	}

	static void popup_play_event_cb(lv_event_t *event) {
		printf("Clicked Play: playing patch# %d\n\r", selected_patch);
		_instance->start_changing_patch(selected_patch);
		_instance->hide_popup();
	}

	static void popup_back_event_cb(lv_event_t *event) {
		printf("Clicked Back\n\r");
		_instance->hide_popup();
	}

	static void popup_explore_event_cb(lv_event_t *event) {
		printf("Clicked Explore\n\r");
	}

	static void patchlist_event_cb(lv_event_t *event) {
		auto obj = _instance->patch_selector_patchlist;
		selected_patch = lv_dropdown_get_selected(obj);
		lv_label_set_text(_instance->popup_patchname, _instance->patch_list.get_patch_name(selected_patch));
		lv_label_set_text(_instance->popup_desc, "TODO: Patch descriptions...");
		// how to redraw?
		// lv_obj_realign(_instance->popup_patchname);
		// lv_obj_realign(_instance->popup_desc);
		_instance->show_popup();
		printf("Event obj is patch_selector_patchlist\n\r");
	}

	// static void patch_selector_event_cb(lv_obj_t *obj, lv_event_t event) {
	// 	switch (event) {
	// 		case LV_EVENT_VALUE_CHANGED: {
	// 			if (obj == _instance->patch_selector_patchlist) {
	// 				selected_patch = lv_dropdown_get_selected(obj);
	// 				lv_label_set_text(_instance->popup_patchname, _instance->patch_list.get_patch_name(selected_patch));
	// 				lv_label_set_text(_instance->popup_desc, "TODO: Patch descriptions...");
	// 				lv_obj_realign(_instance->popup_patchname);
	// 				lv_obj_realign(_instance->popup_desc);
	// 				_instance->show_popup();
	// 				printf("Event obj is patch_selector_patchlist\n\r");

	// 				// } else if (obj == _instance->popup_playbut) {
	// 				// 	printf("C Play\n\r");
	// 				// } else if (obj == _instance->popup_explorebut) {
	// 				// 	printf("Clicked Explore\n\r");
	// 				// } else if (obj == _instance->popup_backbut) {
	// 				// 	printf("Clicked Back\n\r");
	// 			} else
	// 				printf("Event obj not known\n\r");

	// 		} break;

	// 		case LV_EVENT_CLICKED: {
	// 			if (obj == _instance->popup_explorebut) {
	// 				printf("Clicked Explore\n\r");

	// 			} else if (obj == _instance->popup_playbut) {
	// 				printf("Clicked Play: playing patch# %d\n\r", selected_patch);
	// 				_instance->start_changing_patch(selected_patch);
	// 				_instance->hide_popup();

	// 			} else if (obj == _instance->popup_backbut) {
	// 				printf("Clicked Back\n\r");
	// 				_instance->hide_popup();
	// 			}
	// 		} break;

	// 		default:
	// 			// printf("Event = %s, obj.coords = {%d, %d}, {%d, %d}. obj=%p\n\r",
	// 			// 	   LVGLStrings::Events[event].data(),
	// 			// 	   obj->coords.x1,
	// 			// 	   obj->coords.y1,
	// 			// 	   obj->coords.x2,
	// 			// 	   obj->coords.y2,
	// 			// 	   obj);
	// 			break;
	// 	}
	// }

	void start_changing_patch(int32_t new_patch_index) {
		if (!mbox.loading_new_patch && (new_patch_index != (int32_t)patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
			mbox.loading_new_patch = true;
			printf("Loading patch %s\n\r", patch_list.get_patch_name(new_patch_index).data());
		}
	}

	void handle_changing_patch() {
		if (mbox.loading_new_patch && mbox.audio_is_muted) {
			auto cur_patch_index = patch_list.cur_patch_index();
			auto orig_patch_data = patch_list.get_patch(cur_patch_index);
			patch_player.unload_patch();
			patch_list.set_cur_patch_index(mbox.new_patch_index);
			bool ok = patch_player.load_patch(patch_list.get_patch(mbox.new_patch_index));
			if (!ok) {
				mbox.append_message("Can't load patch\n\r");
				printf("Can't load patch\n\r");
				patch_player.unload_patch();
				patch_player.load_patch(orig_patch_data);
			} else
				mbox.append_message("Patch loaded\n\r");

			mbox.loading_new_patch = false;
		}
	}

private:
	static inline PatchSelectorPage *_instance;
	static inline uint32_t selected_patch = 0;
	bool patchlist_ready = true;

	lv_group_t *popup_group;
	lv_group_t *wait_group;

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
	lv_obj_t *popup_backbut_label;

	lv_obj_t *wait_cont;
	lv_obj_t *wait_text;

	lv_style_t style_patchlist;
	lv_style_t style_patchlist_selected;
	lv_style_t style_patchlist_list;
	lv_style_t style_popup_cont;
	lv_style_t style_popup_buttons;
	lv_style_t style_popup_backbut;
	lv_style_t style_popup_desc;
	lv_style_t style_popup_patchname;

	lv_style_t style_wait_cont;

	void _init_styles() {
		// Patch list styles
		lv_style_init(&style_patchlist);
		lv_style_set_radius(&style_patchlist, 3);
		lv_style_set_bg_color(&style_patchlist, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_border_color(&style_patchlist, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patchlist, 2);
		lv_style_set_text_color(&style_patchlist, lv_color_make(0x0D, 0x30, 0x55));
		lv_style_set_text_font(&style_patchlist, &lv_font_MuseoSansRounded_700_14);
		lv_style_set_text_line_space(&style_patchlist, 20);

		lv_style_init(&style_patchlist_selected);
		lv_style_set_radius(&style_patchlist_selected, 3);
		lv_style_set_bg_color(&style_patchlist_selected, lv_color_make(0x00, 0xa1, 0xb5));
		lv_style_set_border_color(&style_patchlist_selected, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patchlist_selected, 1);
		lv_style_set_text_color(&style_patchlist_selected, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_text_font(&style_patchlist_selected, &lv_font_MuseoSansRounded_700_14);

		lv_style_init(&style_patchlist_list);
		lv_style_set_radius(&style_patchlist_list, 3);
		lv_style_set_bg_color(&style_patchlist_list, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_border_color(&style_patchlist_list, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patchlist_list, 1);
		lv_style_set_text_color(&style_patchlist_list, lv_color_make(0x0D, 0x30, 0x55));
		lv_style_set_text_font(&style_patchlist_list, &lv_font_MuseoSansRounded_700_14);

		// Popup styles:
		lv_style_init(&style_popup_cont);
		lv_style_set_radius(&style_popup_cont, 0);
		lv_style_set_bg_color(&style_popup_cont, lv_color_make(0xe6, 0xe6, 0xe6));
		lv_style_set_bg_opa(&style_popup_cont, 255);
		//lv_style_set_border_color(&style_popup_cont, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_border_width(&style_popup_cont, 0);
		lv_style_set_border_opa(&style_popup_cont, 0);
		lv_style_set_pad_gap(&style_popup_cont, 10);
		lv_style_set_pad_all(&style_popup_cont, 4);

		lv_style_init(&style_popup_buttons);
		lv_style_set_radius(&style_popup_buttons, 8);
		lv_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xff, 0xff));
		// lv_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xc3, 0x70));//LV_STATE_FOCUSED,
		// lv_style_set_bg_color(&style_popup_buttons,  lv_color_make(0xf6, 0xdd, 0x53));//LV_STATE_PRESSED,
		lv_style_set_bg_opa(&style_popup_buttons, 255);
		lv_style_set_border_color(&style_popup_buttons, lv_color_make(0x32, 0x32, 0x32));
		lv_style_set_border_width(&style_popup_buttons, 2);
		lv_style_set_text_color(&style_popup_buttons, lv_color_make(0x32, 0x32, 0x32));

		lv_style_init(&style_popup_backbut);
		// lv_style_set_image_opa(&style_popup_backbut, 255);
		//FOCUSED state:
		lv_style_set_radius(&style_popup_backbut, 6);
		lv_style_set_outline_color(&style_popup_backbut, lv_color_hex(0xabcdef));
		lv_style_set_outline_width(&style_popup_backbut, LV_DPX(2));
		lv_style_set_outline_opa(&style_popup_backbut, LV_OPA_0);
		// lv_style_set_outline_opa(&style_popup_backbut, LV_STATE_FOCUSED, LV_OPA_50);
		// lv_style_set_image_recolor(&style_popup_backbut, LV_STATE_FOCUSED, lv_color_hex(0x888888));
		//lv_style_set_outline_pad(&style_popup_backbut, LV_STATE_FOCUSED, 4);
		//lv_style_set_outline_blend_mode(&style_popup_backbut, LV_STATE_FOCUSED, LV_BLEND_MODE_NORMAL);

		lv_style_init(&style_popup_desc);
		lv_style_set_radius(&style_popup_desc, 0);
		// lv_style_set_bg_color(&style_popup_desc, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_opa(&style_popup_desc, 0);
		lv_style_set_text_color(&style_popup_desc, lv_color_make(0x78, 0x78, 0x78));
		lv_style_set_text_font(&style_popup_desc, &lv_font_MuseoSansRounded_500_16);
		lv_style_set_text_letter_space(&style_popup_desc, 0);
		lv_style_set_text_line_space(&style_popup_desc, 12);
		lv_style_set_pad_left(&style_popup_desc, 4);
		lv_style_set_pad_right(&style_popup_desc, 4);
		lv_style_set_pad_top(&style_popup_desc, 3);
		lv_style_set_pad_bottom(&style_popup_desc, 2);

		lv_style_init(&style_popup_patchname);
		// lv_style_set_radius(&style_popup_patchname, 0);
		// lv_style_set_bg_color(&style_popup_patchname, lv_color_make(0xa0, 0xa0, 0xa0));
		lv_style_set_bg_opa(&style_popup_patchname, 0);
		lv_style_set_text_color(&style_popup_patchname, lv_color_make(0x1c, 0x1c, 0x1c));
		lv_style_set_text_font(&style_popup_patchname, &lv_font_MuseoSansRounded_700_17);
		lv_style_set_text_letter_space(&style_popup_patchname, 1);
		lv_style_set_pad_left(&style_popup_patchname, 6);
		lv_style_set_pad_right(&style_popup_patchname, 6);
		lv_style_set_pad_top(&style_popup_patchname, 4);
		lv_style_set_pad_bottom(&style_popup_patchname, 4);

		// Wait cont style
		lv_style_init(&style_wait_cont);
		lv_style_set_radius(&style_wait_cont, 2);
		lv_style_set_bg_color(&style_wait_cont, lv_color_make(0xe6, 0xe6, 0xe6));
		lv_style_set_bg_opa(&style_wait_cont, 255);
		lv_style_set_border_color(&style_wait_cont, lv_color_make(0xff, 0xc3, 0x70));
		lv_style_set_border_width(&style_wait_cont, 1);
		lv_style_set_border_opa(&style_wait_cont, 255);
		lv_style_set_pad_gap(&style_wait_cont, 10);
		lv_style_set_pad_all(&style_wait_cont, 10);
	}
};

} // namespace MetaModule
