#pragma once
#include <stm32f7xx.h>

const int kBlockSize = 32;
const int kSampleRate = 48000;

struct Frame {
	int32_t l;
	int32_t r;
};

using Block = Frame[kBlockSize];

class Audio {
public:
	Audio();

	// void process(Frame *in, Frame *out);
	void process(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]);

	void register_callback(void callbackfunc(Frame (&in)[kBlockSize], Frame (&out)[kBlockSize]));
	//void register_callback(void callbackfunc(Frame *in, Frame *out));

private: 
	Block tx_buf;
	Block rx_buf;
};
