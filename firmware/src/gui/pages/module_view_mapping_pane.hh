#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/state_names.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/add_map_popup.hh"
#include "gui/pages/base.hh"
#include "gui/pages/manual_control_popup.hh"
#include "gui/pages/module_view_mapping_pane_list.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "params/params_state.hh"

namespace MetaModule
{

struct ModuleViewMappingPane {
	ModuleViewMappingPane(PatchStorageProxy &patch_storage,
						  PatchModQueue &patch_mod_queue,
						  ParamsMidiState &params,
						  PageArguments &args,
						  PageList &page_list)
		: patch{patch_storage.get_view_patch()}
		, params{params}
		, args{args}
		, page_list{page_list}
		, add_map_popup{patch_mod_queue}
		, control_popup{patch, patch_mod_queue} {
	}

	void init() {
		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_RELEASED, this);
		lv_obj_add_event_cb(ui_ControlButton, scroll_to_top, LV_EVENT_FOCUSED, this);
		pane_group = lv_group_create();
	}

	void prepare_focus(lv_group_t *group, uint32_t width, bool patch_playing) {
		base_group = group;

		is_patch_playing = patch_playing;
		lv_obj_set_width(ui_MappingParameters, width);
		lv_hide(ui_ControlAlert);
	}

	void show(const DrawnElement &drawn_el) {
		add_map_popup.hide();

		lv_group_remove_all_objs(pane_group);
		lv_group_set_editing(pane_group, false);

		//remove_all_items();

		if (patch.patch_name.length() == 0) {
			pr_warn("Patch name empty\n");
			return;
		}

		auto module_id = args.module_id;
		if (!module_id.has_value() || *module_id >= patch.module_slugs.size()) {
			pr_warn("Module has missing or invalid ID\n");
			return;
		}
		this_module_id = module_id.value();

		args.element_counts = drawn_el.gui_element.count;
		args.element_indices = drawn_el.gui_element.idx;

		auto slug = patch.module_slugs[this_module_id];

		// Knob name label
		lv_label_set_text(ui_Module_Name, slug.c_str());
		auto nm = base_element(drawn_el.element).short_name;
		if (nm.size() == 0)
			nm = "(no name)";
		lv_label_set_text(ui_Element_Name, nm.data());

		drawn_element = &drawn_el;

		displayed_knobsets = 0;
		std::visit([this](auto &el) { prepare_for_element(el); }, drawn_el.element);

		lv_show(ui_MappingParameters);

		auto indev = lv_indev_get_next(nullptr);
		if (!indev)
			return;

		lv_group_focus_next(pane_group);
		lv_indev_set_group(indev, pane_group);

		add_map_popup.prepare_focus(pane_group);
		control_popup.prepare_focus(pane_group);

		is_shown = true;

		lv_obj_scroll_to_y(ui_MappingParameters, 0, LV_ANIM_OFF);
	}

	void refresh() {
		if (drawn_element) {
			remove_all_items();
			show(*drawn_element);
		}
	}

	void hide() {
		lv_hide(ui_MappingParameters);
		lv_hide(ui_ControlAlert);
		add_map_popup.hide();
		control_popup.hide();

		if (base_group) {
			lv_indev_set_group(lv_indev_get_next(nullptr), base_group);
		}

		remove_all_items();
		is_shown = false;
	}

	void update() {
		add_map_popup.update(params);
	}

	void hide_addmap() {
		add_map_popup.hide();
	}

	bool addmap_visible() {
		return add_map_popup.visible;
	}

	void hide_manual_control() {
		control_popup.hide();
	}

	bool manual_control_visible() {
		return control_popup.visible;
	}

	bool is_visible() {
		return is_shown;
	}

private:
	struct MapItemUserData {
		uint32_t set_i; //NOLINT
		std::optional<uint16_t> mapped_panel_id;
		MapItemUserData()
			: set_i{0}
			, mapped_panel_id{std::nullopt} {
		}
	};

	static inline std::array<MapItemUserData, MaxKnobSets + 1> mapped_item_user_data{};

	void remove_all_items() {
		for (auto &obj : map_list_items) {
			lv_obj_del_async(obj);
		}
		map_list_items.clear();
	}

