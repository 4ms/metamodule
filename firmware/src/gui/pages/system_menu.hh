#pragma once
#include "fs/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/firmware_update_tab.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/plugin_tab.hh"
#include "gui/pages/prefs_tab.hh"
#include "gui/pages/system_info_tab.hh"
#include "gui/pages/system_tab.hh"
#include "gui/slsexport/meta5/ui.h"
#include "patch_file/reload_patch.hh"

namespace MetaModule
{

struct SystemMenuPage : PageBase {

	SystemMenuPage(PatchContext info)
		: PageBase{info, PageId::SystemMenu}
		, info_tab{patch_storage, info.metaparams}
		, plugin_tab{info.plugin_manager, info.settings.plugin_preload, info.notify_queue, gui_state, patch_playloader}
		, prefs_tab{info.patch_playloader, info.settings, gui_state}
		, system_tab{patch_storage,
					 params,
					 metaparams,
					 patch_playloader,
					 patch_mod_queue,
					 info.settings,
					 info.notify_queue}
		, fwupdate_tab{patch_storage, patch_playloader}
		, tab_bar(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		init_bg(ui_SystemMenu);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tab_bar);
		lv_group_set_editing(group, true);

		lv_obj_add_event_cb(tab_bar, tab_cb, LV_EVENT_VALUE_CHANGED, this);
	}

	void prepare_focus() final {
		lv_hide(ui_FWUpdateSpinner);
		lv_tabview_set_act(ui_SystemMenuTabView, 0, LV_ANIM_OFF);
		info_tab.prepare_focus(group);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tab_bar);
		lv_group_focus_obj(tab_bar);
		lv_group_set_editing(group, true);

		prefs_tab.set_patch_clicked_callback([this](std::string_view path) {
			auto [filename, vol] = split_volume(path);
			pending_patch_view = PatchLocation{std::string(filename), vol};
		});
	}

	void update() final {

		active_tab->update();

		if (pending_patch_view) {
			auto loc = *pending_patch_view;
			pending_patch_view.reset();

			ReloadPatch patchloader{patch_storage, patches, settings.filesystem};
			if (patchloader.needs_reloading(loc)) {
				auto result = patchloader.reload_patch_file(loc, [] { lv_timer_handler(); });
				if (!result.success) {
					notify_queue.put({result.error_string, Notification::Priority::Error});
					return;
				}
			}
			patches.start_viewing(loc);

			args.patch_loc_hash = PatchLocHash{loc};
			gui_state.force_redraw_patch = true;
			page_list.request_new_page(PageId::PatchView, args);
			return;
		}

		if (gui_state.back_button.is_just_released()) {
			if (!active_tab->consume_back_event()) {

				if (lv_group_get_focused(group) == tab_bar) {
					page_list.request_last_page();
				} else {
					lv_group_remove_all_objs(group);
					lv_group_add_obj(group, tab_bar);
					lv_group_focus_obj(tab_bar);
					lv_group_set_editing(group, true);
				}
			}
		}

		// update playing patch from disk when tab is
		// not making filesystem calls
		if (active_tab->is_idle())
			poll_patch_file_changed();
	}

	void blur() final {
	}

private:
	static void tab_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		page->tab_click();
	}

	void tab_click() {
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tab_bar);

		auto active_tab_index = lv_btnmatrix_get_selected_btn(tab_bar);
		active_tab = tabs[active_tab_index];
		active_tab->prepare_focus(group);
	}

	InfoTab info_tab;
	PluginTab plugin_tab;
	PrefsTab prefs_tab;
	SystemTab system_tab;
	FirmwareUpdateTab fwupdate_tab;
	std::array<SystemMenuTab *, 5> tabs{&info_tab, &plugin_tab, &prefs_tab, &system_tab, &fwupdate_tab};
	SystemMenuTab *active_tab = &info_tab;

	lv_obj_t *tab_bar;

	std::optional<PatchLocation> pending_patch_view;
};

} // namespace MetaModule
