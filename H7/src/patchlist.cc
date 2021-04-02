#include "patchlist.hh"
#include "KP_FM_DRUM_DET.hh"
#include "KarplusStereo.hh"
#include "QuadDrum.hh"
#include "example_drum.hh"
#include "example_drum_verb_mono.h"
#include "example_duallfo.hh"
#include "example_karplus.hh"
#include "example_pitchShift_simple.hh"
#include "example_stereo_verb.h"
#include "fadedelay_two.hh"
#include "gateintest.hh"

PatchList::PatchList()
	: _patches{{exampleDualLFO},
			   {examplePitchShiftSimple},
			   {exampleDrum},
			   {fadedelay_example},
			   {example_drum_verb_mono},
			   {example_stereo_verb},
			   {QuadDrum},
			   {KP_FM_DRUM_DET},
			   {KarplusStereo},
			   {gateintest}}
{
	_cur_patch_idx = 0;
}
