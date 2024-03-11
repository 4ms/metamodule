#pragma once
#include "gui/elements/context.hh"
#include "gui/elements/element_name.hh"
#include "gui/elements/state_names.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/add_map_popup.hh"
#include "gui/pages/base.hh"
#include "gui/pages/choice_popup.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/manual_control_popup.hh"
#include "gui/pages/module_view_mapping_pane_list.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "params/params_state.hh"

namespace MetaModule
{

struct MapKnobUserData {
	uint32_t set_i{};
	std::optional<uint16_t> mapped_panel_id{};
};
struct MapCableUserData {
	uint16_t module_id;
	ElementCount::Indices idx;
};

struct ModuleViewMappingPane {
	ModuleViewMappingPane(FileStorageProxy &patch_storage,
						  PatchModQueue &patch_mod_queue,
						  ParamsMidiState &params,
						  PageArguments &args,
						  PageList &page_list,
						  NotificationQueue &notify_queue,
						  GuiState &gui_state)
		: pane_group(lv_group_create())
		, patch{patch_storage.get_view_patch()}
		, params{params}
		, args{args}
		, page_list{page_list}
		, notify_queue{notify_queue}
		, gui_state{gui_state}
		, add_map_popup{patch_mod_queue}
		, control_popup{patch, patch_mod_queue}
		, patch_mod_queue{patch_mod_queue}
		, patch_storage{patch_storage} {

		lv_obj_add_event_cb(ui_ControlButton, control_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ControlButton, scroll_to_top, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_CableCancelButton, cancel_creating_cable_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CableFinishButton, finish_cable_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CableAddButton, add_cable_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CableRemoveButton, disconnect_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_CablePanelAddButton, add_panel_cable_button_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *group, uint32_t width, bool patch_playing) {
		base_group = group;

		is_patch_playing = patch_playing;
		lv_obj_set_width(ui_MappingParameters, width);
		lv_hide(ui_ControlAlert);

		add_cable_popup.init(ui_MappingMenu, pane_group);
		panel_cable_popup.init(ui_MappingMenu, pane_group);
	}

	void show(const DrawnElement &drawn_el) {
		patch = patch_storage.get_view_patch();
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

		auto slug = patch->module_slugs[this_module_id];

		// Knob name label
		lv_label_set_text(ui_Module_Name, slug.c_str());
		auto nm = base_element(drawn_el.element).short_name;
		if (nm.size() == 0)
			nm = "(no name)";
		lv_label_set_text(ui_Element_Name, nm.data());

		drawn_element = &drawn_el;

		displayed_knobsets = 0;
		displayed_cable_endpts = 0;
		std::visit([this](auto &el) { prepare_for_element(el); }, drawn_el.element);

		lv_show(ui_MappingParameters);

		lv_group_focus_next(pane_group);
		lv_indev_set_group(lv_indev_get_next(nullptr), pane_group);

		add_map_popup.prepare_focus(pane_group, ui_MappingParameters);
		control_popup.prepare_focus(pane_group);

		should_close = false;

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
	}

	void update() {
		add_map_popup.update(params);
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

		else
			should_close = true;
	}

private:
	static inline std::array<MapKnobUserData, MaxKnobSets + 1> mapped_item_user_data{};
	static inline std::array<MapCableUserData, 12> mapped_cable_user_data{};

	void remove_all_items() {
		for (auto &obj : map_list_items) {
			lv_obj_del_async(obj);
		}
		map_list_items.clear();
	}

	void prepare_for_element(const BaseElement &) {
		lv_hide(ui_CableAddButton);
		lv_hide(ui_CableCreationPanel);
		lv_hide(ui_ControlButton);
		lv_hide(ui_CableCancelButton);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);
		lv_hide(ui_MappedPanel);
	}

