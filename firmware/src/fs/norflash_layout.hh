#pragma once
#include <cstdint>

//first 10MB is for bootloaders (512kB) and application (9.5MB)
//next 4MB is Assets (4MB is reserved for this but for now we keep the image to 2MB for faster flashing)
//last 2MB is pathches
static constexpr uint32_t AssetVolFlashOffset = 10 * 1024 * 1024; //0xA00000;
static constexpr uint32_t AssetVolFlashSize = 2 * 1024 * 1024;

static constexpr uint32_t PatchVolFlashOffset = 14 * 1024 * 1024; //0xE00000;
static constexpr uint32_t PatchVolFlashSize = (2 * 1024 * 1024) - (2 * 1024);

static constexpr uint32_t CalDataFlashOffset = PatchVolFlashOffset + PatchVolFlashSize;
static constexpr uint32_t CalDataFlashSize = 2 * 1024;
