#pragma once
#include "audio_stream.hh"
#include "frame.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_manager.hh"
#include "lv_port_indev.h"
#include "patch_file/file_storage_proxy.hh"

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
		.prev_knobset = ',',
		.next_knobset = '.',
	};

public:
	Ui(std::string_view patch_path, size_t block_size);

	bool update();
	void play_patch(std::span<Frame> buffer);

private:
	PatchDirList patch_dir_list;
	PatchPlayer patch_player;
	SimulatorPatchStorage patch_storage;
	FileStorageComm patch_comm;
	FileStorageProxy file_storage_proxy;
	PatchPlayLoader patch_playloader{file_storage_proxy, patch_player};
	PatchModQueue patch_mod_queue;

	NotificationQueue notify_queue;
	PageManager page_manager;
	ParamsMidiState params;
	MetaParams metaparams;
	AudioStream audio_stream{params, patch_player, patch_playloader, patch_mod_queue};
	LvglEncoderSimulatorDriver input_driver{keys};

	std::vector<StreamConfSim::Audio::AudioInFrame> in_buffer;
	std::vector<StreamConfSim::Audio::AudioOutFrame> out_buffer;

	std::array<char, 65536> raw_patch_data;

	uint32_t last_lvgl_task_tm = 0;
	uint32_t last_page_task_tm = 0;

	unsigned cur_outchan_left = 0;
	unsigned cur_outchan_right = 1;
	unsigned cur_inchan_left = 0;
	unsigned cur_inchan_right = 1;

	void lvgl_update_task();
	void page_update_task();
	void transfer_aux_button_events();
	void transfer_params();
	void change_knobset();
	void update_channel_selections();
};

} // namespace MetaModule
