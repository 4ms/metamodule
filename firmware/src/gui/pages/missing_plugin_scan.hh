#pragma once
#include "gui/pages/confirm_popup.hh"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/missing_plugin_autoload.hh"
#include "user_settings/missing_plugin_settings.hh"

namespace MetaModule
{

struct MissingPluginScanner {

	MissingPluginScanner(PluginManager &plugin_manager, lv_obj_t *parent, MissingPluginSettings &settings)
		: missing_plugin_loader{plugin_manager}
		, missing_plugin_popup{parent}
		, waitspinner{create_spinner(parent)}
		, parent{parent}
		, settings{settings}
		, just_done{false} {

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

		title = lv_label_create(missing_plugin_popup.panel);
		lv_obj_move_to_index(title, lv_obj_get_index(missing_plugin_popup.message_label));
		lv_obj_set_width(title, 180);
		lv_obj_set_height(title, LV_SIZE_CONTENT);
		lv_label_set_text(title, "");
		lv_obj_set_align(title, LV_ALIGN_TOP_LEFT);
		lv_obj_set_style_text_color(title, Gui::orange_highlight, LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(title, 255, LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_LEFT, LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(title, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(title, LV_OPA_0, LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(title, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_hor(title, 0, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_ver(title, 2, LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(title, 0, LV_STATE_DEFAULT);

		lv_hide(waitspinner);

		lv_obj_set_style_text_font(missing_plugin_popup.message_label, &ui_font_MuseoSansRounded50014, 0);
	}

	bool init_handling = false;

	void start() {
		init_handling = true;
	}

	void process(PatchData *patch, lv_group_t *group, auto completed_cb) {
		if (init_handling) {
			if (scan(patch)) {
				ask(
					[=](bool ok) {
						if (!ok)
							completed_cb();
					},
					group);
			} else {
				completed_cb();
			}

			init_handling = false;
		}

		process();

		if (just_finished_processing()) {
			if (has_missing(patch)) {
				show_missing(completed_cb);
			} else {
				completed_cb();
			}
		}
	}

	bool is_visible() {
		return missing_plugin_popup.is_visible();
	}

	bool is_done_processing() {
		return !missing_plugin_loader.is_processing();
	}

	void hide() {
		missing_plugin_popup.hide();
		lv_hide(waitspinner);
	}

private:
	bool scan(PatchData *patch) {
		missing_plugin_loader.scan(patch);
		return missing_plugin_loader.missing_brands().size() > 0;
	}

	void ask(auto callback, lv_group_t *parent_group) {
		// Action to be performed after the popup:
		auto do_loading = [this, callback = callback](unsigned should_load) {
			if (should_load) {
				lv_show(waitspinner);
				just_done = false;
				missing_plugin_loader.start_loading_missing();
			}
			callback(should_load);
		};

		if (settings.autoload == MissingPluginSettings::Autoload::Always) {
			// Skip the popup, proceed as if the user clicked OK
			do_loading(true);

		} else if (settings.autoload == MissingPluginSettings::Autoload::Never) {
			// Skip the popup, proceed as if the user clicked Cancel
			do_loading(false);

		} else if (settings.autoload == MissingPluginSettings::Autoload::Ask) {
			missing_plugin_popup.init(parent, parent_group);

			// Populate the list of brands, showing "...and X more" if needed
			std::string message;
			auto missing_brands = missing_plugin_loader.missing_brands();
			for (size_t i = 0; auto const &mod : missing_brands) {
				constexpr size_t max_lines = 6;
				i++;
				if (i > max_lines)
					break;

				if (i == max_lines && i != missing_brands.size()) {
					message += "   ...and ";
					message += std::to_string(missing_brands.size() - max_lines + 1);
					message += " more";
				} else {
					message += "- " + mod + "\n";
				}
			}
			if (message.ends_with('\n'))
				message.pop_back();

			lv_label_set_text(title, "Load missing plugins?");

			missing_plugin_popup.show(do_loading, message.c_str(), "Load");
		}
	}

	void process() {
		if (missing_plugin_loader.is_processing()) {
			lv_show(waitspinner);
			lv_show(status_label);

			auto status = missing_plugin_loader.process_loading();

			if (!missing_plugin_loader.is_processing()) {
				just_done = true;
				lv_hide(waitspinner);
				lv_hide(status_label);

			} else if (status.message.length()) {
				lv_label_set_text(status_label, status.message.c_str());
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

		lv_label_set_text_fmt(title, "Not found:");

		std::string message;
		for (size_t i = 0; auto const &mod : skipped) {
			constexpr size_t max_lines = 6;
			i++;
			if (i > max_lines)
				break;

			if (i == max_lines && i != skipped.size()) {
				message += "   ...and ";
				message += std::to_string(skipped.size() - max_lines + 1);
				message += " more";
			} else {
				message += "- " + mod + "\n";
			}
		}
		if (message.ends_with('\n'))
			message.pop_back();

		missing_plugin_popup.show([callback](unsigned) { callback(); }, message.c_str(), "");
	}

private:
	MissingPluginAutoload missing_plugin_loader;
	ConfirmPopup missing_plugin_popup;
	lv_obj_t *status_label;
	lv_obj_t *waitspinner;
	lv_obj_t *parent;
	lv_obj_t *title;

	MissingPluginSettings &settings;

	bool just_done;
};

} // namespace MetaModule
