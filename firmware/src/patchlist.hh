#pragma once
#include "patch/patch.hh"

struct PatchList {

	static const uint32_t NumPatches = 33;

	PatchList();

	ModuleTypeSlug &get_patch_name(uint32_t patch_id)
	{
		if (patch_id >= NumPatches)
			patch_id = 0;
		return _patch_headers[patch_id]->patch_name;
	}

	PatchHeader *load_patch_header(void *base_addr)
	{
		return reinterpret_cast<PatchHeader *>(base_addr);
	}

	void set_cur_patch_index(int cur_idx)
	{
		_cur_patch_index = cur_idx;
	}

	int cur_patch_index()
	{
		return _cur_patch_index;
	}

	PatchHeader *cur_patch()
	{
		return _patch_headers[_cur_patch_index];
	}

private:
	std::array<PatchHeader *, NumPatches> _patch_headers;
	// TODO: _patch_headers could be constructed directly from init list, and we don't need _patch_addrs
	std::array<void *, NumPatches> _patch_addrs;
	int _cur_patch_index = 0;
};
