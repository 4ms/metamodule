#include "Djembe2.hh"
#include "Djembe4.hh"
#include "moduleFactory.hh"

struct DefaultPatches {
	static ModuleTypeSlug get_default_patch_filename(uint32_t id) {
		if (id == 0)
			return "djembe2.yml";
		if (id == 1)
			return "djembe4.yml";
		return "";
	}

	static size_t get_default_patch_data(uint32_t id, const uint8_t *data) {
		if (id == 0) {
			data = Djembe2_yml;
			return Djembe2_yml_len;
		}
		if (id == 1) {
			data = Djembe4_yml;
			return Djembe4_yml_len;
		}
		data = nullptr;
		return 0;
	}
};
