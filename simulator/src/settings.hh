#pragma once

#include "lib/cxxopts/cxxopts.hpp"
#include <iostream>

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

	void parse(int argc, char *argv[]) {

		try {
			cxxopts::Options options("simulator", "Display and Audio simulator for MetaModule hardware");
			options.show_positional_help();

			options.add_options()(
				"z,zoom", "Initial display zoom percentage", cxxopts::value<unsigned>()->default_value("100"));

			options.add_options()(
				"a,audioout", "Audio output device ID (as seen by SDL)", cxxopts::value<int>()->default_value("0"));

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

			options.add_options()("h,help", "Print help");

			auto args = options.parse(argc, argv);

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
