#pragma once
#include "CoreModules/elements/elements_index.hh"
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/add_map_popup.hh"
#include "gui/pages/choice_popup.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/keyboard_entry.hh"
#include "gui/pages/manual_control_popup.hh"
#include "gui/pages/midi_map_input.hh"
#include "gui/pages/module_view/mapping_pane_list.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "metaparams.hh"
#include "params/expanders.hh"
#include "params/params_state.hh"

namespace MetaModule
{

struct MapKnobUserData {
	uint32_t set_i{};
	std::optional<uint16_t> mappedknob_idx{};
};
struct MapCableUserData {
	uint16_t module_id;
	ElementCount::Indices idx;
};

struct PanelJackMapUserData {
	uint32_t panel_jack_id;
	bool is_input;
	bool is_valid = true;

	PanelJackMapUserData() = default;

	PanelJackMapUserData(uintptr_t raw) {
		is_input = raw & (1 << 31);
		panel_jack_id = raw & ~(1 << 31);

		is_valid = (panel_jack_id > 0);
		panel_jack_id = panel_jack_id - 1;
	}

	operator uintptr_t() {
		return (panel_jack_id + 1) | (is_input << 31);
	}
};

//TODO: Separate this into CableMappingPane, ParamMappingPane

//TODO: remove ui_CableFinishButton button and associated logic
struct ModuleViewMappingPane {
	ModuleViewMappingPane(OpenPatchManager &patches,
						  PatchModQueue &patch_mod_queue,
						  ParamsMidiState &params,
						  MetaParams &metaparams,
						  PageArguments &args,
						  PageList &page_list,
						  NotificationQueue &notify_queue,
						  GuiState &gui_state,
						  PatchPlayLoader &playloader)
		: pane_group(lv_group_create())
		, patch{patches.get_view_patch()}
		, params{params}
		, metaparams{metaparams}
		, args{args}
		, page_list{page_list}
		, notify_queue{notify_queue}
		, gui_state{gui_state}
		, add_map_popup{patch_mod_queue, metaparams}
		, control_popup{patches, patch_mod_queue, playloader}
		, midi_map_popup{params}
		, patch_mod_queue{patch_mod_queue}
		, patches{patches} {

		lv_obj_add_event_cb(ui_ResetButton, reset_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ControlButton, scroll_to_top, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_CableAddButton, add_cable_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CableRemoveButton, disconnect_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CablePanelAddButton, add_panel_cable_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CableMidiAddButton, add_midi_cable_button_cb, LV_EVENT_CLICKED, this);

		lv_obj_set_style_pad_hor(ui_MapList, 3, LV_PART_MAIN);
		lv_obj_set_style_pad_ver(ui_MapList, 3, LV_PART_MAIN);

		lv_hide(ui_ResetButton);
	}

	void prepare_focus(lv_group_t *group, uint32_t width, bool patch_playing) {
		base_group = group;

		is_patch_playing = patch_playing;
		lv_obj_set_width(ui_MappingParameters, width);
		lv_hide(ui_ControlAlert);

		add_cable_popup.init(ui_MappingMenu, pane_group);
		panel_cable_popup.init(ui_MappingMenu, pane_group);
		midi_map_popup.init(ui_MappingMenu, pane_group);
		keyboard_entry.prepare_focus(ui_MappingMenu, pane_group);

		lv_obj_set_y(ui_Keyboard, 144);
	}

