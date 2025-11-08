#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
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

	PatchDescriptionPanel(PatchPlayLoader &patch_playloader,
						  OpenPatchManager &patches,
						  PatchSuggestedAudioSettings &settings)
		: group(lv_group_create())
		, patch_playloader{patch_playloader}
		, patches{patches}
		, settings{settings} {

		// Description
		auto desc_cont = lv_obj_get_parent(ui_Description);
		lv_obj_add_style(desc_cont, &Gui::focus_style, LV_STATE_FOCUSED);
		lv_obj_add_style(desc_cont, &Gui::focus_style, LV_STATE_FOCUS_KEY);

		lv_obj_add_event_cb(desc_cont, editbut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(desc_cont, scroll_top, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ui_DescriptionEditTextArea, textarea_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionEditSaveButton, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_DescriptionEditCancelButton, cancel_cb, LV_EVENT_CLICKED, this);

		// Patch suggested audio settings
		create_suggested_audio_controls();
		lv_obj_move_to_index(ui_DescMIDIPolyNumLabel, 2);

		lv_obj_add_event_cb(suggest_sr_drop, suggested_audio_changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(suggest_bs_drop, suggested_audio_changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(apply_settings_button, apply_settings_cb, LV_EVENT_CLICKED, this);

		lv_obj_set_style_pad_row(ui_DescriptionPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(ui_DescriptionPanel, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_obj_add_event_cb(close_button, closebut_cb, LV_EVENT_CLICKED, this);

		lv_hide(ui_DescriptionEditPanel);
		lv_hide(ui_PatchNameEditTextArea);

		// Group
		lv_group_set_wrap(group, false);
		lv_group_set_editing(group, false);
		lv_group_add_obj(group, desc_cont);
		lv_group_add_obj(group, suggest_sr_drop);
		lv_group_add_obj(group, suggest_bs_drop);
		lv_group_add_obj(group, ui_DescriptionEditTextArea);
		lv_group_add_obj(group, ui_DescriptionEditSaveButton);
		lv_group_add_obj(group, ui_DescriptionEditCancelButton);
		lv_group_add_obj(group, close_button);
		lv_group_add_obj(group, apply_settings_button);
	}

	void prepare_focus(lv_group_t *base_group) {
		parent_group = base_group;
		lv_hide(ui_DescriptionPanel);
	}

	void set_patch(PatchData *cur_patch) {
		patch = cur_patch;
	}

	void set_filename(std::string_view name) {
		filename = name;
	}

	bool is_visible() {
		return is_showing;
	}

	void update() {
		bool show_manual_apply = false;

		if (patch && patches.get_playing_patch() == patches.get_view_patch()) {
			auto current = patch_playloader.get_audio_settings();

			if ((!settings.apply_samplerate && patch->suggested_samplerate != current.sample_rate) ||
				(!settings.apply_blocksize && patch->suggested_blocksize != current.block_size))
			{
				show_manual_apply = true;
			}
		}

		lv_show(apply_settings_button, show_manual_apply);
	}

	bool did_update_names() {
		bool temp = did_save;
		did_save = false;
		return temp;
	}

	void back_event() {
		if (lv_dropdown_is_open(suggest_sr_drop)) {
			lv_dropdown_close(suggest_sr_drop);
			lv_group_set_editing(group, false);

		} else if (lv_dropdown_is_open(suggest_bs_drop)) {
			lv_dropdown_close(suggest_bs_drop);
			lv_group_set_editing(group, false);

		} else if (kb_visible) {
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
		lv_group_focus_obj(close_button);
		lv_obj_scroll_to_view_recursive(close_button, LV_ANIM_OFF);
		lv_group_set_editing(group, false);
		is_showing = true;
		edit_panel_visible = false;

		if (patch->description.length() == 0)
			lv_label_set_text(ui_Description, "Patch Description");
		else
			lv_label_set_text(ui_Description, patch->description.c_str());

		lv_label_set_text(ui_DescPanelPatchName, patch->patch_name.c_str());

		lv_label_set_text(ui_DescPanelFileName, filename.c_str());

		if (patch->midi_poly_num)
			lv_label_set_text_fmt(ui_DescMIDIPolyNumLabel, "MIDI Poly Chans: %u", (unsigned)patch->midi_poly_num);
		else
			lv_label_set_text(ui_DescMIDIPolyNumLabel, "");

		set_suggested_audio_dropdowns();

		lv_hide(apply_settings_button);

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
	void create_suggested_audio_controls() {
		suggest_sr_cont = create_labeled_dropdown(ui_DescriptionPanel);
		suggest_sr_label = lv_obj_get_child(suggest_sr_cont, 0);
		suggest_sr_drop = lv_obj_get_child(suggest_sr_cont, 1);
		lv_obj_set_style_pad_ver(suggest_sr_cont, 4, LV_STATE_DEFAULT);

		suggest_bs_cont = create_labeled_dropdown(ui_DescriptionPanel);
		suggest_bs_label = lv_obj_get_child(suggest_bs_cont, 0);
		suggest_bs_drop = lv_obj_get_child(suggest_bs_cont, 1);
		lv_obj_set_style_pad_ver(suggest_bs_cont, 4, LV_STATE_DEFAULT);

		lv_label_set_text(suggest_sr_label, "Patch Sample Rate:");
		lv_label_set_text(suggest_bs_label, "Patch Block Size:");
		lv_obj_set_style_text_font(suggest_sr_label, &ui_font_MuseoSansRounded50014, LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(suggest_bs_label, &ui_font_MuseoSansRounded50014, LV_STATE_DEFAULT);

		lv_obj_set_style_pad_left(suggest_sr_drop, 10, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_ver(suggest_sr_drop, 6, LV_STATE_DEFAULT);
		lv_obj_set_width(suggest_sr_drop, 90);

		lv_obj_set_style_pad_left(suggest_bs_drop, 10, LV_STATE_DEFAULT);
		lv_obj_set_style_pad_ver(suggest_bs_drop, 6, LV_STATE_DEFAULT);
		lv_obj_set_width(suggest_bs_drop, 90);

		close_button = create_button(ui_DescriptionPanel, "Close");

		apply_settings_button = create_button(ui_DescriptionPanel, "Apply Settings");
	}

	void set_suggested_audio_dropdowns() {
		// Samplerate dropdown
		std::string opts = "Any\n";
		for (auto item : AudioSettings::ValidSampleRates) {
			opts += std::to_string(item / 1000) + "kHz\n";
		}
		opts.pop_back();
		lv_dropdown_set_options(suggest_sr_drop, opts.c_str());
		size_t sel = 0;
		if (patch && patch->suggested_samplerate) {
			for (size_t i = 0; i < AudioSettings::ValidSampleRates.size(); i++) {
				if (AudioSettings::ValidSampleRates[i] == patch->suggested_samplerate) {
					sel = i + 1; // shift by 1 due to Any
					break;
				}
			}
		}
		lv_dropdown_set_selected(suggest_sr_drop, sel);

		// Blocksize dropdown
		opts = "Any\n";
		for (auto item : AudioSettings::ValidBlockSizes) {
			opts += std::to_string(item) + "\n";
		}
		opts.pop_back();
		lv_dropdown_set_options(suggest_bs_drop, opts.c_str());
		sel = 0;
		if (patch && patch->suggested_blocksize) {
			for (size_t i = 0; i < AudioSettings::ValidBlockSizes.size(); i++) {
				if (AudioSettings::ValidBlockSizes[i] == patch->suggested_blocksize) {
					sel = i + 1; // shift by 1 due to Any
					break;
				}
			}
		}
		lv_dropdown_set_selected(suggest_bs_drop, sel);
	}

	static void suggested_audio_changed_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);

		auto current = page->patch_playloader.get_audio_settings();
		auto new_sr = current.sample_rate;
		auto new_bs = current.block_size;

		if (event->target == page->suggest_sr_drop) {
			int sel = lv_dropdown_get_selected(page->suggest_sr_drop);
			// Update patch settings. index 0 is "Any"
			new_sr = sel > 0 ? AudioSettings::ValidSampleRates[sel - 1] : 0;
			if (page->patch->suggested_samplerate != new_sr) {
				page->patch->suggested_samplerate = new_sr;
				page->patches.mark_view_patch_modified();
			}

		} else if (event->target == page->suggest_bs_drop) {
			int sel = lv_dropdown_get_selected(page->suggest_bs_drop);
			// Update patch settings. index 0 is "Any"
			new_bs = sel > 0 ? AudioSettings::ValidBlockSizes[sel - 1] : 0;
			if (page->patch->suggested_blocksize != new_bs) {
				page->patch->suggested_blocksize = new_bs;
				page->patches.mark_view_patch_modified();
			}
		}

		if (page->patches.get_playing_patch() != page->patches.get_view_patch())
			return;

		// If prefs allow patch to override audio sr/bs, and it changed to something other than "Any", then update it
		if ((page->settings.apply_samplerate && new_sr && new_sr != current.sample_rate) ||
			(page->settings.apply_blocksize && new_bs && new_bs != current.block_size))
		{
			page->patch_playloader.request_new_audio_settings(new_sr, new_bs, current.max_overrun_retries);
		}
	}

	static void apply_settings_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchDescriptionPanel *>(event->user_data);

		if (page->patches.get_playing_patch() != page->patches.get_view_patch())
			return;

		// Update the current samplerate/blocksize to whatever the patch overrides are set to.
		// If the override is "Any" then don't change that setting.
		// Ignore the user preference for "allow overrides" since this is a manual override

		auto current = page->patch_playloader.get_audio_settings();

		auto sr_sel = lv_dropdown_get_selected(page->suggest_sr_drop);
		auto sr = sr_sel > 0 ? AudioSettings::ValidSampleRates[sr_sel - 1] : current.sample_rate;

		auto bs_sel = lv_dropdown_get_selected(page->suggest_bs_drop);
		auto bs = bs_sel > 0 ? AudioSettings::ValidBlockSizes[bs_sel - 1] : current.block_size;

		page->patch_playloader.request_new_audio_settings(sr, bs, current.max_overrun_retries);
	}

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
		lv_group_set_editing(page->group, true);
		lv_group_focus_obj(ui_DescriptionEditTextArea);
		lv_event_send(ui_DescriptionEditTextArea, LV_EVENT_CLICKED, nullptr);

		set_content_max_height(ui_DescriptionEditPanel, 230);

		page->edit_panel_visible = true;
	}

	static void scroll_top(lv_event_t *event) {
		lv_obj_scroll_to_y(ui_DescriptionPanel, 0, LV_ANIM_ON);
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
		lv_group_focus_obj(ui_DescriptionEditTextArea);
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

	PatchData *patch = nullptr;

	std::string filename;

	bool is_showing = false;
	bool edit_panel_visible = false;
	bool kb_visible = false;
	bool did_save = false;

	lv_obj_t *suggest_sr_cont = nullptr;
	lv_obj_t *suggest_sr_label = nullptr;
	lv_obj_t *suggest_sr_drop = nullptr;

	lv_obj_t *suggest_bs_cont = nullptr;
	lv_obj_t *suggest_bs_label = nullptr;
	lv_obj_t *suggest_bs_drop = nullptr;

	lv_obj_t *apply_settings_button = nullptr;
	lv_obj_t *close_button = nullptr;

	PatchPlayLoader &patch_playloader;
	OpenPatchManager &patches;
	PatchSuggestedAudioSettings &settings;
};

} // namespace MetaModule
