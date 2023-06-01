#pragma once
#include "CoreModules/elements.hh"
#include "util/base_concepts.hh"
#include "util/static_string.hh"
#include <array>
#include <span>
#include <string_view>

struct KnobDef {
	uint32_t id;
	float x_mm;
	float y_mm;
	std::string_view short_name;
	std::string_view long_name;
	float default_val;
	enum Style { Small, Medium, Large, Slider25mm } knob_style;
	enum { Round, Vertical, Horizontal } orientation; // for sliders
};

struct InJackDef {
	uint32_t id;
	float x_mm;
	float y_mm;
	std::string_view short_name;
	std::string_view long_name;
	float unpatched_val;
	enum { Analog, Gate } signal_type;
};

struct OutJackDef {
	uint32_t id;
	float x_mm;
	float y_mm;
	std::string_view short_name;
	std::string_view long_name;
	enum { Analog, Gate } signal_type;
};

struct SwitchDef {
	uint32_t id;
	float x_mm;
	float y_mm;
	std::string_view short_name;
	std::string_view long_name;
	enum Style { MomentaryButton, LatchingButton, Toggle2pos, Toggle3pos, Encoder } switch_type;
	enum { Round, Vertical, Horizontal } orientation;
	enum { None, Small, Medium, Large } encoder_knob_style;
};

struct LedDef {
	uint32_t id;
	float x_mm;
	float y_mm;
	enum { Red, Blue, White, Green, RedWhite, RedBlue, BlueGreen, RedGreenBlue } led_color;
};

struct AltParamDef {
	uint32_t id;
	std::string_view short_name;
	float min_val;
	float max_val;
	float default_val;
	uint32_t attached_to_param_id;
	enum class AttachedTo { Knob, Switch } attached_to;
	enum class Range { Continuous, Integer } control_type;
};

// Base structure for a module's ModuleInfo
// A module's ModuleInfo class should derive from this class
// and override all non-empty data members with the actual values of the module
struct ModuleInfoBase {
	static constexpr std::string_view slug{""};

	static constexpr uint32_t width_hp = 0;
	static constexpr std::string_view svg_filename{""};

	static constexpr std::array<KnobDef, 0> Knobs{};
	static constexpr std::array<InJackDef, 0> InJacks{};
	static constexpr std::array<OutJackDef, 0> OutJacks{};
	static constexpr std::array<SwitchDef, 0> Switches{};
	static constexpr std::array<LedDef, 0> Leds{};
	static constexpr std::array<AltParamDef, 0> AltParams{};

	// Converts HP to px for a 240x320px screen
	// TODO: make dimensions explicit
	static constexpr uint32_t get_width_px() {
		// 240px = 5.059" so 1HP = 0.2" = 9.488px
		return static_cast<uint32_t>((float)width_hp * 9.488f);
	}

	// Converts px to mm, at a given DPI (template argument)
	// Useful with 72-dpi SVG files, since VCV Rack's px2mm() assumes 75dpi
	template<size_t DPI>
	static constexpr float px_to_mm(float px) {
		constexpr float pix_per_inch = DPI;
		constexpr float mm_per_inch = 25.4f;
		float inches = px / pix_per_inch;
		return inches * mm_per_inch;
	}

	// Converts mm to pixels, when the screen height (in pixels) is known,
	// assuming 3U = screen height
	template<size_t PixelsPer3U>
	static constexpr float mm_to_px(float mm) {
		constexpr float MMper3U = 128.5f;
		constexpr float pixels_per_mm = PixelsPer3U / MMper3U;
		return mm * pixels_per_mm;
	}
};

// A View into a type derived from ModuleInfoBase
// E.g. a view of a specific module's knob/jack/etc information
struct ModuleInfoView {
	// std::string_view slug{""}; //TODO: we really dont need this right?
	uint32_t width_hp = 0;
	std::string_view svg_filename{""};
	std::string_view module_name{""};
	std::span<const KnobDef> Knobs;
	std::span<const InJackDef> InJacks;
	std::span<const OutJackDef> OutJacks;
	std::span<const SwitchDef> Switches;
	std::span<const LedDef> Leds;
	std::span<const AltParamDef> AltParams;

	template<Derived<ModuleInfoBase> T>
	static constexpr ModuleInfoView makeView() {
		return {
			.width_hp = T::width_hp,
			.svg_filename = T::svg_filename,
			.Knobs = T::Knobs,
			.InJacks = T::InJacks,
			.OutJacks = T::OutJacks,
			.Switches = T::Switches,
			.Leds = T::Leds,
			.AltParams = T::AltParams,
		};
	}
};

namespace MetaModule
{
struct ElementInfoView {
	uint32_t width_hp = 0;
	std::string_view svg_filename{""};
	std::string_view module_name{""};
	std::span<const Element> Knobs;
	std::span<const Element> InJacks;
	std::span<const Element> OutJacks;
	std::span<const Element> Switches;
	std::span<const Element> Leds;
	std::span<const Element> AltParams;

	template<Derived<ElementInfoBase> T>
	static constexpr ElementInfoView makeView() {
		return {
			.width_hp = T::width_hp,
			.svg_filename = T::svg_filename,
			.Knobs = T::Knobs,
			.InJacks = T::InJacks,
			.OutJacks = T::OutJacks,
			.Switches = T::Switches,
			.Leds = T::Leds,
			.AltParams = T::AltParams,
		};
	}
};
} // namespace MetaModule
