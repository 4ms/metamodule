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
	} mode;
	uint8_t opa = 128;
};

struct ViewSettings {
	bool map_ring_flash_active = true;
	bool scroll_to_active_param = false;
	bool show_jack_maps = false;
	MapRingStyle map_ring_style = {.mode = MapRingStyle::Mode::CurModuleIfPlaying, .opa = 128};
	MapRingStyle cable_style = {.mode = MapRingStyle::Mode::ShowAll, .opa = 128};
	bool changed = true;
};

} // namespace MetaModule
