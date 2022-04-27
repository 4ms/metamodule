// #include "AllReal4ms.hh"
#include "CoreModules/moduleFactory.hh"
#include "Djembe2.hh"
#include "Djembe4.hh"

struct DefaultPatches {
	static uint32_t num_patches() {
		return 3;
	}

	static ModuleTypeSlug get_filename(uint32_t id) {
		if (id == 0)
			return "djembe2.yml";
		if (id == 1)
			return "djembe4.yml";
		if (id == 2)
			return "smr_resonant_pings.yml";
		return "";
	}

	static size_t get_len(uint32_t id) {
		if (id == 0)
			return Djembe2_yml_len;
		if (id == 1)
			return Djembe4_yml_len;
		if (id == 2)
			return sizeof(SMR_patch) / sizeof(char);
		// return AllReal4ms_yml_len;
		return 0;
	}

	static uint8_t *get_data(uint32_t id) {
		if (id == 0)
			return Djembe2_yml;
		if (id == 1)
			return Djembe4_yml;
		if (id == 2)
			return SMR_patch;
		return nullptr;
	}

	static std::span<uint8_t> get_patch(uint32_t id) {
		if (id == 0)
			return Djembe2_yml;
		if (id == 1)
			return Djembe4_yml;
		if (id == 2)
			return SMR_patch;
		return {};
	}

	static inline uint8_t SMR_patch[] =
		R"( 
PatchData:
  patch_name: SMR Resonant Pings
  module_slugs:
    0: PanelMedium
	1: SMR
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
)";
};
