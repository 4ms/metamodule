#include "AllReal4ms.hh"
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
			return "allread4ms.yml";
		return "";
	}

	static size_t get_len(uint32_t id) {
		if (id == 0)
			return Djembe2_yml_len;
		if (id == 1)
			return Djembe4_yml_len;
		if (id == 2)
			return AllReal4ms_yml_len;
		return 0;
	}

	static uint8_t *get_data(uint32_t id) {
		if (id == 0)
			return Djembe2_yml;
		if (id == 1)
			return Djembe4_yml;
		if (id == 2)
			return AllReal4ms_yml;
		return nullptr;
	}

	static std::span<uint8_t> get_patch(uint32_t id) {
		if (id == 0)
			return Djembe2_yml;
		if (id == 1)
			return Djembe4_yml;
		if (id == 2)
			return AllReal4ms_yml;
		return {};
	}
};
