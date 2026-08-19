#pragma once
#include <cstdint>

// Developer-mode USB drive: USB MSC FAT volume used for transferring a
// mmplugin file from computer to MetaModule.
//
// Memory comes from the plugin arena
//
static constexpr uint32_t DevDriveSizeBytes = 16 * 1024 * 1024;
static constexpr uint32_t DevDriveBlockSize = 512;

static constexpr uint32_t DevDriveAlignment = 4096;

// FAT volume label. Decides the path the host mounts it at (/Volumes/DEV_MM on
// macOS), which is what makes the scripted install workflow possible.
static constexpr char DevDriveLabel[] = "DEV_MM";

// FAT limits volume labels to 11 characters (ff.c rejects longer ones with
// FR_INVALID_NAME); '+.,;=[]' and the usual path characters are also invalid.
static_assert(sizeof(DevDriveLabel) - 1 <= 11, "FAT volume labels are limited to 11 characters");