	void make_nonselectable_item(lv_obj_t *obj) {
		map_list_items.push_back(obj);
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
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

		if (auto *cable = find_internal_cable(this_jack_type, this_jack)) {
			has_connections = true;
			list_cable_nodes(cable);

		} else if (auto panel_jack_id = drawn_element->gui_element.mapped_panel_id) {
			has_connections = true;

			if (this_jack_type == ElementType::Input)
				list_panel_in_cable(this_jack);
			else
				list_panel_out_cable(*panel_jack_id);
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
		// Each cable has an output:
		if (!(cable->out == this_jack && this_jack_type == ElementType::Output)) {
			auto obj = list.create_cable_item(cable->out, ElementType::Output, *patch, ui_MapList);
			make_selectable_outjack_item(obj, cable->out);
		}

		// Output might be connected to the panel
		if (auto panel_jack = patch->find_mapped_outjack(cable->out)) {
			list_panel_out_cable(panel_jack->panel_jack_id);
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

			auto obj = list.create_panel_incable_item(panel_jack->panel_jack_id, ui_MapList);
			make_nonselectable_item(obj);

			for (auto &mappedin : panel_jack->ins) {
				if (mappedin != injack) {
					auto obj = list.create_cable_item(mappedin, ElementType::Input, *patch, ui_MapList);
					make_selectable_injack_item(obj, mappedin);
				}
			}
		}
	}

	void list_panel_out_cable(uint16_t panel_jack_id) {
		lv_hide(ui_CablePanelAddButton);

		auto obj = list.create_panel_outcable_item(panel_jack_id, ui_MapList);
		make_nonselectable_item(obj);
	}

	void prepare_jack_gui() {
		lv_hide(ui_ControlButton);
		lv_hide(ui_ControlAlert);
		lv_hide(ui_AddMapPopUp);

		if (this_jack_has_connections) {
			lv_show(ui_MappedPanel);
			lv_show(ui_CableRemoveButton);
			lv_hide(ui_MappedItemHeader);
			lv_label_set_text(ui_MappedListTitle, "Connected To:");
			lv_label_set_text(ui_CableAddLabel, "New connection");

		} else {
			lv_hide(ui_MappedPanel);
			lv_hide(ui_CableRemoveButton);
			lv_label_set_text(ui_CableAddLabel, "New cable");
		}
		lv_show(ui_CableAddButton);
		lv_group_add_obj(pane_group, ui_CableAddButton);
		lv_group_add_obj(pane_group, ui_CablePanelAddButton);
		lv_group_add_obj(pane_group, ui_CableRemoveButton);
		lv_group_focus_next(pane_group);

		handle_cable_creating();
	}

	void handle_cable_creating() {
		if (!gui_state.new_cable) {
			lv_hide(ui_CableCreationPanel);
			return;
		}

		// Hide "New cable/connection" and "Edit Cable" if already have a cable open
		lv_hide(ui_CableAddButton);
		lv_show(ui_CableCreationPanel);

		auto begin_type = gui_state.new_cable->type;
		auto begin_connected = gui_state.new_cable->has_connections;
		auto begin_node_has_output = begin_connected || begin_type == ElementType::Output;
		auto this_node_has_output = this_jack_has_connections || this_jack_type == ElementType::Output;
		bool can_finish_cable = this_node_has_output ^ begin_node_has_output;
		lv_show(ui_CableFinishButton, can_finish_cable);

		lv_group_add_obj(pane_group, ui_CableFinishButton);
		lv_group_add_obj(pane_group, ui_CableCancelButton);

		auto begin_jack = gui_state.new_cable->jack;
		auto jackname = get_full_element_name(begin_jack.module_id, begin_jack.jack_id, begin_type, *patch);
		lv_label_set_text_fmt(ui_CableCreationLabel,
							  "In progress: adding a cable from %s %s",
							  jackname.module_name.data(),
							  jackname.element_name.data());
	}

	void make_selectable_outjack_item(lv_obj_t *obj, Jack dest) {
		auto idx = ElementCount::mark_unused_indices({.output_idx = (uint8_t)dest.jack_id}, {.num_outputs = 1});
		make_selectable_jack_item(obj, dest.module_id, idx);
	}

	void make_selectable_injack_item(lv_obj_t *obj, Jack dest) {
		auto idx = ElementCount::mark_unused_indices({.input_idx = (uint8_t)dest.jack_id}, {.num_inputs = 1});
		make_selectable_jack_item(obj, dest.module_id, idx);
	}

	void make_selectable_jack_item(lv_obj_t *obj, uint16_t module_id, ElementCount::Indices idx) {
		map_list_items.push_back(obj);
		lv_group_add_obj(pane_group, obj);
		lv_group_focus_obj(obj);
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

	static void add_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		page->add_cable_popup.show(
			[page](unsigned choice) {
				if (choice == 0) //Cancel
					return;
				auto name = get_full_element_name(
					page->this_jack.module_id, page->this_jack.jack_id, page->this_jack_type, *page->patch);

				page->gui_state.new_cable = {.jack = page->this_jack,
											 .type = page->this_jack_type,
											 .has_connections = page->this_jack_has_connections};

				page->notify_queue.put({"Choose a jack to connect to " + std::string(name.module_name) + " " +
											std::string(name.element_name),
										Notification::Priority::Status,
										10000});

				page->page_list.request_new_page(PageId::PatchView, page->args);
			},
			"Navigate to the module and jack you want to patch to.",
			"Start");
	}

	static void add_panel_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		std::string choices;
		if (page->this_jack_type == ElementType::Input && !page->this_jack_has_connections) {
			for (auto i = 0u; i < PanelDef::NumUserFacingInJacks; i++) {
				choices += get_panel_name<PanelDef>(JackInput{}, i);
				if (page->patch->find_mapped_injack(i))
					choices += " (patched)";
				choices += "\n";
			}
		} else {
			for (auto i = 0; i < PanelDef::NumUserFacingOutJacks; i++) {
				choices += get_panel_name<PanelDef>(JackOutput{}, i);
				if (page->patch->find_mapped_outjack(i))
					choices += " (patched)";
				choices += "\n";
			}
		}
		choices.pop_back(); //remove trailing \n

		auto action = [page](unsigned choice) {
			if (choice == 0 || choice > 8)
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
		};

		page->panel_cable_popup.show(action, "Which panel jack do you want to connect to?", "Connect", choices.c_str());
	}

