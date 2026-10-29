#pragma once
#include <array>
#include <cstdint>

namespace MetaModule
{

// Controls -> Audio: the clicks (positive = clockwise) of each panel encoder since the last param
// block. Only the pro has panel encoders: with none, it's empty, so it takes no space in MetaParams.
template<unsigned NumEncoders>
struct EncoderClicks {
	std::array<int8_t, NumEncoders> clicks{};
};

template<>
struct EncoderClicks<0> {};

} // namespace MetaModule
