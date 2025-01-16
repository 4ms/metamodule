#include "patch_file/reload_patch.hh"
#include "delay.hh"
#include "open_patch_manager.hh"
#include "result_t.hh"
#include "util/callable.hh"
// #include <functional>

namespace MetaModule
{
// enum class ReloadState {
// 	Idle,
// 	Requested,
// 	Reloaded,
// 	Failed,
// };

static constexpr unsigned max_open_patches = 20;

PatchLoader::PatchLoader(FileStorageProxy &patch_storage, OpenPatchManager &patches)
	: patch_storage{patch_storage}
	, patches{patches} {
}

// Gets the latest file timestamp and size from M4's cache
// and compares it to our own
bool PatchLoader::check_file_changed(PatchLocation const &patch_loc, uint32_t timestamp, uint32_t filesize) {

	auto start = get_time();

	while (true) {
		auto ok = patch_storage.request_file_info(patch_loc.vol, patch_loc.filename);
		if (ok == true)
			break;
		if (get_time() - start > 5000)
			return false;
	}

	while (true) {
		auto msg = patch_storage.get_message();

		if (msg.message_type == FileStorageProxy::FileInfoSuccess) {
			if (msg.timestamp != timestamp || msg.length != filesize)
				return true;
			else
				return false;
		}

		if (msg.message_type == FileStorageProxy::FileInfoFailed) {
			return false;
		}

		if (get_time() - start > 5000)
			return false;
	}

	return false;
}

Result PatchLoader::reload_patch_file(PatchLocation const &loc, Function<void()> &&wait_func) {

	if (!patches.have_space_to_open_patch(max_open_patches)) {
		return {false, "Too many unsaved patches open! Save or close them to open a new patch"};
	}

	while (!patch_storage.request_load_patch(loc)) {
		wait_func();
	}

	uint32_t timeout = get_time() + 3000;
	while (get_time() < timeout) {

		auto message = patch_storage.get_message();

		// Successfully loaded
		if (message.message_type == FileStorageProxy::LoadFileOK) {

			auto data = patch_storage.get_patch_data(message.bytes_read);

			if (patches.open_patch(data, loc, message.timestamp)) {
				return {.success = true};

			} else {
				pr_warn("Error parsing %s\n", loc.filename.c_str());
				return {false, "Error parsing patch"};
			}

		} else if (message.message_type == FileStorageProxy::LoadFileFailed) {
			// Filesystem error (disk ejected, etc)
			// If it's the playing patch, try loading it from memory
			if (patches.get_playing_patch_loc_hash() == PatchLocHash{loc}) {
				patches.view_playing_patch();
				return {.success = true};
			} else
				return {false, "Failed to load patch file"};
		}

		wait_func();
	}

	pr_err("Timed out trying to load patch from disk\n");
	return {false, "Timed ou requesting to load patch"};
}

// Returns true if timestamp/filesize on disk differs from the open patch (or there is no open patch)
bool PatchLoader::has_changed_on_disk(PatchLocation const &loc) {
	if (auto openpatch = patches.find_open_patch(loc)) {
		if (!check_file_changed(loc, openpatch->timestamp, openpatch->filesize)) {
			patches.start_viewing(openpatch);
			// pr_dbg("Patch %s is open and timestamp/filesize match\n", loc.filename.c_str());
			return false;
		}
	}

	return true;
}

} // namespace MetaModule
