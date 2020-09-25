#pragma once

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
	constexpr float interp_by_index(const float index) const
	{
		unsigned int idx0 = static_cast<unsigned int>(index);
		float phase = index - static_cast<float>(idx0);
		unsigned int idx1 = idx0 + 1;
		if (idx1 >= Size)
			idx1 = 0;

		return data[idx0] + (data[idx1] - data[idx0]) * phase;
	}

	constexpr float interp(const float phase) const
	{
		float const index = phase * (Size - 1);
		return interp_by_index(index);
	}
};
