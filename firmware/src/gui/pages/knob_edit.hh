#pragma once
#include "CoreModules/elements/element_info.hh"
// #include "gui/images/image_list.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/styles.hh"
#include <string>

LV_IMG_DECLARE(knob_large_x);

namespace MetaModule
{
struct KnobEditPage : PageBase {

	KnobEditPage(PatchInfo info, lv_obj_t *parent = nullptr)
		: PageBase{info}
		, base{lv_obj_create(parent)} {

		if (parent == nullptr) {
			PageList::register_page(this, PageId::KnobEdit);
			init_bg(base);
		} else {
			lv_obj_set_size(base, lv_pct(100), lv_pct(100));
			lv_obj_set_style_bg_color(base, lv_color_black(), LV_STATE_DEFAULT);
			lv_obj_set_style_pad_all(base, 4, LV_STATE_DEFAULT);
			lv_obj_add_style(base, &Gui::plain_border_style, LV_PART_MAIN);
		}

		lv_group_set_editing(group, true);

		lv_obj_set_flex_flow(base, LV_FLEX_FLOW_ROW_WRAP);
		lv_obj_set_flex_align(base, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
		lv_obj_set_style_pad_gap(base, 4, LV_STATE_DEFAULT);
		lv_obj_add_flag(base, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_scroll_dir(base, LV_DIR_VER);
		lv_obj_set_scrollbar_mode(base, LV_SCROLLBAR_MODE_ACTIVE);

		knob_name = lv_label_create(base);
		lv_obj_add_style(knob_name, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_width(knob_name, 320);
		lv_obj_set_height(knob_name, 28);

		mapped_info = lv_label_create(base);
		lv_obj_add_style(mapped_info, &Gui::text_block_style, LV_PART_MAIN);
		lv_obj_set_width(mapped_info, 320);
		lv_obj_set_height(mapped_info, 20);

		manual_knob = lv_arc_create(base);
		lv_group_add_obj(group, manual_knob);
		lv_obj_set_size(manual_knob, 50, 50);
		lv_obj_set_style_pad_all(manual_knob, 5, LV_PART_MAIN);
		lv_arc_set_rotation(manual_knob, 135);
		lv_arc_set_bg_angles(manual_knob, 0, 270);
		lv_obj_add_flag(manual_knob, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(manual_knob, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_center(manual_knob);

		map_button = lv_btn_create(base);
		lv_obj_set_size(map_button, 80, 21);
		lv_obj_set_style_pad_all(map_button, 5, LV_PART_MAIN);
		lv_obj_add_flag(map_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

		map_button_label = lv_label_create(map_button);
		lv_obj_add_style(map_button_label, &Gui::button_label_style, LV_PART_MAIN);
		lv_label_set_text(map_button_label, "");
		lv_obj_set_align(map_button_label, LV_ALIGN_CENTER);
		lv_group_add_obj(group, map_button);
	}

	void set_group(lv_group_t *group) {
		lv_group_add_obj(group, manual_knob);
	}

	void prepare_focus() override {
		// Get relevant data: module, patch, param info:
		lv_group_set_editing(group, true);

		this_module_id = PageList::get_selected_module_id();
		auto &patch = patch_storage.get_view_patch();
		// auto patch_id = PageList::get_selected_patch_id();
		// auto &patch = patch_list.get_patch(patch_id);

		if (patch.patch_name.length() == 0) {
			msg_queue.append_message("Patch name empty\n");
			return;
		}
		if (this_module_id >= patch.module_slugs.size()) {
			msg_queue.append_message("Module has invalid ID\n");
			return;
		}
		slug = patch.module_slugs[this_module_id];

		if (!slug.length()) {
			msg_queue.append_message("Module has invalid slug\n");
			return;
		}

		auto moduleinfo = ModuleFactory::getModuleInfo(slug);
		if (moduleinfo.width_hp == 0) {
			msg_queue.append_message("Knob Edit page got empty module slug.\n");
			return;
		}

		this_param_id = PageList::get_selected_control().id;

		printf_("Knob Edit: param id %d module id %d\n", this_param_id, this_module_id);

		// Knob name label
		std::string nm;
		nm.reserve(40);
		nm.append(slug.c_str());
		nm.append(" knob: ");
		// nm.append(moduleinfo.Knobs[this_param_id].long_name);
		lv_label_set_text(knob_name, nm.c_str());

		nm.clear();

		lv_obj_add_flag(manual_knob, LV_OBJ_FLAG_HIDDEN);

		// Mapped/unmapped label
		auto mappedknob = patch.find_mapped_knob(0, PageList::get_selected_module_id(), this_param_id);
		if (mappedknob && mappedknob->panel_knob_id < PanelDef::NumKnobs) {
			nm.append("Mapped to Knob ");
			nm.append(PanelDef::KnobNames[mappedknob->panel_knob_id]);
			//nm.append(" in Set __");

			// Edit Map button
			lv_label_set_text(map_button_label, "Edit Map");
			lv_obj_remove_event_cb(map_button, add_mapbut_cb);
			lv_obj_add_event_cb(map_button, edit_mapbut_cb, LV_EVENT_PRESSED, this);
		} else {
			nm.append("Not mapped");

			// Add Map button
			lv_label_set_text(map_button_label, "Add Map");
			lv_obj_remove_event_cb(map_button, edit_mapbut_cb);
			lv_obj_add_event_cb(map_button, add_mapbut_cb, LV_EVENT_PRESSED, this);

			// Manual knob
			// if (is_this_patch_loaded()) {
			auto static_knob = patch.get_static_knob_value(this_module_id, this_param_id);
			if (static_knob) {
				lv_obj_clear_flag(manual_knob, LV_OBJ_FLAG_HIDDEN);
				lv_arc_set_value(manual_knob, static_knob.value() * 100);
				lv_obj_add_event_cb(manual_knob, manual_knob_adjust, LV_EVENT_VALUE_CHANGED, this);
				printf_("Knob value set to %d\n", (int)(static_knob.value() * 100));
			} else {
				printf_("Error: static param %d in module %d not found\n", this_param_id, this_module_id);
			}
			// }

			//add mapping button
		}
		lv_label_set_text(mapped_info, nm.c_str());
	}

	void update() override {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (PageList::request_last_page()) {
				blur();
			}
		}
	}

	bool is_this_patch_loaded() {
		printf_("Patch loaded: %d, selected patch: %d \n",
				patch_playloader.cur_patch_index(),
				PageList::get_selected_patch_id());
		return patch_playloader.cur_patch_index() == PageList::get_selected_patch_id();
	}

private:
	// void reset_page() {
	// }

	// bool read_slug() {
	// 	return true;
	// }

	static void manual_knob_adjust(lv_event_t *event) {
		auto page = static_cast<KnobEditPage *>(event->user_data);
		lv_obj_t *arc = lv_event_get_target(event);
		StaticParam sp{
			.module_id = page->this_module_id,
			.param_id = page->this_param_id,
			.value = lv_arc_get_value(arc) / 100.f,
		};
		page->patch_mod_queue.put(SetStaticParam{.param = sp});

		auto &patch = page->patch_storage.get_view_patch();
		patch.set_static_knob_value(sp.module_id, sp.param_id, sp.value);
	}

	static void add_mapbut_cb(lv_event_t *event) {
		// auto page = static_cast<KnobEditPage *>(event->user_data);
		printf_("Clicked Add Map\n");
	}

	static void edit_mapbut_cb(lv_event_t *event) {
		// auto page = static_cast<KnobEditPage *>(event->user_data);
		printf_("Clicked Edit Map\n");
	}

	uint16_t this_module_id;
	uint16_t this_param_id;
	ModuleTypeSlug slug;

	lv_obj_t *base = nullptr;
	lv_obj_t *knob_name;
	lv_obj_t *mapped_info;
	lv_obj_t *manual_knob;

	lv_obj_t *map_button;
	lv_obj_t *map_button_label;
};

} // namespace MetaModule
