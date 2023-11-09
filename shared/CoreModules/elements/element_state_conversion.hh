#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/elements.hh"
#include <array>
#include <cmath>
#include <concepts>
#include <type_traits>

namespace MetaModule::StateConversion
{

//TODO: This generates a compiler error for gcc < 12.3
template<typename T>
constexpr typename T::State_t convertState(const T &, float val) requires(std::is_same_v<typename T::State_t, void>)
{
	// This should never by reached
	// All types that inherit from BaseElement but do not define their own State_t will be caught
}

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
constexpr SlideSwitch::State_t convertState(const T &element, float val) requires(std::derived_from<T, SlideSwitch>)
{
	//maps 0..1 -> 1..N
	return SlideSwitch::State_t(1 + std::round(val * (float)(element.num_pos - 1)));
}

template<typename T>
constexpr FlipSwitch::State_t convertState(const T &element, float val)
	requires(std::derived_from<T, FlipSwitch> && !std::same_as<T, Toggle2pos> && !std::same_as<T, Toggle3pos>)
{
	//maps 0..1 -> 0..(num_pos-1)
	return FlipSwitch::State_t(std::round(val * (float)(element.num_pos - 1)));
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

} // namespace MetaModule::StateConversion