	static void finish_cable_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		if (!page->gui_state.new_cable) {
			page->notify_queue.put({"Something went wrong... can't finish a cable here because no cable was started",
									Notification::Priority::Error});
			return;
		}
		auto begin_jack = page->gui_state.new_cable->jack;
		auto begin_jack_type = page->gui_state.new_cable->type;

		bool make_panel_mapping = false;

		// Handle case of starting with a PanelIn->In and finishing on an input
		if (begin_jack_type == ElementType::Input && page->this_jack_type == ElementType::Input) {
			AddJackMapping jackmapping{};
			if (auto panel_jack = page->patch->find_mapped_injack(begin_jack)) {
				jackmapping.jack = page->this_jack;
				jackmapping.panel_jack_id = panel_jack->panel_jack_id;
				make_panel_mapping = true;

			} else if (auto panel_jack = page->patch->find_mapped_injack(page->this_jack)) {
				jackmapping.jack = begin_jack;
				jackmapping.panel_jack_id = panel_jack->panel_jack_id;
				make_panel_mapping = true;
			}

			if (make_panel_mapping) {
				jackmapping.type = ElementType::Input;
				page->patch_mod_queue.put(jackmapping);
				page->notify_queue.put({"Added cable from panel input"});
				page->gui_state.new_cable = std::nullopt;
			}
		}

