#pragma once
#include "fs/helpers.hh"
#include "gui/colors/color_styles.hh"
#include "gui/gui_state.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/prefs_section_audio.hh"
#include "gui/slsexport/prefs_section_button_exp_knobset.hh"
#include "gui/slsexport/prefs_section_catchup.hh"
#include "gui/slsexport/prefs_section_color_scheme.hh"
#include "gui/slsexport/prefs_section_fs.hh"
#include "gui/slsexport/prefs_section_midi.hh"
#include "gui/slsexport/prefs_section_missing_plugins.hh"
#include "gui/slsexport/prefs_section_notifications.hh"
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
		, button_exp_knobset{settings.button_exp_knobset}
		, notifications{settings.notifications}
		, color_scheme{settings.color_scheme}
		, settings{settings} {

		audio_section.create(ui_SystemMenuPrefsTab);
		ssaver_section.create(ui_SystemMenuPrefsTab);
		catchup_section.create(ui_SystemMenuPrefsTab);
		fs_section.create(ui_SystemMenuPrefsTab);
		midi_section.create(ui_SystemMenuPrefsTab);
		buttonexpknobset_section.create(ui_SystemMenuPrefsTab);
		missingplugins_section.create(ui_SystemMenuPrefsTab);
		notifications_section.create(ui_SystemMenuPrefsTab);
		color_scheme_section.create(ui_SystemMenuPrefsTab);

		auto btns = create_save_revert_buttons(ui_SystemMenuPrefsTab);
		save_button = lv_obj_get_child(btns, 1);
		revert_button = lv_obj_get_child(btns, 0);

		lv_hide(audio_section.sr_override_cont);
		lv_obj_add_style(audio_section.sr_override_cont, scheme_text(METACOLOR_PRIMARY_HIGHLIGHT), 0);

		lv_hide(audio_section.bs_override_cont);
		lv_obj_add_style(audio_section.bs_override_cont, scheme_text(METACOLOR_PRIMARY_HIGHLIGHT), 0);

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
		lv_obj_add_event_cb(midi_section.knobset_control_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(midi_section.knobset_cc_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(midi_section.knobset_channel_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(audio_section.sr_override_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(audio_section.bs_override_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(missingplugins_section.dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(buttonexpknobset_section.expander_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(buttonexpknobset_section.require_back_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(notifications_section.amount_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(notifications_section.animation_check, changed_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(color_scheme_section.scheme_dropdown, changed_cb, LV_EVENT_VALUE_CHANGED, this);

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
		lv_obj_add_event_cb(midi_section.knobset_control_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(midi_section.knobset_cc_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(midi_section.knobset_channel_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(audio_section.sr_override_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(audio_section.bs_override_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(missingplugins_section.dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(buttonexpknobset_section.expander_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(buttonexpknobset_section.require_back_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(notifications_section.amount_dropdown, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(notifications_section.animation_check, focus_cb, LV_EVENT_FOCUSED, this);
		lv_obj_add_event_cb(color_scheme_section.scheme_dropdown, focus_cb, LV_EVENT_FOCUSED, this);

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
		set_options(ButtonExpKnobSetSettings::ValidOptions, buttonexpknobset_section.expander_dropdown);
		set_options(NotificationSettings::ValidAmountOptions, notifications_section.amount_dropdown);

		std::string scheme_opts;
		for (unsigned i = 0; i < Scheme::count(); ++i) {
			scheme_opts += std::string(Scheme::name(i)) + "\n";
		}
		if (scheme_opts.length())
			scheme_opts.pop_back();
		lv_dropdown_set_options(color_scheme_section.scheme_dropdown, scheme_opts.c_str());
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
		lv_check(midi_section.knobset_control_check, midi.knobset_control == MidiSettings::KnobsetControl::Enabled);
		lv_dropdown_set_selected(midi_section.knobset_cc_dropdown, midi.knobset_cc);
		lv_dropdown_set_selected(midi_section.knobset_channel_dropdown, midi.knobset_channel - 1);
		update_knobset_control_items(midi.knobset_control == MidiSettings::KnobsetControl::Enabled);

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

		// Button expander knob set
		auto bexp_item = get_index(ButtonExpKnobSetSettings::ValidOptions,
								   [this](auto t) { return t.value == button_exp_knobset.button_expander; });
		lv_dropdown_set_selected(buttonexpknobset_section.expander_dropdown, bexp_item >= 0 ? bexp_item : 0);
		lv_check(buttonexpknobset_section.require_back_check, button_exp_knobset.require_back);
		update_require_back_enabled(button_exp_knobset.button_expander != 0);

		// Notifications
		auto notif_item = get_index(NotificationSettings::ValidAmountOptions,
									[this](auto t) { return t.value == notifications.amount; });
		lv_dropdown_set_selected(notifications_section.amount_dropdown, notif_item >= 0 ? notif_item : 0);
		lv_check(notifications_section.animation_check, notifications.animation);

		// Color scheme: select the persisted id and re-apply (revert path also lands here).
		lv_dropdown_set_selected(color_scheme_section.scheme_dropdown, color_scheme.scheme_id);
		apply_scheme(color_scheme.scheme_id);

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

	auto read_knobset_control_check() {
		return lv_obj_has_state(midi_section.knobset_control_check, LV_STATE_CHECKED) ?
				   MidiSettings::KnobsetControl::Enabled :
				   MidiSettings::KnobsetControl::Disabled;
	}

	void update_knobset_control_items(bool enabled) {
		lv_enable(midi_section.knobset_cc_dropdown, enabled);
		lv_enable(midi_section.knobset_channel_dropdown, enabled);
		auto opa = enabled ? LV_OPA_100 : LV_OPA_50;
		lv_obj_set_style_opa(lv_obj_get_parent(midi_section.knobset_cc_dropdown), opa, LV_PART_MAIN);
		lv_obj_set_style_opa(lv_obj_get_parent(midi_section.knobset_channel_dropdown), opa, LV_PART_MAIN);
	}

	uint32_t read_knobset_cc_dropdown() {
		return lv_dropdown_get_selected(midi_section.knobset_cc_dropdown);
	}

	uint32_t read_knobset_channel_dropdown() {
		return lv_dropdown_get_selected(midi_section.knobset_channel_dropdown) + 1;
	}

	MissingPluginSettings::Autoload read_missing_plugins_dropdown() {
		auto item = lv_dropdown_get_selected(missingplugins_section.dropdown);
		if (item == 1)
			return MissingPluginSettings::Autoload::Always;
		if (item == 2)
			return MissingPluginSettings::Autoload::Never;
		return MissingPluginSettings::Autoload::Ask;
	}

	uint32_t read_button_exp_knobset_dropdown() {
		auto item = lv_dropdown_get_selected(buttonexpknobset_section.expander_dropdown);
		if (item >= 0 && item < ButtonExpKnobSetSettings::ValidOptions.size())
			return ButtonExpKnobSetSettings::ValidOptions[item].value;
		else
			return ButtonExpKnobSetSettings::DefaultButtonExpander;
	}

	bool read_require_back_check() {
		return lv_obj_has_state(buttonexpknobset_section.require_back_check, LV_STATE_CHECKED);
	}

	NotificationSettings::Amount read_notification_amount_dropdown() {
		auto item = lv_dropdown_get_selected(notifications_section.amount_dropdown);
		if (item >= 0 && item < NotificationSettings::ValidAmountOptions.size())
			return NotificationSettings::ValidAmountOptions[item].value;
		else
			return NotificationSettings::DefaultAmount;
	}

	bool read_notification_animation_check() {
		return lv_obj_has_state(notifications_section.animation_check, LV_STATE_CHECKED);
	}

	uint8_t read_color_scheme_dropdown() {
		auto item = lv_dropdown_get_selected(color_scheme_section.scheme_dropdown);
		if (item < Scheme::count())
			return static_cast<uint8_t>(item);
		return ColorSchemeSettings::DefaultSchemeId;
	}

	// Live-applies a scheme so the user sees a preview as they change the dropdown.
	// Atomic styles re-paint via lv_obj_report_style_change(NULL) (called inside
	// Scheme::set), and Gui::init_lvgl_styles() refreshes the composite styles.
	static void apply_scheme(uint8_t scheme_id) {
		Scheme::set(scheme_id);
		Gui::reinit_lvgl_styles();
	}

	void update_require_back_enabled(bool expander_enabled) {
		lv_enable(buttonexpknobset_section.require_back_check, expander_enabled);
		auto opa = expander_enabled ? LV_OPA_100 : LV_OPA_50;
		lv_obj_set_style_opa(buttonexpknobset_section.require_back_cont, opa, LV_PART_MAIN);
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

		auto knobset_control = read_knobset_control_check();
		auto knobset_cc = read_knobset_cc_dropdown();
		auto knobset_channel = read_knobset_channel_dropdown();
		if (midi.knobset_control != knobset_control || midi.knobset_cc != knobset_cc ||
			midi.knobset_channel != knobset_channel)
		{
			midi.knobset_control = knobset_control;
			midi.knobset_cc = knobset_cc;
			midi.knobset_channel = knobset_channel;
			gui_state.do_write_settings = true;
		}

		// Patch suggested audio toggles
		auto apply_sr = read_patch_suggest_samplerate_check();
		auto apply_bs = read_patch_suggest_blocksize_check();
		if (settings.patch_suggested_audio.apply_samplerate != apply_sr ||
			settings.patch_suggested_audio.apply_blocksize != apply_bs)
		{

			auto [cur_sr, cur_bs, cur_mr] = patch_playloader.get_audio_settings();

			// If user flipped one or both overrides off, then undo the override by applying the current settings
			bool flipped_sr_off = !apply_sr && settings.patch_suggested_audio.apply_samplerate;
			bool flipped_bs_off = !apply_bs && settings.patch_suggested_audio.apply_blocksize;

			if (flipped_sr_off && flipped_bs_off) {
				// Change both samplerate and blocksize back to default setting
				patch_playloader.request_new_audio_settings(
					audio_settings.sample_rate, audio_settings.block_size, cur_mr);

			} else if (flipped_sr_off) {
				// Change just samplerate back to default setting:
				patch_playloader.request_new_audio_settings(audio_settings.sample_rate, cur_bs, cur_mr);

			} else if (flipped_bs_off) {
				// Change just blocksize back to default:
				patch_playloader.request_new_audio_settings(cur_sr, audio_settings.block_size, cur_mr);
			}

			settings.patch_suggested_audio.apply_samplerate = apply_sr;
			settings.patch_suggested_audio.apply_blocksize = apply_bs;
			gui_state.do_write_settings = true;

			update_audio_override_status();
		}

		// Missing plugin autoload mode
		auto mp_mode = read_missing_plugins_dropdown();
		if (missing_plugins.autoload != mp_mode) {
			missing_plugins.autoload = mp_mode;
			gui_state.do_write_settings = true;
		}

		// Button expander knob set
		auto bexp = read_button_exp_knobset_dropdown();
		auto bexp_back = read_require_back_check();
		if (button_exp_knobset.button_expander != bexp || button_exp_knobset.require_back != bexp_back) {
			button_exp_knobset.button_expander = bexp;
			button_exp_knobset.require_back = bexp_back;
			gui_state.do_write_settings = true;
		}

		// Notifications
		auto notif_amount = read_notification_amount_dropdown();
		auto notif_anim = read_notification_animation_check();
		if (notifications.amount != notif_amount || notifications.animation != notif_anim) {
			notifications.amount = notif_amount;
			notifications.animation = notif_anim;
			gui_state.do_write_settings = true;
		}

		// Color scheme: scheme has already been live-applied in do_changed_cb;
		// here we only persist the id.
		auto scheme_id = read_color_scheme_dropdown();
		if (color_scheme.scheme_id != scheme_id) {
			color_scheme.scheme_id = scheme_id;
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

		} else if (lv_dropdown_is_open(midi_section.knobset_cc_dropdown)) {
			lv_dropdown_close(midi_section.knobset_cc_dropdown);
			lv_group_focus_obj(midi_section.knobset_cc_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(midi_section.knobset_channel_dropdown)) {
			lv_dropdown_close(midi_section.knobset_channel_dropdown);
			lv_group_focus_obj(midi_section.knobset_channel_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(missingplugins_section.dropdown)) {
			lv_dropdown_close(missingplugins_section.dropdown);
			lv_group_focus_obj(missingplugins_section.dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(buttonexpknobset_section.expander_dropdown)) {
			lv_dropdown_close(buttonexpknobset_section.expander_dropdown);
			lv_group_focus_obj(buttonexpknobset_section.expander_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(notifications_section.amount_dropdown)) {
			lv_dropdown_close(notifications_section.amount_dropdown);
			lv_group_focus_obj(notifications_section.amount_dropdown);
			lv_group_set_editing(group, false);
			return true;

		} else if (lv_dropdown_is_open(color_scheme_section.scheme_dropdown)) {
			lv_dropdown_close(color_scheme_section.scheme_dropdown);
			lv_group_focus_obj(color_scheme_section.scheme_dropdown);
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
		auto knobset_control = read_knobset_control_check();
		auto knobset_cc = read_knobset_cc_dropdown();
		auto knobset_channel = read_knobset_channel_dropdown();
		auto apply_sr = read_patch_suggest_samplerate_check();
		auto apply_bs = read_patch_suggest_blocksize_check();
		auto load_initial_patch = lv_obj_has_state(fs_section.startup_patch_check, LV_STATE_CHECKED);
		auto mp_mode = read_missing_plugins_dropdown();
		auto bexp = read_button_exp_knobset_dropdown();
		auto bexp_back = read_require_back_check();
		auto notif_amount = read_notification_amount_dropdown();
		auto notif_anim = read_notification_animation_check();
		auto scheme_id = read_color_scheme_dropdown();

		lv_show(catchup_section.allowjump_cont, catchupmode == CatchupParam::Mode::ResumeOnEqual);
		update_knobset_control_items(knobset_control == MidiSettings::KnobsetControl::Enabled);
		update_require_back_enabled(bexp != 0);

		// Live-preview scheme so the user can see what they're picking.
		// Save persists the id; revert restores the previous scheme via
		// update_dropdowns_from_settings().
		if (scheme_id != Scheme::current())
			apply_scheme(scheme_id);

		if (block_size == audio_settings.block_size && sample_rate == audio_settings.sample_rate &&
			overrun_retries == audio_settings.max_overrun_retries && timeout == screensaver.timeout_ms &&
			knobwake == screensaver.knobs_can_wake && catchupmode == catchup.mode &&
			catchup_exclude_buttons == catchup.allow_jump_outofrange &&
			load_initial_patch == settings.load_initial_patch && fs_max_patches == fs.max_open_patches &&
			midi_feedback == midi.midi_feedback && knobset_control == midi.knobset_control &&
			knobset_cc == midi.knobset_cc && knobset_channel == midi.knobset_channel &&
			mp_mode == missing_plugins.autoload && apply_sr == settings.patch_suggested_audio.apply_samplerate &&
			apply_bs == settings.patch_suggested_audio.apply_blocksize && bexp == button_exp_knobset.button_expander &&
			bexp_back == button_exp_knobset.require_back && notif_amount == notifications.amount &&
			notif_anim == notifications.animation && scheme_id == color_scheme.scheme_id)
		{
			lv_disable(save_button);
			lv_disable(revert_button);
		} else {
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
		if (target == page->notifications_section.amount_dropdown ||
			target == page->notifications_section.animation_check ||
			target == page->color_scheme_section.scheme_dropdown)
		{
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
	ButtonExpKnobSetSettings &button_exp_knobset;
	NotificationSettings &notifications;
	ColorSchemeSettings &color_scheme;
	UserSettings &settings;

	lv_group_t *group = nullptr;

	PrefsSectionAudio audio_section;
	PrefsSectionScreenSaver ssaver_section;
	PrefsSectionCatchupMode catchup_section;
	PrefsSectionFilesystem fs_section;
	PrefsSectionMidi midi_section;
	PrefsSectionMissingPlugins missingplugins_section;
	PrefsSectionButtonExpKnobSet buttonexpknobset_section;
	PrefsSectionNotifications notifications_section;
	PrefsSectionColorScheme color_scheme_section;

	lv_obj_t *save_button;
	lv_obj_t *revert_button;
};

} // namespace MetaModule
