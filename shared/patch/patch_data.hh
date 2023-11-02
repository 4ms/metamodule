#pragma once
#include "CoreModules/module_type_slug.hh"
#include "patch.hh"
#include "util/static_string.hh"
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

	const MappedKnob *find_mapped_knob(uint32_t set_id, uint32_t module_id, uint32_t param_id) const {
		if (set_id < knob_sets.size()) {
			for (auto &m : knob_sets[set_id].set) {
				if (m.module_id == module_id && m.param_id == param_id)
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

	const MappedInputJack *find_mapped_injack(Jack jack) const {
		for (auto &m : mapped_ins) {
			for (auto &j : m.ins) {
				if (j == jack)
					return &m;
			}
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
};
