// MetaModule MP2 ("pro") A35 firmware.
//
// Boot path (all from mdrivlib target/stm32mp2_ca35): TF-A BL2 loads this image
// at 0x88000040 in EL3 secure -> boot/startup_ca35.s (stack, .bss, vectors, FPU,
// MMU+caches via system/mmu_ca35.cc, GIC init) -> system_init() (system_init.cc:
// I/O supplies, audio PLL, kernel clocks) -> main().
//
// main() starts the Cortex-M33, which runs patch storage (SD card, NOR flash), then the display
// and MP1's GUI (PageManager and its pages), which reaches patch storage with FileStorageProxy.
// Not yet ported: audio (a stand-in answers the patch loader, see audio_stand_in.hh), controls
// (the serial console navigates the GUI, see console_keys.hh), plugins, USB, WiFi, the second
// A35 core.

#include "audio_stand_in.hh"
#include "conf/board_codec_conf.hh"
#include "conf/hsem_conf.hh"
#include "conf/screen_buffer_conf.hh"
#include "conf/screen_conf.hh"
#include "console.hh"
#include "core_intercom/shared_index.hh"
#include "drivers/cache.hh"
#include "drivers/copro_control.hh"
#include "drivers/hsem.hh"
#include "drivers/ipcc.hh"
#include "drivers/risaf.hh"
#include "dynload/plugin_manager.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "git_version.h"
#include "internal_interface/plugin_app_if_internal.hh"
#include "internal_interface/plugin_app_interface.hh"
#include "internal_plugin_manager.hh"
#include "lvgl.h"
#include "lvgl_display.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "ui.hh"
#include <array>
#include <cstdio>

extern "C" const uint8_t m33_firmware[];	 // m33_firmware.S
extern "C" const uint8_t m33_firmware_end[]; // m33_firmware.S

