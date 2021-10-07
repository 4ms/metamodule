#pragma once
#include "pages/base.hh"
// #include "pages/fonts.hh"
// #include "pages/page_widgets.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info)
		: PageBase{info}
	{
		ui = &base_ui;
	}

	struct {
		lv_obj_t *patch_selector;
		lv_obj_t *patch_selector_patchlist;
		lv_obj_t *slider1;
		lv_group_t *group;
	} base_ui, *ui;
	bool is_init = false;

	void init()
	{
		//Write codes patch_selector
		ui->patch_selector = lv_obj_create(nullptr, nullptr);

		ui->group = lv_group_create();
		lv_indev_set_group(lv_indev_get_next(nullptr), ui->group);

		//Write codes patch_selector_patchlist
		ui->patch_selector_patchlist = lv_dropdown_create(ui->patch_selector, nullptr);
		lv_dropdown_set_options(ui->patch_selector_patchlist,
								"list1\nlist2\nlist3\npatch4\npatch5\npatch6\npatch7\npatch8");
		lv_dropdown_set_max_height(ui->patch_selector_patchlist, 200);

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
		lv_obj_add_style(ui->patch_selector_patchlist, LV_DROPDOWN_PART_MAIN, &style_patch_selector_patchlist_main);

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
		lv_obj_add_style(
			ui->patch_selector_patchlist, LV_DROPDOWN_PART_SELECTED, &style_patch_selector_patchlist_selected);

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
		lv_obj_add_style(ui->patch_selector_patchlist, LV_DROPDOWN_PART_LIST, &style_patch_selector_patchlist_list);
		lv_obj_set_pos(ui->patch_selector_patchlist, 5, 20);
		lv_obj_set_width(ui->patch_selector_patchlist, 310);

		lv_group_add_obj(ui->group, ui->patch_selector_patchlist);

		ui->slider1 = lv_slider_create(ui->patch_selector, nullptr);
		lv_obj_set_x(ui->slider1, 30);
		lv_obj_set_y(ui->slider1, 110);
		lv_obj_set_size(ui->slider1, 10, 50);
		lv_slider_set_value(ui->slider1, 30, LV_ANIM_OFF);

		lv_group_add_obj(ui->group, ui->slider1);

		active_patch_idx = patch_list.cur_patch_index();
		is_init = true;
	}

	void focus(PageChangeDirection dir)
	{
		if (!is_init)
			init();

		auto animation_style = dir == PageChangeDirection::Back	   ? LV_SCR_LOAD_ANIM_MOVE_LEFT :
							   dir == PageChangeDirection::Forward ? LV_SCR_LOAD_ANIM_MOVE_RIGHT :
																	   LV_SCR_LOAD_ANIM_FADE_ON;
		lv_scr_load_anim(ui->patch_selector, animation_style, 500, 0, false);

		// ScrollBoxT::set_num_items(patch_list.NumPatches);
		// ScrollBoxT::set_selection(active_patch_idx);
	}

	void update()
	{
		// screen.fill(Colors::white);
		// PageWidgets::setup_header(screen);
		// screen.print("Select a patch:");
		// screen.setFont(PageWidgets::subheader_font);
		// screen.drawHLine(0, box.top, box.width(), Colors::grey.Rgb565());
		// draw_active_patch_highlight_bar();
		// ScrollBoxT::draw_scroll_box();
	}

	void draw_active_patch_highlight_bar()
	{
		// auto active_patch_top_y = item_abs_scrolled_top(active_patch_idx) + ScrollBoxT::ItemTopMargin;
		// const RectC bar{
		// 	.left = 0,
		// 	.top = active_patch_top_y,
		// 	.right = box.right,
		// 	.bottom = active_patch_top_y + lineheight,
		// };
		// if (box.y_intersects(bar)) {
		// 	screen.set_clip_rect(box);
		// 	screen.blendRect(bar, Colors::green.Rgb565(), 0.4f);
		// 	screen.clear_clip_rect();
		// }
	}

	void check_rotary()
	{
		// auto rotary = metaparams.rotary.use_motion();
		// if (rotary > 0)
		// 	ScrollBoxT::animate_next();
		// if (rotary < 0)
		// 	ScrollBoxT::animate_prev();

		// if (metaparams.rotary_button.is_just_released())
		// 	start_changing_patch(ScrollBoxT::get_selection());

		// handle_changing_patch();
	}

	void draw_scrollbox_element(int32_t i)
	{
		// screen.setTextColor(Colors::black);
		// screen.print(patch_list.get_patch_name(i));
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

	void blur() {}

	int32_t active_patch_idx = 0;
};

} // namespace MetaModule
