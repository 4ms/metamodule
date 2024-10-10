#pragma once
#include "patch/patch.hh"
#include <cstdint>

namespace MetaModule
{

// Space-efficient version of MappedKnob
struct MappedKnobSmall {
	uint16_t module_id;
	uint16_t param_id;
	float min;
	float max;

	MappedKnobSmall() = default;
	MappedKnobSmall(MappedKnob const &that)
		: module_id{that.module_id}
		, param_id{that.param_id}
		, min{that.min}
		, max{that.max} {
	}

	bool operator==(MappedKnobSmall const &that) const {
		return module_id == that.module_id && param_id == that.param_id;
	}

	float get_mapped_val(float panel_val) const {
		return (max - min) * panel_val + min;
	}
};

} // namespace MetaModule
