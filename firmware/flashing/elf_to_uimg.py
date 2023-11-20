#!/usr/bin/env python3

import argparse
import logging

from elftools.elf.elffile import ELFFile
from uimg_header import create_uimg_header

class CoreType:
    A7 = 'A7'
    M4 = 'M4'

# These are in the form: A7 - M4 - size
memory_mappings = (
    (0x38000000, 0x00000000, 0x10000),
    (0x30000000, 0x10000000, 0x60000),
)


def get_images_for_elf(filename, *, destination, loader):
    with open(filename, "rb") as file:

        logger.info(f"Parsing {filename}")

        elf_file = ELFFile(file)
        output = bytearray()

        sections = [section for section in elf_file.iter_sections()]

        for segment in elf_file.iter_segments():

            contained_sections = [section for section in sections if segment.section_in_segment(section)]

            region_address = segment["p_vaddr"]
            region_size = segment["p_memsz"]
            write_size = segment["p_filesz"]

            if write_size > 0:
                logger.info("Include segment 0x{:08x} - 0x{:08x} (load size 0x{:08x})".format(region_address, region_address+region_size, write_size))

                for section in contained_sections:
                    logger.debug("Contains {} at 0x{:08x} - 0x{:08x} ".format(section.name, section.header.sh_addr, section.header.sh_addr + section.header.sh_size))
                
                payload = segment.data()
                name = "{}_0x{:08x}".format(destination, region_address)

                if destination != loader:
                    dest_col = 0 if destination == CoreType.A7 else 1
                    loader_col = 0 if loader == CoreType.A7 else 1
                    for mapping in memory_mappings:
                        if region_address >= mapping[dest_col] and region_address <= mapping[dest_col] + mapping[2]:
                            new_region_address = region_address - mapping[dest_col] + mapping[loader_col]
                            logging.debug("Remap 0x{:08x} -> 0x{:08x}".format(region_address, new_region_address))
                            region_address = new_region_address

                print("Creating {} at 0x{:08x} with size {}".format(name, region_address, write_size))
                header = create_uimg_header(payload, loadaddr=region_address, entryaddr=0, name=name)

                output = output + header + payload
                
            else:
                logger.debug("Skipping empty segment 0x{:08x} - 0x{:08x} (Sections: {})".format(region_address, region_address+region_size, ', '.join([s.name for s in contained_sections])))

        return output


if __name__ == "__main__":
    parser = argparse.ArgumentParser("Creat concatenated uimg from elf files")
    parser.add_argument("--a7", dest="a7_file", help="Input a7 elf file")
    parser.add_argument("--m4", dest="m4_file", help="Input m4 elf file")
    parser.add_argument("out_file", help="Output image file")
    parser.add_argument("--loader", help="Core to perform loading", default=CoreType.A7, type=str, choices=['A7', 'M4'])
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    logger = logging
    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    with open(args.out_file, "wb") as out_file:

        if args.a7_file:
            out_file.write(get_images_for_elf(args.a7_file, destination=CoreType.A7, loader=args.loader))

        if args.m4_file:
            out_file.write(get_images_for_elf(args.m4_file, destination=CoreType.M4, loader=args.loader))




            
            