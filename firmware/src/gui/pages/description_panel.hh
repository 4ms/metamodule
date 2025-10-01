#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "patch/patch_data.hh"
#include "patch_play/patch_playloader.hh"
#include "pr_dbg.hh"
#include "src/core/lv_event.h"
#include "user_settings/audio_settings.hh"
#include <string>

namespace MetaModule
{

struct PatchDescriptionPanel {

	PatchDescriptionPanel()
		: group(lv_group_create()) {

		lv_group_add_obj(group, ui_DescriptionEditButton);
		lv_group_add_obj(group, ui_DescriptionClose);

		lv_hide(ui_DescriptionEditPanel);
		lv_hide(ui_PatchNameEditTextArea);
		lv_group_add_obj(group, ui_DescriptionEditTextArea);

		lv_group_add_obj(group, ui_DescriptionEditSaveButton);
		lv_group_add_obj(group, ui_DescriptionEditCancelButton);

		lv_group_set_wrap(group, false);
		lv_group_set_editing(group, false);

		lv_obj_add_event_cb(ui_DescriptionClose, closebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionEditButton, editbut_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_DescriptionEditTextArea, textarea_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_DescriptionEditSaveButton, save_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_DescriptionEditCancelButton, cancel_cb, LV_EVENT_CLICKED, this);

		create_suggested_audio_controls();
		lv_group_add_obj(group, ui_DescSuggestSRDrop);
		lv_group_add_obj(group, ui_DescSuggestBSDrop);
		lv_obj_move_to_index(ui_DescSuggestSRCont, lv_obj_get_index(ui_Description) + 1);
		lv_obj_move_to_index(ui_DescSuggestBSCont, lv_obj_get_index(ui_Description) + 2);
	}

	void prepare_focus(lv_group_t *base_group) {
		parent_group = base_group;
		lv_hide(ui_DescriptionPanel);
	}

	void set_patch(PatchData *cur_patch) {
		patch = cur_patch;
	}

	void set_patch_loader(PatchPlayLoader &pl) {
		patch_playloader = &pl;
	}

	void set_filename(std::string_view name) {
		filename = name;
	}

	bool is_visible() {
		return is_showing;
	}

	bool did_update_names() {
		bool temp = did_save;
		did_save = false;
		return temp;
	}

	void back_event() {
		if (kb_visible) {
			hide_keyboard();
		} else if (edit_panel_visible) {
			show();
		} else {
			hide();
		}
	}

	void show() {
		lv_show(ui_DescriptionPanel);
		lv_hide(ui_DescriptionEditPanel);

		lv_obj_set_parent(ui_DescPanelPatchName, ui_DescriptionPanel);
		lv_obj_move_background(ui_DescPanelPatchName);

		lv_indev_set_group(lv_indev_get_next(nullptr), group);
		lv_group_focus_obj(ui_DescriptionClose);
		lv_group_set_editing(group, false);
		is_showing = true;
		edit_panel_visible = false;

		lv_label_set_text(ui_Description, patch->description.c_str());
		lv_label_set_text(ui_DescPanelPatchName, patch->patch_name.c_str());

		lv_label_set_text(ui_DescPanelFileName, filename.c_str());

		if (patch->midi_poly_num)
			lv_label_set_text_fmt(ui_DescMIDIPolyNumLabel, "MIDI Poly Chans: %u", (unsigned)patch->midi_poly_num);
		else
			lv_label_set_text(ui_DescMIDIPolyNumLabel, "");

		set_suggested_audio_dropdowns();

		set_content_max_height(ui_DescriptionPanel, 230);
	}

	void hide() {
		lv_hide(ui_DescriptionPanel);
		lv_hide(ui_DescriptionEditPanel);
		lv_hide(ui_Keyboard);
		if (parent_group)
			lv_indev_set_group(lv_indev_get_next(nullptr), parent_group);
		is_showing = false;
		kb_visible = false;
		edit_panel_visible = false;
	}

private:
	static void closebut_cb(lv_event_t *event) {
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		page->hide();
	}

	// Edit button: hide panel, show editable panel
	static void editbut_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		lv_hide(ui_DescriptionPanel);
		lv_show(ui_DescriptionEditPanel);

