#pragma once
#include "CoreModules/module_type_slug.hh"
#include <cstdint>
#include <span>

///

#include "patch/default/PlaygroundBefaco.hh"
#include "patch/default/UntwistedBraid.hh"

#include "patch/default/Djembe4verb.hh"
#include "patch/default/DualEnvEnosc.hh"
#include "patch/default/EnOscPoly4.hh"
#include "patch/default/EnOsc_step_seq.hh"
#include "patch/default/KarplusStereo.hh"
#include "patch/default/MIDI_Poly4.hh"
#include "patch/default/Orcas_Heart_Octo_Djembe.hh"
#include "patch/default/QuadDrum.hh"
#include "patch/default/SlothDrone.hh"
#include "patch/default/SpringsintoCaves.hh"
#include "patch/default/WanderVoices.hh"

struct DefaultPatches {

	static inline std::array patch_raw_data = std::to_array<std::span<const char>>({
		Sloth_Drone_patch,		//
		WanderVoices_patch,		//
		DualEnvEnOsc_patch,		//
		SpringsIntoCaves_patch, //
		Orcas_Heart_Octo_Djembe_patch,
		EnOscPoly4_patch, //
		QuadDrum_patch,	  //
		PlaygroundBefaco_patch,
		Djembe4verb_patch,	 //
		KarplusStereo_patch, //
		EnOscStepSeq_patch,
		UntwistedBraid_patch,
		MIDI_Poly4_patch, //
	});

	static inline std::array patch_filenames = std::to_array<ModuleTypeSlug>({
		"SlothDrone.yml",		//
		"WanderVoices.yml",		//
		"DualEnvEnOsc.yml",		//
		"SpringsintoCaves.yml", //
		"Orcas_Heart_Octo_Djembe.yml",
		"EnOscPoly4.yml", //
		"QuadDrum.yml",	  //
		"PlaygroundBefaco.yml",
		"Djembe4verb.yml",	 //
		"KarplusStereo.yml", //
		"EnOscStepSeq.yml",
		"UntwistedBraid_patch.yml",
		"MIDI_Poly4.yml", //
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
