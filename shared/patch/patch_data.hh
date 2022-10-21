#pragma once
#include "CoreModules/moduleFactory.hh" //for ModuleTypeSlug
#include "patch.hh"
#include "util/static_string.hh"
#include <vector>

//72B = 6 vec * 12B ea (data, sz, cap) + patch_name + description
struct PatchData {
	static constexpr size_t DescSize = 255;
	ModuleTypeSlug patch_name{""};
	StaticString<DescSize> description;
	std::vector<ModuleTypeSlug> module_slugs;  //32B
	std::vector<InternalCable> int_cables;	   //16B
	std::vector<MappedInputJack> mapped_ins;   //16B
	std::vector<MappedOutputJack> mapped_outs; //8B
	std::vector<StaticParam> static_knobs;	   //8B
	std::vector<MappedKnob> mapped_knobs;	   //16B

	const MappedKnob *find_mapped_knob(uint32_t module_id, uint32_t param_id) const {
		for (auto &m : mapped_knobs) {
			if (m.module_id == module_id && m.param_id == param_id)
				return &m;
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
};
