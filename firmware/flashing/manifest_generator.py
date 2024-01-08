#!/usr/bin/env python3

import argparse
import logging
import json
import os
import hashlib

ManifestFormatVersion = 1


def process_file(filename, imagetype):

    with open(filename, 'rb') as file:

        entry = dict()

        entry["filename"] = os.path.basename(filename)
        entry["type"] = imagetype
        entry["filesize"] = os.stat(filename).st_size
        entry["md5"] = hashlib.md5(file.read()).hexdigest()

        return entry

def parse_file_version(version):
    """ Convert a string like: firmware-v0.6.2-278-g52dfd038
        Or: v1.2.3
        Or: 2.1.5
        Into: 0.6.2
    """
    vsplit = version.split("-")
    if len(vsplit) > 1:
        v = vsplit[1]
    else:
        v = vsplit[0]

    v = v.strip("v")
    return v

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Generate firmware update manifest json file")
    parser.add_argument("--app", dest="app_file", help="Input application uimg file")
    parser.add_argument("--version", dest="version", help="Version string e.g. \"1.2.3\"")
    parser.add_argument("out_file", help="Output json file")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    
    j = {'version': ManifestFormatVersion}

    version = parse_file_version(args.version)

    j["files"] = []
    j["files"].append(process_file(args.app_file, "app", version))

    with open(args.out_file, "w+") as out_file:
        data_json = json.dumps(j, indent=4)
        out_file.write(data_json)

