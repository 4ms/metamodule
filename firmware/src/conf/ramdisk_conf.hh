#pragma once
#include "fs/ramdisk.hh"
#include <cstdint>

static constexpr uint32_t RamDiskSizeBytes = 32 * 1024 * 1024; //==VIRTDRIVE_SZ is not constexpr
static constexpr uint32_t RamDiskBlockSize = 512;

using RamDrive = RamDisk<RamDiskSizeBytes, RamDiskBlockSize>;
