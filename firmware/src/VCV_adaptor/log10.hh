#pragma once
#include <gcem.hpp>
#include "util/interp_array.hh"
#include <array>

namespace MetaModule
{

template<unsigned Min, unsigned Max, unsigned Size>
constexpr auto make_log10() {
	InterpArray<float, Size> arr;

	for (unsigned i = 0; i < Size; i++) {
		double x = i * (Max - Min) / Size + Min; //x=[Min..Max)
		arr.data[i] = gcem::log(x) / gcem::log(10);
	}

	return arr;
}

constexpr InterpArray<float, 256> log10_0V_12V{make_log10<0, 12, 256>()};

} // namespace MetaModule
