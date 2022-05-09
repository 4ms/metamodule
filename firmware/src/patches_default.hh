#include "CoreModules/moduleFactory.hh"

///
#include "patch/ClockRockinBeats.hh"
#include "patch/Djembe2.hh"
#include "patch/Djembe4.hh"
#include "patch/Djembe4verb.hh"
#include "patch/KarplusStereo.hh"
#include "patch/NonlinearGateSequencer.hh"
#include "patch/OctoSampler.hh"
#include "patch/QuartetofEnsembles.hh"
#include "patch/SeaofEchoes.hh"
#include "patch/Showcase.hh"
#include "patch/SpectralPings.hh"

struct DefaultPatches {

	static inline std::array patch_raw_data = std::to_array<std::span<char>>({
		Showcase_patch,
		Djembe2_patch,
		Djembe4_patch,
		Djembe4verb_patch,
		NonlinearGateSequencer_patch,
		SpectralPings_patch,
		OctoSampler_patch,
		ClockRockinBeats_patch,
		KarplusStereo_patch,
		QuartetofEnsembles_patch,
		SeaofEchoes_patch,
	});

	static constexpr uint32_t num_patches() {
		return patch_raw_data.size();
	}

	static std::span<char> get_patch(uint32_t id) {
		if (id >= patch_raw_data.size())
			return {};
		return patch_raw_data[id];
	}

	static ModuleTypeSlug get_filename(uint32_t id) {
		if (id == 0)
			return "djembe2.yml";
		if (id == 1)
			return "djembe4.yml";
		if (id == 2)
			return "smr_resonant_pings.yml";
		if (id == 3)
			return "Djembe4verb.yml";
		if (id == 4)
			return "SpectralPings.yml";
		std::string t{std::to_string(id) + ".yml"};
		return t.c_str();
	}
};
