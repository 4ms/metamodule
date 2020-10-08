#include "math.hh"
#include <stdint.h>

// Todo put this in a _config.h file
static const int kAudioStreamBlockSize = 64;
static const int kNumAudioDMAHalfTransfers = 2;
static const int kAudioStreamDMABlockSize = kAudioStreamBlockSize * kNumAudioDMAHalfTransfers;

template<typename SampleType, int UsedBits = sizeof(SampleType) * 8>
struct GenericAudioFrame {
	SampleType l;
	SampleType r;

public:
	static const inline unsigned kSampleTypeBits = sizeof(SampleType) * 8;

	static const inline unsigned kMaxValue = MathTools::ipow(2, kSampleTypeBits - 1) - 1;
	static const inline unsigned kMaxSampleTypeValue = MathTools::ipow(2, UsedBits - 1);

	static const inline float kInScaling = static_cast<float>(kMaxValue);
	static const inline float kOutScaling = static_cast<float>(kMaxSampleTypeValue);

public:
	static float scaleInput(SampleType val)
	{
		return sign_extend(val) / kOutScaling;
	}
	static SampleType scaleOutput(float val)
	{
		return static_cast<SampleType>(val * kOutScaling);
	}

	static inline constexpr SampleType sign_extend(const SampleType &v) noexcept
	{
		static_assert((sizeof(SampleType) * 8u) >= UsedBits, "SampleType is smaller than the specified width");
		if constexpr ((sizeof(SampleType) * 8u) == UsedBits)
			return v;
		else {
			using S = struct {
				signed Val : UsedBits;
			};
			return reinterpret_cast<const S *>(&v)->Val;
		}
	}
};

