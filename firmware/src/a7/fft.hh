#pragma once
#include "NE10_dsp.h"
#include "NE10_init.h"
#include "audio.hh"
#include "debug.hh"
#include "util/math_tables.hh"
#include <cstdint>

using namespace MetaModule;

class FFTfx {
	using BlockType = AudioStream::AudioStreamBlock;
	static constexpr uint32_t BufferSize = 16384;
	static constexpr uint32_t BufferSizeMask = BufferSize - 1;

	static constexpr uint32_t FFTSize = 2048;
	static constexpr float FFTScaleFactor = 1.0f / (float)FFTSize;
	static constexpr uint32_t HopSize = 512;

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
			// Grab input
			inputBuffer[0][in_i] = AudioStream::AudioFrame::scaleInput((_in.l + _in.r) / 2);
			// inputBuffer[1][in_i] = AudioStream::AudioFrame::scaleInput(_in.r);
			if (++in_i >= BufferSize)
				in_i = 0;

			// Copy output buffer to output
			_out->l = outputBuffer[0][out_read_i];
			_out->r = _out->l;
			// _out->r = outputBuffer[1][out_read_i];
			_out++;

			// Clear the output sample in the buffer so it is ready for the next overlap-add
			outputBuffer[0][out_read_i] = 0;
			// outputBuffer[1][out_read_i] = 0;
			if (++out_read_i >= BufferSize)
				out_read_i = 0;

			if (++out_write_i >= BufferSize)
				out_write_i = 0;

			// Process a bit
			if (++sample_i >= HopSize) {
				Debug::Pin1::high();
				// Copy the last FFTSize samples, applying the window
				int32_t read_i = (in_i - FFTSize + BufferSize) & BufferSizeMask;
				for (int n = 0; n < FFTSize; n++) {
					timeDomainIn[0][n].r = (ne10_float32_t)inputBuffer[0][read_i & BufferSizeMask] * windowBuffer[n];
					timeDomainIn[0][n].i = 0;
					// timeDomainIn[1][n].r = (ne10_float32_t)inputBuffer[1][read_i & BufferSizeMask] * windowBuffer[n];
					// timeDomainIn[1][n].i = 0;
					read_i++;
				}

				// Run the FFT
				ne10_fft_c2c_1d_float32(freqDomain[0], timeDomainIn[0], cfg, 0);
				// ne10_fft_c2c_1d_float32(freqDomain[1], timeDomainIn[1], cfg, 0);

				// Robotize
				for (int i = 0; i < FFTSize; i++) {
					float amplitude =
						sqrtf(freqDomain[0][i].r * freqDomain[0][i].r + freqDomain[0][i].i * freqDomain[0][i].i);
					freqDomain[0][i].r = amplitude;
					freqDomain[0][i].i = 0;
				}
				// Brick walls:
				// for (int i = 0; i < FFTSize / 8; i++) {
				// 	freqDomain[0][i].r = 0;
				// 	freqDomain[0][i].i = 0;
				// }
				// for (int i = FFTSize / 8; i < FFTSize; i++) {
				// 	freqDomain[1][i].r = 0;
				// 	freqDomain[1][i].i = 0;
				// }

				// IFFT
				ne10_fft_c2c_1d_float32(timeDomainOut[0], freqDomain[0], cfg, 1);
				// ne10_fft_c2c_1d_float32(timeDomainOut[1], freqDomain[0], cfg, 1);

				uint32_t write_i = out_write_i;
				for (int i = 0; i < FFTSize; i++) {
					outputBuffer[0][write_i] +=
						AudioStream::AudioFrame::scaleOutput(timeDomainOut[0][i].r); //* FFTScaleFactor);
					// outputBuffer[1][write_i] +=
					// 	AudioStream::AudioFrame::scaleOutput(timeDomainOut[1][i].r * FFTScaleFactor);
					if (write_i++ >= BufferSize)
						write_i = 0;
				}
				sample_i = 0;
				Debug::Pin1::low();
			}
		}
	}
};
