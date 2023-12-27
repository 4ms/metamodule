#pragma once
#include "gui/helpers/dir_entry_info.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_file/patch_dir_list.hh"
#include "pr_dbg.hh"
#include "util/countzip.hh"
#include "util/zip.hh"

namespace MetaModule
{

struct PatchSelectorSubdirPanel {
	PatchSelectorSubdirPanel(std::vector<EntryInfo> &roller_items)
		: roller_item_infos{roller_items} {
		for (auto vol_cont : vol_conts) {
			auto vol_item = lv_obj_get_child(vol_cont, 0);
			lv_obj_add_event_cb(vol_item, subdir_focus_cb, LV_EVENT_FOCUSED, this);
			lv_obj_add_event_cb(vol_item, subdir_defocus_cb, LV_EVENT_DEFOCUSED, this);
			lv_obj_add_event_cb(vol_item, subdir_click_cb, LV_EVENT_CLICKED, this);
			lv_obj_set_user_data(vol_item, nullptr);
		}
	}

	void populate(lv_group_t *parent_group, PatchDirList &patchfiles) {
		group = parent_group;

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

			// Add root-level dir on volume
			auto vol_button = lv_obj_get_child(vol_cont, 0);
			lv_obj_set_user_data(vol_button, &root);
			lv_group_add_obj(group, vol_button);

			// Add all dirs on volume
			for (auto &dir : root.dirs)
				add_subdir_to_panel(dir, vol_cont);

			lv_enable(vol_cont);
			lv_enable_all_children(vol_cont);
		}
	}

	void refresh() {
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

	void focus() {
		lv_obj_add_state(ui_PatchListRoller, LV_STATE_DISABLED);
		lv_obj_add_state(ui_DrivesPanel, LV_STATE_FOCUSED);

		if (last_subdir_sel) {
			lv_obj_clear_state(last_subdir_sel, LV_STATE_FOCUSED);
			lv_group_focus_obj(last_subdir_sel);
		} else {
			if (group)
				lv_group_focus_next(group);
		}
	}

	void blur() {
		lv_obj_clear_state(ui_DrivesPanel, LV_STATE_FOCUSED);
		lv_obj_clear_state(ui_PatchListRoller, LV_STATE_DISABLED);
		lv_group_focus_obj(ui_PatchListRoller);
		if (group)
			lv_group_set_editing(group, true);

		if (last_subdir_sel)
			lv_obj_add_state(last_subdir_sel, LV_STATE_FOCUSED);
	}

	static void subdir_focus_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorSubdirPanel *>(event->user_data);
		if (!page || !event->target || !event->target->user_data)
			return;

		label_scrolls(event->target);

		page->last_subdir_sel = event->target;

		auto *dir = static_cast<PatchDir *>(event->target->user_data);

		auto parent = lv_obj_get_parent(event->target);
		Volume this_vol{};
		for (auto [vol, vol_cont] : zip(page->vols, page->vol_conts)) {
			if (parent == vol_cont)
				this_vol = vol;
		}

		uint32_t first_roller_entry = 0;
		for (auto [i, entry] : enumerate(page->roller_item_infos)) {
			if (entry.path == dir->name && entry.vol == this_vol) {
				first_roller_entry = i;
				break;
			}
		}
		lv_roller_set_selected(ui_PatchListRoller, first_roller_entry + 1, LV_ANIM_ON);
	}

	static void subdir_defocus_cb(lv_event_t *event) {
		if (!event->target)
			return;
		label_clips(event->target);
	}

	static void subdir_click_cb(lv_event_t *event) {
		auto panel = static_cast<PatchSelectorSubdirPanel *>(event->user_data);
		if (panel)
			panel->blur();
	}

	lv_obj_t *last_subdir_sel = nullptr;

private:
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

		lv_group_add_obj(group, btn);
	}

	lv_group_t *group{};

	const std::array<lv_obj_t *, 3> vol_conts = {ui_USBVolCont, ui_SDVolCont, ui_FlashVolCont};
	static constexpr std::array<Volume, 3> vols = {Volume::USB, Volume::SDCard, Volume::NorFlash};
	static constexpr std::array<const char *, 3> vol_names = {"USB", "Card", "Internal"};

	std::vector<EntryInfo> &roller_item_infos;
};

} // namespace MetaModule
