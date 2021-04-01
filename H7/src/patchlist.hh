#pragma once
#include "patch/patch.hh"

struct PatchList {
	static const uint32_t NumPatches = 7;

	PatchList();

	const Patch &cur_patch()
	{
		if (_cur_patch_idx >= NumPatches)
			_cur_patch_idx = 0;
		return _patches[_cur_patch_idx].patch;
	}

	const Patch &get_patch(uint32_t patch_id)
	{
		if (patch_id >= NumPatches)
			return _patches[0].patch;
		return _patches[patch_id].patch;
	}

	uint32_t cur_patch_index()
	{
		return _cur_patch_idx;
	}
	void next_patch()
	{
		_cur_patch_idx++;
		if (_cur_patch_idx == NumPatches)
			_cur_patch_idx = 0;
	}

	void prev_patch()
	{
		if (_cur_patch_idx == 0)
			_cur_patch_idx = NumPatches - 1;
		else
			_cur_patch_idx--;
	}

	void jump_to_patch(uint32_t patch_index)
	{
		if (patch_index >= NumPatches)
			_cur_patch_idx = NumPatches - 1;
		else
			_cur_patch_idx = patch_index;
	}

	// Todo: move this to UI, and have an interface for audio to set it in UI
	uint8_t audio_load = 0;

private:
	uint32_t _cur_patch_idx = 0;
	PatchRef _patches[NumPatches];
};
