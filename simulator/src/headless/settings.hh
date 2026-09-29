#pragma once

#include "lib/cxxopts/cxxopts.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace MetaModuleSim
{

struct Settings {
	size_t samples_to_run = 48000 * 100;
	std::string patch = "../patches/default/Djembe4verb.yml";
	std::string audio_in_file = "audio_in.wav";
	std::string audio_out_file = "audio_out.wav";
	bool list_modules = false;

	// Instead of playing a patch, check a plugin's element groups/order/names
	bool check_element_layout = false;
	std::string plugin_json;
	std::string plugin_mm_json;
	std::vector<std::string> modules; // empty means all modules

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

			options.add_options()("list-modules",
								  "Print every registered module as `module<TAB>brand<TAB>slug` and exit (used by check_plugin_jsons.py)");

			options.add_options()("check-element-layout",
								  "Check a plugin's element groups, order, and names in plugin-mm.json, then exit. "
								  "The plugin must be built in as an ext-plugin");
			options.add_options()(
				"plugin-json", "plugin.json of the plugin to check", cxxopts::value<std::string>());
			options.add_options()("plugin-mm-json",
								  "plugin-mm.json of the plugin to check (with enum names resolved)",
								  cxxopts::value<std::string>());
			options.add_options()("module",
								  "Module slug to check (repeat, or comma-separate, for more). Default: all modules",
								  cxxopts::value<std::vector<std::string>>());

			options.add_options()("h,help", "Print help");

			auto args = options.parse(argc, argv);

			if (args.count("patch") > 0)
				patch = args["patch"].as<std::string>();

			if (args.count("num_samples") > 0)
				samples_to_run = args["num_samples"].as<unsigned>();

			if (args.count("out") > 0)
				audio_out_file = args["out"].as<std::string>();

			if (args.count("in") > 0)
				audio_in_file = args["in"].as<std::string>();

			if (args.count("list-modules") > 0)
				list_modules = true;

			check_element_layout = args.count("check-element-layout") > 0;

			if (args.count("plugin-json") > 0)
				plugin_json = args["plugin-json"].as<std::string>();

			if (args.count("plugin-mm-json") > 0)
				plugin_mm_json = args["plugin-mm-json"].as<std::string>();

			if (args.count("module") > 0)
				modules = args["module"].as<std::vector<std::string>>();

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
