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
	InvalidateICache,
	RunningPatchTests,
	UartLock,
};

enum UartLockProcID {
	UartLockA7Core0 = 0, // must be 0, comes from MPIDR
	UartLockA7Core1 = 1, // must be 1, comes from MPIDR
	UartLockM4Direct = 2,
	UartLockM4Drain = 3,
};

} // namespace MetaModule
