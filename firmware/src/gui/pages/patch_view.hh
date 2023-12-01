#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "gui/elements/map_ring_animate.hh"
#include "gui/elements/map_ring_drawer.hh"
#include "gui/elements/mapping.hh"
#include "gui/elements/module_drawer.hh"
#include "gui/elements/redraw_light.hh"
#include "gui/elements/update.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/pages/base.hh"
#include "gui/pages/cables.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_view_knobset_menu.hh"
#include "gui/pages/patch_view_settings_menu.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include "src/core/lv_obj_scroll.h"
#include "util/countzip.hh"

namespace MetaModule
{

struct PatchViewPage : PageBase {
	static inline uint32_t Height = 180;

	PatchViewPage(PatchInfo info)
		: PageBase{info}
		, base(ui_PatchViewPage)
		, modules_cont(ui_ModulesPanel)
		, cable_drawer{modules_cont, drawn_elements}
		, info_group(lv_group_create()) {
		PageList::register_page(this, PageId::PatchView);

		init_bg(base);
		lv_group_set_editing(group, false);

		lv_obj_add_event_cb(ui_PlayButton, playbut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_InfoButton, infobut_cb, LV_EVENT_CLICKED, this);

		// Scroll to top when focussing on a button
		lv_obj_add_event_cb(ui_PlayButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_AddButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_InfoButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_KnobButton, button_focussed_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_SettingsButton, button_focussed_cb, LV_EVENT_FOCUSED, this);

		lv_obj_add_event_cb(ui_PatchViewPage, scroll_end_cb, LV_EVENT_SCROLL, this);

		// Settings menu
		settings_menu.init();
		knobset_menu.init();

		lv_obj_add_style(ui_ModuleName, &Gui::header_style, LV_PART_MAIN);
		lv_label_set_text(ui_ModuleName, "");
		lv_hide(ui_ModuleName);

		lv_hide(ui_DescriptionPanel);
		lv_group_add_obj(info_group, ui_DescriptionPanel);
	}

	void prepare_focus() override {
		is_ready = false;
		lv_hide(ui_DescriptionPanel);
		lv_label_set_text(ui_Description, patch.description.c_str());

		is_patch_playing = displayed_patch_loc == patch_playloader.cur_patch_location();

		if (is_patch_playing) {
			lv_label_set_text_fmt(ui_LoadMeter2, "%d%%", metaparams.audio_load);
			lv_show(ui_LoadMeter2);
			lv_obj_add_state(ui_PlayButton, LV_STATE_USER_2);
		} else {
			lv_label_set_text(ui_LoadMeter2, "");
			lv_hide(ui_LoadMeter2);
			lv_obj_clear_state(ui_PlayButton, LV_STATE_USER_2);
		}

		if (active_knob_set == PageList::get_active_knobset() && patch_revision == PageList::get_patch_revision() &&
			displayed_patch_loc == PageList::get_selected_patch_location())
		{
			watch_lights();
			is_ready = true;
			return;
		}
		displayed_patch_loc = PageList::get_selected_patch_location();
		patch_revision = PageList::get_patch_revision();
		active_knob_set = PageList::get_active_knobset();

		clear();

		lv_hide(modules_cont);

		patch = patch_storage.get_view_patch();

		if (patch.patch_name.length() == 0)
			return;

		lv_label_set_text(ui_PatchName, patch.patch_name.c_str());

		module_canvases.reserve(patch.module_slugs.size());
		module_ids.reserve(patch.module_slugs.size());

		lv_group_remove_all_objs(group);
		lv_group_set_editing(group, false);

		lv_group_add_obj(group, ui_PlayButton);
		lv_group_add_obj(group, ui_KnobButton);
		lv_group_add_obj(group, ui_AddButton);
		lv_group_add_obj(group, ui_InfoButton);
		lv_group_add_obj(group, ui_SettingsButton);

		lv_show(modules_cont);

		auto module_drawer = ModuleDrawer{modules_cont, Height};

		auto canvas_buf = std::span<lv_color_t>{page_pixel_buffer};
		int bottom = 0;

		for (auto [module_idx, slug] : enumerate(patch.module_slugs)) {
			module_ids.push_back(module_idx);

			auto canvas = module_drawer.draw_faceplate(slug, canvas_buf);
			if (!canvas)
				continue;

			module_drawer.draw_mapped_elements(
				patch, module_idx, active_knob_set, canvas, drawn_elements, is_patch_playing);

			// Increment the buffer
			lv_obj_refr_size(canvas);
			canvas_buf = canvas_buf.subspan(LV_CANVAS_BUF_SIZE_TRUE_COLOR(1, 1) * lv_obj_get_width(canvas) * Height);
			int this_bottom = lv_obj_get_y(canvas) + lv_obj_get_height(canvas);
			bottom = std::max(bottom, this_bottom);

			module_canvases.push_back(canvas);

			lv_group_add_obj(group, canvas);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_SNAPPABLE);

			lv_obj_add_style(canvas, &Gui::plain_border_style, LV_STATE_DEFAULT);
			lv_obj_add_style(canvas, &Gui::selected_module_style, LV_STATE_FOCUS_KEY);
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
			lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);

