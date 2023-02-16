#pragma once

#include "CoreModules/moduleFactory.hh"

///
// #include "patch/ClockRockinBeats.hh"
// #include "patch/Djembe2.hh"
// #include "patch/Djembe4.hh"
// #include "patch/Djembe4verb.hh"
// #include "patch/KarplusStereo.hh"
// #include "patch/NonlinearGateSequencer.hh"
// #include "patch/OctoSampler.hh"
// #include "patch/QuartetofEnsembles.hh"
// // #include "patch/SeaofEchoes.hh"
// #include "patch/Seq8.hh"
// #include "patch/Showcase.hh"
// #include "patch/SpectralPings.hh"
#include "patch/twosimpleosc.hh"

struct DefaultPatches {

	static inline std::array patch_raw_data = std::to_array<std::span<char>>({
		// Showcase_patch,
		// Djembe2_patch,
		// Djembe4_patch,
		// Djembe4verb_patch,
		// NonlinearGateSequencer_patch,
		// SpectralPings_patch,
		// OctoSampler_patch,
		// ClockRockinBeats_patch,
		// KarplusStereo_patch,
		// QuartetofEnsembles_patch,
		// Seq8_patch,
		twosimpleosc_patch,
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
			// return "Showcase.yml";
			// if (id == 1)
			// return "djembe2.yml";
			// if (id == 2)
			// return "djembe4.yml";
			// if (id == 3)
			// return "djembe4verb.yml";
			// if (id == 4)
			// return "nonlinear.yml";
			// if (id == 5)
			// return "SpectralPings.yml";
			// if (id == 6)
			// return "OctoSampler.yml";
			// if (id == 7)
			// return "ClockRockinBeats.yml";
			// if (id == 8)
			// return "KarplusStereo.yml";
			// if (id == 9)
			// return "QuartetEnOsc.yml";
			// if (id == 10)
			// return "Seq8.yml";
			// if (id == 11)
			return "TwoSimpleOsc.yml";

		std::string t{std::to_string(id) + ".yml"};
		return t.c_str();
	}
};
