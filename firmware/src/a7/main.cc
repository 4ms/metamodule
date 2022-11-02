#include "app_startup.hh"
#include "audio.hh"
#include "conf/board_codec_conf.hh"
#include "conf/qspi_flash_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/stm32xx.h"
#include "fatfs/ramdisk_fileio.hh"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_loader.hh"
#include "patch_player.hh"
#include "patchfileio.hh"
#include "patchlist.hh"
#include "patchstorage.hh"
#include "ramdisk_ops.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "static_buffers.hh"
#include "ui.hh"
#include "usb/usb_drive_device.hh"
#include "util/mem_test.hh"

#include "fusb302.hh"

namespace MetaModule
{

struct SystemInit : AppStartup, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	StaticBuffers::init();

	// Setup RAM disk
	RamDiskOps ramdiskops{StaticBuffers::virtdrive};
	RamDiskFileIO::register_disk(&ramdiskops, Disk::RamDisk);
	RamDiskFileIO::format_disk(Disk::RamDisk);

	// Setup Patch Storage (On QSPI flash)
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	PatchStorage patchdisk{flash, StaticBuffers::virtdrive};

	// Populate Patch List from Patch Storage
	PatchList patch_list{};
	patchdisk.factory_clean(); //Remove this when not testing!
	patchdisk.fill_patchlist_from_norflash(patch_list);
	patchdisk.norflash_patches_to_ramdisk();

	PatchPlayer patch_player;
	PatchLoader patch_loader{patch_list, patch_player};

	ParamCache param_cache;
	UiAudioMailbox mbox;

	Ui ui{patch_loader, patch_list, param_cache, mbox};

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_cache,
					  patch_loader,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block};

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&StaticBuffers::auxsignal_block, SharedMemory::AuxSignalBlockLocation);
	SharedMemory::write_address_of(&patch_player, SharedMemory::PatchPlayerLocation);

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

	param_cache.clear();
	patch_loader.load_initial_patch();
	audio.start();
	ui.start();

	UsbDriveDevice usb_drive{ramdiskops};
	usb_drive.init_usb_device();

	HAL_Delay(10);

	constexpr uint8_t DevAddr = 0b01000100;
	I2CPeriph usbi2c{usb_i2c_conf};
	FUSB302::Device usbctl{usbi2c, DevAddr};
	auto err = usbctl.init();
	if (err)
		printf_("Can't communicate with FUSB302\n");
	else
		printf_("FUSB302 ID Read 0x%x\n", usbctl.get_chip_id());

	usbctl.start_drp_polling();

	Pin fusb_int{GPIO::A, 10, PinMode::Input, 0, PinPull::Up, PinPolarity::Inverted};
	Pin usb_5v_src_enable{GPIO::A, PinNum::_15, PinMode::Output};
	usb_5v_src_enable.low();

	uint32_t tm = HAL_GetTick();
	bool int_asserted = false;
	FUSB302::Device::ConnectedState state;

	while (true) {

		//TODO: use a pinchange interrupt
		if (fusb_int.is_on()) {
			if (!int_asserted) {
				printf_("INT pin asserted\n");
				int_asserted = true;

				usbctl.handle_interrupt();
				auto newstate = usbctl.get_state();
				if (newstate != state) {
					state = newstate;

					if (state == FUSB302::Device::ConnectedState::AsDevice) {
						// usb_5v_src_enable.low();
						printf_("Connected as a device\n");
						usb_drive.start();
					} else if (state == FUSB302::Device::ConnectedState::AsHost) {
						// usb_5v_src_enable.high();
						printf_("TODO: start host...\n");
					} else if (state == FUSB302::Device::ConnectedState::None) {
						printf_("Disconnected, resuming DRP polling\n");
						// usb_5v_src_enable.low();
						usbctl.start_drp_polling();
					}
				}
			}
		} else {
			if (int_asserted) {
				printf_("INT pin de-asserted\n");
				int_asserted = false;
			}
		}
		if ((HAL_GetTick() - tm) > 200) {
			tm = HAL_GetTick();
			usbctl.reg_check<FUSB302::Register::Status0>("Status0");
			usbctl.reg_check<FUSB302::Register::Status0A>("Status0A");
			usbctl.reg_check<FUSB302::Register::Status1A>("Status1A");
		}

		if (ramdiskops.get_status() == RamDiskOps::Status::RequiresWriteBack) {
			patch_list.lock();
			printf("NOR Flash writeback begun.\r\n");
			RamDiskFileIO::unmount_disk(Disk::RamDisk);
			if (patchdisk.ramdisk_patches_to_norflash()) {
				printf("NOR Flash writeback done. Refreshing patch list.\r\n");
				patch_list.mark_modified();
			} else {
				printf("NOR Flash writeback failed!\r\n");
			}
			ramdiskops.set_status(RamDiskOps::Status::NotInUse);
			patch_list.unlock();
		}
		__WFI();
	}
}

void recover_from_task_fault() {
	main();
}
