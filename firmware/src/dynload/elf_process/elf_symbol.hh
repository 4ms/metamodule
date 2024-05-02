#pragma once
#include "elf_helpers.hh"
#include "pr_dbg.hh"
#include <elf.h>
#include <string_view>

namespace ElfFile
{

class ElfDynSymbol {
	//
};

class ElfSymbol {
	Elf32_Sym *raw_symbol;

public:
	ElfSymbol(Elf32_Sym &raw_symbol)
		: raw_symbol{&raw_symbol} {
	}

	uint32_t section_index() {
		return raw_symbol->st_shndx;
	}

	uint32_t name_offset() {
		return raw_symbol->st_name;
	}

	uint32_t offset() {
		return raw_symbol->st_value;
	}

	uint32_t size() {
		return raw_symbol->st_size;
	}
};

} // namespace ElfFile
