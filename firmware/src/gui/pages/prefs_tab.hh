#pragma once
#include "dynload/plugin_loader.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct PrefsTab {

	PrefsTab(FileStorageProxy &patch_storage)
		: file_storage{patch_storage} {
		lv_obj_add_event_cb(ui_ResetFactoryPatchesButton, resetbut_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *group) {
		this->group = group;
		lv_group_remove_obj(ui_ResetFactoryPatchesButton);
		lv_group_add_obj(group, ui_ResetFactoryPatchesButton);
		lv_group_focus_obj(ui_ResetFactoryPatchesButton);
		confirm_popup.init(ui_SystemMenu, group);
	}

	// Returns true if this pages uses the back event
	bool consume_back_event() {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			return true;
		}
		return false;
	}

	void update() {
	}

private:
	static void resetbut_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<PrefsTab *>(event->user_data);
		page->confirm_popup.show(
			[page](bool ok) {
				if (ok) {
					page->file_storage.request_reset_factory_patches();
				}
			},
			"Do you really want to PERMENENTLY DELETE all patches stored internally? This will replace them with "
			"factory default patches.\n",
			"Delete");
	}

	lv_group_t *group = nullptr;
	FileStorageProxy &file_storage;
	ConfirmPopup confirm_popup;
};

} // namespace MetaModule
