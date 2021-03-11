#pragma once
#include "patch/patch.hh"

struct PatchList {
	static const uint32_t NumPatches = 6;

	PatchList();

	const Patch &cur_patch()
	{
		if (_cur_patch >= NumPatches)
			_cur_patch = 0;
		return _patches[_cur_patch].patch;
	}
	uint32_t cur_patch_index()
	{
		return _cur_patch;
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
