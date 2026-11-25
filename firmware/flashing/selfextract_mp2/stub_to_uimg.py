#!/usr/bin/env python3
"""Make the image TF-A BL2 loads from the self-extract stub's ELF: the stub (and its payload), after
a uimg header that says where to load it and where to start it."""

import argparse
import struct
import sys
import time
import zlib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from elftools.elf.elffile import ELFFile
from uimg_header import UImg


def uimg_header(payload, load, entry, name):
    """TF-A's loader (stm32mp_load_baremetal_app) takes the size as the payload's, without the
    header. (MP1's images, made by uimg_header.py, include the header in it.)"""

    def pack(header_crc):
        return struct.pack(
            ">IIIIIIIbbbb32s",
            UImg.magic,
            header_crc,
            int(time.time()),
            len(payload),
            load,
            entry,
            zlib.crc32(payload),
            UImg.os_linux,
            UImg.arch_arm,
            UImg.image_type_kernel,
            UImg.compress_none,
            name.encode("ascii"),
        )

    return pack(zlib.crc32(pack(0)))


def main():
    parser = argparse.ArgumentParser(description="Make the MP2 boot image from the self-extract stub")
    parser.add_argument("elf_file")
    parser.add_argument("out_file")
    args = parser.parse_args()

    with open(args.elf_file, "rb") as f:
        elf = ELFFile(f)
        entry = elf.header.e_entry
        segments = [s for s in elf.iter_segments() if s["p_type"] == "PT_LOAD" and s["p_filesz"] > 0]
        if len(segments) != 1:
            sys.exit(f"FATAL: the stub must be one segment (it has {len(segments)})")
        load = segments[0]["p_paddr"]
        payload = segments[0].data()

    with open(args.out_file, "wb") as f:
        f.write(uimg_header(payload, load, entry, "MetaModule MP2") + payload)

    print(f"stub_to_uimg: {len(payload)} bytes, load 0x{load:x}, entry 0x{entry:x}")


if __name__ == "__main__":
    main()
