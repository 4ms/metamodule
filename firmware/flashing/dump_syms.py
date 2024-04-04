#!/usr/bin/env python3

import argparse
import logging

from pathlib import Path
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

import json

def GetRequiredSymbolNames(file):
    needed_syms = []
    elf = ELFFile(file)
    mmsyms = elf.get_section_by_name(".symtab")
    if isinstance(mmsyms, SymbolTableSection):
        for i in range(mmsyms.num_symbols()):
            n = mmsyms.get_symbol(i).name
            l = mmsyms.get_symbol(i)['st_info']['bind']
            t = mmsyms.get_symbol(i)['st_info']['type']
            ndx = mmsyms.get_symbol(i)['st_shndx']
            if n != "" and l == "STB_GLOBAL" and t != "STT_NOTYPE" and ndx != 'SHN_UNDEF':
                logging.debug(f"{i}: {n}")
                needed_syms.append(n)
    return needed_syms

def GetPluginRequiredSymbolNames(file):
    needed_syms = []
    elf = ELFFile(file)
    mmsyms = elf.get_section_by_name(".symtab")
    if isinstance(mmsyms, SymbolTableSection):
        for i in range(mmsyms.num_symbols()):
            n = mmsyms.get_symbol(i).name
            l = mmsyms.get_symbol(i)['st_info']['bind']
            t = mmsyms.get_symbol(i)['st_info']['type']
            ndx = mmsyms.get_symbol(i)['st_shndx']
            if n != "" and l == "STB_GLOBAL" and ndx == 'SHN_UNDEF':
                logging.debug(f"{i}: bind:{l} type:{t} {n}")
                needed_syms.append(n)
    return needed_syms


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

    for n in needed_syms:
        logging.warning(f"** WARNING: Symbol not found in main.elf: {n} **")

    return syms

def GetLibcSymbols():
    libc_syms = [
         "abort",
         "ceil",
         "cos",
         "cosf",
         "exp",
         "expf",
         "fabs",
         "floor",
         "floorf",
         "fmaxf",
         "fminf",
         "fmod",
         "log2f",
         "logf",
         "memcmp",
         "memcpy",
         "memmove",
         "memset",
         "memchr",
         "pow",
         "powf",
         "roundf",
         "sin",
         "sinf",
         "sqrt",
         "sqrtf",
         "strlen",
         "tanf",
         "tanh",
         "printf",
         "puts",
         "free",
         "__aeabi_atexit",
         "__cxa_pure_virtual",

         "_Znwj", # operator new(unsigned int)
         "_Znaj", # operator new[](unsigned int)
         "_ZdlPv", # operator delete(void*)
         "_ZdaPv", # operator delete[](void*)
         "_ZdlPvj", # operator delete(void*, unsigned int)

         "_ZSt20__throw_length_errorPKc", #std::__throw_length_error(char const*)
         "_ZSt19__throw_logic_errorPKc", #std::__throw_logic_error(char const*)
         "_ZSt17__throw_bad_allocv", #
         "_ZSt28__throw_bad_array_new_lengthv", #
         "_ZSt24__throw_out_of_range_fmtPKcz",

         "_ZNSt19_Sp_make_shared_tag5_S_eqERKSt9type_info",
         "_ZNSt8__detail15_List_node_base7_M_hookEPS0_",

         # Not found, replaced with an empty function
         "_ZNSaIcEC1Ev", # std::allocator<char>::allocator()
         "_ZNSaIcED1Ev", # std::allocator<char>::~allocator()
         "_ZNSaIcED2Ev", # std::allocator<char>::~allocator() ? somehow different?
         "_ZNSaIcEC1ERKS_", # std::allocator<char>::allocator(std::allocator<char> const&)
         "_ZNSaIcEC2ERKS_", # std::allocator<char>::allocator(std::allocator<char> const&) 

         "json_integer_value",
         "json_object",
         "json_object_set_new",
         "json_object_get",
         "json_true",
         "json_false",
         "json_integer",
         "json_array_insert_new",
         "json_array_get",
         "json_number_value",
         "json_dumps",
    ]
    return libc_syms


