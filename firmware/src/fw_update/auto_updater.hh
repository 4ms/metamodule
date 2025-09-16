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

		auto usbauto = FS::file_size(file_storage_proxy, {"autoupdate_fw", Volume::USB});
		auto sdauto = FS::file_size(file_storage_proxy, {"autoupdate_fw", Volume::USB});

		Volume vol = usbauto ? Volume::USB : sdauto ? Volume::SDCard : Volume::MaxVolumes;

		if (vol == Volume::MaxVolumes)
			return;

		const auto manifest_size = FS::file_size(file_storage_proxy, {"metamodule-firmware/metamodule.json", vol});
		if (!manifest_size) {
			pr_err("AutoUpdater: Unable to read update manifest file\n");
			return;
		}

		FirmwareUpdaterProxy updater{file_storage_proxy, true};
		if (!updater.start("metamodule-firmware/metamodule.json", vol, manifest_size.value())) {
			pr_err("AutoUpdater: Could not load manifest file\n");
			return;
		}

		hil_message("*updating\n");
		ui.notify_now_playing("AutoUpdater: Updating firmware...");
		ui.update_screen();

		while (true) {
			const auto status = updater.process();
			if (status.state == FirmwareUpdaterProxy::Success) {
				hil_message("*success\n");

				ui.notify_now_playing("AutoUpdater: Firmware updated!");
				ui.update_screen();
				break;

			} else if (status.state == FirmwareUpdaterProxy::Error) {
				hil_message("*failure\n");
				pr_err("%s\n", status.message.c_str());

				ui.notify_now_playing("AutoUpdater: Failed to update firmware");
				ui.update_screen();
				break;
			}
		}

		while (true) {
			__NOP();
		}
	}
};

} // namespace MetaModule
