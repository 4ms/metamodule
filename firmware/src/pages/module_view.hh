#pragma once
#include "CoreModules/info/module_info_base.hh"
#include "lvgl/src/core/lv_obj_pos.h"
#include "pages/base.hh"
#include "pages/draw_helpers.hh"
#include "pages/images/image_list.hh"
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
		, base(lv_obj_create(nullptr))
		, slug(module_slug) {
		PageList::register_page(this, PageId::ModuleView);

		init_bg(base);

		canvas = lv_canvas_create(base);
		lv_draw_img_dsc_init(&img_dsc);

		roller = lv_roller_create(base);
		lv_group_add_obj(group, roller);
		lv_obj_add_event_cb(roller, roller_cb, LV_EVENT_KEY, this);

		button.clear();

		lv_obj_add_style(roller, &Gui::roller_style, LV_PART_MAIN);
		lv_obj_add_style(roller, &Gui::plain_border_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		lv_obj_add_style(roller, &Gui::roller_sel_style, LV_PART_SELECTED);
	}

	void prepare_focus() override {
		this_module_id = PageList::get_selected_module_id();

		if (!read_slug()) {
			mbox.append_message("Module View page cannot read module slug.\n");
			return;
		}
		printf("ModuleViewPage module %s\n", slug.data());

		auto moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			mbox.append_message("Module View page got empty module slug.\r\n");
			return;
		}

		reset_module_page();

		//Draw module image
		const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug);
		if (!img) {
			printf("Image not found\n");
			return;
		}
		auto width_px = img->header.w;
		lv_obj_set_size(canvas, width_px, 240);
		lv_canvas_set_buffer(canvas, buffer, width_px, 240, LV_IMG_CF_TRUE_COLOR_ALPHA);
		lv_canvas_draw_img(canvas, 0, 0, img, &img_dsc);

		//Create text list (roller options) and circles over components

		size_t num_controls = moduleinfo.InJacks.size() + moduleinfo.OutJacks.size() + moduleinfo.Knobs.size() +
							  moduleinfo.Switches.size();
		opts.reserve(num_controls * 12);
		button.reserve(num_controls);
		mapped_knobs.reserve(num_controls);

		const auto &patch = patch_list.get_patch(PageList::get_selected_patch_id());

		for (const auto el : moduleinfo.Knobs) {
			draw_knob(el, patch);
			img_dsc.angle = 0;
		}

		for (const auto &el : moduleinfo.InJacks) {
			draw_injack(el, patch);
		}

		for (const auto el : moduleinfo.OutJacks) {
			draw_outjack(el, patch);
		}

		for (const auto el : moduleinfo.Switches) {
			draw_switch(el, patch);
		}

		// remove final \n
		if (opts.length() > 0)
			opts.pop_back();

		lv_obj_set_pos(roller, width_px, 0);
		lv_obj_set_size(roller, 320 - width_px, 240);

		// Add text list to roller options
		lv_roller_set_options(roller, opts.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 11);

		//Select first element
		lv_roller_set_selected(roller, 0, LV_ANIM_OFF);
		cur_selected = 0;
		lv_obj_add_style(button[cur_selected], &Gui::panel_highlight_style, LV_PART_MAIN);
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}

		for (auto &mk : mapped_knobs) {
			const float new_pot_val = mk.mapped_knob.get_mapped_val(params.knobs[mk.mapped_knob.panel_knob_id]);
			if (std::abs(new_pot_val - mk.last_pot_reading) > 0.01f) {
				mk.last_pot_reading = new_pot_val;
				const int angle = new_pot_val * 3000.f - 1500.f;
				lv_img_set_angle(mk.obj, angle);
			}
		}
	}

