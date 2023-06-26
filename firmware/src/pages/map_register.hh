#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "pages/animated_knob.hh"
#include "pages/styles.hh"
#include "patch/patch_data.hh"
#include <cstdint>

namespace MetaModule
{

struct MapRegister {
	size_t module_idx;
	const PatchData &patch;
	Mappings &mappings;
	ElementCount::Indices indices{};

	void count(auto &el) {
		indices = indices + ElementCount::count(el);
	}

	std::optional<uint16_t> register_mapping(const BaseElement &, lv_obj_t *) {
		return {};
	}

	std::optional<uint16_t> register_mapping(const Knob &el, lv_obj_t *element_obj) {
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, indices.param_idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, ParamAnimMethod::RotaryPot});
			return mapped_knob->panel_knob_id;
		}
		return {};
	}

	std::optional<uint16_t> register_mapping(const Slider &el, lv_obj_t *element_obj) {
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, indices.param_idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, ParamAnimMethod::LinearSlider});
			return mapped_knob->panel_knob_id;
		}
		return {};
	}

	std::optional<uint16_t> register_mapping(const JackInput &el, lv_obj_t *) {
		if (auto mapped_jack = patch.find_mapped_injack(Jack{(uint16_t)module_idx, indices.input_idx})) {
			return mapped_jack->panel_jack_id;
		}
		return {};
	}

	std::optional<uint16_t> register_mapping(const JackOutput &el, lv_obj_t *) {
		if (auto mapped_jack = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, indices.output_idx})) {
			return mapped_jack->panel_jack_id;
		}
		return {};
	}
};

} // namespace MetaModule
