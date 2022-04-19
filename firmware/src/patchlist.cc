#include "patchlist.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patchlist_ryml_tests.hh"
#include "printf.h"

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

void PatchList::add_patch_from_yaml(const std::span<uint8_t> data) {
	add_patch_from_yaml({reinterpret_cast<char *>(data.data()), data.size()});
}
void PatchList::add_patch_from_yaml(const std::span<char> data) {
	_patch_data.push_back({});
	if (yaml_raw_to_patch(data, _patch_data.back())) {
		printf("Added Patch\r\n");
	} else {
		printf("Failed to parse\r\n");
		_patch_data.pop_back();
	}
}

} // namespace MetaModule
