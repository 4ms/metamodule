#pragma once
#include "impulse-response.hh"
#include "NE10_dsp.h"
#include "NE10_init.h"
#include "audio.hh"
#include <cstdint>
using namespace MetaModule;

class Convolver {
	static constexpr uint32_t SIZE = MetaModule::AudioConf::BlockSize;
	using BlockType = MetaModule::AudioStream::AudioStreamBlock;

public:
	Convolver() = default;

	void init()
	{
		ne10_init_dsp(NE10_OK);
		// cfg = ne10_fft_alloc_c2c_float32(SIZE);
	}

	void process(BlockType &in, BlockType &out)
	{
};

