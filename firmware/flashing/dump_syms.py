#!/usr/bin/env python3

import argparse
import logging
import re
import sys

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

# Every symbol main.elf actually defines, and can therefore export to plugins.
def GetDefinedSymbolNames(elf_file):
    with open(elf_file, "rb") as f:
        return set(GetRequiredSymbolNames(f))

# Convert a C++ qualified name to the substring it produces in a mangled name:
#   MetaModule::MidiInput  ->  10MetaModule9MidiInput
#
# Every symbol belonging to that class or function contains that substring: all
# overloads, all constructor/destructor variants (C1/C2/D0/D1/D2), the vtable
# (_ZTVN10MetaModule9MidiInputE), and the typeinfo. That's what makes matching by
# name enough -- you don't have to know which compiler-generated symbols exist.
def MangledFragment(qualified_name):
    return "".join(f"{len(part)}{part}" for part in qualified_name.split("::"))

# Read a keep-list file. Each non-comment line is one of:
#   MetaModule::MidiInput   a C++ qualified name: keep every symbol of that class/function
#   sym: malloc             an exact symbol name (C functions, or one specific mangled name)
#   re: ^_ZN4rack4midi      a raw regex matched against mangled symbol names
def ReadKeepList(path):
    exact = []
    patterns = []  # (original line, compiled regex)
    for raw in Path(path).read_text().splitlines():
        line = raw.split("#")[0].strip()
        if not line:
            continue
        if line.startswith("sym:"):
            exact.append(line[4:].strip())
        elif line.startswith("re:"):
            expr = line[3:].strip()
            patterns.append((raw.strip(), re.compile(expr)))
        elif "::" in line:
            patterns.append((line, re.compile(re.escape(MangledFragment(line)))))
        else:
            # A bare name with no namespace is a C symbol: match it exactly
            exact.append(line)
    return exact, patterns

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Dump symbols that plugins might need")
    parser.add_argument("--objdir", required=True, action="append", help="Directory with .obj files with the symbols we want to make available to plugins")
    parser.add_argument("--objfile", required=False, action="append", help="Object file (.obj or .o) with the symbols we want to make available to plugins")
    parser.add_argument("--keep-list", dest="keep_list", required=False, help="File listing C++ names to keep in the API (see flashing/api-keep-list.txt)")
    parser.add_argument("--elf", required=False, help="Fully linked main.elf: used to expand keep-list names and to verify every exported symbol really exists")
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

    scanned_syms = set(needed_syms)

    defined_in_elf = GetDefinedSymbolNames(args.elf) if args.elf else None

    # Names we can't discover by scanning objects: libc/libstdc++ functions the
    # firmware provides, vtables, typeinfo, and anything whose definition lives in
    # main.elf but isn't referenced by the export libs.
    if args.keep_list:
        if not defined_in_elf:
            logging.error("** ERROR: --keep-list requires --elf **")
            sys.exit(1)

        exact, patterns = ReadKeepList(args.keep_list)
        for s in exact:
            if s in scanned_syms:
                logging.info(f"Note: keep-list symbol {s} was already found in the objdir files, consider removing it from {args.keep_list}")
        needed_syms += exact

        for line, pattern in patterns:
            matches = [s for s in defined_in_elf if pattern.search(s)]
            if matches:
                logging.debug(f"keep-list '{line}' matched {len(matches)} symbols")
                needed_syms += matches
            else:
                logging.error(f"** ERROR: keep-list entry matched no symbol in main.elf: {line} **")
    else:
        logging.warning("Warning: no --keep-list given, so libc and other non-scannable symbols will be missing from the API")

    # remove duplicates and sort
    needed_syms = list(set(needed_syms))
    needed_syms.sort()

    # A name that main.elf doesn't define can't be exported: find_syms.py would
    # fail on it later, and a plugin using it would fail to link. Usually it means
    # --gc-sections dropped the function because nothing in the firmware calls it
    # (referring to it in keep-symbols.cc is what prevents that).
    if defined_in_elf:
        missing = [s for s in needed_syms if s not in defined_in_elf]
        if missing:
            logging.error("****************************************************************")
            for s in missing:
                logging.error(f"** ERROR: not defined in main.elf, dropping from API: {s} **")
            logging.error("****************************************************************")
            needed_syms = [s for s in needed_syms if s in defined_in_elf]

    logging.info(f"Exporting {len(needed_syms)} API symbols")

    if args.json:
        write_json(args.json, needed_syms)

    if args.text:
        write_text(args.text, needed_syms)

