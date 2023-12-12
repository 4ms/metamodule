#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct MainMenuPage : PageBase {
	MainMenuPage(PatchInfo info)
		: PageBase{info, PageId::MainMenu} {
		init_bg(ui_MainMenu);
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, ui_MenuPanelPatches);
		lv_group_add_obj(group, ui_MenuPanelSave);
		lv_group_add_obj(group, ui_MenuPanelSettings);

		lv_group_focus_obj(ui_MenuPanelPatches);

		lv_obj_add_event_cb(ui_MenuPanelPatches, patchsel_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_MenuPanelSettings, settings_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus() final {
		auto patch = patch_storage.get_view_patch();
		if (patch.patch_name.length() == 0)
			lv_label_set_text(patchname_label, "No patch playing");
		else
			lv_label_set_text(patchname_label, patch.patch_name.c_str());

		lv_group_set_editing(group, false);
		lv_group_focus_obj(ui_MenuPanelPatches);
	}

	void update() final {
		if (metaparams.audio_load != last_audio_load) {
			metaparams.audio_load = last_audio_load;
			lv_label_set_text_fmt(load_label, "%d%%", metaparams.audio_load);
			lv_show(load_label);
		};
	}

	void blur() final {
		;
	}

private:
	static void patchsel_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		page->load_page(PageId::PatchSel, {});
	}

	static void savepatch_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		pr_err("Not implemented\n");
	}

	static void settings_cb(lv_event_t *event) {
		auto page = static_cast<MainMenuPage *>(event->user_data);
		if (!page)
			return;
		page->load_page(PageId::SystemMenu, {});
	}

	unsigned last_audio_load = 0;

	lv_obj_t *patchname_label = ui_MainMenuNowPlayingName;
	lv_obj_t *load_label = ui_MainMenuLoadMeter;
};

} // namespace MetaModule
