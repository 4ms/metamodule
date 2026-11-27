#!/usr/bin/env python3

import argparse
import logging
import re
import sys

from helpers import write_json, write_text
from pathlib import Path
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection

ClassDataPrefixes = ("_ZTV", "_ZTI", "_ZTS")  # vtable, typeinfo, typeinfo name

# The mangled class name that a class data symbol is for, as it appears after "_ZN" in the
# mangled names of the class's member functions:
#   _ZTVN4rack3app8SvgPanelE -> 4rack3app8SvgPanel   (member: _ZN4rack3app8SvgPanel4stepEv)
#   _ZTI16VCVModuleWrapper   -> 16VCVModuleWrapper   (member: _ZN16VCVModuleWrapper...)
def ClassDataClassName(name):
    cls = name[len("_ZTV"):]
    if cls.startswith("N") and cls.endswith("E"):
        cls = cls[1:-1]
    return cls

# weak_class_data: also take weak vtables/typeinfo of classes whose key function this object
# defines (see --weak-class-data).
def GetRequiredSymbolNames(file, weak_class_data=False):
    needed_syms = []
    elf = ELFFile(file)
    mmsyms = elf.get_section_by_name(".symtab")
    weak_class_syms = []
    strong_funcs = []
    if isinstance(mmsyms, SymbolTableSection):
        for i in range(mmsyms.num_symbols()):
            n = mmsyms.get_symbol(i).name
            l = mmsyms.get_symbol(i)['st_info']['bind']
            t = mmsyms.get_symbol(i)['st_info']['type']
            v = mmsyms.get_symbol(i)['st_other']['visibility']
            ndx = mmsyms.get_symbol(i)['st_shndx']
            if n == "" or t == "STT_NOTYPE" or ndx == 'SHN_UNDEF' or v != 'STV_DEFAULT':
                continue
            if l == "STB_GLOBAL":
                logging.debug(f"{i}: {n} {v}")
                needed_syms.append(n)
                if t == "STT_FUNC":
                    strong_funcs.append(n)
            elif weak_class_data and l == "STB_WEAK" and t == "STT_OBJECT" and n.startswith(ClassDataPrefixes):
                weak_class_syms.append(n)

    # A class's key function (its first non-inline virtual function) is a strong member function
    # defined here. Class data of a class with no key function is emitted by every object that uses
    # it, plugins included, so it isn't needed. (A strong non-virtual member function also counts,
    # which only adds a few unneeded symbols.)
    for n in weak_class_syms:
        member_prefix = "_ZN" + ClassDataClassName(n)
        if any(f.startswith(member_prefix) for f in strong_funcs):
            logging.debug(f"weak class data: {n}")
            needed_syms.append(n)

    return needed_syms

# Every symbol main.elf actually defines, and can therefore export to plugins.
def GetDefinedSymbolNames(elf_file):
    with open(elf_file, "rb") as f:
        return set(GetRequiredSymbolNames(f))

# Every global symbol main.elf defines, of any visibility. An exact keep-list name may be hidden:
# e.g. the AArch64 toolchain's libgcc unwinder (_Unwind_*) is, but the firmware can still export it.
def GetDefinedSymbolNamesAnyVisibility(elf_file):
    names = set()
    with open(elf_file, "rb") as f:
        symtab = ELFFile(f).get_section_by_name(".symtab")
        if isinstance(symtab, SymbolTableSection):
            for s in symtab.iter_symbols():
                if s.name != "" and s['st_info']['bind'] == "STB_GLOBAL" and s['st_shndx'] != 'SHN_UNDEF':
                    names.add(s.name)
    return names

# Weak vtables/typeinfo main.elf defines (see --weak-class-data)
def GetDefinedWeakClassDataNames(elf_file):
    names = set()
    with open(elf_file, "rb") as f:
        symtab = ELFFile(f).get_section_by_name(".symtab")
        if isinstance(symtab, SymbolTableSection):
            for s in symtab.iter_symbols():
                if (s['st_info']['bind'] == "STB_WEAK" and s['st_info']['type'] == "STT_OBJECT"
                        and s['st_shndx'] != 'SHN_UNDEF' and s['st_other']['visibility'] == 'STV_DEFAULT'
                        and s.name.startswith(ClassDataPrefixes)):
                    names.add(s.name)
    return names

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
    parser.add_argument("--weak-class-data", dest="weak_class_data", action="store_true",
                        help="Also export weak vtables/typeinfo (_ZTV/_ZTI/_ZTS) of classes whose key function is in "
                             "the scanned objects. Needed for AArch64 (MP2): the generic C++ ABI always makes class "
                             "data weak (COMDAT), while ARM EABI (MP1) makes it global in the key function's object.")
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
                needed_syms += GetRequiredSymbolNames(f, args.weak_class_data)

    for obj_dir in args.objdir:
        obj_files = Path(obj_dir).glob("**/*.obj")
        for obj_file in obj_files:
            logging.debug("------")
            logging.debug(f"Looking for symbols in {obj_file}")
            with open(obj_file, "rb") as f:
                needed_syms += GetRequiredSymbolNames(f, args.weak_class_data)

    scanned_syms = set(needed_syms)

    defined_in_elf = GetDefinedSymbolNames(args.elf) if args.elf else None
    exact = []

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
        defined_any = GetDefinedSymbolNamesAnyVisibility(args.elf)
        exact_set = set(exact)
        weak_class_data = GetDefinedWeakClassDataNames(args.elf) if args.weak_class_data else set()
        missing = [s for s in needed_syms if s not in defined_in_elf and s not in weak_class_data
                   and not (s in exact_set and s in defined_any)]
        if missing:
            logging.error("****************************************************************")
            for s in missing:
                logging.error(f"** ERROR: not defined in main.elf, dropping from API: {s} **")
            logging.error("****************************************************************")
            needed_syms = [s for s in needed_syms if s not in missing]

    logging.info(f"Exporting {len(needed_syms)} API symbols")

    if args.json:
        write_json(args.json, needed_syms)

    if args.text:
        write_text(args.text, needed_syms)

