#pragma once
#include "conf/stream_conf.hh"
#include <array>
#include <cstdint>

struct AuxSignalFrame {
	uint32_t dac1;
	uint32_t dac2;
	uint32_t clock_out;
};

using AuxSignalStreamBlock = std::array<AuxSignalFrame, StreamConf::DAC::BlockSize>;
using DoubleAuxSignalStreamBlock = std::array<AuxSignalStreamBlock, 2>;
