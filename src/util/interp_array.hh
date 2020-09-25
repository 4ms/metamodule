#pragma once
#include <cstddef>
#include <array>

template<typename T, unsigned int Size>
struct InterpArray : public std::array<T, Size> {
	
	constexpr float interp_by_index(const float index) const
	{
		unsigned int idx0 = static_cast<unsigned int>(index);
		float phase = index - static_cast<float>(idx0);
		unsigned int idx1 = idx0 + 1;
		if (idx1 >= Size)
			idx1 = 0;

		return (*this)[idx0] + ((*this)[idx1] - (*this)[idx0]) * phase;
	}

	constexpr float interp(const float phase) const
	{
		float const index = phase * (Size-1);
		return interp_by_index(index);
	}
};

