#pragma once
#include "conf/stream_conf.hh"
#include "metaparams.hh"
#include "params.hh"
#include "params/leds.hh"

namespace MetaModule
{

struct ParamBlock {
	std::array<Params, StreamConf::Audio::MaxBlockSize> params{};
	MetaParams metaparams{};
	LedStates leds{};
};

using DoubleBufParamBlock = std::array<ParamBlock, 2>;

} // namespace MetaModule
