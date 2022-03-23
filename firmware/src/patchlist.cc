#include "patchlist.hh"
#include "Djembe2.hh"
#include "Djembe4.hh"
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
	: _raw_patch_yaml_files{
		  Djembe2_yml,
		  Djembe4_yml,
	  } {

	// And main/ui does the init and startfs
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

	// TODO: read from filesystem like this:
	// for (auto f : files_in_dir("patches/"){
	// 		std::string yamldata = read(f);
	//		if (ok) ...
	// 		yaml_string_to_patch(yamldata, patchheader, patchdata);
	// }
	std::array<uint8_t, 8192> filedata;
	if (norfs.read_file("djembe4.yml", filedata)) {
		std::string yamlstr{reinterpret_cast<char *>(filedata.data())}; //unsigned char -> char
		yaml_string_to_patch(yamlstr, _patch_data[0]);
	}

	if (norfs.read_file("djembe2.yml", filedata)) {
		std::string yamlstr{reinterpret_cast<char *>(filedata.data())}; //unsigned char -> char
		yaml_string_to_patch(yamlstr, _patch_data[1]);
	}

	norfs.set_status(NorFlashFS::Status::NotInUse);

	//for (auto [yamldata, patchdata] : zip(_raw_patch_yaml_files, _patch_data)) {
	//	//Note: we use a std::string because it allocates the space that ryml needs to parse in place
	//	std::string yamlstr{reinterpret_cast<char *>(yamldata)}; //unsigned char -> char
	//	yaml_string_to_patch(yamlstr, patchdata);
	//}

	//FIXME: These hang when running on Cortex-A7, somewhere early in the first test, checking for "Module3"?
	// __BKPT();
	//if (!PatchListTargetTests::run_all_tests()) {

	//	//printf("FAILED yaml tests\r\n");
	//	while (true)
	//		;
	//}
}

} // namespace MetaModule
