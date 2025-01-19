#include "gui/gui_state.hh"
#include "gui/pages/base.hh"
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
	PatchLoader patch_loader;

	bool version_conflict = false;

	// Handle user modifying patch file disk via wifi or usb/sdcard
	PatchFileChangeChecker(FileStorageProxy &patch_storage,
						   OpenPatchManager &open_patch_manager,
						   PatchPlayLoader &patch_playloader,
						   GuiState &gui_state,
						   NotificationQueue &notify_queue)
		: patch_storage{patch_storage}
		, open_patch_manager{open_patch_manager}
		, patch_playloader{patch_playloader}
		, gui_state{gui_state}
		, notify_queue{notify_queue}
		, patch_loader{patch_storage, open_patch_manager} {
	}

	enum class Status {
		OK,
		FailLoadFile,
		VersionConflict,
	};

	Status check_playing_patch() {
		auto auto_reload = true; //settings.filesystem.auto_reload_patch_file;

		PatchLocation loc = open_patch_manager.get_playing_patch_loc();

		if (patch_loader.has_changed_on_disk(loc)) {
			pr_trace("check_playing_patch: File on disk does not match file in memory (changed on disk)\n");

			if (open_patch_manager.get_playing_patch_modification_count() == 0) {
				version_conflict = false;

				// Patch changed on disk, but not in memory, so reload it if muted
				// or if auto reload is enabled
				// Otherwise if we're playing and disabled auto-reload, then PatchView/ModuleView
				// will see the patch_file_changed flag and reload if we stop/start playback
				// or do Revert or Reload from the fiel menu
				if (patch_playloader.is_audio_muted() || auto_reload) {

					if (auto result = patch_loader.reload_patch_file(loc); result.success) {
						patch_playloader.request_reload_playing_patch(false);

						pr_trace(
							"check_playing_patch: patch is muted or auto reload enabled: reloading playing patch\n");

						if (open_patch_manager.get_playing_patch() == open_patch_manager.get_view_patch()) {
							gui_state.view_patch_file_changed = true;
							pr_trace("check_playing_patch: ... also marking view_patch_file_changed\n");
						}
						return Status::OK;

					} else {
						return Status::FailLoadFile;
					}
				} else {
					// Patch is not muted and auto reload is disabled:
					// So we just wait until user mutes/unmutes
					if (gui_state.playing_patch_needs_manual_reload == false)
						pr_trace("check_playing_patch: patch is not muted and auto reload disabled: set ppnmr=true\n");
					gui_state.playing_patch_needs_manual_reload = true;

					return Status::OK;
				}
			} else {
				if (version_conflict) {
					return Status::OK; //only notify once

				} else {
					version_conflict = true;
					notify_queue.put({
						.message = "A new version of the patch that's playing was just transferred, but "
								   "you have unsaved changes. Please save, revert, or duplicate the patch",
						.priority = Notification::Priority::Info,
						.duration_ms = 3000,
					});

					return Status::VersionConflict;
				}
			}
		} else {
			pr_trace("check_playing_patch: file on disk matches file in memory\n");
		}
		return Status::OK;
	}

	Status check_view_patch() {
		auto auto_reload = true; //settings.filesystem.auto_reload_patch_file;
		PatchLocation loc = open_patch_manager.get_playing_patch_loc();

		// If we're viewing a different patch than the one that's playing...
		if (open_patch_manager.get_playing_patch() != open_patch_manager.get_view_patch()) {

			PatchLocation viewloc = open_patch_manager.get_view_patch_loc();
			// ...And the view patch changed on disk
			if (patch_loader.has_changed_on_disk(viewloc)) {
				// And it didn't change in memory
				if (open_patch_manager.get_view_patch_modification_count() == 0) {
					if (auto_reload) {
						if (auto result = patch_loader.reload_patch_file(loc); result.success) {
							gui_state.view_patch_file_changed = true;
						} else
							return Status::FailLoadFile;
					}
				} else {
					// It changed in memory and on disk:
					gui_state.view_patch_file_changed = true;
					return Status::VersionConflict;
				}
			}
		}

		return Status::OK;
	}
};

} // namespace MetaModule
