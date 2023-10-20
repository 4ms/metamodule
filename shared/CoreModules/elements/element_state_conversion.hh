#pragma once
#include "CoreModules/elements/elements.hh"
#include <array>
#include <concepts>
#include <type_traits>
#include <algorithm>

namespace MetaModule::StateConversion
{

// Here we provide a non-ambigous set of fallbacks
// For all element types that need a custom behaviour, a specialization for that particular type needs to be created
// Since overload resolution does not work for template parameters, just inheriting from a specialized type (and expecting the method to fall back to the parent's) will not work

//TODO: This generates a compiler error for gcc < 12.3
template<typename T>
constexpr typename T::State_t convertState(const T &, float val) requires(std::is_same_v<typename T::State_t, void>)
{
	// This should never by reached
	// All types that inherit from BaseElement but do not define their own State_t will be caught
}

// to be defined for all kinds of elements
template<typename T>
constexpr MomentaryButton::State_t convertState(const T &, float val) requires(std::derived_from<T, MomentaryButton>)
{
	return val > 0 ? MomentaryButton::State_t::PRESSED : MomentaryButton::State_t::RELEASED;
}

template<typename T>
constexpr LatchingButton::State_t convertState(const T &, float val) requires(std::derived_from<T, LatchingButton>)
{
	return val > 0 ? LatchingButton::State_t::DOWN : LatchingButton::State_t::UP;
}

template<typename T>
constexpr Toggle2pos::State_t convertState(const T &, float val) requires(std::derived_from<T, Toggle2pos>)
{
	if (val < 0.5f) {
		return Toggle2pos::State_t::DOWN;
	} else {
		return Toggle2pos::State_t::UP;
	}
}

template<typename T>
constexpr Toggle3pos::State_t convertState(const T &, float val) requires(std::derived_from<T, Toggle3pos>)
{
	if (val < 0.25f) {
		return Toggle3pos::State_t::DOWN;
	} else if (val < 0.75f) {
		return Toggle3pos::State_t::CENTER;
	} else {
		return Toggle3pos::State_t::UP;
	}
}

template<typename T>
constexpr Pot::State_t convertState(const T &, float val) requires(std::derived_from<T, Pot>)
{
	return val;
}

//
// LEDs
//

// Fallback for single LED elements
template<typename T>
constexpr std::array<float, T::NumLights> convertLED(const T &, float value) requires(T::NumLights == 1)
{
	return {value};
}

// Fallback for single LED elements with explicit type conversion
template<typename T>
constexpr std::array<float, T::NumLights> convertLED(const T &, bool value) requires(T::NumLights == 1)
{
	return {value ? 1.0f : 0.0f};
}

template<typename T>
constexpr std::array<float, T::NumLights> convertLED(const T &, BipolarColor_t color)
	requires(std::derived_from<T, DualLight>)
{
	return {-std::min(color.value, 0.0f), std::max(color.value, 0.f)};
}

template<typename T>
constexpr std::array<float, T::NumLights> convertLED(const T &, FullColor_t color)
	requires(std::derived_from<T, RgbLed>)
{
	//fades from green to red to blue
	float green = 1.f - 2.f * color.value;
	float blue = -green;

	green = std::clamp(green, 0.f, 1.f);
	blue = std::clamp(blue, 0.f, 1.f);

	float red = 1.f - (green + blue);
	red = std::clamp(red, 0.f, 1.f);

	return {red, green, blue};
}

} // namespace MetaModule::StateConversion
