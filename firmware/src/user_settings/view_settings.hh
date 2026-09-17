#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>

namespace MetaModule
{

// Size of the PatchView module canvas
struct RackSize {
	constexpr static unsigned ViewWidthPx = 308;
	constexpr static unsigned RackWidthStepHP = 4;
	constexpr static unsigned MinRackWidthHP = 28;

	// Max HP is 2 screens wide when fully zoomed out (tiny modules)
	constexpr static unsigned MaxRackWidthHP = 128;
	constexpr static unsigned DefaultRackWidthHP = 40;

	constexpr static unsigned clamp_rack_width(unsigned hp) {
		return hp < MinRackWidthHP ? MinRackWidthHP : hp > MaxRackWidthHP ? MaxRackWidthHP : hp;
	}

	constexpr static unsigned num_rack_width_steps() {
		return (MaxRackWidthHP - MinRackWidthHP) / RackWidthStepHP;
	}

	// HP of step index `step`
	constexpr static unsigned rack_width_for_step(unsigned step) {
		return clamp_rack_width(MinRackWidthHP + step * RackWidthStepHP);
	}

	// Index of the largest step that isn't wider than hp
	constexpr static unsigned rack_width_step(unsigned hp) {
		return (clamp_rack_width(hp) - MinRackWidthHP) / RackWidthStepHP;
	}

	constexpr static unsigned snap_rack_width(unsigned hp) {
		return RackSize::on_hp_step_grid(clamp_rack_width(hp));
	}

	// 1 HP is 5.08mm wide and a 3U faceplate is 128.5mm tall, so pixels-per-HP follows
	// the height the faceplate is drawn at
	constexpr static float px_per_hp(unsigned faceplate_height_px) {
		return 5.08f * (float)faceplate_height_px / 128.5f;
	}

	constexpr static unsigned hp_across_screen(unsigned faceplate_height_px) {
		auto view_width_px = ViewWidthPx;
		return (unsigned)((float)view_width_px / px_per_hp(faceplate_height_px));
	}

	// Rounds a width down onto a grid of `step` HP counting up from `min_hp`
	constexpr static unsigned on_hp_step_grid(unsigned hp) {
		constexpr auto step = RackWidthStepHP;
		constexpr auto min_hp = MinRackWidthHP;
		return hp <= min_hp ? min_hp : min_hp + (hp - min_hp) / step * step;
	}
};

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

	// How taut the cables are drawn: 100 hangs them in a straight line, 0 is maximum droop.
	// The default reproduces the sag cables have always had.
	constexpr static uint8_t MinCableTension = 50;
	constexpr static uint8_t MaxCableTension = 100;
	constexpr static uint8_t DefaultCableTension = 70;
	uint8_t cable_tension = DefaultCableTension;

	constexpr static uint8_t clamp_cable_tension(unsigned tension) {
		return std::clamp<uint8_t>(tension, MinCableTension, MaxCableTension);
	}

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

	bool auto_layout = true;	 // automatically compact layout
	bool auto_rack_width = true; // wrap at screen edge
	unsigned rack_width_hp = RackSize::DefaultRackWidthHP;
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
