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
    syms = {} 
    elf = ELFFile(file)
    symtab = elf.get_section_by_name(".symtab")
    for i in range(symtab.num_symbols()):
        s = symtab.get_symbol(i)
        if s.name in needed_syms:
            syms[s.name] = s['st_value']
            logging.debug(f"{hex(s['st_value'])}\t{s.name}")
            needed_syms.remove(s.name)

    for n in needed_syms:
        logging.warning(f"** WARNING: Symbol not found: {n} **")

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
         "__aeabi_atexit",
         "__cxa_pure_virtual",
         "_ZNSaIcEC1Ev", # std::allocator<char>::allocator()
         "_ZNSaIcED1Ev", # std::allocator<char>::~allocator()
         "_ZNSaIcED2Ev", # std::allocator<char>::~allocator() ? somehow different?
         "_ZNSaIcEC1ERKS_", # std::allocator<char>::allocator(std::allocator<char> const&)
         "_ZNSaIcEC2ERKS_", # std::allocator<char>::allocator(std::allocator<char> const&) ? somehow different?

         "_Znwj", # operator new(unsigned int)
         "_Znaj", # operator new[](unsigned int)
         "_ZdlPv", # operator delete(void*)
         "_ZdaPv", # operator delete[](void*)
         "_ZdlPvj", # operator delete(void*, unsigned int)

         "_ZSt20__throw_length_errorPKc", #std::__throw_length_error(char const*)
         "_ZSt19__throw_logic_errorPKc", #std::__throw_logic_error(char const*)
         "_ZSt17__throw_bad_allocv", #
         "_ZSt28__throw_bad_array_new_lengthv", #

         "pffft_new_setup",
         "pffft_aligned_free",
         "pffft_transform",
         "pffft_destroy_setup",
         "pffft_aligned_malloc",
         "pffft_zconvolve_accumulate",

         "json_integer_value",
         "json_object",
         "json_object_set_new",
         "json_object_get",
         "json_true",
         "json_false",
         "json_integer",

         "_ZN10MetaModule13ModuleFactory5infosE",
         "_ZTV16VCVModuleWrapper",
         "_ZN10MetaModule13ModuleFactory14creation_funcsE",
         "_ZTVN4rack6engine6ModuleE",
    ]
    return libc_syms


if __name__ == "__main__":
    parser = argparse.ArgumentParser("Dump symbols that plugins might need")
    parser.add_argument("--objdir", help="Object dir with .obj files with the symbols we neeed (VCV_module_wrapper.cc.obj)")
    parser.add_argument("--elf", help="Fully linked elf file with addresses of all symbols (main.elf)")
    parser.add_argument("--out", help="output header file")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG, format='%(message)s')
    else:
        logging.basicConfig(level=logging.INFO, format='%(message)s')

    needed_syms = []

    obj_files = Path(args.objdir).glob("**/*.obj")
    for obj_file in obj_files:
        logging.info(f"Looking for symbols in {obj_file}")
        with open(obj_file, "rb") as f:
            needed_syms += GetRequiredSymbolNames(f)

    needed_syms += GetLibcSymbols()

    logging.debug("Finding symbol addresses:")

    with open(args.elf, "rb") as f:
        syms = GetAddressesOfSymbols(f, needed_syms)


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
    with open(args.out, "w") as f:
        f.write(symlist)


# flashing/dump_syms.py --objdir ./build/mp1corea7/medium/VCV_adaptor/CMakeFiles/VCV_adaptor.dir/ --elf ./build/mp1corea7/medium/main.elf --out src/dynload/host_sym_list.hh -v

