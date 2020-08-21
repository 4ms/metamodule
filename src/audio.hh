#pragma once
#include <stm32f7xx.h>
#include <array>
#include "params.hh"
#include "oscs.hh"
#include "processors/vca.h"
#include "processors/bit_crush.h"
#include "processors/lpf.h"
#include "processors/lpg.h"

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
	};
	enum AudioChannels {
		LEFT,
		RIGHT
	};
	using AudioDMABlock = std::array<AudioFrame, kAudioStreamDMABlockSize>;
	using AudioStreamBlock = std::array<AudioFrame, kAudioStreamBlockSize>;

	Audio(Params &p);
	void start();
	static void process(AudioStreamBlock& in, AudioStreamBlock& out);

private:
	void register_callback(void callbackfunc(AudioStreamBlock& in, AudioStreamBlock& out));

	AudioDMABlock tx_buf_;
	AudioDMABlock rx_buf_;
	Params& params;

	static inline AudioProcessor *current_fx[2];
	static inline Audio *instance;
};

struct AudioProcessorList {
	static inline AudioProcessor* FX[] = {
		new VCA,
		new BitCrusher,
		new LowPassFilter,
		new LPG,
	};
};

