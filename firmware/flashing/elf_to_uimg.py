#!/usr/bin/env python3

import argparse
import logging

from elftools.elf.elffile import ELFFile
from uimg_header import create_uimg_header, UImg

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
        target_areas = []

        sections = [section for section in elf_file.iter_sections()]

        for segment in elf_file.iter_segments():

            contained_sections = [section for section in sections if segment.section_in_segment(section)]

            # This is the location where everything will end up just before main()
            vma = segment["p_vaddr"]
            vma_size = segment["p_memsz"]

            # This is the location of the initialization data the for the region above
            # Can be smaller than above if this segments contains sections that are not initialized
            lma = segment["p_paddr"]
            lma_size = segment["p_filesz"]

            # Check if there is any initialization data to load at all
            if lma_size > 0:
                logger.info("Include segment (VMA: 0x{:08x}-0x{:08x} LMA: 0x{:08x}-0x{:08x})".format(vma, vma+vma_size, lma, lma+lma_size))

                for section in contained_sections:
                    logger.debug("Contains {} at 0x{:08x} - 0x{:08x} ".format(section.name, section.header.sh_addr, section.header.sh_addr + section.header.sh_size))
                
                payload = segment.data()
                sectnames = "+".join([section.name for section in contained_sections])[:32]
                name = "{}_{}".format(destination, sectnames)

                # Default settings for type and entry point that should be ignored by the bootloader
                type = UImg.image_type_copro if destination == CoreType.M4 else UImg.image_type_firmware
                entry_point = 0

                # The core that does the loading has different memory mappings than the core that executes
                # Remap relevant sections from what is given in the elf file to where the loader core has that mapped
                if destination != loader:
                    dest_col = 0 if destination == CoreType.A7 else 1
                    loader_col = 0 if loader == CoreType.A7 else 1
                    for mapping in memory_mappings:
                        if lma >= mapping[dest_col] and lma <= mapping[dest_col] + mapping[2]:
                            new_lma = lma - mapping[dest_col] + mapping[loader_col]
                            logger.debug("Remap 0x{:08x} -> 0x{:08x}".format(lma, new_lma))
                            lma = new_lma

                # Define if this image can be booted. This includes
                # - It is for the A7 core (since that one always needs to start execution)
                # - It contains the entry point for the whole elf file
                if destination == CoreType.A7:
                    image_entry_point = elf_file.header.e_entry
                    if image_entry_point >= vma and image_entry_point <= vma + vma_size:

                        # Set the file's entry point and assign a special image type
                        type = UImg.image_type_kernel
                        entry_point = image_entry_point

                print("Creating {} at 0x{:08x} with size {}".format(name, lma, lma_size))
                if type == UImg.image_type_kernel:
                    print("Contains entry point at 0x{:08x}".format(entry_point))

                header = create_uimg_header(payload, loadaddr=lma, entryaddr=entry_point, name=name, type=type)

                # Just concatenate generated images
                output = output + header + payload

                # Remember target area for overlap check later on
                target_areas.append((lma, lma + len(payload)))
                
            else:
                logger.debug("Skipping empty segment (VMA: 0x{:08x}-0x{:08x} Sections: {})".format(vma, vma+vma_size, ', '.join([s.name for s in contained_sections])))

        return output, target_areas


if __name__ == "__main__":
    parser = argparse.ArgumentParser("Create concatenated uimg from elf files")
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

        target_areas = []

        if args.a7_file:
            output, areas = get_images_for_elf(args.a7_file, destination=CoreType.A7, loader=args.loader)
            out_file.write(output)
            target_areas.extend(areas)

        if args.m4_file:
            output, areas = get_images_for_elf(args.m4_file, destination=CoreType.M4, loader=args.loader)
            out_file.write(output)
            target_areas.extend(areas)

        # Check if any sections overlap
        for i in range(len(target_areas)):
            for j in range(len(target_areas)):
                if i != j:
                    a = target_areas[i]
                    b = target_areas[j]
                    if (a[1] >= b[0] and a[1] <= b[1]) or (b[1] >= a[0] and b[1] <= a[1]):
                        raise ValueError("Sections 0x{:08x}-0x{:08x} and 0x{:08x}-0x{:08x} overlap".format(a[0], a[1], b[0], b[1]))




            
            
