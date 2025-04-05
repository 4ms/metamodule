#pragma once
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/patch_location.hh"
#include "result_t.hh"
#include "user_settings/fs_settings.hh"
#include "util/callable.hh"

namespace MetaModule
{

class ReloadPatch {
	FileStorageProxy &patch_storage;
	OpenPatchManager &patches;
	FilesystemSettings &fs_settings;

public:
	struct FileTimeSize {
		uint32_t timestamp;
		uint32_t filesize;
	};

	ReloadPatch(FileStorageProxy &patch_storage, OpenPatchManager &patches, FilesystemSettings &fs_settings);

	// Gets the latest file timestamp and size from M4's cache
	// and compares it to our own

	bool check_file_changed(PatchLocation const &patch_loc, uint32_t timestamp, uint32_t filesize);

	std::optional<FileTimeSize> get_file_info(PatchLocation const &patch_loc);

	Result reload_patch_file(PatchLocation const &loc, Function<void()> &&wait_func = [] {});

	bool is_not_open_or_has_changed_on_disk(PatchLocation const &loc);
};
} // namespace MetaModule