namespace
{
using namespace MetaModule;

// Display memory
__attribute__((section(".framebuffers"))) alignas(4096) std::array<uint32_t, 720 * 1280> framebuffer;
// Partial render buffer: 1/4 of the GUI, same as MP1
std::array<lv_color_t, ScreenBufferConf::viewWidth * ScreenBufferConf::viewHeight / 4> lvgl_draw_buffer;

// Shared with the M33 (shared_index.hh). The M33 reads files into raw_patch_data, and writes the
// patch list and dir entries into storage_list_buffer serialized (see dir_list_serial.hh).
__attribute__((section(".sharedmem"))) IntercoreStorageMessage storage_message;
__attribute__((section(".sharedmem"))) std::array<char, 1024 * 1024> raw_patch_data;
__attribute__((section(".sharedmem"))) std::array<char, 256 * 1024> storage_list_buffer;

// Audio: silent for now (see audio_stand_in.hh)
constexpr uint32_t AudioBlockSize = 256;
alignas(64) std::array<int32_t, 2 * AudioBlockSize * StreamConf::Audio::NumOutChans> audio_out{};
alignas(64) std::array<int32_t, 2 * AudioBlockSize * StreamConf::Audio::NumInChans> audio_in{};

void start_m33() {
	// Park the M33 before (re)initializing the peripherals it uses
	mdrivlib::CoproController::reset();
	mdrivlib::HWSemaphoreGlobalBase::init_peripheral();
	mdrivlib::IPCC_<1>::init_peripheral();
	A35Console::use_hsem_lock();

	// Shared memory: open it to the M33 in the DDR firewall, create the shared objects in
	// .sharedmem, and publish pointers to them in the index the M33 reads
	using namespace mdrivlib::RISAF;
	constexpr unsigned SharedMemRegionIndex = 10;
	if (!add_ddr_region(SharedMemRegionIndex,
						SHAREDMEM_ADDR,
						SHAREDMEM_ADDR + SHAREDMEM_SIZE - 1,
						CID_A35 | CID_M33,
						CID_A35 | CID_M33,
						true))
		printf("Shared memory: RISAF4 is locked, can't open it to the M33!\n");

	storage_message = {};
	auto &index = shared_index();
	index.storage_message = &storage_message;
	index.magic = SharedIndex::ValidMagic;

	if constexpr (M33_LOAD_ADDR >= mdrivlib::RISAF::DDRBase) {
		// TF-A's DDR region only allows CID0/CID1: open the M33's region to it (CID2)
		constexpr unsigned M33RegionIndex = 11;
		if (!add_ddr_region(M33RegionIndex,
							M33_LOAD_ADDR,
							M33_LOAD_ADDR + M33_REGION_SIZE - 1,
							CID_A35 | CID_M33,
							CID_A35 | CID_M33,
							true))
			printf("M33: RISAF4 is locked, can't open DDR to the M33!\n");
	}

	auto size = size_t(m33_firmware_end - m33_firmware);
	printf("M33: loading %zu bytes to 0x%08x and starting\n", size, unsigned(M33_LOAD_ADDR));
	mdrivlib::CoproController::load_and_start({m33_firmware, size}, M33_LOAD_ADDR);

	using mdrivlib::CoproController;
	auto reset_us = CoproController::wait_for_breadcrumb(M33_LOAD_ADDR, 0, CoproController::BreadcrumbResetRan, 100);
	auto main_us = CoproController::wait_for_breadcrumb(M33_LOAD_ADDR, 1, CoproController::BreadcrumbReachedMain, 1000);
	if (reset_us < 0)
		printf("M33: reset handler DID NOT RUN\n");
	else if (main_us < 0)
		printf("M33: reset handler ran, main() NOT REACHED\n");
}

void start_display() {
	static mdrivlib::DsiScreen screen{ScreenConf};
	framebuffer.fill(0xFF000000);
	screen.clean_framebuffer_cache(framebuffer.data());
	if (auto err = screen.init(framebuffer.data()); err != mdrivlib::DsiScreen::Error::None)
		printf("Display init FAILED (error %u)\n", unsigned(err));
}

void start_audio(AudioStandIn &audio) {
	auto &codec = Hardware::codec;
	if (codec.init() != CodecT::CODEC_NO_ERR) {
		printf("Codec init FAILED: patches can't be loaded (nothing answers the patch loader)\n");
		return;
	}

	mdrivlib::SystemCache::clean_dcache_by_range(audio_out.data(), sizeof audio_out);
	codec.set_tx_buffer(std::span<int32_t>{audio_out}, AudioBlockSize);
	codec.set_rx_buffer(std::span<int32_t>{audio_in}, AudioBlockSize);
	codec.set_callbacks([&audio] { audio.process(); }, [&audio] { audio.process(); });
	codec.start();
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

	start_m33();
	start_display();

	static LvglDisplay lvgl_display;
	lvgl_display.init(framebuffer, lvgl_draw_buffer);

	// Patch storage, on the M33
	static FileStorageComm storage_comm{storage_message};
	static PatchDirList patch_dir_list;
	static FileStorageProxy file_storage{raw_patch_data, storage_comm, patch_dir_list, storage_list_buffer};

	static PatchPlayer patch_player;
	static OpenPatchManager open_patches_manager;
	static PatchPlayLoader patch_playloader{file_storage, open_patches_manager, patch_player};
	static PatchModQueue patch_mod_queue;

	static AudioStandIn audio{patch_playloader};
	start_audio(audio);

	// The RamDisk holds the assets and plugin files. It's big, so it's on the heap rather than in
	// .bss (which is cleared at startup)
	static RamDiskOps ramdisk_ops{*new RamDrive};
	static FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};

	static PluginManager plugin_manager{file_storage, ramdisk};
	static Ui ui{lvgl_display, patch_playloader, file_storage, open_patches_manager, patch_mod_queue, plugin_manager, ramdisk};

	static PluginAppInterface::Internal plugin_internal{ui.get_settings(), open_patches_manager, ui.get_notify_queue()};
	static PluginAppInterface plugin_interface{plugin_internal};
	plugin_interface.register_interface();

	// Unpacks the assets into the RamDisk, and registers the built-in modules' info
	static AssetFS asset_fs{0};
	static InternalPluginManager internal_plugin_manager{ramdisk, asset_fs};

	ui.start();
	printf("GUI started. Navigate with the console: arrows (or a/d) turn, Enter clicks, Backspace is Back\n");

	while (true) {
		ui.update();
	}
}
