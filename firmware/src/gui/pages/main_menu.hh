#pragma once
#include "gui/helpers/load_meter.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/make_cable.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct MainMenuPage : PageBase {
	MainMenuPage(PatchContext info)
		: PageBase{info, PageId::MainMenu} {
		init_bg(ui_MainMenu);
		lv_group_remove_all_objs(group);

		lv_group_add_obj(group, ui_MainMenuNowPlayingPanel);
		lv_group_add_obj(group, ui_MainMenuLastViewedPanel);

		lv_group_add_obj(group, ui_MenuPanelPatches);
		lv_group_add_obj(group, ui_MenuPanelSave); //new patch
		lv_group_add_obj(group, ui_MenuPanelSettings);

		lv_group_focus_obj(ui_MenuPanelPatches);
		lv_group_set_wrap(group, false);

		lv_obj_add_event_cb(ui_MenuPanelPatches, patchsel_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_MenuPanelSettings, settings_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_MenuPanelSave, new_patch_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_MainMenuLastViewedPanel, last_viewed_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_MainMenuNowPlayingPanel, now_playing_cb, LV_EVENT_CLICKED, this);

		lv_label_set_text(ui_MainMenuNowPlaying, "Loading Modules...");
		lv_label_set_text(ui_MainMenuNowPlayingName, "");

		lv_hide(ui_MainMenuLastViewedPanel);

		lv_label_set_text(ui_MenuLabelPatches, "Load\nPatch");
	}

	void prepare_focus() final {
		abort_cable(gui_state, notify_queue);

		auto patch = patches.get_playing_patch();
		if (!patch || patch->patch_name.length() == 0) {
			lv_hide(ui_MainMenuNowPlayingPanel);
		} else {
			lv_show(ui_MainMenuNowPlayingPanel);
			lv_show(ui_MainMenuNowPlaying);
			lv_show(ui_MainMenuNowPlayingName);
			lv_label_set_text(ui_MainMenuNowPlaying, "Playing:");
			lv_label_set_text(ui_MainMenuNowPlayingName, patch->patch_name.c_str());
		}

		auto viewpatch = patches.get_view_patch();
		if (viewpatch == patch || !viewpatch || viewpatch->patch_name.length() == 0) {
			lv_hide(ui_MainMenuLastViewedPanel);
		} else {
			lv_show(ui_MainMenuLastViewedPanel);
			lv_label_set_text(ui_MainMenuLastViewed, "Last Viewed:");
			lv_label_set_text(ui_MainMenuLastViewedName, viewpatch->patch_name.c_str());
		}

		lv_group_set_editing(group, false);
		lv_group_focus_obj(ui_MenuPanelPatches);
	}

	void update() final {
		if (gui_state.back_button.is_just_released()) {
			if (patches.get_view_patch())
				load_patch_view_page();
		}

		update_load_text(metaparams, ui_MainMenuLoadMeter);

		poll_patch_file_changed();
	}

	void blur() final {
		;
	}

private:
	void load_patch_view_page() {
		load_page(PageId::PatchView,
				  {
					  .patch_loc = patches.get_view_patch_loc(),
					  .patch_loc_hash = patches.get_view_patch_loc_hash(),
				  });
	}

	static void last_viewed_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		page->load_patch_view_page();
	}

	static void now_playing_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		if (page->patches.get_playing_patch()) {
			page->patches.view_playing_patch();
			page->load_patch_view_page();
		}
	}

	static void patchsel_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		page->load_page(PageId::PatchSel, {});
	}

	static void new_patch_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		page->patches.new_patch();
		page->patch_playloader.request_load_view_patch();
		page->page_list.set_active_knobset(0);
		page->load_page(PageId::ModuleList,
						{.patch_loc_hash = page->patches.get_view_patch_loc_hash(), .view_knobset_id = 0});
	}

	static void settings_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		page->load_page(PageId::SystemMenu, {});
	}
};

} // namespace MetaModule
