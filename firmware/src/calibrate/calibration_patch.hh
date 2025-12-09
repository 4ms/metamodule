#pragma once
#include "patch/patch_data.hh"

namespace MetaModule
{

struct CalibrationPatch {
	PatchData *make_cal_patch() {
		patch.blank_patch("Calibrator");

		// 4 dual-output modules
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

		// Expander outs
		patch.add_mapped_outjack(8, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(9, {.module_id = src1, .jack_id = 1});
		patch.add_mapped_outjack(10, {.module_id = src2, .jack_id = 0});
		patch.add_mapped_outjack(11, {.module_id = src2, .jack_id = 1});
		patch.add_mapped_outjack(12, {.module_id = src3, .jack_id = 0});
		patch.add_mapped_outjack(13, {.module_id = src3, .jack_id = 1});
		patch.add_mapped_outjack(14, {.module_id = src4, .jack_id = 0});
		patch.add_mapped_outjack(15, {.module_id = src4, .jack_id = 1});
		return &patch;
	}

	PatchData *make_check_patch() {
		patch.blank_patch("Calibration Checker");

		uint16_t src1 = patch.add_module("4msCompany:Source");

		// knob center (= 0V output)
		patch.set_or_add_static_knob_value(src1, 0, 0.5f);

		// Enable hidden "octave mode"
		patch.set_or_add_static_knob_value(src1, 3, 1.0f);

		// Map knob A to Source knob
		patch.add_update_mapped_knob(0,
									 MappedKnob{
										 .panel_knob_id = 0,
										 .module_id = src1,
										 .param_id = 0,
										 .min = 0,
										 .max = 1,
									 });

		// Connect all panel output jacks to same Source output
		patch.add_mapped_outjack(0, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(1, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(2, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(3, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(4, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(5, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(6, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(7, {.module_id = src1, .jack_id = 0});

		patch.add_mapped_outjack(8, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(9, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(10, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(11, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(12, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(13, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(14, {.module_id = src1, .jack_id = 0});
		patch.add_mapped_outjack(15, {.module_id = src1, .jack_id = 0});
		return &patch;
	}

	PatchData *make_hardware_check_patch() {
		patch.blank_patch("Hardware Checker");

		std::array<uint16_t, 16> vco{
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),

			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
			(uint16_t)patch.add_module("4msCompany:FM"),
		};

		auto panel_out_idx = 0;
		auto octave = 0;
		for (auto v : vco) {
			patch.set_or_add_static_knob_value(v, 0, 1.0f); // Pitch
			patch.set_or_add_static_knob_value(v, 1, 1.0f); // Mix
			patch.set_or_add_static_knob_value(v, 6, 0.f);	// Shape
			patch.set_or_add_static_knob_value(v, 7, 1.f);	// ShapeCV

			// Each output is an octave higher, starting from 40Hz
			patch.set_or_add_static_knob_value(v, 4, std::min(octave / 7.f + 1.f / 14.f, 1.f)); // RatioCoarseKnob
			// Expanders are higher by a fifth or so
			patch.set_or_add_static_knob_value(v, 5, panel_out_idx < 8 ? 0.f : 0.25f); // RatioFineKnob

			// Output
			patch.add_mapped_outjack(panel_out_idx, {.module_id = v, .jack_id = 0}); //OutputOut

			// 0-5: In 1-6 => Voct,
			if (panel_out_idx < 6)
				patch.add_mapped_injack(panel_out_idx, {.module_id = v, .jack_id = 1}); //InputV_Oct_S

			// 6-7: GateIn1-2 => Shape CV
			else if (panel_out_idx < 8)
				patch.add_mapped_injack(panel_out_idx, {.module_id = v, .jack_id = 4}); //InputShape_Cv

			// 8-13: Exp In1-6
			else if (panel_out_idx < 14)
				patch.add_mapped_injack(panel_out_idx, {.module_id = v, .jack_id = 1}); //InputV_Oct_S

			octave = (octave + 1) % 8;

			panel_out_idx++;
		}

		return &patch;
	}

private:
	PatchData patch;
};
} // namespace MetaModule
