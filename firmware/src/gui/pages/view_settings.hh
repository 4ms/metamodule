#pragma once
#include <cstdint>

namespace MetaModule
{

struct MapRingStyle {
	enum class Mode {
		HideAlways,
		CurModule,
		CurModuleIfPlaying,
		ShowAllIfPlaying,
		ShowAll,
	} mode{Mode::CurModuleIfPlaying};
	uint8_t opa = 128;
};

struct ModuleDisplaySettings {
	bool map_ring_flash_active = true;
	bool scroll_to_active_param = false;
	MapRingStyle param_style = {.mode = MapRingStyle::Mode::CurModuleIfPlaying, .opa = 128};
	MapRingStyle paneljack_style = {.mode = MapRingStyle::Mode::CurModuleIfPlaying, .opa = 128};
	MapRingStyle cable_style = {.mode = MapRingStyle::Mode::ShowAll, .opa = 128};
	unsigned view_height_px = 180;
	bool changed = true;
};

struct ViewSettings {
	ModuleDisplaySettings patch_view{};
	ModuleDisplaySettings module_view{};

	enum class SampleRate {
		SR_24K = 24000,
		SR_48K = 48000,
		SR_96K = 96000,
	} sample_rate = SampleRate::SR_48K;

	enum class BlockSize {
		BS_32 = 32,
		BS_64 = 64,
		BS_128 = 128,
		BS_256 = 256,
		BS_512 = 512,
	} block_size = BlockSize::BS_64;
};

} // namespace MetaModule
