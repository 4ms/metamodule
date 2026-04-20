#pragma once
#include "console/pr_dbg.hh"
#include "general_io.hh"
#include "gui/ui.hh"
#include "patch_file/file_storage_proxy.hh"
#include "test_modules.hh"
#include "test_patches.hh"

namespace MetaModule
{

struct CpuLoadTest {
	static bool should_run_tests(FileStorageProxy &file_storage_proxy) {
		return FS::file_size(file_storage_proxy, {"run_cpu_tests", Volume::USB}).has_value();
	}

	static void run_tests(FileStorageProxy &file_storage_proxy, Ui &ui, PluginManager &plugin_manager) {
		std::string should_run;
		FS::read_file(file_storage_proxy, should_run, {"run_cpu_tests", Volume::USB});

		const auto run_all = should_run.starts_with("all\n");
		const auto run_modules = run_all || should_run.starts_with("modules\n");
		const auto run_patches = run_all || should_run.starts_with("patches\n");
		const auto run_hil = should_run.starts_with("hil\n");

		bool do_module_tests = run_modules;
		bool do_patch_tests = run_patches;

		if (run_hil) {
			// TODO: auto load all plugins on USB drive
			if (!preload_all_plugins(plugin_manager)) {
				hil_message("*failure\n");
				return;
			}
			do_module_tests = true;
		}

		if (run_modules || run_patches) {
			ui.preload_plugins(plugin_manager);
		}

		// TODO: check file contents and only test brands that are in the file
		// "Brand1\nBrand2\n" => only test Brand1 and Brand2

		if (do_module_tests || do_patch_tests) {
			pr_info("A7 Core 2 running CPU load tests\n");
			hil_message("*loadtesting\n");
		}

		if (do_module_tests) {
			run_module_tests(file_storage_proxy, ui);
		}

		if (do_patch_tests) {
			run_patch_tests(file_storage_proxy, ui);
		}

		if (do_module_tests || do_patch_tests) {
			hil_message("*success\n");
		}
	}

	static void run_module_tests(FileStorageProxy &file_storage_proxy, Ui &ui) {
		// clear previous results files
		FS::write_file(file_storage_proxy, std::string("In progress"), {"cpu_test.csv", Volume::USB});
		FS::write_file(file_storage_proxy, std::string(""), {"cpu_test_in_progress.csv", Volume::USB});

		std::string results;
		results.reserve(1024 * 1024); // reserve a 1MB to reduce memory fragmentation
		LoadTest::test_all_modules([&file_storage_proxy, &ui, &results](std::string_view csv_line) {
			results += csv_line;
			FS::append_file(file_storage_proxy, csv_line, {"cpu_test_in_progress.csv", Volume::USB});
			ui.update_screen();
		});
		FS::write_file(file_storage_proxy, results, {"cpu_test.csv", Volume::USB});
	}

	static void run_patch_tests(FileStorageProxy &file_storage_proxy, Ui &ui) {
		FS::write_file(file_storage_proxy, std::string("In progress"), {"cpu_test_patches.csv", Volume::USB});
		FS::write_file(file_storage_proxy, std::string(""), {"cpu_test_patches_in_progress.csv", Volume::USB});

		std::string results;
		results.reserve(64 * 1024);
		LoadTest::test_all_patches(
			file_storage_proxy, [&file_storage_proxy, &ui, &results](std::string_view csv_line) {
				results += csv_line;
				FS::append_file(
					file_storage_proxy, csv_line, {"cpu_test_patches_in_progress.csv", Volume::USB});
				ui.update_screen();
			});
		FS::write_file(file_storage_proxy, results, {"cpu_test_patches.csv", Volume::USB});
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
