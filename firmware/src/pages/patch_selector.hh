#pragma once
#include "pages/base.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info)
		: PageBase{info}
	{}

	lv_obj_t *patch_selector;
	lv_obj_t *patch_selector_patchlist;
	lv_obj_t *slider1;
	lv_group_t *group;

	int32_t active_patch_idx = 0;

	void init() override
	{
		//Write codes patch_selector
		patch_selector = lv_obj_create(nullptr, nullptr);

		group = lv_group_create();
		lv_indev_set_group(lv_indev_get_next(nullptr), group);

		//Write codes patch_selector_patchlist
		patch_selector_patchlist = lv_dropdown_create(patch_selector, nullptr);
		lv_dropdown_set_options(patch_selector_patchlist,
								"list1\nlist2\nlist3\npatch4\npatch5\npatch6\npatch7\npatch8");
		lv_dropdown_set_max_height(patch_selector_patchlist, 200);

		//Write style LV_DROPDOWN_PART_MAIN for patch_selector_patchlist
		static lv_style_t style_patch_selector_patchlist_main;
		lv_style_reset(&style_patch_selector_patchlist_main);

		//Write style state: LV_STATE_DEFAULT for style_patch_selector_patchlist_main
		lv_style_set_radius(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_color(
			&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_dir(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(
			&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, 1);
		lv_style_set_text_color(
			&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
		// lv_style_set_text_font(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
		lv_style_set_text_line_space(&style_patch_selector_patchlist_main, LV_STATE_DEFAULT, 20);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_MAIN, &style_patch_selector_patchlist_main);

		//Write style LV_DROPDOWN_PART_SELECTED for patch_selector_patchlist
		static lv_style_t style_patch_selector_patchlist_selected;
		lv_style_reset(&style_patch_selector_patchlist_selected);

		//Write style state: LV_STATE_DEFAULT for style_patch_selector_patchlist_selected
		lv_style_set_radius(&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
		lv_style_set_bg_grad_color(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
		lv_style_set_bg_grad_dir(&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, 1);
		lv_style_set_text_color(
			&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		// lv_style_set_text_font(&style_patch_selector_patchlist_selected, LV_STATE_DEFAULT, &lv_font_simsun_12);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_SELECTED, &style_patch_selector_patchlist_selected);

		//Write style LV_DROPDOWN_PART_LIST for patch_selector_patchlist
		static lv_style_t style_patch_selector_patchlist_list;
		lv_style_reset(&style_patch_selector_patchlist_list);

		//Write style state: LV_STATE_DEFAULT for style_patch_selector_patchlist_list
		lv_style_set_radius(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, 3);
		lv_style_set_bg_color(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_color(
			&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
		lv_style_set_bg_grad_dir(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
		lv_style_set_bg_opa(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, 255);
		lv_style_set_border_color(
			&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
		lv_style_set_border_width(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, 1);
		lv_style_set_text_color(
			&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
		// lv_style_set_text_font(&style_patch_selector_patchlist_list, LV_STATE_DEFAULT, &lv_font_simsun_12);
		lv_obj_add_style(patch_selector_patchlist, LV_DROPDOWN_PART_LIST, &style_patch_selector_patchlist_list);
		lv_obj_set_pos(patch_selector_patchlist, 5, 20);
		lv_obj_set_width(patch_selector_patchlist, 310);

		lv_group_add_obj(group, patch_selector_patchlist);

		slider1 = lv_slider_create(patch_selector, nullptr);
		lv_obj_set_x(slider1, 30);
		lv_obj_set_y(slider1, 110);
		lv_obj_set_size(slider1, 10, 50);
		lv_slider_set_value(slider1, 30, LV_ANIM_OFF);

		lv_group_add_obj(group, slider1);

		active_patch_idx = patch_list.cur_patch_index();

		screen = patch_selector;
		init_bg();
	}

	void update() override
	{
		// screen.fill(Colors::white);
		// PageWidgets::setup_header(screen);
		// screen.print("Select a patch:");
		// screen.setFont(PageWidgets::subheader_font);
		// screen.drawHLine(0, box.top, box.width(), Colors::grey.Rgb565());
		// draw_active_patch_highlight_bar();
		// ScrollBoxT::draw_scroll_box();
	}

	void start_changing_patch(int32_t new_patch_index)
	{
		if (!mbox.loading_new_patch && (new_patch_index != patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
			mbox.loading_new_patch = true;
		}
	}

	void handle_changing_patch()
	{
		if (mbox.loading_new_patch && mbox.audio_is_muted) {
			auto orig_patch = patch_list.cur_patch();
			patch_player.unload_patch();
			patch_list.set_cur_patch_index(mbox.new_patch_index);
			bool ok = patch_player.load_patch(patch_list.cur_patch());
			if (!ok) {
				mbox.set_message("Can't load patch");
				patch_player.unload_patch();
				patch_player.load_patch(orig_patch);
			} else
				mbox.clear_message();

			active_patch_idx = patch_list.cur_patch_index();
			mbox.loading_new_patch = false;
		}
	}
};

} // namespace MetaModule
