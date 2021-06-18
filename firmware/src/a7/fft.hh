#pragma once
#include "NE10_dsp.h"
#include "NE10_init.h"
#include "audio.hh"
#include "util/math_tables.hh"
#include <cstdint>

using namespace MetaModule;

class FFTfx {
	using BlockType = AudioStream::AudioStreamBlock;
	static constexpr uint32_t BufferSize = 16384;

	static constexpr uint32_t FFTSize = 2048; // AudioConf::BlockSize;
	static constexpr float FFTScaleFactor = 1.0f / (float)FFTSize;
	static constexpr uint32_t HopSize = 512;
	static constexpr uint32_t Period = 512;

	uint32_t in_i = 0;
	uint32_t out_read_i = 0;
	uint32_t out_write_i = 0;
	uint32_t sample_i = 0;
	bool buffer_full = false;

	ne10_fft_cfg_float32_t __attribute__((aligned(16))) cfg;
	ne10_fft_cpx_float32_t __attribute__((aligned(16))) timeDomainIn[2][FFTSize];
	ne10_fft_cpx_float32_t __attribute__((aligned(16))) timeDomainOut[2][FFTSize];
	ne10_fft_cpx_float32_t __attribute__((aligned(16))) freqDomain[2][FFTSize];
	float windowBuffer[FFTSize];
	float inputBuffer[2][BufferSize];
	float outputBuffer[2][BufferSize];

public:
	FFTfx() = default;

	void init()
	{
		ne10_init_dsp(NE10_OK);
		cfg = ne10_fft_alloc_c2c_float32(FFTSize);
		for (auto &channel : timeDomainOut) {
			for (auto &x : channel) {
				x.r = 0;
				x.i = 0;
			}
		}

		out_write_i = HopSize;

		// float inputAudio[AudioConf::BlockSize] ///not used: this is out "BlockType in" but made mono, but still
		// interpolated L/R

		// Cosine window
		for (int n = 0; n < FFTSize; n++)
			windowBuffer[n] = 0.5f * (1.0f - sinTable.interp_wrap(0.25f + n / (float)(FFTSize - 1)));
		// windowBuffer[n] = 0.5f * (1.0f - sin(M_PI/2.0f + 2.0f * M_PI * n / (float)(FFTSize - 1)));
		// windowBuffer[n] = 0.5f * (1.0f - cosf(2.0f * M_PI * n / (float)(FFTSize - 1)));
	}

	void process(BlockType &in, BlockType &out)
	{
		auto _out = out.begin();
		for (auto &_in : in) {
			inputBuffer[0][in_i] = _in.l;
			inputBuffer[1][in_i] = _in.r;
			if (++in_i >= BufferSize)
				in_i = 0;

			_out->l = outputBuffer[0][out_read_i];
			_out->r = outputBuffer[1][out_read_i];
			outputBuffer[0][out_read_i] = 0;
			outputBuffer[1][out_read_i] = 0;
			if (++out_read_i >= BufferSize)
				out_read_i = 0;
			if (++out_write_i >= BufferSize)
				out_write_i = 0;
		}

		for (auto &_in : in) {
			timeDomainIn[0][in_i].r = AudioStream::AudioFrame::scaleInput(_in.l);
			timeDomainIn[0][in_i].i = 0;
			timeDomainIn[1][in_i].r = AudioStream::AudioFrame::scaleInput(_in.r);
			timeDomainIn[1][in_i].i = 0;
			if (++in_i >= FFTSize) {
				in_i = 0;
				buffer_full = true;
			}
		}

		// FFT
		ne10_fft_c2c_1d_float32(freqDomain[0], timeDomainIn[0], cfg, 0);
		ne10_fft_c2c_1d_float32(freqDomain[1], timeDomainIn[1], cfg, 0);

		// Brick walls:
		for (int i = 0; i < FFTSize / 2; i++) {
			freqDomain[0][i].r = 0;
			freqDomain[0][i].i = 0;
		}
		for (int i = FFTSize / 2; i < FFTSize; i++) {
			freqDomain[1][i].r = 0;
			freqDomain[1][i].i = 0;
		}

		// IFFT
		ne10_fft_c2c_1d_float32(timeDomainOut[0], freqDomain[0], cfg, 1);
		ne10_fft_c2c_1d_float32(timeDomainOut[1], freqDomain[0], cfg, 1);

		for (int i = 0; i < AudioConf::BlockSize; i++) {
			out[i].l = AudioStream::AudioFrame::scaleOutput(timeDomainOut[0][i].r);
			out[i].r = AudioStream::AudioFrame::scaleOutput(timeDomainOut[1][i].r);
		}
	}
};
