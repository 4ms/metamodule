#pragma once
#include "pages/base.hh"
#include "pages/images/image_list.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include "printf.h"

namespace MetaModule
{

struct PatchViewPage : PageBase {
	PatchViewPage(PatchInfo info, uint32_t patch_id = 0)
		: PageBase{info}
		, base(lv_obj_create(nullptr))
		, _patch_id{patch_id} {
		PageList::register_page(this, PageId::PatchView);

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);

		patchname = lv_label_create(base);
		lv_obj_add_style(patchname, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_size(patchname, 320, 30);

		description = lv_label_create(base);
		lv_obj_add_style(description, &Gui::text_block_style, LV_PART_MAIN);
		lv_label_set_long_mode(description, LV_LABEL_LONG_DOT);
		lv_obj_set_size(description, 320, 70);

		modules_cont = lv_obj_create(base);
		lv_obj_set_size(modules_cont, 320, 240);
		lv_obj_set_flex_flow(modules_cont, LV_FLEX_FLOW_ROW);
		lv_obj_set_style_pad_gap(modules_cont, 0, LV_STATE_DEFAULT);

		lv_group_set_wrap(group, true);
		lv_group_add_obj(group, modules_cont);

		////Play button
		//popup_playbut = lv_btn_create(popup_cont);
		//lv_obj_add_style(popup_playbut, &style_popup_buttons, LV_PART_MAIN);
		//popup_playbut_label = lv_label_create(popup_playbut);
		//lv_label_set_text(popup_playbut_label, "Play");
		// // Play button, above Explore, up 10px
		// lv_obj_align(popup_playbut, popup_explorebut, LV_ALIGN_OUT_TOP_MID, 0, -10);
		// lv_group_add_obj(group, popup_playbut);
		// lv_obj_add_event_cb(popup_playbut, popup_play_event_cb, LV_EVENT_CLICKED, this);

		set_patch_id(_patch_id);
	}

	void set_patch_id(uint32_t patch_id) {
		// LVGLMemory::print_mem_usage("PatchSel::setup_popup 0");
		_patch_id = patch_id;
		printf("patch id = %d\n", _patch_id);
		lv_label_set_text(patchname, patch_list.get_patch_name(_patch_id));
		lv_label_set_text(description,
						  "TODO: Patch descriptions...\nLorum ipsum\nADmnjf djknmd asjfkjdf a sd, sdhan di and uienad "
						  "kjtkjcnmheujhne, hfjasdasdf-adf. LKfamfkm dkjlfkolea. Ipsum Lorum\n");
		for (auto &m : modules)
			lv_obj_del(m);
		modules.clear();

		auto patch = patch_list.get_patch(_patch_id);
		for (auto slug : patch.module_slugs) {
			lv_obj_t *m = modules.emplace_back(lv_img_create(modules_cont));
			const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug);
			lv_img_set_src(m, img);
			lv_group_add_obj(group, m);
		}
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
		// handle_changing_patch();
	}

	void prepare_focus() override {
		set_patch_id(PageList::get_selected_patch_id());
	}

	static void playbut_cb(lv_event_t *event) {
		auto obj = event->current_target;
		auto page = static_cast<PatchViewPage *>(event->user_data);

		printf("Clicked Play: playing patch# %d\n\r", PageList::get_selected_patch_id());
		// 	page->start_changing_patch(page->patch_id);
	}

private:
	lv_obj_t *description;
	lv_obj_t *patchname;
	lv_obj_t *modules_cont;

	std::vector<lv_obj_t *> modules;

	lv_obj_t *base;
	uint32_t _patch_id;

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
};
} // namespace MetaModule

// }

// void _init_styles() {

//// Popup styles:
//lv_style_init(&style_popup_cont);
//lv_style_set_radius(&style_popup_cont, 0);
//lv_style_set_bg_color(&style_popup_cont, lv_color_make(0xe6, 0xe6, 0xe6));
//lv_style_set_bg_opa(&style_popup_cont, 255);
////lv_style_set_border_color(&style_popup_cont, lv_color_make(0xff, 0xc3, 0x70));
//lv_style_set_border_width(&style_popup_cont, 0);
//lv_style_set_border_opa(&style_popup_cont, 0);
//lv_style_set_pad_gap(&style_popup_cont, 10);
//lv_style_set_pad_all(&style_popup_cont, 4);

