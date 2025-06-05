#include "gui/gui_state.hh"
#include "gui/notify/queue.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_file/reload_patch.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct PatchFileChangeChecker {
	FileStorageProxy &patch_storage;
	OpenPatchManager &open_patch_manager;
	PatchPlayLoader &patch_playloader;
	GuiState &gui_state;
	NotificationQueue &notify_queue;
	ReloadPatch patch_loader;

	bool version_conflict = false;

	// Handle user modifying patch file disk via wifi or usb/sdcard
	PatchFileChangeChecker(FileStorageProxy &patch_storage,
						   OpenPatchManager &open_patch_manager,
						   PatchPlayLoader &patch_playloader,
						   GuiState &gui_state,
						   NotificationQueue &notify_queue,
						   FilesystemSettings &fs_settings)
		: patch_storage{patch_storage}
		, open_patch_manager{open_patch_manager}
		, patch_playloader{patch_playloader}
		, gui_state{gui_state}
		, notify_queue{notify_queue}
		, patch_loader{patch_storage, open_patch_manager, fs_settings} {
	}

	enum class Status {
		OK,
		FailLoadFile,
		VersionConflict,
	};

	Status check_playing_patch() {
		auto auto_reload = true; //settings.filesystem.auto_reload_patch_file;

		PatchLocation loc = open_patch_manager.get_playing_patch_loc();

		if (patch_loader.is_not_open_or_has_changed_on_disk(loc)) {
			pr_trace("check_playing_patch: File on disk does not match file in memory (changed on disk)\n");

			if (open_patch_manager.get_playing_patch_modification_count() == 0) {
				version_conflict = false;

				// Patch changed on disk, but not in memory, so reload it if muted or if auto reload is enabled
				if (patch_playloader.is_audio_muted() || auto_reload) {

					if (auto result = patch_loader.reload_patch_file(loc); result.success) {
						patch_playloader.request_reload_playing_patch(false);

						if (open_patch_manager.get_playing_patch() == open_patch_manager.get_view_patch()) {
							gui_state.force_redraw_patch = true;
						}
						return Status::OK;

					} else {
						return Status::FailLoadFile;
					}
				} else {
					// Patch is not muted and auto reload is disabled:
					// So we just notify the user
					gui_state.playing_patch_needs_manual_reload = true;

					return Status::OK;
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
		} else {
			pr_dump("check_playing_patch: file on disk matches file in memory\n");
		}
		return Status::OK;
	}

	Status check_view_patch() {
		PatchLocation viewloc = open_patch_manager.get_view_patch_loc();

		if (patch_loader.is_not_open_or_has_changed_on_disk(viewloc)) {
			pr_dbg("check_view_patch: File on disk does not match file in memory (changed on disk)\n");

			if (open_patch_manager.get_view_patch_modification_count() == 0) {
				version_conflict = false;

				if (auto result = patch_loader.reload_patch_file(viewloc); result.success) {
					pr_dbg("check_view_patch: Marking view_patch_file_changed true\n");
					notify_queue.put({"New patch file detected, refreshed", Notification::Priority::Status, 800});

					gui_state.view_patch_file_changed = true;
				} else
					return Status::FailLoadFile;

			} else {
				if (version_conflict) {
					return Status::OK; //only notify once

				} else {
					version_conflict = true;
					std::string message = "A new version of ";
					message.append(viewloc.filename.c_str());
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
