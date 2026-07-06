#pragma once

#include "lib/cxxopts/cxxopts.hpp"
#include <iostream>
#include <optional>

namespace MetaModuleSim
{

struct Settings {
	unsigned zoom = 100;
	std::string sdcard_path = "patches/";
	std::string flash_path = "../patches/default/";
	std::string asset_file = "build/assets.uimg";
	int audioout_dev = 0;
	std::string test_brand = "";
	float fullscale_volts = 5;

	// MIDI (rtmidi). If a port index is unset, a virtual port is created instead.
	std::optional<int> midiin_dev{};  // hardware MIDI input port index
	std::optional<int> midiout_dev{}; // hardware MIDI output port index
	bool list_midi = false;			  // print available MIDI ports and exit

	// Headless screenshot support: load a patch, jump to a page, render some
	// frames, then dump the screen to a BMP file and exit.
	std::string startup_patch = ""; // patch filename on the SD card, e.g. "/test-cable-disp.yml"
	std::string start_page = "";	// page to jump to on startup, e.g. "jackmap"
	std::string screenshot_path = ""; // if set, capture to this BMP path then exit
	unsigned screenshot_frames = 120; // UI update cycles to run before capturing
	std::string input_sequence = ""; // ordered encoder actions to simulate, e.g. "cw cw click"

	void parse(int argc, char *argv[]) {

		try {
			cxxopts::Options options("simulator", "Display and Audio simulator for MetaModule hardware");
			options.show_positional_help();

			options.add_options()(
				"z,zoom", "Initial display zoom percentage", cxxopts::value<unsigned>()->default_value("100"));

			options.add_options()(
				"a,audioout", "Audio output device ID (as seen by SDL)", cxxopts::value<int>()->default_value("0"));

			options.add_options()(
				"midiin", "MIDI input port index (default: create a virtual port)", cxxopts::value<int>());

			options.add_options()(
				"midiout", "MIDI output port index (default: create a virtual port)", cxxopts::value<int>());

			options.add_options()("listmidi", "List available MIDI input/output ports and exit");

			options.add_options()("p,sdcarddir",
								  "Host directory simulating SD Card root",
								  cxxopts::value<std::string>()->default_value("patches/"));

			options.add_options()("f,flashdir",
								  "Host directory simulating internal NOR Flash root",
								  cxxopts::value<std::string>()->default_value("../patches/default/"));

			options.add_options()("s,assets",
								  "Location of assets.uimg file (built by firmware project)",
								  cxxopts::value<std::string>()->default_value("../firmware/build/assets.uimg"));

			options.add_options()(
				"t,test_brand", "Brand slug to run tests on", cxxopts::value<std::string>()->default_value(""));

			options.add_options()("l,fullScaleVolts",
								  "Volts (peak) which corresponds to full-scale signal sent to sound card",
								  cxxopts::value<float>()->default_value("5"));

			options.add_options()("patch",
								  "Patch file on the SD card to load on startup (e.g. /test-cable-disp.yml)",
								  cxxopts::value<std::string>()->default_value(""));

			options.add_options()(
				"page", "Page to jump to on startup (e.g. jackmap, midimap)", cxxopts::value<std::string>()->default_value(""));

			options.add_options()("screenshot",
								  "Capture the screen to this BMP file after rendering, then exit",
								  cxxopts::value<std::string>()->default_value(""));

			options.add_options()("screenshot-frames",
								  "UI update cycles to run before capturing a screenshot",
								  cxxopts::value<unsigned>()->default_value("120"));

			options.add_options()("input",
								  "Ordered encoder actions to simulate on startup, e.g. \"cw cw click\" "
								  "(tokens: cw, ccw, click, back; repeat with cw:3)",
								  cxxopts::value<std::string>()->default_value(""));

			options.add_options()("h,help", "Print help");

			auto args = options.parse(argc, argv);

			if (args.count("patch") > 0)
				startup_patch = args["patch"].as<std::string>();

			if (args.count("page") > 0)
				start_page = args["page"].as<std::string>();

			if (args.count("screenshot") > 0)
				screenshot_path = args["screenshot"].as<std::string>();

			if (args.count("screenshot-frames") > 0)
				screenshot_frames = args["screenshot-frames"].as<unsigned>();

			if (args.count("input") > 0)
				input_sequence = args["input"].as<std::string>();

			if (args.count("zoom") > 0)
				zoom = std::clamp(args["zoom"].as<unsigned>(), 25U, 800U);

			if (args.count("sdcarddir") > 0)
				sdcard_path = args["sdcarddir"].as<std::string>();

			if (args.count("flashdir") > 0)
				flash_path = args["flashdir"].as<std::string>();

			if (args.count("assets") > 0)
				asset_file = args["assets"].as<std::string>();

			if (args.count("test_brand") > 0)
				test_brand = args["test_brand"].as<std::string>();

			if (args.count("audioout") > 0)
				audioout_dev = args["audioout"].as<int>();

			if (args.count("midiin") > 0)
				midiin_dev = args["midiin"].as<int>();

			if (args.count("midiout") > 0)
				midiout_dev = args["midiout"].as<int>();

			if (args.count("listmidi") > 0)
				list_midi = true;

			if (args.count("fullScaleVolts") > 0)
				fullscale_volts = args["fullScaleVolts"].as<float>();

			if (args.count("help") || args.count("?") || args.count("h")) {
				std::cout << options.help() << std::endl;
				exit(0);
			}

		} catch (const cxxopts::exceptions::exception &e) {
			std::cout << "Error parsing options: " << e.what() << std::endl;
			exit(1);
		}
	}

	//TODO: option to load wav file, which is played into selected channel by pressing space
	//TODO: parse config file
};

} // namespace MetaModuleSim