	void show(const DrawnElement &drawn_el) {
		patch = patches.get_view_patch();
		add_map_popup.hide();

		lv_group_remove_all_objs(pane_group);
		lv_group_set_editing(pane_group, false);

		if (patch->patch_name.length() == 0) {
			pr_warn("Patch name empty\n");
			return;
		}

		auto module_id = args.module_id;
		if (!module_id.has_value() || *module_id >= patch->module_slugs.size()) {
			pr_warn("Module has missing or invalid ID\n");
			return;
		}
		this_module_id = module_id.value();

		args.element_counts = drawn_el.gui_element.count;
		args.element_indices = drawn_el.gui_element.idx;
		args.detail_mode = true;

		auto slug = patch->module_slugs[this_module_id];
		auto display_name = ModuleFactory::getModuleDisplayName(slug);

		// Knob name label
		lv_label_set_text(ui_Module_Name, display_name.data());
		auto nm = base_element(drawn_el.element).short_name;
		if (nm.size() == 0)
			nm = "(no name)";
		lv_label_set_text(ui_Element_Name, nm.data());

		drawn_element = &drawn_el;

		displayed_knobsets = 0;
		displayed_cable_endpts = 0;
		std::visit([this](auto &el) { prepare_for_element(el); }, drawn_el.element);

		lv_show(ui_MappingParameters);

		lv_indev_set_group(lv_indev_get_next(nullptr), pane_group);

		add_map_popup.prepare_focus(pane_group, ui_MappingParameters);
		control_popup.prepare_focus(pane_group);
		lv_obj_set_parent(ui_ControlAlert, ui_MappingParameters);

		lv_group_set_wrap(pane_group, false);

		should_close = false;

		is_visible = true;

		lv_obj_scroll_to_y(ui_MappingParameters, 0, LV_ANIM_OFF);
	}

	void show_control_popup(lv_group_t *parent_group, lv_obj_t *parent, const DrawnElement &drawn_el) {
		if (!control_popup.is_visible()) {
			lv_obj_set_parent(ui_ControlAlert, parent);
			control_popup.prepare_focus(parent_group);
			lv_obj_clear_state(ui_ControlButton, LV_STATE_PRESSED);
			control_popup.show(&drawn_el);
		}
	}

	void hide_control_popup() {
		control_popup.hide();
	}

	bool control_popup_visible() {
		return control_popup.is_visible();
	}

	void refresh() {
		if (is_visible && drawn_element) {
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
		is_visible = false;
	}

	void update() {
		add_map_popup.update(params, metaparams);

		if (midi_map_popup.is_visible())
			midi_map_popup.update();

		if (is_patch_playing) {

			if (last_active_knobset != page_list.get_active_knobset()) {
				if (last_active_knobset <= map_list_items.size()) {
					//Remove active mark
					if (auto set_i = last_active_knobset + 1; set_i < map_list_items.size()) {
						if (auto obj = map_list_items[set_i]) {
							lv_obj_set_style_text_color(obj, lv_color_white(), LV_STATE_DEFAULT);
							lv_obj_set_style_text_color(obj, lv_color_white(), LV_STATE_FOCUSED);
						}
					}
				}
				if (page_list.get_active_knobset() <= map_list_items.size()) {
					//Add active mark
					if (auto set_i = page_list.get_active_knobset() + 1; set_i < map_list_items.size()) {
						if (auto obj = map_list_items[set_i]) {
							lv_obj_set_style_text_color(obj, lv_color_hex(0xFDB818), LV_STATE_DEFAULT);
							lv_obj_set_style_text_color(obj, lv_color_hex(0xFDB818), LV_STATE_FOCUSED);
						}
					}
				}
				last_active_knobset = page_list.get_active_knobset();
			}
		}
	}

	bool is_creating_map() const {
		return add_map_popup.visible;
	}

	bool wants_to_close() {
		return should_close;
	}

	void back_event() {
		if (add_map_popup.visible)
			add_map_popup.hide();

		else if (control_popup.visible)
			control_popup.hide();

		else if (add_cable_popup.is_visible())
			add_cable_popup.hide();

		else if (panel_cable_popup.is_visible())
			panel_cable_popup.hide();

		else if (midi_map_popup.is_visible()) {
			midi_map_popup.back();
			if (midi_map_popup.should_close())
				midi_map_popup.hide();
		}

		else if (keyboard_entry.is_visible())
			keyboard_entry.back();

		else
			should_close = true;
	}

private:
	void remove_all_items() {
		for (auto &obj : map_list_items) {
			lv_obj_del_async(obj);
		}
		map_list_items.clear();
	}

	void prepare_for_element(const BaseElement &) {
		lv_hide(ui_CableAddButton);
		lv_hide(ui_ControlButton);
		lv_hide(ui_ResetButton);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);
		lv_hide(ui_CableMidiAddButton);
		lv_hide(ui_MappedPanel);
	}

	//
	// Jacks
	//

	void prepare_for_element(JackInput const &el) {
		this_jack = {.module_id = (uint16_t)this_module_id, .jack_id = drawn_element->gui_element.idx.input_idx};
		this_jack_type = ElementType::Input;
		prepare_for_jack();
	}

