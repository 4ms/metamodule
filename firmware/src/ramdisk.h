// #pragma once
// #include <stdint.h>

// #define RamDisk_SizeBytes (16UL*1024UL*1024UL)
// #define RamDisk_BlockSize 0x200U
// #define RamDisk_NumBlocks (RamDisk_SizeBytes / RamDisk_BlockSize)

// extern __attribute__((section(".virtdrive"))) uint8_t virtdrive[RamDisk_SizeBytes];

// enum RamDiskStatus {
// 	NotInit,
// 	Disconnected,
// 	Connected,
// };

// #ifdef __cplusplus
// extern "C" {
// #endif

// void RamDisk_SetStatus(enum RamDiskStatus status);
// enum RamDiskStatus RamDisk_GetStatus(void);

// #ifdef __cplusplus
// }
// #endif
