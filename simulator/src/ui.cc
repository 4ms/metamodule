#include "ui.hh"
#include "gui/notify/queue.hh"

namespace MetaModule
{

Ui::Ui(std::string_view patch_path, std::string_view asset_path, size_t block_size)
	: ramdrive{new RamDrive}
	, ramdisk_ops{*ramdrive}
	, ramdisk{&ramdisk_ops, Volume::RamDisk}
	, patch_storage(patch_path, patch_dir_list, ramdisk)
	, patch_comm{patch_storage}
	, file_storage_proxy{raw_patch_data, patch_comm, patch_dir_list}
	, asset_fs{asset_path}
	, internal_plugin_manager{ramdisk, asset_fs}
	, plugin_manager{file_storage_proxy, ramdisk}
	, page_manager{file_storage_proxy,
				   patch_playloader,
				   params,
				   metaparams,
				   notify_queue,
				   patch_mod_queue,
				   plugin_manager}
	, in_buffer(block_size)
	, out_buffer(block_size) {

	params.clear();
	metaparams.clear();

	Gui::init_lvgl_styles();
	page_manager.init();

	patch_playloader.notify_audio_is_muted();
	std::cout << "UI: buffers have # frames: in: " << in_buffer.size() << ", out: " << out_buffer.size() << "\n";

	params.jack_senses = 0x0;
	params.set_input_plugged(cur_inchan_left, true);
	params.set_input_plugged(cur_inchan_right, true);

	params.set_output_plugged(cur_outchan_left, true);
	params.set_output_plugged(cur_outchan_right, true);
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
		params.knobs[cur_param].changed = false;

		if (input_driver.param_inc()) {
			params.knobs[cur_param].val = std::clamp(params.knobs[cur_param] + 0.05f, 0.f, 1.f);
			params.knobs[cur_param].changed = true;

			std::cout << "Knob #" << cur_param << " = " << params.knobs[cur_param].val << "\n";
		}

		if (input_driver.param_dec()) {
			params.knobs[cur_param].val = std::clamp(params.knobs[cur_param] - 0.05f, 0.f, 1.f);
			params.knobs[cur_param].changed = true;

			std::cout << "Knob #" << cur_param << " = " << params.knobs[cur_param].val << "\n";
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

} // namespace MetaModule
