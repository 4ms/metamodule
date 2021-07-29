#pragma once
#include "conf/stream_conf.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

struct AuxSignalFrame {
	uint32_t clock_out;
};

using AuxSignalStreamBlock = std::array<AuxSignalFrame, StreamConf::Audio::BlockSize>;
using DoubleAuxSignalStreamBlock = std::array<AuxSignalStreamBlock, 2>;

} // namespace MetaModule
