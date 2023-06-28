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
	uint32_t el_count = 0;

	std::optional<uint16_t> register_mapping(const auto &el, lv_obj_t *element_obj) {
		auto id = register_mapping_impl(el, element_obj);
		count(el);
		//auto de = DrawnElement{element_obj,
		return id;
	}

private:
	void count(auto &el) {
		indices = indices + ElementCount::count(el);
		el_count++;
	}

	std::optional<uint16_t> register_mapping_impl(const BaseElement &, lv_obj_t *) {
		return {};
	}

	std::optional<uint16_t> register_mapping_impl(const Knob &el, lv_obj_t *element_obj) {
		auto panel_map = patch.find_mapped_knob(module_idx, indices.param_idx);

		mappings.knobs.push_back({element_obj, panel_map, el, indices.param_idx, ParamAnimMethod::RotaryPot});

		if (panel_map)
			return panel_map->panel_knob_id;
		return {};
	}

	std::optional<uint16_t> register_mapping_impl(const Slider &el, lv_obj_t *element_obj) {
		auto panel_map = patch.find_mapped_knob(module_idx, indices.param_idx);

		mappings.knobs.push_back({element_obj, panel_map, el, indices.param_idx, ParamAnimMethod::LinearSlider});

		if (panel_map)
			return panel_map->panel_knob_id;
		return {};
	}

	std::optional<uint16_t> register_mapping_impl(const JackInput &el, lv_obj_t *element_obj) {
		auto panel_map = patch.find_mapped_injack(Jack{(uint16_t)module_idx, indices.input_idx});

		mappings.injacks.push_back({element_obj, panel_map, el, indices.input_idx});

		if (panel_map)
			return panel_map->panel_jack_id;
		return {};
	}

	std::optional<uint16_t> register_mapping_impl(const JackOutput &el, lv_obj_t *element_obj) {
		auto panel_map = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, indices.output_idx});

		mappings.outjacks.push_back({element_obj, panel_map, el, indices.output_idx});

		if (panel_map)
			return panel_map->panel_jack_id;
		return {};
	}

	std::optional<uint16_t> register_mapping_impl(const LightElement &el, lv_obj_t *element_obj) {
		mappings.lights.push_back({element_obj, el, indices.light_idx});
		return {};
	}
};

} // namespace MetaModule
