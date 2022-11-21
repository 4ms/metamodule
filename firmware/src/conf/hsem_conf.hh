#pragma once

namespace MetaModule
{
enum SemaphoreLocks {
	MainCoreReady = 1,
	ParamsBuf1Lock,
	ParamsBuf2Lock,
	ScreenFrameBufLock,
	ScreenFrameWriteLock,
	M4_ready,
	ParamCacheLock,
	RamDiskLock,
};

} // namespace MetaModule
