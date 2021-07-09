#pragma once
#include "patch/patch.hh"

struct PatchList {

#ifdef METAMODULE_INTEGRATION_TESTS
	// MARK: Change NumPatches here:
	static const uint32_t NumPatches = 10; // Integration test patches
#else
	static const uint32_t NumPatches = 2; // Normal mode
#endif

	PatchList();

	ModuleTypeSlug &get_patch_name(uint32_t patch_id)
	{
		if (patch_id >= NumPatches)
			patch_id = 0;
		return _patch_headers[patch_id]->patch_name;
	}

	void load_patch_header(PatchHeader *ph, void *base_addr)
	{
		ph = reinterpret_cast<PatchHeader *>(base_addr);
	}

private:
	std::array<PatchHeader *, NumPatches> _patch_headers;
	std::array<void *, NumPatches> _patch_addrs;
};