	void activate_list_item(lv_obj_t *obj, uint32_t set_i, std::optional<uint16_t> mapped_panel_id) {
		map_list_items.push_back(obj);
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
		if (displayed_knobsets < mapped_item_user_data.size()) {
			mapped_item_user_data[displayed_knobsets].set_i = set_i;
			mapped_item_user_data[displayed_knobsets].mapped_panel_id = mapped_panel_id;
			lv_obj_set_user_data(obj, &(mapped_item_user_data[displayed_knobsets]));
			displayed_knobsets++;
		} else {
			pr_err("Cannot display more than %d knobsets\n", mapped_item_user_data.size());
			lv_obj_set_user_data(obj, nullptr);
		}
	}

	void group_edit_cable_button(lv_obj_t *obj) {
		map_list_items.push_back(obj);
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
		lv_obj_add_event_cb(obj, edit_cable_button_cb, LV_EVENT_RELEASED, this);
		// lv_obj_set_user_data(obj, reinterpret_cast<void *>(cable_idx));
	}

	void prepare_for_element(const BaseElement &) {
		lv_hide(ui_ControlButton);
		lv_hide(ui_MappedPanel);
	}

	void prepare_for_jack() {
		lv_hide(ui_ControlButton);
		lv_show(ui_MappedPanel);
		lv_hide(ui_MappedItemHeader);
		lv_label_set_text(ui_MappedListTitle, "Cables:");
	}

	void prepare_for_element(const JackOutput &) {
		prepare_for_jack();

		Jack thisjack = {.module_id = (uint16_t)this_module_id, .jack_id = drawn_element->gui_element.idx.output_idx};

		for (auto &cable : patch.int_cables) {
			if (cable.out == thisjack) {
				for (auto &injack : cable.ins) {
					auto obj = list.create_cable_item(injack, ElementType::Input, patch, ui_MapList);
					group_edit_cable_button(obj);
				}
			}
		}

		auto panel_jack_id = drawn_element->gui_element.mapped_panel_id;
		if (panel_jack_id) {
			auto obj = list.create_panel_outcable_item(panel_jack_id.value(), ui_MapList);
			group_edit_cable_button(obj);
		} else {
			auto obj = list.create_unmapped_list_item("Add cable...", ui_MapList);
			group_edit_cable_button(obj);
		}
	}

	void prepare_for_element(const JackInput &) {
		prepare_for_jack();

		Jack thisjack = {.module_id = (uint16_t)this_module_id, .jack_id = drawn_element->gui_element.idx.input_idx};

		for (auto &cable : patch.int_cables) {
			for (auto &injack : cable.ins) {
				if (injack == thisjack) {
					auto obj = list.create_cable_item(cable.out, ElementType::Output, patch, ui_MapList);
					group_edit_cable_button(obj);
				}
			}
		}

		auto panel_jack_id = drawn_element->gui_element.mapped_panel_id;
		if (panel_jack_id) {
			auto obj = list.create_panel_incable_item(panel_jack_id.value(), ui_MapList);
			group_edit_cable_button(obj);
		} else {
			auto obj = list.create_unmapped_list_item("Add cable...", ui_MapList);
			group_edit_cable_button(obj);
		}
	}

	void prepare_for_element(const ParamElement &) {
		lv_show(ui_MappedPanel);
		lv_show(ui_MappedItemHeader);
		lv_show(ui_ControlButton, is_patch_playing);
		lv_label_set_text(ui_MappedListTitle, "Mappings:");

		if (is_patch_playing) {
			lv_group_add_obj(pane_group, ui_ControlButton);
			lv_group_focus_obj(ui_ControlButton);
		}

		// Show MIDI set first (always show, even if set is empty)
		auto [_, added_list_item] = show_knobset(patch.midi_maps, PatchData::MIDIKnobSet);
		if (!added_list_item)
			show_unmapped_knobset(PatchData::MIDIKnobSet, patch.valid_knob_set_name(PatchData::MIDIKnobSet));

		// Show all non-empty knobsets
		std::optional<unsigned> first_empty_set = std::nullopt;
		for (uint32_t set_i = 0; set_i < patch.knob_sets.size(); set_i++) {
			auto &set = patch.knob_sets[set_i];

			// Show non-empty knobset if it has a mapping
			// If it's not mapped, only show it if the knobset is not empty
			auto [set_is_empty, added_list_item] = show_knobset(set, set_i);
			if (!set_is_empty && !added_list_item)
				show_unmapped_knobset(set_i, patch.valid_knob_set_name(set_i));

			else if (set_is_empty && !first_empty_set.has_value())
				first_empty_set = set_i;
		}

		// Show the first empty knobset (if there is one)
		if (first_empty_set.has_value()) {
			unsigned set_i = first_empty_set.value();
			show_unmapped_knobset(set_i, "(new knobset)");
		}
	}

