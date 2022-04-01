#include "app_startup.hh"
#include "audio.hh"
#include "conf/board_codec_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "fatfs/fileio.hh"
#include "hsem_handler.hh"
#include "norflashramdisk_ops.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchfileio.hh"
#include "patchlist.hh"
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

	MemTest::check(0xC300'0000, 0xD000'0000);
	MemTest::check(0xD000'0000, 0xE000'0000);

	StaticBuffers::init();
	PatchList patch_list{};

	NorFlashRamDiskOps nordisk{StaticBuffers::virtdrive};
	FileIO::register_disk(&nordisk, Disk::NORFlash);
	if (!FileIO::mount_disk(Disk::NORFlash)) {
		printf("No Fatfs found on NOR Flash, formatting and creating default patch files\r\n");
		PatchFileIO::factory_reset(Disk::NORFlash);
	}
	PatchFileIO::load_patches_from_disk(Disk::NORFlash, patch_list);

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

	UsbDriveDevice usb_drive{nordisk};
	usb_drive.start();

	while (true) {
		if (nordisk.get_status() == NorFlashRamDiskOps::Status::RequiresWriteBack) {
			mbox.patchlist_reloading = true;
			printf("NOR Flash writeback begun.\r\n");
			if (FileIO::unmount_disk(Disk::NORFlash)) { //nordisk.unmount()) {
				printf("NOR Flash writeback done. Refreshing patch list.\r\n");
				PatchFileIO::load_patches_from_disk(Disk::NORFlash, patch_list);
				mbox.patchlist_updated = true;
			} else {
				printf("NOR Flash writeback failed!\r\n");
			}
			nordisk.set_status(NorFlashRamDiskOps::Status::NotInUse);
			mbox.patchlist_reloading = false;
		}
		__WFI();
	}
}

void recover_from_task_fault() {
	main();
}
