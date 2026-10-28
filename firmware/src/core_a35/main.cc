// MetaModule MP2 ("pro") A35 firmware: core 0, as on MP1 (core_a7/main.cc). It starts everything,
// then plays the audio. Core 1 runs the GUI (aux_core.cc).

// Not yet ported: the other controls, jack sense, MIDI, USB, WiFi.

#include "audio/audio.hh"
#include "aux_core.hh"
#include "calibrate/calibration_data_reader.hh"
#include "console.hh"
#include "copro.hh"
#include "git_version.h"
#include "i2c_scan.hh"
#include "ld.h"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_player.hh"
#include "patch_play/patch_playloader.hh"
#include "static_buffers.hh"
#include <cstdio>

// system/sbrk_ca35.cc
uintptr_t heap_region_start();
size_t heap_region_size();

int main() {
	using namespace MetaModule;

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

#ifndef MP2_TEST_CARRIER
	scan_i2c_buses();
#endif

	// Core 1 runs the GUI and plays part of the patch. This returns once it's ready for the audio.
	static AuxCoreObjects aux_objects{patch_player, patch_playloader, file_storage, open_patches_manager, patch_mod_queue};
	if (!start_aux_core(aux_objects))
		printf("A35 core 1 is not running: no GUI!\n");

	StaticBuffers::sync_params.clear();
	audio.start();

	// Same as MP1's main loop (core_a7/main.cc)
	while (true) {
		audio.handle_overruns();

		if (audio.get_audio_errors() > 0) {
			pr_err("Audio error\n");
			audio.start();
		}
	}
}