private:
	void draw_knob(const KnobDef &el, const PatchData &patch) {
		int16_t c_x = std::round(ModuleInfoBase::mm_to_px<240>(el.x_mm));
		int16_t c_y = std::round(ModuleInfoBase::mm_to_px<240>(el.y_mm));

		const lv_img_dsc_t *knob = DrawHelper::get_knob_img_240(el.knob_style);
		if (!knob)
			return;

		int width = knob->header.w;
		int height = knob->header.h;
		int left = c_x - width / 2;
		int top = c_y - height / 2;

		if (auto mappedknob = patch.find_mapped_knob(this_module_id, el.id)) {
			opts += "[";
			opts += PanelDef::KnobNames[mappedknob->panel_knob_id];
			opts += "] ";
			opts += el.short_name;
			opts += "\n";
			lv_obj_t *obj = lv_img_create(base);
			lv_img_set_src(obj, knob);
			lv_obj_set_pos(obj, left, top);
			lv_img_set_pivot(obj, width / 2, height / 2);
			lv_obj_add_style(obj, &Gui::mapped_knob_style, LV_PART_MAIN);
			mapped_knobs.push_back({
				.obj = obj,
				.mapped_knob = *mappedknob,
			});
			// Circle around mapped knobs
			lv_canvas_draw_arc(canvas, c_x, c_y, width * 0.8f, 0, 3600, &Gui::mapped_knob_arcdsc);
		} else {
			opts += el.short_name;
			opts += "\n";
			img_dsc.pivot.x = width / 2;
			img_dsc.pivot.y = height / 2;
			//TODO: make patch.find_static_knob()
			auto static_knob = std::find_if(patch.static_knobs.begin(), patch.static_knobs.end(), [&](auto &p) {
				return p.module_id == this_module_id && p.param_id == el.id;
			});
			img_dsc.angle = (static_knob != patch.static_knobs.end()) ? static_knob->value * 3000.f - 1500.f : -1500;
			lv_canvas_draw_img(canvas, left, top, knob, &img_dsc);
		}

		add_button(c_x, c_y, knob->header.w * 1.2f);
	}

	// void draw_mapped_knob(MappedKnob &mappedknob) { //width, height, c_x, c_y
	// }

	void draw_outjack(const OutJackDef &el, const PatchData &patch) {
		int c_x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
		int c_y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
		add_button(c_x, c_y);
		lv_canvas_draw_img(canvas, c_x - jack_x.header.w / 2, c_y - jack_x.header.h / 2, &jack_x, &img_dsc);

		Jack jack{.module_id = this_module_id, .jack_id = (uint16_t)el.id};
		if (auto mappedknob = patch.find_mapped_outjack(jack)) {
			lv_canvas_draw_arc(canvas, c_x, c_y, jack_x.header.w * 0.8f, 0, 3600, &Gui::mapped_knob_arcdsc);
			opts += "[";
			opts += PanelDef::OutJackNames[mappedknob->panel_jack_id];
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
		if (auto mappedknob = patch.find_mapped_injack(jack)) {
			lv_canvas_draw_arc(canvas, c_x, c_y, jack_x.header.w * 0.8f, 0, 3600, &Gui::mapped_knob_arcdsc);
			opts += "[";
			opts += PanelDef::InJackNames[mappedknob->panel_jack_id];
			opts += "] ";
		}
		opts += el.short_name;
		opts += "\n";
	}

	void draw_switch(const SwitchDef &el, const PatchData &patch) {
		int x = ModuleInfoBase::mm_to_px<240>(el.x_mm);
		int y = ModuleInfoBase::mm_to_px<240>(el.y_mm);
		add_button(x, y);
		opts += el.short_name;
		opts += "\n";
		const lv_img_dsc_t *sw = DrawHelper::get_switch_img_240(el.switch_type);
		if (sw)
			lv_canvas_draw_img(canvas, x - sw->header.w / 2, y - sw->header.h / 2, sw, &img_dsc);
	}

	void add_button(int x, int y, int size = 20) {
		auto &b = button.emplace_back();
		b = lv_btn_create(base);
		lv_obj_add_style(b, &Gui::invisible_style, LV_PART_MAIN);
		lv_obj_set_pos(b, x - size / 2, y - size / 2);
		lv_obj_set_size(b, size, size);
	}

	void reset_module_page() {
		for (auto &b : button) {
			lv_obj_del(b);
		}
		button.clear();
		for (auto &k : mapped_knobs) {
			lv_obj_del(k.obj);
		}
		mapped_knobs.clear();
		opts.clear();
	}

	bool read_slug() {
		auto module_id = PageList::get_selected_module_id();
		auto patch_id = PageList::get_selected_patch_id();
		const PatchData &patch = patch_list.get_patch(patch_id);
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

	std::string opts;
	uint16_t this_module_id;
	int32_t cur_selected = 0;
	std::string_view slug;

	struct MKnob {
		lv_obj_t *obj;
		const MappedKnob &mapped_knob;
		float last_pot_reading = 0.5f;
	};
	std::vector<MKnob> mapped_knobs;
	std::vector<lv_obj_t *> button;
	lv_obj_t *roller = nullptr;
	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(240, 240)];
	lv_obj_t *canvas = nullptr;
	lv_obj_t *base = nullptr;
	lv_draw_img_dsc_t img_dsc;
};

} // namespace MetaModule
