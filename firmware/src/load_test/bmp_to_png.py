#!/usr/bin/env python3
"""Convert the module-image BMPs produced by the firmware image generator to PNG.

The firmware's image generator (triggered by a `run_image_gen` file on the USB
drive) writes one 24-bit uncompressed BMP per module to:

    module-images/<brand>/<module>.bmp

This script walks that tree and writes a PNG next to each BMP (preserving the
brand subdirectories). It has no third-party dependencies — it parses the
specific BMP format the firmware emits and encodes PNG using only the standard
library (zlib + struct).

Examples:
    # Convert in place (PNGs written beside the BMPs):
    ./bmp_to_png.py module-images

    # Convert into a separate tree, mirroring the brand subdirs:
    ./bmp_to_png.py module-images --out module-images-png

    # Convert and delete the source BMPs afterward:
    ./bmp_to_png.py module-images --delete-bmp
"""
from __future__ import annotations

import argparse
import struct
import sys
import zlib
from pathlib import Path


class BmpError(Exception):
    pass


def decode_bmp(data: bytes) -> tuple[int, int, bytearray]:
    """Decode a 24-bit BI_RGB BMP into (width, height, rgb_top_down).

    Returns pixel data as top-down RGB rows (3 bytes/pixel), with no row
    padding.
    """
    if len(data) < 54 or data[0:2] != b"BM":
        raise BmpError("not a BMP file")

    pixel_offset = struct.unpack_from("<I", data, 10)[0]
    header_size = struct.unpack_from("<I", data, 14)[0]
    width = struct.unpack_from("<i", data, 18)[0]
    height_raw = struct.unpack_from("<i", data, 22)[0]
    planes = struct.unpack_from("<H", data, 26)[0]
    bpp = struct.unpack_from("<H", data, 28)[0]
    compression = struct.unpack_from("<I", data, 30)[0]

    if planes != 1:
        raise BmpError(f"unexpected plane count {planes}")
    if bpp != 24:
        raise BmpError(f"only 24-bit BMPs are supported (got {bpp}-bit)")
    if compression != 0:
        raise BmpError(f"only uncompressed (BI_RGB) BMPs are supported (got compression {compression})")
    if header_size < 40:
        raise BmpError(f"unexpected info header size {header_size}")

    width = abs(width)
    top_down = height_raw < 0  # negative height => rows stored top-to-bottom
    height = abs(height_raw)

    row_padded = ((width * 3 + 3) // 4) * 4
    needed = pixel_offset + row_padded * height
    if len(data) < needed:
        raise BmpError(f"truncated pixel data (have {len(data)}, need {needed})")

    out = bytearray()
    for out_y in range(height):
        # BMP rows are bottom-up unless height is negative. We want top-down.
        src_y = out_y if top_down else (height - 1 - out_y)
        off = pixel_offset + src_y * row_padded
        row = bytearray(data[off : off + width * 3])
        # BMP stores pixels as BGR; PNG wants RGB. Swapping byte 0 and byte 2 of
        # every triple converts between them. Extended-slice assignment is done
        # in C, so this is fast.
        row[0::3], row[2::3] = row[2::3], row[0::3]
        out += row

    return width, height, out


def _png_chunk(tag: bytes, payload: bytes) -> bytes:
    return (
        struct.pack(">I", len(payload))
        + tag
        + payload
        + struct.pack(">I", zlib.crc32(tag + payload) & 0xFFFFFFFF)
    )


def encode_png(width: int, height: int, rgb_top_down: bytes | bytearray) -> bytes:
    """Encode top-down RGB pixel data (3 bytes/pixel) as an 8-bit truecolor PNG."""
    stride = width * 3
    raw = bytearray()
    for y in range(height):
        raw.append(0)  # filter type 0 (None)
        raw += rgb_top_down[y * stride : (y + 1) * stride]

    ihdr = struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0)  # 8-bit, truecolor
    return (
        b"\x89PNG\r\n\x1a\n"
        + _png_chunk(b"IHDR", ihdr)
        + _png_chunk(b"IDAT", zlib.compress(bytes(raw), 9))
        + _png_chunk(b"IEND", b"")
    )


def convert_file(bmp_path: Path, png_path: Path) -> None:
    width, height, rgb = decode_bmp(bmp_path.read_bytes())
    png_path.parent.mkdir(parents=True, exist_ok=True)
    png_path.write_bytes(encode_png(width, height, rgb))


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("input", type=Path, help="directory to scan for .bmp files (e.g. module-images)")
    parser.add_argument(
        "--out",
        type=Path,
        default=None,
        help="output directory root (default: write each .png beside its .bmp)",
    )
    parser.add_argument("--delete-bmp", action="store_true", help="delete each source .bmp after a successful convert")
    parser.add_argument("-q", "--quiet", action="store_true", help="only print a final summary and any errors")
    args = parser.parse_args(argv)

    root: Path = args.input
    if not root.is_dir():
        print(f"error: '{root}' is not a directory", file=sys.stderr)
        return 2

    bmps = sorted(root.rglob("*.bmp"))
    if not bmps:
        print(f"No .bmp files found under '{root}'", file=sys.stderr)
        return 1

    converted = 0
    failed = 0
    for bmp in bmps:
        rel = bmp.relative_to(root)
        png = (args.out / rel if args.out else bmp).with_suffix(".png")
        try:
            convert_file(bmp, png)
        except (BmpError, OSError) as e:
            print(f"FAILED {bmp}: {e}", file=sys.stderr)
            failed += 1
            continue

        converted += 1
        if not args.quiet:
            print(f"{bmp} -> {png}")
        if args.delete_bmp:
            try:
                bmp.unlink()
            except OSError as e:
                print(f"warning: could not delete {bmp}: {e}", file=sys.stderr)

    print(f"Converted {converted} image(s)" + (f", {failed} failed" if failed else ""))
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
