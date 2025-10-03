#pragma once
#include "gui/pages/confirm_popup.hh"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/missing_plugin_autoload.hh"

namespace MetaModule
{

struct MissingPluginScanner {

	MissingPluginScanner(PluginManager &plugin_manager, lv_obj_t *parent, lv_group_t *group)
		: missing_plugin_loader{plugin_manager}
		, missing_plugin_popup{parent}
		, waitspinner{create_spinner(parent)}
		, parent{parent} {

		status_label = lv_label_create(parent);
		lv_obj_set_align(status_label, LV_ALIGN_TOP_MID);
		lv_obj_set_width(status_label, lv_pct(100));
		lv_obj_set_height(status_label, LV_SIZE_CONTENT);
		lv_obj_set_pos(status_label, 0, 0);
		lv_obj_set_style_bg_color(status_label, lv_color_hex(0x222222), 0);
		lv_obj_set_style_bg_opa(status_label, LV_OPA_100, 0);
		lv_obj_set_style_pad_ver(status_label, 4, 0);
		lv_obj_set_style_pad_hor(status_label, 8, 0);
		lv_obj_set_style_text_font(status_label, &ui_font_MuseoSansRounded50014, 0);
		lv_obj_set_style_text_color(status_label, Gui::orange_highlight, 0);
		lv_obj_set_style_text_align(status_label, LV_TEXT_ALIGN_CENTER, 0);
		lv_obj_add_flag(status_label, LV_OBJ_FLAG_FLOATING);

		lv_label_set_text(status_label, "");
		lv_hide(status_label);

		lv_hide(waitspinner);
	}

	bool scan(PatchData *patch) {
		missing_plugin_loader.scan(patch);
		return missing_plugin_loader.missing_brands().size() > 0;
	}

	void ask(auto should_load, lv_group_t *parent_group) {
		missing_plugin_popup.init(parent, parent_group);

		auto missing_brands = missing_plugin_loader.missing_brands();

		std::string message = "Load missing brands?";
		for (auto &mod : missing_brands)
			message += "\n" + mod;

		missing_plugin_popup.show(
			[this, callback = should_load](unsigned choice) {
				if (choice == 1) { //confirm button
					lv_show(ui_waitspinner);
					just_done = false;
					missing_plugin_loader.start_loading_missing();
				}

				callback(choice);
			},
			message.c_str(),
			"Load");
	}

	void process() {
		if (missing_plugin_loader.is_processing()) {
			lv_show(waitspinner);
			// lv_label_set_text(status_label, "Searching for plugins");
			lv_show(status_label);

			auto status = missing_plugin_loader.process_loading();

			if (!missing_plugin_loader.is_processing())
				just_done = true;

			if (status.message.length()) {
				lv_label_set_text(status_label, status.message.c_str());
				pr_dbg("msg: %s\n", status.message.c_str());
			}

			if (!missing_plugin_loader.is_processing()) {
				lv_hide(waitspinner);
				lv_hide(status_label);
			}
		}
	}

	bool just_finished_processing() {
		auto t = just_done;
		just_done = false;
		return t;
	}

	bool has_missing(PatchData *patch) {
		missing_plugin_loader.scan(patch);
		return missing_plugin_loader.skipped_modules().size() > 0;
	}

	void show_missing(auto callback) {
		auto skipped = missing_plugin_loader.skipped_modules();
		std::string message = "Not found:";
		for (auto &mod : skipped)
			message += "\n" + mod;

		missing_plugin_popup.show([callback](unsigned) { callback(); }, message.c_str(), "");
	}

	bool is_done_processing() {
		return !missing_plugin_loader.is_processing();
	}

	bool is_visible() {
		return missing_plugin_popup.is_visible();
	}

	void hide() {
		missing_plugin_popup.hide();
		lv_hide(waitspinner);
	}

private:
	MissingPluginAutoload missing_plugin_loader;
	ConfirmPopup missing_plugin_popup;
	lv_obj_t *status_label;
	lv_obj_t *waitspinner;
	lv_obj_t *parent;
	bool just_done;
};

} // namespace MetaModule
