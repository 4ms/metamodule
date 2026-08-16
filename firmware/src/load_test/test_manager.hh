#pragma once
#include "console/pr_dbg.hh"
#include "general_io.hh"
#include "gui/ui.hh"
#include "patch_file/file_storage_proxy.hh"
#include "test_modules.hh"
#include "test_modules_memory.hh"
#include "test_patches.hh"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <optional>
#include <string_view>

namespace MetaModule
{

struct CpuLoadTest {

	// The first line of the run_cpu_tests file selects what to run: one of
	// these keywords, or - for the HIL cpu load test - the name of a single
	// brand to test instead of all of them.
	static constexpr std::array<std::string_view, 5> keywords{"hil", "all", "modules", "patches", "leak"};

	// Returns the first line of run_cpu_tests, stripped of trailing whitespace,
	// or "" if the file does not exist.
	static std::string read_command(FileStorageProxy &file_storage_proxy) {
		if (!FS::file_size(file_storage_proxy, {"run_cpu_tests", Volume::USB}).has_value())
			return "";

		std::string content;
		FS::read_file(file_storage_proxy, content, {"run_cpu_tests", Volume::USB});

		auto line = content.substr(0, content.find('\n'));
		while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t'))
			line.pop_back();

		return line;
	}

	struct HilTestParams {
		bool run = false;
		std::string brand; // empty => test every brand
	};

	static HilTestParams get_hil_test_params(FileStorageProxy &file_storage_proxy) {
		HilTestParams params;

		auto cmd = read_command(file_storage_proxy);
		if (cmd.empty())
			return params;

		if (cmd == "hil") {
			params.run = true;
			return params;
		}

		// Another test's keyword, not ours
		if (std::ranges::find(keywords, cmd) != keywords.end())
			return params;

		// Anything else names a single brand to load test
		params.run = true;
		params.brand = cmd;
		return params;
	}

	static bool should_run_module_tests(FileStorageProxy &file_storage_proxy) {
		auto cmd = read_command(file_storage_proxy);
		return cmd == "all" || cmd == "modules";
	}

	static bool should_run_patch_tests(FileStorageProxy &file_storage_proxy) {
		auto cmd = read_command(file_storage_proxy);
		return cmd == "all" || cmd == "patches";
	}

	static void run_hil_tests(FileStorageProxy &file_storage_proxy,
							  Ui &ui,
							  PluginManager &plugin_manager,
							  std::string_view only_brand = "") {
		if (only_brand.size())
			pr_info("Running HIL CPU load tests for brand '%.*s'\n", (int)only_brand.size(), only_brand.data());
		else
			pr_info("Running HIL CPU load tests\n");

		hil_message("*loadtesting\n");

		// clear previous results files
		FS::write_file(file_storage_proxy, std::string("In progress"), {"cpu_test.csv", Volume::USB});
		FS::write_file(file_storage_proxy, std::string("\n"), {"cpu_test_in_progress.csv", Volume::USB});

		std::string results;
		results.reserve(1024 * 1024); // reserve 1MB to reduce memory fragmentation

		auto append_file = [&file_storage_proxy, &ui, &results](std::string_view csv_line) {
			results += csv_line;
			FS::append_file(file_storage_proxy, csv_line, {"cpu_test_in_progress.csv", Volume::USB});
			ui.update_screen();
		};

		lv_show(ui_MainMenuNowPlayingPanel);
		lv_show(ui_MainMenuNowPlaying);

		append_file(LoadTest::csv_header());

		PatchPlayer player;

		// Test built-in brands first (registered before any plugin is loaded)
		bool tested_a_brand = false;
		for (auto brand : ModuleFactory::getAllBrands()) {
			if (only_brand.size() && only_brand != brand)
				continue;
			LoadTest::test_brand(brand, player, append_file);
			tested_a_brand = true;
		}

		// Then load one plugin at a time, test its module(s), and unload it.
		// Loading all plugins at once exhausts memory, so we keep only one resident.
		// Testing a single built-in brand needs no plugins loaded at all.
		if (!tested_a_brand || only_brand.empty()) {
			auto tested = test_plugins_one_at_a_time(plugin_manager, player, append_file, only_brand);
			if (!tested.has_value()) {
				pr_err("Failed getting plugin list for HIL CPU load tests\n");
				hil_message("*failure\n");
				return;
			}
			tested_a_brand |= *tested;
		}

		// A brand that never showed up (typo, or its plugin failed to load) would
		// otherwise look like a successful run that happened to test nothing.
		if (only_brand.size() && !tested_a_brand) {
			pr_err(
				"Brand '%.*s' not found in any built-in module or plugin\n", (int)only_brand.size(), only_brand.data());
			hil_message("*failure\n");
			return;
		}

		lv_label_set_text(ui_MainMenuNowPlaying, "Finished load tests");

		FS::write_file(file_storage_proxy, results, {"cpu_test.csv", Volume::USB});
		hil_message("*success\n");
	}

