#pragma once
#include "pr_dbg.hh"
#include <cstdint>

// This is the "legacy" (ie non-FIT) U-Boot image header
namespace BootImageDef
{

constexpr uint32_t IH_MAGIC = 0x27051956;	 /* Image Magic Number		*/
constexpr uint32_t IH_MAGIC_BE = 0x56190527; /* Image Magic Number (big endian)		*/
constexpr uint32_t IH_NMLEN = 32;			 /* Image Name Length		*/

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

inline uint32_t be_to_le(uint32_t x) {
	return (((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >> 8) | ((x & 0x0000ff00) << 8) | ((x & 0x000000ff) << 24));
}

inline void debug_print_raw_header(BootImageDef::ImageHeader const &header) {
	pr_dbg("Raw header (big-endian):\n");
	pr_dbg("  ih_magic: %08x\n", header.ih_magic);
	pr_dbg("  ih_hcrc:  %08x\n", header.ih_hcrc);
	pr_dbg("  ih_time:  %08x\n", header.ih_time);
	pr_dbg("  ih_size:  %08x\n", header.ih_size);
	pr_dbg("  ih_load:  %08x\n", header.ih_load);
	pr_dbg("  ih_ep:    %08x\n", header.ih_ep);
	pr_dbg("  ih_dcrc:  %08x\n", header.ih_dcrc);
	pr_dbg("  ih_os:    %08x\n", header.ih_os);
	pr_dbg("  ih_arch:  %08x\n", header.ih_arch);
	pr_dbg("  ih_type:  %08x\n", header.ih_type);
	pr_dbg("  ih_comp:  %08x\n", header.ih_comp);
	pr_dbg("  ih_name:  %.32s\n", header.ih_name);
}

} // namespace BootImageDef
