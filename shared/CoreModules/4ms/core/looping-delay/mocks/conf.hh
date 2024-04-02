#pragma once

#include <cstdint>

namespace Brain
{
constexpr inline int16_t MinPotChange = 10;
constexpr inline int16_t MinCVChange = 10;

constexpr inline float AudioGain = 1.216f; // gain to apply to acheive 0dB out:in

struct CVAdcConf
{
    static constexpr uint16_t uni_min_value = 65;
	static constexpr uint16_t bi_min_value = 20;
};
}