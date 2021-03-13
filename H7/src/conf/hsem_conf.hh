#pragma once
#include <cstdint>

namespace MetaModule
{
enum SemaphoreLocks {
	SharedBusLock = 1,
	ParamsBuf1Lock,
	ParamsBuf2Lock,
	LEDFrameBufLock,
	ScreenFrameBuf1Lock,
	ScreenFrameBuf2Lock,
};

} // namespace MetaModule
