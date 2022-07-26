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

	while (true) {
		if (ramdiskops.get_status() == RamDiskOps::Status::RequiresWriteBack) {
			mbox.patchlist_reloading = true;
			printf("NOR Flash writeback begun.\r\n");
			RamDiskFileIO::unmount_disk(Disk::NORFlash);
			if (patchdisk.ramdisk_patches_to_norflash()) {
				printf("NOR Flash writeback done. Refreshing patch list.\r\n");
				// PatchFileIO::load_patches_from_disk(Disk::NORFlash, patch_list);
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
