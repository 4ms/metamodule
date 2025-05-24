#pragma once
#include "general_io.hh"
#include "gui/ui.hh"
#include "patch_file/file_storage_proxy.hh"
#include "test_modules.hh"

namespace MetaModule
{

struct AutoUpdater {
	static void run(FileStorageProxy &file_storage_proxy, Ui &ui) {
		using namespace mdrivlib;

		if (!FS::file_size(file_storage_proxy, {"autoupdate_fw", Volume::USB})) {
			return;
		}

		const auto manifest_size =
			FS::file_size(file_storage_proxy, {"metamodule-firmware/metamodule.json", Volume::USB});
		if (!manifest_size) {
			pr_err("unable to read update manifest file\n");
			return;
		}

		FirmwareUpdaterProxy updater{file_storage_proxy, true};
		if (!updater.start("metamodule-firmware/metamodule.json", Volume::USB, manifest_size.value())) {
			pr_err("could not load manifest file\n");
			return;
		}

		std::size_t prev_prog{};

		auto print_prog = [&prev_prog](const FirmwareUpdaterProxy::Status &status) {
			const auto state = status.state == FirmwareUpdaterProxy::Verifying ? "verifying" : "writing";

			if (status.bytes_completed != prev_prog) {
				prev_prog = status.bytes_completed;
				printf("*%u*%u*%s*%s\n", status.bytes_completed, status.file_size, state, status.name.c_str());
			}
		};

		printf("*updating\n");
		lv_label_set_text(ui_MainMenuNowPlaying, "Updating firmware...");

		while (true) {
			const auto status = updater.process();
			if (status.state == FirmwareUpdaterProxy::Verifying || status.state == FirmwareUpdaterProxy::Writing) {
				print_prog(status);
			} else if (status.state == FirmwareUpdaterProxy::Success) {
				printf("*success\n");
				lv_label_set_text(ui_MainMenuNowPlaying, "Succeess!");
				break;
			} else if (status.state == FirmwareUpdaterProxy::Error) {
				printf("*failure\n");
				lv_label_set_text(ui_MainMenuNowPlaying, "failure :(");
				pr_err("%s\n", status.message.c_str());
				break;
			}
		}

		while (true) {
			__NOP();
		}
	}
};

struct CpuLoadTest {
	static void run_tests(FileStorageProxy &file_storage_proxy, Ui &ui) {
		using namespace mdrivlib;

		std::string should_run;
		FS::read_file(file_storage_proxy, should_run, {"run_cpu_tests", Volume::USB});

		const auto run_all = should_run.starts_with("all\n");
		const auto run_hil = should_run.starts_with("hil\n");
		if (run_hil) {
			/// auto load all plugins on USB drive
		}

		if (run_all || run_hil) {
			// TODO: if not "all" then check file contents and only test brands that are in the file
			// "Brand1\nBrand2\n" => only test Brand1 and Brand2
			// "all\n" => test all builtin and preloaded plugins

			pr_info("A7 Core 2 running CPU load tests\n");

			printf("*loadtesting\n");

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
			printf("*success\n");
		}
	};
};

} // namespace MetaModule
