#pragma once
#include "console/pr_dbg.hh"
#include "general_io.hh"
#include "gui/ui.hh"
#include "patch_file/file_storage_proxy.hh"
#include "test_modules.hh"
#include "test_patches.hh"
#include <cstdlib>

namespace MetaModule
{

struct CpuLoadTest {

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
	static bool should_run_hil_tests(FileStorageProxy &file_storage_proxy) {
		if (FS::file_size(file_storage_proxy, {"run_cpu_tests", Volume::USB}).has_value()) {
			std::string should_run;
			FS::read_file(file_storage_proxy, should_run, {"run_cpu_tests", Volume::USB});
			return should_run.starts_with("hil\n");
		}
		return false;
	}
	static bool should_run_module_tests(FileStorageProxy &file_storage_proxy) {
		if (FS::file_size(file_storage_proxy, {"run_cpu_tests", Volume::USB}).has_value()) {
			std::string should_run;
			FS::read_file(file_storage_proxy, should_run, {"run_cpu_tests", Volume::USB});
			return should_run.starts_with("all\n") || should_run.starts_with("modules\n");
		}
		return false;
	}

	static bool should_run_patch_tests(FileStorageProxy &file_storage_proxy) {
		if (FS::file_size(file_storage_proxy, {"run_cpu_tests", Volume::USB}).has_value()) {
			std::string should_run;
			FS::read_file(file_storage_proxy, should_run, {"run_cpu_tests", Volume::USB});
			return should_run.starts_with("all\n") || should_run.starts_with("patches\n");
		}
		return false;
	}

	static void run_hil_tests(FileStorageProxy &file_storage_proxy, Ui &ui, PluginManager &plugin_manager) {
		pr_info("Running HIL CPU load tests\n");

		if (!preload_all_plugins(plugin_manager)) {
			pr_err("Failed preloading plugins for HIL CPU load tests\n");
			hil_message("*failure\n");
			return;
		}
		hil_message("*loadtesting\n");

		run_module_tests(file_storage_proxy, ui);
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

	static bool preload_all_plugins(PluginManager &plugin_manager) {
		plugin_manager.start_loading_plugin_list();

		while (true) {
			auto result = plugin_manager.process_loading();

			if (result.state == PluginFileLoader::State::GotList) {
				break;
			}

			if (result.state == PluginFileLoader::State::Error) {
				return false;
			}
		}

		auto list = plugin_manager.found_plugin_list();

		for (auto i = 0u; i < list->size(); ++i) {
			printf("Loading plugin: '%s'\n", plugin_manager.plugin_name(i).c_str());

			plugin_manager.load_plugin(i);
			auto load = true;
			while (load) {
				switch (plugin_manager.process_loading().state) {
					using enum PluginFileLoader::State;
					case Success:
						load = false;
						break;

					case RamDiskFull:
					case InvalidPlugin:
					case Error:
						return false;

					default:
						continue;
				}
			}
		}

		return true;
	}
};

} // namespace MetaModule
