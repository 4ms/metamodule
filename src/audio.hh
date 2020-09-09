#pragma once
#include "fxList.hh"
#include "math.hh"
#include "oscs.hh"
#include "params.hh"
#include <array>
#include <stm32f7xx.h>
using namespace MathTools;
//Todo put this in a _config.h file
static const int kAudioStreamBlockSize = 32; //number of frames (L/R pairs) we process at a time
static const int kNumAudioDMAHalfTransfers = 2;
static const int kAudioStreamDMABlockSize = kAudioStreamBlockSize * kNumAudioDMAHalfTransfers;
static const int kSampleRate = 48000;

class Audio {
public:
	struct AudioFrame {
		int16_t l;
		int16_t r;

	private:
		static const inline size_t kSampleSizeBits = 16;
		static const inline size_t kMaxValue = ipow(2, kSampleSizeBits - 1) - 1;
		static const inline float kScaling = static_cast<float>(kMaxValue);

	public:
		static float scaleInput(int16_t val) { return val / kScaling; }
		static int16_t scaleOutput(float val) { return val * kScaling; }
	};

	enum AudioChannels {
		LEFT,
		RIGHT
	};
	using AudioDMABlock = std::array<AudioFrame, kAudioStreamDMABlockSize>;
	using AudioStreamBlock = std::array<AudioFrame, kAudioStreamBlockSize>;

	Audio(Params &p);
	void start();
	static void process(AudioStreamBlock &in, AudioStreamBlock &out);

private:
	void check_fx_change();
	void register_callback(void callbackfunc(AudioStreamBlock &in, AudioStreamBlock &out));

	AudioDMABlock tx_buf_;
	AudioDMABlock rx_buf_;
	Params &params;

	FXList FX_left;
	FXList FX_right;

	static inline AudioProcessor *current_fx[2];
	static inline Audio *instance;
};

