#pragma once
#include <cstdint>

namespace MetaModule
{
enum SemaphoreLocks {
	SharedBusLock = 1,
	ParamsBuf1Lock,
	ParamsBuf2Lock,
	LEDFrameBufLock,
	ScreenFrameBufLock,
	ScreenFrameWriteLock,
	M4_ready,
};

} // namespace MetaModule
