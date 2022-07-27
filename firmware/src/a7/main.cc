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

	// Populate Patch List from Patch Storage:
	PatchList patch_list{};
	RamDiskOps ramdiskops{StaticBuffers::virtdrive};
	RamDiskFileIO::register_disk(&ramdiskops, Disk::NORFlash);
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};

	PatchStorage patchdisk{flash, StaticBuffers::virtdrive};
	patchdisk.fill_patchlist_from_norflash(patch_list);

	PatchPlayer patch_player;
	ParamQueue param_queue;
	UiAudioMailbox mbox;

	Ui ui{patch_player, patch_list, param_queue, mbox};

	AudioStream audio{patch_player,
					  StaticBuffers::audio_in_dma_block,
					  StaticBuffers::audio_out_dma_block,
					  param_queue,
					  mbox,
					  StaticBuffers::param_blocks,
					  StaticBuffers::auxsignal_block};

	//Used by mini, but will be deprecated:
	static uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];

	SharedMemory::write_address_of(&StaticBuffers::param_blocks, SharedMemory::ParamsPtrLocation);
	SharedMemory::write_address_of(&led_frame_buffer, SharedMemory::LEDFrameBufLocation);
	SharedMemory::write_address_of(&StaticBuffers::auxsignal_block, SharedMemory::AuxSignalBlockLocation);
	SharedMemory::write_address_of(&patch_player, SharedMemory::PatchPlayerLocation);

	// Needed for LED refresh
	HWSemaphoreCoreHandler::enable_global_ISR(2, 1);

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;
	param_queue.clear();
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

	enum FUSBRegister : uint8_t {
		ID = 0x01,
		Control2 = 0x08,
		OCP = 0x0D,
		Status0A = 0x3C,
		Status1A = 0x3D,
		InterruptA = 0x3E,
		InterruptB = 0x3F,
		Status0 = 0x40,
		Status1 = 0x41,
		Interrupt = 0x42,
	};
	data[0] = 0b00000011;
	usbi2c.mem_write(DevAddr, FUSBRegister::Control2, 1, data, 1);
	data[0] = 0xAA;
	usbi2c.mem_read(DevAddr, FUSBRegister::Control2, 1, data, 1);
	printf_("Control2 read %x\n", data[0]);

	data[0] = 0b00000000;
	usbi2c.mem_write(DevAddr, FUSBRegister::OCP, 1, data, 1);

	Pin fusb_int{GPIO::A, 10, PinMode::Input};
	bool usb_connected = false;

	uint32_t tm = HAL_GetTick();

	while (true) {
		if ((HAL_GetTick() - tm) > 200) {
			usbi2c.mem_read(DevAddr, FUSBRegister::Status0, 1, &(data[0]), 1);
			if (data[0] != data[1])
				printf_("Status0: %x\n", data[0]);
			data[1] = data[0];

			usbi2c.mem_read(DevAddr, FUSBRegister::Interrupt, 1, &(data[2]), 1);
			if (data[2] != data[3])
				printf_("Interrupt: %x\n", data[2]);
			data[3] = data[2];
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
			mbox.patchlist_reloading = true;
			printf("NOR Flash writeback begun.\r\n");
			RamDiskFileIO::unmount_disk(Disk::NORFlash);
			if (patchdisk.ramdisk_patches_to_norflash()) {
				printf("NOR Flash writeback done. Refreshing patch list.\r\n");
				mbox.patchlist_updated = true;
			} else {
				printf("NOR Flash writeback failed!\r\n");
			}
			ramdiskops.set_status(RamDiskOps::Status::NotInUse);
			mbox.patchlist_reloading = false;
		}
		__WFI();
	}
}

void recover_from_task_fault() {
	main();
}
