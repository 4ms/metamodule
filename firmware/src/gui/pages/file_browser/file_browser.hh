#pragma once
#include "fs/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/filebrowser/ui.h"
#include "gui/styles.hh"
#include "patch_file/file_storage_proxy.hh"
#include <filesystem>
#include <functional>

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

		lv_obj_set_width(ui_FileBrowserPathLabel, 300);
		lv_label_set_long_mode(ui_FileBrowserPathLabel, LV_LABEL_LONG_SCROLL);
	}

	void set_title(std::string_view title) {
		if (title.data() && strlen(title.data()))
			lv_label_set_text(ui_FileBrowserTitle, title.data());
		else
			lv_label_set_text(ui_FileBrowserTitle, "Open a file\n");
	}

	// Extension filters are comma-separated list without dot or start: "wav, WAV, raw"
	void filter_extensions(std::string_view extensions) {
		if (extensions == "*/") {
			exts = "Dirs only";
			dir_mode = true;
			lv_label_set_text(ui_FileBrowserSubtitle, "Folders only:");
		} else {
			exts = extensions;
			dir_mode = false;

			if (extensions.contains("*.*"))
				lv_label_set_text(ui_FileBrowserSubtitle, "*.*");
			else
				lv_label_set_text(ui_FileBrowserSubtitle, extensions.data());
		}
	}

	void show(std::string_view start_dir, const std::function<void(char *)> action) {
		parent_group = lv_indev_get_act()->group;
		lv_group_activate(group);
		lv_group_set_editing(group, true);
		this->action = std::move(action);

		visible = true;

		refresh_state = RefreshState::TryingToRequest;

		if (start_dir.length()) {
			auto [start_path, start_vol] = split_volume(start_dir);
			show_path = start_path;
			show_vol = start_vol;

			if (!show_path.ends_with("/")) {
				show_path += "/";
			}

			pr_dbg("Showing browser. start_dir = %s => %s (vol %d)\n", start_dir.data(), show_path.c_str(), show_vol);
		} else {
			if (show_path == "") {
				show_vol = Volume::MaxVolumes;
			}

			else if (!show_path.ends_with("/"))
			{
				show_path = std::filesystem::path(show_path).parent_path().string() + "/";
				pr_dbg("Browser: Path did not end in /, using parent: %s\n", show_path.c_str());
			}

			pr_dbg("Showing browser. No path specified, using %s (vol %d)\n", show_path.c_str(), show_vol);
		}

		lv_obj_set_parent(ui_FileBrowserCont, lv_layer_top());
		lv_show(ui_FileBrowserCont);
	}

	bool consume_back() {
		if (action)
			action(nullptr);
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
					// pr_dbg("Reloading vol %d, path: '%s'\n", show_vol, show_path.c_str());
					refresh_roller();
					refresh_state = RefreshState::Idle;

				} else if (message == FileStorageProxy::DirEntriesFailed) {
					// hide_spinner();
					pr_dbg("Failed to display dir %d:%s\n", show_vol, show_path.c_str());
					auto ok = pop_dir();
					if (ok)
						refresh_state = RefreshState::TryingToRequest;
					else {
						lv_roller_set_options(ui_FileBrowserRoller, "< Back", LV_ROLLER_MODE_NORMAL);
						lv_roller_set_selected(ui_FileBrowserRoller, 0, LV_ANIM_OFF);
						refresh_state = RefreshState::Idle;
					}
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
		unsigned num_items = 0;

		roller_text.append("< Back\n");

		if (dir_mode) {
			roller_text.append(Gui::blue_text("[Select this folder]") + std::string("\n"));
		}

		for (auto const &subdir : dir_tree.dirs) {
			// pr_dbg("Vol %s:\n", subdir.name.c_str());
			roller_text += Gui::yellow_text(subdir.name);
			roller_text += "/\n"; //dirs end in a slash
			num_items++;
		}

		for (auto const &file : dir_tree.files) {
			// pr_dbg("File %s - %u %u\n", file.filename.c_str(), file.filesize, file.timestamp);
			roller_text += file.filename;
			roller_text += "\n";
			num_items++;
		}

		// remove trailing \n
		if (roller_text.length() > 0)
			roller_text.pop_back();

		lv_roller_set_options(ui_FileBrowserRoller, roller_text.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_FileBrowserRoller, num_items > 0 ? 1 : 0, LV_ANIM_OFF);
	}

	bool pop_dir() {
		if (show_vol == Volume::MaxVolumes)
			return false; // not valid

		if (show_path.back() == '/') {
			show_path.back() = '\0';
		}

		if (show_path == "" || show_path == "/") {
			show_vol = Volume::MaxVolumes;
			show_path = "";
		}

		pr_dbg("pop_dir(): '%s' => ", show_path.c_str());
		show_path = std::filesystem::path(show_path).parent_path().string();
		pr_dbg("'%s'\n", show_path.c_str());

		return true;

		// auto lastslash = show_path.rfind('/');
		// if (lastslash != std::string::npos) {
		// 	show_path = show_path.substr(0, lastslash);
		// } else {
		// 	show_vol = Volume::MaxVolumes;
		// 	show_path = "";
		// }
	}

	void push_dir(std::string_view dir) {
		show_path = std::filesystem::path(show_path) / dir;
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

		return Volume::MaxVolumes;
	}

	void choose(std::string_view file) {
		push_dir(file);
		std::string fullpath = volstr(show_vol) + show_path;

		// Allocate some chars:
		char *path = strndup(fullpath.data(), fullpath.size());
		// Rack specifies that the caller will free() path in action():
		if (action)
			action(path);

		hide();
	}

	void roller_click() {
		std::string text;
		text.resize(256);
		lv_roller_get_selected_str(ui_FileBrowserRoller, text.data(), (uint32_t)text.max_size());
		text.resize(strlen(text.data()));

		trim_color_string(text);

		if (text == "< Back") {
			pop_dir();

		} else if (text.ends_with(":/")) {
			// Clicked a volume:
			show_vol = strvol(text);
			show_path = "";

		} else if (text.ends_with("/")) {
			// Clicked a dir:
			push_dir(text);

		} else if (text.starts_with("[Select this folder]")) {
			// Selected a folder
			choose("");

		} else {
			// Selected a file
			choose(text);
		}

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
	bool dir_mode = false;
};
} // namespace MetaModule
