#include "../shared/gcem/include/gcem.hpp"
#include "CoreModules/4ms/core/helpers/mapping.h"
#include "doctest.h"
#include <iostream>

//Copy-pasted from ENVVCACore.cc
struct VoltageToFreqTableRange {
	static constexpr float min = -0.1f;
	static constexpr float max = 0.5f;
};
constinit auto VoltageToFrequencyTable =
	Mapping::LookupTable_t<50>::generate<VoltageToFreqTableRange>([](auto voltage) {
		// two points in the V->f curve
		constexpr double V_1 = 0.4;
		constexpr double f_1 = 0.09;
		constexpr double V_2 = 0.06;
		constexpr double f_2 = 1000.0;

		// std::pow is not required to be constexpr by the standard
		// so this might not work in clang
		constexpr double ArgScalingFactor = 10.0;
		constexpr double arg = gcem::log2(f_1 / f_2) / (V_1 - V_2);
		constexpr double b = gcem::pow(2.0f, arg / ArgScalingFactor);
		constexpr double a = f_1 / gcem::pow(gcem::pow(2.0, arg), V_1);

		// interpolate
		auto frequency = float(gcem::pow(b, double(voltage) * ArgScalingFactor) * a);

		return frequency;
	});

TEST_CASE("check mapping table") {
	constexpr unsigned LEN = 50;
	constexpr float min = -0.1f;
	constexpr float max = 0.5f;

	// generate check data with original table:
	// for (unsigned i = 0; i < LEN; i++){
	// auto x = min + i * (max - min) / float(LEN-1);
	// std::cout << "\t{" << x << ", " << VoltageToFrequencyTable.lookup(x) << "},\n";
	// }
	constexpr std::pair<float, float> checkdata[] = {
		{-0.1, 80146.8},		{-0.0877551, 57303.4}, {-0.0755102, 40970.8}, {-0.0632653, 29293.4},
		{-0.0510204, 20944.2},	{-0.0387755, 14974.7}, {-0.0265306, 10706.6}, {-0.0142857, 7655.03},
		{-0.00204081, 5473.2},	{0.0102041, 3913.23},  {0.022449, 2797.89},	  {0.0346939, 2000.44},
		{0.0469388, 1430.27},	{0.0591837, 1022.62},  {0.0714286, 731.153},  {0.0836735, 522.76},
		{0.0959184, 373.764},	{0.108163, 267.234},   {0.120408, 191.067},	  {0.132653, 136.609},
		{0.144898, 97.673},		{0.157143, 69.8343},   {0.169388, 49.9302},	  {0.181633, 35.6992},
		{0.193878, 25.5242},	{0.206122, 18.2493},   {0.218367, 13.0479},	  {0.230612, 9.32901},
		{0.242857, 6.67007},	{0.255102, 4.76897},   {0.267347, 3.40972},	  {0.279592, 2.43789},
		{0.291837, 1.74304},	{0.304082, 1.24624},   {0.316327, 0.891039},  {0.328571, 0.637076},
		{0.340816, 0.455497},	{0.353061, 0.325672},  {0.365306, 0.232849},  {0.377551, 0.166483},
		{0.389796, 0.119032},	{0.402041, 0.0851056}, {0.414286, 0.0608488}, {0.426531, 0.0435058},
		{0.438776, 0.0311058},	{0.45102, 0.02224},	   {0.463265, 0.0159012}, {0.47551, 0.0113691},
		{0.487755, 0.00812866}, {0.5, 0.00581184},
	};

	// Check data with refactored table:
	for (unsigned i = 0; i < LEN; i++) {
		auto x = min + i * (max - min) / float(LEN - 1);
		auto y = VoltageToFrequencyTable.lookup(x);
		CHECK(y == doctest::Approx(checkdata[i].second));
	}
}
