#pragma once
#include "fs/dir_entry_kind.hh"
#include "gui/helpers/dir_entry_info.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/helpers/lvgl_mem_helper.hh"
#include "gui/helpers/lvgl_string_helper.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {

	PatchSelectorPage(PatchContext info, PatchSelectorSubdirPanel &subdir_panel)
		: PageBase{info, PageId::PatchSel}
		, subdir_panel{subdir_panel} {

		init_bg(ui_PatchSelectorPage);

		lv_group_add_obj(group, ui_PatchListRoller);
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_click_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_scroll_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_FOCUS_KEY);
		lv_obj_clear_state(ui_Flashbut, LV_STATE_FOCUSED);
	}

	void prepare_focus() override {
		gui_state.new_cable = std::nullopt;

		state = State::TryingToRequestPatchList;
		hide_spinner();
		blur_subdir_panel();

		lv_group_set_editing(group, true);
		lv_group_set_wrap(group, false);

		auto playing_patch = patch_storage.get_playing_patch();
		if (!playing_patch || playing_patch->patch_name.length() == 0) {
			lv_label_set_text(ui_NowPlayingName, "none");
			lv_label_set_text(ui_LoadMeter, "");
		} else {
			lv_label_set_text_fmt(ui_NowPlayingName, "%.31s", playing_patch->patch_name.c_str());
			lv_label_set_text_fmt(ui_LoadMeter, "%d%%", metaparams.audio_load);
		}

		setup_subdir_panel();
	}

	void setup_subdir_panel() {
		subdir_panel.set_parent(ui_PatchSelectorPage, 1);
		subdir_panel.focus_cb = [this](Volume vol, std::string_view dir) {
			for (auto [i, entry] : enumerate(roller_item_infos)) {
				if (entry.path == dir && entry.vol == vol) {
					lv_roller_set_selected(ui_PatchListRoller, i + 1, LV_ANIM_ON);
					break;
				}
			}
		};
		subdir_panel.click_cb = [this](Volume vol, std::string_view dir) {
			blur_subdir_panel();
		};

		refresh_subdir_panel();
	}

	void refresh_subdir_panel() {
		auto idx = lv_roller_get_selected(ui_PatchListRoller);
		if (idx < roller_item_infos.size())
			subdir_panel.refresh(roller_item_infos[idx]);
	}

	void refresh_patchlist(PatchDirList &patchfiles) {
		subdir_panel.populate(patchfiles);
		populate_roller(patchfiles);
	}

	void blur_subdir_panel() {
		lv_obj_clear_state(ui_DrivesPanel, LV_STATE_FOCUSED);
		lv_obj_clear_state(ui_PatchListRoller, LV_STATE_DISABLED);
		lv_group_focus_obj(ui_PatchListRoller);

		if (group) {
			lv_group_activate(group);
			lv_group_set_editing(group, true);
		}

		subdir_panel.blur();
	}

	void populate_roller(PatchDirList &patchfiles) {
		// Save current selection
		std::optional<EntryInfo> last_entry_info{};
		auto idx = lv_roller_get_selected(ui_PatchListRoller);
		if (idx < roller_item_infos.size()) {
			last_entry_info = roller_item_infos[idx];
		}

		roller_item_infos.clear();

		std::string roller_text;
		for (auto [vol, vol_name, root] : zip(patchfiles.vols, patchfiles.vol_name, patchfiles.vol_root)) {
			if (root.files.size() == 0 && root.dirs.size() == 0)
				continue;

			roller_text += format_volume_name(vol_name, root);

			roller_item_infos.push_back({DirEntryKind::Dir, vol, "", ""});
			add_all_files_to_roller(vol, roller_text, " ", root);

			// Subdirs:
			for (auto &subdir : root.dirs) {
				if (subdir.files.size()) {
					roller_text += format_subdir_name(subdir);
					roller_item_infos.push_back({DirEntryKind::Dir, vol, subdir.name, ""});
					add_all_files_to_roller(vol, roller_text, "  ", subdir);
				}
			}
		}
		// remove trailing \n
		if (roller_text.length() > 0)
			roller_text.pop_back();

		auto roller_label = lv_obj_get_child(ui_PatchListRoller, 0);
		lv_label_set_recolor(roller_label, true);

		lv_roller_set_options(ui_PatchListRoller, roller_text.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_PatchListRoller, 1, LV_ANIM_OFF);

		// Try to find the previous select in the new set of data
		if (last_entry_info) {
			std::optional<unsigned> match_idx{};
			for (auto [i, entry] : enumerate(roller_item_infos)) {
				if (entry == last_entry_info)
					match_idx = i;
			}

			if (match_idx)
				lv_roller_set_selected(ui_PatchListRoller, *match_idx, LV_ANIM_OFF);
		}
	}

	void add_all_files_to_roller(Volume vol, std::string &roller_text, std::string prefix, PatchDir &dir) {
		for (auto &p : dir.files) {
			roller_text += prefix + std::string{p.patchname} + "\n";
			roller_item_infos.emplace_back(EntryInfo{DirEntryKind::File, vol, dir.name, p.filename});
		}
	}

	std::string format_volume_name(StaticString<31> const &vol_name, PatchDir &root) {
		std::string roller_text = Gui::orange_highlight_html + std::string(vol_name) + "#";

		add_file_count(roller_text, root);
		add_dir_count(roller_text, root);

		roller_text += "\n";
		return roller_text;
	}

	std::string format_subdir_name(PatchDir const &subdir) {
		std::string roller_text;

		if (subdir.name.size() > 0) {
			roller_text += Gui::yellow_highlight_html + subdir.name + "#";
			add_file_count(roller_text, subdir);
		}
		roller_text += "\n";
		return roller_text;
	}

	void add_file_count(std::string &roller_text, PatchDir const &root) {
		if (root.files.size() > 0)
			roller_text += " (" + std::to_string(root.files.size()) + " files)";
	}

	void add_dir_count(std::string &roller_text, PatchDir const &root) {
		if (root.dirs.size() > 0)
			roller_text += " (" + std::to_string(root.dirs.size()) + " dirs)";
	}

	void update() override {

		if (metaparams.back_button.is_just_released()) {
			if (!lv_obj_has_state(ui_PatchListRoller, LV_STATE_DISABLED)) {
				lv_obj_add_state(ui_PatchListRoller, LV_STATE_DISABLED);
				lv_obj_clear_state(ui_PatchListRoller, LV_STATE_FOCUSED);
				subdir_panel.focus();
			} else {
				page_list.request_last_page();
			}
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
				if (patch_storage.request_patchlist(gui_state.force_refresh_vol)) {
					state = State::RequestedPatchList;
					show_spinner();
				}
				break;

			case State::RequestedPatchList: {
				auto message = patch_storage.get_message().message_type;
				if (message == FileStorageProxy::PatchListChanged) {
					gui_state.force_refresh_vol = std::nullopt;
					state = State::ReloadingPatchList;
				} else if (message == FileStorageProxy::PatchListUnchanged) {
					gui_state.force_refresh_vol = std::nullopt;
					hide_spinner();
					state = State::Idle;
				}
			} break;

			case State::ReloadingPatchList:
				//TODO: use our member var patch_list, not patch_storage
				refresh_patchlist(patch_storage.get_patch_list());
				refresh_subdir_panel();
				hide_spinner();
				state = State::Idle;
				break;

			case State::TryingToRequestPatchData:
				if (patch_storage.load_if_open(selected_patch)) {
					view_loaded_patch();
				} else if (patch_storage.request_load_patch(selected_patch)) {
					state = State::RequestedPatchData;
					show_spinner();
				}
				break;

			case State::RequestedPatchData: {
				auto message = patch_storage.get_message();

				if (message.message_type == FileStorageProxy::PatchDataLoaded) {
					// Try to parse the patch and open the PatchView page
					if (patch_storage.parse_loaded_patch(message.bytes_read)) {
						view_loaded_patch();
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

	void view_loaded_patch() {
		auto patch = patch_storage.get_view_patch();
		pr_trace("Parsed patch: %.31s\n", patch->patch_name.data());

		args.patch_loc_hash = PatchLocHash{selected_patch};
		page_list.request_new_page(PageId::PatchView, args);

		state = State::Closing;
	}

	void blur() final {
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
		static uint32_t prev_idx = 0;

		auto page = static_cast<PatchSelectorPage *>(event->user_data);
		auto idx = lv_roller_get_selected(ui_PatchListRoller);

		// Skip over dir entries:
		if (idx < page->roller_item_infos.size()) {
			auto &entry = page->roller_item_infos[idx];
			if (entry.kind == DirEntryKind::Dir) {
				auto max = lv_roller_get_option_cnt(ui_PatchListRoller) - 1;
				auto new_idx = (idx == 0) ? 1 : (idx == max) ? max - 1 : (idx > prev_idx) ? idx + 1 : idx - 1;
				lv_roller_set_selected(ui_PatchListRoller, new_idx, LV_ANIM_ON);
				prev_idx = new_idx;
			}
		}
		page->refresh_subdir_panel();
	}

	static void patchlist_click_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorPage *>(event->user_data);

		auto idx = lv_roller_get_selected(ui_PatchListRoller);

		auto selected_patch = page->get_roller_item_patchloc(idx);
		if (selected_patch) {
			page->selected_patch = *selected_patch;
			page->state = State::TryingToRequestPatchData;
		} else {
			//Do nothing? Close/open directory? Focus subdir panel?
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

	std::vector<EntryInfo> roller_item_infos;

	PatchSelectorSubdirPanel &subdir_panel;

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
