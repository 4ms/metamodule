#pragma once
#include <cstdint>

// Developer-mode USB drive: USB MSC FAT volume used for transferring a
// mmplugin file from computer to MetaModule.
//
// Memory comes from the plugin arena
//
static constexpr uint32_t DevDriveSizeBytes = 8 * 1024 * 1024;
static constexpr uint32_t DevDriveBlockSize = 512;

static constexpr uint32_t DevDriveAlignment = 4096;

// FAT volume label
static constexpr char DevDriveLabel[] = "DEV_METAMODULE";
