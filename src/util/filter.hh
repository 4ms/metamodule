#pragma once

constexpr unsigned int Log2Int(const unsigned int x)
{
	for (int i = 0; i < 32; i++)
		if (x == (1UL << i))
			return i;
	return 0;
}

template<int size, class T = unsigned int>
struct Oversampler {
	static_assert(Log2Int(size) > 0, "Oversampler<size, T> requires size to be a power of 2");

public:
	Oversampler() {}
	void add_val(T newval)
	{
		buff_ += newval;
		if (++idx_ >= size) {
			val_ = buff_ >> oversample_shift_;
			idx_ = 0;
			buff_ = 0;
		}
	}
	T val()
	{
		return val_;
	}

private:
	constexpr static auto oversample_shift_ = Log2Int(size);
	T buff_ = 0;
	T val_ = 0;
	unsigned int idx_ = 0;
};

