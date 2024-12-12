#!/usr/bin/env python3
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Append a null character to a file")
    parser.add_argument("--in", dest="infile", required=True, help="input file")
    parser.add_argument("--out", dest="outfile", required=True, help="output file")
    args = parser.parse_args()

    with open(args.infile, "rb") as f:
        data = f.read()


    with open(args.outfile, "wb") as f:
        f.write(data)
        f.write(bytes([0,0,0,0]))

