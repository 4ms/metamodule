#pragma once
#include "audio_stream.hh"
#include "lv_port_indev.h"
#define printf_ printf
///

#include "gui/pages/page_manager.hh"
#include "params/params_state.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_file/patchlist.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

class Ui {

	RotaryEncoderKeys keys{
		.turn_cw = SDLK_RIGHT,
		.turn_ccw = SDLK_LEFT,
		.click = SDLK_DOWN,
		.aux_button = SDLK_UP,
		.quit = SDLK_ESCAPE,
		.param_inc = ']',
		.param_dec = '[',
	};

public:
	Ui(std::string_view patch_path, size_t block_size);

	bool update();
	void play_patch(std::span<Frame> buffer);

private:
	PatchPlayer patch_player;
	PatchStorageProxy patch_storage;
	PatchPlayLoader patch_playloader{patch_storage, patch_player};
	PatchModQueue patch_mod_queue;

	MessageQueue msg_queue;
	PageManager page_manager;
	ParamsState params;
	MetaParams metaparams;
	AudioStream audio_stream{params, patch_player, patch_playloader};
	LvglEncoderSimulatorDriver input_driver{keys};

	std::vector<StreamConfSim::Audio::AudioInFrame> in_buffer;
	std::vector<StreamConfSim::Audio::AudioOutFrame> out_buffer;

	uint32_t last_lvgl_task_tm = 0;
	uint32_t last_page_task_tm = 0;

	void lvgl_update_task();
	void page_update_task();
	void transfer_aux_button_events();
	void transfer_params();
};

} // namespace MetaModule
