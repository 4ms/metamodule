#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/prefs_menu.hh"
#include "patch_play/patch_playloader.hh"
#include "src/core/lv_obj_scroll.h"
#include "user_settings/audio_settings.hh"
#include <functional>

namespace MetaModule
{

struct PrefsTab : SystemMenuTab {
	PrefsTab(PatchPlayLoader &patch_playloader,
			 AudioSettings &audio_settings,
			 ScreensaverSettings &screensaver,
			 CatchupSettings &catchup,
			 GuiState &gui_state)
		: patch_playloader{patch_playloader}
		, audio_settings{audio_settings}
		, screensaver{screensaver}
		, catchup{catchup}
		, gui_state{gui_state} {
		init_SystemPrefsCatchupPane(ui_SystemMenuPrefsTab);

		lv_obj_add_event_cb(ui_SystemPrefsSaveButton, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SystemPrefsRevertButton, revert_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_SystemPrefsAudioBlocksizeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverTimeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverKnobsCheck, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupModeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupExcludeButtonsCheck, changed_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_SystemPrefsAudioBlocksizeDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverTimeDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverKnobsCheck, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupModeDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupExcludeButtonsCheck, focus_cb, LV_EVENT_FOCUSED, nullptr);

		lv_obj_move_foreground(ui_SystemPrefsButtonCont);

		std::string opts;
		for (auto item : AudioSettings::ValidBlockSizes) {
			opts += std::to_string(item) + "\n";
		}
		if (opts.length())
			opts.pop_back();
		lv_dropdown_set_options(ui_SystemPrefsAudioBlocksizeDropdown, opts.c_str());

		opts = "";
		for (auto item : AudioSettings::ValidSampleRates) {
			opts += std::to_string(item) + "\n";
		}
		if (opts.length())
			opts.pop_back();
		lv_dropdown_set_options(ui_SystemPrefsAudioSampleRateDropdown, opts.c_str());

		auto set_options = [](auto const &ValidOptions, lv_obj_t *dropdown) {
			std::string opts = "";
			for (auto item : ValidOptions) {
				opts += std::string(item.label) + "\n";
			}
			if (opts.length())
				opts.pop_back();
			lv_dropdown_set_options(dropdown, opts.c_str());
		};

		set_options(ScreensaverSettings::ValidOptions, ui_SystemPrefsCatchupModeDropdown);
		set_options(CatchupSettings::ValidOptions, ui_SystemPrefsCatchupModeDropdown);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		lv_group_remove_obj(ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_remove_obj(ui_SystemPrefsAudioBlocksizeDropdown);
		lv_group_remove_obj(ui_SystemPrefsScreensaverTimeDropdown);
		lv_group_remove_obj(ui_SystemPrefsScreensaverKnobsCheck);
		lv_group_remove_obj(ui_SystemPrefsCatchupModeDropdown);
		lv_group_remove_obj(ui_SystemPrefsCatchupExcludeButtonsCheck);
		lv_group_remove_obj(ui_SystemPrefsRevertButton);
		lv_group_remove_obj(ui_SystemPrefsSaveButton);

		lv_group_add_obj(group, ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_add_obj(group, ui_SystemPrefsAudioBlocksizeDropdown);
		lv_group_add_obj(group, ui_SystemPrefsScreensaverTimeDropdown);
		lv_group_add_obj(group, ui_SystemPrefsScreensaverKnobsCheck);
		lv_group_add_obj(group, ui_SystemPrefsCatchupModeDropdown);
		lv_group_add_obj(group, ui_SystemPrefsCatchupExcludeButtonsCheck);
		lv_group_add_obj(group, ui_SystemPrefsRevertButton);
		lv_group_add_obj(group, ui_SystemPrefsSaveButton);

		lv_dropdown_close(ui_SystemPrefsAudioSampleRateDropdown);
		lv_dropdown_close(ui_SystemPrefsAudioBlocksizeDropdown);
		lv_dropdown_close(ui_SystemPrefsScreensaverTimeDropdown);
		lv_dropdown_close(ui_SystemPrefsCatchupModeDropdown);

		lv_group_focus_obj(ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_set_editing(group, true);

		//todo: implement this
		lv_hide(ui_SystemPrefsCatchupExcludeButtonsCont);

		update_dropdowns_from_settings();
	}

	void update_dropdowns_from_settings() {
		auto get_index = [](auto dataset, auto test) {
			int idx = -1;
			if (auto found = std::find_if(dataset.begin(), dataset.end(), test)) {
				idx = std::distance(dataset.begin(), found);
			}
			return idx;
		};
		auto sr_item =
			get_index(AudioSettings::ValidSampleRates, [this](auto t) { return t == audio_settings.sample_rate; });
		lv_dropdown_set_selected(ui_SystemPrefsAudioSampleRateDropdown, sr_item >= 0 ? sr_item : 1);

		auto bs_item =
			get_index(AudioSettings::ValidBlockSizes, [this](auto t) { return t == audio_settings.block_size; });
		lv_dropdown_set_selected(ui_SystemPrefsAudioBlocksizeDropdown, bs_item >= 0 ? bs_item : 1);

		auto screensaver_item = get_index(ScreensaverSettings::ValidOptions,
										  [this](auto t) { return t.timeout_ms == screensaver.timeout_ms; });
		lv_dropdown_set_selected(ui_SystemPrefsScreensaverTimeDropdown, screensaver_item >= 0 ? screensaver_item : 1);

		lv_check(ui_SystemPrefsScreensaverKnobsCheck, screensaver.knobs_can_wake);

		auto catchupmode_item =
			get_index(CatchupSettings::ValidOptions, [this](auto t) { return t.mode == catchup.mode; });
		lv_dropdown_set_selected(ui_SystemPrefsCatchupModeDropdown, catchupmode_item >= 0 ? catchupmode_item : 1);

		lv_check(ui_SystemPrefsCatchupExcludeButtonsCheck, catchup.button_exclude);

		gui_state.do_write_settings = false;

		lv_disable(ui_SystemPrefsSaveButton);
		lv_disable(ui_SystemPrefsRevertButton);
	}

	uint32_t read_samplerate_dropdown() {
		auto sr_item = lv_dropdown_get_selected(ui_SystemPrefsAudioSampleRateDropdown);

		if (sr_item >= 0 && sr_item < AudioSettings::ValidSampleRates.size())
			return AudioSettings::ValidSampleRates[sr_item];
		else
			return AudioSettings::DefaultSampleRate;
	}

	uint32_t read_blocksize_dropdown() {
		auto bs_item = lv_dropdown_get_selected(ui_SystemPrefsAudioBlocksizeDropdown);

		if (bs_item >= 0 && bs_item < AudioSettings::ValidBlockSizes.size())
			return AudioSettings::ValidBlockSizes[bs_item];
		else
			return AudioSettings::DefaultBlockSize;
	}

	uint32_t read_timeout_dropdown() {
		auto to_item = lv_dropdown_get_selected(ui_SystemPrefsScreensaverTimeDropdown);

		if (to_item >= 0 && to_item < ScreensaverSettings::ValidOptions.size())
			return ScreensaverSettings::ValidOptions[to_item].timeout_ms;
		else
			return ScreensaverSettings::defaultTimeout;
	}

	bool read_knobwake_check() {
		return lv_obj_has_state(ui_SystemPrefsScreensaverKnobsCheck, LV_STATE_CHECKED);
	}

	CatchupParam::Mode read_catchup_mode_dropdown() {
		auto item = lv_dropdown_get_selected(ui_SystemPrefsCatchupModeDropdown);

		if (item >= 0 && item < CatchupSettings::ValidOptions.size()) {
			return CatchupSettings::ValidOptions[item].mode;
		} else {
			return CatchupSettings::DefaultMode;
		}
	}

	bool read_catchup_exclude_check() {
		return lv_obj_has_state(ui_SystemPrefsCatchupExcludeButtonsCheck, LV_STATE_CHECKED);
	}

	void update_settings_from_dropdown() {
		auto block_size = read_blocksize_dropdown();
		auto sample_rate = read_samplerate_dropdown();

		if (audio_settings.block_size != block_size || audio_settings.sample_rate != sample_rate) {

			audio_settings.block_size = block_size;
			audio_settings.sample_rate = sample_rate;

			patch_playloader.request_new_audio_settings(sample_rate, block_size);
			gui_state.do_write_settings = true;
		}

		auto timeout = read_timeout_dropdown();
		auto knobwake = read_knobwake_check();

		if (screensaver.timeout_ms != timeout || screensaver.knobs_can_wake != knobwake) {
			screensaver.timeout_ms = timeout;
			screensaver.knobs_can_wake = knobwake;
			gui_state.do_write_settings = true;
		}

		auto catchupmode = read_catchup_mode_dropdown();
		auto catchup_exclude_buttons = read_catchup_exclude_check();

		if (catchup.mode != catchupmode || catchup.button_exclude != catchup_exclude_buttons) {
			catchup.mode = catchupmode;
			catchup.button_exclude = catchup_exclude_buttons;
			patch_playloader.set_all_param_catchup_mode(catchup.mode, catchup.button_exclude);
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

		} else if (lv_dropdown_is_open(ui_SystemPrefsScreensaverTimeDropdown)) {
			lv_dropdown_close(ui_SystemPrefsScreensaverTimeDropdown);
			lv_group_focus_obj(ui_SystemPrefsScreensaverTimeDropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(ui_SystemPrefsCatchupModeDropdown)) {
			lv_dropdown_close(ui_SystemPrefsCatchupModeDropdown);
			lv_group_focus_obj(ui_SystemPrefsCatchupModeDropdown);
			lv_group_set_editing(group, false);
			return true;

		} else {
			update_settings_from_dropdown();
			return false;
		}
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
		auto timeout = page->read_timeout_dropdown();
		auto knobwake = page->read_knobwake_check();
		auto catchupmode = page->read_catchup_mode_dropdown();
		auto catchup_exclude_buttons = page->read_catchup_exclude_check();

		if (block_size == page->audio_settings.block_size && sample_rate == page->audio_settings.sample_rate &&
			timeout == page->screensaver.timeout_ms && knobwake == page->screensaver.knobs_can_wake &&
			catchupmode == page->catchup.mode && catchup_exclude_buttons == page->catchup.button_exclude)
		{
			lv_disable(ui_SystemPrefsSaveButton);
			lv_disable(ui_SystemPrefsRevertButton);
		} else {
			lv_enable(ui_SystemPrefsSaveButton);
			lv_enable(ui_SystemPrefsRevertButton);
		}
	}

	static void focus_cb(lv_event_t *event) {
		if (!event)
			return;

		auto tar = event->target;

		if (tar == ui_SystemPrefsCatchupModeDropdown || tar == ui_SystemPrefsCatchupExcludeButtonsCheck) {
			lv_obj_scroll_to_view_recursive(ui_SystemPrefsSaveButton, LV_ANIM_ON);

		} else if (tar == ui_SystemPrefsAudioBlocksizeDropdown || tar == ui_SystemPrefsAudioSampleRateDropdown) {
			lv_obj_scroll_to_y(ui_SystemMenuPrefsTab, 0, LV_ANIM_ON);
		}
	}

	PatchPlayLoader &patch_playloader;
	AudioSettings &audio_settings;
	ScreensaverSettings &screensaver;
	CatchupSettings &catchup;
	GuiState &gui_state;

	lv_group_t *group = nullptr;
};

} // namespace MetaModule
