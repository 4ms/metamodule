#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "gui/elements/element_drawer.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/map_ring_drawer.hh"
#include "gui/elements/mapping.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/update.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include "util/countzip.hh"

//exported:
extern "C" {
#include "gui/slsexport/patchview/ui.h"
}
extern "C" void ui_PatchView_screen_init();

namespace MetaModule
{

struct PatchViewPage : PageBase {
	static inline uint32_t Height = 180;

	struct ViewSettings {
		bool map_ring_flash_active = true; //flash map ring if knob is turned while patch is playing
		MapRingDisplay::Style map_ring_style = MapRingDisplay::Style::ShowAllIfPlaying;
	};
	ViewSettings settings;

	PatchViewPage(PatchInfo info)
		: PageBase{info} {
		PageList::register_page(this, PageId::PatchView);

		ui_PatchView_screen_init();
		base = ui_PatchView; //NOLINT

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_flex_align(base, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_gap(base, 4, LV_STATE_DEFAULT);
		lv_obj_add_flag(base, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_scroll_dir(base, LV_DIR_VER);
		lv_obj_set_scrollbar_mode(base, LV_SCROLLBAR_MODE_ACTIVE);

		lv_obj_add_event_cb(base, base_scroll_cb, LV_EVENT_SCROLL, (void *)this);

		patchname = ui_PatchName; //NOLINT

		playbut = ui_PlayButton; //NOLINT
		lv_obj_add_flag(playbut, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(playbut, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_event_cb(playbut, playbut_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(playbut, playbut_focussed_cb, LV_EVENT_FOCUSED, this);

		lv_obj_add_flag(ui_AddButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_InfoButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_KnobButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_SettingsButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

		// Scroll to top when focussing on a button
		lv_obj_add_event_cb(ui_AddButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_InfoButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_KnobButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_SettingsButton, button_focussed_cb, LV_EVENT_FOCUSED, this);

		// description = lv_label_create(base);
		// lv_obj_add_style(description, &Gui::text_block_style, LV_PART_MAIN);
		// lv_label_set_long_mode(description, LV_LABEL_LONG_WRAP);
		// lv_obj_set_width(description, 320);
		// lv_obj_set_height(description, 51);

		module_name = lv_label_create(base);
		lv_obj_add_style(module_name, &Gui::header_style, LV_PART_MAIN);
		lv_label_set_text(module_name, "Select a module:");

		modules_cont = lv_obj_create(base);
		lv_obj_set_size(modules_cont, 320, 4 * Height + 8);
		lv_obj_set_style_bg_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_flex_flow(modules_cont, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_style_pad_gap(modules_cont, 3, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(modules_cont, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLLABLE);
		// lv_obj_set_scroll_dir(modules_cont, LV_DIR_ALL); //FIXME: why no horiz scrolling?
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		// lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_CHAIN); //FIXME: has no effect?

		cable_layer = lv_canvas_create(lv_layer_top()); // NOLINT
		lv_obj_set_size(cable_layer, 320, 240);
		lv_obj_set_align(cable_layer, LV_ALIGN_CENTER);
		lv_canvas_set_buffer(cable_layer, cable_buf.data(), 320, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);

		lv_draw_line_dsc_init(&cable_drawline_dsc);
		cable_drawline_dsc.width = 4;
		cable_drawline_dsc.opa = LV_OPA_60;
		cable_drawline_dsc.blend_mode = LV_BLEND_MODE_NORMAL;
	}

	void prepare_focus() override {

		patch = patch_storage.get_view_patch();

		is_patch_playing = PageList::get_selected_patch_id() == patch_playloader.cur_patch_index();

		if (patch.patch_name.length() == 0)
			return;

		lv_label_set_text(patchname, patch.patch_name.c_str());
		// lv_label_set_text(description, patch.description.c_str());

		blur();

		module_canvases.reserve(patch.module_slugs.size());
		module_ids.reserve(patch.module_slugs.size());

		//lv_obj_set_height(modules_cont, 2 * height + 8);

		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		lv_group_add_obj(group, playbut);
		lv_group_add_obj(group, ui_KnobButton);
		lv_group_add_obj(group, ui_AddButton);
		lv_group_add_obj(group, ui_InfoButton);
		lv_group_add_obj(group, ui_SettingsButton);

		auto module_drawer = ModuleDrawer{modules_cont, Height};

		auto canvas_buf = std::span<lv_color_t>{page_pixel_buffer};

		for (auto [module_idx, slug] : enumerate(patch.module_slugs)) {
			module_ids.push_back(module_idx);

			auto canvas = module_drawer.draw_faceplate(slug, canvas_buf);
			if (!canvas)
				continue;

			module_drawer.draw_mapped_elements(patch, module_idx, canvas, drawn_elements, is_patch_playing);

			// Increment the buffer
			lv_obj_refr_size(canvas);
			canvas_buf = canvas_buf.subspan(LV_CANVAS_BUF_SIZE_TRUE_COLOR(1, 1) * lv_obj_get_width(canvas) * Height);

			module_canvases.push_back(canvas);

			lv_group_add_obj(group, canvas);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_SNAPPABLE);

			lv_obj_add_style(canvas, &Gui::plain_border_style, LV_STATE_DEFAULT);
			lv_obj_add_style(canvas, &Gui::selected_module_style, LV_STATE_FOCUS_KEY);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
			lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);

			// Give the callback access to the module_idx:
			lv_obj_set_user_data(canvas, (void *)(&module_ids[module_ids.size() - 1]));
			lv_obj_add_event_cb(canvas, module_pressed_cb, LV_EVENT_PRESSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_focus_cb, LV_EVENT_FOCUSED, (void *)this);
			lv_obj_add_event_cb(canvas, module_defocus_cb, LV_EVENT_DEFOCUSED, (void *)this);
		}

		update_map_ring_style(0);
		//auto cable_drawer = CableDrawer{cable_cont, modules, patch, height};
		//cable_drawer.draw_all();

		// lv_obj_refresh_self_size(modules_cont);
		lv_obj_scroll_to_y(base, 0, LV_ANIM_OFF);
	}

	void blur() override {
		for (auto &m : module_canvases) {
			lv_obj_del(m);
		}

		drawn_elements.clear();
		module_canvases.clear();
		module_ids.clear();
	}

	void update() override {
		is_patch_playing = PageList::get_selected_patch_id() == patch_playloader.cur_patch_index();
		//TODO: show mapping ring layer if patch is playing

		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}

		if (is_patch_playing) {
			for (auto &drawn_el : drawn_elements) {
				std::visit(
					[this, gui_el = drawn_el.gui_element](auto &el) -> void {
						//if (drawn.obj) //TODO: This can be removed now, right?
						bool did_update = update_element(el, this->params, patch, gui_el);

						if (did_update && settings.map_ring_flash_active) {
							MapRingDisplay::flash_once(gui_el.map_ring);
							lv_obj_scroll_to_view_recursive(gui_el.obj, LV_ANIM_ON);
						}
					},
					drawn_el.element);
			}
		}
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style(unsigned module_id) {
		using enum MapRingDisplay::Style;

		for (auto &drawn_el : drawn_elements) {
			auto map_ring = drawn_el.gui_element.map_ring;

			switch (settings.map_ring_style) {
				case ShowAllIfPlaying:
					if (is_patch_playing)
						MapRingDisplay::show(map_ring);
					else
						MapRingDisplay::hide(map_ring);
					break;

				case CurModule:
					if (module_id == drawn_el.gui_element.module_idx)
						MapRingDisplay::show(map_ring);
					else
						MapRingDisplay::hide(map_ring);
					break;

				case CurModuleIfPlaying:
					if (module_id == drawn_el.gui_element.module_idx && is_patch_playing)
						MapRingDisplay::show(map_ring);
					else
						MapRingDisplay::hide(map_ring);
					break;

				case ShowAll:
					MapRingDisplay::show(map_ring);
					break;

				case HideAlways:
					MapRingDisplay::hide(map_ring);
					break;
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
		if (!this_module_obj) //|| this_module_obj == page->playbut // or any of the other buttons?
			return;

		auto user_data = lv_obj_get_user_data(this_module_obj);
		if (!user_data)
			return;

		uint32_t module_id = *(static_cast<uint32_t *>(user_data));
		if (module_id >= page->patch.module_slugs.size())
			return;

		const auto this_slug = page->patch.module_slugs[module_id];
		lv_label_set_text(page->module_name, this_slug.c_str());

		// if (lv_obj_get_scroll_y(page->base) == 0 && num_rows > 1)
		// 	lv_obj_scroll_to_y(page->base, 119, LV_ANIM_ON);

		page->update_map_ring_style(module_id);

		lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);

		// Draw all cables connected to this module
		// TODO: gotta be a cleaner way to do this...
		// 		push Jack{c.out}, this_module_obj, Jack{in}, outmodule_obj
		// 		draw_cable(Jack out, Jack in, lv_obj_t *out_module, lv_obj_t *in_module);
		const auto thismoduleinfo = ModuleFactory::getModuleInfo(this_slug);
		if (thismoduleinfo.width_hp > 0) {
			//for (const auto &c : patch.int_cables) {
			//	// Draw cable(s) if out jack is on this module
			//	if (c.out.module_id == module_id) {
			//		auto end = DrawHelper::get_jack_xy(thismoduleinfo.OutJacks, this_module_obj, c.out, height);

			//		// Draw a cable from this out jack to all in jacks it's connected to
			//		for (const auto &in : c.ins) {
			//			// Iterate through all modules to find the one with a matching id (TODO: better way to do this?)
			//			for (auto inmodule_obj : page->modules) {
			//				uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(inmodule_obj)));
			//				if (t_module_id == in.module_id) {
			//					const auto inmodule_info =
			//						ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
			//					auto start = DrawHelper::get_jack_xy(inmodule_info.InJacks, inmodule_obj, in, height);
			//					page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
			//					DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
			//					break;
			//				}
			//			}
			//		}
			//		continue; //We drew the output to all inputs, no need to check if any inputs are on this module
			//	}
			//	// Draw cable if in jack is on this module
			//	for (const auto &in : c.ins) {
			//		if (in.module_id == module_id) {
			//			auto start = DrawHelper::get_jack_xy(thismoduleinfo.InJacks, this_module_obj, in, height);
			//			//Find output jack on another module
			//			for (auto outmodule_obj : page->modules) {
			//				uint32_t t_module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(outmodule_obj)));
			//				if (t_module_id == c.out.module_id) {
			//					auto outmodule_info = ModuleFactory::getModuleInfo(patch.module_slugs[t_module_id]);
			//					auto end =
			//						DrawHelper::get_jack_xy(outmodule_info.OutJacks, outmodule_obj, c.out, height);
			//					page->cable_drawline_dsc.color = DrawHelper::get_cable_color(in);
			//					DrawHelper::draw_cable(start, end, page->cable_layer, &page->cable_drawline_dsc);
			//					break;
			//				}
			//			}
			//		}
			//	}
			// }
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
		lv_obj_scroll_to_y(page->base, 0, LV_ANIM_ON);
	}

	static void button_focussed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_obj_scroll_to_y(page->base, 0, LV_ANIM_ON);
	}

private:
	// lv_obj_t *description;
	lv_obj_t *patchname;
	lv_obj_t *modules_cont;
	lv_obj_t *module_name;
	// lv_obj_t *playbut_label;
	lv_obj_t *playbut;
	lv_obj_t *cable_layer;

	PatchData &patch = patch_storage.get_view_patch();

	std::vector<lv_obj_t *> module_canvases;
	std::vector<uint32_t> module_ids;
	std::vector<DrawnElement> drawn_elements;
	bool is_patch_playing = false;

	lv_draw_line_dsc_t cable_drawline_dsc;

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
