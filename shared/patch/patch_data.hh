#pragma once
#include <module_type_slug.hh>
#include "patch.hh"
#include <util/static_string.hh>
#include <algorithm>
#include <optional>
#include <vector>

struct PatchData {
	static constexpr size_t DescSize = 255;
	ModuleTypeSlug patch_name{""};
	StaticString<DescSize> description;
	std::vector<ModuleTypeSlug> module_slugs;
	std::vector<InternalCable> int_cables;
	std::vector<MappedInputJack> mapped_ins;
	std::vector<MappedOutputJack> mapped_outs;
	std::vector<StaticParam> static_knobs;
	std::vector<MappedKnobSet> knob_sets;
	std::vector<ModuleInitState> module_states;
	MappedKnobSet midi_maps;
	uint32_t midi_poly_num = 1;

	static constexpr uint32_t MIDIKnobSet = 0xFFFFFFFF;

	// PatchData() = default;
	// PatchData(PatchData &) = default;
	// PatchData(PatchData &&) = default;
	// PatchData &operator=(const PatchData &) = default;
	// PatchData &operator=(PatchData &&) = default;
	// PatchData(std::string_view patch_name)
	// 	: patch_name{patch_name}
	// 	, module_slugs{"HubMedium"}
	// 	, knob_sets{{{}, "Knob Set 1"}} {
	// }

	void blank_patch(std::string_view patch_name) {
		*this = PatchData{};
		// description = "";
		// module_slugs.clear();
		// int_cables.clear();
		// mapped_ins.clear();
		// mapped_outs.clear();
		// static_knobs.clear();
		// knob_sets.clear();
		// module_states.clear();
		// midi_maps.set.clear();
		// midi_poly_num = 1;

		this->patch_name.copy(patch_name);
		module_slugs.push_back("HubMedium");
		knob_sets.push_back({{}, "Knob Set 1"});
		midi_maps.name = "MIDI";
	}

	const MappedKnob *find_mapped_knob(uint32_t set_id, uint32_t module_id, uint32_t param_id) const {
		if (set_id == MIDIKnobSet)
			return find_midi_map(module_id, param_id);

		if (set_id < knob_sets.size()) {
			for (auto &m : knob_sets[set_id].set) {
				if (m.module_id == module_id && m.param_id == param_id)
					return &m;
			}
		}
		return nullptr;
	}

	const MappedKnob *find_mapped_knob(uint32_t set_id, uint16_t panel_knob_id) const {
		if (set_id == MIDIKnobSet)
			return find_midi_map(panel_knob_id);

		if (set_id < knob_sets.size()) {
			for (auto &m : knob_sets[set_id].set) {
				if (m.panel_knob_id == panel_knob_id)
					return &m;
			}
		}
		return nullptr;
	}

	const MappedKnob *find_midi_map(uint32_t module_id, uint32_t param_id) const {
		for (auto &m : midi_maps.set) {
			if (m.module_id == module_id && m.param_id == param_id)
				return &m;
		}
		return nullptr;
	}

	const MappedKnob *find_midi_map(uint16_t panel_knob_id) const {
		for (auto &m : midi_maps.set) {
			if (m.panel_knob_id == panel_knob_id)
				return &m;
		}
		return nullptr;
	}

	// Adds the knob mapping if and only if it does not exist
	bool add_unique_mapped_knob(uint32_t set_id, MappedKnob const &map) {
		if (!find_mapped_knob(set_id, map.module_id, map.param_id)) {
			knob_sets[set_id].set.push_back(map);
			return true;
		}

		return false;
	}

	// Updates an existing mapped knob, or adds it if it doesn't exist yet
	bool add_update_mapped_knob(uint32_t set_id, MappedKnob const &map) {
		if (set_id >= knob_sets.size())
			return false;

		if (map.module_id >= module_slugs.size())
			return false;

		// if (map.param_id >= PanelDef::NumKnobs)
		// 	return false;

		if (auto *m = _get_mapped_knob(set_id, map.module_id, map.param_id)) {
			*m = map;
		} else {
			knob_sets[set_id].set.push_back(map);
		}

		return true;
	}

	bool add_update_midi_map(MappedKnob const &map) {
		if (!map.is_midi_cc())
			return false;

		if (map.module_id >= module_slugs.size())
			return false;

		if (auto *m = _get_midi_map(map.module_id, map.param_id)) {
			*m = map;
		} else {
			midi_maps.set.push_back(map);
		}

		return true;
	}

	bool remove_mapping(uint32_t set_id, MappedKnob const &map) {
		if (set_id >= knob_sets.size())
			return false;

		if (map.module_id >= module_slugs.size())
			return false;

		auto num_erased = std::erase_if(knob_sets[set_id].set, [&map](auto m) {
			return (m.module_id == map.module_id && m.param_id == map.param_id);
		});

		return num_erased > 0;
	}

	const StaticParam *find_static_knob(uint32_t module_id, uint32_t param_id) const {
		for (auto &m : static_knobs) {
			if (m.module_id == module_id && m.param_id == param_id)
				return &m;
		}
		return nullptr;
	}

	std::optional<float> get_static_knob_value(uint16_t module_id, uint16_t param_id) const {
		for (auto &m : static_knobs) {
			if (m.module_id == module_id && m.param_id == param_id)
				return m.value;
		}
		return std::nullopt;
	}

