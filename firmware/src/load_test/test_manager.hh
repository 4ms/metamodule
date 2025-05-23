#pragma once
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

		if (should_run.starts_with("all\n")) {
			// TODO: if not "all" then check file contents and only test brands that are in the file
			// "Brand1\nBrand2\n" => only test Brand1 and Brand2
			// "all\n" => test all builtin and preloaded plugins

			pr_info("A7 Core 2 running CPU load tests\n");

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
		}
	};
};

} // namespace MetaModule
