#pragma once
#include "fs/dir_entry_kind.hh"
#include "gui/helpers/dir_entry_info.hh"
#include "gui/helpers/load_meter.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/helpers/roller_hover_text.hh"
#include "gui/pages/base.hh"
#include "gui/pages/make_cable.hh"
#include "gui/pages/missing_plugin_scan.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector_subdir_panel.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "patch_file/reload_patch.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {

	static constexpr unsigned max_open_patches = 20;

	PatchSelectorPage(PatchContext info, PatchSelectorSubdirPanel &subdir_panel)
		: PageBase{info, PageId::PatchSel}
		, subdir_panel{subdir_panel}
		, patchfiles{patch_storage.get_patch_list()}
		, patchloader{patch_storage, patches, settings.filesystem}
		, missing_plugins{info.plugin_manager, ui_PatchSelectorPage, group, settings.missing_plugins}
		, roller_hover(ui_PatchSelectorPage, ui_PatchListRoller, [this] { redraw_cb(); }) {

		init_bg(ui_PatchSelectorPage);

		lv_group_add_obj(group, ui_PatchListRoller);
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_click_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_PatchListRoller, patchlist_scroll_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_PatchListRoller, nullptr, LV_STATE_FOCUS_KEY);
		lv_obj_clear_state(ui_Flashbut, LV_STATE_FOCUSED);

		roller_hover.center_on_roller(false);
		roller_hover.set_y_offset(13);
		auto hov = roller_hover.get_cont();
		lv_obj_add_flag(hov, LV_OBJ_FLAG_FLOATING);
		lv_obj_set_x(hov, 3);
		lv_obj_set_width(hov, 210);
		lv_obj_set_align(hov, LV_ALIGN_RIGHT_MID);
	}

	void redraw_cb() {
		if (!lv_obj_has_state(ui_PatchListRoller, LV_STATE_DISABLED))
			roller_hover.display_in_time(10);
	}

	void prepare_focus() override {
		abort_cable(gui_state, notify_queue);

		// Don't persist module selection
		args.module_id = std::nullopt;

		if (last_refresh_check_tm == 0)
			state = State::ReloadingPatchList;
		else
			state = State::TryingToRequestPatchList;
		hide_spinner();
		blur_subdir_panel();

		lv_group_set_editing(group, true);
		lv_group_set_wrap(group, false);

		auto playing_patch = patches.get_playing_patch();
		is_patch_playloaded = playing_patch && playing_patch->patch_name.length() > 0;

		update_load_text(is_patch_playloaded, metaparams, patch_playloader, settings.patch_view, ui_LoadMeter);

		if (is_patch_playloaded) {
			lv_label_set_text_fmt(ui_NowPlayingName, "%.31s", playing_patch->patch_name.c_str());
		} else {
			lv_label_set_text(ui_NowPlayingName, "none");
		}

		is_populating_subdir_panel = true;
		setup_subdir_panel();

		patchfiles_locked = false;
		refresh_patchlist();

		roller_hover.hide();
	}

	void setup_subdir_panel() {
		subdir_panel.set_parent(ui_PatchSelectorPage, 1);

		subdir_panel.focus_cb = [this](Volume vol, std::string_view dir) {
			if (!is_populating_subdir_panel) {
				for (auto [i, entry] : enumerate(roller_item_infos)) {
					if (entry.path == dir && entry.vol == vol) {
						lv_roller_set_selected(ui_PatchListRoller, i + 1, LV_ANIM_ON);
						scroll_to_next_valid();
						break;
					}
				}
			}
		};
		subdir_panel.click_cb = [this](Volume vol, std::string_view dir) {
			blur_subdir_panel();
		};
	}

	void refresh_subdir_panel() {
		auto idx = lv_roller_get_selected(ui_PatchListRoller);
		if (idx < roller_item_infos.size()) {
			subdir_panel.refresh_highlighted_item(roller_item_infos[idx]);
		}
	}

	void refresh_patchlist() {
		// Do not access patchfiles while M4 is accessing them
		if (!patchfiles_locked) {
			is_populating_subdir_panel = true;
			refresh_open_patches();
			subdir_panel.populate(patchfiles);
			subdir_panel.show_recent_files();
			populate_roller();
		}
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

	void refresh_open_patches() {
		auto &root = patchfiles.volume_root(Volume::RamDisk);
		root.files.clear();
		root.dirs.clear();

		auto open_patch_list = patches.get_open_patch_list();

		for (auto &patch : open_patch_list) {
			auto vol_name = std::string{PatchDirList::get_vol_name(patch.loc.vol)};
			auto patch_name = vol_name + ": " + std::string{std::string_view{patch.patch.patch_name}};

			if (patch.modification_count > 0)
				patch_name = Gui::red_text("•") + " " + patch_name;

			if (patch.loc_hash == patches.get_playing_patch_loc_hash())
				patch_name = Gui::green_text(LV_SYMBOL_PLAY) + " " + patch_name;

			root.files.emplace_back(
				patch.loc.filename, 0, patch.modification_count, PatchName{patch_name}, patch.loc.vol);
		}
	}

	void populate_roller() {
		// Save current selection
		std::optional<EntryInfo> last_entry_info{};
		auto idx = last_selected_idx;
		if (idx < roller_item_infos.size()) {
			if (roller_item_infos[idx].name.length())
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

		// Try to find the previously selected item in the new set of data, otherwise pick first non-dir entry
		unsigned match_idx = 1;
		for (auto [i, entry] : enumerate(roller_item_infos)) {
			if (last_entry_info) {
				if (entry == *last_entry_info) {
					match_idx = i;
					break;
				}
			} else {
				if (entry.kind == DirEntryKind::File) {
					match_idx = i;
					break;
				}
			}
		}

		lv_roller_set_selected(ui_PatchListRoller, match_idx, LV_ANIM_OFF);
		roller_hover.hide();
	}

	void add_all_files_to_roller(Volume vol, std::string &roller_text, std::string prefix, PatchDir &dir) {
		for (auto &p : dir.files) {
			roller_text += prefix + std::string{p.patchname} + "\n";

			roller_item_infos.emplace_back(EntryInfo{
				.kind = DirEntryKind::File,
				.vol = vol,
				.path = dir.name,
				.name = p.filename,
				.link_vol = p.link_vol,
			});
		}
	}

	std::string format_volume_name(StaticString<31> const &vol_name, PatchDir &root) {
		std::string roller_text = Gui::orange_text(vol_name);

		// TODO: make a setting to hide/show these?
		add_file_count(roller_text, root);
		add_dir_count(roller_text, root);

		roller_text += "\n";
		return roller_text;
	}

	std::string format_subdir_name(PatchDir const &subdir) {
		std::string roller_text;

		if (subdir.name.size() > 0) {
			roller_text += Gui::yellow_text(subdir.name);
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
		if (root.dirs.size() > 0) {
			unsigned num = 0;
			for (auto &d : root.dirs) {
				if (d.files.size() > 0)
					num++;
			}
			if (num > 0)
				roller_text += " (" + std::to_string(num) + " dirs)";
		}
	}

	void update() override {

		if (is_populating_subdir_panel) {
			refresh_subdir_panel();
			is_populating_subdir_panel = false;
		}

		if (gui_state.back_button.is_just_released()) {
			if (missing_plugins.is_visible()) {
				missing_plugins.hide();

			} else if (!lv_obj_has_state(ui_PatchListRoller, LV_STATE_DISABLED)) {
				lv_obj_add_state(ui_PatchListRoller, LV_STATE_DISABLED);
				lv_obj_clear_state(ui_PatchListRoller, LV_STATE_FOCUSED);
				subdir_panel.focus();

			} else {
				page_list.request_new_page_no_history(PageId::MainMenu, args);
			}

			roller_hover.hide();
		}

		update_spinner();

		roller_hover.update();

		switch (state) {
			case State::Idle: {
				//periodically check if patchlist needs updating:
				uint32_t now = lv_tick_get();
				if (now - last_refresh_check_tm > 1000) { //poll media once per second
					last_refresh_check_tm = now;
					state = State::TryingToRequestPatchList;

					update_load_text(
						is_patch_playloaded, metaparams, patch_playloader, settings.patch_view, ui_LoadMeter);
				} else {
					// Poll for patch file changes in between polling for patch list updates
					poll_patch_file_changed();
				}
			} break;

			case State::TryingToRequestPatchList: {
				if (patch_storage.request_patchlist()) {
					// Lock patchesfiles: we are not allowed to access it, because M4 has access now
					patchfiles_locked = true;
					state = State::RequestedPatchList;
					show_spinner();
				}
			} break;

			case State::RequestedPatchList: {
				auto message = patch_storage.get_message();
				if (message.message_type == FileStorageProxy::PatchListChanged) {
					state = State::ReloadingPatchList;

					// Unlock patchesfiles: M4 is done with it
					patchfiles_locked = false;

				} else if (message.message_type == FileStorageProxy::PatchListUnchanged) {
					hide_spinner();
					state = State::Idle;

					// Unlock patchesfiles: M4 is done with it
					patchfiles_locked = false;
				}
			} break;

			case State::ReloadingPatchList:
				refresh_patchlist();
				refresh_subdir_panel();
				hide_spinner();
				state = State::Idle;
				break;

			case State::LoadPatchFile: {

				// If the patch is not open, or if it's opened but modified on disk only
				// then (re)load it from disk, checking for missing plugins
				if (patchloader.needs_reloading(selected_patch)) {
					show_spinner();

					auto result = patchloader.reload_patch_file(selected_patch, [this] {
						update_spinner();
						lv_timer_handler();
					});

					if (result.success) {
						check_missing_plugins();

					} else {
						lv_group_set_editing(group, true);
						notify_queue.put({.message = result.error_string, .priority = Notification::Priority::Error});
						state = State::Idle;
					}
				} else {
					// Here we know the patch is open already.

					// If patch is unmodifed in RAM, then check for missing plugins
					if (patches.find_open_patch(selected_patch)->modification_count == 0) {
						check_missing_plugins();

					} else {
						// Otherwise the patch has unsaved changes so just view it, don't reload/load anything
						patches.start_viewing(selected_patch);
						open_patch_view_page();
					}
				}

				hide_spinner();
			} break;

			case State::CheckMissingPlugins: {
				missing_plugins.process(patches.get_view_patch(), group, [this] { open_patch_view_page(); });
			} break;

			case State::Closing:
				break;
		}
	}

	void check_missing_plugins() {
		patches.start_viewing(selected_patch);

		state = State::CheckMissingPlugins;

		missing_plugins.start();
	}

	void blur() final {
		hide_spinner();
		roller_hover.hide();
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

private:
	void open_patch_view_page() {
		args.patch_loc_hash = PatchLocHash{selected_patch};
		gui_state.force_redraw_patch = true;
		page_list.request_new_page(PageId::PatchView, args);
		roller_hover.hide();

		state = State::Closing;
	}

	void scroll_to_next_valid() {
		static uint32_t prev_idx = 0;
		auto idx = lv_roller_get_selected(ui_PatchListRoller);

		// Skip over dir entries:
		if (idx < roller_item_infos.size()) {
			auto &entry = roller_item_infos[idx];
			if (entry.kind == DirEntryKind::Dir) {
				auto max = lv_roller_get_option_cnt(ui_PatchListRoller) - 1;
				auto new_idx = (idx == 0) ? 1 : (idx >= max) ? max - 1 : (idx > prev_idx) ? idx + 1 : idx - 1;
				if (roller_item_infos[new_idx].kind == DirEntryKind::Dir) {
					// Handle skipping over two consecutive Dir entries
					new_idx = (new_idx == 0)   ? 2 :
							  (new_idx >= max) ? max - 1 :
							  (new_idx > idx)  ? new_idx + 1 :
												 new_idx - 1;
				}
				lv_roller_set_selected(ui_PatchListRoller, new_idx, LV_ANIM_ON);
				prev_idx = new_idx;
			}
		}
	}

	static void patchlist_scroll_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorPage *>(event->user_data);

		page->scroll_to_next_valid();

		if (!page->is_populating_subdir_panel)
			page->refresh_subdir_panel();

		page->roller_hover.hide();
	}

	static void patchlist_click_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorPage *>(event->user_data);

		auto idx = lv_roller_get_selected(ui_PatchListRoller);

		page->roller_hover.hide();

		auto selected_patch = page->get_roller_item_patchloc(idx);
		if (selected_patch) {
			page->selected_patch = *selected_patch;
			page->state = State::LoadPatchFile;
			page->last_selected_idx = idx;
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
				p->vol = entry.link_vol.value_or(entry.vol);

				if (entry.path.empty())
					p->filename.copy(std::string(entry.name));
				else
					p->filename.copy(std::string(entry.path + "/" + entry.name));
			}
		} else
			pr_err("Bad roller index: %d, max is %zu\n", selected_index, roller_item_infos.size());

		return p;
	}

	PatchLocation selected_patch{"", Volume::NorFlash};

	std::vector<EntryInfo> roller_item_infos;
	unsigned last_selected_idx = 0;

	PatchSelectorSubdirPanel &subdir_panel;
	PatchDirList &patchfiles;
	bool patchfiles_locked = true;
	ReloadPatch patchloader;

	MissingPluginScanner missing_plugins;

	bool is_populating_subdir_panel = false;

	static constexpr uint32_t spinner_lag_ms = 200;
	uint32_t spinner_show_tm = 0;

	enum class State {
		Idle,

		TryingToRequestPatchList,
		RequestedPatchList,
		ReloadingPatchList,

		LoadPatchFile,

		CheckMissingPlugins,

		Closing,
	} state{State::TryingToRequestPatchList};

	uint32_t last_refresh_check_tm = 0;

	RollerHoverText roller_hover;

	bool is_patch_playloaded = false;
};

} // namespace MetaModule
