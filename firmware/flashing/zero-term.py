#!/usr/bin/env python3
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Append a null character to a file")
    parser.add_argument("--in", dest="infile", required=True, help="input file")
    parser.add_argument("--out", dest="outfile", required=True, help="output file")
    parser.add_argument("--pad-to", dest="pad_to", type=lambda x: int(x, 0), help="pad the output with zeros to this size (bytes)")
    args = parser.parse_args()

    with open(args.infile, "rb") as f:
        data = f.read()

    data += bytes([0,0,0,0])
    if args.pad_to is not None:
        if len(data) > args.pad_to:
            raise SystemExit(f"ERROR: {args.infile} is {len(data)} bytes, more than {args.pad_to}")
        data += bytes(args.pad_to - len(data))

    with open(args.outfile, "wb") as f:
        f.write(data)

