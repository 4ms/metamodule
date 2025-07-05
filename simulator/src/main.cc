#include "../firmware/src/load_test/test_modules.hh"
#include "frame.hh"
#include "lv_port_disp.h"
#include "lvgl.h"
#include "sdl_audio.hh"
#include "settings.hh"
#include "ui.hh"
#include <string_view>

int main(int argc, char *argv[]) {
	MetaModuleSim::Settings settings;

	settings.parse(argc, argv);

	lv_init();
	lv_port_disp_init(320, 240, settings.zoom);

	SDLAudio<Frame> audio_out{settings.audioout_dev};

	auto sdcard_path = std::filesystem::absolute(settings.sdcard_path);

	auto flash_path = std::filesystem::absolute(settings.flash_path);

	auto asset_tar_path = std::filesystem::absolute(settings.asset_file);

	MetaModule::Ui ui{sdcard_path.string(), flash_path.string(), asset_tar_path.string(), audio_out.get_block_size()};

	MetaModule::start_module_threads();

	if (settings.test_brand != "") {
		pr_info("Running CPU load tests for `%s`\n", settings.test_brand.c_str());

		MetaModule::LoadTest::test_module_brand(settings.test_brand, [](std::string_view csv_line) {});
	}

	ui.set_audio_fullscale(settings.fullscale_volts);
	audio_out.set_callback([&ui](auto playback_buffer) { ui.play_patch(playback_buffer); });
	audio_out.unpause();

	// Run until get Quit event
	while (ui.update()) {
	}

	audio_out.pause();

	MetaModule::kill_module_threads();

	lv_port_disp_deinit();
	lv_deinit();

	return 0;
}
