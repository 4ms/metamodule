#!/usr/bin/env python3
"""Pack a binary into a self-extracting payload for the boot stub.

Output layout (all little-endian):
  0x00  u32 magic 'MMSX' (0x58534D4D)
  0x04  u32 uncompressed size
  0x08  u32 compressed size
  0x0C  u32 crc32 of the uncompressed data
  0x10  LZ4-block-format compressed data

The compressor emits standard LZ4 block format (greedy match search,
single-entry hash table, 64KB window) so the stream can be decoded by any
LZ4 block decoder, including the ~40-line one in stub.c.

The script decompresses its own output with an independent reference decoder
and byte-compares against the input, so a compressor bug cannot produce a
flashable-but-broken image.

Only python stdlib is used.
"""

import argparse
import struct
import sys
import zlib

MAGIC = 0x58534D4D  # 'MMSX'
HASH_LOG = 16
MINMATCH = 4
# LZ4 spec end-of-block rules:
#  - the last 5 bytes are always literals
#  - the last match must start at least 12 bytes before the end
MFLIMIT = 12
LASTLITERALS = 5


def lz4_compress(src: bytes) -> bytes:
    n = len(src)
    out = bytearray()
    append = out.append
    extend = out.extend

    if n == 0:
        return bytes(out)

    table = [-1] * (1 << HASH_LOG)
    shift = 32 - HASH_LOG

    def emit_sequence(anchor: int, i: int, mlen_minus4: int, offset: int):
        litlen = i - anchor
        tok_lit = 15 if litlen >= 15 else litlen
        tok_mat = 15 if mlen_minus4 >= 15 else mlen_minus4
        append((tok_lit << 4) | tok_mat)
        if litlen >= 15:
            rem = litlen - 15
            while rem >= 255:
                append(255)
                rem -= 255
            append(rem)
        extend(src[anchor:i])
        append(offset & 0xFF)
        append(offset >> 8)
        if mlen_minus4 >= 15:
            rem = mlen_minus4 - 15
            while rem >= 255:
                append(255)
                rem -= 255
            append(rem)

    i = 0
    anchor = 0
    mflimit = n - MFLIMIT
    matchlimit = n - LASTLITERALS
    search_count = 0

    while i < mflimit:
        v = src[i] | (src[i + 1] << 8) | (src[i + 2] << 16) | (src[i + 3] << 24)
        h = (v * 2654435761 & 0xFFFFFFFF) >> shift
        ref = table[h]
        table[h] = i

        if (
            ref >= 0
            and i - ref <= 0xFFFF
            and src[ref : ref + 4] == src[i : i + 4]
        ):
            # Extend the match, comparing chunks first for speed
            m = i + 4
            r = ref + 4
            while m + 64 <= matchlimit and src[m : m + 64] == src[r : r + 64]:
                m += 64
                r += 64
            while m < matchlimit and src[m] == src[r]:
                m += 1
                r += 1
            emit_sequence(anchor, i, (m - i) - MINMATCH, i - ref)
            i = m
            anchor = m
            search_count = 0
        else:
            # Accelerate over incompressible regions
            i += 1 + (search_count >> 6)
            search_count += 1

    # Final literals
    litlen = n - anchor
    tok_lit = 15 if litlen >= 15 else litlen
    append(tok_lit << 4)
    if litlen >= 15:
        rem = litlen - 15
        while rem >= 255:
            append(255)
            rem -= 255
        append(rem)
    extend(src[anchor:n])

    return bytes(out)


def lz4_decompress(comp: bytes, expected_size: int) -> bytes:
    """Independent reference decoder used to verify the compressor's output."""
    out = bytearray()
    i = 0
    n = len(comp)
    while i < n:
        token = comp[i]
        i += 1
        litlen = token >> 4
        if litlen == 15:
            while True:
                b = comp[i]
                i += 1
                litlen += b
                if b != 255:
                    break
        out += comp[i : i + litlen]
        i += litlen
        if i >= n:
            break  # last sequence has no match part
        offset = comp[i] | (comp[i + 1] << 8)
        i += 2
        if offset == 0:
            raise ValueError("corrupt stream: zero offset")
        mlen = (token & 0xF) + MINMATCH
        if (token & 0xF) == 15:
            while True:
                b = comp[i]
                i += 1
                mlen += b
                if b != 255:
                    break
        start = len(out) - offset
        if start < 0:
            raise ValueError("corrupt stream: offset before start")
        for k in range(mlen):  # byte-wise: matches may overlap the output head
            out.append(out[start + k])
    if len(out) != expected_size:
        raise ValueError(f"decompressed size {len(out)} != expected {expected_size}")
    return bytes(out)


def main():
    parser = argparse.ArgumentParser(description="LZ4-pack a firmware image for the self-extract stub")
    parser.add_argument("in_file")
    parser.add_argument("out_file")
    args = parser.parse_args()

    with open(args.in_file, "rb") as f:
        src = f.read()

    comp = lz4_compress(src)

    # Verify with the independent decoder before writing anything
    roundtrip = lz4_decompress(comp, len(src))
    if roundtrip != src:
        print("FATAL: LZ4 roundtrip verification failed", file=sys.stderr)
        sys.exit(1)

    crc = zlib.crc32(src) & 0xFFFFFFFF
    header = struct.pack("<IIII", MAGIC, len(src), len(comp), crc)

    with open(args.out_file, "wb") as f:
        f.write(header + comp)

    ratio = 100.0 * len(comp) / len(src)
    print(f"lz4_pack: {len(src)} -> {16 + len(comp)} bytes ({ratio:.1f}%), crc32 0x{crc:08x}")


if __name__ == "__main__":
    main()