//lv_style_init(&style_popup_buttons);
//lv_style_set_radius(&style_popup_buttons, 8);
//lv_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xff, 0xff));
//// lv_style_set_bg_color(&style_popup_buttons, lv_color_make(0xff, 0xc3, 0x70));//LV_STATE_FOCUSED,
//// lv_style_set_bg_color(&style_popup_buttons,  lv_color_make(0xf6, 0xdd, 0x53));//LV_STATE_PRESSED,
//lv_style_set_bg_opa(&style_popup_buttons, 255);
//lv_style_set_border_color(&style_popup_buttons, lv_color_make(0x32, 0x32, 0x32));
//lv_style_set_border_width(&style_popup_buttons, 2);
//lv_style_set_text_color(&style_popup_buttons, lv_color_make(0x32, 0x32, 0x32));

//lv_style_init(&style_popup_backbut);
//// lv_style_set_image_opa(&style_popup_backbut, 255);
////FOCUSED state:
//lv_style_set_radius(&style_popup_backbut, 6);
//lv_style_set_outline_color(&style_popup_backbut, lv_color_hex(0xabcdef));
//lv_style_set_outline_width(&style_popup_backbut, LV_DPX(2));
//lv_style_set_outline_opa(&style_popup_backbut, LV_OPA_0);
//// lv_style_set_outline_opa(&style_popup_backbut, LV_STATE_FOCUSED, LV_OPA_50);
//// lv_style_set_image_recolor(&style_popup_backbut, LV_STATE_FOCUSED, lv_color_hex(0x888888));
////lv_style_set_outline_pad(&style_popup_backbut, LV_STATE_FOCUSED, 4);
////lv_style_set_outline_blend_mode(&style_popup_backbut, LV_STATE_FOCUSED, LV_BLEND_MODE_NORMAL);

//lv_style_init(&style_popup_desc);
//lv_style_set_radius(&style_popup_desc, 0);
//// lv_style_set_bg_color(&style_popup_desc, lv_color_make(0xff, 0xff, 0xff));
//lv_style_set_bg_opa(&style_popup_desc, 0);
//lv_style_set_text_color(&style_popup_desc, lv_color_make(0x78, 0x78, 0x78));
//lv_style_set_text_font(&style_popup_desc, &lv_font_MuseoSansRounded_500_16);
//lv_style_set_text_letter_space(&style_popup_desc, 0);
//lv_style_set_text_line_space(&style_popup_desc, 12);
//lv_style_set_pad_left(&style_popup_desc, 4);
//lv_style_set_pad_right(&style_popup_desc, 4);
//lv_style_set_pad_top(&style_popup_desc, 3);
//lv_style_set_pad_bottom(&style_popup_desc, 2);

//lv_style_init(&style_popup_patchname);
//// lv_style_set_radius(&style_popup_patchname, 0);
//// lv_style_set_bg_color(&style_popup_patchname, lv_color_make(0xa0, 0xa0, 0xa0));
//lv_style_set_bg_opa(&style_popup_patchname, 0);
//lv_style_set_text_color(&style_popup_patchname, lv_color_make(0x1c, 0x1c, 0x1c));
//lv_style_set_text_font(&style_popup_patchname, &lv_font_MuseoSansRounded_700_17);
//lv_style_set_text_letter_space(&style_popup_patchname, 1);
//lv_style_set_pad_left(&style_popup_patchname, 6);
//lv_style_set_pad_right(&style_popup_patchname, 6);
//lv_style_set_pad_top(&style_popup_patchname, 4);
//lv_style_set_pad_bottom(&style_popup_patchname, 4);

//// Wait cont style
//lv_style_init(&style_wait_cont);
//lv_style_set_radius(&style_wait_cont, 2);
//lv_style_set_bg_color(&style_wait_cont, lv_color_make(0xe6, 0xe6, 0xe6));
//lv_style_set_bg_opa(&style_wait_cont, 255);
//lv_style_set_border_color(&style_wait_cont, lv_color_make(0xff, 0xc3, 0x70));
//lv_style_set_border_width(&style_wait_cont, 1);
//lv_style_set_border_opa(&style_wait_cont, 255);
//lv_style_set_pad_gap(&style_wait_cont, 10);
//lv_style_set_pad_all(&style_wait_cont, 10);
// }
