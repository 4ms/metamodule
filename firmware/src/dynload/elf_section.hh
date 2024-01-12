#pragma once
#include "elf_helpers.hh"
#include <elf.h>
#include <span>
#include <string_view>

namespace ElfFile
{

class ElfSection {
	const uint8_t *elf_data_start;
	std::string_view elf_string_table;
	Elf32_Shdr *header;

public:
	ElfSection(const uint8_t *const elf_data_start, std::string_view string_table, Elf32_Shdr &header)
		: elf_data_start{elf_data_start}
		, elf_string_table{string_table}
		, header{&header} {
	}

	uint32_t offset() {
		return header->sh_offset;
	}

	uint32_t size_bytes() {
		return header->sh_size;
	}

	uint32_t num_entries() {
		return size_bytes() / header->sh_entsize;
	}

	// The can mean different things for different section types
	uint32_t linked_section_idx() {
		return header->sh_link;
	}

	bool is_code() {
		return header->sh_type == SHT_PROGBITS && (header->sh_flags & SHF_ALLOC) && (header->sh_flags & SHF_EXECINSTR);
	}

	bool is_rodata() {
		return header->sh_type == SHT_PROGBITS && (header->sh_flags & SHF_ALLOC) && (header->sh_flags & SHF_MERGE) &&
			   (header->sh_flags & SHF_STRINGS);
	}

	uint8_t const *begin() {
		return elf_data_start + offset();
	}

	uint8_t const *end() {
		return elf_data_start + offset() + size_bytes();
	}

	std::string_view section_name() {
		return read_string(elf_string_table, header->sh_name);
	}

	std::span<Elf32_Sym> get_raw_symbols() {
		return {(Elf32_Sym *)begin(), num_entries()};
	}

	std::string_view get_string_table() {
		return {(char *)(elf_data_start + offset()), size_bytes()};
	}
};

class ElfProgramSegment {
	const uint8_t *elf_data_start;
	Elf32_Phdr *header;

public:
	ElfProgramSegment(const uint8_t *const elf_data_start, Elf32_Phdr &header)
		: elf_data_start{elf_data_start}
		, header{&header} {
	}

	uint32_t offset() const {
		return header->p_offset;
	}

	uint32_t file_size() const {
		return header->p_filesz;
	}

	uint32_t mem_size() const {
		return header->p_memsz;
	}

	bool is_loadable() const {
		return header->p_type == PT_LOAD;
	}

	uintptr_t address() const {
		return header->p_vaddr;
	}

	uint8_t const *begin() {
		return elf_data_start + offset();
	}

	uint8_t const *end() {
		return elf_data_start + offset() + file_size();
	}
};

} // namespace ElfFile
