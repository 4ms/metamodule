#pragma once
#include "CoreModules/elements/element_info.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/module_param.hh"
#include "gui/elements/update.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/knob_edit.hh"
#include "gui/pages/page_list.hh"
#include "gui/styles.hh"
#include <string>

LV_IMG_DECLARE(jack_x);
LV_IMG_DECLARE(knob9mm_x);
LV_IMG_DECLARE(knob_x);
LV_IMG_DECLARE(button_x);
LV_IMG_DECLARE(knob_unlined_x);
LV_IMG_DECLARE(knob_large_x);
LV_IMG_DECLARE(slider_x);
LV_IMG_DECLARE(switch_left);
LV_IMG_DECLARE(switch_right);
LV_IMG_DECLARE(switch_up);
LV_IMG_DECLARE(switch_down);

namespace MetaModule
{
struct ModuleViewPage : PageBase {

	struct ViewSettings {
		bool map_ring_flash_active = true;
		MapRingDisplay::Style map_ring_style = {.mode = MapRingDisplay::StyleMode::ShowAll, .opa = LV_OPA_50};
	};
	ViewSettings settings;

	ModuleViewPage(PatchInfo info, std::string_view module_slug = "EnOsc")
		: PageBase{info}
		, slug(module_slug)
		, patch{patch_storage.get_view_patch()}
		, base(lv_obj_create(nullptr))
		, roller(lv_roller_create(base))
		, edit_pane(lv_obj_create(base))
		, knob_edit_pane{info, edit_pane} {
		PageList::register_page(this, PageId::ModuleView);

		init_bg(base);

		lv_draw_img_dsc_init(&img_dsc);

		lv_group_add_obj(group, roller);
		lv_obj_add_style(roller, &Gui::roller_style, LV_PART_MAIN);
		lv_obj_add_style(roller,
						 &Gui::plain_border_style,
						 /*LV_PART_MAIN |*/ LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		lv_obj_add_style(roller, &Gui::roller_sel_style, LV_PART_SELECTED);

		lv_obj_add_flag(edit_pane, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_style(edit_pane, &Gui::plain_border_style, LV_PART_MAIN);
		lv_obj_set_style_pad_all(edit_pane, 0, LV_STATE_DEFAULT);

		button.clear();
		module_controls.clear();
	}

	void prepare_focus() override {
		patch = patch_storage.get_view_patch();

		is_patch_playing = PageList::get_selected_patch_id() == patch_playloader.cur_patch_index();
		mode = ViewMode::List;

		this_module_id = PageList::get_selected_module_id();

		if (!read_slug()) {
			msg_queue.append_message("Module View page cannot read module slug.\n");
			return;
		}
		printf_("ModuleViewPage module %s\n", slug.data());

		moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			msg_queue.append_message("Module View page got empty module info.\r\n");
			return;
		}

		reset_module_page();

		size_t num_elements = moduleinfo.elements.size();
		opts.reserve(num_elements * 16); // 16 chars per roller item
		button.reserve(num_elements);
		drawn_elements.reserve(num_elements);
		module_controls.reserve(num_elements);

		auto module_drawer = ModuleDrawer{base, 240};
		canvas = module_drawer.draw_faceplate(slug, buffer);

		lv_obj_refr_size(canvas);
		auto width_px = lv_obj_get_width(canvas);

		module_drawer.draw_mapped_elements(
			patch, this_module_id, active_knob_set, canvas, drawn_elements, is_patch_playing);

		lv_obj_update_layout(canvas);

		for (const auto &drawn_element : drawn_elements) {
			std::visit(
				[this, drawn = drawn_element.gui_element](auto &el) {
					if (!drawn.obj)
						return;

					opts += el.short_name;
					if (drawn.mapped_panel_id) {
						opts += " [";
						opts += get_panel_name<PanelDef>(el, *(drawn.mapped_panel_id));
						opts += "]";
					}
					opts += "\n";

					add_button(drawn.obj);
					//emplace_back fails for clang-14
					module_controls.push_back({ModuleParam::get_type(el), (uint32_t)drawn.idx});
				},
				drawn_element.element);
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		//Show Roller and select it
		lv_obj_set_pos(roller, width_px, 0);
		lv_obj_set_size(roller, 320 - width_px, 240);
		lv_obj_clear_flag(roller, LV_OBJ_FLAG_HIDDEN);

		// Add text list to roller options
		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 11);
		lv_obj_add_event_cb(roller, roller_cb, LV_EVENT_KEY, this);
		lv_obj_add_event_cb(roller, roller_click_cb, LV_EVENT_PRESSED, this);

		// Select first element
		lv_roller_set_selected(roller, 0, LV_ANIM_OFF);
		cur_selected = 0;

		if (button.size() > 0) {
			lv_obj_add_style(button[cur_selected], &Gui::panel_highlight_style, LV_PART_MAIN);
		}

		update_map_ring_style();

		// Hide Edit pane
		lv_obj_set_pos(edit_pane, width_px, 0);
		lv_obj_set_size(edit_pane, 320 - width_px, 240);
		lv_obj_add_flag(edit_pane, LV_OBJ_FLAG_HIDDEN);

		lv_group_focus_obj(roller);
		lv_group_set_editing(group, false);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (mode == ViewMode::List) {
				if (PageList::request_last_page()) {
					blur();
				}
			} else {
				mode = ViewMode::List;
				lv_obj_add_flag(edit_pane, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(roller, LV_OBJ_FLAG_HIDDEN);
				lv_group_focus_obj(roller);
				lv_group_set_editing(group, true);
			}
		}

		if (is_patch_playing) {
			for (auto &drawn_el : drawn_elements) {
				std::visit(
					[this, gui_el = drawn_el.gui_element](auto &el) {
						bool did_update = update_element(el, params, patch, gui_el);
						if (did_update) {
							if (settings.map_ring_flash_active)
								MapRingDisplay::flash_once(gui_el.map_ring, settings.map_ring_style, true);
						}
					},
					drawn_el.element);
			}
		}
	}

	// This gets called after map_ring_style changes
	void update_map_ring_style() {
		using enum MapRingDisplay::StyleMode;

		for (auto &drawn_el : drawn_elements) {
			auto map_ring = drawn_el.gui_element.map_ring;

			switch (settings.map_ring_style.mode) {
				case ShowAllIfPlaying:
				case CurModuleIfPlaying:
					if (is_patch_playing)
						MapRingDisplay::show(map_ring, settings.map_ring_style.opa);
					else
						MapRingDisplay::hide(map_ring);

					break;

				case CurModule:
				case ShowAll:
					MapRingDisplay::show(map_ring, settings.map_ring_style.opa);
					break;

				case HideAlways:
					MapRingDisplay::hide(map_ring);
					break;
			}
		}
	}

	// void blur() final {
	// drawn_elements.clear();
	// }

private:
	void add_button(lv_obj_t *obj) {
		auto c_x = lv_obj_get_x(obj) + lv_obj_get_width(obj) / 2;
		auto c_y = lv_obj_get_y(obj) + lv_obj_get_height(obj) / 2;
		add_button(c_x, c_y, (float)lv_obj_get_width(obj) * 1.5f);
	}

	void add_button(int x, int y, int size = 20) {
		auto &b = button.emplace_back();
		b = lv_btn_create(base);
		lv_obj_add_style(b, &Gui::invisible_style, LV_PART_MAIN);
		lv_obj_set_pos(b, x - size / 2, y - size / 2);
		lv_obj_set_size(b, size, size);
	}

	void reset_module_page() {
		for (auto &b : button)
			lv_obj_del(b);

		if (canvas)
			lv_obj_del(canvas);

		button.clear();
		drawn_elements.clear();
		module_controls.clear();
		opts.clear();
	}

	bool read_slug() {
		auto module_id = PageList::get_selected_module_id();
		if (patch.patch_name.length() == 0)
			return false;
		if (module_id >= patch.module_slugs.size())
			return false;

		slug = patch.module_slugs[module_id];
		return true;
	}

	static void roller_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto roller = page->roller;
		auto &cur_sel = page->cur_selected;
		auto &but = page->button;

		// Turn off old button
		if (cur_sel >= 0) {
			lv_obj_remove_style(but[cur_sel], &Gui::panel_highlight_style, LV_PART_MAIN);
			lv_event_send(but[cur_sel], LV_EVENT_REFRESH, nullptr);
		}

		// Get the new button
		cur_sel = lv_roller_get_selected(roller);

		// Turn on new button
		lv_obj_add_style(but[cur_sel], &Gui::panel_highlight_style, LV_PART_MAIN);
		lv_event_send(but[cur_sel], LV_EVENT_REFRESH, nullptr);
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto cur_sel = page->cur_selected;
		auto &module_controls = page->module_controls;

		if (cur_sel < module_controls.size()) {
			printf_("Click %d\n", cur_sel);
			PageList::set_selected_control(module_controls[cur_sel]);

			// Hide roller, show edit pane
			page->mode = ViewMode::Knob;
			lv_obj_add_flag(page->roller, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(page->edit_pane, LV_OBJ_FLAG_HIDDEN);
			page->knob_edit_pane.prepare_focus();
			page->knob_edit_pane.set_group(page->group);

			// Show manual knob
			// auto patch_id = PageList::get_selected_patch_id();
			// auto &patch = page->patch_list.get_patch(patch_id);
			// auto mappedknob =
			// patch.find_mapped_knob(PageList::get_selected_module_id(),
			// module_controls[cur_sel].id); if (!mappedknob) { 	auto static_knob =
			// patch.get_static_knob_value(page->this_module_id,
			// module_controls[cur_sel].id); 	if (static_knob) {
			// 		lv_obj_clear_flag(page->manual_knob,
			// LV_OBJ_FLAG_HIDDEN); 		lv_arc_set_value(page->manual_knob,
			// static_knob.value() * 100); 		lv_group_focus_obj(page->manual_knob);
			// 		lv_group_set_editing(page->group, true);
			// 		printf_("Initial knob value set to %f\n",
			// (double)static_knob.value() * 100);
			// 	}
			// } else {
			// 	lv_obj_add_flag(page->manual_knob, LV_OBJ_FLAG_HIDDEN);
			// 	printf_("Knob is mapped\n");
			// }

			// PageList::request_new_page(PageId::KnobEdit);
			// page->blur();
		}
	}

	static void manual_knob_adjust(lv_event_t *event) {
		auto page = static_cast<ModuleViewPage *>(event->user_data);
		auto this_control_id = static_cast<uint16_t>(PageList::get_selected_control().id);
		lv_obj_t *arc = lv_event_get_target(event);

		StaticParam sp{
			.module_id = page->this_module_id,
			.param_id = this_control_id,
			.value = lv_arc_get_value(arc) / 100.f,
		};

		if (page->is_patch_playing) {
			page->patch_mod_queue.put(SetStaticParam{.param = sp});
		} else {

			// FIXME: this just modifies PatchStoage::_view_patch which will get
			//  overwritten if we select a new patch in PatchSelector
			page->patch.set_static_knob_value(sp.module_id, sp.param_id, sp.value);
		}
	}

	ModuleInfoView moduleinfo;

	std::string opts;
	uint16_t this_module_id;
	uint32_t cur_selected = 0;
	std::string_view slug;
	bool is_patch_playing = false;
	PatchData &patch;

	// TODO:put this in PageList
	unsigned active_knob_set = 0;

	std::vector<lv_obj_t *> button;
	std::vector<ModuleParam> module_controls;
	std::vector<DrawnElement> drawn_elements;

	lv_obj_t *base = nullptr;
	lv_obj_t *canvas = nullptr;
	lv_obj_t *roller = nullptr;
	lv_obj_t *edit_pane = nullptr;
	KnobEditPage knob_edit_pane;

	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)];
	lv_draw_img_dsc_t img_dsc;

	enum class ViewMode { List, Knob } mode;
};

} // namespace MetaModule
