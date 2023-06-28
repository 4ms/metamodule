#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "pages/elements/context.hh"
#include "patch/patch_data.hh"
#include <cstdint>

namespace MetaModule
{

struct ElementContextHelper {
	uint16_t module_idx;
	const PatchData &patch;
	ElementCount::Indices indices{};

	ElementContext get_context(const auto &el, lv_obj_t *element_obj) {
		auto gui_element = get_context_impl(el, element_obj);
		count(el);
		return gui_element;
	}

private:
	void count(auto &el) {
		indices = indices + ElementCount::count(el);
	}

	auto get_context_impl(const BaseElement &, lv_obj_t *) {
		return ElementContext{};
	}

	auto get_context_impl(const Pot &, lv_obj_t *element_obj) {
		auto panel_map = patch.find_mapped_knob(module_idx, indices.param_idx);
		auto mapped_panel_id =
			panel_map ? std::optional<uint16_t>{panel_map->panel_knob_id} : std::optional<uint16_t>{};
		return ElementContext{element_obj, module_idx, indices.param_idx, mapped_panel_id};
	}

	auto get_context_impl(const JackInput &, lv_obj_t *element_obj) {
		auto panel_map = patch.find_mapped_injack(Jack{(uint16_t)module_idx, indices.input_idx});
		auto mapped_panel_id =
			panel_map ? std::optional<uint16_t>{panel_map->panel_jack_id} : std::optional<uint16_t>{};
		return ElementContext{element_obj, module_idx, indices.input_idx, mapped_panel_id};
	}

	auto get_context_impl(const JackOutput &, lv_obj_t *element_obj) {
		auto panel_map = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, indices.output_idx});
		auto mapped_panel_id =
			panel_map ? std::optional<uint16_t>{panel_map->panel_jack_id} : std::optional<uint16_t>{};
		return ElementContext{element_obj, module_idx, indices.output_idx, mapped_panel_id};
	}

	auto get_context_impl(const LightElement &, lv_obj_t *element_obj) {
		return ElementContext{element_obj, module_idx, indices.light_idx, {}};
	}
};

} // namespace MetaModule