def write_binary(outfile, syms):
    strtab = bytearray()
    symtab = bytearray()
    for sym, addr in syms.items():
        offset = len(strtab)
        symtab += bytearray(addr.to_bytes(4, "little"))
        symtab += bytearray(offset.to_bytes(4, "little"))

        strtab += bytearray(sym.encode())
        strtab += bytearray(b'\x00')

    magic = bytearray("SYMS".encode())
    
    bin = bytearray()
    bin += magic
    bin += bytearray(len(symtab).to_bytes(4, 'little'))
    bin += bytearray(len(strtab).to_bytes(4, 'little'))
    bin += symtab
    bin += strtab

    with open(outfile, "wb") as f:
        f.write(bin)


def write_json(outfile, syms):
    data = json.dumps(syms)
    with open(outfile, "w") as f:
        f.write(data)


def write_yaml(outfile, syms):
    data = "Symbols:\n"
    for sym, addr in syms.items():
        data += f"  - Name: {sym}\n"
        # data += f"    Hash: {elfhash(sym)}\n"
        data += f"    Addr: {hex(addr)}\n"

    with open(outfile, "w") as f:
        f.write(data)

        # Pad so that data size is aligned to 4 bytes
        padding = len(data) % 4
        f.write("\x00" * padding)



def write_header(outfile, syms):
    symlist = """
#pragma once
#include "host_symbol.hh"
#include <array>

static constexpr inline auto HostSymbols = std::to_array<ElfFile::HostSymbol>({
"""
    for sym, addr in syms.items():
        symlist+= f"""{{"{sym}", 0, {hex(addr)}}},
"""

    symlist += """
});
    """
    with open(outfile, "w") as f:
        f.write(symlist)



if __name__ == "__main__":
    parser = argparse.ArgumentParser("Dump symbols that plugins might need")
    parser.add_argument("--objdir", action="append", help="Object dir with .obj files with the symbols we want to make available to plugins (i.e. VCV_module_wrapper.cc.obj)")
    parser.add_argument("--elf", help="Fully linked elf file with addresses of all symbols (main.elf)")
    parser.add_argument("--plugin", action="append", help="Path to sample plugin .so file to test if all symbols will be resolved")
    parser.add_argument("--header", help="output c++ header file")
    parser.add_argument("--bin", help="output binary")
    parser.add_argument("--json", help="output json")
    parser.add_argument("--yaml", help="output yaml")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG, format='%(message)s')
    else:
        logging.basicConfig(level=logging.INFO, format='%(message)s')

    needed_syms = []

    for obj_dir in args.objdir:
        obj_files = Path(obj_dir).glob("**/*.obj")
        for obj_file in obj_files:
            logging.info("------")
            logging.info(f"Looking for symbols in {obj_file}")
            with open(obj_file, "rb") as f:
                needed_syms += GetRequiredSymbolNames(f)

    if args.plugin:
        for plugin in args.plugin:
            logging.info("------")
            logging.info(f"Checking if symbols in {plugin} would be resolved")
            with open(plugin, "rb") as f:
                needed_syms += GetPluginRequiredSymbolNames(f)


    libc_syms = GetLibcSymbols()
    for s in libc_syms:
        if s in needed_syms:
            logging.debug(f"Manually given symbol {s} already requested")
        else:
            needed_syms.append(s)

    # needed_syms += GetLibcSymbols()

    # remove duplicates
    needed_syms = list(set(needed_syms))

    logging.debug("------")
    logging.debug("Finding symbol addresses:")

    with open(args.elf, "rb") as f:
        syms = GetAddressesOfSymbols(f, needed_syms)


    if args.header:
        write_header(args.header, syms)

    if args.bin:
        write_binary(args.bin, syms)

    if args.json:
        write_json(args.json, syms)

    if args.yaml:
        write_yaml(args.yaml, syms)