		if (!make_panel_mapping) {
			AddInternalCable newcable{};
			if (begin_jack_type == ElementType::Input) {
				newcable.in = begin_jack;
				newcable.out = page->this_jack;
			} else {
				newcable.in = page->this_jack;
				newcable.out = begin_jack;
			}

			page->patch_mod_queue.put(newcable);
			page->notify_queue.put({"Added cable"});
			page->gui_state.new_cable = std::nullopt;
		}
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
											 {.module_id = endpoint.module_id, .element_indices = endpoint.idx});
		}
	}

	static void cancel_creating_cable_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewMappingPane *>(event->user_data);

		page->gui_state.new_cable = std::nullopt;
		page->notify_queue.put({"Cancelled making a cable", Notification::Priority::Info, 1000});
		page->should_close = true;
	}

	//
	// Params
	//
	void prepare_for_element(const ParamElement &) {
		lv_hide(ui_CableAddButton);
		lv_hide(ui_CableCreationPanel);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);

		lv_show(ui_MappedPanel);
		lv_show(ui_MappedItemHeader);
		lv_show(ui_ControlButton, is_patch_playing);
		lv_label_set_text(ui_ControlButtonLabel, "Adjust");
		lv_label_set_text(ui_MappedListTitle, "Mappings:");

		if (is_patch_playing) {
			lv_group_add_obj(pane_group, ui_ControlButton);
			lv_group_focus_obj(ui_ControlButton);
		}

		// Show MIDI set first (always show, even if set is empty)
		auto [_, added_list_item] = show_knobset(patch->midi_maps, PatchData::MIDIKnobSet);
		if (!added_list_item)
			show_unmapped_knobset(PatchData::MIDIKnobSet, patch->valid_knob_set_name(PatchData::MIDIKnobSet));

		// Show all non-empty knobsets
		std::optional<unsigned> first_empty_set = std::nullopt;
		for (uint32_t set_i = 0; set_i < patch->knob_sets.size(); set_i++) {
			auto &set = patch->knob_sets[set_i];

			// Show non-empty knobset if it has a mapping
			// If it's not mapped, only show it if the knobset is not empty
			auto [set_is_empty, added_list_item] = show_knobset(set, set_i);
			if (!set_is_empty && !added_list_item)
				show_unmapped_knobset(set_i, patch->valid_knob_set_name(set_i));

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
		auto setname = patch->valid_knob_set_name(set_i);

		for (auto &map : set.set) {
			if (map.module_id > 0 && map.module_id < patch->module_slugs.size()) {
				set_is_empty = false;
				if (map.param_id == drawn_element->gui_element.idx.param_idx && map.module_id == this_module_id) {
					auto obj =
						list.create_map_list_item(map, setname, ui_MapList, set_i == page_list.get_active_knobset());
					make_selectable_knobset_item(obj, set_i, map.panel_knob_id);
					lv_obj_add_event_cb(obj, edit_map_button_cb, LV_EVENT_CLICKED, this);
					added_list_item = true;
				}
			}
		}
		return {set_is_empty, added_list_item};
	}

	void show_unmapped_knobset(unsigned set_i, const char *setname) {
		auto obj = list.create_unmapped_list_item(setname, ui_MapList, set_i == page_list.get_active_knobset());
		make_selectable_knobset_item(obj, set_i, std::nullopt);
		lv_obj_add_event_cb(obj, add_map_button_cb, LV_EVENT_CLICKED, this);
	}

	void make_selectable_knobset_item(lv_obj_t *obj, uint32_t set_i, std::optional<uint16_t> mapped_panel_id) {
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

	//
	// AltParams
	//
	void prepare_for_element(const AltParamElement &) {
		lv_hide(ui_CableAddButton);
		lv_hide(ui_CableCreationPanel);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);

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
		lv_hide(ui_CableCreationPanel);
		lv_hide(ui_CableRemoveButton);
		lv_hide(ui_CablePanelAddButton);

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
			if (!data.mapped_panel_id.has_value())
				return;

			page->page_list.update_state(PageId::ModuleView, page->args);
			page->page_list.request_new_page(PageId::KnobMap,
											 {.mappedknob_id = data.mapped_panel_id, .view_knobset_id = data.set_i});
		}
	}

	static void add_map_button_cb(lv_event_t *event) {
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

	const DrawnElement *drawn_element = nullptr;
	bool is_patch_playing = false;
	bool should_close = false;
	PatchData *patch;
	ParamsMidiState &params;

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
	PatchModQueue &patch_mod_queue;
	FileStorageProxy &patch_storage;
};

} // namespace MetaModule
