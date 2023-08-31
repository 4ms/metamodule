#pragma once
#include "CoreModules/module_type_slug.hh"
#include "patch.hh"
#include "util/static_string.hh"
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

	const MappedKnob *find_mapped_knob(uint32_t set_id, uint32_t module_id, uint32_t param_id) const {
		if (set_id < knob_sets.size()) {
			for (auto &m : knob_sets[set_id].set) {
				if (m.module_id == module_id && m.param_id == param_id)
					return &m;
			}
		}
		return nullptr;
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

	const char *validate_knob_set_name(unsigned set_i) {
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
};
