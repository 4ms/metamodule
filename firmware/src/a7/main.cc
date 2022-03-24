#include "app_startup.hh"
#include "audio.hh"
#include "conf/board_codec_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/pin.hh"
#include "drivers/stm32xx.h"
#include "hsem_handler.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "shared_bus.hh"
#include "shared_memory.hh"
#include "static_buffers.hh"
#include "ui.hh"
#include "usb/usb_drive_device.hh"

namespace MetaModule
{

struct SystemInit : AppStartup, Debug, Hardware {
} _sysinit;

} // namespace MetaModule

void main() {
	using namespace MetaModule;

	StaticBuffers::init();

	NorFlashFS norfs{"0", StaticBuffers::virtdrive}; //Volume 0 = RamDisk. TODO: use string volume names

	PatchList patch_list{};

	if (!norfs.init()) {
		printf("ERROR: NOR Flash returned wrong id\r\n");
	}
	if (norfs.startfs()) {
		printf("NOR Flash mounted as virtual fs\r\n");
	} else {
		printf("No Fatfs found on NOR Flash, creating FS and default patch files...\r\n");
		auto ok = norfs.make_fs();
		uint8_t *default_patch;

		uint32_t len = patch_list.get_default_patch_data(0, default_patch);
		ok &= norfs.create_file(patch_list.get_default_patch_filename(0), {default_patch, len});

		len = patch_list.get_default_patch_data(1, default_patch);
		ok &= norfs.create_file(patch_list.get_default_patch_filename(1), {default_patch, len});

		ok &= norfs.stopfs();
		if (!ok)
			printf("Failed to create filesystem and default patches\r\n");
	}

	patch_list.refresh_patches_from_fs(norfs);

	PatchPlayer patch_player;
	ParamQueue param_queue;
	UiAudioMailbox mbox;

	// LedFrame<LEDUpdateHz> leds{StaticBuffers::led_frame_buffer};

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

	// // Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;
	param_queue.clear();
	audio.start();
	ui.start();

	// norfs.init();
	UsbDriveDevice usb_drive{&norfs};
	usb_drive.start();

	while (true) {
		ui.update();
		if (norfs.get_status() == NorFlashFS::Status::RequiresWriteBack) {
			printf("NOR Flash writeback begun.\r\n");
			if (norfs.stopfs()) {
				printf("NOR Flash writeback done. Refreshing patch list.\r\n");
				patch_list.refresh_patches_from_fs(norfs);
				mbox.patchlist_updated = true;
			} else {
				printf("NOR Flash writeback failed!\r\n");
			}
			norfs.set_status(NorFlashFS::Status::NotInUse);
		}
	}
}

void recover_from_task_fault() {
	main();
}