			// Give the callback access to the module_idx:
			lv_obj_set_user_data(canvas, (void *)(&module_ids[module_ids.size() - 1]));
			lv_obj_add_event_cb(canvas, module_pressed_cb, LV_EVENT_CLICKED, (void *)this);
			lv_obj_add_event_cb(canvas, module_focus_cb, LV_EVENT_FOCUSED, (void *)this);
		}

		watch_lights();

		highlighted_module_id = std::nullopt;
		highlighted_module_obj = nullptr;
		update_map_ring_style();
		cable_drawer.set_height(bottom + 30);
		cable_drawer.draw(patch);

		lv_obj_scroll_to_y(base, 0, LV_ANIM_OFF);

		settings_menu.focus(group);
		knobset_menu.focus(group, patch.knob_sets);
		is_ready = true;
	}

	void blur() override {
		// printf("Blur patchview page\n");
		settings_menu.hide();
		knobset_menu.hide();
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_PRESSED);
		lv_obj_clear_state(ui_SettingsButton, LV_STATE_FOCUSED);
		lv_obj_clear_state(ui_InfoButton, LV_STATE_PRESSED);
		lv_obj_clear_state(ui_InfoButton, LV_STATE_FOCUSED);
	}

	void update() override {
		bool last_is_patch_playing = is_patch_playing;
		is_patch_playing = displayed_patch_loc == patch_playloader.cur_patch_location();

		if (is_patch_playing != last_is_patch_playing || view_settings.changed) {
			view_settings.changed = false;
			update_map_ring_style();
			update_cable_style();
		}

		if (is_patch_playing != last_is_patch_playing || knobset_settings.changed) {
			knobset_settings.changed = false;
			update_active_knobset();
		}

		if (auto &knobset = knobset_menu.requested_knobset_view) {
			PageList::set_viewing_knobset(knobset.value());
			knobset = std::nullopt;
			PageList::request_new_page(PageId::KnobSetView);
		}

		if (metaparams.meta_buttons[0].is_just_released()) {
			if (settings_menu.visible) {
				settings_menu.hide();
			} else if (knobset_menu.visible) {
				knobset_menu.hide();
			} else if (showing_info) {
				showing_info = false;
				lv_hide(ui_DescriptionPanel);
				lv_indev_set_group(lv_indev_get_next(nullptr), group);
				lv_obj_clear_state(ui_InfoButton, LV_STATE_PRESSED);
			} else if (PageList::request_last_page()) {
				blur();
				params.lights.stop_watching_all();
			}
		}

		if (is_patch_playing) {
			update_changed_params();
			if (metaparams.audio_load != last_audio_load) {
				metaparams.audio_load = last_audio_load;
				lv_label_set_text_fmt(ui_LoadMeter2, "%d%%", metaparams.audio_load);
				lv_show(ui_LoadMeter2);
			}
		}

		if (is_patch_playing) {
			lv_obj_add_state(ui_PlayButton, LV_STATE_USER_2);
		} else {
			lv_obj_clear_state(ui_PlayButton, LV_STATE_USER_2);
		}
	}

