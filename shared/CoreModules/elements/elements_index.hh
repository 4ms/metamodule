#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"

namespace MetaModule::ElementIndex
{

inline uint8_t get_index(const BaseElement &, ElementCount::Indices) {
	return 0; //error
}

inline uint8_t get_index(const ParamElement &, ElementCount::Indices indices) {
	return indices.param_idx;
}

inline uint8_t get_index(const LightElement &, ElementCount::Indices indices) {
	return indices.light_idx;
}

inline uint8_t get_index(const JackInput &, ElementCount::Indices indices) {
	return indices.input_idx;
}

inline uint8_t get_index(const JackOutput &, ElementCount::Indices indices) {
	return indices.output_idx;
}

}; // namespace MetaModule::ElementIndex
