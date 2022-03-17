#pragma once
#include <stdint.h>

#define RAMDISK_BLK_NBR 0x40000U // 128MB
#define RAMDISK_BLK_SIZ 0x200U

extern __attribute__((section(".virtdrive"))) uint8_t virtdrive[RAMDISK_BLK_NBR * RAMDISK_BLK_SIZ];
