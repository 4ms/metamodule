#pragma once
#include "fs/helpers.hh"
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/prefs_section_audio.hh"
#include "gui/slsexport/prefs_section_catchup.hh"
#include "gui/slsexport/prefs_section_fs.hh"
#include "gui/slsexport/prefs_section_midi.hh"
#include "gui/slsexport/prefs_section_missing_plugins.hh"
#include "gui/slsexport/prefs_section_screensaver.hh"
#include "gui/slsexport/ui_local.h"
#include "gui/styles.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/audio_settings.hh"

namespace MetaModule
{

struct PrefsTab : SystemMenuTab {

	PrefsTab(PatchPlayLoader &patch_playloader, UserSettings &settings, GuiState &gui_state)
		: patch_playloader{patch_playloader}
		, audio_settings{settings.audio}
		, screensaver{settings.screensaver}
		, catchup{settings.catchup}
		, gui_state{gui_state}
		, fs{settings.filesystem}
		, midi{settings.midi}
		, missing_plugins{settings.missing_plugins}
		, settings{settings} {

		audio_section.create(ui_SystemMenuPrefsTab);
		ssaver_section.create(ui_SystemMenuPrefsTab);
		catchup_section.create(ui_SystemMenuPrefsTab);
		fs_section.create(ui_SystemMenuPrefsTab);
		midi_section.create(ui_SystemMenuPrefsTab);
		missingplugins_section.create(ui_SystemMenuPrefsTab);

		auto btns = create_save_revert_buttons(ui_SystemMenuPrefsTab);
		save_button = lv_obj_get_child(btns, 1);
		revert_button = lv_obj_get_child(btns, 0);

		lv_hide(audio_section.sr_override_cont);
		lv_obj_set_style_text_color(audio_section.sr_override_cont, Gui::orange_highlight, 0);

		lv_hide(audio_section.bs_override_cont);
		lv_obj_set_style_text_color(audio_section.bs_override_cont, Gui::orange_highlight, 0);

		lv_obj_add_event_cb(save_button, save_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(revert_button, revert_cb, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(audio_section.blocksize_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(audio_section.overrun_retries, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(audio_section.samplerate_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ssaver_section.time_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ssaver_section.knobs_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(catchup_section.mode_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(catchup_section.allowjump_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(fs_section.startup_patch_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(fs_section.max_patches_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(midi_section.feedback_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(audio_section.sr_override_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(audio_section.bs_override_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(missingplugins_section.dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(audio_section.blocksize_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(audio_section.overrun_retries, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(audio_section.samplerate_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ssaver_section.time_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(ssaver_section.knobs_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(catchup_section.mode_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(catchup_section.allowjump_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(fs_section.startup_patch_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(fs_section.max_patches_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(midi_section.feedback_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(audio_section.sr_override_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(audio_section.bs_override_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(missingplugins_section.dropdown, focus_cb, LV_EVENT_FOCUSED, this);

		std::string opts;
		for (auto item : AudioSettings::ValidBlockSizes) {
			opts += std::to_string(item) + "\n";
		}
		if (opts.length())
			opts.pop_back();
		lv_dropdown_set_options(audio_section.blocksize_dropdown, opts.c_str());

		opts = "";
		for (auto item : AudioSettings::ValidOverrunRetries) {
			if (item == 0)
				opts += std::string("None");
			else
				opts += std::string("\n") + std::to_string(item);
		}

		lv_dropdown_set_options(audio_section.overrun_retries, opts.c_str());
		lv_obj_set_width(audio_section.samplerate_dropdown, 80);

		opts = "";
		for (auto item : AudioSettings::ValidSampleRates) {
			opts += samplerate_string(item) + "\n";
		}
		if (opts.length())
			opts.pop_back();
		lv_dropdown_set_options(audio_section.samplerate_dropdown, opts.c_str());

		auto set_options = [](auto const &ValidOptions, lv_obj_t *dropdown) {
			std::string opts = "";
			for (auto item : ValidOptions) {
				opts += std::string(item.label) + "\n";
			}
			if (opts.length())
				opts.pop_back();
			lv_dropdown_set_options(dropdown, opts.c_str());
		};

		set_options(ScreensaverSettings::ValidOptions, catchup_section.mode_dropdown);
		set_options(CatchupSettings::ValidOptions, catchup_section.mode_dropdown);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		// Remove all objects and re-add the tab side bar
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, lv_tabview_get_tab_btns(ui_SystemMenuTabView));

		// Add all dropdowns and switches inside containers
		lv_foreach_child(ui_SystemMenuPrefsTab, [&group](lv_obj_t *cont, unsigned) {
			lv_foreach_child(cont, [&group](lv_obj_t *obj, unsigned) {
				if (lv_obj_has_class(obj, &lv_dropdown_class)) {
					lv_group_add_obj(group, obj);
					lv_dropdown_close(obj);

				} else if (lv_obj_has_class(obj, &lv_switch_class)) {
					lv_group_add_obj(group, obj);

				} else if (lv_obj_has_class(obj, &lv_btn_class)) {
					lv_group_add_obj(group, obj);
				}
			});
		});

		lv_group_focus_obj(audio_section.samplerate_dropdown);
		lv_group_set_editing(group, true);

		auto startup_patch = std::string{volume_string(settings.initial_patch_vol)} + settings.initial_patch_name;
		lv_label_set_text(fs_section.startup_patch_label, startup_patch.c_str());

		lv_show(catchup_section.allowjump_cont);

		update_dropdowns_from_settings();
	}

	bool is_idle() override {
		return true;
	}

private:
	static std::string samplerate_string(uint32_t sr) {
		return std::to_string(sr / 1000) + "kHz";
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
		lv_dropdown_set_selected(audio_section.samplerate_dropdown, sr_item >= 0 ? sr_item : 1);

		auto bs_item =
			get_index(AudioSettings::ValidBlockSizes, [this](auto t) { return t == audio_settings.block_size; });
		lv_dropdown_set_selected(audio_section.blocksize_dropdown, bs_item >= 0 ? bs_item : 1);

		auto ovr_item = get_index(AudioSettings::ValidOverrunRetries,
								  [this](auto t) { return t == audio_settings.max_overrun_retries; });
		lv_dropdown_set_selected(audio_section.overrun_retries, ovr_item >= 0 ? ovr_item : 1);

		auto screensaver_item = get_index(ScreensaverSettings::ValidOptions,
										  [this](auto t) { return t.timeout_ms == screensaver.timeout_ms; });
		lv_dropdown_set_selected(ssaver_section.time_dropdown, screensaver_item >= 0 ? screensaver_item : 1);

		lv_check(ssaver_section.knobs_check, screensaver.knobs_can_wake);

		auto catchupmode_item =
			get_index(CatchupSettings::ValidOptions, [this](auto t) { return t.mode == catchup.mode; });
		lv_dropdown_set_selected(catchup_section.mode_dropdown, catchupmode_item >= 0 ? catchupmode_item : 1);

		lv_check(catchup_section.allowjump_check, catchup.allow_jump_outofrange);

		auto maxpatches_item = get_index(std::array{2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 25},
										 [this](uint32_t t) { return t == fs.max_open_patches; });
		lv_dropdown_set_selected(fs_section.max_patches_dropdown, maxpatches_item >= 0 ? maxpatches_item : 3);

		lv_check(fs_section.startup_patch_check, settings.load_initial_patch);

		lv_show(catchup_section.allowjump_cont, catchup.mode == CatchupParam::Mode::ResumeOnEqual);

		lv_check(midi_section.feedback_check, midi.midi_feedback == MidiSettings::MidiFeedback::Enabled);

		// Patch suggested audio toggles
		lv_check(audio_section.sr_override_check, settings.patch_suggested_audio.apply_samplerate);
		lv_check(audio_section.bs_override_check, settings.patch_suggested_audio.apply_blocksize);

		// Missing plugin autoload mode
		{
			int idx = settings.missing_plugins.autoload == MissingPluginSettings::Autoload::Ask	   ? 0 :
					  settings.missing_plugins.autoload == MissingPluginSettings::Autoload::Always ? 1 :
																									 2;
			lv_dropdown_set_selected(missingplugins_section.dropdown, idx);
		}

		gui_state.do_write_settings = false;

		lv_disable(save_button);
		lv_disable(revert_button);

		update_audio_override_status();
	}

	void update_audio_override_status() {
		auto [cur_sr, cur_bs, _] = patch_playloader.get_audio_settings();

		if (cur_sr >= 0 && cur_sr != settings.audio.sample_rate) {
			std::string msg = "Sample Rate:\n(default)";
			lv_label_set_text(audio_section.samplerate_label, msg.c_str());
			lv_obj_set_style_text_font(audio_section.samplerate_label, &ui_font_MuseoSansRounded70014, 0);

			lv_show(audio_section.sr_override_cont);
			lv_label_set_text(audio_section.sr_override_label, samplerate_string(cur_sr).c_str());

		} else {
			lv_label_set_text(audio_section.samplerate_label, "Sample Rate:");
			lv_obj_set_style_text_font(audio_section.samplerate_label, &ui_font_MuseoSansRounded70016, 0);
			lv_hide(audio_section.sr_override_cont);
		}

		if (cur_bs > 0 && cur_bs != settings.audio.block_size) {
			std::string msg = "Block Size:\n(default)";
			lv_label_set_text(audio_section.blocksize_label, msg.c_str());
			lv_obj_set_style_text_font(audio_section.blocksize_label, &ui_font_MuseoSansRounded70014, 0);

			lv_show(audio_section.bs_override_cont);
			lv_label_set_text_fmt(audio_section.bs_override_label, "%u", (unsigned)cur_bs);
		} else {
			lv_label_set_text(audio_section.blocksize_label, "Block size:");
			lv_obj_set_style_text_font(audio_section.blocksize_label, &ui_font_MuseoSansRounded70016, 0);
			lv_hide(audio_section.bs_override_cont);
		}
	}

	uint32_t read_samplerate_dropdown() {
		auto sr_item = lv_dropdown_get_selected(audio_section.samplerate_dropdown);

		if (sr_item >= 0 && sr_item < AudioSettings::ValidSampleRates.size())
			return AudioSettings::ValidSampleRates[sr_item];
		else
			return AudioSettings::DefaultSampleRate;
	}

	uint32_t read_blocksize_dropdown() {
		auto bs_item = lv_dropdown_get_selected(audio_section.blocksize_dropdown);

		if (bs_item >= 0 && bs_item < AudioSettings::ValidBlockSizes.size())
			return AudioSettings::ValidBlockSizes[bs_item];
		else
			return AudioSettings::DefaultBlockSize;
	}

	uint32_t read_overrun_dropdown() {
		auto ovr_item = lv_dropdown_get_selected(audio_section.overrun_retries);

		if (ovr_item >= 0 && ovr_item < AudioSettings::ValidOverrunRetries.size())
			return AudioSettings::ValidOverrunRetries[ovr_item];
		else
			return AudioSettings::DefaultOverrunRetries;
	}

	bool read_patch_suggest_samplerate_check() {
		return lv_obj_has_state(audio_section.sr_override_check, LV_STATE_CHECKED);
	}

	bool read_patch_suggest_blocksize_check() {
		return lv_obj_has_state(audio_section.bs_override_check, LV_STATE_CHECKED);
	}

	uint32_t read_timeout_dropdown() {
		auto to_item = lv_dropdown_get_selected(ssaver_section.time_dropdown);

		if (to_item >= 0 && to_item < ScreensaverSettings::ValidOptions.size())
			return ScreensaverSettings::ValidOptions[to_item].timeout_ms;
		else
			return ScreensaverSettings::defaultTimeout;
	}

	bool read_knobwake_check() {
		return lv_obj_has_state(ssaver_section.knobs_check, LV_STATE_CHECKED);
	}

	CatchupParam::Mode read_catchup_mode_dropdown() {
		auto item = lv_dropdown_get_selected(catchup_section.mode_dropdown);

		if (item >= 0 && item < CatchupSettings::ValidOptions.size()) {
			return CatchupSettings::ValidOptions[item].mode;
		} else {
			return CatchupSettings::DefaultMode;
		}
	}

	bool read_catchup_exclude_check() {
		return lv_obj_has_state(catchup_section.allowjump_check, LV_STATE_CHECKED);
	}

	uint32_t read_fs_max_open_patches() {
		std::array<char, 4> txt;
		lv_dropdown_get_selected_str(fs_section.max_patches_dropdown, txt.data(), txt.size());
		auto val = atoi(txt.data());
		return val > 0 ? val : FilesystemSettings::DefaultMaxOpenPatches;
	}

	auto read_midi_feedback_check() {
		return lv_obj_has_state(midi_section.feedback_check, LV_STATE_CHECKED) ? MidiSettings::MidiFeedback::Enabled :
																				 MidiSettings::MidiFeedback::Disabled;
	}

	MissingPluginSettings::Autoload read_missing_plugins_dropdown() {
		auto item = lv_dropdown_get_selected(missingplugins_section.dropdown);
		if (item == 1)
			return MissingPluginSettings::Autoload::Always;
		if (item == 2)
			return MissingPluginSettings::Autoload::Never;
		return MissingPluginSettings::Autoload::Ask;
	}

	// Update the settings structure from the dropdown and checkbox selections
	// This is called when the user clicks "Apply" or exits the prefs page
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

			// hide/show overrides
			update_audio_override_status();

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
			patch_playloader.update_param_catchup_mode();
			gui_state.do_write_settings = true;
		}

		if (settings.load_initial_patch != lv_obj_has_state(fs_section.startup_patch_check, LV_STATE_CHECKED)) {
			settings.load_initial_patch = lv_obj_has_state(fs_section.startup_patch_check, LV_STATE_CHECKED);
			gui_state.do_write_settings = true;
		}

		auto max_open_patches = read_fs_max_open_patches();

		if (fs.max_open_patches != max_open_patches) {
			fs.max_open_patches = max_open_patches;
			gui_state.do_write_settings = true;
		}

		auto midi_feedback = read_midi_feedback_check();
		if (midi.midi_feedback != midi_feedback) {
			midi.midi_feedback = midi_feedback;
			gui_state.do_write_settings = true;
		}

		// Patch suggested audio toggles
		auto apply_sr = read_patch_suggest_samplerate_check();
		auto apply_bs = read_patch_suggest_blocksize_check();
		if (settings.patch_suggested_audio.apply_samplerate != apply_sr ||
			settings.patch_suggested_audio.apply_blocksize != apply_bs)
		{
			settings.patch_suggested_audio.apply_samplerate = apply_sr;
			settings.patch_suggested_audio.apply_blocksize = apply_bs;
			gui_state.do_write_settings = true;
		}

		// Missing plugin autoload mode
		auto mp_mode = read_missing_plugins_dropdown();
		if (missing_plugins.autoload != mp_mode) {
			missing_plugins.autoload = mp_mode;
			gui_state.do_write_settings = true;
		}

		lv_disable(save_button);
		lv_disable(revert_button);
	}

	// Returns true if this page uses the back event
	bool consume_back_event() override {
		if (lv_dropdown_is_open(audio_section.samplerate_dropdown)) {
			lv_dropdown_close(audio_section.samplerate_dropdown);
			lv_group_focus_obj(audio_section.samplerate_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(audio_section.blocksize_dropdown)) {
			lv_dropdown_close(audio_section.blocksize_dropdown);
			lv_group_focus_obj(audio_section.blocksize_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(audio_section.overrun_retries)) {
			lv_dropdown_close(audio_section.overrun_retries);
			lv_group_focus_obj(audio_section.overrun_retries);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(ssaver_section.time_dropdown)) {
			lv_dropdown_close(ssaver_section.time_dropdown);
			lv_group_focus_obj(ssaver_section.time_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(catchup_section.mode_dropdown)) {
			lv_dropdown_close(catchup_section.mode_dropdown);
			lv_group_focus_obj(catchup_section.mode_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(fs_section.max_patches_dropdown)) {
			lv_dropdown_close(fs_section.max_patches_dropdown);
			lv_group_focus_obj(fs_section.max_patches_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(missingplugins_section.dropdown)) {
			lv_dropdown_close(missingplugins_section.dropdown);
			lv_group_focus_obj(missingplugins_section.dropdown);
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
		if (auto page = static_cast<PrefsTab *>(event->user_data))
			page->do_changed_cb();
	}

	void do_changed_cb() {
		auto block_size = read_blocksize_dropdown();
		auto sample_rate = read_samplerate_dropdown();
		auto overrun_retries = read_overrun_dropdown();
		auto timeout = read_timeout_dropdown();
		auto knobwake = read_knobwake_check();
		auto catchupmode = read_catchup_mode_dropdown();
		auto catchup_exclude_buttons = read_catchup_exclude_check();
		auto fs_max_patches = read_fs_max_open_patches();
		auto midi_feedback = read_midi_feedback_check();
		auto apply_sr = read_patch_suggest_samplerate_check();
		auto apply_bs = read_patch_suggest_blocksize_check();
		auto load_initial_patch = lv_obj_has_state(fs_section.startup_patch_check, LV_STATE_CHECKED);
		auto mp_mode = read_missing_plugins_dropdown();

		lv_show(catchup_section.allowjump_cont, catchupmode == CatchupParam::Mode::ResumeOnEqual);

		if (block_size == audio_settings.block_size && sample_rate == audio_settings.sample_rate &&
			overrun_retries == audio_settings.max_overrun_retries && timeout == screensaver.timeout_ms &&
			knobwake == screensaver.knobs_can_wake && catchupmode == catchup.mode &&
			catchup_exclude_buttons == catchup.allow_jump_outofrange &&
			load_initial_patch == settings.load_initial_patch && fs_max_patches == fs.max_open_patches &&
			midi_feedback == midi.midi_feedback && mp_mode == missing_plugins.autoload &&
			apply_sr == settings.patch_suggested_audio.apply_samplerate &&
			apply_bs == settings.patch_suggested_audio.apply_blocksize)
		{
			lv_disable(save_button);
			lv_disable(revert_button);
		} else {
			lv_enable(save_button);
			lv_enable(revert_button);
		}

		// If user flips Allow Patch to Override switch off, then change current audio settings
		if (!apply_sr && settings.patch_suggested_audio.apply_samplerate) {
			// Change samplerate back to default:
			auto [cur_sr, cur_bs, cur_mr] = patch_playloader.get_audio_settings();
			patch_playloader.request_new_audio_settings(audio_settings.sample_rate, cur_bs, cur_mr);

			// Reload page:
			settings.patch_suggested_audio.apply_samplerate = apply_sr;
			settings.patch_suggested_audio.apply_blocksize = apply_bs;

			update_dropdowns_from_settings();
			lv_enable(save_button);
			lv_enable(revert_button);
		}
		if (!apply_bs && settings.patch_suggested_audio.apply_blocksize) {
			// Change blocksize back to default:
			auto [cur_sr, cur_bs, cur_mr] = patch_playloader.get_audio_settings();
			patch_playloader.request_new_audio_settings(cur_sr, audio_settings.block_size, cur_mr);

			// Reload page:
			settings.patch_suggested_audio.apply_samplerate = apply_sr;
			settings.patch_suggested_audio.apply_blocksize = apply_bs;

			update_dropdowns_from_settings();
			lv_enable(save_button);
			lv_enable(revert_button);
		}
	}

	static void focus_cb(lv_event_t *event) {
		if (!event)
			return;

		auto page = static_cast<PrefsTab *>(event->user_data);

		auto target = event->target;

		// scroll to bottom if we select last items
		if (target == page->missingplugins_section.dropdown) {
			lv_obj_scroll_to_view_recursive(page->save_button, LV_ANIM_ON);

			// scroll to top if we select first items
		} else if (target == page->audio_section.blocksize_dropdown ||
				   target == page->audio_section.samplerate_dropdown)
		{
			lv_obj_scroll_to_y(ui_SystemMenuPrefsTab, 0, LV_ANIM_ON);
		}
	}

	PatchPlayLoader &patch_playloader;
	AudioSettings &audio_settings;
	ScreensaverSettings &screensaver;
	CatchupSettings &catchup;
	GuiState &gui_state;
	FilesystemSettings &fs;
	MidiSettings &midi;
	MissingPluginSettings &missing_plugins;
	UserSettings &settings;

	lv_group_t *group = nullptr;

	PrefsSectionAudio audio_section;
	PrefsSectionScreenSaver ssaver_section;
	PrefsSectionCatchupMode catchup_section;
	PrefsSectionFilesystem fs_section;
	PrefsSectionMidi midi_section;
	PrefsSectionMissingPlugins missingplugins_section;

	lv_obj_t *save_button;
	lv_obj_t *revert_button;
};

} // namespace MetaModule
