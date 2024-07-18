#pragma once
#include "conf/auxstream_conf.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

using AuxStreamBlock = std::array<AuxStreamFrame, StreamConf::Audio::MaxBlockSize>;
using DoubleAuxStreamBlock = std::array<AuxStreamBlock, 2>;

} // namespace MetaModule
