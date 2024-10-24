#pragma once

namespace MetaModule
{
enum SemaphoreLocks {
	MainCoreReady = 1,
	ParamsBuf1Lock,
	ParamsBuf2Lock,
	AuxCoreReady,
	ScreenFrameWriteLock,
	M4CoreReady,
	ParamCacheLock,
	RamDiskLock,
	SharedI2CLock,
};

} // namespace MetaModule
