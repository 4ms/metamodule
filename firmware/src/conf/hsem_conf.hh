#pragma once

namespace MetaModule
{
enum SemaphoreLocks {
	MainCoreReady = 1,
	ParamsBuf1Lock,
	ParamsBuf2Lock,
	LEDFrameBufLock,
	ScreenFrameBufLock,
	ScreenFrameWriteLock,
	M4_ready,
	ParamCacheLock,
	RamDiskLockOnA7Done,
	RamDiskLockOnM4Using
};

} // namespace MetaModule
