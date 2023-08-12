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
	PatchPlayLoader &patch_playloader;
	MessageQueue msg_queue;
	PageManager page_manager;
	ParamsState params;
	MetaParams metaparams;
	AudioStream audio_stream;
	LvglEncoderSimulatorDriver input_driver{keys};

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
	Ui(PatchPlayLoader &patch_playloader,
	   PatchStorageProxy &patch_storage,
	   PatchModQueue &patch_mod_queue,
	   PatchPlayer &player);

	bool run();
	void play_patch(std::span<Frame> buffer);

private:
	uint32_t last_lvgl_task_tm = 0;
	uint32_t last_page_task_tm = 0;

	void lvgl_update_task();
	void page_update_task();
	void transfer_aux_button_events();
	void transfer_params();
};

} // namespace MetaModule
