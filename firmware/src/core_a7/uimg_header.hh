#pragma once
#include <cstdint>

// This is the "legacy" (ie non-FIT) U-Boot image header
namespace BootImageDef
{

constexpr uint32_t IH_MAGIC = 0x27051956; /* Image Magic Number		*/
constexpr uint32_t IH_NMLEN = 32;		  /* Image Name Length		*/

//  Legacy format image header,
//  all data in network byte order (aka natural aka bigendian).
//  Taken from u-boot include/image.h
struct ImageHeader {
	uint32_t ih_magic;		   /* Image Header Magic Number	*/
	uint32_t ih_hcrc;		   /* Image Header CRC Checksum	*/
	uint32_t ih_time;		   /* Image Creation Timestamp	*/
	uint32_t ih_size;		   /* Image Data Size		*/
	uint32_t ih_load;		   /* Data	 Load  Address		*/
	uint32_t ih_ep;			   /* Entry Point Address		*/
	uint32_t ih_dcrc;		   /* Image Data CRC Checksum	*/
	uint8_t ih_os;			   /* Operating System		*/
	uint8_t ih_arch;		   /* CPU architecture		*/
	uint8_t ih_type;		   /* Image Type			*/
	uint8_t ih_comp;		   /* Compression Type		*/
	uint8_t ih_name[IH_NMLEN]; /* Image Name		*/
};

static_assert(sizeof(ImageHeader) == 64);

} // namespace BootImageDef
