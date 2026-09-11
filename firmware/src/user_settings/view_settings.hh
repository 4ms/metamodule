#pragma once
#include <array>
#include <cstddef>
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
	// Height in px of a module faceplate in PatchView (240 = full screen height)
	constexpr static std::array<unsigned, 5> ZoomLevels = {120, 150, 180, 210, 240};
	constexpr static unsigned DefaultZoomLevel = 180;
	unsigned view_height_px = DefaultZoomLevel;

	// Index into ZoomLevels of the level closest to the given height
	constexpr static size_t zoom_level_index(unsigned height_px) {
		size_t closest = 0;
		unsigned closest_dist = ~0u;

		for (size_t i = 0; i < ZoomLevels.size(); i++) {
			auto dist = ZoomLevels[i] > height_px ? ZoomLevels[i] - height_px : height_px - ZoomLevels[i];
			if (dist < closest_dist) {
				closest_dist = dist;
				closest = i;
			}
		}
		return closest;
	}

	constexpr static unsigned nearest_zoom_level(unsigned height_px) {
		return ZoomLevels[zoom_level_index(height_px)];
	}
	bool changed = true; //???unused but keep for backward compat
	bool show_graphic_screens = true;

	// Status bar:
	bool show_samplerate = true;
	bool float_loadmeter = false;
	bool show_knobset_name = false;

	// Show aliases on element roller:
	bool show_jack_aliases = false;
	bool show_knob_aliases = false;

	bool nav_wrapping = false;

	constexpr static std::array<unsigned, 6> ThrottleAmounts = {32, 16, 8, 4, 2, 1};
	unsigned graphic_screen_throttle = 1;
};

} // namespace MetaModule