	void prepare_for_element(JackOutput const &el) {
		this_jack = {.module_id = (uint16_t)this_module_id, .jack_id = drawn_element->gui_element.idx.output_idx};
		this_jack_type = ElementType::Output;
		prepare_for_jack();
	}

	void prepare_for_jack() {
		bool has_connections = false;

		lv_show(ui_CablePanelAddButton);
		lv_show(ui_CableMidiAddButton, this_jack_type == ElementType::Input);

		if (auto *cable = find_internal_cable(this_jack_type, this_jack)) {
			has_connections = true;
			list_cable_nodes(cable);

		} else if (auto panel_jack_id = drawn_element->gui_element.mapped_panel_id) {
			has_connections = true;

			if (this_jack_type == ElementType::Input)
				list_panel_in_cable(this_jack);
			else if (auto panel_jack = patch->find_mapped_outjack(*panel_jack_id)) {
				list_panel_out_cable(panel_jack);
			}
		}

		this_jack_has_connections = has_connections;
		prepare_jack_gui();
	}

	const InternalCable *find_internal_cable(ElementType dir, Jack jack) {
		if (dir == ElementType::Output)
			return patch->find_internal_cable_with_outjack(jack);
		else
			return patch->find_internal_cable_with_injack(jack);
	}

	void list_cable_nodes(InternalCable const *cable) {
		lv_hide(ui_CableMidiAddButton);

		// Each cable has an output:
		if (!(cable->out == this_jack && this_jack_type == ElementType::Output)) {
			auto obj = list.create_cable_item(cable->out, ElementType::Output, *patch, ui_MapList);
			make_selectable_outjack_item(obj, cable->out);
		}

		// Output might be connected to the panel
		if (auto panel_jack = patch->find_mapped_outjack(cable->out)) {
			list_panel_out_cable(panel_jack);
		}

		// Each cable has 1 or more inputs:
		for (auto &injack : cable->ins) {
			//draw it if NOT (it's this jack and this jack is an input)
			if (!(injack == this_jack && this_jack_type == ElementType::Input)) {
				auto obj = list.create_cable_item(injack, ElementType::Input, *patch, ui_MapList);
				make_selectable_injack_item(obj, injack);
			}
		}
	}

	void list_panel_in_cable(Jack injack) {
		if (auto panel_jack = patch->find_mapped_injack(injack)) {
			lv_hide(ui_CablePanelAddButton);
			lv_hide(ui_CableMidiAddButton);

			auto obj = list.create_panel_in_item(panel_jack->panel_jack_id, ui_MapList, panel_jack->alias_name);
			make_selectable_panel_jack_item(obj, panel_jack);

			for (auto &mappedin : panel_jack->ins) {
				if (mappedin != injack) {
					auto obj = list.create_cable_item(mappedin, ElementType::Input, *patch, ui_MapList);
					make_selectable_injack_item(obj, mappedin);
				}
			}
		}
	}

	void list_panel_out_cable(const MappedOutputJack *panel_jack) {
		lv_hide(ui_CablePanelAddButton);
		lv_hide(ui_CableMidiAddButton);

		auto obj = list.create_panel_out_item(panel_jack->panel_jack_id, ui_MapList, panel_jack->alias_name);
		make_selectable_panel_jack_item(obj, panel_jack);
	}

	void prepare_jack_gui() {
		lv_hide(ui_ControlButton);
		lv_hide(ui_ResetButton);
		lv_hide(ui_ControlAlert);
		lv_hide(ui_AddMapPopUp);

		if (this_jack_has_connections) {
			lv_show(ui_MappedPanel);
			lv_show(ui_CableRemoveButton);
			lv_hide(ui_MappedItemHeader);
			lv_label_set_text(ui_MappedListTitle, "Connected To:");
			lv_label_set_text(ui_CableAddLabel, "New cable");

		} else {
			lv_hide(ui_MappedPanel);
			lv_hide(ui_CableRemoveButton);
			lv_label_set_text(ui_CableAddLabel, "New cable");
		}
		lv_show(ui_CableAddButton);
		lv_group_add_obj(pane_group, ui_CableAddButton);
		lv_group_add_obj(pane_group, ui_CablePanelAddButton);
		lv_group_add_obj(pane_group, ui_CableMidiAddButton);
		lv_group_add_obj(pane_group, ui_CableRemoveButton);
		lv_group_focus_obj(ui_CableAddButton);
	}

