#pragma once
#include "CoreModules/info/module_info_base.hh"
#include "knob_edit.hh"
#include "lvgl/src/core/lv_obj_pos.h"
#include "pages/base.hh"
#include "pages/draw_helpers.hh"
#include "pages/images/image_list.hh"
#include "pages/module_param.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
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

	ModuleViewPage(PatchInfo info, std::string_view module_slug = "EnOsc")
		: PageBase{info}
		, slug(module_slug)
		, base(lv_obj_create(nullptr))
		, canvas(lv_canvas_create(base))
		, roller(lv_roller_create(base))
		, edit_pane(lv_obj_create(base))
		, knob_edit_pane{info, edit_pane} {
		PageList::register_page(this, PageId::ModuleView);

		init_bg(base);

		lv_draw_img_dsc_init(&img_dsc);

		lv_group_add_obj(group, roller);
		lv_obj_add_style(roller, &Gui::roller_style, LV_PART_MAIN);
		lv_obj_add_style(roller, &Gui::plain_border_style, /*LV_PART_MAIN |*/ LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		lv_obj_add_style(roller, &Gui::roller_sel_style, LV_PART_SELECTED);

		lv_obj_add_flag(edit_pane, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_style(edit_pane, &Gui::plain_border_style, LV_PART_MAIN);
		lv_obj_set_style_pad_all(edit_pane, 0, LV_STATE_DEFAULT);

		button.clear();
		module_controls.clear();
	}

	void prepare_focus() override {
		mode = ViewMode::List;

		this_module_id = PageList::get_selected_module_id();

		if (!read_slug()) {
			msg_queue.append_message("Module View page cannot read module slug.\n");
			return;
		}
		printf_("ModuleViewPage module %s\n", slug.data());

		moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			msg_queue.append_message("Module View page got empty module slug.\r\n");
			return;
		}

		reset_module_page();

		//Draw module image
		const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug);
		if (!img) {
			printf_("Image not found\n");
			return;
		}
		auto width_px = img->header.w;
		lv_obj_set_size(canvas, width_px, 240);
		lv_canvas_set_buffer(canvas, buffer, width_px, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);
		lv_canvas_draw_img(canvas, 0, 0, img, &img_dsc);

		//Create text list (roller options) and circles over components

		size_t num_controls = moduleinfo.InJacks.size() + moduleinfo.OutJacks.size() + moduleinfo.Knobs.size() +
							  moduleinfo.Switches.size();
		opts.reserve(num_controls * 12); //12 chars per roller item
		button.reserve(num_controls);
		mapped_knobs.reserve(num_controls);
		static_knobs.reserve(num_controls);
		module_controls.reserve(num_controls);

		// const auto &patch = patch_list.get_patch(PageList::get_selected_patch_id());
		const auto &patch = patch_storage.get_view_patch();

		for (const auto el : moduleinfo.Knobs) {
			draw_knob(el, patch);
			module_controls.push_back({ModuleParam::Type::Knob, el.id});
		}

		for (const auto &el : moduleinfo.InJacks) {
			draw_injack(el, patch);
			module_controls.push_back({ModuleParam::Type::InJack, el.id});
		}

		for (const auto el : moduleinfo.OutJacks) {
			draw_outjack(el, patch);
			module_controls.push_back({ModuleParam::Type::OutJack, el.id});
		}

		for (const auto el : moduleinfo.Switches) {
			draw_switch(el, patch);
			module_controls.push_back({ModuleParam::Type::Switch, el.id + moduleinfo.Knobs.size()});
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		lv_obj_set_pos(roller, width_px, 0);
		lv_obj_set_size(roller, 320 - width_px, 240);
		lv_obj_clear_flag(roller, LV_OBJ_FLAG_HIDDEN);

		// Add text list to roller options
		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 11);
		lv_obj_add_event_cb(roller, roller_cb, LV_EVENT_KEY, this);
		lv_obj_add_event_cb(roller, roller_click_cb, LV_EVENT_CLICKED, this);

		//Select first element
		lv_roller_set_selected(roller, 0, LV_ANIM_OFF);
		cur_selected = 0;
		lv_obj_add_style(button[cur_selected], &Gui::panel_highlight_style, LV_PART_MAIN);

		lv_obj_set_pos(edit_pane, width_px, 0);
		lv_obj_set_size(edit_pane, 320 - width_px, 240);
		lv_obj_add_flag(edit_pane, LV_OBJ_FLAG_HIDDEN);
	}

	void update() override {
		// Back button: Knob -> List -> last_page
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

		// Update mapped knobs rotation
		for (auto &knob : mapped_knobs) {
			const float new_pot_val = knob.patchconf.get_mapped_val(params.knobs[knob.patchconf.panel_knob_id]);
			if (std::abs(new_pot_val - knob.last_pot_reading) > 0.01f) {
				knob.last_pot_reading = new_pot_val;
				DrawHelper::animate_control(knob, moduleinfo);
			}
		}

		// Update static knobs rotation
		for (auto &knob : static_knobs) {
			if (std::abs(knob.patchconf.value - knob.last_pot_reading) > 0.01f) {
				knob.last_pot_reading = knob.patchconf.value;
				DrawHelper::animate_control(knob, moduleinfo);
			}
		}
	}

