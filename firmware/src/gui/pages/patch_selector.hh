#pragma once
//TODO: selecting/focussing Internal on subdir panel makes roller jump to SD
//TODO: SD/Internal does not highlight when navigating roller
//TODO: clikcing a subdir item goes to roller OK but focusses on Dir entry, not first file
#include "fs/dir_entry_kind.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/helpers/lvgl_mem_helper.hh"
#include "gui/helpers/lvgl_string_helper.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "pr_dbg.hh"
#include "src/core/lv_obj.h"

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
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_click_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_scroll_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_FOCUS_KEY);

		for (auto vol_cont : vol_conts) {
			auto vol_item = lv_obj_get_child(vol_cont, 0);
			lv_obj_add_event_cb(vol_item, subdir_focus_cb, LV_EVENT_FOCUSED, this);
			lv_obj_add_event_cb(vol_item, subdir_defocus_cb, LV_EVENT_DEFOCUSED, this);
			lv_obj_add_event_cb(vol_item, subdir_click_cb, LV_EVENT_CLICKED, this);
			lv_obj_set_user_data(vol_item, nullptr);
			lv_obj_add_style(vol_item, &Gui::subdir_panel_item_style, LV_STATE_DEFAULT);
			lv_obj_add_style(vol_item, &Gui::subdir_panel_item_sel_style, LV_STATE_FOCUSED);
			lv_obj_add_style(vol_item, &Gui::subdir_panel_item_sel_style, LV_STATE_FOCUS_KEY);
		}
	}

	void prepare_focus() override {
		state = State::TryingToRequestPatchList;
		hide_spinner();
		focus_roller();

		lv_group_set_wrap(group, false);

		auto patchname = patch_playloader.cur_patch_name();
		if (patchname.length() == 0) {
			lv_label_set_text(ui_NowPlayingName, "none");
			lv_label_set_text(ui_LoadMeter, "");
		} else {
			lv_label_set_text_fmt(ui_NowPlayingName, "%.31s", patchname.c_str());
			lv_label_set_text_fmt(ui_LoadMeter, "%d%%", metaparams.audio_load);
		}

		refresh_subdir_panel();
	}

	void refresh_patchlist(PatchDirList &patchfiles) {
		populate_subdir_panel(patchfiles);
		populate_roller(patchfiles);
	}

	void populate_subdir_panel(PatchDirList &patchfiles) {
		// populate side bar with volumes and dirs
		for (auto [vol_cont, root] : zip(vol_conts, patchfiles.vol_root)) {

			// Delete existing dir labels (except first one, which is the volume root)
			if (auto num_children = lv_obj_get_child_cnt(vol_cont); num_children > 1) {
				for (unsigned i = 1; i < num_children; i++) {
					lv_obj_del_async(lv_obj_get_child(vol_cont, i));
				}
			}

			// No need to scan if no files or dirs: disable it
			if (root.files.size() == 0 && root.dirs.size() == 0) {
				lv_disable(vol_cont);
				lv_disable_all_children(vol_cont);
				lv_obj_clear_state(vol_cont, LV_STATE_FOCUSED);
				continue;
			}

			auto vol_button = lv_obj_get_child(vol_cont, 0);
			lv_obj_set_user_data(vol_button, &root);

			pr_dbg("Add to group: %p [vol]\n", vol_button);
			lv_group_add_obj(group, vol_button);
			for (auto &dir : root.dirs) {
				add_subdir_to_panel(dir, vol_cont);
			}

			lv_enable(vol_cont);
			lv_enable_all_children(vol_cont);
		}
	}

	void add_subdir_to_panel(PatchDir &dir, lv_obj_t *vol_label) {
		if (dir.files.size() == 0)
			return;

		auto *btn = lv_btn_create(vol_label);
		auto *name_label = lv_label_create(btn);

		lv_obj_add_style(btn, &Gui::subdir_panel_item_style, LV_STATE_DEFAULT);
		lv_obj_add_style(btn, &Gui::subdir_panel_item_sel_style, LV_STATE_FOCUSED);
		lv_obj_add_style(btn, &Gui::subdir_panel_item_sel_style, LV_STATE_FOCUS_KEY);

		lv_label_set_text_fmt(name_label, "%s", dir.name.c_str());
		lv_label_set_long_mode(name_label, LV_LABEL_LONG_CLIP);
		lv_obj_set_width(name_label, LV_PCT(100));

		lv_obj_add_flag(btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_set_user_data(btn, &dir);
		lv_obj_add_event_cb(btn, subdir_focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(btn, subdir_defocus_cb, LV_EVENT_DEFOCUSED, this);
		lv_obj_add_event_cb(btn, subdir_click_cb, LV_EVENT_CLICKED, this);

		pr_dbg("Add to group: %p %s\n", btn, dir.name.c_str());
		lv_group_add_obj(group, btn);
	}

	void populate_roller(PatchDirList &patchfiles) {
		std::string roller_text;
		roller_item_infos.clear();

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

		lv_roller_set_options(ui_PatchListRoller, roller_text.c_str(), LV_ROLLER_MODE_NORMAL);
	}

	void add_all_files_to_roller(Volume vol, std::string &roller_text, std::string prefix, PatchDir &dir) {
		for (auto &p : dir.files) {
			roller_text += prefix + std::string{p.patchname} + "\n";
			roller_item_infos.emplace_back(EntryInfo{DirEntryKind::File, vol, dir.name, p.filename});
		}
	}

	std::string format_volume_name(StaticString<31> const &vol_name, PatchDir &root) {
		std::string roller_text = "[" + std::string(vol_name) + "]";

		add_file_count(roller_text, root);
		add_dir_count(roller_text, root);

		roller_text += "\n";
		return roller_text;
	}

	std::string format_subdir_name(PatchDir const &subdir) {
		std::string roller_text = " " + subdir.name;
		add_file_count(roller_text, subdir);
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

		if (metaparams.meta_buttons[0].is_just_released()) {
			if (lv_group_get_focused(group) == ui_PatchListRoller) {
				focus_subdir_panel();
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
				refresh_subdir_panel();
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

	void focus_subdir_panel() {
		lv_obj_add_state(ui_PatchListRoller, LV_STATE_DISABLED);
		lv_obj_add_state(ui_DrivesPanel, LV_STATE_FOCUSED);

		pr_dbg("Focus subdir: sel = %p\n", last_subdir_sel);
		if (last_subdir_sel) {
			lv_obj_clear_state(last_subdir_sel, LV_STATE_FOCUSED);
			lv_group_focus_obj(last_subdir_sel);
		} else {
			lv_group_focus_next(group);
		}
	}

	void focus_roller() {
		lv_obj_clear_state(ui_DrivesPanel, LV_STATE_FOCUSED);
		lv_obj_clear_state(ui_PatchListRoller, LV_STATE_DISABLED);
		lv_group_focus_obj(ui_PatchListRoller);
		lv_group_set_editing(group, true);
	}

	void refresh_subdir_panel() {
		auto idx = lv_roller_get_selected(ui_PatchListRoller);
		if (idx >= roller_item_infos.size())
			return;

		auto &entry = roller_item_infos[idx];

		for (auto [vol, vol_name, vol_cont] : zip(vols, vol_names, vol_conts)) {
			if (vol != entry.vol)
				continue;

			lv_foreach_child(vol_cont, [this, entry, vol_name](lv_obj_t *obj, unsigned i) {
				auto label_child = (i == 0) ? 1 : 0;
				const char *txt = lv_label_get_text(lv_obj_get_child(obj, label_child));
				const char *roller_path = (i == 0) ? vol_name : entry.path.c_str();
				if (txt == nullptr)
					return true;

				pr_dbg("Compare '%s' to %s\n", roller_path, txt);
				if (strcmp(txt, roller_path) == 0) {
					if (last_subdir_sel) {
						lv_obj_clear_state(last_subdir_sel, LV_STATE_FOCUSED);
						label_clips(last_subdir_sel);
					}
					last_subdir_sel = obj;
					lv_obj_add_state(obj, LV_STATE_FOCUSED);
					label_scrolls(obj);
					lv_obj_scroll_to_view_recursive(obj, LV_ANIM_ON);
					return (i == 0) ? true : false;
				}
				return true;
			});
		}
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
			pr_trace("Clicked vol %d, patch %s\n", (uint32_t)selected_patch->vol, selected_patch->filename.c_str());
		} else {
			//Do nothing? Close/open directory? Focus subdir panel?
		}
	}

	static void subdir_focus_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorPage *>(event->user_data);
		if (!page || !event->target || !event->target->user_data)
			return;

		label_scrolls(event->target);

		page->last_subdir_sel = event->target;

		auto *dir = static_cast<PatchDir *>(event->target->user_data);

		uint32_t first_roller_entry = 0;
		for (auto [i, entry] : enumerate(page->roller_item_infos)) {
			if (entry.path == dir->name) {
				first_roller_entry = i;
				break;
			}
		}
		lv_roller_set_selected(ui_PatchListRoller, first_roller_entry + 1, LV_ANIM_ON);
	}

	static void label_scrolls(lv_obj_t *obj) {
		if (lv_obj_get_child_cnt(obj) > 0) {
			lv_label_set_long_mode(lv_obj_get_child(obj, 0), LV_LABEL_LONG_SCROLL);
		}
	}

	static void label_clips(lv_obj_t *obj) {
		if (lv_obj_get_child_cnt(obj) > 0) {
			lv_label_set_long_mode(lv_obj_get_child(obj, 0), LV_LABEL_LONG_CLIP);
		}
	}

	static void subdir_defocus_cb(lv_event_t *event) {
		if (!event->target)
			return;
		label_clips(event->target);
	}

	static void subdir_click_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorPage *>(event->user_data);
		if (page)
			page->focus_roller();
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

	std::array<lv_obj_t *, 3> vol_conts = {ui_USBVolCont, ui_SDVolCont, ui_FlashVolCont};
	std::array<Volume, 3> vols = {Volume::USB, Volume::SDCard, Volume::NorFlash};
	std::array<const char *, 3> vol_names = {"USB", "Card", "Internal"};
	std::vector<EntryInfo> roller_item_infos;

	lv_obj_t *last_subdir_sel = nullptr;

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
