#pragma once
#include "elf_helpers.hh"
#include "elf_symbol.hh"
#include "pr_dbg.hh"
#include <algorithm>
#include <elf.h>
#include <span>
#include <string_view>

namespace ElfFile
{

class ElfReloc {
	Elf32_Rel *raw_reloc;
	ElfSymbol symbol;
	std::string_view string_table;

public:
	ElfReloc(Elf32_Rel &raw_reloc, std::span<Elf32_Sym> raw_dyn_symbols, std::string_view string_table)
		: raw_reloc{&raw_reloc}
		, symbol{raw_dyn_symbols[dyn_symbol_index()]}
		, string_table{string_table} {
	}

	uint32_t dyn_symbol_index() {
		return ELF32_R_SYM(raw_reloc->r_info);
	}

	std::string_view symbol_name() {
		return read_string(string_table, symbol.name_offset());
	}

	uint32_t reloc_type() {
		return ELF32_R_TYPE(raw_reloc->r_info);
	}

	// Address (relative to start of elf file) to write the symbol's address to
	uint32_t reloc_offset() {
		return raw_reloc->r_offset;
	}

	// "Value" of symbol, used to determine the actual address of the loaded symbol
	uint32_t symbol_value() {
		return symbol.offset();
	}
};

} // namespace ElfFile
