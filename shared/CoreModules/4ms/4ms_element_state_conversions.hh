#pragma once

#include "4ms_elements.hh"
#include <cmath>


namespace MetaModule::StateConversion
{

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

}
