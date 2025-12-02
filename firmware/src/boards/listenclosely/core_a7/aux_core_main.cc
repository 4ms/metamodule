#include "conf/hsem_conf.hh"
#include "core_a7/a7_shared_memory.hh"
#include "coreproc_plugin/async_thread_control.hh"
#include "drivers/hsem.hh"
#include "fat_file_io.hh"
#include "fs/syscall/filesystem.hh"
#include "ramdisk_ops.hh"
#include "system/print_time.hh"

extern "C" void aux_core_main() {
	using namespace MetaModule;
	using namespace mdrivlib;

	// Tell A7 we're not ready yet
	HWSemaphore<AuxCoreReady>::lock();

	// Wait for m4 core to be ready
	while (HWSemaphore<MainCoreReady>::is_locked() || HWSemaphore<M4CoreReady>::is_locked())
		;

	pr_info("A7 Core 2 starting\n");

	start_module_threads();

#ifdef CONSOLE_USE_USB
	UartLog::use_usb(A7SharedMemoryS::ptrs.console_buffer);
#endif

	RamDiskOps ramdisk_ops{*A7SharedMemoryS::ptrs.ramdrive};
	FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	Filesystem::init(ramdisk);

	auto settings_file = fopen("nor:/settings.yml", "r");

	// Wait for M4 to be ready (so USB and SD are available)
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked())
		;

	hil_message("*ready\n");
	hil_message("*initialized\n");

	// Signal that we're ready
	printf("A7 Core 2 initialized\n");
	print_time();

	HWSemaphore<AuxCoreReady>::unlock();

	while (true) {
		// TODO: handle requests to write settings file
		__NOP();
	}
}
