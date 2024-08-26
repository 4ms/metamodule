#include <cstdint>

template<uint32_t MaxSampleVal, float Threshold>
static inline int32_t compress(int32_t val) {
	static constexpr float Max = (float)MaxSampleVal;
	static constexpr float CompressionFactor = Max * Max * Threshold * (1.f - Threshold);

	static constexpr int32_t ThresholdValue = Threshold * Max;

	float tv = CompressionFactor / (float)val;
	if (val > ThresholdValue)
		return int32_t(Max - tv);
	else if (val < -ThresholdValue)
		return int32_t(-Max - tv);
	else
		return val;
}
