#include "math.hh"
#include <stdint.h>

// Todo put this in a _config.h file
static const int kAudioStreamBlockSize = 32;
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
		return convert_s24_to_s32(val) / kOutScaling;
	}
	static SampleType scaleOutput(float val)
	{
		return static_cast<SampleType>(val * kOutScaling);
	}

	// Todo: test this, and check generated ASM
	static inline constexpr SampleType sign_extend(const SampleType &v) noexcept
	{
		// static_assert(std::is_integral<SampleType>::value, "SampleType is not integral");
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
	static int32_t convert_s24_to_s32(int32_t src)
	{
		uint32_t in_24bit = src << 8;
		int32_t in_s24bit = (int32_t)in_24bit;
		in_s24bit >>= 8;
		return (in_s24bit);
	}
};

