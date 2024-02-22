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
		: file_storage{patch_storage}
		, plugin_loader{patch_storage}
		, plugin_button(lv_btn_create(ui_SystemMenuPrefs))
		, plugin_button_label(lv_label_create(plugin_button)) {
		lv_obj_add_event_cb(ui_ResetFactoryPatchesButton, resetbut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(plugin_button, load_plugin_but_cb, LV_EVENT_CLICKED, this);

		////// set up UI: TODO do this in SLS
		lv_obj_set_width(plugin_button, LV_SIZE_CONTENT);
		lv_obj_set_height(plugin_button, LV_SIZE_CONTENT);
		lv_obj_set_align(plugin_button, LV_ALIGN_CENTER);
		lv_obj_add_flag(plugin_button, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
		lv_obj_clear_flag(plugin_button,
						  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
							  LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN);
		lv_obj_set_style_bg_color(plugin_button, lv_color_hex(0x444444), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(plugin_button, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(plugin_button, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(plugin_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(plugin_button, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(plugin_button, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(plugin_button, 3, LV_PART_MAIN | LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(plugin_button, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
		lv_obj_set_style_outline_opa(plugin_button, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

		lv_obj_set_width(plugin_button_label, LV_SIZE_CONTENT);
		lv_obj_set_height(plugin_button_label, LV_SIZE_CONTENT);
		lv_obj_set_align(plugin_button_label, LV_ALIGN_CENTER);
		lv_label_set_text(plugin_button_label, "Load Plugins");
	}

	void prepare_focus(lv_group_t *group) {
		this->group = group;
		lv_group_remove_obj(ui_ResetFactoryPatchesButton);
		lv_group_remove_obj(plugin_button);
		lv_group_add_obj(group, ui_ResetFactoryPatchesButton);
		lv_group_add_obj(group, plugin_button);

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
		auto result = plugin_loader.process();
		if (result.error_message.length()) {
			pr_err("Error: %s\n", result.error_message.c_str());
		}
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

	static void load_plugin_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;

		auto page = static_cast<PrefsTab *>(event->user_data);
		pr_dbg("Start plugin loader\n");
		page->plugin_loader.start();
	}

	lv_group_t *group = nullptr;
	FileStorageProxy &file_storage;
	ConfirmPopup confirm_popup;

	//TODO: Organizationally, maybe this should be in main, and a ref to it in PatchContext?
	PluginFileLoader plugin_loader;

	lv_obj_t *plugin_button;
	lv_obj_t *plugin_button_label;
};

} // namespace MetaModule
