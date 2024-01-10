#pragma once
#include "elf_helpers.hh"
#include <elf.h>
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

	uint32_t size() {
		return header->sh_size;
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
		return elf_data_start + offset() + size();
	}

	std::string_view section_name() {
		return read_string(elf_string_table, header->sh_name);
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

	uint32_t address() const {
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
