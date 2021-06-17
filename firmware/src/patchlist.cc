#include "patchlist.hh"

#ifndef METAMODULE_INTEGRATION_TESTS
	#include "KP_FM_DRUM_DET.hh"
	#include "KarplusStereo.hh"
	#include "LPFBPF.hh"
	#include "QuadDrum.hh"
	#include "example_drum.hh"
	#include "example_drum_verb_mono.h"
	#include "example_duallfo.hh"
	#include "example_karplus.hh"
	#include "example_pitchShift_simple.hh"
	#include "example_stereo_verb.h"
	#include "fadedelay_two.hh"
	#include "simple_lfo_passthrru.hh"

PatchList::PatchList()
	: _patches{
		  {simple_lfo_passthrru},
		  {example_stereo_verb},
		  {examplePitchShiftSimple},
		  {exampleDrum},
		  {fadedelay_example},
		  {example_drum_verb_mono},
		  {QuadDrum},
		  {KP_FM_DRUM_DET},
		  {KarplusStereo},
		  {LPFBPF},
	  }
{
	_cur_patch_idx = 0;
}

#else
	#include "patch/integration_tests/all_tests.hh"

PatchList::PatchList()
	: _patches{
		  {test_14switchCore_clock},
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
	_cur_patch_idx = 0;
}

#endif
