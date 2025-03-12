#include "patch_file/reload_patch.hh"
#include "delay.hh"
#include "open_patch_manager.hh"
#include "result_t.hh"
#include "util/callable.hh"

namespace MetaModule
{

static constexpr unsigned max_open_patches = 5;

ReloadPatch::ReloadPatch(FileStorageProxy &patch_storage, OpenPatchManager &patches)
	: patch_storage{patch_storage}
	, patches{patches} {
}

// Gets the latest file timestamp and size from M4's cache
std::optional<ReloadPatch::FileTimeSize> ReloadPatch::get_file_info(PatchLocation const &patch_loc) {

	auto start = get_time();

	while (!patch_storage.request_file_info(patch_loc.vol, patch_loc.filename)) {
		if (get_time() - start > 5000) {
			pr_err("ReloadPatch::get_file_info timeout making request\n");
			return {};
		}
	}

	while (true) {
		auto msg = patch_storage.get_message();

		if (msg.message_type == FileStorageProxy::FileInfoSuccess) {
			return FileTimeSize{.timestamp = msg.timestamp, .filesize = msg.length};
		}

		if (msg.message_type == FileStorageProxy::FileInfoFailed) {
			pr_dbg("ReloadPatch::get_file_info: get file info for '%s' failed \n", patch_loc.filename.c_str());
			return {};
		}

		if (get_time() - start > 5000) {
			pr_err("ReloadPatch::get_file_info timeout waiting for response\n");
			return {};
		}
	}

	pr_err("ReloadPatch::get_file_info internal error\n");
	return {};
}

bool ReloadPatch::check_file_changed(PatchLocation const &patch_loc, uint32_t timestamp, uint32_t filesize) {
	if (patch_loc.vol == Volume::RamDisk || patch_loc.vol == Volume::MaxVolumes)
		return false;

	if (auto filetimesize = get_file_info(patch_loc)) {
		return (filetimesize->timestamp != timestamp) || (filetimesize->filesize != filesize);
	} else
		return false;
}

Result ReloadPatch::reload_patch_file(PatchLocation const &loc, Function<void()> &&wait_func) {

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
	return {false, "Timed out requesting to load patch"};
}

// Returns true if timestamp/filesize on disk differs from the open patch (or there is no open patch)
bool ReloadPatch::has_changed_on_disk(PatchLocation const &loc) {
	if (auto openpatch = patches.find_open_patch(loc)) {
		return check_file_changed(loc, openpatch->timestamp, openpatch->filesize);
	}

	return true; //not found, return true because patch needs to be loaded from disk
}

} // namespace MetaModule