	struct KnobSetStatus {
		bool set_is_empty;
		bool added_list_item;
	};

	KnobSetStatus show_knobset(MappedKnobSet const &set, unsigned set_i) {
		bool set_is_empty = true;
		bool added_list_item = false;
		auto setname = patch.valid_knob_set_name(set_i);

		for (auto &map : set.set) {
			if (map.module_id > 0 && map.module_id < patch.module_slugs.size()) {
				set_is_empty = false;
				if (map.param_id == drawn_element->gui_element.idx.param_idx && map.module_id == this_module_id) {
					auto obj = list.create_map_list_item(map, setname, ui_MapList);
					activate_list_item(obj, set_i, map.panel_knob_id);
					lv_obj_add_event_cb(obj, edit_button_cb, LV_EVENT_RELEASED, this);
					added_list_item = true;
				}
			}
		}
		return {set_is_empty, added_list_item};
	}

	void show_unmapped_knobset(unsigned set_i, const char *setname) {
		auto obj = list.create_unmapped_list_item(setname, ui_MapList);
		activate_list_item(obj, set_i, std::nullopt);
		lv_obj_add_event_cb(obj, add_button_cb, LV_EVENT_RELEASED, this);
	}

	static void edit_button_cb(lv_event_t *event) {
		if (!event || !event->user_data || !event->target)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		auto obj = event->target;
		auto objdata = lv_obj_get_user_data(obj);
		if (!objdata)
			return;

		auto data = *static_cast<MapItemUserData *>(objdata);
		if (!data.mapped_panel_id.has_value())
			return;

		page->page_list.stash_state(PageId::ModuleView, page->args);
		page->args.mappedknob_id = data.mapped_panel_id;
		page->args.view_knobset_id = data.set_i;
		page->page_list.request_new_page(PageId::KnobMap, page->args);
	}

	static void edit_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (!event->target)
			return;

		page->page_list.stash_state(PageId::ModuleView, page->args);
		page->page_list.request_new_page(PageId::CableEdit, page->args);
		page->hide();
	}

	static void add_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		uint32_t knobset_id = 0; //FIXME
		auto obj = event->target;
		if (auto knobset_ptr = lv_obj_get_user_data(obj)) {
			knobset_id = *static_cast<uint32_t *>(knobset_ptr);
		}

		// Clear all CC events
		if (knobset_id == PatchData::MIDIKnobSet) {
			for (auto &cc : page->params.midi_ccs)
				cc.changed = false;
		}

		auto module_id = page->drawn_element->gui_element.module_idx;
		auto param_id = page->drawn_element->gui_element.idx.param_idx;
		page->add_map_popup.show(knobset_id, param_id, module_id);
	}

	static void scroll_to_top(lv_event_t *event) {
		if (event->target == ui_ControlButton) {
			lv_obj_scroll_to_y(ui_MappingParameters, 0, LV_ANIM_ON);
		}
	}

	static void control_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (event->target == ui_ControlButton) {
			lv_obj_clear_state(ui_ControlButton, LV_STATE_PRESSED);
			page->control_popup.show(page->drawn_element);
		}
	}

	lv_group_t *base_group = nullptr;
	lv_group_t *pane_group = nullptr;

	const DrawnElement *drawn_element;
	bool is_patch_playing = false;
	bool is_shown = false;
	PatchData &patch;
	ParamsMidiState &params;

	PageArguments &args;
	PageList &page_list;

	unsigned this_module_id = 0;
	unsigned displayed_knobsets = 0;

	MappingPaneList list;
	AddMapPopUp add_map_popup;
	ManualControlPopUp control_popup;

	std::vector<lv_obj_t *> map_list_items;
};

} // namespace MetaModule
