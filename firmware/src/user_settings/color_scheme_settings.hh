#pragma once

#include <cstdint>

// Forward-declare so this header doesn't pull lvgl.h transitively (color_scheme.hh
// includes lvgl.h for its mc() helper). Settings code shouldn't depend on lvgl.
namespace MetaModule::Scheme
{
unsigned count();
}

namespace MetaModule
{

struct ColorSchemeSettings {
	static constexpr uint8_t DefaultSchemeId = 0;

	uint8_t scheme_id = DefaultSchemeId;

	void make_valid() {
		if (scheme_id >= Scheme::count())
			scheme_id = DefaultSchemeId;
	}
};

} // namespace MetaModule
