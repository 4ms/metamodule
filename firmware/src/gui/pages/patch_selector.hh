#pragma once
#include "fs/dir_entry_kind.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/helpers/lvgl_mem_helper.hh"
#include "gui/helpers/lvgl_string_helper.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

//TODO: keep our place in the list when changing media (if possible)
//Keep track of hovered_patch_id/vol
//And restore that after a refresh:
struct PatchSelectorPage : PageBase {
	struct EntryInfo {
		DirEntryKind kind;
		Volume vol;
		std::string path;
		std::string name;
	};

	PatchSelectorPage(PatchInfo info)
		: PageBase{info, PageId::PatchSel} {

		init_bg(ui_PatchSelectorPage);

		lv_group_add_obj(group, ui_PatchListRoller);
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_select_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_scroll_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_FOCUS_KEY);
	}

	void prepare_focus() override {
		state = State::TryingToRequestPatchList;
		lv_obj_add_flag(ui_waitspinner, LV_OBJ_FLAG_HIDDEN);
		lv_group_set_editing(group, true);

		auto patchname = patch_playloader.cur_patch_name(); // auto patchplaying_idx = patch_storage
		if (patchname.length() == 0) {
			lv_label_set_text(ui_NowPlayingName, "none");
			lv_label_set_text(ui_LoadMeter, "");
		} else {
			lv_label_set_text_fmt(ui_NowPlayingName, "%.31s", patchname.c_str());
			lv_label_set_text_fmt(ui_LoadMeter, "%d%%", metaparams.audio_load);
		}
	}

	// PatchDir *displayed_dir;
	//PatchDir *first_valid_dir(PatchDirList &patchfiles) {
	//	// try volume roots
	//	for (auto &root : patchfiles.vol_root) {
	//		if (root.files.size() > 0) {
	//			return &root;
	//		}
	//	}
	//	//try any dir on any volume
	//	for (auto &root : patchfiles.vol_root) {
	//		for (auto &dir : root.dirs) {
	//			if (dir.files.size() > 0) {
	//				return &root;
	//			}
	//		}
	//	}
	//	pr_err("No files found on any volume, in any directory\n");
	//	return nullptr;
	//}

	void refresh_patchlist(PatchDirList &patchfiles) {
		// populate side bar with volumes and dirs
		populate_sub_dir_panel(patchfiles);

		// populate roller
		std::string roller_text;
		roller_item_infos.clear();

		for (auto [vol, vol_name, root] : zip(patchfiles.vols, patchfiles.vol_name, patchfiles.vol_root)) {
			if (root.files.size() == 0 && root.dirs.size() == 0)
				continue;

			roller_text += "[" + std::string(vol_name) + "]";
			if (root.files.size() > 0)
				roller_text += " (" + std::to_string(root.files.size()) + " files)";
			if (root.dirs.size() > 0)
				roller_text += " (" + std::to_string(root.dirs.size()) + " dirs)";
			roller_text += "\n";

			roller_item_infos.push_back({DirEntryKind::Dir, vol, "", ""});
			add_all_files_to_roller(vol, roller_text, " ", root);

			// Subdirs:
			for (auto &subdir : root.dirs) {
				roller_text += " " + subdir.name + " (" + std::to_string(subdir.files.size()) + " files)\n";
				roller_item_infos.push_back({DirEntryKind::Dir, vol, subdir.name, ""});
				add_all_files_to_roller(vol, roller_text, "  ", subdir);
			}
		}
		// remove trailing \n
		if (roller_text.length() > 0)
			roller_text.pop_back();

		lv_roller_set_options(ui_PatchListRoller, roller_text.c_str(), LV_ROLLER_MODE_NORMAL);
	}

	void populate_sub_dir_panel(PatchDirList &patchfiles) {
		// populate side bar with volumes and dirs
		for (auto [vol_label, root] : zip(vol_labels, patchfiles.vol_root)) {

			// Delete existing dir labels (except first one, which is the volume root)
			if (auto num_children = lv_obj_get_child_cnt(vol_label); num_children > 1) {
				for (unsigned i = 1; i < num_children; i++) {
					pr_dbg("Deleting child %d of %p\n", i, vol_label);
					lv_obj_del_async(lv_obj_get_child(vol_label, i));
				}
			}

			// No need to scan if no files or dirs: disable it
			if (root.files.size() == 0 && root.dirs.size() == 0) {
				lv_disable(vol_label);
				lv_disable_all_children(vol_label);
				lv_obj_clear_state(vol_label, LV_STATE_CHECKED);
				continue;
			}

			for (auto &dir : root.dirs) {
				add_sub_dir_to_panel(dir, vol_label);
			}

			lv_enable(vol_label);
			lv_enable_all_children(vol_label);
		}
	}

	void add_sub_dir_to_panel(PatchDir &dir, lv_obj_t *vol_label) {
		auto *name_label = lv_label_create(vol_label);
		lv_obj_set_size(name_label, LV_PCT(100), 20);
		lv_obj_set_style_pad_all(name_label, 0, LV_PART_MAIN);
		lv_obj_set_style_pad_left(name_label, 15, LV_PART_MAIN);
		lv_label_set_text_fmt(name_label, "%s", dir.name.c_str());
		lv_label_set_long_mode(name_label, LV_LABEL_LONG_CLIP);

		lv_obj_set_style_bg_color(name_label, Gui::orange_highlight, LV_STATE_CHECKED);
		lv_obj_set_style_bg_opa(name_label, LV_OPA_100, LV_STATE_CHECKED);
	}

	void add_all_files_to_roller(Volume vol, std::string &roller_text, std::string prefix, PatchDir &dir) {
		for (auto &p : dir.files) {
			roller_text += prefix + std::string{p.patchname} + "\n";
			roller_item_infos.emplace_back(EntryInfo{DirEntryKind::File, vol, dir.name, p.filename});
		}
	}

	void refresh_volume_labels() {
		auto idx = lv_roller_get_selected(ui_PatchListRoller);
		if (idx >= roller_item_infos.size())
			return;

		auto &entry = roller_item_infos[idx];

		for (auto [vol, vol_label] : zip(vols, vol_labels)) {
			if (vol != entry.vol)
				continue;

			auto num_children = lv_obj_get_child_cnt(vol_label);
			for (unsigned i = 0; i < num_children; i++) {
				auto obj = lv_obj_get_child(vol_label, i);
				const char *txt = (i == 0) ? "" : lv_label_get_text(obj);
				if (txt == nullptr)
					continue;
				if (strcmp(txt, entry.path.c_str()) == 0) {
					if (last_checked)
						lv_obj_clear_state(last_checked, LV_STATE_CHECKED);
					last_checked = obj;
					lv_obj_add_state(obj, LV_STATE_CHECKED);
					break;
				}
			}
		}
	}

	void update() override {

		if (metaparams.meta_buttons[0].is_just_released()) {
			if (lv_group_get_focused(group) == ui_PatchListRoller)
				lv_group_focus_obj(ui_DrivesPanel);
			else
				page_list.request_last_page();
		}

		update_spinner();

		switch (state) {
			case State::Idle: {
				//periodically check if patchlist needs updating:
				uint32_t now = lv_tick_get();
				if (now - last_refresh_check_tm > 1000) { //poll media once per second
					last_refresh_check_tm = now;
					state = State::TryingToRequestPatchList;

					lv_label_set_text_fmt(ui_LoadMeter, "%d%%", metaparams.audio_load);
				}
			} break;

			case State::TryingToRequestPatchList:
				if (patch_storage.request_patchlist()) {
					state = State::RequestedPatchList;
					show_spinner();
				}
				break;

			case State::RequestedPatchList: {
				auto message = patch_storage.get_message().message_type;
				if (message == FileStorageProxy::PatchListChanged) {
					state = State::ReloadingPatchList;
				} else if (message == FileStorageProxy::PatchListUnchanged) {
					hide_spinner();
					state = State::Idle;
				}
				//else other messages ==> error? repeat request? idle?
			} break;

			case State::ReloadingPatchList:
				//TODO: use our member var patch_list, not patch_storage
				refresh_patchlist(patch_storage.get_patch_list());
				refresh_volume_labels();
				hide_spinner();
				state = State::Idle;
				break;

			case State::TryingToRequestPatchData:
				if (patch_storage.request_viewpatch(selected_patch)) {
					state = State::RequestedPatchData;
					show_spinner();
				}
				break;

			case State::RequestedPatchData: {
				auto message = patch_storage.get_message();

				if (message.message_type == FileStorageProxy::PatchDataLoaded) {
					// Try to parse the patch and open the PatchView page
					if (patch_storage.parse_view_patch(message.bytes_read)) {
						auto view_patch = patch_storage.get_view_patch();
						pr_dbg("Parsed patch: %.31s\n", view_patch.patch_name.data());

						args.patch_loc = selected_patch;
						args.patch_loc_hash = PatchLocHash{selected_patch};
						page_list.request_new_page(PageId::PatchView, args);

						state = State::Closing;
						hide_spinner();

					} else {
						pr_warn("Error parsing %s\n", selected_patch.filename.c_str());
						state = State::Idle;
						hide_spinner();
					}
				} else if (message.message_type == FileStorageProxy::PatchDataLoadFail) {
					pr_warn("Error loading patch %s\n", selected_patch.filename.c_str());
					state = State::Idle;
					lv_group_set_editing(group, true);
					hide_spinner();
					//TODO: handle error... try reloading patch list?
				}
			} break;

			case State::Closing:
				break;
		}
	}

	void blur() override {
		hide_spinner();
	}

	void show_spinner() {
		// Schedule a time to show spinner if there's not already one scheduled
		if (!spinner_show_tm)
			spinner_show_tm = get_time() + spinner_lag_ms;
	}

	void update_spinner() {
		if (spinner_show_tm && get_time() >= spinner_show_tm) {
			lv_show(ui_waitspinner);
		}
	}

	void hide_spinner() {
		spinner_show_tm = 0;
		lv_hide(ui_waitspinner);
	}

	static void patchlist_scroll_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorPage *>(event->user_data);
		page->refresh_volume_labels();
	}

	static void patchlist_select_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorPage *>(event->user_data);

		auto idx = lv_roller_get_selected(ui_PatchListRoller);
		pr_dbg("Clicked roller idx %d\n", idx);

		auto selected_patch = page->get_roller_item_patchloc(idx);
		if (selected_patch) {
			page->selected_patch = *selected_patch;
			page->state = State::TryingToRequestPatchData;
			pr_dbg("Clicked vol %d, patch %s\n", (uint32_t)selected_patch->vol, selected_patch->filename.c_str());
		} else {
			pr_dbg("Clicked index %d, no action\n", idx);
			//Do nothing? Close/open directory?
		}
	}

	std::optional<PatchLocation> get_roller_item_patchloc(uint32_t selected_index) {
		std::optional<PatchLocation> p{};

		if (selected_index < roller_item_infos.size()) {
			auto &entry = roller_item_infos[selected_index];
			if (entry.kind == DirEntryKind::File) {
				p = PatchLocation{};
				p->vol = entry.vol;
				p->filename.copy(std::string(entry.path + "/" + entry.name));
			}
		} else
			pr_err("Bad roller index: %d, max is %zu\n", selected_index, roller_item_infos.size());
		return p;
	}

private:
	PatchLocation selected_patch{"", Volume::NorFlash};

	std::array<lv_obj_t *, 3> vol_labels = {ui_USBVolCont, ui_SDVolCont, ui_FlashVolCont};
	std::array<Volume, 3> vols = {Volume::USB, Volume::SDCard, Volume::NorFlash};
	std::vector<EntryInfo> roller_item_infos;
	lv_obj_t *last_checked = nullptr;

	static constexpr uint32_t spinner_lag_ms = 200;
	uint32_t spinner_show_tm = 0;

	enum class State {
		Idle,

		TryingToRequestPatchList,
		RequestedPatchList,
		ReloadingPatchList,

		TryingToRequestPatchData,
		RequestedPatchData,

		Closing,
	} state{State::TryingToRequestPatchList};

	uint32_t last_refresh_check_tm = 0;
};

} // namespace MetaModule
