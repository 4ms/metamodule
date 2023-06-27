#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "lvgl/lvgl.h"
#include "lvgl/src/core/lv_event.h"
#include "lvgl/src/core/lv_obj.h"
#include "pages/animated_knob.hh"
#include "pages/base.hh"
#include "pages/draw_helpers.hh"
#include "pages/elements/element_drawer.hh"
#include "pages/elements/map_ring_drawer.hh"
#include "pages/images/image_list.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/map_register.hh"
#include "pages/module_drawer.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include "printf.h"
#include "util/countzip.hh"

namespace MetaModule
{

struct PatchViewPage : PageBase {
	static inline uint32_t height = 240;
	// static_assert(height == 120 || height == 240);

	PatchViewPage(PatchInfo info)
		: PageBase{info}
		, base(lv_obj_create(nullptr)) {
		PageList::register_page(this, PageId::PatchView);

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_flex_align(base, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_gap(base, 4, LV_STATE_DEFAULT);
		lv_obj_add_flag(base, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_scroll_dir(base, LV_DIR_VER);
		lv_obj_set_scrollbar_mode(base, LV_SCROLLBAR_MODE_ACTIVE);

		lv_obj_add_event_cb(base, base_scroll_cb, LV_EVENT_SCROLL, (void *)this);

		patchname = lv_label_create(base);
		lv_obj_add_style(patchname, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_width(patchname, 248);
		lv_obj_set_height(patchname, 28);

		playbut = lv_btn_create(base);
		lv_obj_set_height(playbut, 21);
		lv_obj_set_width(playbut, 60);
		lv_obj_set_style_pad_ver(playbut, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_hor(playbut, 5, LV_PART_MAIN);
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
		lv_obj_set_size(modules_cont, 320, 2 * height + 8);
		lv_obj_set_style_bg_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_flex_flow(modules_cont, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_style_pad_gap(modules_cont, 3, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(modules_cont, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLLABLE);
		// lv_obj_set_scroll_dir(modules_cont, LV_DIR_VER);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		// lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_CHAIN);

		cable_layer = lv_canvas_create(lv_layer_top()); // NOLINT
		lv_obj_set_size(cable_layer, 320, 240);
		lv_obj_set_align(cable_layer, LV_ALIGN_CENTER);
		lv_canvas_set_buffer(cable_layer, cable_buf, 320, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);

		lv_draw_line_dsc_init(&cable_drawline_dsc);
		cable_drawline_dsc.width = 4;
		cable_drawline_dsc.opa = LV_OPA_60;
		cable_drawline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
	}

	void prepare_focus() override {
		const auto &patch = patch_storage.get_view_patch();
		patch_instance = &patch;

		// printf_("patch id = %d\n", patch_storage.get_view_patch_id());
		if (patch.patch_name.length() == 0)
			return;

		lv_label_set_text(patchname, patch.patch_name.c_str());
		lv_label_set_text(description, patch.description.c_str());

		for (auto &m : modules)
			lv_obj_del(m);
		modules.clear();
		module_ids.clear();
		mappings.knobs.clear();
		modules.reserve(patch.module_slugs.size());
		module_ids.reserve(patch.module_slugs.size());

		lv_obj_set_height(modules_cont, 2 * height + 8);

		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		lv_group_add_obj(group, playbut);

		auto module_drawer = ModuleDrawer{modules_cont, patch, height};

		constexpr uint32_t pixel_size = (LV_COLOR_SIZE / 8) / sizeof(buffer[0]);
		uint32_t xpos = 0;
		for (auto [module_idx, slug] : enumerate(patch.module_slugs)) {
			module_ids.push_back(module_idx);

			auto canvas_buf = &(buffer[pixel_size * height * xpos]);

			auto canvas = module_drawer.draw_with_mappings(module_idx, canvas_buf, mappings);
			if (!canvas)
				continue;

			modules.push_back(canvas);

			lv_group_add_obj(group, canvas);

			// give the callback access to the module_idx
			lv_obj_set_user_data(canvas, (void *)(&module_ids[module_ids.size() - 1]));
			lv_obj_add_event_cb(canvas, module_pressed_cb, LV_EVENT_PRESSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_focus_cb, LV_EVENT_FOCUSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_defocus_cb, LV_EVENT_DEFOCUSED, (void *)this);

			xpos += lv_obj_get_width(canvas);
			if (xpos >= MaxBufferWidth) {
				printf_("Max image size reached\n");
				break;
			}
		}
		// lv_obj_refresh_self_size(modules_cont);
	}

	void blur() override {
		for (auto &m : modules) {
			lv_obj_del(m); //also deletes child objects: mapped and static knobs
		}
		mappings.knobs.clear();
		modules.clear();
		module_ids.clear();
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}

		for (auto &mk : mappings.knobs) {
			if (mk.anim_method == ParamAnimMethod::RotaryPot) {
				const float new_pot_val = mk.patchconf.get_mapped_val(params.knobs[mk.patchconf.panel_knob_id]);
				if (std::abs(new_pot_val - mk.last_pot_reading) > 0.01f) {
					mk.last_pot_reading = new_pot_val;
					const int angle = new_pot_val * 3000.f - 1500.f;
					lv_img_set_angle(mk.obj, angle);
				}
			}
		}
	}

	static void base_scroll_cb(lv_event_t *event) {
		lv_event_t e2;
		e2.user_data = event->user_data;
		module_focus_cb(&e2);
	}

	static void module_pressed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);

		auto obj = event->current_target;
		uint32_t module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(obj)));
		PageList::set_selected_module_id(module_id);
		printf_("Clicked Module %d\n", module_id);
		PageList::request_new_page(PageId::ModuleView);
	}

	static void module_focus_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;
		auto this_module_obj = lv_group_get_focused(page->group);
		if (this_module_obj == page->playbut)
			return;
		uint32_t module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(this_module_obj)));
		const auto &patch = page->patch_storage.get_view_patch();
		const auto this_slug = patch.module_slugs[module_id];
		lv_label_set_text(page->module_name, this_slug.c_str());