	void make_selectable_panel_jack_item(lv_obj_t *obj, const MappedOutputJack *panel_jack) {
		map_list_items.push_back(obj);

		lv_group_add_obj(pane_group, obj);

		lv_obj_add_event_cb(obj, click_panelmap_item_cb, LV_EVENT_CLICKED, this);

		PanelJackMapUserData val;
		val.is_input = false;
		val.panel_jack_id = panel_jack->panel_jack_id;
		lv_obj_set_user_data(obj, reinterpret_cast<void *>((uintptr_t)val));
	}

	void make_selectable_panel_jack_item(lv_obj_t *obj, const MappedInputJack *panel_jack) {
		map_list_items.push_back(obj);

		lv_group_add_obj(pane_group, obj);

		lv_obj_add_event_cb(obj, click_panelmap_item_cb, LV_EVENT_CLICKED, this);

		PanelJackMapUserData val;
		val.is_input = true;
		val.panel_jack_id = panel_jack->panel_jack_id;
		lv_obj_set_user_data(obj, reinterpret_cast<void *>((uintptr_t)val));
	}

	void make_selectable_outjack_item(lv_obj_t *obj, Jack dest) {
		auto idx = ElementIndex::set_index(JackOutput{}, dest.jack_id);
		make_selectable_jack_item(obj, dest.module_id, idx);
	}

	void make_selectable_injack_item(lv_obj_t *obj, Jack dest) {
		auto idx = ElementIndex::set_index(JackInput{}, dest.jack_id);
		make_selectable_jack_item(obj, dest.module_id, idx);
	}

	void make_selectable_jack_item(lv_obj_t *obj, uint16_t module_id, ElementCount::Indices idx) {
		map_list_items.push_back(obj);
		lv_group_add_obj(pane_group, obj);
		// lv_group_focus_obj(obj);
		lv_obj_add_event_cb(obj, follow_cable_button_cb, LV_EVENT_CLICKED, this);
		if (displayed_cable_endpts < mapped_cable_user_data.size()) {
			mapped_cable_user_data[displayed_cable_endpts] = {module_id, idx};
			lv_obj_set_user_data(obj, &(mapped_cable_user_data[displayed_cable_endpts]));
			displayed_cable_endpts++;
		} else {
			pr_err("Cannot display more than %d cables\n", mapped_item_user_data.size());
			lv_obj_set_user_data(obj, nullptr);
		}
	}

	void start_new_cable() {
		auto name = get_full_element_name(this_jack.module_id, this_jack.jack_id, this_jack_type, *patch);

		gui_state.new_cable = {.jack = this_jack, .type = this_jack_type, .has_connections = this_jack_has_connections};

		notify_queue.put(
			{"Choose a jack to connect to " + std::string(name.module_name) + " " + std::string(name.element_name),
			 Notification::Priority::Status,
			 4000});

		page_list.request_new_page(PageId::PatchView, args);
	}

	static void add_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (page->gui_state.already_displayed_cable_instructions) {
			page->start_new_cable();
		} else {
			page->add_cable_popup.show(
				[page](unsigned choice) {
					if (choice == 0) //Cancel
						return;
					page->start_new_cable();
				},
				"Navigate to the module and jack you want to patch to.",
				"Start");
		}
	}

	static void add_panel_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		std::string choices;
		std::optional<unsigned> first_unpatched_jack{};

		if (page->this_jack_type == ElementType::Input && !page->this_jack_has_connections) {
			unsigned num_jacks = PanelDef::NumUserFacingInJacks;
			num_jacks += Expanders::get_connected().ext_audio_connected ? AudioExpander::NumInJacks : 0;
			for (auto i = 0u; i < num_jacks; i++) {
				choices += get_panel_name(JackInput{}, i);
				if (page->patch->find_mapped_injack(i))
					choices += " (patched)";
				else if (!first_unpatched_jack.has_value())
					first_unpatched_jack = i;

				choices += "\n";
			}
		} else {
			unsigned num_jacks = PanelDef::NumUserFacingOutJacks;
			num_jacks += Expanders::get_connected().ext_audio_connected ? AudioExpander::NumOutJacks : 0;
			for (auto i = 0u; i < num_jacks; i++) {
				choices += get_panel_name(JackOutput{}, i);
				if (page->patch->find_mapped_outjack(i))
					choices += " (patched)";
				else if (!first_unpatched_jack.has_value())
					first_unpatched_jack = i;
				choices += "\n";
			}
		}
		choices.pop_back(); //remove trailing \n

