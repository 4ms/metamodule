#include "patchlist.hh"
#include "Djembe2.hh"
#include "Djembe4.hh"
#include "ff.h"
#include "norfs.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patchlist_ryml_tests.hh"
#include "printf.h"
#include "util/zip.hh"
// #include "test6.hh"
// #include "v2patch.hh"

// #include "patch/integration_tests/all_tests.hh"

namespace MetaModule
{
PatchList::PatchList(NorFlashFS &norfs)
	: _status{Status::NotLoaded} {
	// main/ui does the init and startfs
	// and if startfs() returns false, it calls mkfs and
	// norfs.create_file(PatchList::get_default_patch_name(), PatchList::get_default_patch());
	// and then stopfs()
	norfs.set_status(NorFlashFS::Status::InUse);

	// TODO: make this LoadPatchFSToRAMDIsk()
	{
		if (!norfs.init()) {
			printf("NOR Flash returned wrong id\r\n");
			return;
		}

		if (norfs.startfs()) {
			printf("NOR Flash mounted as virtual fs\r\n");
		} else {
			printf("No Fatfs found on NOR Flash, creating FS and default patch files...\r\n");
			auto ok = norfs.make_fs();
			if (!ok) {
				printf("Failed to create fs\r\n");
				return;
			}
			ok = norfs.create_file("djembe2.yml", {Djembe2_yml, Djembe2_yml_len});
			if (!ok) {
				printf("Failed to create file 1\r\n");
				return;
			}
			ok = norfs.create_file("djembe4.yml", {Djembe4_yml, Djembe4_yml_len});
			if (!ok) {
				printf("Failed to create file 2\r\n");
				return;
			}
			printf("Success.\r\n");

			printf("Writing back to NOR Flash.\r\n");

			norfs.stopfs();
		}
	}
	refresh_patches_from_fs(norfs);
	norfs.set_status(NorFlashFS::Status::NotInUse);

	//FIXME: These hang when running on Cortex-A7, somewhere early in the first test, checking for "Module3"?
	// __BKPT();
	//if (!PatchListTargetTests::run_all_tests()) {

	//	//printf("FAILED yaml tests\r\n");
	//	while (true)
	//		;
	//}
}

void PatchList::refresh_patches_from_fs(NorFlashFS &norfs) {
	//TODO: compare stack buffer vs dynamic buffer
	constexpr size_t MaxFileSize = 32768;
	char buf[MaxFileSize];
	uint32_t filesize;
	DIR dj;
	FILINFO fileinfo;

	_status = Status::Loading;
	auto res = f_findfirst(&dj, &fileinfo, "", "*.yml");
	while (res == FR_OK && fileinfo.fname[0]) {
		printf("Found file: %s, Reading... ", fileinfo.fname);
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
