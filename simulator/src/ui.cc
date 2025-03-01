#include "ui.hh"
#include "dynload/autoload_plugins.hh"
#include "gui/notify/queue.hh"
#include "stubs/fs/fs_proxy.hh"

namespace MetaModule
{

Ui::Ui(std::string_view sdcard_path, std::string_view flash_path, std::string_view asset_path, size_t block_size)
	: ramdrive{new RamDrive}
	, ramdisk_ops{*ramdrive}
	, ramdisk{&ramdisk_ops, Volume::RamDisk}
	, patch_storage(sdcard_path, flash_path, patch_dir_list, ramdisk)
	, patch_comm{patch_storage}
	, file_storage_proxy{raw_patch_data, patch_comm, patch_dir_list}
	, asset_fs{asset_path}
	, internal_plugin_manager{ramdisk, asset_fs}
	, plugin_manager{file_storage_proxy, ramdisk}
	, page_manager{file_storage_proxy,
				   open_patches_manager,
				   patch_playloader,
				   params,
				   metaparams,
				   notify_queue,
				   patch_mod_queue,
				   plugin_manager,
				   settings,
				   screensaver,
				   ramdisk}
	, in_buffer(block_size)
	, out_buffer(block_size) {

	register_volume_host_path(Volume::SDCard, sdcard_path);
	register_volume_host_path(Volume::NorFlash, flash_path);

	params.clear();
	metaparams.clear();

	Gui::init_lvgl_styles();
	page_manager.init();

	tvg::Initializer::init(0, tvg::CanvasEngine::Sw);

	if (!Settings::read_settings(file_storage_proxy, &settings)) {
		settings = UserSettings{};
		pr_warn("Could not read settings.yml, using defaults\n");
		if (!Settings::write_settings(file_storage_proxy, settings)) {
			pr_err("Failed to write settings file\n");
		}
	}

	autoload_plugins();

	patch_playloader.notify_audio_is_muted();
	std::cout << "UI: buffers have # frames: in: " << in_buffer.size() << ", out: " << out_buffer.size() << "\n";

	params.jack_senses = 0x0;
	params.set_input_plugged(cur_inchan_left, true);
	params.set_input_plugged(cur_inchan_right, true);

	params.set_output_plugged(cur_outchan_left, true);
	params.set_output_plugged(cur_outchan_right, true);

	patch_playloader.set_all_param_catchup_mode(settings.catchup.mode, settings.catchup.button_exclude);
}

// "Scheduler" for UI tasks
// returns true until it gets a QUIT event
bool Ui::update() {

	auto tm = lv_tick_get(); //milliseconds
	if (tm - last_lvgl_task_tm >= 1) {
		lvgl_update_task();
		last_lvgl_task_tm = tm;
	}

	tm = lv_tick_get();
	if (tm - last_page_task_tm >= 16) {
		transfer_aux_button_events();
		transfer_params();
		change_knobset();
		update_channel_selections();
		page_update_task();
		last_page_task_tm = tm;
	}

	bool keep_running = input_driver.get_quit() == LV_QUIT_NONE;
	return keep_running;
}

void Ui::play_patch(std::span<Frame> soundcard_out) {
	// assert(soundcard_out.size() == out_buffer.size());

	//TODO: enable soundcard audio input
	// for (size_t i = 0; auto &frame : out_buffer) {
	// 	auto &in = soundcard_in[i++];

	// 	frame.chan[cur_inchan_left] = in.l;
	// 	frame.chan[cur_inchan_right] = in.r;
	// }

	audio_stream.process(in_buffer, out_buffer);

	for (auto &w : params.lights.watch_lights) {
		if (w.is_active())
			w.value = patch_player.get_module_light(w.module_id, w.light_id);
	}

	for (auto &d : params.text_displays.watch_displays) {
		if (d.is_active()) {
			auto text = std::span<char>(d.text._data, d.text.capacity);
			auto sz = patch_player.get_display_text(d.module_id, d.light_id, text);
			d.text._data[sz] = 0;
		}
	}

	for (auto &p : params.param_watcher.active_watched_params()) {
		if (p.is_active()) {
			p.value = patch_player.get_param(p.module_id, p.param_id);
		}
	}

	for (size_t i = 0; auto &frame : out_buffer) {
		auto &out = soundcard_out[i++];

		out.l = frame.chan[cur_outchan_left];
		out.r = frame.chan[cur_outchan_right];
	}
}

void Ui::lvgl_update_task() {
	lv_timer_handler();
}

void Ui::page_update_task() { //60Hz
	page_manager.update_current_page();
	auto load_status = patch_playloader.handle_file_events();
	if (!load_status.success) {
		notify_queue.put({load_status.error_string, Notification::Priority::Error, 5000});
	} else if (load_status.error_string.size()) {
		notify_queue.put({load_status.error_string, Notification::Priority::Info, 3000});
	}
}

void Ui::transfer_aux_button_events() {
	// Transfer aux button events SDL => LVGL => metaparams
	if (input_driver.aux_button_just_pressed())
		metaparams.meta_buttons[0].register_falling_edge();

	if (input_driver.aux_button_just_released())
		metaparams.meta_buttons[0].register_rising_edge();
}

void Ui::transfer_params() {
	if (unsigned cur_param = input_driver.selected_param(); cur_param < params.knobs.size()) {

		auto delta = input_driver.param_fine() ? 0.001f : 0.05f;

		if (input_driver.param_inc()) {
			float val = std::clamp(params.knobs[cur_param].val + delta, 0.f, 1.f);
			if (params.knobs[cur_param].store_changed(val))
				std::cout << "Knob #" << cur_param << " = " << params.knobs[cur_param].val << "\n";
			else
				std::cout << "Failed to change knob";
		}

		if (input_driver.param_dec()) {
			float val = std::clamp(params.knobs[cur_param].val - delta, 0.f, 1.f);
			if (params.knobs[cur_param].store_changed(val))
				std::cout << "Knob #" << cur_param << " = " << params.knobs[cur_param].val << "\n";
			else
				std::cout << "Failed to change knob";
		}
	}
}

void Ui::change_knobset() {
	if (auto change = input_driver.knobset_changed(); change != 0) {
		metaparams.rotary_with_metabutton.motion += change;
	}
}

void Ui::update_channel_selections() {
	if (cur_outchan_left != input_driver.selected_outchan()) {
		params.set_output_plugged(cur_outchan_left, false);
		params.set_output_plugged(cur_outchan_right, false);

		cur_outchan_left = input_driver.selected_outchan();
		cur_outchan_right = (cur_outchan_left + 1) % 8;

		params.set_output_plugged(cur_outchan_left, true);
		params.set_output_plugged(cur_outchan_right, true);

		std::cout << "Out Jack #" << cur_outchan_left + 1 << " --> Soundcard left output\n";
		std::cout << "Out Jack #" << cur_outchan_right + 1 << " --> Soundcard right output\n";
	}

	if (cur_inchan_left != input_driver.selected_inchan()) {
		params.set_input_plugged(cur_inchan_left, false);
		params.set_input_plugged(cur_inchan_right, false);

		cur_inchan_left = input_driver.selected_inchan();
		cur_inchan_right = (cur_inchan_left + 1) % 8;

		params.set_input_plugged(cur_inchan_left, true);
		params.set_input_plugged(cur_inchan_right, true);

		std::cout << "Soundcard left input --> Input Jack # " << cur_inchan_left + 1 << "\n";
		std::cout << "Soundcard right input --> Input Jack # " << cur_inchan_right + 1 << "\n";
	}
}

void Ui::autoload_plugins() {
	auto autoloader = AutoLoader{plugin_manager, settings.plugin_autoload};

	while (true) {
		auto status = autoloader.process();

		if (status.state == AutoLoader::State::Error) {
			notify_queue.put({status.message, Notification::Priority::Error, 2000});
			break;
		}

		if (status.state == AutoLoader::State::Done) {
			break;
		}

		if (status.message.length()) {
			lv_label_set_text(ui_MainMenuNowPlaying, status.message.c_str());
		}

		auto now = get_time();
		if ((now - last_lvgl_task_tm) > 2) {
			last_lvgl_task_tm = now;
			lv_timer_handler();
		}
	}

	lv_label_set_text(ui_MainMenuNowPlaying, "");
	page_manager.init();
}

} // namespace MetaModule
