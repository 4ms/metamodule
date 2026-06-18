#include "../firmware/src/load_test/test_modules.hh"
#include "frame.hh"
#include "lv_port_disp.h"
#include "lvgl.h"
#include "sdl_audio.hh"
#include "settings.hh"
#include "ui.hh"
#include <chrono>
#include <iostream>
#include <optional>
#include <string_view>
#include <thread>

static std::optional<MetaModule::PageId> resolve_page(std::string_view name) {
	using MetaModule::PageId;
	if (name.empty())
		return std::nullopt;
	if (name == "mainmenu")
		return PageId::MainMenu;
	if (name == "patchsel")
		return PageId::PatchSel;
	if (name == "patchview")
		return PageId::PatchView;
	if (name == "moduleview")
		return PageId::ModuleView;
	if (name == "modulelist")
		return PageId::ModuleList;
	if (name == "jackmap")
		return PageId::JackMapView;
	if (name == "midimap")
		return PageId::MidiMapView;
	std::cout << "Unknown --page '" << name << "'\n";
	return std::nullopt;
}

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

	// Optional headless startup state for screenshots/testing
	if (!settings.startup_patch.empty())
		ui.load_patch(settings.startup_patch, MetaModule::Volume::SDCard);

	if (auto page = resolve_page(settings.start_page))
		ui.goto_page(*page);

	// Headless screenshot mode: render a few frames so the page settles, then
	// dump the screen to a BMP file and exit without starting audio.
	if (!settings.screenshot_path.empty()) {
		for (unsigned i = 0; i < settings.screenshot_frames; i++) {
			ui.update();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		int rc = lv_port_disp_capture(settings.screenshot_path.c_str());
		if (rc == 0)
			std::cout << "Saved screenshot to " << settings.screenshot_path << "\n";
		else
			std::cout << "Screenshot capture failed (rc=" << rc << ")\n";

		MetaModule::kill_module_threads();
		lv_port_disp_deinit();
		lv_deinit();
		return rc;
	}

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
