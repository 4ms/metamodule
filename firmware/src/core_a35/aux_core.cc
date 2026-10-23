// The second A35 core ("core 1"; MP1's A7 core 2), as on MP1 (core_a7/aux_core_main.cc): it runs
// the GUI, and MP1's AuxPlayer (core_a7/aux_core_player.hh): when the audio stream on core 0 signals
// it with an SGI, it plays its share of the patch's modules, and reads the text displays the GUI
// watches.
//
// The GUI is here rather than on core 0 because only core 0 does the parts of each audio frame that
// aren't split between the cores, so core 1 has time left for the GUI even when core 0 is
// overloaded.

#include "aux_core.hh"
#include "conf/screen_conf.hh"
#include "console.hh"
#include "console/uart_log.hh"
#include "core_a7/aux_core_player.hh"
#include "core_a7/dev_drive_service.hh"
#include "core_a7/device_settings_proxy.hh"
#include "drivers/secondary_core_control.hh"
#include "dynload/plugin_manager.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/syscall/filesystem.hh"
#include "internal_interface/plugin_app_if_internal.hh"
#include "internal_interface/plugin_app_interface.hh"
#include "internal_plugin_manager.hh"
#include "lvgl_display.hh"
#include "static_buffers.hh"
#include "ui.hh"
#include "usb/usb_status_reader.hh"
#include <atomic>
#include <cstdio>

extern "C" void aux_core_startup(); // mdrivlib boot/aux_core_startup.s

namespace MetaModule
{

namespace
{
// Core 1 starts at aux_main() with no arguments (when we're at EL3, mdrivlib's SecondaryCore can't
// pass any), so this is how it gets core 0's objects
AuxCoreObjects const *aux_objects;

enum class AuxState { NotStarted, Started, Ready };
std::atomic<AuxState> aux_state = AuxState::NotStarted;

// TODO: Move to mdrivlib
// CPUECTLR_EL1.SMPEN: the core takes part in the cluster's cache coherency
bool smp_enabled() {
	uint64_t cpuectlr;
	asm volatile("mrs %0, S3_1_C15_C2_1" : "=r"(cpuectlr));
	return cpuectlr & (1 << 6);
}

// The display's interrupt goes to the core that initializes it, so this must run on core 1
void start_display() {
	static mdrivlib::DsiScreen screen{ScreenConf};
	auto &framebuffer = StaticBuffers::framebuffer;
	framebuffer.fill(0xFF000000);
	screen.clean_framebuffer_cache(framebuffer.data());
	if (auto err = screen.init(framebuffer.data()); err != mdrivlib::DsiScreen::Error::None)
		printf("Display init FAILED (error %u)\n", unsigned(err));
}

void run_aux_core(AuxCoreObjects const &objects) {
	start_display();

	LvglDisplay lvgl_display;
	lvgl_display.init(StaticBuffers::framebuffer, StaticBuffers::lvgl_draw_buffer);

	// The RamDisk holds the assets and plugin files. It's big, so it's on the heap rather than in
	// .bss (which is cleared at startup)
	RamDiskOps ramdisk_ops{*new RamDrive};
	FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	// libc file access (fopen, etc), used by modules for their assets
	Filesystem::init(ramdisk);

	PluginManager plugin_manager{objects.file_storage, ramdisk};
	Ui ui{lvgl_display,
		  StaticBuffers::sync_params,
		  objects.patch_playloader,
		  objects.file_storage,
		  objects.open_patch_manager,
		  objects.patch_mod_queue,
		  plugin_manager,
		  ramdisk};

	// USB, on the M33 (as on MP1): the GUI reads the connection status it publishes, and we tell it
	// the USB settings that aren't the defaults
	usb_status_block = &StaticBuffers::usb_connection_status;

	if (auto role = ui.get_settings().usb_role_mode; role != UsbRoleMode::Auto) {
		while (!DeviceSettingsProxy::send_role_mode(role))
			;
	}
	if (auto mode = ui.get_settings().usb_device_mode; mode != UsbDeviceMode::MidiConsole) {
		while (!DeviceSettingsProxy::send_device_mode(mode))
			;
	}

	PluginAppInterface::Internal plugin_internal{ui.get_settings(), objects.open_patch_manager, ui.get_notify_queue()};
	PluginAppInterface plugin_interface{plugin_internal};
	plugin_interface.register_interface();

	// Unpacks the assets into the RamDisk, and registers the built-in modules' info
	AssetFS asset_fs{0};
	InternalPluginManager internal_plugin_manager{ramdisk, asset_fs};

	// Registers the SGI handlers. They must be enabled from this core (the GIC banks SGIs per core).
	// Must be before any patch is loaded or audio starts.
	AuxPlayer aux_player{objects.patch_player, ui};

	ui.preload_plugins(plugin_manager);

	ui.start();
	printf("GUI started. Navigate with the control encoder and Back button, or the console: arrows (or a/d) "
		   "turn, Enter clicks, Backspace is Back\n");

	// The developer drive (Developer Mode), as on MP1
	DevDrive dev_drive;
	DevDriveService dev_drive_service{
		dev_drive,
		plugin_manager,
		objects.patch_playloader,
		ui.get_notify_queue(),
		StaticBuffers::dev_drive_block,
		[&ui] { ui.release_plugin_objects(); },
		[&ui](std::span<char> file_data, std::string_view name) { return ui.play_patch_file(file_data, name); }};

	// Core 0 starts the audio
	aux_state.store(AuxState::Ready, std::memory_order_release);

	while (true) {
		ui.update();
		dev_drive_service.process(ui.get_settings().developer.enabled);
	}
}
} // namespace

bool start_aux_core(AuxCoreObjects const &objects) {
	if (!smp_enabled())
		printf("A35 core 0: SMPEN is not set, the cores' caches are not coherent!\n");

	aux_objects = &objects;

	if (auto err = mdrivlib::SecondaryCore::start(aux_core_startup); err != 0) {
		printf("A35 core 1: failed to start (%d)\n", err);
		return false;
	}

	for (auto start = HAL_GetTick(); aux_state.load(std::memory_order_acquire) == AuxState::NotStarted;) {
		if (HAL_GetTick() - start > 100) {
			printf("A35 core 1: did not start!\n");
			return false;
		}
	}

	// Preloading plugins can take a while
	while (aux_state.load(std::memory_order_acquire) != AuxState::Ready)
		;

	return true;
}

} // namespace MetaModule

// Called by aux_core_startup on core 1, after it enables its MMU, caches and GIC interface
extern "C" void aux_main() {
	using namespace MetaModule;

	// Like core 0's
	if (A35Console::core0_buffered())
		UartLog::use_buffer(&StaticBuffers::console_buffers[1]);

	// Core 0 is waiting for us to start, so it's not printing
	printf("A35 core 1: started%s\n", smp_enabled() ? "" : ", but SMPEN is not set!");

	aux_state.store(AuxState::Started, std::memory_order_release);

	run_aux_core(*aux_objects);
}