	void set_static_knob_value(uint32_t module_id, uint32_t param_id, float val) {
		for (auto &m : static_knobs) {
			if (m.module_id == module_id && m.param_id == param_id)
				m.value = val;
		}
	}

	void add_internal_cable(Jack in, Jack out) {
		if (auto existing_cable_out = _find_internal_cable_with_outjack(out))
			existing_cable_out->ins.push_back(in);
		else
			int_cables.push_back({out, {in}});
	}

	void disconnect_injack(Jack jack) {
		// Remove from inputs on all internal cables
		for (auto &cable : int_cables) {
			std::erase_if(cable.ins, [jack](auto in) { return (in == jack); });
		}
		// Remove any cables that now have no inputs
		std::erase_if(int_cables, [](auto cable) { return (cable.ins.size() == 0); });

		// Remove from inputs on all panel mappings
		for (auto &map : mapped_ins) {
			std::erase_if(map.ins, [jack](auto in) { return (in == jack); });
		}
		// Remove any panel mappings that now have no inputs
		std::erase_if(mapped_ins, [](auto map) { return (map.ins.size() == 0); });
	}

	void disconnect_outjack(Jack jack) {
		// Remove any cables with this output
		std::erase_if(int_cables, [jack](auto cable) { return (cable.out == jack); });

		// Remove any panel mappings with this output
		std::erase_if(mapped_outs, [jack](auto map) { return (map.out == jack); });
	}

	const MappedInputJack *find_mapped_injack(Jack jack) const {
		for (auto &m : mapped_ins) {
			for (auto &j : m.ins) {
				if (j == jack)
					return &m;
			}
		}
		return nullptr;
	}

	const MappedInputJack *find_mapped_injack(uint16_t panel_jack_id) const {
		for (auto &m : mapped_ins) {
			if (m.panel_jack_id == panel_jack_id)
				return &m;
		}
		return nullptr;
	}

	const MappedOutputJack *find_mapped_outjack(Jack jack) const {
		for (auto &m : mapped_outs) {
			if (m.out == jack)
				return &m;
		}
		return nullptr;
	}

	const MappedOutputJack *find_mapped_outjack(uint16_t panel_jack_id) const {
		for (auto &m : mapped_outs) {
			if (m.panel_jack_id == panel_jack_id)
				return &m;
		}
		return nullptr;
	}

	void add_mapped_injack(uint16_t panel_jack_id, Jack jack) {
		bool done = false;
		for (auto &m : mapped_ins) {
			if (m.panel_jack_id == panel_jack_id) {
				for (auto &j : m.ins) {
					if (j == jack)
						done = true; //exact match already exists, no further action needed
				}
				if (!done) {
					m.ins.push_back(jack);
					done = true;
				}
			}
		}
		if (!done)
			mapped_ins.push_back({panel_jack_id, {jack}});
	}

	void add_mapped_outjack(uint16_t panel_jack_id, Jack jack) {
		bool done = false;
		for (auto &m : mapped_outs) {
			if (m.panel_jack_id == panel_jack_id) {
				m.out = jack;
				done = true;
			}
		}
		if (!done)
			mapped_outs.push_back({panel_jack_id, jack});
	}

	const InternalCable *find_internal_cable_with_outjack(Jack out_jack) const {
		for (auto &c : int_cables) {
			if (c.out == out_jack && c.ins.size() > 0) {
				return &c;
			}
		}
		return nullptr;
	}

	const InternalCable *find_internal_cable_with_injack(Jack in_jack) const {
		for (auto &c : int_cables) {
			for (auto &in : c.ins) {
				if (in == in_jack) {
					return &c;
				}
			}
		}
		return nullptr;
	}

	const char *valid_knob_set_name(unsigned set_i) const {
		if (set_i == MIDIKnobSet)
			return "MIDI";

		if (set_i >= knob_sets.size())
			return "";

		if (knob_sets[set_i].name.length() > 0)
			return knob_sets[set_i].name.c_str();
		else
			return default_knob_set_name[set_i];
	}

	const char *default_knob_set_name[MaxKnobSets] = {
		"Knob Set 1",
		"Knob Set 2",
		"Knob Set 3",
		"Knob Set 4",
		"Knob Set 5",
		"Knob Set 6",
		"Knob Set 7",
		"Knob Set 8",
	};

private:
	//non-const version for private use only
	MappedKnob *_get_mapped_knob(uint32_t set_id, uint32_t module_id, uint32_t param_id) {
		if (set_id < knob_sets.size()) {
			for (auto &m : knob_sets[set_id].set) {
				if (m.module_id == module_id && m.param_id == param_id)
					return &m;
			}
		}
		return nullptr;
	}

	MappedKnob *_get_midi_map(uint32_t module_id, uint32_t param_id) {
		for (auto &m : midi_maps.set) {
			if (m.module_id == module_id && m.param_id == param_id)
				return &m;
		}
		return nullptr;
	}

	InternalCable *_find_internal_cable_with_outjack(Jack out_jack) {
		for (auto &c : int_cables) {
			if (c.out == out_jack && c.ins.size() > 0) {
				return &c;
			}
		}
		return nullptr;
	}
};
