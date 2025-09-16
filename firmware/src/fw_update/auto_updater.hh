#pragma once

#include "fs/syscall/fs_syscall_proxy.hh"
#include "general_io.hh"
#include "gui/ui.hh"
#include "patch_file/file_storage_proxy.hh"
#include "reboot.hh"
#include "updater_proxy.hh"

namespace MetaModule
{

struct AutoUpdater {
	static void run(FileStorageProxy &file_storage_proxy, Ui &ui) {
		using namespace mdrivlib;

		auto usbauto = FS::file_size(file_storage_proxy, {"autoupdate_fw", Volume::USB});
		auto sdauto = FS::file_size(file_storage_proxy, {"autoupdate_fw", Volume::SDCard});

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

				if (vol == Volume::USB)
					rename("usb:/autoupdate_fw", "usb:/done_autoupdate_fw");
				else if (vol == Volume::SDCard)
					rename("sdc:/autoupdate_fw", "sdc:/done_autoupdate_fw");

				pr_info("AutoUpdater: Renamed autoupdate file\n");

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

		int64_t tm = HAL_GetTick();
		while (true) {
			int64_t now = HAL_GetTick();
			if (now - tm > 10'000)
				reboot_system();
		}
	}
};

} // namespace MetaModule
