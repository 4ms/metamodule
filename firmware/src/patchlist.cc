#include "patchlist.hh"
#include "norfs.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patchlist_ryml_tests.hh"
#include "util/zip.hh"

#include "Djembe2.hh"
#include "Djembe4.hh"
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

	NorFlashFS norfs;
	norfs.init();
	if (norfs.startfs()) {
		// printf("NOR Flash mounted as virtual fs");
	} else {
		auto ok = norfs.make_default_fs();
		if (!ok)
			return;
		// const std::span<unsigned char> d{Djembe2_yml, Djembe2_yml_len};
		ok = norfs.create_file("djembe2.yml", Djembe2_yml, Djembe2_yml_len);
		if (!ok)
			return;
		norfs.create_file("djembe4.yml", Djembe4_yml, Djembe4_yml_len);

		// printf("NOR Flash failed to mount");
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
