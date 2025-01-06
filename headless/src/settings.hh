#pragma once

#include "lib/cxxopts/cxxopts.hpp"
#include <iostream>

namespace MetaModuleSim
{

struct Settings {
	size_t samples_to_run = 48000 * 100;
	std::string patch = "../patches/default/Djembe4verb.yml";
	std::string audio_in_file = "audio_in.raw";
	std::string audio_out_file = "audio_out.raw";

	void parse(int argc, char *argv[]) {

		try {
			cxxopts::Options options("headless", "MetaModule headless mode");
			options.show_positional_help();

			options.add_options()(
				"n,num_samples", "Number of samples to process", cxxopts::value<unsigned>()->default_value("480000"));

			options.add_options()("p,patch",
								  "Patch file to play",
								  cxxopts::value<std::string>()->default_value("../patches/default/Djembe4verb.yml"));

			options.add_options()("i,in",
								  "Input signal raw data (floats, interleaved 2 channels)",
								  cxxopts::value<std::string>()->default_value("audio_in.raw"));

			options.add_options()("o,out",
								  "Output signal raw data (floats, interleaved 2 channels)",
								  cxxopts::value<std::string>()->default_value("audio_out.raw"));

			options.add_options()("h,help", "Print help");

			auto args = options.parse(argc, argv);

			if (args.count("patch") > 0)
				patch = args["patch"].as<std::string>();

			if (args.count("num_samples") > 0)
				samples_to_run = args["num_samples"].as<unsigned>();

			if (args.count("out") > 0)
				audio_out_file = args["audio_out_file"].as<std::string>();

			if (args.count("int") > 0)
				audio_in_file = args["audio_in_file"].as<std::string>();

			if (args.count("help") || args.count("?") || args.count("h")) {
				std::cout << options.help() << std::endl;
				exit(0);
			}

		} catch (const cxxopts::exceptions::exception &e) {
			std::cout << "Error parsing options: " << e.what() << std::endl;
			exit(1);
		}
	}
};

} // namespace MetaModuleSim
