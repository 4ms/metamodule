#include "ramdisk.h"

// constexpr uint32_t RAMDISK_BLK_NBR = 0x40000U; // 128MB
// constexpr uint32_t RAMDISK_BLK_SIZ = 0x200; //512B

__attribute__((section(".virtdrive"))) uint8_t virtdrive[RAMDISK_BLK_NBR * RAMDISK_BLK_SIZ];
