#include "patchlist.hh"
#include "Djembe2.hh"
#include "Djembe4.hh"
#include "ff.h"
#include "norfs.hh"
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

void PatchList::refresh_patches_from_fs(NorFlashFS &norfs) {
	//TODO: compare stack buffer vs dynamic buffer
	constexpr size_t MaxFileSize = 32768;
	char buf[MaxFileSize];
	uint32_t filesize;
	DIR dj;
	FILINFO fileinfo;

	_status = Status::Loading;
	_patch_data.clear();
	auto res = f_findfirst(&dj, &fileinfo, "", "*.yml");
	while (res == FR_OK && fileinfo.fname[0]) {
		printf("Found patch file: %s, Reading... ", fileinfo.fname);
		filesize = norfs.read_file(fileinfo.fname, buf, MaxFileSize);

		if (filesize == MaxFileSize) {
			printf("File exceeds %zu bytes, too big. Skipping\r\n", MaxFileSize);
			continue;
		}
		if (!filesize) {
			printf("File cannot be read. Skipping\r\n");
			continue;
		}
		printf("Read %d bytes.. parsing... ", filesize);

		_patch_data.push_back({});
		if (yaml_raw_to_patch({buf, filesize}, _patch_data.back())) {
			printf("Added Patch\r\n");
		} else {
			printf("Failed to parse\r\n");
			_patch_data.pop_back();
		}
		res = f_findnext(&dj, &fileinfo);
	}
	NumPatches = _patch_data.size();
	_status = Status::Ready;
}

} // namespace MetaModule
