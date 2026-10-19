#pragma once
#include "fs/ramdisk.hh"
#include <cstdint>

// The A35 has a full-size RamDisk (60MB, same as MP1), in its own RAM: the GUI unpacks the assets
// into it, and loads plugin files into it.
// FIXME: on MP1 the RamDisk is in memory shared by all cores, so the M4 can present it over USB.
// Share it with the M33 when it does USB. Until then, the M33 just has a token one, since
// PatchStorage needs one to exist.
#if defined(CORE_CA35)
static constexpr uint32_t RamDiskSizeBytes = 60 * 1024 * 1024;
#else
static constexpr uint32_t RamDiskSizeBytes = 64 * 1024;
#endif
static constexpr uint32_t RamDiskBlockSize = 512;

using RamDrive = RamDisk<RamDiskSizeBytes, RamDiskBlockSize>;
