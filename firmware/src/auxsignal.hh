#pragma once
#include "conf/stream_conf.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

struct AuxSignalFrame {
#if defined(BOARD_HAS_DAC)
	uint32_t clock_out;
	uint32_t dac1;
	uint32_t dac2;
#else
	union {
		uint32_t clock_out;
		uint32_t dac1;
		uint32_t dac2;
	};
#endif
};

using AuxSignalStreamBlock = std::array<AuxSignalFrame, StreamConf::Audio::BlockSize>;
using DoubleAuxSignalStreamBlock = std::array<AuxSignalStreamBlock, 2>;

} // namespace MetaModule