	static void run_module_tests(FileStorageProxy &file_storage_proxy, Ui &ui) {
		pr_info("Running module CPU load tests\n");

		// clear previous results files
		FS::write_file(file_storage_proxy, std::string("In progress"), {"cpu_test.csv", Volume::USB});
		FS::write_file(file_storage_proxy, std::string("\n"), {"cpu_test_in_progress.csv", Volume::USB});

		std::string results;
		results.reserve(1024 * 1024); // reserve a 1MB to reduce memory fragmentation
		LoadTest::test_all_modules([&file_storage_proxy, &ui, &results](std::string_view csv_line) {
			results += csv_line;
			FS::append_file(file_storage_proxy, csv_line, {"cpu_test_in_progress.csv", Volume::USB});
			ui.update_screen();
		});
		FS::write_file(file_storage_proxy, results, {"cpu_test.csv", Volume::USB});
		hil_message("*success\n");
	}

	static void run_patch_tests(PatchPlayer &player, FileStorageProxy &file_storage_proxy) {
		pr_info("Running patch CPU load tests\n");
		FS::write_file(file_storage_proxy, std::string("In progress"), {"cpu_test_patches.csv", Volume::USB});
		FS::write_file(file_storage_proxy, std::string("\n"), {"cpu_test_patches_in_progress.csv", Volume::USB});

		std::string results;
		results.reserve(64 * 1024);
		LoadTest::test_all_patches(
			player, file_storage_proxy, [&file_storage_proxy, &results](std::string_view csv_line) {
				results += csv_line;
				FS::append_file(file_storage_proxy, csv_line, {"cpu_test_patches_in_progress.csv", Volume::USB});
			});
		FS::write_file(file_storage_proxy, results, {"cpu_test_patches.csv", Volume::USB});
		hil_message("*success\n");
	}

	// Leak-slope diagnostic, triggered by a run_cpu_tests file of the form:
	//   leak
	//   Brand:Slug
	//   <iterations>      (optional, defaults to 100)
	struct LeakTestParams {
		bool run = false;
		std::string slug;
		unsigned iterations = 100;
	};

	static LeakTestParams get_leak_test_params(FileStorageProxy &file_storage_proxy) {
		LeakTestParams params;

		if (!FS::file_size(file_storage_proxy, {"run_cpu_tests", Volume::USB}).has_value())
			return params;

		std::string content;
		FS::read_file(file_storage_proxy, content, {"run_cpu_tests", Volume::USB});

		if (!content.starts_with("leak\n"))
			return params;

		// Line 1: "leak", Line 2: Brand:Slug, Line 3 (optional): iteration count
		auto line1_end = content.find('\n');
		auto slug_start = line1_end + 1;
		auto slug_end = content.find('\n', slug_start);

		params.slug =
			content.substr(slug_start, slug_end == std::string::npos ? std::string::npos : slug_end - slug_start);

		// Trim trailing whitespace/newline
		while (!params.slug.empty() &&
			   (params.slug.back() == '\r' || params.slug.back() == ' ' || params.slug.back() == '\n'))
			params.slug.pop_back();

		if (slug_end != std::string::npos) {
			if (auto n = std::atoi(content.c_str() + slug_end + 1); n > 0)
				params.iterations = (unsigned)n;
		}

		params.run = !params.slug.empty();
		return params;
	}

