#pragma once
#include <stdint.h>

// actual freq = update_rate(Hz) * increment(#) / 2^32
// increment = 2^32 * freq / update_rate
template<int update_rate>
struct TriangleOscillator {
	TriangleOscillator(uint32_t freq)
		: increment_(freq * (max_ / update_rate))
	{}
	TriangleOscillator()
		: increment_(0)
	{}
	uint32_t Process()
	{
		phase_ += increment_;
		uint32_t sample = phase_ * 2;
		if (phase_ > max_ / 2)
			sample = max_ - sample;
		return sample;
	}

	void set_frequency(uint32_t freq)
	{
		increment_ = freq * (max_ / update_rate);
	}
	void set_phase(uint32_t phase)
	{
		phase_ = phase;
	}

private:
	static constexpr uint32_t max_ = 0xFFFFFFFF;
	uint32_t phase_ = 0;
	uint32_t increment_;
};

template<int update_rate>
struct PhaseAccum {
	PhaseAccum(uint32_t freq)
		: increment_(freq * (max_ / update_rate))
	{}
	PhaseAccum()
		: increment_(0)
	{}
	uint32_t Process()
	{
		phase_ += increment_;
		return phase_;
	}

	void set_frequency(uint32_t freq)
	{
		increment_ = freq * (max_ / update_rate);
	}
	void set_phase(uint32_t phase)
	{
		phase_ = phase;
	}

private:
	static constexpr uint32_t max_ = 0xFFFFFFFF;
	uint32_t phase_ = 0;
	uint32_t increment_;
};

