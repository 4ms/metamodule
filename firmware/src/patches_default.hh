// #include "AllReal4ms.hh"
#include "CoreModules/moduleFactory.hh"
#include "Djembe2.hh"
#include "Djembe4.hh"
#include "Djembe4verb.hh"
#include "patch/SpectralPings.hh"

struct DefaultPatches {
	static uint32_t num_patches() {
		return 5;
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
		return "";
	}

	static size_t get_len(uint32_t id) {
		if (id == 0)
			return sizeof(Djembe2_patch) / sizeof(char);
		if (id == 1)
			return sizeof(Djembe4_patch) / sizeof(char);
		if (id == 2)
			return sizeof(SMR_patch) / sizeof(char);
		if (id == 3)
			return sizeof(Djembe4verb_patch) / sizeof(char);
		if (id == 4)
			return sizeof(SpectralPings_patch) / sizeof(char);
		return 0;
	}

	static char *get_data(uint32_t id) {
		if (id == 0)
			return Djembe2_patch;
		if (id == 1)
			return Djembe4_patch;
		if (id == 2)
			return SMR_patch;
		if (id == 3)
			return Djembe4verb_patch;
		if (id == 4)
			return SpectralPings_patch;
		return nullptr;
	}

	static std::span<char> get_patch(uint32_t id) {
		if (id == 0)
			return Djembe2_patch;
		if (id == 1)
			return Djembe4_patch;
		if (id == 2)
			return SMR_patch;
		if (id == 3)
			return Djembe4verb_patch;
		if (id == 4)
			return SpectralPings_patch;
		return {};
	}

	static inline char SMR_patch[] =
		R"( 
PatchData:
  patch_name: 'SMR Resonant Pings'
  description: "Lush resonant ping and plucks, in stereo.

  Big knobs control pitch (quantized to Cmaj by default).
  Gate 1 is the master clock, and small knobs control clock div/mult for each channel."
  module_slugs:
    0: Djembe
    1: PEG
    2: StMix
    3: SMR
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 2
  mapped_ins:
    - alias_name: Test1
      panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 3
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 4
  static_knobs:
    - module_id: 1
      param_id: 2
      value: 0.3
  mapped_knobs:
    - module_id: 1
      panel_knob_id: 3
      param_id: 3
      curve_type: 0
      min: 0.0
      max: 1.0
)";
};
