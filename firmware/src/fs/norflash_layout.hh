#pragma once
#include <cstdint>

//first 10MB is for bootloaders (512kB) and application (9.5MB)
//next 4MB is Assets
//last 2MB is patches, minus 4k for Calibration data
static constexpr uint32_t BootloaderSize = 512 * 1024;
static constexpr uint32_t FirmwareSize = (10 * 1024 * 1024) - BootloaderSize;
static constexpr uint32_t AssetVolFlashSize = 5 * 1024 * 1024;
static constexpr uint32_t CalDataFlashSize = 4096;
static constexpr uint32_t PatchVolFlashSize = (1 * 1024 * 1024) - CalDataFlashSize;

static constexpr uint32_t FirmwareOffset = BootloaderSize;
static constexpr uint32_t AssetVolFlashOffset = FirmwareOffset + FirmwareSize;
static constexpr uint32_t PatchVolFlashOffset = AssetVolFlashOffset + AssetVolFlashSize;
static constexpr uint32_t CalDataFlashOffset = PatchVolFlashOffset + PatchVolFlashSize;
