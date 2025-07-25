#pragma once
#include "gui/helpers/dir_entry_info.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "patch_file/patch_dir_list.hh"
#include "pr_dbg.hh"
#include <cstring>
#include <functional>

namespace MetaModule
{

struct PatchSelectorSubdirPanel {

	PatchSelectorSubdirPanel() {
		group = lv_group_create();

		for (auto vol_cont : vol_conts) {
			auto vol_item = lv_obj_get_child(vol_cont, 0);

			lv_obj_add_style(vol_item, &Gui::subdir_panel_item_sel_blurred_style, LV_STATE_USER_2);

			while (lv_obj_remove_event_cb(vol_item, nullptr)) {
			}
			lv_obj_add_event_cb(vol_item, subdir_click_cb, LV_EVENT_CLICKED, this);
			lv_obj_add_event_cb(vol_item, subdir_focus_cb, LV_EVENT_FOCUSED, this);
			lv_obj_add_event_cb(vol_item, subdir_defocus_cb, LV_EVENT_DEFOCUSED, this);
		}
	}

	void set_parent(lv_obj_t *parent, unsigned zindex) {
		lv_obj_set_parent(ui_DrivesPanel, parent);
		lv_obj_move_to_index(ui_DrivesPanel, zindex);
	}

	void populate(PatchDirList const &patchfiles) {
		lv_group_remove_all_objs(group);

		// populate side bar with volumes and dirs
		for (auto [vol_cont, root] : zip(vol_conts, patchfiles.vol_root)) {

			auto vol_item = lv_obj_get_child(vol_cont, 0);

			// No need to scan if no files or dirs: disable it
			if (root.files.size() == 0 && root.dirs.size() == 0) {
				lv_disable(vol_cont);
				lv_foreach_child(vol_cont, [](lv_obj_t *child, unsigned i) {
					lv_show(child, i == 0);
					lv_disable(child);
				});
				continue;
			}

			// Add root-level dir on volume
			lv_obj_set_user_data(vol_item, (void *)&root);
			lv_group_add_obj(group, vol_item);

			// Add all dirs with files
			auto num_existing_subdir_items = lv_obj_get_child_cnt(vol_cont) - 1;
			for (auto i = 0u; auto &dir : root.dirs) {
				if (dir.files.size() == 0) {
					continue;
				}

				// Use existing lvgl entry object, or add a new one if needed
				if (i < num_existing_subdir_items) {
					overwrite_subdir(dir, lv_obj_get_child(vol_cont, i + 1));
				} else {
					add_subdir_to_panel(dir, vol_cont);
				}
				i++;
			}

			int excess_dirs = (int)num_existing_subdir_items - (int)root.dirs.size();
			if (excess_dirs > 0) {
				for (auto i = 0; i < excess_dirs; i++) {
					lv_hide(lv_obj_get_child(vol_cont, i + root.dirs.size() + 1));
				}
			}

			lv_enable(vol_cont);
			lv_enable_all_children(vol_cont);
			lv_group_set_wrap(group, false);
		}
	}

	void hide_recent_files() {
		lv_hide(vol_conts[0]);
	}

	void show_recent_files() {
		lv_show(vol_conts[0]);
	}

	void refresh_highlighted_item(EntryInfo const &selected_patch) {
		// TODO: check if list was re-populated, or if entry info dir name changed, and only refresh if so

		for (auto [vol, vol_name, vol_cont] : zip(PatchDirList::vols, PatchDirList::vol_name, vol_conts)) {

			// Clear highlighting styles on all entries
			lv_obj_clear_state(vol_cont, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY | LV_STATE_USER_2);
			lv_foreach_child(vol_cont, [](lv_obj_t *child, unsigned i) {
				lv_obj_clear_state(child, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY | LV_STATE_USER_2);
				label_clips(child);
			});

			if (vol != selected_patch.vol) {
				continue;
			}

			lv_obj_t *dir_obj = nullptr;

			// Find the entry that matches the current patch's volume and path
			lv_foreach_child(vol_cont, [selected_patch, vol_name = vol_name, &dir_obj](lv_obj_t *obj, unsigned i) {
				auto label_child = lv_obj_get_child(obj, (i == 0) ? 1 : 0);
				const char *txt = lv_label_get_text(label_child);
				const char *roller_path = (i == 0) ? vol_name : selected_patch.path.c_str();
				if (txt != nullptr) {
					if (strcmp(txt, roller_path) == 0)
						dir_obj = obj;
				}
			});

			if (dir_obj) {
				if (lv_obj_has_state(ui_DrivesPanel, LV_STATE_FOCUSED)) {
					lv_obj_add_state(dir_obj, LV_STATE_FOCUSED);
					lv_obj_clear_state(dir_obj, LV_STATE_USER_2);
				} else {
					lv_obj_add_state(dir_obj, LV_STATE_USER_2);
					lv_obj_clear_state(dir_obj, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY);
				}
				label_scrolls(dir_obj);
				lv_obj_scroll_to_view_recursive(dir_obj, LV_ANIM_ON);

				last_subdir_sel = dir_obj;
			}
		}
	}

