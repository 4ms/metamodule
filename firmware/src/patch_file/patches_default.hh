#pragma once
#include "CoreModules/module_type_slug.hh"
#include <cstdint>
#include <span>

///

#include "patch/default/Befaco4msPlayground.hh"
#include "patch/default/BefacoVCOs.hh"
#include "patch/default/Braids-Quad.hh"
#include "patch/default/Djembe4verb.hh"
#include "patch/default/EnOscDual.hh"
#include "patch/default/EnOscPoly4.hh"
#include "patch/default/EnOsc_8_step_seq.hh"
#include "patch/default/EnvVCA_knobsets.hh"
#include "patch/default/KarplusStereo.hh"
#include "patch/default/QuadDrum.hh"
#include "patch/default/SlothDrone.hh"
#include "patch/default/twosimpleosc.hh"

struct DefaultPatches {

	static inline std::array patch_raw_data = std::to_array<std::span<const char>>({
		Sloth_Drone_patch,
		EnOscPoly4_patch,
		QuadDrum_patch,
		Befaco4msPlayground_patch,
		Djembe4verb_patch,
		EnOsc_Dual_patch,
		BefacoVCOs_patch,
		KarplusStereo_patch,
		EnOsc8StepSeq_patch,
		twosimpleosc_patch,
		EnvVCA_knobsets_patch,
		BraidsQuad_patch,
	});

	static inline std::array patch_filenames = std::to_array<ModuleTypeSlug>({
		"SlothDrone.yml",
		"EnOscPoly4.yml",
		"QuadDrum.yml",
		"Befaco4msPlayground.yml",
		"Djembe4verb.yml",
		"EnOsc_Dual.yml",
		"BefacoVCOs.yml",
		"KarplusStereo.yml",
		"EnOsc8StepSeq.yml",
		"twosimpleosc.yml",
		"EnvVCA_knobsets.yml",
		"BraidsQuad.yml",
	});

	static constexpr uint32_t num_patches() {
		return patch_raw_data.size();
	}

	static std::span<const char> get_patch(uint32_t id) {
		if (id >= patch_raw_data.size())
			return {};
		return {patch_raw_data[id].data(), patch_raw_data[id].size_bytes()};
	}

	static ModuleTypeSlug get_filename(uint32_t id) {
		if (id < patch_filenames.size())
			return patch_filenames[id];
		else {
			ModuleTypeSlug s;
			s._data[0] = ((id / 10) % 10) + '0';
			s._data[1] = (id % 10) + '0';
			s._data[2] = '.';
			s._data[3] = 'y';
			s._data[4] = 'm';
			s._data[5] = 'l';
			s._data[6] = '\0';
			return s;
		}
	}
};
