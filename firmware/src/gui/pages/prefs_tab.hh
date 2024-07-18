#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/pages/view_settings.hh"
#include "gui/slsexport/meta5/ui.h"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct PrefsTab : SystemMenuTab {
	PrefsTab(PatchPlayLoader &patch_playloader, AudioSettings &settings, GuiState &gui_state)
		: patch_playloader{patch_playloader}
		, settings{settings}
		, gui_state{gui_state} {
		lv_obj_add_event_cb(ui_SystemPrefsSaveButton, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SystemPrefsRevertButton, revert_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_SystemPrefsAudioBlocksizeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		lv_group_remove_obj(ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_remove_obj(ui_SystemPrefsAudioBlocksizeDropdown);
		lv_group_remove_obj(ui_SystemPrefsRevertButton);
		lv_group_remove_obj(ui_SystemPrefsSaveButton);

		lv_group_add_obj(group, ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_add_obj(group, ui_SystemPrefsAudioBlocksizeDropdown);
		lv_group_add_obj(group, ui_SystemPrefsRevertButton);
		lv_group_add_obj(group, ui_SystemPrefsSaveButton);

		lv_dropdown_close(ui_SystemPrefsAudioSampleRateDropdown);
		lv_dropdown_close(ui_SystemPrefsAudioBlocksizeDropdown);

		lv_group_focus_obj(ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_set_editing(group, true);

		update_dropdowns_from_settings();
	}

	void update_dropdowns_from_settings() {
		auto sr_item = settings.sample_rate == 24000 ? 0 :
					   settings.sample_rate == 48000 ? 1 :
					   settings.sample_rate == 96000 ? 2 :
													   1;
		lv_dropdown_set_selected(ui_SystemPrefsAudioSampleRateDropdown, sr_item);

		auto bs_item = settings.block_size == 32  ? 0 :
					   settings.block_size == 64  ? 1 :
					   settings.block_size == 128 ? 2 :
					   settings.block_size == 256 ? 3 :
					   settings.block_size == 512 ? 4 :
													1;
		lv_dropdown_set_selected(ui_SystemPrefsAudioBlocksizeDropdown, bs_item);

		gui_state.do_write_settings = false;

		lv_disable(ui_SystemPrefsSaveButton);
		lv_disable(ui_SystemPrefsRevertButton);
	}

	uint32_t read_samplerate_dropdown() {
		auto sr_item = lv_dropdown_get_selected(ui_SystemPrefsAudioSampleRateDropdown);

		auto sample_rate = sr_item == 0 ? 24000 : sr_item == 1 ? 48000 : sr_item == 2 ? 96000 : 48000;
		return sample_rate;
	}

	uint32_t read_blocksize_dropdown() {
		auto bs_item = lv_dropdown_get_selected(ui_SystemPrefsAudioBlocksizeDropdown);

		auto block_size = bs_item == 0 ? 32 :
						  bs_item == 1 ? 64 :
						  bs_item == 2 ? 128 :
						  bs_item == 3 ? 256 :
						  bs_item == 4 ? 512 :
										 64;

		return block_size;
	}

	void update_settings_from_dropdown() {
		auto block_size = read_blocksize_dropdown();
		auto sample_rate = read_samplerate_dropdown();

		if (settings.block_size != block_size || settings.sample_rate != sample_rate) {

			settings.block_size = block_size;
			settings.sample_rate = sample_rate;

			patch_playloader.request_new_audio_settings(sample_rate, block_size);
			gui_state.do_write_settings = true;
		}

		lv_disable(ui_SystemPrefsSaveButton);
		lv_disable(ui_SystemPrefsRevertButton);
	}

	// Returns true if this page uses the back event
	bool consume_back_event() override {
		if (lv_dropdown_is_open(ui_SystemPrefsAudioSampleRateDropdown)) {
			lv_dropdown_close(ui_SystemPrefsAudioSampleRateDropdown);
			lv_group_focus_obj(ui_SystemPrefsAudioSampleRateDropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(ui_SystemPrefsAudioBlocksizeDropdown)) {
			lv_dropdown_close(ui_SystemPrefsAudioBlocksizeDropdown);
			lv_group_focus_obj(ui_SystemPrefsAudioBlocksizeDropdown);
			lv_group_set_editing(group, false);
			return true;

		} else
			return false;
	}

private:
	static void save_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PrefsTab *>(event->user_data);

		page->update_settings_from_dropdown();
		lv_group_focus_next(page->group);
	}

	static void revert_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PrefsTab *>(event->user_data);

		page->update_dropdowns_from_settings();
		lv_group_focus_next(page->group);
	}

	static void changed_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PrefsTab *>(event->user_data);

		auto block_size = page->read_blocksize_dropdown();
		auto sample_rate = page->read_samplerate_dropdown();

		if (block_size == page->settings.block_size && sample_rate == page->settings.sample_rate) {
			lv_disable(ui_SystemPrefsSaveButton);
			lv_disable(ui_SystemPrefsRevertButton);
		} else {
			lv_enable(ui_SystemPrefsSaveButton);
			lv_enable(ui_SystemPrefsRevertButton);
		}
	}

	PatchPlayLoader &patch_playloader;
	AudioSettings &settings;
	GuiState &gui_state;

	lv_group_t *group = nullptr;
};

} // namespace MetaModule
