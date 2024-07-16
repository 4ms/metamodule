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
	PrefsTab(PatchPlayLoader &patch_playloader, ViewSettings &settings, GuiState &gui_state)
		: patch_playloader{patch_playloader}
		, settings{settings}
		, gui_state{gui_state} {
		lv_obj_add_event_cb(ui_SystemPrefsSaveButton, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SystemPrefsRevertButton, revert_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_SystemPrefsAudioBlocksizeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		// lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, sample_rate_open, LV_EVENT_READY, this);
		// lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, sample_rate_close, LV_EVENT_CANCEL, this);
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
		auto sr_item = settings.sample_rate == ViewSettings::SampleRate::SR_24K ? 0 :
					   settings.sample_rate == ViewSettings::SampleRate::SR_48K ? 1 :
					   settings.sample_rate == ViewSettings::SampleRate::SR_96K ? 2 :
																				  1;
		lv_dropdown_set_selected(ui_SystemPrefsAudioSampleRateDropdown, sr_item);

		auto bs_item = settings.block_size == ViewSettings::BlockSize::BS_32  ? 0 :
					   settings.block_size == ViewSettings::BlockSize::BS_64  ? 1 :
					   settings.block_size == ViewSettings::BlockSize::BS_128 ? 2 :
					   settings.block_size == ViewSettings::BlockSize::BS_256 ? 3 :
					   settings.block_size == ViewSettings::BlockSize::BS_512 ? 4 :
																				1;
		lv_dropdown_set_selected(ui_SystemPrefsAudioBlocksizeDropdown, bs_item);

		gui_state.do_write_settings = false;

		lv_disable(ui_SystemPrefsSaveButton);
		lv_disable(ui_SystemPrefsRevertButton);
	}

	ViewSettings::SampleRate read_samplerate_dropdown() {
		auto sr_item = lv_dropdown_get_selected(ui_SystemPrefsAudioSampleRateDropdown);

		auto sample_rate = sr_item == 0 ? ViewSettings::SampleRate::SR_24K :
						   sr_item == 1 ? ViewSettings::SampleRate::SR_48K :
						   sr_item == 2 ? ViewSettings::SampleRate::SR_96K :
										  ViewSettings::SampleRate::SR_48K;
		return sample_rate;
	}

	ViewSettings::BlockSize read_blocksize_dropdown() {
		auto bs_item = lv_dropdown_get_selected(ui_SystemPrefsAudioBlocksizeDropdown);

		auto block_size = bs_item == 0 ? ViewSettings::BlockSize::BS_32 :
						  bs_item == 1 ? ViewSettings::BlockSize::BS_64 :
						  bs_item == 2 ? ViewSettings::BlockSize::BS_128 :
						  bs_item == 3 ? ViewSettings::BlockSize::BS_256 :
						  bs_item == 4 ? ViewSettings::BlockSize::BS_512 :
										 ViewSettings::BlockSize::BS_64;

		return block_size;
	}

	void update_settings_from_dropdown() {
		auto block_size = read_blocksize_dropdown();
		auto sample_rate = read_samplerate_dropdown();

		if (settings.block_size != block_size) {
			settings.block_size = block_size;
			patch_playloader.request_blocksize(std::to_underlying(block_size));
			gui_state.do_write_settings = true;
		}

		if (settings.sample_rate != sample_rate) {
			settings.sample_rate = sample_rate;
			patch_playloader.request_samplerate(std::to_underlying(sample_rate));
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

	// static void sample_rate_close(lv_event_t *event) {
	// 	if (!event || !event->user_data)
	// 		return;
	// 	auto page = static_cast<PrefsTab *>(event->user_data);
	// }

	// static void blocksize_cb(lv_event_t *event) {
	// 	if (!event || !event->user_data)
	// 		return;
	// 	auto page = static_cast<PrefsTab *>(event->user_data);
	// }

	// static void samplerate_cb(lv_event_t *event) {
	// 	if (!event || !event->user_data)
	// 		return;
	// 	auto page = static_cast<PrefsTab *>(event->user_data);
	// }

	PatchPlayLoader &patch_playloader;
	ViewSettings &settings;
	GuiState &gui_state;

	lv_group_t *group = nullptr;
};

} // namespace MetaModule
