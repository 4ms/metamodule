#include "../firmware/src/load_test/test_modules.hh"
#include "frame.hh"
#include "lv_port_disp.h"
#include "lvgl.h"
#include "sdl_audio.hh"
#include "settings.hh"
#include "ui.hh"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>

static void run_cycles(MetaModule::Ui &ui, unsigned n) {
	for (unsigned i = 0; i < n; i++) {
		ui.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

static void push_key(SDL_Keycode keycode, bool down) {
	SDL_Event e{};
	e.type = down ? SDL_KEYDOWN : SDL_KEYUP;
	e.key.state = down ? SDL_PRESSED : SDL_RELEASED;
	e.key.repeat = 0;
	e.key.keysym.sym = keycode;
	SDL_PushEvent(&e);
}

// Simulate a sequence of encoder actions (e.g. "cw cw click") by synthesizing
// the same SDL key events the input driver reads, running UI cycles in between
// so LVGL processes each one.
static void simulate_input(MetaModule::Ui &ui, const std::string &seq) {
	auto const &keys = ui.input_keys();

	run_cycles(ui, 12); // let the starting page settle before sending input

	std::istringstream iss(seq);
	std::string tok;
	while (iss >> tok) {
		unsigned count = 1;
		std::string name = tok;
		if (auto colon = tok.find(':'); colon != std::string::npos) {
			name = tok.substr(0, colon);
			count = (unsigned)std::stoul(tok.substr(colon + 1));
		}

		for (unsigned c = 0; c < count; c++) {
			if (name == "cw") {
				push_key(keys.turn_cw, true);
				run_cycles(ui, 4);
				push_key(keys.turn_cw, false);
				run_cycles(ui, 2);
			} else if (name == "ccw") {
				push_key(keys.turn_ccw, true);
				run_cycles(ui, 4);
				push_key(keys.turn_ccw, false);
				run_cycles(ui, 2);
			} else if (name == "click") {
				push_key(keys.click, true);
				run_cycles(ui, 4);
				push_key(keys.click, false);
				run_cycles(ui, 6);
			} else if (name == "back") {
				push_key(keys.aux_button, true);
				run_cycles(ui, 4);
				push_key(keys.aux_button, false);
				run_cycles(ui, 4);
			} else {
				std::cout << "Unknown --input token '" << name << "'\n";
			}
		}
	}
}

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
	lv_port_disp_init(settings.screenw, settings.screenh, settings.zoom);

	SDLAudio<Frame> audio_out{settings.audioout_dev};

	// The default resource paths (patches/, build/assets.uimg, ../patches/default/)
	// are relative to the simulator/ directory. So the binary can be launched from
	// any working directory, fall back to resolving them relative to the executable
	// (which lives in simulator/build/) when they aren't found relative to the cwd.
	namespace fs = std::filesystem;
	fs::path sim_dir;
	if (argc > 0 && std::string_view(argv[0]).find('/') != std::string_view::npos) {
		std::error_code ec;
		auto exe = fs::weakly_canonical(fs::absolute(argv[0], ec), ec);
		if (!ec)
			sim_dir = exe.parent_path().parent_path(); // simulator/build/simulator -> simulator/
	}

	auto resolve_resource = [&](const std::string &p) -> fs::path {
		std::error_code ec;
		auto cwd_rel = fs::absolute(p, ec);
		if (!ec && fs::exists(cwd_rel, ec))
			return cwd_rel;
		if (!sim_dir.empty()) {
			auto sim_rel = sim_dir / p;
			if (fs::exists(sim_rel, ec))
				return sim_rel;
		}
		return cwd_rel; // not found anywhere; reported by the file layer (no longer aborts)
	};

	auto sdcard_path = resolve_resource(settings.sdcard_path);
	auto flash_path = resolve_resource(settings.flash_path);
	auto asset_tar_path = resolve_resource(settings.asset_file);

	if (std::error_code ec; !fs::exists(sdcard_path, ec))
		std::cout << "Warning: SD-card patch dir not found: " << sdcard_path
				  << " (pass -p <dir> or run from the simulator/ directory)\n";

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

	// Simulate encoder input (e.g. navigate to and click a list item) before capture
	if (!settings.input_sequence.empty())
		simulate_input(ui, settings.input_sequence);

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
