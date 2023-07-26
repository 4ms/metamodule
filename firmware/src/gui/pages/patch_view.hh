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
extern "C" void ui_PatchViewPage_screen_init();

namespace MetaModule
{

struct PatchViewPage : PageBase {
	using enum MapRingDisplay::StyleMode;
	static inline uint32_t Height = 180;

	struct ViewSettings {
		bool map_ring_flash_active = true; //flash map ring if knob is turned while patch is playing
		bool scroll_to_active_param = false;
		MapRingDisplay::Style map_ring_style = {.mode = CurModuleIfPlaying, .opa = LV_OPA_50};
	};
	ViewSettings settings;

	PatchViewPage(PatchInfo info)
		: PageBase{info} {
		PageList::register_page(this, PageId::PatchView);

		ui_PatchViewPage_screen_init();
		base = ui_PatchViewPage; //NOLINT

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_flex_align(base, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_gap(base, 4, LV_STATE_DEFAULT);
		lv_obj_add_flag(base, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_scroll_dir(base, LV_DIR_VER);
		lv_obj_set_scrollbar_mode(base, LV_SCROLLBAR_MODE_ACTIVE);

		// lv_obj_add_event_cb(base, base_scroll_cb, LV_EVENT_SCROLL, (void *)this);

		patchname = ui_PatchName; //NOLINT

		playbut = ui_PlayButton; //NOLINT
		lv_obj_add_flag(playbut, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_clear_flag(playbut, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_event_cb(playbut, playbut_cb, LV_EVENT_PRESSED, this);

		lv_obj_add_flag(ui_AddButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_InfoButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_KnobButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(ui_SettingsButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

		// Scroll to top when focussing on a button
		lv_obj_add_event_cb(playbut, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_AddButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_InfoButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_KnobButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_SettingsButton, button_focussed_cb, LV_EVENT_FOCUSED, this);

		// Settings menu
		lv_obj_set_parent(ui_SettingsMenu, lv_layer_top());
		lv_obj_add_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN); /// Flags
		lv_obj_add_event_cb(ui_SettingsButton, settings_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_SettingsCloseButton, settings_cb, LV_EVENT_PRESSED, this);
		lv_obj_add_event_cb(ui_ShowAllCheck, settings_map_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ShowSelectedCheck, settings_map_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_FlashMapCheck, settings_map_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_MapTranspSlider, settings_map_cb, LV_EVENT_VALUE_CHANGED, this);

		module_name = lv_label_create(base); //NOLINT
		lv_obj_add_style(module_name, &Gui::header_style, LV_PART_MAIN);
		lv_label_set_text(module_name, "Select a module:");

		modules_cont = lv_obj_create(base); //NOLINT
		lv_obj_set_size(modules_cont, 320, 4 * Height + 8);
		lv_obj_set_style_bg_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(modules_cont, lv_color_black(), LV_STATE_DEFAULT);
		lv_obj_set_flex_flow(modules_cont, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_style_pad_gap(modules_cont, 3, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(modules_cont, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_radius(modules_cont, 0, LV_STATE_DEFAULT);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_flag(modules_cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

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

		// blur();

		module_canvases.reserve(patch.module_slugs.size());
		module_ids.reserve(patch.module_slugs.size());

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

		highlighted_module_id = std::nullopt;
		update_map_ring_style();
		//auto cable_drawer = CableDrawer{cable_cont, modules, patch, height};
		//cable_drawer.draw_all();

		lv_obj_scroll_to_y(base, 0, LV_ANIM_OFF);

		settings_menu_group = lv_group_create();
		lv_group_remove_all_objs(settings_menu_group);
		lv_group_set_editing(settings_menu_group, false);
		lv_group_add_obj(settings_menu_group, ui_SettingsCloseButton);
		lv_group_add_obj(settings_menu_group, ui_ShowAllCheck);
		lv_group_add_obj(settings_menu_group, ui_ShowSelectedCheck);
		lv_group_add_obj(settings_menu_group, ui_FlashMapCheck);
		lv_group_add_obj(settings_menu_group, ui_MapTranspSlider);
		lv_group_add_obj(settings_menu_group, ui_ShowAllCablesCheck);
	}

	void blur() override {
		hide_settings_menu();
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_PRESSED);
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_FOCUSED);

		for (auto &m : module_canvases) {
			lv_obj_del(m);
		}

		drawn_elements.clear();
		module_canvases.clear();
		module_ids.clear();
		lv_group_del(settings_menu_group);
	}

	void update() override {
		bool last_is_patch_playing = is_patch_playing;
		is_patch_playing = PageList::get_selected_patch_id() == patch_playloader.cur_patch_index();

		if (is_patch_playing != last_is_patch_playing)
			update_map_ring_style();

		if (metaparams.meta_buttons[0].is_just_released()) {
			if (!lv_obj_has_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN)) {
				hide_settings_menu();
			} else if (PageList::request_last_page()) {
				blur();
			}
		}

		if (is_patch_playing) {
			for (auto &drawn_el : drawn_elements) {
				std::visit(
					[this, gui_el = drawn_el.gui_element](auto &el) -> void {
						//if (drawn.obj) //TODO: This can be removed now, right?
						bool did_update = update_element(el, this->params, patch, gui_el);

						if (did_update) {
							if (settings.map_ring_flash_active) {
								MapRingDisplay::flash_once(gui_el.map_ring,
														   settings.map_ring_style,
														   highlighted_module_id == gui_el.module_idx);
							}
							if (settings.scroll_to_active_param) {
								lv_obj_scroll_to_view_recursive(gui_el.obj, LV_ANIM_ON);
							}
						}
					},
					drawn_el.element);
			}
		}
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style() {
		for (auto &drawn_el : drawn_elements) {
			auto map_ring = drawn_el.gui_element.map_ring;
			bool is_on_highlighted_module = (drawn_el.gui_element.module_idx == highlighted_module_id);
			MapRingDisplay::show_hide(map_ring, settings.map_ring_style, is_on_highlighted_module, is_patch_playing);
		}
	}

	static void settings_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewPage *>(event->user_data);

		if (lv_obj_has_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN)) {
			page->show_settings_menu();
		} else {
			page->hide_settings_menu();
		}
	}

	static void settings_map_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		lv_event_code_t event_code = lv_event_get_code(event);
		auto obj = lv_event_get_target(event);

		if (event_code == LV_EVENT_VALUE_CHANGED) {
			auto show_all = lv_obj_has_state(ui_ShowAllCheck, LV_STATE_CHECKED);
			auto show_selected = lv_obj_has_state(ui_ShowSelectedCheck, LV_STATE_CHECKED);
			auto flash_active = lv_obj_has_state(ui_FlashMapCheck, LV_STATE_CHECKED);

			// Do not allow both ShowAll and ShowSelected to be checked
			if (obj == ui_ShowAllCheck && show_all) {
				lv_obj_clear_state(ui_ShowSelectedCheck, LV_STATE_CHECKED);
				show_selected = !show_selected;
			} else if (obj == ui_ShowSelectedCheck && show_selected) {
				lv_obj_clear_state(ui_ShowAllCheck, LV_STATE_CHECKED);
				show_all = !show_all;
			}

			auto page = static_cast<PatchViewPage *>(event->user_data);
			auto &style = page->settings.map_ring_style;

			//TODO: one more switch: Always/While Playing
			if (show_all)
				style.mode = MapRingDisplay::StyleMode::ShowAllIfPlaying;
			else if (show_selected)
				style.mode = MapRingDisplay::StyleMode::CurModuleIfPlaying;
			else
				style.mode = MapRingDisplay::StyleMode::HideAlways;

			auto opacity = lv_slider_get_value(ui_MapTranspSlider); //0..100
			opacity = (float)opacity * 2.5f;
			page->settings.map_ring_style.opa = opacity;
			page->settings.map_ring_flash_active = flash_active;
			page->update_map_ring_style();
		}
	}

	void show_settings_menu() {
		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;
		lv_indev_set_group(indev, settings_menu_group);
		lv_group_focus_obj(ui_SettingsCloseButton);
		lv_obj_clear_state(ui_SettingsCloseButton, LV_STATE_PRESSED);
		lv_obj_clear_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN);
	}

	void hide_settings_menu() {
		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;
		lv_indev_set_group(indev, group);
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_PRESSED);
		lv_obj_add_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN);
	}

	static void module_pressed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;
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

		page->highlighted_module_id = module_id;

		const auto this_slug = page->patch.module_slugs[module_id];
		lv_label_set_text(page->module_name, this_slug.c_str());

		// if (lv_obj_get_scroll_y(page->base) == 0 && num_rows > 1)
		// 	lv_obj_scroll_to_y(page->base, 119, LV_ANIM_ON);

		page->update_map_ring_style();

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
		printf_("Module defocus cb\n");
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_canvas_fill_bg(page->cable_layer, lv_color_white(), LV_OPA_0);
	}

	static void playbut_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		printf_("Clicked Play: playing patch# %d\n\r", PageList::get_selected_patch_id());
		page->start_changing_patch();
	}

	static void button_focussed_cb(lv_event_t *event) {
		printf_("But focus cb\n");
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_label_set_text(page->module_name, "Select a module:");
		lv_obj_scroll_to_y(page->base, 0, LV_ANIM_ON);
		page->highlighted_module_id = std::nullopt;
		// Hide the Settings Menu
		lv_obj_add_flag(ui_SettingsMenu, LV_OBJ_FLAG_HIDDEN);
	}

private:
	// lv_obj_t *description;
	lv_obj_t *base;
	lv_obj_t *patchname;
	lv_obj_t *modules_cont;
	lv_obj_t *module_name;
	lv_obj_t *playbut;
	lv_obj_t *cable_layer;

	lv_group_t *settings_menu_group;

	std::optional<uint32_t> highlighted_module_id{};

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

	void start_changing_patch() {
		patch_playloader.request_load_view_patch();
	}
};

} // namespace MetaModule
