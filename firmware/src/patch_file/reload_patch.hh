#pragma once
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/patch_location.hh"
#include "result_t.hh"
#include "util/callable.hh"

namespace MetaModule
{

class PatchLoader {
	FileStorageProxy &patch_storage;
	OpenPatchManager &patches;

public:
	PatchLoader(FileStorageProxy &patch_storage, OpenPatchManager &patches);

	// Gets the latest file timestamp and size from M4's cache
	// and compares it to our own
	bool check_file_changed(PatchLocation const &patch_loc, uint32_t timestamp, uint32_t filesize);

	Result reload_patch_file(PatchLocation const &loc, Function<void()> &&wait_func);

	bool has_changed_on_disk(PatchLocation const &loc);
};
} // namespace MetaModule
