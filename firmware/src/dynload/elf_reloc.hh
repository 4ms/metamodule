#pragma once
#include "elf_helpers.hh"
#include "elf_symbol.hh"
#include "pr_dbg.hh"
#include <elf.h>
#include <span>
#include <string_view>

namespace ElfFile
{

class ElfReloc {
	Elf32_Rel *raw_reloc;
	ElfSymbol symbol;

public:
	ElfReloc(Elf32_Rel &raw_reloc, std::span<Elf32_Sym> raw_dyn_symbols)
		: raw_reloc{&raw_reloc}
		, symbol{raw_dyn_symbols[dyn_symbol_index()]} {
	}

	uint32_t dyn_symbol_index() {
		return ELF32_R_SYM(raw_reloc->r_info);
	}

	std::string_view dyn_symbol_name(std::string_view table) {
		return read_string(table, symbol.name_offset());
	}

	uint32_t symbol_type() {
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

class Relocater {
	uint32_t base_address;

public:
	Relocater(uint32_t elf_load_address)
		: base_address{elf_load_address} {
	}

	void write_reloc(ElfReloc &reloc) {
		if (reloc.symbol_type() == R_ARM_GLOB_DAT) {
			auto reloc_address = reinterpret_cast<uint32_t *>(reloc.reloc_offset() + base_address);
			*reloc_address = reloc.symbol_value() + base_address;
		}
	}
};
} // namespace ElfFile
