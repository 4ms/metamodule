#include "patchlist.hh"

#ifndef METAMODULE_INTEGRATION_TESTS
	// #include "KP_FM_DRUM_DET.hh"
	// #include "KarplusStereo.hh"
	// #include "LPFBPF.hh"
	// #include "QuadDrum.hh"
	// #include "example_drum.hh"
	// #include "example_drum_verb_mono.h"
	// #include "example_duallfo.hh"
	// #include "example_karplus.hh"
	// #include "example_pitchShift_simple.hh"
	// #include "example_stereo_verb.h"
	// #include "fadedelay_two.hh"
	// #include "simple_lfo_passthrru.hh"
	#include "mixerpass.hh"
	#include "StereoVerb.hh"
	#include "testbin3.hh"
	#include "anothertest.hh"
	#include "testbin2.hh"
	#include "quaddjmebe.hh"
	#include "dualdjmebe.hh"

PatchList::PatchList()
	: _patch_addrs{
		  testbin2_mmpatch,
		  dualdjmebe_mmpatch,
		  quaddjmebe_mmpatch,
		  testbin3_mmpatch,
		  mixerpass_mmpatch,
		  StereoVerb_mmpatch,
	  }
{
	for (int i = 0; i < NumPatches; i++) {
		_patch_headers[i] = load_patch_header(_patch_addrs[i]);
	}
}

#else
	#include "patch/integration_tests/all_tests.hh"

PatchList::PatchList()
	: _patches{
		  {test_quantizerCore},
		  {test_14switchCore_cv},
		  {test_bitcrushCore},
		  {test_karplusCore},
		  {test_clkdivideCore},
		  {test_clkmultiplierCore},
		  {test_comparatorCore},
		  // {test_crossfadeCore},
		  // {test_logicCore},
		  // {test_minmaxCore}
		  {test_sense_pins_CV},
		  {test_sense_pins_gates},
		  {test_sense_pins_audio},
		  // MARK: Add patches below here:
	  }
{
	for (int i = 0; i < NumPatches; i++) {
		_patch_headers[i] = load_patch_header(_patch_addrs[i]);
	}
}

#endif
