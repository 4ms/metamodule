#include "aux_core_player.hh"
#include "conf/hsem_conf.hh"
#include "core_a7/a7_shared_memory.hh"
#include "coreproc_plugin/async_thread_control.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "dynload/plugin_manager.hh"
#include "fs/norflash_layout.hh"
#include "fs/syscall/filesystem.hh"
#include "fw_update/updater_proxy.hh"
#include "gui/ui.hh"
#include "internal_plugin_manager.hh"
#include "load_test/test_manager.hh"
#include "ramdisk_ops.hh"

using FrameBufferT =
	std::array<lv_color_t, MetaModule::ScreenBufferConf::width * MetaModule::ScreenBufferConf::height / 4>;
static inline FrameBufferT framebuf1 alignas(64);
static inline FrameBufferT framebuf2 alignas(64);

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

	LVGLDriver gui{MMDisplay::flush_to_screen, MMDisplay::read_input, MMDisplay::wait_cb, framebuf1, framebuf2};

	RamDiskOps ramdisk_ops{*A7SharedMemoryS::ptrs.ramdrive};
	FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	AssetFS asset_fs{AssetVolFlashOffset};
	Filesystem::init(ramdisk);
	auto &file_storage_proxy = *A7SharedMemoryS::ptrs.patch_storage;
	PluginManager plugin_manager{file_storage_proxy, ramdisk};
	Ui ui{*A7SharedMemoryS::ptrs.patch_playloader,
		  file_storage_proxy,
		  *A7SharedMemoryS::ptrs.open_patch_manager,
		  *A7SharedMemoryS::ptrs.sync_params,
		  *A7SharedMemoryS::ptrs.patch_mod_queue,
		  plugin_manager,
		  ramdisk};
	ui.update_screen();
	ui.update_page();

	InternalPluginManager internal_plugin_manager{ramdisk, asset_fs};
	if (!internal_plugin_manager.asset_fs_valid) {
		ui.notify_error("Graphic assets are corrupted!\nRe-install firmware.");
	}

	AuxPlayer aux_player{*A7SharedMemoryS::ptrs.patch_player, ui};

	// Wait for M4 to be ready (so USB and SD are available)
	while (mdrivlib::HWSemaphore<M4CoreReady>::is_locked())
		;

	[&]() {
		using namespace mdrivlib;

		if (!FS::file_size(file_storage_proxy, {"autoupdate_fw", Volume::USB})) {
			return;
		}

		const auto manifest_size =
			FS::file_size(file_storage_proxy, {"metamodule-firmware/metamodule.json", Volume::USB});
		if (!manifest_size) {
			pr_err("unable to read update manifest file\n");
			return;
		}

		FirmwareUpdaterProxy updater{file_storage_proxy, true};
		if (!updater.start("metamodule-firmware/metamodule.json", Volume::USB, manifest_size.value())) {
			pr_err("could not load manifest file\n");
			return;
		}

		std::size_t prev_prog{};

		auto print_prog = [&prev_prog](const FirmwareUpdaterProxy::Status &status) {
			const auto state = status.state == FirmwareUpdaterProxy::Verifying ? "verifying" : "writing";

			if (status.bytes_completed != prev_prog) {
				prev_prog = status.bytes_completed;
				printf("*%u*%u*%s*%s\n", status.bytes_completed, status.file_size, state, status.name.c_str());
			}
		};

		printf("*updating\n");

		while (true) {
			const auto status = updater.process();
			if (status.state == FirmwareUpdaterProxy::Verifying || status.state == FirmwareUpdaterProxy::Writing) {
				print_prog(status);
			} else if (status.state == FirmwareUpdaterProxy::Success) {
				printf("*success\n\n");
				break;
			} else if (status.state == FirmwareUpdaterProxy::Error) {
				printf("*failure\n");
				pr_err("%s\n", status.message.c_str());
				break;
			}
		}

		while (true) {
			__NOP();
		}
	}();

	printf("*initialized\n");

	ui.preload_plugins();

	// Signal that we're ready
	printf("A7 Core 2 initialized\n");

	CpuLoadTest::run_tests(file_storage_proxy, ui);

	HWSemaphore<AuxCoreReady>::unlock();

	ui.load_initial_patch();

	while (true) {
		ui.update_screen();
		ui.update_page();
		__NOP();
	}
}