private:
	void watch_lights() {
		is_patch_playing = displayed_patch_loc == patch_playloader.cur_patch_location();
		if (is_patch_playing) {
			for (const auto &drawn_element : drawn_elements) {
				auto &gui_el = drawn_element.gui_element;
				for (unsigned i = 0; i < gui_el.count.num_lights; i++) {
					params.lights.start_watching_light(gui_el.module_idx, gui_el.idx.light_idx + i);
				}
			}
		}
	}

	void update_changed_params() {
		std::array<std::vector<float>, MAX_MODULES_IN_PATCH> light_vals; //384B on the stack

		// copy light values from params
		// indexed by module id and light element id
		for (auto &wl : params.lights.watch_lights) {
			if (wl.is_active()) {
				auto &vec = light_vals[wl.module_id];
				if (vec.size() <= wl.light_id)
					vec.resize(wl.light_id + 1);
				vec[wl.light_id] = wl.value;
			}
		}

		// Redraw all elements that have changed state (knobs, lights, etc)
		auto is_visible = [](lv_coord_t pos) {
			auto visible_top = lv_obj_get_scroll_y(ui_PatchViewPage);
			auto visible_bot = visible_top + 240;
			return pos >= visible_top && pos < visible_bot;
		};

		for (auto &drawn_el : drawn_elements) {
			if (!drawn_el.gui_element.obj)
				continue;

			auto module_top_to_obj = lv_obj_get_y(drawn_el.gui_element.obj);
			auto panel_top_to_module_top = lv_obj_get_y(lv_obj_get_parent(drawn_el.gui_element.obj));
			auto panel_top_pos = lv_obj_get_y(ui_ModulesPanel);
			auto ypos = module_top_to_obj + panel_top_to_module_top + panel_top_pos;
			auto y2pos = ypos + lv_obj_get_height(drawn_el.gui_element.obj);

			if (!is_visible(ypos) && !is_visible(y2pos))
				continue;

			auto &gui_el = drawn_el.gui_element;

			auto was_redrawn = std::visit(UpdateElement{params, patch, drawn_el.gui_element}, drawn_el.element);
			if (was_redrawn) {
				if (view_settings.map_ring_flash_active)
					MapRingDisplay::flash_once(
						gui_el.map_ring, view_settings.map_ring_style, highlighted_module_id == gui_el.module_idx);

				if (view_settings.scroll_to_active_param)
					lv_obj_scroll_to_view_recursive(gui_el.obj, LV_ANIM_ON);
			}

			update_light(drawn_el, light_vals[gui_el.module_idx]);
		}
	}

	void update_map_ring_style() {
		if (!is_ready)
			return;

		for (auto &drawn_el : drawn_elements) {
			auto map_ring = drawn_el.gui_element.map_ring;
			bool is_on_highlighted_module = (drawn_el.gui_element.module_idx == highlighted_module_id);
			MapRingDisplay::update(map_ring, view_settings.map_ring_style, is_on_highlighted_module, is_patch_playing);
		}
	}

	void update_cable_style() {
		static MapRingDisplay::Style last_cable_style;
		if (view_settings.cable_style.mode != last_cable_style.mode) {
			if (view_settings.cable_style.mode == MapRingDisplay::StyleMode::ShowAll)
				cable_drawer.draw(patch);
			else
				cable_drawer.clear();
		}
		last_cable_style = view_settings.cable_style;
		cable_drawer.set_opacity(view_settings.cable_style.opa);
	}

	void update_active_knobset() {
		blur();
		PageList::set_active_knobset(knobset_settings.active_knobset);
		patch_mod_queue.put(ChangeKnobSet{knobset_settings.active_knobset});
		prepare_focus();
	}

	void redraw_modulename() {
		auto module_id = highlighted_module_id.value_or(0xFFFFFFFF);
		if (module_id >= patch.module_slugs.size())
			return;

		if (highlighted_module_obj == nullptr)
			return;

		lv_show(ui_ModuleName);

		auto module_y = lv_obj_get_y(highlighted_module_obj);
		auto scroll_y = lv_obj_get_scroll_top(ui_PatchViewPage);
		auto header_y = lv_obj_get_y(ui_ModulesPanel);
		int16_t module_top_on_screen = header_y - scroll_y + module_y;
		int16_t module_bot_on_screen = module_top_on_screen + Height;
		int16_t space_above = module_top_on_screen;
		int16_t space_below = 240 - module_bot_on_screen;
		if (space_below > space_above) {
			lv_obj_set_y(ui_ModuleName, module_bot_on_screen - 120 + 16);
		} else {
			lv_obj_set_y(ui_ModuleName, module_top_on_screen - 120 - 9);
		}
	}

	void clear() {
		for (auto &m : module_canvases)
			lv_obj_del(m);

		module_canvases.clear();
		drawn_elements.clear();
		module_ids.clear();

		settings_menu.blur();
		knobset_menu.blur();
	}

	static void module_pressed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;

		auto obj = event->current_target;
		if (!obj)
			return;
		uint32_t module_id = *(static_cast<uint32_t *>(lv_obj_get_user_data(obj)));
		PageList::set_selected_module_id(module_id);
		PageList::request_new_page(PageId::ModuleView);
	}

	static void module_focus_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		if (!page)
			return;

		auto this_module_obj = lv_group_get_focused(page->group);
		if (!this_module_obj)
			return;

		auto user_data = lv_obj_get_user_data(this_module_obj);
		if (!user_data)
			return;

		uint32_t module_id = *(static_cast<uint32_t *>(user_data));
		if (module_id >= page->patch.module_slugs.size())
			return;

		page->highlighted_module_id = module_id;
		page->highlighted_module_obj = this_module_obj;

		const auto this_slug = page->patch.module_slugs[module_id];
		lv_label_set_text(ui_ModuleName, this_slug.c_str());

		auto module_x = lv_obj_get_x(page->highlighted_module_obj);
		lv_obj_set_x(ui_ModuleName, module_x);

		page->redraw_modulename();

		page->update_map_ring_style();
	}

	static void scroll_end_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		page->redraw_modulename();
	}

	static void playbut_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		page->patch_playloader.request_load_view_patch();
	}

	static void infobut_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_show(ui_DescriptionPanel);
		lv_show(ui_Description);
		page->showing_info = true;
		lv_indev_set_group(lv_indev_get_act(), page->info_group);
	}

	static void button_focussed_cb(lv_event_t *event) {
		auto page = static_cast<PatchViewPage *>(event->user_data);
		lv_label_set_text(ui_ModuleName, "");
		lv_hide(ui_ModuleName);
		lv_obj_scroll_to_y(page->base, 0, LV_ANIM_ON);
		page->highlighted_module_id = std::nullopt;
		page->update_map_ring_style();
		page->settings_menu.hide();
		page->knobset_menu.hide();
	}

	lv_obj_t *base;
	lv_obj_t *modules_cont;
	CableDrawer cable_drawer;

	lv_group_t *info_group;
	bool showing_info = false;

	PatchViewSettingsMenu::ViewSettings view_settings;
	PatchViewSettingsMenu settings_menu{view_settings};

	PatchViewKnobsetMenu::Settings knobset_settings;
	PatchViewKnobsetMenu knobset_menu{knobset_settings};

	std::optional<uint32_t> highlighted_module_id{};
	lv_obj_t *highlighted_module_obj = nullptr;

	PatchData &patch = patch_storage.get_view_patch();

	std::vector<lv_obj_t *> module_canvases;
	std::vector<uint32_t> module_ids;
	std::vector<DrawnElement> drawn_elements;
	bool is_patch_playing = false;
	bool is_ready = false;

	PatchLocation displayed_patch_loc{0xFFFFFFFF, Volume::MaxVolumes};
	uint32_t patch_revision = 0xFFFFFFFF;

	unsigned active_knob_set = 0;

	unsigned last_audio_load = 0;

	struct focussed_context {
		PatchViewPage *page;
		uint32_t selected_module_id;
	};
};

} // namespace MetaModule
