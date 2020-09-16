#pragma once
#include "codec_WM8731.hh"
#include "fxList.hh"
#include "hal_callback.hh"
#include "math.hh"
#include "oscs.hh"
#include "params.hh"
#include "stm32f7xx.h"
#include <array>

using namespace MathTools;

//Todo put this in a _config.h file
static const int kAudioStreamBlockSize = 32; //number of frames (L/R pairs) we process at a time
static const int kNumAudioDMAHalfTransfers = 2;
static const int kAudioStreamDMABlockSize = kAudioStreamBlockSize * kNumAudioDMAHalfTransfers;

//Todo: create generic ICodec class, and use it here. Then derive from it to get CodecWM8731, CodecCS4721, etc..
//Then the SharedBus::i2c can given to a codec object, and a ref to the codec object can be passed to the ctor of Audio
//And in unit tests we can give a testable codec object (plays from .wav file, and writes to .wav file)
//
class Audio {
public:
	// Data types:
	struct AudioFrame {
		int16_t l;
		int16_t r;

	private:
		static const inline size_t kSampleSizeBits = 16;
		static const inline size_t kMaxValue = ipow(2, kSampleSizeBits - 1) - 1;
		static const inline float kScaling = static_cast<float>(kMaxValue);

	public:
		static float scaleInput(int16_t val)
		{
			return val / kScaling;
		}
		static int16_t scaleOutput(float val)
		{
			return val * kScaling;
		}
	};

	enum AudioChannels { LEFT,
						 RIGHT };
	using AudioStreamBlock = std::array<AudioFrame, kAudioStreamBlockSize>;

	// Public methods:
	Audio(Params &p, I2CPeriph &i2c, uint32_t sample_rate = 48000);
	void start();
	void process(AudioStreamBlock &in, AudioStreamBlock &out);

private:
	void check_fx_change();
	void register_callback(void callbackfunc(AudioStreamBlock &in, AudioStreamBlock &out));

	AudioStreamBlock tx_buf_[2];
	AudioStreamBlock rx_buf_[2];
	Params &params;

	FXList FX_left;
	FXList FX_right;

	CodecWM8731 codec;
	uint32_t sample_rate_;

	static inline AudioProcessor *current_fx[2];

	struct TXCompleteCallback : HALCallbackManager::HALCBBase {
		TXCompleteCallback(Audio &a);
		virtual void halcb();
		Audio &audiostream;
	} callback_tx_complete;

	struct TXHalfCompleteCallback : HALCallbackManager::HALCBBase {
		TXHalfCompleteCallback(Audio &a);
		virtual void halcb();
		Audio &audiostream;
	} callback_tx_halfcomplete;
};

