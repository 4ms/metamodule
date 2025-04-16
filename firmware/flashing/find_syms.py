#!/usr/bin/env python3

import argparse
import logging
from helpers import read_symbol_list, write_yaml
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

def GetAddressesOfSymbols(file, needed_syms):
    syms = {} 
    elf = ELFFile(file)
    symtab = elf.get_section_by_name(".symtab")
    if isinstance(symtab, SymbolTableSection):
        for i in range(symtab.num_symbols()):
            s = symtab.get_symbol(i)
            if s.name in needed_syms:
                syms[s.name] = s['st_value']
                logging.debug(f"{hex(s['st_value'])}\t{s.name}")
                needed_syms.remove(s.name)

    if len(needed_syms) > 0:
        logging.error("****************************************************************")
        for n in needed_syms:
            logging.error(f"** ERROR: Symbol not found in main.elf: {n} **")
        logging.error("****************************************************************")

    if len(needed_syms) == 0:
        logging.info("_____________________________________")
        logging.info("| All API symbols found in main.elf |")
        logging.info("_____________________________________")

    return syms

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Find symbol addresses in an elf file")
    parser.add_argument("--symbols", required=True, help="Name of file with list of symbols names to find (json or plain text)")
    parser.add_argument("--elf", required=True, help="Fully linked elf file to be scanned for the API symbols (main.elf)")
    parser.add_argument("--out", required=True, help="Name of file to save the output table (yaml format)")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG, format='%(message)s')
    else:
        logging.basicConfig(level=logging.INFO, format='%(message)s')

    logging.debug(f"Looking for symbols in {args.symbols}")
    needed_syms = read_symbol_list(args.symbols)

    logging.debug("API requires symbols:")
    for sym in needed_syms:
        logging.debug(sym)


    logging.debug("Finding symbol addresses")
    with open(args.elf, "rb") as f:
        syms = GetAddressesOfSymbols(f, needed_syms)

    logging.debug("Writing symbol table")
    write_yaml(args.out, syms)


