#include "math.hh"
#include <cstdint>

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
	// Todo: use operators for these. operator float() and ...?
	// clang-format off
	static float scaleInput(SampleType val) { return convert_s24_to_s32(val) / kOutScaling; }
	static SampleType scaleOutput(float val) { return static_cast<SampleType>(val * kOutScaling); }
	// clang-format on

	// Todo: use ASM sign-extension
	// Todo: deduce if we need this based on shift amount
	static int32_t convert_s24_to_s32(int32_t src)
	{
		uint32_t in_24bit = src << 8;
		int32_t in_s24bit = (int32_t)in_24bit;
		in_s24bit >>= 8;
		return (in_s24bit);
	}
};

using AudioFrame = GenericAudioFrame<int32_t, 24>;

