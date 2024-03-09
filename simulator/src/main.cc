#include "frame.hh"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include "sdl_audio.hh"
#include "settings.hh"
#include "ui.hh"

int main(int argc, char *argv[]) {
	MetaModuleSim::Settings settings;

	settings.parse(argc, argv);

	lv_init();
	lv_port_disp_init(320, 240, settings.zoom);

	SDLAudio<Frame> audio_out{settings.audioout_dev};

	auto patch_path = std::filesystem::absolute(settings.patch_path);
	auto asset_path = std::filesystem::absolute("../../firmware/build/intdrive.img");

	MetaModule::Ui ui{patch_path.string(), asset_path.string(), audio_out.get_block_size()};

	audio_out.set_callback([&ui](auto playback_buffer) { ui.play_patch(playback_buffer); });
	audio_out.unpause();

	// Run until get Quit event
	while (ui.update()) {
	}

	lv_port_disp_deinit();
	lv_deinit();

	return 0;
}
