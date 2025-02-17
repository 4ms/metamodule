#!/usr/bin/env python3

import argparse
import logging
import json
import os
import hashlib
import re
import shutil
import zlib

ManifestFormatVersion = 1


def process_file(dest_dir, filename, imagetype, *, name=None, address=None, compressed=False):

    with open(filename, 'rb') as file:

        entry = dict()

        entry["type"]     = imagetype
        entry["md5"]      = hashlib.md5(file.read()).hexdigest()
        entry["address"]  = int(address)

        if name is not None:
            entry["name"] = name

        if not compressed:
            entry["filename"] = os.path.basename(filename)
            entry["filesize"] = os.stat(filename).st_size

            try:
                shutil.copyfile(filename, os.path.join(dest_dir, entry["filename"]))
            except shutil.SameFileError:
                pass
        else:
            entry["filename"] = os.path.basename(filename) + ".gz"
            entry["uncompressed_size"] = os.stat(filename).st_size

            with open(filename, "rb") as orig_file:
                with open(os.path.join(dest_dir, entry["filename"]), "wb") as dest_file:

                    # use level 9 as in esptool, can probably be changed
                    compressed_data = zlib.compress(orig_file.read(), level=9)
                    dest_file.write(compressed_data)

                    entry["filesize"] = len(compressed_data)



        return entry

def parse_file_version(version):
    """ Convert a string like: firmware-v0.6.2-278-g52dfd038
        Or: v1.2.3
        Or: 2.1.5
        Into: 0.6.2
    """
    
    match = re.match(r".*(?P<major>[0-9]+)\.(?P<minor>[0-9]+)\.(?P<revision>[0-9]+).*", version)

    if match is None:
        raise ValueError(f"'{version}' does not contain a valid version")

    result = match.groupdict()

    for key,value in result.items():
        result[key] = int(value)

    return result
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser("Generate firmware update manifest json file")
    parser.add_argument("--app", dest="app_file", help="Input application uimg file")
    parser.add_argument("--fsbl", dest="fsbl_file", help="First stage bootloader")
    parser.add_argument("--dfu", dest="dfu_file", help="DFU bootloader")
    parser.add_argument("--assets", dest="assets_file", help="Assets filesystem image")
    parser.add_argument("--wifi_bootloader", dest="wifi_bl_file", help="Wifi bootloader binary")
    parser.add_argument("--wifi_application", dest="wifi_app_file", help="Wifi application binary")
    parser.add_argument("--wifi_filesystem", dest="wifi_fs_file", help="Wifi filesystem image")
    parser.add_argument("--version", dest="version", help="Version string e.g. \"1.2.3\"")
    parser.add_argument("out_file", help="Output json file")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    destination_dir = os.path.dirname(args.out_file)
    os.makedirs(destination_dir, exist_ok=True)

    j = {'version': ManifestFormatVersion, 'files': []}

    if args.version:
        j["metadata"] = {'version': parse_file_version(args.version)}

    if args.fsbl_file:
        j["files"].append(process_file(destination_dir, args.fsbl_file, "app", name="FSBL1", address=0x0))
        j["files"].append(process_file(destination_dir, args.fsbl_file, "app", name="FSBL2", address=0x040000))

    if args.dfu_file:
        j["files"].append(process_file(destination_dir, args.dfu_file, "app", name="DFU", address=0x050000))

    if args.app_file:
        j["files"].append(process_file(destination_dir, args.app_file, "app", name="Main App", address=0x080000))

    if args.assets_file:
        j["files"].append(process_file(destination_dir, args.assets_file, "app", name="Assets", address=0xa00000))

    if args.wifi_fs_file:
        j["files"].append(process_file(destination_dir, args.wifi_fs_file, "wifi", name="Wifi Filesystem", address=0x200000, compressed=True))

    if args.wifi_bl_file:
        j["files"].append(process_file(destination_dir, args.wifi_bl_file, "wifi", name="Wifi Bootloader", address=0x0))

    if args.wifi_app_file:
        j["files"].append(process_file(destination_dir, args.wifi_app_file, "wifi", name="Wifi Application", address=0x10000))

    with open(args.out_file, "w+") as out_file:
        data_json = json.dumps(j, indent=4)
        out_file.write(data_json)

