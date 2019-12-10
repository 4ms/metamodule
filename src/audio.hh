#pragma once
#include <stm32f7xx.h>
#include <array>
#include "params.hh"

const int kBlockSize = 32; //number of frames (L/R pairs) we process at a time
const int kDMABlockSize = kBlockSize * 2; //number of frames for DMA to read/write (two DMA half-transfers)
const int kSampleRate = 48000;

struct Frame {
	int16_t l;
	int16_t r;
};

using DMABlock = std::array<Frame, kDMABlockSize>;
using Block = std::array<Frame, kBlockSize>;

//Todo: Triosc belongs elsewhere

//actual freq = update_rate(Hz) * increment(#) / 2^32
// increment = 2^32 * freq / update_rate
template<int update_rate>
struct TriangleOscillator {
    TriangleOscillator(uint32_t freq) : increment_(freq * (max_/update_rate)) {}
    TriangleOscillator() : increment_(0) {}
    uint32_t Process() {
        phase_ += increment_;
        uint32_t sample = phase_ * 2;
        if (phase_ > max_/2)
            sample = max_-sample;
        return sample;
}   

    void set_frequency(uint32_t freq) { increment_ = freq; }
    void set_phase(uint32_t phase) { phase_ = phase; }

private:
    static constexpr uint32_t max_ = 0xFFFFFFFF;
    uint32_t phase_ = 0;
    uint32_t increment_;
};


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

