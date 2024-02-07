#!/usr/bin/env python3

import argparse
import logging

from pathlib import Path
from elftools.elf.elffile import ELFFile

def GetRequiredSymbolNames(file):
    needed_syms = []
    elf = ELFFile(file)
    mmsyms = elf.get_section_by_name(".symtab")
    if mmsyms is not None:
        for i in range(mmsyms.num_symbols()):
            n = mmsyms.get_symbol(i).name
            l = mmsyms.get_symbol(i)['st_info']['bind']
            t = mmsyms.get_symbol(i)['st_info']['type']
            ndx = mmsyms.get_symbol(i)['st_shndx']
            if n != "" and l == "STB_GLOBAL" and t != "STT_NOTYPE" and ndx != 'SHN_UNDEF':
                logging.debug(f"{i}: {n}")
                needed_syms.append(n)
    return needed_syms


def GetAddressesOfSymbols(file, needed_syms):
    syms = []
    elf = ELFFile(file)
    symtab = elf.get_section_by_name(".symtab")
    for i in range(symtab.num_symbols()):
        s = symtab.get_symbol(i)
        if s.name in needed_syms:
            syms.append({s.name: s['st_value']})
            logging.debug(f"{hex(s['st_value'])}\t{s.name}")
            needed_syms.remove(s.name)

    for n in needed_syms:
        logging.warning(f"** WARNING: Symbol not found: {n} **")
    return syms


if __name__ == "__main__":
    parser = argparse.ArgumentParser("Dump symbols that plugins might need")
    parser.add_argument("--objdir", help="Object dir with .obj files with the symbols we neeed (VCV_module_wrapper.cc.obj)")
    parser.add_argument("--elf", help="Fully linked elf file with addresses of all symbols (main.elf)")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG, format='%(message)s')
    else:
        logging.basicConfig(level=logging.WARNING, format='%(message)s')

    needed_syms = []
    obj_files = Path(args.objdir).glob("*.obj")
    for obj_file in obj_files:
        print(f"Looking for symbols in {obj_file}")
        with open(obj_file, "rb") as f:
            needed_syms += GetRequiredSymbolNames(f)

    # objfile = "../build/mp1corea7/medium/main.elf"
    logging.debug("Finding symbol addresses:")
    with open(args.elf, "rb") as f:
        syms = GetAddressesOfSymbols(f, needed_syms)
        
