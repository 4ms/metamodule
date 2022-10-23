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
	usb_drive.start();

	HAL_Delay(10);
	I2CPeriph usbi2c{usb_i2c_conf};
	uint8_t data[4] = {0xAA};
	constexpr uint8_t DevAddr = 0b01000100;
	auto err = usbi2c.mem_read(0b01000100, 0x01, 1, data, 1);
	if (err == mdrivlib::I2CPeriph::I2C_NO_ERR)
		printf_("ID Read %d\n", data[0]);
	else {
		printf_("Err: %d\n", err);
		__BKPT();
	}

	// TODO: Get USB-C working totally and move to its own class/file
	enum FUSBRegister : uint8_t {
		ID = 0x01,
		Control0 = 0x06,
		Control1 = 0x07,
		Control2 = 0x08,
		Power = 0x0B,
		OCP = 0x0D,
		Status0A = 0x3C,
		Status1A = 0x3D,
		InterruptA = 0x3E,
		InterruptB = 0x3F,
		Status0 = 0x40,
		Status1 = 0x41,
		Interrupt = 0x42,
	};
	data[0] = 0b00000100; //enable all Interrupts to host
	usbi2c.mem_write(DevAddr, FUSBRegister::Control0, 1, data, 1);

	data[0] = 0b00000101; //Enable SNK polling, (TOGGLE=1)
	usbi2c.mem_write(DevAddr, FUSBRegister::Control2, 1, data, 1);

	// data[0] = 0b00001111; //Enable all power
	// usbi2c.mem_write(DevAddr, FUSBRegister::Power, 1, data, 1);

	Pin fusb_int{GPIO::A, 10, PinMode::Input, 0, PinPull::Up};
	bool usb_connected = false;

	uint32_t tm = HAL_GetTick();

	while (true) {
		if ((HAL_GetTick() - tm) > 200) {
			tm = HAL_GetTick();
			usbi2c.mem_read(DevAddr, FUSBRegister::Status0, 1, &(data[0]), 1);
			if (data[0] != data[1])
				printf_("Status0: %x\n", data[0]);
			data[1] = data[0];

			usbi2c.mem_read(DevAddr, FUSBRegister::Interrupt, 1, &(data[2]), 1);
			// if (data[2] != data[3])
			// 	printf_("Interrupt: %x\n", data[2]);
			// data[3] = data[2];
		}
		if (fusb_int.is_on()) {
			if (!usb_connected)
				printf_("USB Connnected\n");
			usb_connected = true;
		} else {
			if (usb_connected)
				printf_("USB Disconnnected\n");
			usb_connected = false;
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
