#pragma once
#include <array>
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
	bool changed = true; //???unused but keep for backward compat
	bool show_graphic_screens = true;

	constexpr static std::array<unsigned, 6> ThrottleAmounts = {32, 16, 8, 4, 2, 1};
	unsigned graphic_screen_throttle = 1;
};

} // namespace MetaModule
