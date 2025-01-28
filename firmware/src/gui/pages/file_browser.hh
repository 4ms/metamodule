#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/slsexport/filebrowser/ui.h"
#include "patch_file/file_storage_proxy.hh"

namespace MetaModule
{

// TODO: try aligned_alloc with clean/invalidate cache  (see calibration_routine)
// If not, then put this in static_buffers
#if !defined(SIMULATOR) && !defined(TEST_PROJECT)
__attribute__((section(".ddma")))
#endif
static DirTree<FileEntry>
	dir_tree;

struct FileBrowserDialog {
	FileBrowserDialog(FileStorageProxy &file_storage, NotificationQueue &notify_queue, PageList &page_list)
		: file_storage{file_storage}
		, notify_queue{notify_queue}
		, page_list{page_list}
		, group(lv_group_create()) {

		lv_group_add_obj(group, ui_FileBrowserRoller);
		lv_label_set_text(ui_FileBrowserTitle, "Open a file\n");
		lv_hide(ui_FileBrowserCont);
		auto roller_label = lv_obj_get_child(ui_FileBrowserRoller, 0);
		lv_label_set_recolor(roller_label, true);
	}

	void set_title(std::string_view title) {
		if (title.data() && title.length())
			lv_label_set_text(ui_FileBrowserTitle, title.data());
	}

	// Extension filters are comma-separated list without dot or start: "wav, WAV, raw"
	void filter_extensions(std::string_view extensions) {
		exts = extensions;
	}

	void show(std::string_view start_dir, const std::function<void(char *)> action) {
		this->action = std::move(action);

		visible = true;
		refresh_state = RefreshState::TryingToRequest;
		lv_obj_set_parent(ui_FileBrowserCont, lv_layer_top());
		lv_show(ui_FileBrowserCont);
	}

	bool consume_back() {
		// TODO: should back go back to the previous directory? Or close the dialog?
		return false;
	}

	void update() {
		switch (refresh_state) {
			case RefreshState::Idle: {
				//periodically check if patchlist needs updating:
				uint32_t now = lv_tick_get();
				if (now - last_refresh_check_tm > 1000) {
					last_refresh_check_tm = now;
					refresh_state = RefreshState::TryingToRequest;
				}
			} break;

			case RefreshState::TryingToRequest: {
				if (file_storage.request_dir_entries(&dir_tree, show_vol, show_path, exts)) {
					refresh_state = RefreshState::Requested;
					// show_spinner();
				}
			} break;

			case RefreshState::Requested: {
				auto message = file_storage.get_message().message_type;
				if (message == FileStorageProxy::DirEntriesChanged) {
					pr_dbg("Reloading %d:%s\n", show_vol, show_path.c_str());
					refresh_roller(dir_tree);
					refresh_state = RefreshState::Idle;

				} else if (message == FileStorageProxy::DirEntriesNoChange) {
					// hide_spinner();
					pr_dbg("No change to %d:%s\n", show_vol, show_path.c_str());
					refresh_state = RefreshState::Idle;
				}
			} break;
		}
	}

	void hide() {
		lv_hide(ui_FileBrowserCont);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

private:
	void refresh_roller(DirTree<FileEntry> &root) {
		std::string roller_text;

		for (auto const &subdir : root.dirs) {
			pr_dbg("%s:\n", subdir.name.c_str());
			roller_text += Gui::yellow_text(subdir.name);
			roller_text += "\n";
		}

		for (auto const &file : root.files) {
			pr_dbg("%s - %u %u\n", file.filename.c_str(), file.filesize, file.timestamp);
			roller_text += file.filename;
			roller_text += "\n";
		}

		// remove trailing \n
		if (roller_text.length() > 0)
			roller_text.pop_back();

		lv_roller_set_options(ui_FileBrowserRoller, roller_text.c_str(), LV_ROLLER_MODE_NORMAL);
	}

	FileStorageProxy &file_storage;
	NotificationQueue &notify_queue;
	PageList &page_list;

	lv_group_t *group;

	std::function<void(char *)> action;

	std::string exts;

	bool visible = false;

	enum class RefreshState { Idle, TryingToRequest, Requested };
	RefreshState refresh_state{RefreshState::TryingToRequest};

	uint32_t last_refresh_check_tm = 0;

	Volume show_vol = Volume::USB;
	std::string show_path = "";
};
} // namespace MetaModule
