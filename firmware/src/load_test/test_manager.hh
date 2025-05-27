#pragma once
#include "console/pr_dbg.hh"
#include "general_io.hh"
#include "gui/ui.hh"
#include "patch_file/file_storage_proxy.hh"
#include "test_modules.hh"

namespace MetaModule
{

struct CpuLoadTest {
	static void run_tests(FileStorageProxy &file_storage_proxy, Ui &ui) {
		using namespace mdrivlib;

		std::string should_run;
		FS::read_file(file_storage_proxy, should_run, {"run_cpu_tests", Volume::USB});

		bool do_tests = false;

		const auto run_all = should_run.starts_with("all\n");
		const auto run_hil = should_run.starts_with("hil\n");
		if (run_hil) {
			// TODO: auto load all plugins on USB drive
			if (!ui.preload_all_plugins()) {
				hil_message("*failure\n");
				return;
			}
			do_tests = true;
		}

		if (run_all) {
			ui.preload_plugins();
			do_tests = true;
		}

		// TODO: check file contents and only test brands that are in the file
		// "Brand1\nBrand2\n" => only test Brand1 and Brand2

		if (do_tests) {
			pr_info("A7 Core 2 running CPU load tests\n");

			hil_message("*loadtesting\n");

			// clear previous results files
			FS::write_file(file_storage_proxy, std::string("In progress"), {"cpu_test.csv", Volume::USB});
			FS::write_file(file_storage_proxy, std::string(""), {"cpu_test_in_progress.csv", Volume::USB});

			std::string results;
			LoadTest::test_all_modules([&file_storage_proxy, &ui, &results](std::string_view csv_line) {
				results += csv_line;
				FS::append_file(file_storage_proxy, csv_line, {"cpu_test_in_progress.csv", Volume::USB});
				ui.update_screen();
			});
			FS::write_file(file_storage_proxy, results, {"cpu_test.csv", Volume::USB});
			hil_message("*success\n");
		}
	};
};

} // namespace MetaModule
