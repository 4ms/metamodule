#include "patchlist.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patchlist_ryml_tests.hh"
#include "util/zip.hh"

#include "Djembe2.hh"
#include "test6.hh"
#include "v2patch.hh"

// #include "patch/integration_tests/all_tests.hh"

namespace MetaModule
{
PatchList::PatchList()
	: _raw_patch_yaml_files{
		  Djembe2_yml,

		  // test_inputs_56g1g2_mmpatch,
		  // test_14switchCore_clock_mmpatch,
		  // test_14switchCore_cv_mmpatch,
		  // test_adCore_mmpatch,
		  // test_attCore_mmpatch,
		  // test_bitcrushCore_mmpatch,
		  // test_bpfCore_mmpatch,
		  // test_clkdividerCore_mmpatch,
		  // test_clkmultiplierCore_mmpatch,
		  // test_comparatorCore_mmpatch,
		  // test_crossfadeCore_mmpatch,
		  // test_eightstepCore_mmpatch,
		  // test_envelopefollowerCore_mmpatch,
		  // test_fourstepCore_mmpatch,
		  // test_gateCore_mmpatch,
		  // test_karplusCore_mmpatch,
		  // test_logicCore_mmpatch,
		  // test_minmaxCore_mmpatch,
		  // test_multilfoCore_mmpatch,
		  // test_octaveCore_mmpatch,
		  // test_pannerCore_mmpatch,
		  // test_quantizerCore_mmpatch,
		  // test_sampleholdCore_mmpatch,
		  // test_sendCore_mmpatch,
		  // test_sense_pins_CV_mmpatch,
		  // test_sense_pins_audio_mmpatch,
		  // test_sense_pins_gates_mmpatch,
		  // test_stereomixerCore_mmpatch,
		  // test_vcaCore_mmpatch,
		  // MARK: Add patches below here:
	  } {

	// TODO: read from filesystem like this:
	// for (auto f : files_in_dir("patches/"){
	// 		std::string yamldata = read(f);
	//		if (ok) ...
	// 		yaml_string_to_patch(yamldata, patchheader, patchdata);
	// }

	for (auto [yamldata, patchheader, patchdata] : zip(_raw_patch_yaml_files, _patch_headers, _patch_data)) {
		//Note: we use a std::string because it allocates the space that ryml needs to parse in place
		std::string yamlstr{reinterpret_cast<char *>(yamldata)}; //unsigned char -> char
		yaml_string_to_patch(yamlstr, patchheader, patchdata);
	}

	if (!PatchListTargetTests::run_all_tests()) {

		//printf("FAILED yaml tests\r\n");
		while (true)
			;
	}
}

} // namespace MetaModule
