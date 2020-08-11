#pragma once
#include <stm32f7xx.h>
#include <array>
#include "params.hh"
#include "oscs.hh"

const int kBlockSize = 32; //number of frames (L/R pairs) we process at a time
const int kDMABlockSize = kBlockSize * 2; //number of frames for DMA to read/write (two DMA half-transfers)
const int kSampleRate = 48000;

struct Frame {
	int16_t l;
	int16_t r;
};

using DMABlock = std::array<Frame, kDMABlockSize>;
using Block = std::array<Frame, kBlockSize>;

class Audio {
public:
    Audio() = default;
    void start();
    void process(Params &params, Block& in, Block& out);
    void register_callback(void callbackfunc(Block& in, Block& out));

private:
	DMABlock tx_buf_;
	DMABlock rx_buf_;
};

