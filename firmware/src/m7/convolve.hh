#pragma once
#include <cstdint>
using namespace MetaModule;
class Convolver {

public:
	Convolver() = default;

	void init()
	{
	}

	using BlockType = AudioStream::AudioStreamBlock;
	void process(BlockType &in, BlockType &out)
	{
		for (int i = 0; i < AudioConf::BlockSize; i++) {
			out[i].l = in[i].l;
			out[i].r = in[i].r;
		}
	}
};
