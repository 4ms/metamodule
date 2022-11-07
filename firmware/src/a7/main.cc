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
// #include "usb/usb_manager.hh"
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
	// ==> m4:
	// RamDiskOps ramdiskops{StaticBuffers::virtdrive};
	// RamDiskFileIO::register_disk(&ramdiskops, Disk::RamDisk);
	// RamDiskFileIO::format_disk(Disk::RamDisk);

	// Setup Patch Storage (On QSPI flash)
	mdrivlib::QSpiFlash flash{qspi_patchflash_conf};
	PatchStorage patchdisk{flash, StaticBuffers::virtdrive};

	// Populate Patch List from Patch Storage
	PatchList patch_list{};
	// patchdisk.factory_clean(); //Remove this when not testing!
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

	// Maybe only A7 has access to the PLL?
	// USB_HS_PHYCInit();

	// Tell M4 we're done with init
	HWSemaphore<MainCoreReady>::unlock();

	// wait for M4 to be ready
	while (HWSemaphore<M4_ready>::is_locked())
		;

	param_cache.clear();
	patch_loader.load_initial_patch();
	audio.start();
	ui.start();

	// UsbManager usb{ramdiskops};
	// usb.start();

	while (true) {
		// usb.process();

		// TODO: if disk is unexpectedly disconnected, we should scan it
		// TODO: can this be encapsulated? patch_list + RamDiskFileIO/ramdiskops + patch_storage

		// if (ramdiskops.get_status() == RamDiskOps::Status::RequiresWriteBack) {
		if (false) { //HSEM<RamDiskAvailableToA7> unlocked
			patch_list.lock();
			printf_("NOR Flash writeback begun.\r\n");
			//RamDiskFileIO::unmount_disk(Disk::RamDisk); // ==> M4 does this before unlocking HSEM [and it doesn't do anything anyways]
			if (patchdisk.ramdisk_patches_to_norflash()) {
				printf_("NOR Flash writeback done. Refreshing patch list.\r\n");
				patch_list.mark_modified();
			} else {
				printf_("NOR Flash writeback failed!\r\n");
			}
			// ramdiskops.set_status(RamDiskOps::Status::NotInUse);
			//unlock HSEM<RamDiskAvailableToM4>
			patch_list.unlock();
		}
		__WFI();
	}
}

void recover_from_task_fault() {
	main();
}
