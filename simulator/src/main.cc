#include "audio_stream.hh"
#include "frame.hh"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "sdl_audio.hh"
#include "settings.hh"
#include "ui.hh"
#include <iostream>

int main(int argc, char *argv[]) {
	MetaModuleSim::Settings settings;

	settings.parse(argc, argv);

	lv_init();
	lv_port_disp_init(320, 240, settings.zoom);
	ui_init();

	SDLAudio<Frame> audio_out{settings.audioout_dev};

	MetaModule::Ui ui{settings.patch_path, audio_out.get_block_size()};

	audio_out.set_callback([&ui](auto playback_buffer) { ui.play_patch(playback_buffer); });
	audio_out.unpause();

	// Run until get Quit event
	while (ui.update()) {
	}

	lv_port_disp_deinit();
	lv_deinit();

	return 0;
}
