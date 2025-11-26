#pragma once
#include "gui/notify/queue.hh"
#include "gui/pages/file_browser/file_save_dialog.hh"
#include "gui/pages/page_list.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct PatchSaveDialog {

	PatchSaveDialog(FileStorageProxy &patch_storage,
					OpenPatchManager &patches,
					PatchPlayLoader &play_loader,
					FileSaveDialog &file_save_dialog,
					NotificationQueue &notify_queue,
					PageList &page_list)
		: dialog{file_save_dialog}
		, patches{patches}
		, patch_playloader{play_loader}
		, notify_queue{notify_queue}
		, page_list{page_list} {
	}

	enum class Action { None, Save, Duplicate, Rename };

	void prepare_focus(Action action) {
		this->action = action;
	}

	void show(lv_group_t *parent_group) {
		auto vol = patches.get_view_patch_vol();
		if (vol == Volume::RamDisk)
			vol = Volume::NorFlash;

		auto fullpath = patches.get_view_patch_filename();

		dialog.show(
			vol, fullpath, ".yml", parent_group, [this](Volume vol, std::string_view path) { save(vol, path); });

		is_renaming = false;
	}

	void hide() {
		dialog.hide();
	}

	bool is_visible() {
		return dialog.is_visible();
	}

	bool did_save() {
		bool t = saved;
		saved = false;
		return t;
	}

	bool did_rename() {
		bool t = is_renaming;
		is_renaming = false;
		return t;
	}

	void back_event() {
		pr_err("Should not call PSD::back_event bec. PageManager handles it\n");
		dialog.back_event();
	}

private:
	void save(Volume file_vol, std::string_view path) {
		// Cleanup path:
		auto fullpath = std::filesystem::path(path).lexically_normal().string();
		if (fullpath.starts_with("/")) {
			fullpath = fullpath.substr(1);
		}

		if (!fullpath.ends_with(".yml")) {
			fullpath.append(".yml");
		}

		auto patchname = std::filesystem::path(fullpath).filename().string();
		if (patchname.ends_with(".yml")) {
			patchname = patchname.substr(0, patchname.length() - 4);
		}

		if (action == Action::Save) {
			patches.get_view_patch()->patch_name = patchname;
			patches.rename_view_patch_file(fullpath, file_vol);
			patch_playloader.request_save_patch();

			saved = true;
			hide();

		} else if (action == Action::Rename) {
			if (patches.get_view_patch_loc_hash() != PatchLocHash{fullpath, file_vol}) {
				patches.get_view_patch()->patch_name = patchname;
				patch_playloader.request_rename_view_patch({fullpath, file_vol});
				is_renaming = true;
				hide();
			} else {
				notify_queue.put({"To rename a patch, you must enter a new name", Notification::Priority::Error});
			}

		} else if (action == Action::Duplicate) {
			// update module state for current patch
			patch_playloader.get_module_states();
			if (patches.duplicate_view_patch(fullpath, file_vol)) {
				patches.get_view_patch()->patch_name = patchname;
				patch_playloader.request_save_patch();
				saved = true;
				auto patch_loc = PatchLocation{std::string_view{fullpath}, file_vol};
				page_list.request_new_page_no_history(
					PageId::PatchView, {.patch_loc = patch_loc, .patch_loc_hash = PatchLocHash{patch_loc}});

				hide();
			} else {
				//send notification of failure
				std::string err_str = "File " + fullpath + " already exists and is open, cannot save over it.";
				notify_queue.put({err_str, Notification::Priority::Error});
			}
		}
	}

	FileSaveDialog &dialog;
	OpenPatchManager &patches;
	PatchPlayLoader &patch_playloader;
	NotificationQueue &notify_queue;
	PageList &page_list;

	bool saved = false;
	bool is_renaming = false;

	Action action{};
};

} // namespace MetaModule
