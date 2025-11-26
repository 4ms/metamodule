#pragma once
#include "fs/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/slsexport/filebrowser/ui.h"
#include "gui/styles.hh"
#include "patch_file/file_storage_proxy.hh"
#include "static_buffers.hh"
#include <filesystem>
#include <functional>

namespace MetaModule
{

struct FileBrowserDialog {
	FileBrowserDialog(FileStorageProxy &file_storage, NotificationQueue &notify_queue)
		: file_storage{file_storage} // , notify_queue{notify_queue}
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
			exts = "";
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

	// Flags the browser to be shown.
	// Safe to call from audio or AsyncThread context
	void show(std::string_view start_dir, const std::function<void(char *)> action) {
		should_show = true;
		this->action = action;
		should_show_path.copy(start_dir);
	}

	// Actually shows the browser. Only called in the GUI context
	void do_show() {
		if (auto indev = lv_indev_get_next(nullptr))
			parent_group = indev->group;

		lv_group_activate(group);
		lv_group_set_editing(group, true);
		lv_obj_set_parent(ui_FileBrowserCont, lv_layer_top());
		lv_show(ui_FileBrowserCont);

		visible = true;

		refresh_state = RefreshState::TryingToRequest;

		auto start_dir = std::string_view{should_show_path};

		if (start_dir.length()) {
			auto [start_path, start_vol] = split_volume(start_dir);
			show_path = start_path;
			show_vol = start_vol;

			if (!show_path.ends_with("/")) {
				show_path += "/";
			}

		} else {
			if (show_path == "") {
				show_vol = Volume::MaxVolumes;
			}

			else if (!show_path.ends_with("/"))
			{
				show_path = std::filesystem::path(show_path).parent_path().string() + "/";
			}
		}
	}

	void back_event() {
		// Try going back a dir
		if (pop_dir()) {
			refresh_state = RefreshState::TryingToRequest;
			return; //consumed
		}

		// Module crashes if given a nullptr, even though that's what Rack does
		// if (action)
		// 	action(nullptr);

		hide();
	}

	void update() {
		if (should_show) {
			do_show();
			should_show = false;
		}

		switch (refresh_state) {
			case RefreshState::Idle: {
				//nothing
			} break;

			case RefreshState::TryingToRequest: {
				if (file_storage.request_dir_entries(&StaticBuffers::dir_tree, show_vol, show_path, exts)) {
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
					auto ok = pop_dir();
					if (ok)
						refresh_state = RefreshState::TryingToRequest;
					else {
						lv_roller_set_options(ui_FileBrowserRoller, TextBack.data(), LV_ROLLER_MODE_NORMAL);
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
		return should_show || visible;
	}

private:
	void refresh_roller() {
		auto path = volstr(show_vol) + show_path;
		lv_label_set_text(ui_FileBrowserPathLabel, path.c_str());

		std::string roller_text;
		unsigned num_items = 0;

		if (show_vol != Volume::MaxVolumes) {
			roller_text.append("< Back\n");

			if (dir_mode) {
				roller_text.append(Gui::blue_text(TextSelectFolder) + std::string("\n"));
			}
		}

		for (auto const &subdir : StaticBuffers::dir_tree.dirs) {
			// Workaround for string alignment differences in M4 vs A7?
			StaticString<255> subdirname;
			subdirname.copy(subdir.name);
			roller_text.append(Gui::yellow_text(subdirname));
			roller_text.append("/\n"); // dirs end in a slash
			num_items++;
		}

		for (auto const &file : StaticBuffers::dir_tree.files) {
			// Workaround for string alignment differences in M4 vs A7?
			StaticString<255> filename;
			filename.copy(file.filename);
			roller_text.append(std::string_view(filename));
			roller_text.append("\n");
			num_items++;
		}

		// remove trailing \n
		if (roller_text.length() > 0)
			roller_text.pop_back();
		else {
			// Empty
			roller_text = "No disks detected";
		}

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

		show_path = std::filesystem::path(show_path).parent_path().string();

		return true;
	}

	void push_dir(std::string_view dir) {
		auto t = std::filesystem::path(show_path) / std::filesystem::path(dir);
		show_path = t.string();
	}

	static std::string volstr(Volume vol) {
		auto str = volume_string(vol);
		if (str == "" || str == "ram:/")
			return "Disks:";
		else
			return std::string(str);
	}

	void choose(std::string_view file) {
		push_dir(file);
		std::string fullpath = volstr(show_vol) + show_path;

		// Allocate some chars:
		char *path = strdup(fullpath.data());
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

		if (text == TextBack) {
			pop_dir();

		} else if (text == TextNoDisksFound) {
			hide();

		} else if (text.ends_with(":/")) {
			// Clicked a volume:
			show_vol = string_to_volume(text);
			show_path = "";
		} else if (text.ends_with("/")) {
			// Clicked a dir:
			push_dir(text);
		} else if (text.starts_with(TextSelectFolder)) {
			// Selected a folder
			choose("");
		} else {
			// Selected a file
			choose(dir_mode ? "" : text);
		}

		refresh_state = RefreshState::TryingToRequest;
	}

	static void roller_click_cb(lv_event_t *event) {
		if (auto page = static_cast<FileBrowserDialog *>(event->user_data))
			page->roller_click();
	}

	FileStorageProxy &file_storage;

	lv_group_t *group;
	lv_group_t *parent_group = nullptr;

	// Flag to indicate a non-GUI thread requested we show the browser
	bool should_show = false;
	StaticString<255> should_show_path = "";

	std::function<void(char *)> action;

	std::string exts;

	bool visible = false;

	enum class RefreshState { Idle, TryingToRequest, Requested };
	RefreshState refresh_state{RefreshState::TryingToRequest};

	Volume show_vol = Volume::MaxVolumes;
	std::string show_path = "";
	bool dir_mode = false;

	static constexpr std::string_view TextSelectFolder = "[Select this folder]";
	static constexpr std::string_view TextBack = "< Back";
	static constexpr std::string_view TextNoDisksFound = "No disks found";
};
} // namespace MetaModule
