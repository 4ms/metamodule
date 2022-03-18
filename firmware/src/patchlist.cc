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
PatchList::PatchList()
	: _raw_patch_yaml_files{
		  Djembe2_yml,
		  Djembe4_yml,
	  } {

	// TODO: make this LoadPatchFSToRAMDIsk()
	{
		NorFlashFS norfs;
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

	for (auto [yamldata, patchdata] : zip(_raw_patch_yaml_files, _patch_data)) {
		//Note: we use a std::string because it allocates the space that ryml needs to parse in place
		std::string yamlstr{reinterpret_cast<char *>(yamldata)}; //unsigned char -> char
		yaml_string_to_patch(yamlstr, patchdata);
	}

	//FIXME: These hang when running on Cortex-A7, somewhere early in the first test, checking for "Module3"?
	// __BKPT();
	//if (!PatchListTargetTests::run_all_tests()) {

	//	//printf("FAILED yaml tests\r\n");
	//	while (true)
	//		;
	//}
}

} // namespace MetaModule