		lv_obj_set_parent(ui_DescPanelPatchName, ui_DescriptionEditPanel);
		lv_obj_move_background(ui_DescPanelPatchName);

		lv_textarea_set_text(ui_DescriptionEditTextArea, lv_label_get_text(ui_Description));
		lv_group_set_editing(page->group, false);

		set_content_max_height(ui_DescriptionEditPanel, 230);

		page->edit_panel_visible = true;
	}

	// Any text area: show keyboard
	static void textarea_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		auto kb_hidden = lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN);
		if (kb_hidden) {
			if (event->target == ui_DescriptionEditTextArea) {
				page->show_keyboard();
				lv_keyboard_set_textarea(ui_Keyboard, event->target);
				lv_obj_add_state(event->target, LV_STATE_USER_1);
				set_content_max_height(ui_DescriptionEditPanel, 128);
				set_content_max_height(event->target, 128);
				lv_obj_scroll_to_view_recursive(event->target, LV_ANIM_ON);
				page->active_ta = event->target;
			}
		}
	}

	void show_keyboard() {
		// replace callbacks
		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);

		lv_show(ui_Keyboard);
		lv_group_add_obj(group, ui_Keyboard);
		lv_group_focus_obj(ui_Keyboard);
		lv_group_set_editing(group, true);

		lv_obj_set_parent(ui_Keyboard, ui_PatchViewPage);
		lv_obj_set_y(ui_Keyboard, 128);
		kb_visible = true;
	}

	void hide_keyboard() {
		lv_obj_clear_state(ui_DescriptionEditTextArea, LV_STATE_USER_1);
		if (active_ta)
			lv_group_focus_obj(active_ta);
		lv_group_remove_obj(ui_Keyboard);
		lv_hide(ui_Keyboard);

		lv_obj_set_height(ui_DescriptionEditTextArea, LV_SIZE_CONTENT);
		set_content_max_height(ui_DescriptionEditPanel, 230);
		kb_visible = false;
	}

	static void save_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);

		if (page->patch) {
			page->patch->description = lv_textarea_get_text(ui_DescriptionEditTextArea);
			lv_label_set_text(ui_Description, lv_textarea_get_text(ui_DescriptionEditTextArea));
			page->did_save = true;
		}
		page->hide();
	}

	static void cancel_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		page->hide();
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);

		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			page->hide_keyboard();
		}
	}

	lv_group_t *group;
	lv_group_t *parent_group = nullptr;

	lv_obj_t *active_ta = nullptr;

	PatchData *patch = nullptr;

	std::string filename;

	bool is_showing = false;
	bool edit_panel_visible = false;
	bool kb_visible = false;
	bool did_save = false;

	lv_obj_t *ui_DescSuggestSRCont = nullptr;
	lv_obj_t *ui_DescSuggestSRLabel = nullptr;
	lv_obj_t *ui_DescSuggestSRDrop = nullptr;

	lv_obj_t *ui_DescSuggestBSCont = nullptr;
	lv_obj_t *ui_DescSuggestBSLabel = nullptr;
	lv_obj_t *ui_DescSuggestBSDrop = nullptr;

	PatchPlayLoader *patch_playloader = nullptr;

	void create_suggested_audio_controls() {
		if (!ui_DescSuggestSRCont) {
			ui_DescSuggestSRCont = lv_obj_create(ui_DescriptionPanel);
			lv_obj_remove_style_all(ui_DescSuggestSRCont);
			lv_obj_set_width(ui_DescSuggestSRCont, lv_pct(100));
			lv_obj_set_height(ui_DescSuggestSRCont, LV_SIZE_CONTENT);
			lv_obj_set_align(ui_DescSuggestSRCont, LV_ALIGN_CENTER);
			lv_obj_set_flex_flow(ui_DescSuggestSRCont, LV_FLEX_FLOW_ROW);
			lv_obj_set_flex_align(
				ui_DescSuggestSRCont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
			lv_obj_clear_flag(ui_DescSuggestSRCont, LV_OBJ_FLAG_SCROLLABLE);

			ui_DescSuggestSRLabel = lv_label_create(ui_DescSuggestSRCont);
			lv_label_set_text(ui_DescSuggestSRLabel, "Samplerate:");

			ui_DescSuggestSRDrop = lv_dropdown_create(ui_DescSuggestSRCont);
			lv_obj_add_event_cb(ui_DescSuggestSRDrop, suggested_audio_changed_cb, LV_EVENT_VALUE_CHANGED, this);
		}
		if (!ui_DescSuggestBSCont) {
			ui_DescSuggestBSCont = lv_obj_create(ui_DescriptionPanel);
			lv_obj_remove_style_all(ui_DescSuggestBSCont);
			lv_obj_set_width(ui_DescSuggestBSCont, lv_pct(100));
			lv_obj_set_height(ui_DescSuggestBSCont, LV_SIZE_CONTENT);
			lv_obj_set_align(ui_DescSuggestBSCont, LV_ALIGN_CENTER);
			lv_obj_set_flex_flow(ui_DescSuggestBSCont, LV_FLEX_FLOW_ROW);
			lv_obj_set_flex_align(
				ui_DescSuggestBSCont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
			lv_obj_clear_flag(ui_DescSuggestBSCont, LV_OBJ_FLAG_SCROLLABLE);

			ui_DescSuggestBSLabel = lv_label_create(ui_DescSuggestBSCont);
			lv_label_set_text(ui_DescSuggestBSLabel, "Blocksize:");

			ui_DescSuggestBSDrop = lv_dropdown_create(ui_DescSuggestBSCont);
			lv_obj_add_event_cb(ui_DescSuggestBSDrop, suggested_audio_changed_cb, LV_EVENT_VALUE_CHANGED, this);
		}
	}

	void set_suggested_audio_dropdowns() {
		// Build options with 'None' + valid values
		auto build_opts = [](auto const &ValidOptions) {
			std::string opts = "None\n";
			for (auto v : ValidOptions) {
				opts += std::to_string(v);
				opts += "\n";
			}
			if (!opts.empty())
				opts.pop_back();
			return opts;
		};

		// Samplerate dropdown
		if (ui_DescSuggestSRDrop) {
			std::string sr_opts = build_opts(AudioSettings::ValidSampleRates);
			lv_dropdown_set_options(ui_DescSuggestSRDrop, sr_opts.c_str());
			int sel = 0; // None
			if (patch && patch->suggested_samplerate) {
				for (size_t i = 0; i < AudioSettings::ValidSampleRates.size(); ++i) {
					if (AudioSettings::ValidSampleRates[i] == patch->suggested_samplerate) {
						sel = static_cast<int>(i) + 1; // shift by 1 due to None
						break;
					}
				}
			}
			lv_dropdown_set_selected(ui_DescSuggestSRDrop, sel);
		}

		// Blocksize dropdown
		if (ui_DescSuggestBSDrop) {
			std::string bs_opts = build_opts(AudioSettings::ValidBlockSizes);
			lv_dropdown_set_options(ui_DescSuggestBSDrop, bs_opts.c_str());
			int sel = 0; // None
			if (patch && patch->suggested_blocksize) {
				for (size_t i = 0; i < AudioSettings::ValidBlockSizes.size(); ++i) {
					if (AudioSettings::ValidBlockSizes[i] == patch->suggested_blocksize) {
						sel = static_cast<int>(i) + 1; // shift by 1 due to None
						break;
					}
				}
			}
			lv_dropdown_set_selected(ui_DescSuggestBSDrop, sel);
		}
	}

	static void suggested_audio_changed_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);
		if (!page->patch_playloader)
			return;

		auto current = page->patch_playloader->get_audio_settings();

		if (event->target == page->ui_DescSuggestSRDrop) {
			int sel = lv_dropdown_get_selected(page->ui_DescSuggestSRDrop);
			if (sel <= 0)
				return; // None
			uint32_t new_sr = AudioSettings::ValidSampleRates[sel - 1];
			page->patch_playloader->request_new_audio_settings(new_sr, current.block_size, current.max_overrun_retries);

		} else if (event->target == page->ui_DescSuggestBSDrop) {
			int sel = lv_dropdown_get_selected(page->ui_DescSuggestBSDrop);
			if (sel <= 0)
				return; // None
			uint32_t new_bs = AudioSettings::ValidBlockSizes[sel - 1];
			page->patch_playloader->request_new_audio_settings(
				current.sample_rate, new_bs, current.max_overrun_retries);
		}
	}
};

} // namespace MetaModule
