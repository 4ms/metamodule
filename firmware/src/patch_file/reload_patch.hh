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

	// blocking
	Result reload_patch_file(PatchLocation const &loc, Function<void()> &&wait_func);

	// non-blocking
	// enum class ReloadResult { Trying, Reloaded, Failed };
	// ReloadResult try_reload_patch_file(PatchLocation const &loc);
	bool try_reload_from_cache(PatchLocation const &loc);
};
} // namespace MetaModule
