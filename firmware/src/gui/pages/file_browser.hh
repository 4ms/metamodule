#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/slsexport/filebrowser/ui.h"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include "patch_file/file_storage_proxy.hh"

namespace MetaModule
{

struct FileBrowserDialog {
	FileBrowserDialog(FileStorageProxy &file_storage,
					  NotificationQueue &notify_queue,
					  PatchSelectorSubdirPanel &subdir_panel,
					  PageList &page_list)
		: file_storage{file_storage}
		, notify_queue{notify_queue}
		, subdir_panel{subdir_panel}
		, page_list{page_list}
		, group(lv_group_create()) {

		lv_group_add_obj(group, ui_FileBrowserRoller);
		lv_hide(ui_FileBrowserCont);
	}

	void prepare_focus(lv_group_t *parent_group) {
		group = parent_group;
		lv_label_set_text(ui_FileBrowserTitle, "Open a file\n");
		exts = "";
	}

	void set_title(std::string_view title) {
		if (title.data() && title.length())
			lv_label_set_text(ui_FileBrowserTitle, title.data());
	}

	// Extension are comma-separated list
	void filter_extensions(std::string_view extensions) {
		exts = extensions;
	}

	void show(std::string_view start_dir, const std::function<void(char *)> action) {
		mode = Mode::MainPanel;
		refresh_state = RefreshState::TryingToRequest;
		lv_obj_set_parent(ui_FileBrowserCont, lv_layer_top());
		lv_show(ui_FileBrowserCont);
	}

	bool consume_back() {
		if (mode == Mode::DrivePanel) {
			mode = Mode::Hidden;
			return true;
		}
		if (mode == Mode::MainPanel) {
			mode = Mode::DrivePanel;
			return true;
		}

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
				auto &cur_tree = cur_refresh_vol == Volume::USB ? usb_dir_tree : sd_dir_tree;
				if (file_storage.request_dir_entries(&cur_tree, cur_refresh_vol, exts)) {
					pr_dbg("Made request for %d\n", cur_refresh_vol);
					refresh_state = RefreshState::Requested;
					// show_spinner();
				}
			} break;

			case RefreshState::Requested: {
				auto message = file_storage.get_message().message_type;
				if (message == FileStorageProxy::DirEntriesSuccess) {
					refresh_state = RefreshState::Reloading;

				} else if (message == FileStorageProxy::DirEntriesFailed) {
					// hide_spinner();
					pr_dbg("Request for %d failed\n", cur_refresh_vol);
					cur_refresh_vol = cur_refresh_vol == Volume::USB ? Volume::SDCard : Volume::USB;
					refresh_state = RefreshState::Idle;
				}
			} break;

			case RefreshState::Reloading:
				pr_dbg("Reloading %d\n", cur_refresh_vol);
				// subdir_panel.populate(dir_tree);
				subdir_panel.hide_recent_files();
				// hide_spinner();
				subdir_panel.focus();
				refresh_roller(usb_dir_tree);
				refresh_roller(sd_dir_tree);
				refresh_state = RefreshState::Idle;

				cur_refresh_vol = cur_refresh_vol == Volume::USB ? Volume::SDCard : Volume::USB;
				break;
		}
	}

	void hide() {
		lv_hide(ui_FileBrowserCont);
		mode = Mode::Hidden;
	}

	bool is_visible() {
		return mode != Mode::Hidden;
	}

	void refresh_roller(DirTree<FileEntry> &root) {
		for (auto const &f : root.files) {
			pr_dbg("%s - %u %u\n", f.filename, f.filesize, f.timestamp);
		}
		for (auto const &d : root.dirs) {
			pr_dbg("%s:\n", d.name.c_str());
			for (auto const &f : usb_dir_tree.files) {
				pr_dbg(" %s - %u %u\n", f.filename, f.filesize, f.timestamp);
			}
		}
	}

private:
	FileStorageProxy &file_storage;
	NotificationQueue &notify_queue;
	PatchSelectorSubdirPanel &subdir_panel;
	PageList &page_list;

	DirTree<FileEntry> usb_dir_tree;
	DirTree<FileEntry> sd_dir_tree;

	lv_group_t *group;

	std::string exts;

	enum class Mode { Hidden, MainPanel, DrivePanel };
	Mode mode = Mode::Hidden;

	enum class RefreshState {
		Idle,
		TryingToRequest,
		Requested,
		Reloading
	} refresh_state{RefreshState::TryingToRequest};
	Volume cur_refresh_vol = Volume::USB;

	uint32_t last_refresh_check_tm = 0;
};
} // namespace MetaModule
