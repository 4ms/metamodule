#include "patchlist.hh"
#include "Djembe2.hh"
#include "Djembe4.hh"
#include "ff.h"
#include "patch_convert/yaml_to_patch.hh"
#include "patchlist_ryml_tests.hh"
#include "printf.h"
#include "util/zip.hh"

namespace MetaModule
{
PatchList::PatchList()
	: _status{Status::NotLoaded} {
	//FIXME: These hang when running on Cortex-A7, somewhere early in the first test, checking for "Module3"?
	// __BKPT();
	//if (!PatchListTargetTests::run_all_tests()) {
	//	printf("FAILED yaml tests\r\n");
	//	while (true)
	//		;
	//}
}

//TODO: move to default_patch_files.hh
ModuleTypeSlug PatchList::get_default_patch_filename(uint32_t id) {
	if (id == 0)
		return "djembe2.yml";
	if (id == 1)
		return "djembe4.yml";
	return "";
}

size_t PatchList::get_default_patch_data(uint32_t id, const uint8_t *data) {
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

void PatchList::add_patch_from_yaml(const std::span<char> data) {
	_patch_data.push_back({});
	NumPatches++;
	if (yaml_raw_to_patch(data, _patch_data.back())) {
		printf("Added Patch\r\n");
	} else {
		printf("Failed to parse\r\n");
		_patch_data.pop_back();
		NumPatches--;
	}
}

} // namespace MetaModule
