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

	constexpr float interp_by_index_wrap(const float index) const
	{
		unsigned int idx0 = static_cast<unsigned int>(index);
		while (idx0 >= Size)
			idx0 -= Size;
		const float phase = index - static_cast<float>(idx0);
		const unsigned int idx1 = (idx0 == (Size - 1)) ? 0 : idx0 + 1;

		return data[idx0] + (data[idx1] - data[idx0]) * phase;
	}

	constexpr float interp_by_index(const float index) const
	{
		unsigned int idx0 = static_cast<unsigned int>(index);
		const float phase = index - static_cast<float>(idx0);
		const unsigned int idx1 = (idx0 == (Size - 1)) ? 0 : idx0 + 1;

		return data[idx0] + (data[idx1] - data[idx0]) * phase;
	}

	constexpr float interp_wrap(const float phase) const
	{
		const float index = phase * (Size - 1);
		return interp_by_index_wrap(index);
	}

	constexpr float interp(const float phase) const
	{
		const float index = phase * (Size - 1);
		return interp_by_index(index);
	}

	constexpr float closest_wrap(const float phase) const
	{
		unsigned int idx = static_cast<unsigned int>(phase * (Size - 1));
		while (idx >= Size)
			idx -= Size;
		return data[idx];
	}

	constexpr float closest(const float phase) const
	{
		const unsigned int idx = static_cast<unsigned int>(phase * (Size - 1));
		return data[idx];
	}
};
