#include "patchlist.hh"
#include "example_drum.hh"
#include "example_drum_verb_mono.h"
#include "example_duallfo.hh"
#include "example_karplus.hh"
#include "example_pitchShift_simple.hh"
#include "example_stereo_verb.h"
#include "fadedelay_two.hh"

PatchList::PatchList()
	: _patches{{exampleDualLFO},
			   {examplePitchShiftSimple},
			   {exampleDrum},
			   {fadedelay_example},
			   {example_drum_verb_mono},
			   {example_stereo_verb}}
{
	_cur_patch_idx = 0;
}
