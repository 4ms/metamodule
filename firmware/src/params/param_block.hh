#pragma once
#include "conf/stream_conf.hh"
#include "metaparams.hh"
#include "params.hh"

namespace MetaModule
{

struct ParamBlock {
	std::array<Params, StreamConf::Audio::BlockSize> params{};
	MetaParams metaparams{};
};

using DoubleBufParamBlock = std::array<ParamBlock, 2>;

} // namespace MetaModule
