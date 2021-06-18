#pragma once
#include "NE10_dsp.h"
#include "NE10_init.h"
#include "audio.hh"
#include <cstdint>
using namespace MetaModule;

class FFTfx {
	static constexpr uint32_t SIZE = MetaModule::AudioConf::BlockSize;
	using BlockType = MetaModule::AudioStream::AudioStreamBlock;

	ne10_fft_cfg_float32_t __attribute__((aligned(16))) cfg;
	ne10_fft_cpx_float32_t __attribute__((aligned(16))) timeDomain[2][SIZE];
	ne10_fft_cpx_float32_t __attribute__((aligned(16))) freqDomain[2][SIZE];

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
			timeDomain[0][i].r = AudioStream::AudioFrame::scaleInput(in[i].l);
			timeDomain[0][i].i = 0;
			timeDomain[1][i].r = AudioStream::AudioFrame::scaleInput(in[i].r);
			timeDomain[1][i].i = 0;
		}

		// FFT
		ne10_fft_c2c_1d_float32(freqDomain[0], timeDomain[0], cfg, 0);
		ne10_fft_c2c_1d_float32(freqDomain[1], timeDomain[1], cfg, 0);

		// Brick walls:
		for (int i = 0; i < SIZE / 2; i++) {
			freqDomain[0][i].r = 0;
			freqDomain[0][i].i = 0;
		}
		for (int i = SIZE / 2; i < SIZE; i++) {
			freqDomain[1][i].r = 0;
			freqDomain[1][i].i = 0;
		}

		// IFFT
		ne10_fft_c2c_1d_float32(freqDomain[0], timeDomain[0], cfg, 1);
		ne10_fft_c2c_1d_float32(freqDomain[0], timeDomain[1], cfg, 1);

		for (int i = 0; i < AudioConf::BlockSize; i++) {
			out[i].l = AudioStream::AudioFrame::scaleOutput(timeDomain[0][i].r);
			out[i].r = AudioStream::AudioFrame::scaleOutput(timeDomain[1][i].r);
		}
	}
};
