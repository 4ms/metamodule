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

		lv_obj_add_event_cb(ui_FileBrowserRoller, roller_click_cb, LV_EVENT_CLICKED, this);
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
		parent_group = lv_indev_get_act()->group;
		lv_group_activate(group);
		lv_group_set_editing(group, true);
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
				//nothing
			} break;

			case RefreshState::TryingToRequest: {
				if (file_storage.request_dir_entries(&dir_tree, show_vol, show_path, exts)) {
					refresh_state = RefreshState::Requested;
					// show_spinner();
				}
			} break;

			case RefreshState::Requested: {
				auto message = file_storage.get_message().message_type;
				if (message == FileStorageProxy::DirEntriesSuccess) {
					pr_dbg("Reloading vol %d, path: '%s'\n", show_vol, show_path.c_str());
					refresh_roller();
					refresh_state = RefreshState::Idle;

				} else if (message == FileStorageProxy::DirEntriesFailed) {
					// hide_spinner();
					pr_dbg("Failed to load %d:%s\n", show_vol, show_path.c_str());
					lv_roller_set_options(
						ui_FileBrowserRoller, "< Back\nCannot display directory", LV_ROLLER_MODE_NORMAL);
					refresh_state = RefreshState::Idle;
				}
				lv_group_set_editing(group, true);
			} break;
		}
	}

	void hide() {
		if (parent_group)
			lv_group_activate(parent_group);

		lv_hide(ui_FileBrowserCont);
		visible = false;
	}

	bool is_visible() {
		return visible;
	}

private:
	void refresh_roller() {
		auto path = volstr(show_vol) + show_path;
		lv_label_set_text(ui_FileBrowserPathLabel, path.c_str());

		std::string roller_text;

		roller_text.append("< Back\n");

		for (auto const &subdir : dir_tree.dirs) {
			pr_dbg("Vol %s:\n", subdir.name.c_str());
			roller_text += Gui::yellow_text(subdir.name);
			roller_text += "/\n"; //dirs end in a slash
		}

		for (auto const &file : dir_tree.files) {
			pr_dbg("File %s - %u %u\n", file.filename.c_str(), file.filesize, file.timestamp);
			roller_text += file.filename;
			roller_text += "\n";
		}

		// remove trailing \n
		if (roller_text.length() > 0)
			roller_text.pop_back();

		lv_roller_set_options(ui_FileBrowserRoller, roller_text.c_str(), LV_ROLLER_MODE_NORMAL);
	}

	void pop_dir() {
		if (show_path.back() == '/') {
			show_path.back() = '\0';
		}

		auto lastslash = show_path.rfind('/');
		if (lastslash != std::string::npos) {
			show_path = show_path.substr(0, lastslash);
		} else {
			show_vol = Volume::MaxVolumes;
			show_path = "";
		}
	}

	void push_dir(std::string_view dir) {
		show_path += std::string(dir);
	}

	std::string volstr(Volume vol) {
		if (vol == Volume::USB)
			return "usb:/";
		else if (vol == Volume::SDCard)
			return "sdc:/";
		else
			return "Disks:";
	}

	Volume strvol(std::string_view str) {
		if (str.starts_with("usb:") || str.starts_with("USB:"))
			return Volume::USB;

		if (str.starts_with("sdc:") || str.starts_with("SD Card:"))
			return Volume::SDCard;

		// if (str.starts_with("ram:"))
		// 	return Volume::RamDisk;
		// if (str.starts_with("nor:"))
		// 	return Volume::NorFlash;

		return Volume::MaxVolumes;
	}

	void choose(std::string_view file) {
		push_dir(file);
		std::string fullpath = volstr(show_vol) + show_path;

		char *path = strndup(fullpath.data(), fullpath.size());
		// Rack and Cardinal specify that the caller will free() path
		action(path);

		hide();
	}

	void roller_click() {
		std::string text;
		text.resize(256);
		lv_roller_get_selected_str(ui_FileBrowserRoller, text.data(), text.max_size());
		text.resize(strlen(text.data()));

		pr_dbg("Path: '%s', click item %d: '%s'\n",
			   show_path.c_str(),
			   lv_roller_get_selected(ui_FileBrowserRoller),
			   text.c_str());

		// Trim color
		if (text.starts_with("^")) {
			//  "^123456 Text^ "
			//   ________....
			//    8 char
			text = text.substr(8);
			if (auto endpos = text.find('^'); endpos != text.npos) {
				if (text[endpos + 1] == ' ')
					text.erase(endpos, 2);
				else
					text.erase(endpos, 1);
			}
			// text = text.substr(8, text.length() - 11);
			pr_dbg("Trimmed: '%s' (%d)\n", text.c_str(), text.length());
		}

		if (text == "< Back") {
			pop_dir();
		} else if (text.ends_with(":/")) {
			show_vol = strvol(text);
			show_path = "";
			pr_dbg("Set vol: %d\n", show_vol);
		} else if (text.ends_with("/")) {
			push_dir(text);
			pr_dbg("Push dir=>'%s'\n", show_path.c_str());
		} else {
			choose(text);
		}

		pr_dbg("=>path: '%s'\n", show_path.c_str());
		refresh_state = RefreshState::TryingToRequest;
	}

	static void roller_click_cb(lv_event_t *event) {
		auto page = static_cast<FileBrowserDialog *>(event->user_data);
		if (!page)
			return;
		page->roller_click();
	}

	FileStorageProxy &file_storage;
	NotificationQueue &notify_queue;
	PageList &page_list;

	lv_group_t *group;
	lv_group_t *parent_group = nullptr;

	std::function<void(char *)> action;

	std::string exts;

	bool visible = false;

	enum class RefreshState { Idle, TryingToRequest, Requested };
	RefreshState refresh_state{RefreshState::TryingToRequest};

	Volume show_vol = Volume::MaxVolumes;
	std::string show_path = "";
};
} // namespace MetaModule
