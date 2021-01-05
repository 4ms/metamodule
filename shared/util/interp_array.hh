#pragma once

template<typename T, unsigned int Size>
struct InterpArray {
	T data[Size];

	T &operator[](const unsigned int index)
	{
		return data[index];
	}
	T &set(const unsigned int index)
	{
		return data[index];
	}
	void set(const unsigned int index, T val)
	{
		data[index] = val;
	}
	const T operator[](const unsigned int index) const
	{
		return data[index];
	}
	const T get(const unsigned int index) const
	{
		return data[index];
	}

	// Return an interpolated value where index = 0 and index = Size are the first element
	constexpr float interp_by_index_wrap(const float index) const
	{
		unsigned int idx0 = static_cast<unsigned int>(index);
		const float phase = index - static_cast<float>(idx0);
		while (idx0 >= Size)
			idx0 -= Size;
		const unsigned int idx1 = (idx0 == (Size - 1)) ? 0 : idx0 + 1;

		return (data[idx1] * phase) + (data[idx0] * (1.0f - phase));
		// return data[idx0] + (data[idx1] - data[idx0]) * phase;
		// return data[idx1] * index - data[idx1] * idx0 + data[idx0] - data[idx0] * index + data[idx0]*idx0;
	}

	// Return an interpolated value. index = 0 returns the first element and index = Size-1 returns the last element
	// Boundary checking is not done
	constexpr float interp_by_index(const float index) const
	{
		unsigned int idx0 = static_cast<unsigned int>(index);
		const float phase = index - static_cast<float>(idx0);
		const unsigned int idx1 = (idx0 == (Size - 1)) ? 0 : idx0 + 1;

		// return data[idx0] + (data[idx1] - data[idx0]) * phase;
		return (data[idx1] * phase) + (data[idx0] * (1.0f - phase));
	}

	// Return an interpolated value where phase = 0 and phase = 1 return the first element
	constexpr float interp_wrap(const float phase) const
	{
		const float index = phase * Size;
		return interp_by_index_wrap(index);
	}

	// Return an interpolated value where phase = 0 returns the first element, and phase = 1 returns the last element
	constexpr float interp(const float phase) const
	{
		const float index = phase * (Size - 1);
		return interp_by_index(index);
	}

	// Todo: this is really "floor" not "closest" (it doesn't round)
	// phase = 0 and phase = 1, 2, 3.. return first element
	constexpr float closest_wrap(const float phase) const
	{
		unsigned int idx = static_cast<unsigned int>(phase * Size);
		while (idx >= Size)
			idx -= Size;
		return data[idx];
	}

	// Todo: this is really "floor" not "closest" (it doesn't round)
	// phase = 0 returns first element, phase = 1 returns last element
	// No boundary checking is done
	constexpr float closest(const float phase) const
	{
		const unsigned int idx = static_cast<unsigned int>(phase * (Size - 1));
		return data[idx];
	}
};
