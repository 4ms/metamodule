#pragma once

template<typename SampleT>
class KneeCompressor {
	const float kMaxSampleVal;
	const float kThresholdCoef;
	const SampleT kThreshold;

public:
	//  num_sample_bits is usually 8, 16, 24, or 32
	//  threshold_percent is the threshold at which limiting should begin (0.75 is a good place to start)

	KneeCompressor(int num_sample_bits, float threshold_percent)
		: kMaxSampleVal{calc_max_sample_val(num_sample_bits)}
		, kThresholdCoef{calc_threshold_coef(kMaxSampleVal, threshold_percent)}
		, kThreshold{calc_threshold(num_sample_bits, threshold_percent)}
	{}

	constexpr float calc_max_sample_val(int num_sample_bits)
	{
		return static_cast<float>(1 << (num_sample_bits - 1));
	}
	constexpr float calc_threshold_coef(float m, float threshold_percent)
	{
		return m * m * threshold_percent * (1.0f - threshold_percent);
	}
	constexpr SampleT calc_threshold(int num_sample_bits, float threshold_percent)
	{
		return static_cast<SampleT>(threshold_percent * (1 << (num_sample_bits - 1)));
	}

	constexpr SampleT compress(const SampleT val) const
	{
		const float tv = kThresholdCoef / ((float)val);
		if (val > kThreshold)
			return static_cast<SampleT>(kMaxSampleVal - tv);
		else if (val < -kThreshold)
			return static_cast<SampleT>(-kMaxSampleVal - tv);
		else
			return val;
	}
};

template<>
class KneeCompressor<float> {
	const float kThresholdCoef;
	const float kThreshold;
	constexpr float calc_threshold_coef(float threshold_percent)
	{
		return threshold_percent * (1.0f - threshold_percent);
	}

public:
	//  sample values range from -1.0 to +1.0
	//  threshold_percent is the threshold at which limiting should begin
	KneeCompressor(float threshold_percent = 0.75f)
		: kThresholdCoef{calc_threshold_coef(threshold_percent)}
		, kThreshold{threshold_percent}
	{}

	constexpr float compress(const float val) const
	{
		const float tv = kThresholdCoef / val;
		if (val > kThreshold)
			return (1.f - tv);
		else if (val < -kThreshold)
			return (-1.f - tv);
		else
			return val;
	}
};

