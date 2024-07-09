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

	unsigned max_open_patches = 20;
};

} // namespace MetaModule
