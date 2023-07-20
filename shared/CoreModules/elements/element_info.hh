#pragma once
#include "CoreModules/elements/elements.hh"
#include <array>
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct ModuleInfoBase {
	static constexpr std::string_view slug{""};
	static constexpr std::string_view description{""};
	static constexpr std::string_view svg_filename{""};
	static constexpr uint32_t width_hp = 0;
	static constexpr bool uses_center_coords = false;
	static constexpr std::array<Element, 0> Elements{};

	template<size_t DPI = 75>
	static constexpr float to_mm(float px) {
		constexpr float pix_per_inch = DPI;
		constexpr float mm_per_inch = 25.4f;
		float inches = px / pix_per_inch;
		return inches * mm_per_inch;
	}

	static constexpr float to_mm(float px, float DPI) {
		constexpr float mm_per_inch = 25.4f;
		float inches = px / DPI;
		return inches * mm_per_inch;
	}

	// mm: length or position in mm
	// pixels_per_3U: the module height in pixels
	static constexpr float mm_to_px(float mm, uint32_t pixels_per_3U) {
		constexpr float mm_per_3U = 128.5f; //standard Eurorack size
		float pixels_per_mm = pixels_per_3U / mm_per_3U;
		return mm * pixels_per_mm;
	}
};

// Hack to allow us to copy/paste enum list from VCV Module files
#ifndef VCVRACK
#ifndef ENUMS
#define ENUMS(name, count) name, name##_LAST = name + (count)-1
#endif
#endif

} // namespace MetaModule