private:
	void draw_outjack(const OutJackDef &el, const PatchData &patch) {
		int c_x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
		int c_y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
		add_button(c_x, c_y);
		lv_canvas_draw_img(canvas, c_x - jack_x.header.w / 2, c_y - jack_x.header.h / 2, &jack_x, &img_dsc);

		Jack jack{.module_id = this_module_id, .jack_id = (uint16_t)el.id};
		if (auto mappedjack = patch.find_mapped_outjack(jack)) {
			Gui::mapped_jack_arcdsc.color = Gui::palette_main[el.id % 8];
			lv_canvas_draw_arc(canvas, c_x, c_y, jack_x.header.w * 0.8f, 0, 3600, &Gui::mapped_jack_arcdsc);
			opts += "[";
			opts += PanelDef::OutJackNames[mappedjack->panel_jack_id];
			opts += "] ";
		}
		opts += el.short_name;
		opts += "\n";
	}

	void draw_injack(const InJackDef &el, const PatchData &patch) {
		int c_x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
		int c_y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
		add_button(c_x, c_y);
		lv_canvas_draw_img(canvas, c_x - jack_x.header.w / 2, c_y - jack_x.header.h / 2, &jack_x, &img_dsc);

		Jack jack{.module_id = this_module_id, .jack_id = (uint16_t)el.id};
		if (auto mappedjack = patch.find_mapped_injack(jack)) {
			Gui::mapped_jack_arcdsc.color = Gui::palette_main[el.id % 8];
			lv_canvas_draw_arc(canvas, c_x, c_y, jack_x.header.w * 0.8f, 0, 3600, &Gui::mapped_jack_arcdsc);
			opts += "[";
			opts += PanelDef::InJackNames[mappedjack->panel_jack_id];
			opts += "] ";
		}
		opts += el.short_name;
		opts += "\n";
	}

	void draw_switch(const SwitchDef &el, const PatchData &patch) {
		draw_control(el, patch, moduleinfo.Knobs.size());
	}

	void draw_knob(const KnobDef &el, const PatchData &patch) {
		draw_control(el, patch, 0);
	}

	void draw_control(const auto /*ControlC*/ &el, const PatchData &patch, uint32_t id_offset = 0) {
		auto id = id_offset + el.id;
		auto static_ctrl = patch.find_static_knob(this_module_id, id);
		float value = static_ctrl ? static_ctrl->value : 0.f;
		auto ctrl_opt = DrawHelper::draw_control(base, el, 240, value);
		if (ctrl_opt) {
			lv_obj_t *ctrl_obj = ctrl_opt.value();
			auto anim_method = DrawHelper::get_anim_method(el);
			if (auto mapped_knob = patch.find_mapped_knob(this_module_id, id)) {
				mapped_knobs.push_back({ctrl_obj, *mapped_knob, anim_method});
				opts += "[";
				opts += PanelDef::KnobNames[mapped_knob->panel_knob_id];
				opts += "] ";
				DrawHelper::draw_control_ring(canvas, el, mapped_knob->panel_knob_id, 240);
			} else if (static_ctrl) {
				static_knobs.push_back({ctrl_obj, *static_ctrl, anim_method});
			}
		}
		opts += el.short_name;
		opts += "\n";

		auto img = DrawHelper::get_control_img(el, 240, value);
		auto [c_x, c_y] = DrawHelper::scale_center(el, 240);
		add_button(c_x, c_y, img->header.w * 1.2f);
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
		button.clear();

		for (auto &k : mapped_knobs)
			lv_obj_del(k.obj);
		mapped_knobs.clear();

		for (auto &k : static_knobs)
			lv_obj_del(k.obj);
		static_knobs.clear();

		module_controls.clear();
		opts.clear();
	}

	bool read_slug() {
		auto module_id = PageList::get_selected_module_id();
		const auto &patch = patch_storage.get_view_patch();
		if (patch.patch_name.length() == 0)
			return false;
		if (module_id >= patch.module_slugs.size())
			return false;

		slug = patch.module_slugs[module_id];
		return true;
	}

	bool is_this_patch_loaded() {
		return patch_playloader.cur_patch_index() == PageList::get_selected_patch_id();
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
			// auto mappedknob = patch.find_mapped_knob(PageList::get_selected_module_id(), module_controls[cur_sel].id);
			// if (!mappedknob) {
			// 	auto static_knob = patch.get_static_knob_value(page->this_module_id, module_controls[cur_sel].id);
			// 	if (static_knob) {
			// 		lv_obj_clear_flag(page->manual_knob, LV_OBJ_FLAG_HIDDEN);
			// 		lv_arc_set_value(page->manual_knob, static_knob.value() * 100);
			// 		lv_group_focus_obj(page->manual_knob);
			// 		lv_group_set_editing(page->group, true);
			// 		printf_("Initial knob value set to %f\n", (double)static_knob.value() * 100);
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

		if (page->is_this_patch_loaded()) {
			page->patch_mod_queue.put(SetStaticParam{.param = sp});
		} else {

			//FIXME: this just modifies PatchStoage::_view_patch which will get
			// overwritten if we select a new patch in PatchSelector
			//
			// auto &patch = page->patch_list.get_patch(PageList::get_selected_patch_id());
			auto &patch = page->patch_storage.get_view_patch();
			patch.set_static_knob_value(sp.module_id, sp.param_id, sp.value);
		}
	}

	ModuleInfoView moduleinfo;

	std::string opts;
	uint16_t this_module_id;
	uint32_t cur_selected = 0;
	std::string_view slug;

	std::vector<DrawHelper::MKnob> mapped_knobs;
	std::vector<DrawHelper::SKnob> static_knobs;

	std::vector<lv_obj_t *> button;
	std::vector<ModuleParam> module_controls;

	lv_obj_t *base = nullptr;
	lv_obj_t *canvas = nullptr;
	lv_obj_t *roller = nullptr;
	lv_obj_t *edit_pane = nullptr;
	// lv_obj_t *manual_knob = nullptr;
	KnobEditPage knob_edit_pane;

	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)];
	lv_draw_img_dsc_t img_dsc;

	enum class ViewMode { List, Knob } mode;
};

} // namespace MetaModule
