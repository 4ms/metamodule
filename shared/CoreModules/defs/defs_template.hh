#include "util/static_string.hh"
#include <array>
#include <cstddef>
#include <string>

struct KnobDef {
	uint32_t id; // matches id used in patch files, and in CoreModule::set_param(id, val)

	// Todo: what units? mm?
	float x;
	float y;

	float default_val;
	enum { Small, Medium, Large } knob_type;

	// TODO: should we use these (they're from VCV, I think)
	// float display_base;
	// float display_mult;
	// float display_offset;
	// std::string units;

	std::string_view short_name;
	std::string_view long_name;
	std::string_view description;
};

struct InJackDef {};

struct OutJackDef {};

struct ModuleDefsBase {

	static constexpr std::string_view slug{""};

	// Image
	static constexpr uint32_t width_hp = 0;

	static constexpr std::string_view svg_filename{""};

	// Knobs
	static constexpr uint32_t NumKnobs = 0;
	static constexpr std::array<KnobDef, NumKnobs> Knobs{};

	static constexpr uint32_t NumInJacks = 0;
	static constexpr std::array<KnobDef, NumInJacks> InJacks{};

	static constexpr uint32_t NumOutJacks = 0;
	static constexpr std::array<KnobDef, NumOutJacks> OutJacks{};

	constexpr uint32_t get_width_px() {
		// 240px = 5.059" so 1HP = 0.2" = 9.488px
		return static_cast<uint32_t>((float)width_hp * 9.488f);
	}

	static constexpr uint32_t mm2um(float mm) {
		return static_cast<uint32_t>(1000.f * mm);
	}

	// Need a lookup function somewhere LVGL sees, like:
	// lv_img_dsc_t* get_module_image_from_slug(StaticString<31> slug);
};
