#pragma once
#include "elf_helpers.hh"
#include "elf_symbol.hh"
#include "elf_types.hh"
#include "pr_dbg.hh"
#include <algorithm>
#include <elf.h>
#include <span>
#include <string_view>

namespace ElfFile
{

class ElfReloc {
	Elf_Rel *raw_reloc;
	ElfSymbol symbol;
	std::string_view string_table;

public:
	ElfReloc(Elf_Rel &raw_reloc, std::span<Elf_Sym> raw_dyn_symbols, std::string_view string_table)
		: raw_reloc{&raw_reloc}
		, symbol{raw_dyn_symbols[dyn_symbol_index()]}
		, string_table{string_table} {
	}

	uint32_t dyn_symbol_index() {
		return elf_r_sym(raw_reloc->r_info);
	}

	std::string_view symbol_name() {
		return read_string(string_table, symbol.name_offset());
	}

	uint32_t reloc_type() {
		return elf_r_type(raw_reloc->r_info);
	}

	// Address (relative to start of elf file) to write the symbol's address to
	elf_addr_t reloc_offset() {
		return raw_reloc->r_offset;
	}

	// Explicit addend (RELA-style, ELF64). REL-style (ELF32/ARM) relocations
	// keep their addend in-place at the relocated address, so this is 0.
	elf_addr_t addend() {
#if defined(METAMODULE_ELF64)
		return raw_reloc->r_addend;
#else
		return 0;
#endif
	}

	// "Value" of symbol, used to determine the actual address of the loaded symbol
	elf_addr_t symbol_value() {
		return symbol.offset();
	}
};

} // namespace ElfFile
