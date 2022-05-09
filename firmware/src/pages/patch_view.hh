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
	static inline uint32_t height = 120;
	// static_assert(height == 120 || height == 240);

	PatchViewPage(PatchInfo info)
		: PageBase{info}
		, base(lv_obj_create(nullptr)) {
		PageList::register_page(this, PageId::PatchView);

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_style_pad_gap(base, 4, LV_STATE_DEFAULT);
		lv_obj_add_flag(base, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_scroll_dir(base, LV_DIR_HOR);
		lv_obj_add_flag(base, LV_OBJ_FLAG_SCROLL_CHAIN);

		patchname = lv_label_create(base);
		lv_obj_add_style(patchname, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_width(patchname, 252);
		lv_obj_set_height(patchname, 28);

		playbut = lv_btn_create(base);
		lv_obj_set_height(playbut, 21);
		lv_obj_set_width(playbut, 60);
		lv_obj_set_style_pad_all(playbut, 3, LV_PART_MAIN);
		lv_obj_add_flag(playbut, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(playbut, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_event_cb(playbut, playbut_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(playbut, playbut_focussed_cb, LV_EVENT_FOCUSED, this);

		playbut_label = lv_label_create(playbut);
		lv_obj_add_style(playbut_label, &Gui::button_label_style, LV_PART_MAIN);
		lv_label_set_text(playbut_label, "Play");
		lv_obj_set_align(playbut_label, LV_ALIGN_CENTER);

		description = lv_label_create(base);
		lv_obj_add_style(description, &Gui::text_block_style, LV_PART_MAIN);
		lv_label_set_long_mode(description, LV_LABEL_LONG_WRAP);
		lv_obj_set_width(description, 320);
		lv_obj_set_height(description, 51);

		module_name = lv_label_create(base);
		lv_obj_add_style(module_name, &Gui::header_style, LV_PART_MAIN);
		lv_label_set_text(module_name, "Select a module:");

		modules_cont = lv_obj_create(base);
		lv_obj_set_size(modules_cont, 320, height + 8);
		lv_obj_set_style_bg_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_flex_flow(modules_cont, LV_FLEX_FLOW_ROW);
		lv_obj_set_style_pad_gap(modules_cont, 3, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(modules_cont, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_CHAIN);

		lv_draw_img_dsc_init(&draw_img_dsc);

		// cable_layer = lv_canvas_create(lv_layer_top()); // NOLINT
		// lv_obj_set_size(cable_layer, 320, height);
		// lv_obj_set_align(cable_layer, LV_ALIGN_BOTTOM_MID);
		// lv_canvas_set_buffer(cable_layer, cable_buf, 320, height, LV_IMG_CF_TRUE_COLOR_ALPHA);

		lv_draw_line_dsc_init(&cable_drawline_dsc);
		cable_drawline_dsc.width = 4;
		cable_drawline_dsc.opa = LV_OPA_60;
		cable_drawline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
	}

	void prepare_focus() override {
		auto patch_id = PageList::get_selected_patch_id();
		const auto &patch = patch_list.get_patch(patch_id);
		patch_instance = &patch;

		printf("patch id = %d\n", patch_id);
		if (patch.patch_name.length() == 0)
			return;

		lv_label_set_text(patchname, patch_list.get_patch_name(patch_id));
		lv_label_set_text(description, patch_list.get_patch(patch_id).description.c_str());

		// for (auto &k : mapped_knobs)
		// 	lv_obj_del(k.obj);
		for (auto &m : modules)
			lv_obj_del(m);
		printf("deleted obj\n");
		modules.clear();
		module_ids.clear();
		mapped_knobs.clear();
		modules.reserve(patch.module_slugs.size());
		module_ids.reserve(patch.module_slugs.size());

		lv_obj_set_height(modules_cont, height + 8);

		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		lv_group_add_obj(group, playbut);

		constexpr uint32_t pixel_size = (LV_COLOR_SIZE / 8) / sizeof(buffer[0]);
		uint32_t xpos = 0;
		for (auto [i, slug] : enumerate(patch.module_slugs)) {
			module_ids.push_back(i);

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

			lv_obj_add_style(canvas, &Gui::selected_module_style, LV_STATE_FOCUS_KEY);

			auto buf = &(buffer[pixel_size * height * xpos]);
			lv_obj_set_size(canvas, widthpx, height);
			lv_canvas_set_buffer(canvas, buf, widthpx, height, LV_IMG_CF_TRUE_COLOR);

			// Draw module artwork
			lv_canvas_draw_img(canvas, 0, 0, img, &draw_img_dsc);

			// Draw module controls
			const auto moduleinfo = ModuleFactory::getModuleInfo(slug);
			DrawHelper::draw_module_jacks(canvas, moduleinfo, patch, i, height);
			for (const auto &el : moduleinfo.Knobs) {
				auto mknob = DrawHelper::draw_mapped_knob(canvas, canvas, el, patch, i, height);
				if (mknob.has_value()) {
					mapped_knobs.push_back(mknob.value());
				}
			}

			lv_obj_set_user_data(canvas, (void *)(&module_ids[module_ids.size() - 1]));
			lv_obj_add_event_cb(canvas, moduleimg_cb, LV_EVENT_PRESSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_focus_cb, LV_EVENT_FOCUSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_defocus_cb, LV_EVENT_DEFOCUSED, (void *)this);

			lv_group_add_obj(group, canvas);

			xpos += widthpx;
			if (xpos >= MaxBufferWidth) {
				printf("Max size reached\n");
				break;
			}
		}
		lv_obj_refresh_self_size(modules_cont);
		printf("have %d mapped knobs\n", mapped_knobs.size());
	}

	void blur() override {
		for (auto &m : modules) {
			lv_obj_del(m);
		}
		// for (auto &k : mapped_knobs) {
		// 	lv_obj_del(k.obj);
		// }
		modules.clear();
		module_ids.clear();
		mapped_knobs.clear();
		// lv_canvas_fill_bg(cable_layer, lv_color_white(), LV_OPA_0);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
		handle_changing_patch();

		for (auto &mk : mapped_knobs) {
			if (mk.anim_method == DrawHelper::RotaryPot) {
				const float new_pot_val = mk.mapped_knob.get_mapped_val(params.knobs[mk.mapped_knob.panel_knob_id]);
				if (std::abs(new_pot_val - mk.last_pot_reading) > 0.01f) {
					mk.last_pot_reading = new_pot_val;
					const int angle = new_pot_val * 3000.f - 1500.f;
					lv_img_set_angle(mk.obj, angle);
				}
			}
		}
	}

	static void moduleimg_cb(lv_event_t *event) {
		auto obj = event->current_target;
		uint32_t module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(obj)));
		PageList::set_selected_module_id(module_id);
		printf("Clicked Module %d\n", module_id);
		PageList::request_new_page(PageId::ModuleView);
	}

	static void module_focus_cb(lv_event_t *event) {
		auto this_module_obj = event->current_target;
		uint32_t module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(this_module_obj)));
		printf("Focussed Module %d\n", module_id);

		auto page = static_cast<PatchViewPage *>(event->user_data);

		// if (page->height == 120) {
		// 	page->height = 240;
		// 	// page->blur();
		// 	page->focus();
		// }
		const auto &patch = page->patch_list.get_patch(PageList::get_selected_patch_id());

		const auto this_slug = patch.module_slugs[module_id];

		const auto thismoduleinfo = ModuleFactory::getModuleInfo(this_slug);
		lv_label_set_text(page->module_name, this_slug.c_str());

		bool do_draw_cables = false;
		if (do_draw_cables) {
			// lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);

			// const int x_offset = 0;
			// const int y_offset = height == 120 ? -6 : 6;
			// for (const auto &c : patch.int_cables) {
			// 	for (const auto &in : c.ins) {
			// 		if (in.module_id == module_id) {
			// 			auto [in_x, in_y] = DrawHelper::scale_center(thismoduleinfo.InJacks[in.jack_id], height);
			// 			auto scroll_x = 0;

			// 			lv_area_t coords;
			// 			lv_obj_get_coords(this_module_obj, &coords);
			// 			int in_module_left = coords.x1;
			// 			in_x = in_x + in_module_left - scroll_x + x_offset;
			// 			in_y += y_offset;

			// 			int out_module_left = 0;
			// 			for (auto mod : page->modules) {
			// 				uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(mod)));
			// 				if (t_module_id == c.out.module_id) {
			// 					lv_area_t coords;
			// 					lv_obj_get_coords(mod, &coords);
			// 					out_module_left = coords.x1;
			// 					break;
			// 				}
			// 			}
			// 			const auto other_moduleinfo = ModuleFactory::getModuleInfo(patch.module_slugs[c.out.module_id]);
			// 			auto [out_x, out_y] =
			// 				DrawHelper::scale_center(other_moduleinfo.OutJacks[c.out.jack_id], height);
			// 			out_x = out_x + out_module_left - scroll_x + x_offset;
			// 			out_y += y_offset;

			// 			lv_point_t points[2] = {{(int16_t)in_x, (int16_t)in_y}, {(int16_t)out_x, (int16_t)out_y}};
			// 			page->cable_drawline_dsc.color =
			// 				Gui::cable_palette[(c.out.jack_id + c.out.module_id) % Gui::cable_palette.size()];
			// 			lv_canvas_draw_line(page->cable_layer, points, 2, &page->cable_drawline_dsc);
			// 		}
			// 	}
			// }
		}
	}

	static void module_defocus_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		// lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);
	}

	static void playbut_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		printf("Clicked Play: playing patch# %d\n\r", PageList::get_selected_patch_id());
		page->start_changing_patch();
	}

	static void playbut_focussed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_label_set_text(page->module_name, "Select a module:");

		// if (page->height == 240) {
		// 	page->height = 120;
		// page->blur();
		// page->focus();
		// }

		lv_obj_scroll_to_y(page->base, 0, LV_ANIM_ON);
	}

