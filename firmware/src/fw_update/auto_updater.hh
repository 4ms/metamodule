#pragma once

#include "general_io.hh"
#include "gui/ui.hh"
#include "patch_file/file_storage_proxy.hh"
#include "updater_proxy.hh"

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

		hil_message("*updating\n");
		lv_label_set_text(ui_MainMenuNowPlaying, "Updating firmware...");

		while (true) {
			const auto status = updater.process();
			if (status.state == FirmwareUpdaterProxy::Success) {
				hil_message("*success\n");
				lv_label_set_text(ui_MainMenuNowPlaying, "Succeess!");
				break;
			} else if (status.state == FirmwareUpdaterProxy::Error) {
				hil_message("*failure\n");
				pr_err("%s\n", status.message.c_str());

				lv_label_set_text(ui_MainMenuNowPlaying, "failure :(");
				break;
			}
		}

		while (true) {
			__NOP();
		}
	}
};

} // namespace MetaModule
