#pragma once
#include "example_drum.hh"
#include "example_drum_verb_mono.h"
#include "example_duallfo.hh"
#include "example_karplus.hh"
#include "example_pitchShift_simple.hh"
#include "example_stereo_verb.h"
#include "fadedelay_two.hh"
#include "patch/patch.hh"

struct PatchList {
	static constexpr uint32_t NumPatches = 6;

	PatchList()
		: _patches{{exampleDualLFO},
				   {examplePitchShiftSimple},
				   {exampleDrum},
				   {fadedelay_example},
				   {example_drum_verb_mono},
				   {example_stereo_verb}}
	{}

	const Patch &cur_patch()
	{
		return _patches[_cur_patch].patch;
	}

	void next_patch()
	{
		_cur_patch++;
		if (_cur_patch == NumPatches)
			_cur_patch = 0;
	}

	void prev_patch()
	{
		if (_cur_patch == 0)
			_cur_patch = NumPatches - 1;
		else
			_cur_patch--;
	}

	uint8_t audio_load = 0;
	bool should_redraw_patch = false;

private:
	uint32_t _cur_patch = 0;
	PatchRef _patches[NumPatches];
};

