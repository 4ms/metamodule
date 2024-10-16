#pragma once
#include "conf/stream_conf.hh"
#include "metaparams.hh"
#include "params.hh"

namespace MetaModule
{

struct ParamBlock {
	std::array<Params, StreamConf::Audio::MaxBlockSize> params{};
	MetaParams metaparams{};
	char padding[32];
};

constexpr auto pb_sz = sizeof(ParamBlock); //33024

using DoubleBufParamBlock = std::array<ParamBlock, 2>;

} // namespace MetaModule
