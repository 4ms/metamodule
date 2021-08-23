#pragma once
#include <cstdint>

namespace MetaModule
{

struct AuxStreamFrame {};

struct AuxStreamUpdateConf : mdrivlib::DefaultPinChangeConf {};

struct AuxStream {
	void init() {}
	void queue_data(AuxStreamFrame &) {}
	void output_next() {}
};

} // namespace MetaModule
