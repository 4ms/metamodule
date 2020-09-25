#pragma once

#include <array>
template<typename T, unsigned int Size>
struct InterpArray {
	T data[Size];

	T &operator[](const unsigned int index)
	{
		return data[index];
	}
	const T operator[](const unsigned int index) const
	{
		return data[index];
	}
	const T operator[](const float index) const
	{
		return interp(index);
	}
	const T interp(const float index) const
	{
		int idx0 = static_cast<int>(index);
		float phase = index - static_cast<float>(idx0);
		int idx1 = idx0 + 1;
		if (idx1 >= Size)
			idx1 = 0;

		return data[idx0] + (data[idx1] - data[idx0]) * phase;
	}
};
/*
		InterpArray<float, 512> fold1;
		foldSamp[1] = fold1.interp(lookupIndex);
		foldSamp[2] = fold2.interp(lookupIndex);
		foldSamp[3] = fold3.interp(lookupIndex);
*/
