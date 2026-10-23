// MetaModule MP2 ("pro") A35 firmware.

// Not yet ported: the other controls, jack sense, MIDI, USB, WiFi.

#include "audio/audio.hh"
#include "aux_core.hh"
#include "calibrate/calibration_data_reader.hh"
#include "conf/hsem_conf.hh"
#include "conf/screen_conf.hh"
#include "console.hh"
#include "copro.hh"
#include "core_a7/dev_drive_service.hh"
#include "core_a7/device_settings_proxy.hh"
#include "drivers/cache.hh"
#include "dynload/plugin_manager.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/syscall/filesystem.hh"
#include "git_version.h"
#include "internal_interface/plugin_app_if_internal.hh"
#include "internal_interface/plugin_app_interface.hh"
#include "internal_plugin_manager.hh"
#include "ld.h"
#include "lvgl.h"
#include "lvgl_display.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "static_buffers.hh"
#include "ui.hh"
#include "usb/usb_status_reader.hh"
#include <array>
#include <cstdio>

// system/sbrk_ca35.cc
uintptr_t heap_region_start();
size_t heap_region_size();

namespace
{
using namespace MetaModule;

// TODO: Move to aux_core_main
void start_display() {
	static mdrivlib::DsiScreen screen{ScreenConf};
	auto &framebuffer = StaticBuffers::framebuffer;
	framebuffer.fill(0xFF000000);
	screen.clean_framebuffer_cache(framebuffer.data());
	if (auto err = screen.init(framebuffer.data()); err != mdrivlib::DsiScreen::Error::None)
		printf("Display init FAILED (error %u)\n", unsigned(err));
}

} // namespace

int main() {
	A35Console::init();
	printf("\n\nMetaModule Pro\n");
	printf("Build: %s (%s)\n", GIT_HASH.data(), GIT_COMMIT_TIME.data());
	printf("Version: %s\n", GIT_FIRMWARE_VERSION_TAG.data());
	// Line-buffered, so lines from the two cores don't interleave
	setvbuf(stdout, nullptr, _IOLBF, 256);

	HAL_Init();

	StaticBuffers::init();

	if (heap_region_start() != A35_HEAP)
		printf("Heap: RISAF4 is locked, can't open DDR at 0x%08x to the A35: using the %zu MB left in RAM\n",
			   unsigned(A35_HEAP),
			   heap_region_size() / (1024 * 1024));

	// Once the M33 is running, it owns the NOR flash (patch storage), so read the calibration first
	auto cal = CalibrationDataReader::read_calibration_or_defaults(FlashLoader{}, CalDataFlashOffset);

	start_m33();
	start_display();

	static LvglDisplay lvgl_display;
	lvgl_display.init(StaticBuffers::framebuffer, StaticBuffers::lvgl_draw_buffer);

	// Patch storage, on the M33
	static FileStorageComm storage_comm{StaticBuffers::storage_message};
	static PatchDirList patch_dir_list;
	static FileStorageProxy file_storage{
		StaticBuffers::raw_patch_data, storage_comm, patch_dir_list, StaticBuffers::storage_list_buffer};

	static PatchPlayer patch_player;
	static OpenPatchManager open_patches_manager;
	static PatchPlayLoader patch_playloader{file_storage, open_patches_manager, patch_player};
	static PatchModQueue patch_mod_queue;

	// Initializes the codec. The audio starts once the GUI is up.
	static AudioStream audio{patch_player,
							 StaticBuffers::audio_in_dma_block,
							 StaticBuffers::audio_out_dma_block,
							 StaticBuffers::sync_params,
							 patch_playloader,
							 StaticBuffers::param_blocks,
							 patch_mod_queue};
	audio.set_calibration(cal);

	// The RamDisk holds the assets and plugin files. It's big, so it's on the heap rather than in
	// .bss (which is cleared at startup)
	static RamDiskOps ramdisk_ops{*new RamDrive};
	static FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	// libc file access (fopen, etc), used by modules for their assets
	Filesystem::init(ramdisk);

	static PluginManager plugin_manager{file_storage, ramdisk};
	static Ui ui{lvgl_display,
				 StaticBuffers::sync_params,
				 patch_playloader,
				 file_storage,
				 open_patches_manager,
				 patch_mod_queue,
				 plugin_manager,
				 ramdisk};

	// USB, on the M33 (as on MP1, core_a7/aux_core_main.cc): the GUI reads the connection status it
	// publishes, and we tell it the USB settings that aren't the defaults
	usb_status_block = &StaticBuffers::usb_connection_status;

	if (auto role = ui.get_settings().usb_role_mode; role != UsbRoleMode::Auto) {
		while (!DeviceSettingsProxy::send_role_mode(role))
			;
	}
	if (auto mode = ui.get_settings().usb_device_mode; mode != UsbDeviceMode::MidiConsole) {
		while (!DeviceSettingsProxy::send_device_mode(mode))
			;
	}

	// Core 1 plays part of the patch, so it must be running before a patch loads
	start_aux_core(patch_player, ui);

	static PluginAppInterface::Internal plugin_internal{ui.get_settings(), open_patches_manager, ui.get_notify_queue()};
	static PluginAppInterface plugin_interface{plugin_internal};
	plugin_interface.register_interface();

	// Unpacks the assets into the RamDisk, and registers the built-in modules' info
	static AssetFS asset_fs{0};
	static InternalPluginManager internal_plugin_manager{ramdisk, asset_fs};

	ui.preload_plugins(plugin_manager);

	ui.start();
	printf("GUI started. Navigate with the control encoder and Back button, or the console: arrows (or a/d) "
		   "turn, Enter clicks, Backspace is Back\n");

	StaticBuffers::sync_params.clear();
	audio.start();

	// The developer drive (Developer Mode): MP1 runs this on core 1 (core_a7/aux_core_main.cc).
	static DevDrive dev_drive;
	static DevDriveService dev_drive_service{
		dev_drive,
		plugin_manager,
		patch_playloader,
		ui.get_notify_queue(),
		StaticBuffers::dev_drive_block,
		[] { ui.release_plugin_objects(); },
		[](std::span<char> file_data, std::string_view name) { return ui.play_patch_file(file_data, name); }};

	while (true) {
		ui.update();
		dev_drive_service.process(ui.get_settings().developer.enabled);

		// Same as MP1's main loop (core_a7/main.cc)
		audio.handle_overruns();

		if (audio.get_audio_errors() > 0) {
			pr_err("Audio error\n");
			audio.start();
		}
	}
}
