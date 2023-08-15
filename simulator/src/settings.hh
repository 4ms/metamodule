#pragma once

#include "lib/cxxopts/cxxopts.hpp"

namespace MetaModuleSim
{

struct Settings {
	unsigned zoom = 100;
	std::string patch_path = "../shared/patch/";
	unsigned audioout_dev = 0;

	void parse(int argc, char *argv[]) {

		try {
			cxxopts::Options options("simulator", "Display and Audio simulator for MetaModule hardware");
			options.show_positional_help();

			options.add_options()(
				"z,zoom", "Initial display zoom percentage", cxxopts::value<unsigned>()->default_value("100"));

			options.add_options()("a,audioout",
								  "Audio output device ID (as seen by SDL)",
								  cxxopts::value<unsigned>()->default_value("0"));

			options.add_options()("p,patchdir",
								  "Directory with patch files",
								  cxxopts::value<std::string>()->default_value("../shared/patch/"));

			options.add_options()("h,help", "Print help");

			auto args = options.parse(argc, argv);

			if (args.count("zoom") > 0)
				zoom = std::clamp(args["zoom"].as<unsigned>(), 25U, 800U);

			if (args.count("patchdir") > 0)
				patch_path = args["patchdir"].as<std::string>();

			if (args.count("audioout") > 0)
				audioout_dev = args["audioout"].as<unsigned>();

			if (args.count("help") || args.count("?") || args.count("h")) {
				std::cout << options.help() << std::endl;
				exit(0);
			}

		} catch (const cxxopts::OptionException &e) {
			std::cout << "Error parsing options: " << e.what() << std::endl;
			exit(1);
		}
	}

	//TODO: option to load wav file, which is played into selected channel by pressing space
	//TODO: parse config file
};

} // namespace MetaModuleSim
