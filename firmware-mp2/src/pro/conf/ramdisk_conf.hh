#pragma once
#include "fs/ramdisk.hh"
#include <cstdint>

// FIXME: MP1's RamDisk is 60MB, in memory shared by all cores, and the A7 uses it for plugin
// loading and assets. On MP2 nothing uses it yet: PatchStorage just needs one to exist.
// Make it full size and shared when the A35 needs it.
static constexpr uint32_t RamDiskSizeBytes = 64 * 1024;
static constexpr uint32_t RamDiskBlockSize = 512;

using RamDrive = RamDisk<RamDiskSizeBytes, RamDiskBlockSize>;
