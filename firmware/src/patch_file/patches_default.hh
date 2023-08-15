#pragma once
#include "CoreModules/module_type_slug.hh"
#include <cstdint>
#include <span>

///
#include "patch/default/Braids-Quad.yml.hh"
#include "patch/default/Djembe4.hh"
#include "patch/default/Djembe4verb.hh"
#include "patch/default/EnOscDual.yml.hh"
#include "patch/default/EnvVCA_knobsets.yml.hh"
#include "patch/default/KarplusStereo.hh"
#include "patch/default/Seq8.hh"
#include "patch/default/envevenbraids.hh"
#include "patch/default/twosimpleosc.yml.hh"

struct DefaultPatches {

	static inline std::array patch_raw_data = std::to_array<std::span<char>>({
		env_even_braids,
		KarplusStereo_patch,
		Seq8_patch,
		Djembe4verb_patch,
		Djembe4_patch,
		twosimpleosc_patch,
		EnvVCA_knobsets_patch,
		EnOsc_Dual_patch,
		BraidsQuad_patch,
	});

	static constexpr uint32_t num_patches() {
		return patch_raw_data.size();
	}

	static std::span<char> get_patch(uint32_t id) {
		if (id >= patch_raw_data.size())
			return {};
		return {patch_raw_data[id].data(), patch_raw_data[id].size_bytes()};
	}

	static ModuleTypeSlug get_filename(uint32_t id) {
		if (id == 0)
			return "EnvEvenVCO.yml";
		if (id == 1)
			return "KarplusStereo.yml";
		if (id == 2)
			return "Seq8.yml";
		if (id == 3)
			return "djembe4verb.yml";
		if (id == 4)
			return "djembe4.yml";
		if (id == 5)
			return "twosimpleosc.yml";
		if (id == 6)
			return "EnvVCA_knobsets.yml";
		if (id == 7)
			return "EnOsc_Dual.yml";
		if (id == 8)
			return "Braids-Quad.yml";

		ModuleTypeSlug s;
		s._data[0] = ((id / 10) % 10) + '0';
		s._data[1] = (id % 10) + '0';
		s._data[2] = '.';
		s._data[3] = 'y';
		s._data[4] = 'm';
		s._data[5] = 'l';
		return s;
	}
};
