#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "sdl_audio.hh"
#include "ui.hh"
#include <iostream>

int main(int argc, char *argv[]) {
	// Set zoom to startup with a larger window (zoomed in)
	int zoom = 2;

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
	SDLAudio audio{0};

	MetaModule::PatchPlayer patch_player;
	MetaModule::PatchStorageProxy patch_storage{patch_path};
	MetaModule::PatchPlayLoader patch_playloader{patch_storage, patch_player};
	MetaModule::PatchModQueue patch_mod_queue;
	MetaModule::Ui ui{patch_playloader, patch_storage, patch_mod_queue};

	ui.start();

	while (ui.update()) {
	}

	lv_port_disp_deinit();
	lv_deinit();

	return 0;
}
