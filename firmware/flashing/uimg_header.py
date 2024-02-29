#!/usr/bin/env python3

import struct
import time
import zlib
import argparse

# U-Boot compatible "legacy" image header
# Defined by U-Boot in u-boot repo: https://github.com/u-boot/u-boot/blob/master/include/image.h

class UImg:
    magic = 0x27051956       

    os_linux = 5             # U-Boot uses this for Linux OS images
    os_uboot = 17            # U-Boot uses this for SSBL images

    arch_arm = 2

    image_type_kernel = 2    # U-Boot uses this for Linux OS images
    image_type_firmware = 5  # U-Boot uses this for SSBL images
    image_type_copro = 40

    compress_none = 0        # MP1-Boot only supports uncompressed kernels, for now
    # compress_gzip = 1
    # compress_bzip2 = 2


def create_uimg_header(payload, *, loadaddr, entryaddr, name, type):

    image_name = name.encode("ascii")

    # These are the choices for some options in the U-Boot header
    # MP1-Boot ignores these, but if you're using this script with
    # U-Boot, then it might matter:
    os = UImg.os_linux
    compress = UImg.compress_none
    arch = UImg.arch_arm

    # Force payload alignment
    alignment = len(payload) % 4
    while alignment > 0:
        payload += b'\x00'
        alignment -= 1

    # Calculate some header entries:
    header_size = 64
    datalen = len(payload) + header_size
    tmstamp = int(time.time())
    data_crc = zlib.crc32(payload)

    # To calc the header CRC, we generate a header with the CRC zero'ed out.
    # Then we calc the CRC of that, add fill the CRC value back in
    header_no_crc = struct.pack(">IIIIIIIbbbb32s",  # BigEndian: 4-byte ints * 7, bytes * 4, 32-byte string
        UImg.magic,                                 # Image Header Magic Number	
        0,                                          # Placeholder for header CRC
        tmstamp,                                    # Image Creation Timestamp	
        datalen,                                    # Image Data Size		
        loadaddr,                                   # Data Load Address		
        entryaddr,                                  # Entry Point Address		
        data_crc,                                   # Image Data CRC Checksum	
        os,                                         # Operating System		
        arch,                                       # CPU architecture		
        type,                                       # Image Type			
        compress,                                   # Compression Type		
        image_name,                                 # Image Name		
        )

    # Calculate and set header checksum
    hcrc = struct.pack(">I", zlib.crc32(header_no_crc))
    header = bytearray(header_no_crc)
    header[4:8] = hcrc

    return header, payload


if __name__ == "__main__":

    parser = argparse.ArgumentParser("Creat uimg from binary file")
    parser.add_argument("binary_file", help="Input binary file")
    parser.add_argument("image_file", help="Output image file")
    parser.add_argument("--load_addr", help="Address to load binary file to", type=lambda x: int(x,0), default=0xC2000040)
    parser.add_argument("--entry_point_offset", help="Entry point of the binary file", type=lambda x: int(x,0), default=0)
    parser.add_argument("--bootable", help="Can this image be used to boot (by jumping to entry offset)?", action='store_true')
    parser.add_argument("--name", help="Encoded name of the image", type=str, default="stm32mp1-baremetal image")
    args = parser.parse_args()


    with open(args.binary_file, "rb") as bin_file:

        payload = bin_file.read()

        header, payload = create_uimg_header(
                    payload,
                    loadaddr=args.load_addr,
                    entryaddr=args.load_addr + args.entry_point_offset,
                    name=args.name,
                    type=UImg.image_type_kernel if args.bootable else UImg.image_type_firmware
                    )

        with open(args.image_file, "wb") as uimg_file:
            uimg_file.write(header + payload)
