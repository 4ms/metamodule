#include "gui/gui_state.hh"
#include "gui/notify/queue.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/reload_patch.hh"

namespace MetaModule
{

struct PatchFileChangeChecker {
	OpenPatchManager &open_patch_manager;
	NotificationQueue &notify_queue;
	ReloadPatch patch_loader;

	bool version_conflict = false;

	// Handle user modifying patch file disk via wifi or usb/sdcard
	PatchFileChangeChecker(FileStorageProxy &patch_storage,
						   OpenPatchManager &open_patch_manager,
						   NotificationQueue &notify_queue,
						   FilesystemSettings &fs_settings)
		: open_patch_manager{open_patch_manager}
		, notify_queue{notify_queue}
		, patch_loader{patch_storage, open_patch_manager, fs_settings} {
	}

	enum class Status {
		OK,
		FailLoadFile,
		VersionConflict,
		DidReload,
	};

	Status check_patch(PatchLocation const &loc) {
		if (patch_loader.is_not_open_or_has_changed_on_disk(loc)) {
			pr_trace("check_playing_patch: File on disk does not match file in memory (changed on disk)\n");

			if (open_patch_manager.get_playing_patch_modification_count() == 0) {
				version_conflict = false;

				// Patch changed on disk, but not in memory, so reload it
				if (auto result = patch_loader.reload_patch_file(loc); result.success) {
					return Status::DidReload;
				} else {
					return Status::FailLoadFile;
				}

			} else {
				if (version_conflict) {
					return Status::OK; //only notify once

				} else {
					version_conflict = true;
					std::string message = "A new version of ";
					message.append(loc.filename.c_str());
					message.append(" was just transferred, but you have unsaved changes. Please save, revert, or "
								   "duplicate the patch");
					notify_queue.put({
						.message = message,
						.priority = Notification::Priority::Info,
						.duration_ms = 3000,
					});

					return Status::VersionConflict;
				}
			}
		}

		return Status::OK;
	}
};

} // namespace MetaModule