	static void run_leak_test(FileStorageProxy &file_storage_proxy, Ui &ui, LeakTestParams const &params) {
		pr_info("Running module leak-slope test: %s (%u iterations)\n", params.slug.c_str(), params.iterations);

		FS::write_file(file_storage_proxy, std::string("In progress"), {"leak_test.csv", Volume::USB});

		std::string results;
		results.reserve(64 * 1024);
		LoadTest::test_module_leak_slope(
			params.slug, params.iterations, [&file_storage_proxy, &ui, &results](std::string_view line) {
				results += line;
				FS::append_file(file_storage_proxy, line, {"leak_test_in_progress.csv", Volume::USB});
				ui.update_screen();
			});

		FS::write_file(file_storage_proxy, results, {"leak_test.csv", Volume::USB});
		hil_message("*success\n");
	}

	// Loads each plugin one at a time, running the CPU load test on the module(s)
	// it registers, then unloads it before moving on — so only a single plugin is
	// ever resident. The brand(s) a plugin contributes are found by diffing
	// ModuleFactory::getAllBrands() before/after loading it (same approach as
	// ModuleImageGen). If only_brand is set, every other brand is skipped and
	// loading stops as soon as the plugin providing it has been tested.
	// Returns nullopt only if the plugin list couldn't be read (a plugin that
	// fails to load is skipped); otherwise, whether any brand was tested.
	static std::optional<bool> test_plugins_one_at_a_time(PluginManager &plugin_manager,
														  PatchPlayer &player,
														  auto append_file,
														  std::string_view only_brand = "") {
		// Scanning for plugins is silent too, and when a single brand is being
		// tested it is the very first thing that happens after *loadtesting
		LoadTest::send_heartbeat();

		plugin_manager.start_loading_plugin_list();

		while (true) {
			auto result = plugin_manager.process_loading();
			if (result.state == PluginFileLoader::State::GotList)
				break;
			if (result.state == PluginFileLoader::State::Error)
				return std::nullopt;
		}

		auto list = plugin_manager.found_plugin_list();
		bool tested_a_brand = false;

		for (auto i = 0u; i < list->size(); ++i) {
			auto plugin_file_name = plugin_manager.plugin_name(i);
			printf("Loading plugin: '%s'\n", plugin_file_name.c_str());

			// Loading a plugin produces no test output, so without this the host
			// sees no traffic while plugins are skipped. Testing a single brand
			// can skip dozens of plugins in a row before finding its own, which
			// is well past the host's inter-message timeout.
			LoadTest::send_heartbeat();

			auto brands_before = ModuleFactory::getAllBrands();

			plugin_manager.load_plugin(i);
			bool loaded_ok = true;
			while (true) {
				using enum PluginFileLoader::State;
				auto state = plugin_manager.process_loading().state;
				if (state == Success)
					break;
				if (state == RamDiskFull || state == InvalidPlugin || state == Error) {
					pr_warn("Failed to load plugin '%s' for CPU load test, skipping\n", plugin_file_name.c_str());
					loaded_ok = false;
					break;
				}
			}

			if (loaded_ok) {
				bool tested_this_plugin = false;

				for (auto brand : ModuleFactory::getAllBrands()) {
					if (std::ranges::find(brands_before, brand) != brands_before.end())
						continue; // pre-existing brand, not from this plugin
					if (only_brand.size() && only_brand != brand)
						continue;
					LoadTest::test_brand(brand, player, append_file);
					tested_this_plugin = true;
				}

				// Never free the plugin's code while the player still holds one of its
				// modules: unloading the plugin invalidates the module's vtable, and the
				// next load_patch() would deinit the dangling module and crash.
				if (player.is_loaded)
					player.unload_patch();

				plugin_manager.unload_plugin(plugin_file_name);

				tested_a_brand |= tested_this_plugin;

				// The brand we were asked for has been found and tested, so there's
				// no reason to keep loading the rest of the plugins.
				if (only_brand.size() && tested_this_plugin)
					break;
			}
		}

		return tested_a_brand;
	}
};

} // namespace MetaModule
