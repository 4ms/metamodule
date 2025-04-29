#!/usr/bin/env python3

import argparse
import logging

from helpers import write_json, write_text
from pathlib import Path
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

def GetRequiredSymbolNames(file):
    needed_syms = []
    elf = ELFFile(file)
    mmsyms = elf.get_section_by_name(".symtab")
    if isinstance(mmsyms, SymbolTableSection):
        for i in range(mmsyms.num_symbols()):
            n = mmsyms.get_symbol(i).name
            l = mmsyms.get_symbol(i)['st_info']['bind']
            t = mmsyms.get_symbol(i)['st_info']['type']
            v = mmsyms.get_symbol(i)['st_other']['visibility']
            ndx = mmsyms.get_symbol(i)['st_shndx']
            if n != "" and l == "STB_GLOBAL" and t != "STT_NOTYPE" and ndx != 'SHN_UNDEF' and v == 'STV_DEFAULT':
                logging.debug(f"{i}: {n} {v}")
                needed_syms.append(n)
    return needed_syms

# These are symbols that are already in main.elf, but I don't know an easy way to find them
def GetLibcSymbols():
    libc_syms = [
         # These needed if plugin compiled with libc sources
         "malloc",
         "calloc",
         "realloc",
         "free",
         "_malloc_r",
         "_calloc_r",
         "_realloc_r",
         "_free_r",
         "_times_r",
         "memalign",

         "abort",
         "__assert_func",

         "_impure_ptr",
         "_impure_data",
         "__cxa_pure_virtual",

         "_exit",
         "_fini",
         "_getpid_r",
         "_open_r",
         "_close_r",
         "_fstat_r",
         "stat",
         "_isatty_r",
         "_write_r",
         "_kill_r",
         "_read_r",
         "_lseek_r",
         "_sbrk_r",
         "gettimeofday",
         "_gettimeofday",
         "_gettimeofday_r",

         "expm1l",
         "log1pl",

         "__atexit",
         "__aeabi_atexit",
         "__atexit_recursive_mutex",

         "_Z9get_ticksv",
    ]
    return libc_syms


if __name__ == "__main__":
    parser = argparse.ArgumentParser("Dump symbols that plugins might need")
    parser.add_argument("--objdir", required=True, action="append", help="Directory with .obj files with the symbols we want to make available to plugins")
    parser.add_argument("--objfile", required=False, action="append", help="Object file (.obj or .o) with the symbols we want to make available to plugins")
    parser.add_argument("--text-out", dest="text", help="file to output names of symbols")
    parser.add_argument("--json-out", dest="json", help="file to output names of symbols as json")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG, format='%(message)s')
    else:
        logging.basicConfig(level=logging.INFO, format='%(message)s')

    needed_syms = []

    if args.objfile:
        for obj_file in args.objfile:
            logging.debug("------")
            logging.debug(f"Looking for symbols in {obj_file}")
            with open(obj_file, "rb") as f:
                needed_syms += GetRequiredSymbolNames(f)

    for obj_dir in args.objdir:
        obj_files = Path(obj_dir).glob("**/*.obj")
        for obj_file in obj_files:
            logging.debug("------")
            logging.debug(f"Looking for symbols in {obj_file}")
            with open(obj_file, "rb") as f:
                needed_syms += GetRequiredSymbolNames(f)

    libc_syms = GetLibcSymbols()
    for s in libc_syms:
        if s in needed_syms:
            logging.info(f"Note: Manually given symbol {s} already found in objdir files, consider removing from GetLibcSymbols")
        else:
            needed_syms.append(s)

    # remove duplicates and sort
    needed_syms = list(set(needed_syms))
    needed_syms.sort()

    if args.json:
        write_json(args.json, needed_syms)

    if args.text:
        write_text(args.text, needed_syms)

