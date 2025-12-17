#pragma once
#include "conf/stream_conf.hh"
#include "params/leds.hh"
#include "params/metaparams.hh"
#include "params/params.hh"

namespace MetaModule
{

struct ParamBlock {
	std::array<Params, StreamConf::Audio::MaxBlockSize> params{};
	MetaParams metaparams{};
	LedStates leds{};
};

using DoubleBufParamBlock = std::array<ParamBlock, 2>;

} // namespace MetaModule
