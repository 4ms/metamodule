#!/usr/bin/env python3
"""Pack an MP2 A35 ELF into the payload of the self-extract stub (stub.c).

Each loadable segment of the ELF that has data (the code and constants, and .data) is LZ4-compressed
on its own, so the stub can unpack it straight to where it's linked.

Output layout (all little-endian):
  0x00  u32 magic 'MM2X' (0x58324D4D)
  0x04  u32 number of segments
  0x08  u64 entry point
  then, for each segment, at an 8-byte boundary:
  0x00  u64 load address
  0x08  u32 uncompressed size
  0x0C  u32 compressed size
  0x10  u32 crc32 of the uncompressed data
  0x14  u32 0
  0x18  LZ4-block-format compressed data

The compressor is MP1's (../selfextract/lz4_pack.py), which also checks each segment by
decompressing it with an independent decoder.
"""

import argparse
import struct
import sys
import zlib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "selfextract"))

from elftools.elf.elffile import ELFFile
from lz4_pack import lz4_compress, lz4_decompress

MAGIC = 0x58324D4D  # 'MM2X'


def main():
    parser = argparse.ArgumentParser(description="Pack an MP2 A35 ELF for the self-extract stub")
    parser.add_argument("elf_file")
    parser.add_argument("out_file")
    parser.add_argument(
        "--avoid",
        nargs=2,
        metavar=("START_SYMBOL", "END_SYMBOL"),
        help="Symbols in the ELF for the memory the stub itself is in: no segment may be unpacked there",
    )
    args = parser.parse_args()

    segments = []
    with open(args.elf_file, "rb") as f:
        elf = ELFFile(f)
        entry = elf.header.e_entry
        for seg in elf.iter_segments():
            if seg["p_type"] == "PT_LOAD" and seg["p_filesz"] > 0:
                segments.append((seg["p_paddr"], seg.data()))

        avoid = None
        if args.avoid:
            symtab = elf.get_section_by_name(".symtab")
            avoid = [symtab.get_symbol_by_name(name)[0]["st_value"] for name in args.avoid]

    if not any(load <= entry < load + len(data) for load, data in segments):
        sys.exit(f"FATAL: entry point 0x{entry:x} is not in a segment of {args.elf_file}")

    out = bytearray(struct.pack("<IIQ", MAGIC, len(segments), entry))
    total = 0

    for load, data in segments:
        end = load + len(data)
        if avoid and load < avoid[1] and end > avoid[0]:
            sys.exit(
                f"FATAL: segment 0x{load:x}-0x{end:x} overlaps the boot image "
                f"(0x{avoid[0]:x}-0x{avoid[1]:x}): the stub would overwrite itself"
            )

        comp = lz4_compress(data)
        if lz4_decompress(comp, len(data)) != data:
            sys.exit("FATAL: LZ4 roundtrip verification failed")

        out += b"\0" * (-len(out) % 8)
        out += struct.pack("<QIIII", load, len(data), len(comp), zlib.crc32(data) & 0xFFFFFFFF, 0)
        out += comp
        total += len(data)
        print(f"pack_elf: 0x{load:08x}-0x{end:08x}: {len(data)} -> {len(comp)} bytes")

    with open(args.out_file, "wb") as f:
        f.write(out)

    print(f"pack_elf: {total} -> {len(out)} bytes ({100.0 * len(out) / total:.1f}%), entry 0x{entry:x}")


if __name__ == "__main__":
    main()
