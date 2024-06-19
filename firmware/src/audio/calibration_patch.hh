#pragma once
#include "patch_data.hh"

namespace MetaModule
{

struct CalibrationPatch {
	PatchData *make_patch() {
		patch.blank_patch("Calibrator");
		// 4 dual-output SRC modules
		uint16_t src1 = patch.add_module("4msCompany:Atvert2");
		uint16_t src2 = patch.add_module("4msCompany:Atvert2");
		uint16_t src3 = patch.add_module("4msCompany:Atvert2");
		uint16_t src4 = patch.add_module("4msCompany:Atvert2");

		// All knobs center (= 0V output)
		patch.set_or_add_static_knob_value(src1, 0, 0.5f);
		patch.set_or_add_static_knob_value(src1, 1, 0.5f);
		patch.set_or_add_static_knob_value(src2, 0, 0.5f);
		patch.set_or_add_static_knob_value(src2, 1, 0.5f);
		patch.set_or_add_static_knob_value(src3, 0, 0.5f);
		patch.set_or_add_static_knob_value(src3, 1, 0.5f);
		patch.set_or_add_static_knob_value(src4, 0, 0.5f);
		patch.set_or_add_static_knob_value(src4, 1, 0.5f);

		// Connect outputs to panel jacks
		patch.add_mapped_outjack(0, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(1, {.module_id = src1, .jack_id = 1});
		patch.add_mapped_outjack(2, {.module_id = src2, .jack_id = 0});
		patch.add_mapped_outjack(3, {.module_id = src2, .jack_id = 1});
		patch.add_mapped_outjack(4, {.module_id = src3, .jack_id = 0});
		patch.add_mapped_outjack(5, {.module_id = src3, .jack_id = 1});
		patch.add_mapped_outjack(6, {.module_id = src4, .jack_id = 0});
		patch.add_mapped_outjack(7, {.module_id = src4, .jack_id = 1});
		return &patch;
	}

private:
	PatchData patch;
};
} // namespace MetaModule
