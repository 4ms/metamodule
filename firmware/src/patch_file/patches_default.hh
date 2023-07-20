#pragma once
#include "CoreModules/module_type_slug.hh"
#include <cstdint>
#include <span>

///
#include "patch/AllBefaco.hh"
#include "patch/ClockRockinBeats.hh"
#include "patch/Djembe4.hh"
#include "patch/Djembe4verb.hh"
#include "patch/KarplusStereo.hh"
#include "patch/NonlinearGateSequencer.hh"
#include "patch/OctoSampler.hh"
#include "patch/QuartetofEnsembles.hh"
#include "patch/Seq8.hh"
#include "patch/Showcase.hh"
#include "patch/SpectralPings.hh"
#include "patch/braidslfo.hh"
#include "patch/dualatt.hh"
#include "patch/envevenbraids.hh"
#include "patch/twosimpleosc.hh"

struct DefaultPatches {

	static inline std::array patch_raw_data = std::to_array<std::span<char>>({
		Showcase_patch,
		env_even_braids,
		AllBefaco_patch,
		Djembe4_patch,
		Djembe4verb_patch,
		NonlinearGateSequencer_patch,
		SpectralPings_patch,
		OctoSampler_patch,
		ClockRockinBeats_patch,
		KarplusStereo_patch,
		QuartetofEnsembles_patch,
		Seq8_patch,
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
			return "Showcase";
		if (id == 1)
			return "envevenbraids";
		if (id == 2)
			return "AllBefaco";
		if (id == 3)
			return "djembe4";
		if (id == 4)
			return "djembe4verb";
		if (id == 5)
			return "nonlinear";
		if (id == 6)
			return "SpectralPings";
		if (id == 7)
			return "OctoSampler";
		if (id == 8)
			return "ClockRockinBeats";
		if (id == 9)
			return "KarplusStereo";
		if (id == 10)
			return "QuartetEnOsc";
		if (id == 11)
			return "Seq8";
		if (id == 12)
			return "TwoSimpleOsc";

		return "??";
	}
};