		auto action = [page](unsigned choice) {
			if (choice == 0)
				return;

			AddJackMapping jackmapping{};
			jackmapping.panel_jack_id = (uint16_t)(choice - 1);

			if (page->this_jack_type == ElementType::Input) {
				if (auto *cable = page->patch->find_internal_cable_with_injack(page->this_jack)) {
					// Input jack that's connected to an output -> Panel Out jack
					jackmapping.jack = cable->out;
					jackmapping.type = ElementType::Output;
				} else {
					// Input jack that's not connected any output -> Panel In jack
					jackmapping.jack = page->this_jack;
					jackmapping.type = ElementType::Input;
				}
			} else {
				jackmapping.jack = page->this_jack;
				jackmapping.type = ElementType::Output;
			}

			page->patch_mod_queue.put(jackmapping);
			page->notify_queue.put({"Connected to panel"});
			page->gui_state.new_cable = std::nullopt;
			page->should_close = true;
		};

		page->panel_cable_popup.show(action,
									 "Which panel jack do you want to connect to?",
									 "Connect",
									 choices.c_str(),
									 first_unpatched_jack.value_or(0));
	}

	static void add_midi_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		auto name = get_full_element_name(
			page->this_jack.module_id, page->this_jack.jack_id, page->this_jack_type, *page->patch);
		std::string title = "Map MIDI to: " + std::string(name.element_name);
		page->midi_map_popup.set_header_text(title);

		page->midi_map_popup.show([page](std::optional<MidiMappings> choice) {
			if (choice.has_value()) {
				page->notify_queue.put({"Connected to MIDI signal"});

				AddJackMapping mapping{};
				mapping.panel_jack_id = choice.value();
				mapping.jack = page->this_jack;
				mapping.type = page->this_jack_type;

				page->patch_mod_queue.put(mapping);
				page->gui_state.new_cable = std::nullopt;
				page->should_close = true;

			} else
				pr_dbg("Cancel making MIDI signal\n");
		});
	}

	static void disconnect_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		DisconnectJack disconnect{.jack = page->this_jack, .type = page->this_jack_type};
		page->patch_mod_queue.put(disconnect);
		page->notify_queue.put({"Disconnected jack"});
		page->gui_state.new_cable = std::nullopt;
	}

	static void follow_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (!event->target)
			return;

		if (auto objdata = lv_obj_get_user_data(event->target)) {
			auto endpoint = *static_cast<MapCableUserData *>(objdata);
			page->page_list.request_new_page(PageId::ModuleView,
											 {.patch_loc_hash = page->args.patch_loc_hash,
											  .module_id = endpoint.module_id,
											  .element_indices = endpoint.idx,
											  .detail_mode = true});
		}
	}

	//
	// Params
	//

	void prepare_for_element(const ParamElement &) {
		lv_hide(ui_CableAddButton);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);
		lv_hide(ui_CableMidiAddButton);

		lv_show(ui_MappedPanel);
		lv_show(ui_MappedItemHeader);

		// Do not use Reset Button for individual params until we implement calling
		// paramQuantity->reset() and/or paramWidget->onReset()
		lv_hide(ui_ResetButton);

		lv_show(ui_ControlButton, is_patch_playing);
		lv_label_set_text(ui_ControlButtonLabel, "Adjust");
		lv_label_set_text(ui_MappedListTitle, "Mappings:");

		if (is_patch_playing) {
			lv_group_add_obj(pane_group, ui_ControlButton);
		}

		// Show MIDI set first (always show, even if set is empty)
		if (!show_knobset(patch->midi_maps, PatchData::MIDIKnobSet))
			show_unmapped_knobset(PatchData::MIDIKnobSet, patch->valid_knob_set_name(PatchData::MIDIKnobSet));

		// Show all non-empty knobsets
		for (uint32_t set_i = 0; set_i < patch->knob_sets.size(); set_i++) {
			auto &set = patch->knob_sets[set_i];

			// Show non-empty knobset if it has a mapping
			// If it's not mapped, only show it if the knobset is not empty
			if (!show_knobset(set, set_i))
				show_unmapped_knobset(set_i, patch->valid_knob_set_name(set_i));
		}

		if (patch->knob_sets.size() < 8) {
			show_unmapped_knobset(patch->knob_sets.size(), "(new knobset)");
		}

		if (is_patch_playing) {
			lv_group_add_obj(pane_group, ui_ResetButton);
			lv_group_focus_obj(ui_ControlButton);
		}
	}

	bool show_knobset(MappedKnobSet const &set, unsigned set_i) {
		bool added_list_item = false;
		auto setname = patch->valid_knob_set_name(set_i);

		for (auto &map : set.set) {
			if (map.module_id > 0 && map.module_id < patch->module_slugs.size()) {
				if (map.param_id == drawn_element->gui_element.idx.param_idx && map.module_id == this_module_id) {
					bool is_active = is_patch_playing && set_i == page_list.get_active_knobset();
					auto obj = list.create_param_map_list_item(map, setname, ui_MapList, is_active);
					make_selectable_knobset_item(obj, set_i, map.panel_knob_id);
					lv_obj_add_event_cb(obj, edit_map_button_cb, LV_EVENT_CLICKED, this);
					added_list_item = true;
				}
			}
		}
		return added_list_item;
	}

	void show_unmapped_knobset(unsigned set_i, const char *setname) {
		bool is_active = is_patch_playing && set_i == page_list.get_active_knobset();
		auto obj = list.create_unmapped_list_item(setname, ui_MapList, is_active);
		make_selectable_knobset_item(obj, set_i, std::nullopt);
		lv_obj_add_event_cb(obj, add_map_button_cb, LV_EVENT_CLICKED, this);
	}

	void make_selectable_knobset_item(lv_obj_t *obj, uint32_t set_i, std::optional<uint16_t> mapped_panel_id) {
		map_list_items.push_back(obj);
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
		if (displayed_knobsets < mapped_item_user_data.size()) {
			mapped_item_user_data[displayed_knobsets].set_i = set_i;
			if (auto mapped_knob =
					patch->find_mapped_knob_idx(set_i, this_module_id, drawn_element->gui_element.idx.param_idx))

				mapped_item_user_data[displayed_knobsets].mappedknob_idx = mapped_knob.value();
			else
				mapped_item_user_data[displayed_knobsets].mappedknob_idx = std::nullopt;

			lv_obj_set_user_data(obj, &(mapped_item_user_data[displayed_knobsets]));

			displayed_knobsets++;
		} else {
			pr_err("Cannot display more than %d knobsets\n", mapped_item_user_data.size());
			lv_obj_set_user_data(obj, nullptr);
		}
	}

	//
	// AltParams
	//
	void prepare_for_element(const AltParamElement &) {
		lv_hide(ui_CableAddButton);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);
		lv_hide(ui_CableMidiAddButton);
		lv_hide(ui_ResetButton);

		lv_hide(ui_MappedPanel);
		lv_hide(ui_MappedItemHeader);

		lv_show(ui_ControlButton, is_patch_playing);
		lv_label_set_text(ui_ControlButtonLabel, "Adjust");

		if (is_patch_playing) {
			lv_group_add_obj(pane_group, ui_ControlButton);
			lv_group_focus_obj(ui_ControlButton);
		}
	}

	//
	// LightElement
	//
	void prepare_for_element(const LightElement &) {
		lv_hide(ui_CableAddButton);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);
		lv_hide(ui_CableMidiAddButton);

		lv_hide(ui_MappedPanel);
		lv_hide(ui_MappedItemHeader);

		lv_hide(ui_ControlButton);
	}

	static void edit_map_button_cb(lv_event_t *event) {
		if (!event || !event->user_data || !event->target)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (!event->target)
			return;

		if (auto objdata = lv_obj_get_user_data(event->target)) {

			auto data = *static_cast<MapKnobUserData *>(objdata);
			if (!data.mappedknob_idx.has_value())
				return;

			page->page_list.update_state(PageId::ModuleView, page->args);
			page->page_list.request_new_page(PageId::KnobMap,
											 {.patch_loc_hash = page->args.patch_loc_hash,
											  .mappedknob_id = data.mappedknob_idx,
											  .view_knobset_id = data.set_i});
		}
	}

	static void add_map_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		uint32_t knobset_id = 0;
		auto obj = event->target;
		if (auto knobset_ptr = lv_obj_get_user_data(obj)) {
			knobset_id = *static_cast<uint32_t *>(knobset_ptr);
		} else {
			pr_err("Knob set id not set\n");
			return;
		}

		// Clear all CC events
		if (knobset_id == PatchData::MIDIKnobSet) {
			for (auto &cc : page->params.midi_ccs)
				cc.changed = false;
		}

		auto module_id = page->drawn_element->gui_element.module_idx;
		auto param_id = page->drawn_element->gui_element.idx.param_idx;
		page->metaparams.ext_buttons_high_events = 0;
		page->metaparams.ext_buttons_low_events = 0;
		page->add_map_popup.show(knobset_id, param_id, module_id, page->patch);
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

	static void reset_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (auto def_val = get_normalized_default_value(page->drawn_element->element); def_val.has_value()) {
			StaticParam sp{
				.module_id = page->drawn_element->gui_element.module_idx,
				.param_id = page->drawn_element->gui_element.idx.param_idx,
				.value = def_val.value(),
			};
			page->patch->set_or_add_static_knob_value(sp.module_id, sp.param_id, sp.value);
			page->patch_mod_queue.put(SetStaticParam{.param = sp});
		}
	}

	static void click_panelmap_item_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);
		if (!lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN))
			return;

		auto userdata = lv_obj_get_user_data(event->target);
		if (!userdata)
			return;

		auto panelmap = PanelJackMapUserData(reinterpret_cast<uintptr_t>(userdata));
		if (!panelmap.is_valid)
			return;

		page->show_jack_alias_keyboard(panelmap, event->target);
	}

	void show_jack_alias_keyboard(PanelJackMapUserData panelmap, lv_obj_t *obj) {
		auto alias_text_obj = ui_comp_get_child(obj, UI_COMP_MAPPEDKNOBSETITEM_KNOBSETNAMETEXT);

		keyboard_entry.show_keyboard(alias_text_obj, [panelmap = panelmap, this](std::string_view text) {
			if (panelmap.is_input)
				patch->set_panel_in_alias(panelmap.panel_jack_id, text);
			else
				patch->set_panel_out_alias(panelmap.panel_jack_id, text);
			patches.mark_view_patch_modified();
		});
	}

	static inline std::array<MapKnobUserData, MaxKnobSets + 1> mapped_item_user_data{};
	static inline std::array<MapCableUserData, 12> mapped_cable_user_data{};
	static inline FixedVector<PanelJackMapUserData, 16> mapped_paneljack_user_data{};
	uint32_t last_active_knobset = 0;

	lv_group_t *base_group = nullptr;
	lv_group_t *pane_group = nullptr;

	const DrawnElement *drawn_element = nullptr;
	bool is_patch_playing = false;
	bool should_close = false;
	PatchData *patch;
	ParamsMidiState &params;
	MetaParams &metaparams;

	PageArguments &args;
	PageList &page_list;
	NotificationQueue &notify_queue;
	GuiState &gui_state;

	unsigned this_module_id = 0;
	unsigned displayed_knobsets = 0;
	unsigned displayed_cable_endpts = 0;

	MappingPaneList list;
	AddMapPopUp add_map_popup;
	ManualControlPopUp control_popup;

	std::vector<lv_obj_t *> map_list_items;

	Jack this_jack{};
	ElementType this_jack_type{};
	bool this_jack_has_connections = false;

	ConfirmPopup add_cable_popup;
	ChoicePopup panel_cable_popup;
	MidiMapPopup midi_map_popup;
	PatchModQueue &patch_mod_queue;

	OpenPatchManager &patches;

	bool is_visible = false;

	KeyboardEntry keyboard_entry;
};

} // namespace MetaModule
