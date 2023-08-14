#include "audio_stream.hh"
#include "frame.hh"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "sdl_audio.hh"
#include "ui.hh"
#include <iostream>

int main(int argc, char *argv[]) {
	// Set zoom to startup with a larger window (zoomed in) TODO: make cli option
	int zoom = 2;

	// Index of audio device for SDL to use TODO: make cli option
	unsigned audio_device_index = 0;

	// First argument is path to dir with patch files
	std::string_view patch_path{""};

	if (argc > 1) {
		patch_path = argv[1];
	}

	if (patch_path.length() == 0) {
		std::cout << "No path to patch dir specified, using '../shared/patch/'"
				  << "\n";
		patch_path = "../shared/patch/";
	}

	lv_init();
	lv_port_disp_init(320, 240, zoom);

	SDLAudio<Frame> audio{audio_device_index};

	MetaModule::Ui ui{patch_path, audio.get_block_size()};

	audio.set_callback([&ui](auto playback_buffer) { ui.play_patch(playback_buffer); });
	audio.unpause();

	// Run until get QUIT event
	while (ui.run()) {
	}

	lv_port_disp_deinit();
	lv_deinit();

	return 0;
}
