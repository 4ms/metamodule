#pragma once
#include <stm32f7xx.h>
#include <array>
#include "params.hh"
#include "oscs.hh"

//Todo put this in a _config.h file
static const int kAudioStreamBlockSize = 32; //number of frames (L/R pairs) we process at a time
static const int kAudioStreamDMABlockSize = kAudioStreamBlockSize * 2; //number of frames for DMA to read/write (two DMA half-transfers)
static const int kSampleRate = 48000;

struct AudioFrame {
	int16_t l;
	int16_t r;
};

using AudioDMABlock = std::array<AudioFrame, kAudioStreamDMABlockSize>;
using AudioStreamBlock = std::array<AudioFrame, kAudioStreamBlockSize>;

class Audio {
public:
	Audio() = default;
	void start();
	void process(Params &params, AudioStreamBlock& in, AudioStreamBlock& out);
	void register_callback(void callbackfunc(AudioStreamBlock& in, AudioStreamBlock& out));

private:
	AudioDMABlock tx_buf_;
	AudioDMABlock rx_buf_;
};

