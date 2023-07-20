#pragma once
#include "fs/ramdisk.hh"
#include <cstdint>

static constexpr uint32_t RamDiskSizeBytes = 4 * 1024 * 1024;
static constexpr uint32_t RamDiskBlockSize = 512;

using RamDrive = RamDisk<RamDiskSizeBytes, RamDiskBlockSize>;
