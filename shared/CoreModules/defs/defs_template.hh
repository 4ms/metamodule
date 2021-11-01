#include <array>
#include <cstddef>
#include <static_string.hh>
#include <string>

struct KnobDef {
	uint32_t id; // matches id used in patch files, and in CoreModule::set_param(id, val)

	// Todo: what units? 72dpi points from top-left? Or 75dpi? Or mm?
	uint32_t x;
	uint32_t y;

	float default_val;

	// TODO: should we use these (they're from VCV, I think)
	float display_base;
	float display_mult;
	float display_offset;
	std::string units;

	std::string_view short_name;
	std::string_view long_name;
	std::string_view description;
};

struct ModuleDefsBase {

	// const lv_img_dsc_t *img_src;
	// TODO: don't depend on LVGL, instead we need another way to address this asset.
	// We could have a lookup function like:
	// lv_img_dsc_t* get_module_image_by_index(uint32_t module_index);
	// This would only be needed by the same UI code that uses LVGL already
	// static constexpr uint32_t compiled_image_index = -1;
	// static constexpr StaticString<31> slug{empt};
	static constexpr std::string_view slug{""};

	// Image
	static constexpr uint32_t width_hp = 0;
	constexpr uint32_t get_width_px() {
		// 240px = 5.059" so 1HP = 0.2" = 9.488px
		return static_cast<uint32_t>((float)width_hp * 9.488f);
	}

	static constexpr std::string_view svg_filename = "";

	// Knobs
	static constexpr uint32_t NumKnobs = 0;
	std::array<KnobDef, NumKnobs> Knobs;
};