private:
	lv_obj_t *description;
	lv_obj_t *patchname;
	lv_obj_t *modules_cont;
	lv_obj_t *module_name;
	lv_obj_t *playbut_label;
	lv_obj_t *playbut;
	// lv_obj_t *cable_layer;

	std::vector<lv_obj_t *> modules;
	std::vector<uint32_t> module_ids;
	std::vector<DrawHelper::MKnob> mapped_knobs;

	static constexpr uint32_t MaxBufferWidth = 1024;
	static inline uint8_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR(240, MaxBufferWidth)];
	lv_draw_img_dsc_t draw_img_dsc;

	static inline uint8_t cable_buf[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 320)];
	lv_draw_line_dsc_t cable_drawline_dsc;

	static inline const PatchData *patch_instance;

	struct focussed_context {
		PatchViewPage *page;
		uint32_t selected_module_id;
	};

	lv_obj_t *base;

	void draw_cable(Jack out, Jack in) {
	}

	void start_changing_patch() {
		auto _patch_id = PageList::get_selected_patch_id();
		if (!mbox.loading_new_patch && (_patch_id != patch_list.cur_patch_index())) {
			mbox.new_patch_index = _patch_id;
			mbox.loading_new_patch = true;
			printf("Loading patch %s\n", patch_list.get_patch_name(_patch_id).data());
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
				mbox.append_message("Can't load patch\n");
				printf("Can't load patch\n");
				patch_player.unload_patch();
				patch_player.load_patch(orig_patch_data);
			} else
				mbox.append_message("Patch loaded\n");

			mbox.loading_new_patch = false;
		}
	}
};
} // namespace MetaModule
