#pragma once
#include "NE10_dsp.h"
#include "NE10_init.h"
#include "audio.hh"
#include <cstdint>
using namespace MetaModule;

class FFTfx {
	static constexpr uint32_t SIZE = MetaModule::AudioConf::BlockSize;
	using BlockType = MetaModule::AudioStream::AudioStreamBlock;

	ne10_fft_cfg_float32_t __attribute__((align(16))) cfg;
	ne10_fft_cpx_float32_t __attribute__((align(16))) timeDomain[SIZE];
	ne10_fft_cpx_float32_t __attribute__((align(16))) freqDomain[SIZE];

public:
	FFTfx() = default;

	void init()
	{
		ne10_init_dsp(NE10_OK);
		cfg = ne10_fft_alloc_c2c_float32(SIZE);
	}

	void process(BlockType &in, BlockType &out)
	{
		for (int i = 0; i < SIZE; i++) {
			timeDomain[i].r = AudioStream::AudioFrame::scaleInput(in[i].l);
			timeDomain[i].i = 0;
		}

		// FFT
		ne10_fft_c2c_1d_float32(freqDomain, timeDomain, cfg, 0);

		// Brick wall LPF:
		for (int i = SIZE / 2; i < SIZE; i++) {
			freqDomain[i].r = 0;
			freqDomain[i].i = 0;
		}

		// IFFT
		ne10_fft_c2c_1d_float32(freqDomain, timeDomain, cfg, 1);

		for (int i = 0; i < AudioConf::BlockSize; i++) {
			out[i].l = AudioStream::AudioFrame::scaleOutput(timeDomain[i].r);
			out[i].r = in[i].r;
		}
	}
};
