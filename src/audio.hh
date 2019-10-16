#pragma once
#include <stm32f7xx.h>

const int kBlockSize = 32; //number of frames (L/R pairs) we process at a time
const int kDMABlockSize = kBlockSize * 2; //number of frames total (two DMA half-transfers)
const int kSampleRate = 48000;

struct Frame {
	int16_t l;
	int16_t r;
};

//todo: compare with Buffer<Frame, kDMABlockSize> 
using DMABlock = Frame[kDMABlockSize];
using Block = Frame[kBlockSize];

struct TriangleOscillator {
  TriangleOscillator(uint32_t freq) : freq_(freq) {}
  TriangleOscillator() : freq_(0) {}
  uint32_t Process() {
    phase_ += freq_;
    uint32_t sample = phase_ * 2;
    if (phase_ > max_/2)
      sample = max_-sample;
    return sample;
  }

  void set_frequency(uint32_t freq) { freq_ = freq; }
  void set_phase(uint32_t phase) { phase_ = phase; }

private:
  static constexpr uint32_t max_ = 0xFFFFFFFF;
  uint32_t phase_ = 0;
  uint32_t freq_;
};


class Audio {

public:
	Audio();
	void start();

	// void process(Frame *in, Frame *out);
	void process(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]);

	void register_callback(void callbackfunc(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]));
	//void register_callback(void callbackfunc(Frame *in, Frame *out));

private: 
	DMABlock tx_buf;
	DMABlock rx_buf;

};

