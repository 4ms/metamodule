#pragma once
#include "lvgl/lvgl.h"
#include "lvgl/src/core/lv_obj.h"
#include "pages/base.hh"
#include "pages/draw_helpers.hh"
#include "pages/images/image_list.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include "printf.h"

namespace MetaModule
{

struct PatchViewPage : PageBase {
	constexpr static uint32_t height = 120;
	static_assert(height == 120 || height == 240);

	PatchViewPage(PatchInfo info, uint32_t patch_id = 0)
		: PageBase{info}
		, base(lv_obj_create(nullptr))
		, _patch_id{patch_id} {
		PageList::register_page(this, PageId::PatchView);

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_style_pad_gap(base, 4, LV_STATE_DEFAULT);

		patchname = lv_label_create(base);
		lv_obj_add_style(patchname, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_size(patchname, 320, 30);
		lv_obj_set_style_border_width(patchname, 0, 0);
		// lv_obj_set_style_border_opa(patchname, LV_OPA_COVER, 0);
		// lv_obj_set_style_border_color(patchname, lv_palette_main(LV_PALETTE_CYAN), 0);

		description = lv_label_create(base);
		lv_obj_add_style(description, &Gui::text_block_style, LV_PART_MAIN);
		lv_label_set_long_mode(description, LV_LABEL_LONG_DOT);
		lv_obj_set_width(description, 270);

		playbut = lv_btn_create(base);
		// lv_obj_add_style(playbut, &style_popup_buttons, LV_PART_MAIN);
		playbut_label = lv_label_create(playbut);
		lv_label_set_text(playbut_label, "Play");
		// lv_obj_set_size(playbut, 60, 20);

		modules_cont = lv_obj_create(base);
		lv_obj_set_size(modules_cont, 320, height + 8);
		lv_obj_set_style_bg_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_flex_flow(modules_cont, LV_FLEX_FLOW_ROW);
		lv_obj_set_style_pad_gap(modules_cont, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(modules_cont, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

		lv_draw_img_dsc_init(&draw_img_dsc);

		////Play button
		//popup_playbut = lv_btn_create(popup_cont);
		//lv_obj_add_style(popup_playbut, &style_popup_buttons, LV_PART_MAIN);
		//popup_playbut_label = lv_label_create(popup_playbut);
		//lv_label_set_text(popup_playbut_label, "Play");
		// // Play button, above Explore, up 10px
		// lv_obj_align(popup_playbut, popup_explorebut, LV_ALIGN_OUT_TOP_MID, 0, -10);
		// lv_group_add_obj(group, popup_playbut);
		// lv_obj_add_event_cb(popup_playbut, popup_play_event_cb, LV_EVENT_CLICKED, this);

		// set_patch_id(_patch_id);
	}

	void set_patch_id(uint32_t patch_id) {
		_patch_id = patch_id;
		printf("patch id = %d\n", _patch_id);
		const PatchData &patch = patch_list.get_patch(_patch_id);
		if (patch.patch_name.length() == 0)
			return;

		// LVGLMemory::print_mem_usage("PatchSel::setup_popup 0");
		lv_label_set_text(patchname, patch_list.get_patch_name(_patch_id));
		lv_label_set_text(description,
						  "TODO: Patch descriptions...\nLorum ipsum\nADmnjf djknmd asjfkjdf a sd, sdhan di and uienad "
						  "kjtkjcnmheujhne, hfjasdasdf-adf. Lofamfkm dkjlfkolea. Ipsum Lorum\n");

		for (auto &m : modules)
			lv_obj_del(m);
		modules.clear();
		modules.reserve(patch.module_slugs.size());
		module_ids.clear();
		module_ids.reserve(patch.module_slugs.size());

		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		constexpr uint32_t pixel_size = (LV_COLOR_SIZE / 8) / sizeof(buffer[0]);
		uint32_t xpos = 0;
		for (auto [i, slug] : enumerate(patch.module_slugs)) {
			printf("Drawing %s\n", slug.c_str());
			const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug, height);
			if (!img) {
				printf("Image not found for %s\n", slug.c_str());
				continue;
			}
			auto widthpx = img->header.w;
			printf("Width is %d\n", widthpx);

			lv_obj_t *canvas = modules.emplace_back(lv_canvas_create(modules_cont));
			lv_obj_add_style(canvas, &Gui::plain_border_style, LV_STATE_DEFAULT);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_CLICKABLE);
			lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE); //inherited from parent?
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

			lv_obj_set_style_outline_color(canvas, lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_STATE_FOCUS_KEY);
			lv_obj_set_style_outline_width(canvas, 4, LV_STATE_FOCUS_KEY);
			lv_obj_set_style_outline_opa(canvas, LV_OPA_70, LV_STATE_FOCUS_KEY);

			auto buf = &(buffer[pixel_size * height * xpos]);
			printf("Buf ptr is %p (+%zu) (buffer[%d * height * %d])\n", buf, buf - buffer, pixel_size, xpos);
			lv_obj_set_size(canvas, widthpx, height);
			lv_canvas_set_buffer(canvas, buf, widthpx, height, LV_IMG_CF_TRUE_COLOR);

			lv_canvas_draw_img(canvas, 0, 0, img, &draw_img_dsc);
			const auto info = ModuleFactory::getModuleInfo(slug);
			DrawHelper::draw_module_controls(canvas, info, height);

			module_ids.push_back(i);
			lv_obj_add_event_cb(canvas, moduleimg_cb, LV_EVENT_PRESSED, (void *)(&module_ids[module_ids.size() - 1]));
			lv_group_add_obj(group, canvas);

			xpos += widthpx;
			if (xpos >= MaxBufferWidth) {
				printf("Max size reached\n");
				break;
			}
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

	static void moduleimg_cb(lv_event_t *event) {
		auto obj = event->current_target;
		uint32_t module_id = *(static_cast<uint32_t *>(event->user_data));
		PageList::set_selected_module_id(module_id);
		printf("Clicked Module %d\n", module_id);
		PageList::request_new_page(PageId::ModuleView);
	}

	static void playbut_cb(lv_event_t *event) {
		// auto obj = event->current_target;
		// auto page = static_cast<PatchViewPage *>(event->user_data);
		printf("Clicked Play: playing patch# %d\n\r", PageList::get_selected_patch_id());
		// 	page->start_changing_patch(page->patch_id);
	}

private:
	lv_obj_t *description;
	lv_obj_t *patchname;
	lv_obj_t *modules_cont;
	lv_obj_t *playbut_label;
	lv_obj_t *playbut;

	static constexpr uint32_t MaxBufferWidth = 1024;
	std::vector<lv_obj_t *> modules;
	std::vector<uint32_t> module_ids;
	static inline uint8_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR(height, MaxBufferWidth)];
	lv_draw_img_dsc_t draw_img_dsc;

	bool should_show_moduleview = false;

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
			//TODO check for nullpatch
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
