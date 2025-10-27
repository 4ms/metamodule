#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/prefs_pane_catchup.hh"
#include "gui/slsexport/prefs_pane_fs.hh"
#include "patch_play/patch_playloader.hh"
#include "src/core/lv_obj_scroll.h"
#include "user_settings/audio_settings.hh"

namespace MetaModule
{

struct PrefsTab : SystemMenuTab {
	PrefsTab(PatchPlayLoader &patch_playloader,
			 AudioSettings &audio_settings,
			 ScreensaverSettings &screensaver,
			 CatchupSettings &catchup,
			 FilesystemSettings &fs,
			 GuiState &gui_state)
		: patch_playloader{patch_playloader}
		, audio_settings{audio_settings}
		, screensaver{screensaver}
		, catchup{catchup}
		, gui_state{gui_state}
		, fs{fs} {
		init_SystemPrefsCatchupPane(ui_SystemMenuPrefsTab);
		init_SystemPrefsFSPane(ui_SystemMenuPrefsTab);

		lv_obj_add_event_cb(ui_SystemPrefsSaveButton, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SystemPrefsRevertButton, revert_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(ui_SystemPrefsAudioBlocksizeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsAudioOverrunRetriesDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverTimeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverKnobsCheck, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupModeDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupAllowJumpOutOfRangeCheck, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_SystemPrefsFSMaxPatchesDropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_SystemPrefsAudioBlocksizeDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsAudioOverrunRetriesDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsAudioSampleRateDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverTimeDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsScreensaverKnobsCheck, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupModeDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsCatchupAllowJumpOutOfRangeCheck, focus_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemPrefsFSMaxPatchesDropdown, focus_cb, LV_EVENT_FOCUSED, nullptr);

		lv_obj_move_foreground(ui_SystemPrefsButtonCont);

		std::string opts;
		for (auto item : AudioSettings::ValidBlockSizes) {
			opts += std::to_string(item) + "\n";
		}
		if (opts.length())
			opts.pop_back();
		lv_dropdown_set_options(ui_SystemPrefsAudioBlocksizeDropdown, opts.c_str());

		opts = std::accumulate(AudioSettings::ValidOverrunRetries.begin(),
							   AudioSettings::ValidOverrunRetries.end(),
							   std::string(""),
							   [](std::string const &sum, uint32_t item) {
								   if (item == 0)
									   return std::string("None");
								   else
									   return sum + std::string("\n") + std::to_string(item);
							   });

		lv_dropdown_set_options(ui_SystemPrefsAudioOverrunRetriesDropdown, opts.c_str());

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
		lv_group_remove_obj(ui_SystemPrefsAudioOverrunRetriesDropdown);
		lv_group_remove_obj(ui_SystemPrefsScreensaverTimeDropdown);
		lv_group_remove_obj(ui_SystemPrefsScreensaverKnobsCheck);
		lv_group_remove_obj(ui_SystemPrefsCatchupModeDropdown);
		lv_group_remove_obj(ui_SystemPrefsCatchupAllowJumpOutOfRangeCheck);
		lv_group_remove_obj(ui_SystemPrefsFSMaxPatchesDropdown);

		lv_group_remove_obj(ui_SystemPrefsRevertButton);
		lv_group_remove_obj(ui_SystemPrefsSaveButton);

		lv_group_add_obj(group, ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_add_obj(group, ui_SystemPrefsAudioBlocksizeDropdown);
		lv_group_add_obj(group, ui_SystemPrefsAudioOverrunRetriesDropdown);
		lv_group_add_obj(group, ui_SystemPrefsScreensaverTimeDropdown);
		lv_group_add_obj(group, ui_SystemPrefsScreensaverKnobsCheck);
		lv_group_add_obj(group, ui_SystemPrefsCatchupModeDropdown);
		lv_group_add_obj(group, ui_SystemPrefsCatchupAllowJumpOutOfRangeCheck);
		lv_group_add_obj(group, ui_SystemPrefsFSMaxPatchesDropdown);
		lv_group_add_obj(group, ui_SystemPrefsRevertButton);
		lv_group_add_obj(group, ui_SystemPrefsSaveButton);

		lv_dropdown_close(ui_SystemPrefsAudioSampleRateDropdown);
		lv_dropdown_close(ui_SystemPrefsAudioBlocksizeDropdown);
		lv_dropdown_close(ui_SystemPrefsAudioOverrunRetriesDropdown);
		lv_dropdown_close(ui_SystemPrefsScreensaverTimeDropdown);
		lv_dropdown_close(ui_SystemPrefsCatchupModeDropdown);
		lv_dropdown_close(ui_SystemPrefsFSMaxPatchesDropdown);

		lv_group_focus_obj(ui_SystemPrefsAudioSampleRateDropdown);
		lv_group_set_editing(group, true);

		lv_show(ui_SystemPrefsCatchupAllowJumpOutofRangeCont);

		update_dropdowns_from_settings();
	}

	bool is_idle() override {
		return true;
	}

private:
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

		auto ovr_item = get_index(AudioSettings::ValidOverrunRetries,
								  [this](auto t) { return t == audio_settings.max_overrun_retries; });
		lv_dropdown_set_selected(ui_SystemPrefsAudioOverrunRetriesDropdown, ovr_item >= 0 ? ovr_item : 1);

		auto screensaver_item = get_index(ScreensaverSettings::ValidOptions,
										  [this](auto t) { return t.timeout_ms == screensaver.timeout_ms; });
		lv_dropdown_set_selected(ui_SystemPrefsScreensaverTimeDropdown, screensaver_item >= 0 ? screensaver_item : 1);

		lv_check(ui_SystemPrefsScreensaverKnobsCheck, screensaver.knobs_can_wake);

		auto catchupmode_item =
			get_index(CatchupSettings::ValidOptions, [this](auto t) { return t.mode == catchup.mode; });
		lv_dropdown_set_selected(ui_SystemPrefsCatchupModeDropdown, catchupmode_item >= 0 ? catchupmode_item : 1);

		lv_check(ui_SystemPrefsCatchupAllowJumpOutOfRangeCheck, catchup.allow_jump_outofrange);

		auto maxpatches_item = get_index(std::array{2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25},
										 [this](uint32_t t) { return t == fs.max_open_patches; });
		lv_dropdown_set_selected(ui_SystemPrefsFSMaxPatchesDropdown, maxpatches_item >= 0 ? maxpatches_item : 3);

		lv_show(ui_SystemPrefsCatchupAllowJumpOutofRangeCont, catchup.mode == CatchupParam::Mode::ResumeOnEqual);

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

	uint32_t read_overrun_dropdown() {
		auto ovr_item = lv_dropdown_get_selected(ui_SystemPrefsAudioOverrunRetriesDropdown);

		if (ovr_item >= 0 && ovr_item < AudioSettings::ValidOverrunRetries.size())
			return AudioSettings::ValidOverrunRetries[ovr_item];
		else
			return AudioSettings::DefaultOverrunRetries;
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
		return lv_obj_has_state(ui_SystemPrefsCatchupAllowJumpOutOfRangeCheck, LV_STATE_CHECKED);
	}

	uint32_t read_fs_max_open_patches() {
		std::array<char, 4> txt;
		lv_dropdown_get_selected_str(ui_SystemPrefsFSMaxPatchesDropdown, txt.data(), txt.size());
		auto val = atoi(txt.data());
		return val > 0 ? val : FilesystemSettings::DefaultMaxOpenPatches;
	}

	void update_settings_from_dropdown() {
		auto block_size = read_blocksize_dropdown();
		auto sample_rate = read_samplerate_dropdown();
		auto max_overrun_retries = read_overrun_dropdown();

		if (audio_settings.block_size != block_size || audio_settings.sample_rate != sample_rate ||
			audio_settings.max_overrun_retries != max_overrun_retries)
		{

			audio_settings.block_size = block_size;
			audio_settings.sample_rate = sample_rate;
			audio_settings.max_overrun_retries = max_overrun_retries;

			patch_playloader.request_new_audio_settings(sample_rate, block_size, max_overrun_retries);
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

		if (catchup.mode != catchupmode || catchup.allow_jump_outofrange != catchup_exclude_buttons) {
			catchup.mode = catchupmode;
			catchup.allow_jump_outofrange = catchup_exclude_buttons;
			patch_playloader.set_all_param_catchup_mode(catchup.mode, catchup.allow_jump_outofrange);
			gui_state.do_write_settings = true;
		}

		auto max_open_patches = read_fs_max_open_patches();

		if (fs.max_open_patches != max_open_patches) {
			fs.max_open_patches = max_open_patches;
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

		} else if (lv_dropdown_is_open(ui_SystemPrefsAudioOverrunRetriesDropdown)) {
			lv_dropdown_close(ui_SystemPrefsAudioOverrunRetriesDropdown);
			lv_group_focus_obj(ui_SystemPrefsAudioOverrunRetriesDropdown);
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

		} else if (lv_dropdown_is_open(ui_SystemPrefsFSMaxPatchesDropdown)) {
			lv_dropdown_close(ui_SystemPrefsFSMaxPatchesDropdown);
			lv_group_focus_obj(ui_SystemPrefsFSMaxPatchesDropdown);
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
		auto overrun_retries = page->read_overrun_dropdown();
		auto timeout = page->read_timeout_dropdown();
		auto knobwake = page->read_knobwake_check();
		auto catchupmode = page->read_catchup_mode_dropdown();
		auto catchup_exclude_buttons = page->read_catchup_exclude_check();
		auto fs_max_patches = page->read_fs_max_open_patches();

		if (block_size == page->audio_settings.block_size && sample_rate == page->audio_settings.sample_rate &&
			overrun_retries == page->audio_settings.max_overrun_retries && timeout == page->screensaver.timeout_ms &&
			knobwake == page->screensaver.knobs_can_wake && catchupmode == page->catchup.mode &&
			catchup_exclude_buttons == page->catchup.allow_jump_outofrange &&
			fs_max_patches == page->fs.max_open_patches)
		{
			lv_disable(ui_SystemPrefsSaveButton);
			lv_disable(ui_SystemPrefsRevertButton);
		} else {
			lv_enable(ui_SystemPrefsSaveButton);
			lv_enable(ui_SystemPrefsRevertButton);
		}

		lv_show(ui_SystemPrefsCatchupAllowJumpOutofRangeCont, catchupmode == CatchupParam::Mode::ResumeOnEqual);
	}

	static void focus_cb(lv_event_t *event) {
		if (!event)
			return;

		auto target = event->target;

		// scroll to bottom if we select last items
		// if (target == ui_SystemPrefsCatchupModeDropdown || target == ui_SystemPrefsCatchupExcludeButtonsCheck ||
		if (target == ui_SystemPrefsFSMaxPatchesDropdown) {
			lv_obj_scroll_to_view_recursive(ui_SystemPrefsSaveButton, LV_ANIM_ON);

			// scroll to top if we select first items
		} else if (target == ui_SystemPrefsAudioBlocksizeDropdown || target == ui_SystemPrefsAudioSampleRateDropdown) {
			lv_obj_scroll_to_y(ui_SystemMenuPrefsTab, 0, LV_ANIM_ON);
		}
	}

	PatchPlayLoader &patch_playloader;
	AudioSettings &audio_settings;
	ScreensaverSettings &screensaver;
	CatchupSettings &catchup;
	GuiState &gui_state;
	FilesystemSettings &fs;

	lv_group_t *group = nullptr;
};

} // namespace MetaModule
