#pragma once
#include <stm32f7xx.h>

const int kBlockSize = 32; //number of frames (L/R pairs) we process at a time
const int kDMABlockSize = kBlockSize * 2; //number of frames total (two DMA half-transfers)
const int kSampleRate = 48000;

struct Frame {
	int32_t l;
	int32_t r;
};

using Block = Frame[kDMABlockSize];

class Audio {
public:
	Audio();
	void start();

	// void process(Frame *in, Frame *out);
	void process(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]);

	void register_callback(void callbackfunc(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]));
	//void register_callback(void callbackfunc(Frame *in, Frame *out));

private: 
	Block tx_buf;
	Block rx_buf;
};
