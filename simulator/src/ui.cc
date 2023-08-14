#include "ui.hh"

namespace MetaModule
{

Ui::Ui(std::string_view patch_path, size_t block_size)
	: patch_storage(patch_path)
	, msg_queue{1024}
	, page_manager{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue}
	, in_buffer(block_size)
	, out_buffer(block_size) {
	params.clear();
	metaparams.clear();

	Gui::init_lvgl_styles();
	page_manager.init();

	patch_playloader.audio_is_muted();
	std::cout << "UI: buffers have # frames: in: " << in_buffer.size() << ", out: " << out_buffer.size() << "\n";

	params.jack_senses = 0xFFFFFFFF;
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

	// 	frame.chan[0] = in.l;
	// 	frame.chan[1] = in.r;
	// }

	audio_stream.process(in_buffer, out_buffer);

	for (size_t i = 0; auto &frame : out_buffer) {
		auto &out = soundcard_out[i++];

		//TODO: allow routing to be dynamically configured
		// For now out 1 -> SDL 1, and 2->2
		out.l = frame.chan[0];
		out.r = frame.chan[1];
	}
}

void Ui::lvgl_update_task() {
	lv_timer_handler();

	auto msg = msg_queue.get_message();
	if (!msg.empty()) {
		printf_("%s", msg.data());
		msg_queue.clear_message();
	}
}

void Ui::page_update_task() { //60Hz
	page_manager.update_current_page();
	patch_playloader.handle_sync_patch_loading();
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

			printf("Knob #%d = %1.2f\n", cur_param, (double)params.knobs[cur_param].val);
		}

		if (input_driver.param_dec()) {
			params.knobs[cur_param].val = std::clamp(params.knobs[cur_param] - 0.05f, 0.f, 1.f);
			params.knobs[cur_param].changed = true;

			printf("Knob #%d = %1.2f\n", cur_param, (double)params.knobs[cur_param].val);
		}
	}
}

} // namespace MetaModule