	void focus() {
		lv_obj_add_state(ui_DrivesPanel, LV_STATE_FOCUSED);

		lv_group_activate(group);

		if (last_subdir_sel) {
			if (lv_obj_has_flag(last_subdir_sel, LV_OBJ_FLAG_HIDDEN)) {
				if (group) {
					lv_obj_clear_state(last_subdir_sel, LV_STATE_USER_2);
					lv_group_focus_next(group);
					last_subdir_sel = lv_group_get_focused(group);
				}
			} else {
				lv_obj_clear_state(last_subdir_sel, LV_STATE_USER_2);
				lv_group_focus_obj(last_subdir_sel);
			}
		} else {
			if (group)
				lv_group_focus_next(group);
		}
	}

	void blur() {
		lv_obj_clear_state(ui_DrivesPanel, LV_STATE_FOCUSED);
		if (last_subdir_sel) {
			lv_obj_clear_state(last_subdir_sel, LV_STATE_FOCUSED);
			lv_obj_add_state(last_subdir_sel, LV_STATE_USER_2);
		}
	}

	static void subdir_focus_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorSubdirPanel *>(event->user_data);
		if (!page || !event->target || !event->target->user_data)
			return;

		label_scrolls(event->target);
		page->last_subdir_sel = event->target;

		if (page->focus_cb) {
			auto parent = lv_obj_get_parent(event->target);

			Volume this_vol{};
			for (auto [vol, vol_cont] : zip(PatchDirList::vols, page->vol_conts)) {
				if (parent == vol_cont) {
					this_vol = vol;
					break;
				}
			}

			std::string_view dirname = "";
			if (auto dir = static_cast<PatchDir const *>(event->target->user_data); dir) {
				dirname = std::string_view{dir->name};
			}

			page->focus_cb(this_vol, dirname);
		}
	}

	static void subdir_defocus_cb(lv_event_t *event) {
		if (!event->target)
			return;
		label_clips(event->target);
	}

	static void subdir_click_cb(lv_event_t *event) {
		auto page = static_cast<PatchSelectorSubdirPanel *>(event->user_data);

		if (page && event->target && page->click_cb) {
			auto parent = lv_obj_get_parent(event->target);

			Volume this_vol{};
			for (auto [vol, vol_cont] : zip(PatchDirList::vols, page->vol_conts)) {
				if (parent == vol_cont) {
					this_vol = vol;
					break;
				}
			}

			std::string_view dirname = "";
			if (auto dir = static_cast<PatchDir const *>(event->target->user_data); dir) {
				dirname = std::string_view{dir->name};
			}

			page->click_cb(this_vol, dirname);
		}
	}

	const std::array<lv_obj_t *, 4> vol_conts = {ui_OpenFileCont, ui_USBVolCont, ui_SDVolCont, ui_FlashVolCont};

	std::function<void(Volume vol, std::string_view dirname)> focus_cb;
	std::function<void(Volume vol, std::string_view dirname)> click_cb;

private:
	void overwrite_subdir(PatchDir const &dir, lv_obj_t *btn) {
		if (lv_obj_get_child_cnt(btn) != 1) {
			pr_err("Volume button %p has %d children, expected 1\n", btn, lv_obj_get_child_cnt(btn));
			return;
		}

		auto name_label = lv_obj_get_child(btn, 0);

		if (!lv_obj_has_class(name_label, &lv_label_class)) {
			pr_err("Volume button %p child is not a label\n", btn);
			return;
		}

		lv_label_set_text(name_label, dir.name.c_str());
		lv_obj_set_user_data(btn, (void *)&dir);
		lv_show(btn);

		lv_group_add_obj(group, btn);
	}

	void add_subdir_to_panel(PatchDir const &dir, lv_obj_t *vol_label) {
		if (dir.files.size() == 0)
			return;

		auto *btn = lv_btn_create(vol_label);
		auto *name_label = lv_label_create(btn);

		lv_obj_add_style(btn, &Gui::subdir_panel_item_style, LV_STATE_DEFAULT);
		lv_obj_add_style(btn, &Gui::subdir_panel_item_sel_style, LV_STATE_FOCUSED);
		lv_obj_add_style(btn, &Gui::subdir_panel_item_sel_style, LV_STATE_FOCUS_KEY);
		lv_obj_add_style(btn, &Gui::subdir_panel_item_sel_blurred_style, LV_STATE_USER_2);

		lv_label_set_text_fmt(name_label, "%s", dir.name.c_str());
		lv_label_set_long_mode(name_label, LV_LABEL_LONG_CLIP);
		lv_obj_set_width(name_label, LV_PCT(100));

		lv_obj_add_flag(btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_set_user_data(btn, (void *)&dir);

		while (lv_obj_remove_event_cb(btn, nullptr)) {
		}
		lv_obj_add_event_cb(btn, subdir_focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(btn, subdir_defocus_cb, LV_EVENT_DEFOCUSED, this);
		lv_obj_add_event_cb(btn, subdir_click_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, btn);
	}

	lv_obj_t *last_subdir_sel = nullptr;
	lv_group_t *group = nullptr;
};

} // namespace MetaModule
