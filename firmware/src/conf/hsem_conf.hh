#pragma once

namespace MetaModule
{
enum SemaphoreLocks {
	M7_ready = 1,
	ParamsBuf1Lock,
	ParamsBuf2Lock,
	LEDFrameBufLock,
	ScreenFrameBufLock,
	ScreenFrameWriteLock,
	M4_ready,
};

} // namespace MetaModule
