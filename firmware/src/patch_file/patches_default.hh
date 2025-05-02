#pragma once
#include "util/static_string.hh"
#include <cstdint>
#include <span>

///

#include "../patches/default/Ensemble Wash.hh"
#include "../patches/default/Karpeggiator.hh"
#include "../patches/default/MorphingDrone.hh"
#include "../patches/default/Oscillator Wash.hh"
#include "../patches/default/Thunderbanshee.hh"
#include "../patches/default/West Coast FM Madness.hh"
#include "../patches/default/Wonky Bass.hh"
#include "../patches/default/Wooden Groove.hh"

#include "../patches/default/Djembe4verb.hh"
#include "../patches/default/DualEnvEnosc.hh"
#include "../patches/default/EnOscPoly4.hh"
#include "../patches/default/EnOsc_step_seq.hh"
#include "../patches/default/KarplusStereo.hh"
#include "../patches/default/MIDI_Poly4.hh"
#include "../patches/default/Orcas_Heart_Octo_Djembe.hh"
// #include "../patches/default/PlaygroundBefaco.hh"
// #include "../patches/default/QuadDrum.hh"
#include "../patches/default/SlothDrone.hh"
// #include "../patches/default/SpringsintoCaves.hh"
// #include "../patches/default/UntwistedBraid.hh"
#include "../patches/default/WanderVoices.hh"

struct DefaultPatches {

	static inline std::array patch_raw_data = std::to_array<std::span<const char>>({
		patch_Ensemble_Wash,
		patch_Karpeggiator,
		patch_MorphingDrone,
		patch_Oscillator_Wash,
		patch_Thunderbanshee,
		patch_West_Coast_FM_Madness,
		patch_Wonky_Bass,
		patch_Wooden_Groove,

		Djembe4verb_patch, //
		DualEnvEnOsc_patch,
		EnOscPoly4_patch,
		EnOscStepSeq_patch,
		KarplusStereo_patch,
		MIDI_Poly4_patch,
		Orcas_Heart_Octo_Djembe_patch,
		// PlaygroundBefaco_patch,
		// QuadDrum_patch,
		Sloth_Drone_patch,
		// SpringsIntoCaves_patch,
		// UntwistedBraid_patch,
		WanderVoices_patch,
	});

	static inline std::array patch_filenames = std::to_array<StaticString<63>>({
		"Ensemble_Wash.yml",
		"Karpeggiator.yml",
		"MorphingDrone.yml",
		"Oscillator_Wash.yml",
		"Thunderbanshee.yml",
		"West_Coast_FM_Madness.yml",
		"Wonky_Bass.yml",
		"Wooden_Groove.yml",

		"Djembe4verb.yml",	//
		"DualEnvEnOsc.yml", //
		"EnOscPoly4.yml",	//
		"EnOscStepSeq.yml",
		"KarplusStereo.yml", //
		"MIDI_Poly4.yml",	 //
		"Orcas_Heart_Octo_Djembe.yml",
		// "PlaygroundBefaco.yml",
		// "QuadDrum.yml",			//
		"SlothDrone.yml", //
		// "SpringsintoCaves.yml", //
		// "UntwistedBraid_patch.yml",
		"WanderVoices.yml", //
	});

	static constexpr uint32_t num_patches() {
		return patch_raw_data.size();
	}

	static std::span<const char> get_patch(uint32_t id) {
		if (id >= patch_raw_data.size())
			return {};
		return {patch_raw_data[id].data(), patch_raw_data[id].size_bytes()};
	}

	static auto get_filename(uint32_t id) {
		if (id < patch_filenames.size())
			return patch_filenames[id];
		else {
			StaticString<63> s;
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
