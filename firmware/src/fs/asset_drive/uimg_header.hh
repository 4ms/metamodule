#pragma once
#include <cstdint>

// This is the "legacy" (ie non-FIT) U-Boot image header
namespace Uimg
{

#if __BYTE_ORDER == __LITTLE_ENDIAN
inline uint32_t be32_to_cpu(uint32_t x) {
	return ((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >> 8) | ((x & 0x0000ff00) << 8) | ((x & 0x000000ff) << 24);
}
#else
inline uint32_t be32_to_cpu(uint32_t x) {
	return x;
}
#endif

constexpr uint32_t IH_MAGIC = 0x27051956; /* Image Magic Number */
constexpr uint32_t IH_NMLEN = 32;		  /* Image Name Length */

//  Legacy format image header,
//  all data in network byte order (aka natural aka bigendian).
//  Taken from u-boot include/image.h
struct image_header {
	uint32_t ih_magic;		   /* Image Header Magic Number */
	uint32_t ih_hcrc;		   /* Image Header CRC Checksum */
	uint32_t ih_time;		   /* Image Creation Timestamp */
	uint32_t ih_size;		   /* Image Data Size */
	uint32_t ih_load;		   /* Data	 Load  Address */
	uint32_t ih_ep;			   /* Entry Point Address */
	uint32_t ih_dcrc;		   /* Image Data CRC Checksum */
	uint8_t ih_os;			   /* Operating System */
	uint8_t ih_arch;		   /* CPU architecture */
	uint8_t ih_type;		   /* Image Type */
	uint8_t ih_comp;		   /* Compression Type */
	uint8_t ih_name[IH_NMLEN]; /* Image Name */
};

constexpr uint32_t HeaderSize = sizeof(image_header);

enum image_type_t {
	IH_TYPE_INVALID = 0,	 /* Invalid Image */
	IH_TYPE_KERNEL = 2,		 /* OS Kernel Image (A7 bootable) */
	IH_TYPE_FIRMWARE = 5,	 /* Firmware Image (A7 non-bootable)*/
	IH_TYPE_STM32IMAGE = 35, /* STMicroelectronics STM32 Image (FSBL bootloader) */
	IH_TYPE_COPRO = 40,		 /* Coprocessor Image for remoteproc (M4 firmware) */
};
} // namespace Uimg