		// if (lv_obj_get_scroll_y(page->base) == 0 && num_rows > 1)
		// 	lv_obj_scroll_to_y(page->base, 119, LV_ANIM_ON);

		const auto thismoduleinfo = ModuleFactory::getModuleInfo(this_slug);
		lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);

		// Draw all cables connected to this module
		// TODO: gotta be a cleaner way to do this...
		// 		push Jack{c.out}, this_module_obj, Jack{in}, outmodule_obj
		// 		draw_cable(Jack out, Jack in, lv_obj_t *out_module, lv_obj_t *in_module);
		if (thismoduleinfo.width_hp > 0) {
			for (const auto &c : patch.int_cables) {
				// Draw cable(s) if out jack is on this module
				if (c.out.module_id == module_id) {
					auto end = DrawHelper::get_jack_xy(thismoduleinfo.OutJacks, this_module_obj, c.out, height);

					// Draw a cable from this out jack to all in jacks it's connected to
					for (const auto &in : c.ins) {
						// Iterate through all modules to find the one with a matching id (TODO: better way to do this?)
						for (auto inmodule_obj : page->modules) {
							uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(inmodule_obj)));
							if (t_module_id == in.module_id) {
								const auto inmodule_info =
									ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
								auto start = DrawHelper::get_jack_xy(inmodule_info.InJacks, inmodule_obj, in, height);
								page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
								DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
								break;
							}
						}
					}
					continue; //We drew the output to all inputs, no need to check if any inputs are on this module
				}
				// Draw cable if in jack is on this module
				for (const auto &in : c.ins) {
					if (in.module_id == module_id) {
						auto start = DrawHelper::get_jack_xy(thismoduleinfo.InJacks, this_module_obj, in, height);
						//Find output jack on another module
						for (auto outmodule_obj : page->modules) {
							uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(outmodule_obj)));
							if (t_module_id == c.out.module_id) {
								auto outmodule_info = ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
								auto end =
									DrawHelper::get_jack_xy(outmodule_info.OutJacks, outmodule_obj, c.out, height);
								page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
								DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
								break;
							}
						}
					}
				}
			}
		}
	}

	static void module_defocus_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);
	}

	static void playbut_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		// printf_("Clicked Play: playing patch# %d\n\r", PageList::get_selected_patch_id());
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
	lv_obj_t *cable_layer;

	std::vector<lv_obj_t *> modules;
	std::vector<uint32_t> module_ids;

	Mappings mappings;

	lv_draw_line_dsc_t cable_drawline_dsc;

	static inline const PatchData *patch_instance;

	struct focussed_context {
		PatchViewPage *page;
		uint32_t selected_module_id;
	};

	lv_obj_t *base;

	void start_changing_patch() {
		patch_playloader.request_load_view_patch();
	}
};
} // namespace MetaModule
