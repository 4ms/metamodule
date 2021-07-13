#pragma once
#include "NE10_dsp.h"
#include "NE10_init.h"
#include "audio.hh"
#include "impulse-response.hh"
#include <cstdint>
using namespace MetaModule;

#ifndef ENABLE_NE10_FIR_FLOAT_NEON
	#define ENABLE_NE10_FIR_FLOAT_NEON
#endif

class Convolver {
	static constexpr uint32_t SIZE = AudioConf::BlockSize;
	using BlockType = AudioStream::AudioStreamBlock;
	static constexpr uint32_t IRSize = 2048;
	ne10_float32_t __attribute__((aligned(16))) firFilterCoeff[IRSize];
	ne10_float32_t __attribute__((aligned(16))) firFilterState[IRSize + AudioConf::BlockSize - 1];
	ne10_fir_instance_f32_t __attribute__((aligned(16))) firFilter;

	ne10_float32_t __attribute__((aligned(16))) filterIn[AudioConf::BlockSize];
	ne10_float32_t __attribute__((aligned(16))) filterOut[AudioConf::BlockSize];

public:
	Convolver() = default;

	void init()
	{
		ne10_init_dsp(NE10_OK);

		for (unsigned int n = 0; n < IRSize; ++n) {
			// the filter coefficients are the time-inverse of the impulse response
			firFilterCoeff[n] = static_cast<float>(impulse_response[IRSize - 1 - n]) / 32768.f;
		}
		ne10_fir_init_float(&firFilter, IRSize, firFilterCoeff, firFilterState, AudioConf::BlockSize);
	}

	void process(BlockType &in, BlockType &out)
	{

		for (int i = 0; i < AudioConf::BlockSize; i++) {
			filterIn[i] = AudioStream::AudioFrame::scaleInput(in[i].l);
		}
		ne10_fir_float_neon(&firFilter, filterIn, filterOut, AudioConf::BlockSize);
		// for (int i = 0; i < AudioConf::BlockSize; i++) {
		// 	filterOut[i] = filterIn[i];
		// }

		for (int i = 0; i < AudioConf::BlockSize; i++) {
			out[i].l = AudioStream::AudioFrame::scaleOutput(filterOut[i]);
			out[i].r = out[i].l;
		}
	}
};
