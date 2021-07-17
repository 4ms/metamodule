#include "patchlist.hh"

#include "patch/integration_tests/all_tests.hh"

#include "StereoVerb.hh"
#include "dualdjembe.hh"
#include "mappeddjembe.hh"
#include "mixerpass.hh"
#include "quaddjembe.hh"
#include "simplequaddjembe.hh"

PatchList::PatchList()
	: _patch_addrs{
		  // mixerpass_mmpatch,
		  mappeddjembe_mmpatch,
		  simplequaddjembe_mmpatch,
		  dualdjembe_mmpatch,
		  StereoVerb_mmpatch,
		  quaddjembe_mmpatch,
		  test_14switchCore_clock_mmpatch,
		  test_14switchCore_cv_mmpatch,
		  test_adCore_mmpatch,
		  test_attCore_mmpatch,
		  test_bitcrushCore_mmpatch,
		  test_bpfCore_mmpatch,
		  test_clkdividerCore_mmpatch,
		  test_clkmultiplierCore_mmpatch,
		  test_comparatorCore_mmpatch,
		  test_crossfadeCore_mmpatch,
		  test_eightstepCore_mmpatch,
		  test_envelopefollowerCore_mmpatch,
		  test_fourstepCore_mmpatch,
		  test_gateCore_mmpatch,
		  test_karplusCore_mmpatch,
		  test_logicCore_mmpatch,
		  test_minmaxCore_mmpatch,
		  test_multilfoCore_mmpatch,
		  test_octaveCore_mmpatch,
		  test_pannerCore_mmpatch,
		  test_quantizerCore_mmpatch,
		  test_sampleholdCore_mmpatch,
		  test_sendCore_mmpatch,
		  test_sense_pins_CV_mmpatch,
		  test_sense_pins_audio_mmpatch,
		  test_sense_pins_gates_mmpatch,
		  test_stereomixerCore_mmpatch,
		  test_vcaCore_mmpatch,
		  // MARK: Add patches below here:
	  }
{
	for (uint32_t i = 0; i < NumPatches; i++) {
		_patch_headers[i] = load_patch_header(_patch_addrs[i]);
	}
}
