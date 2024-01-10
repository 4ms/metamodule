#pragma once
#include "pr_dbg.hh"
#include <algorithm>
#include <elf.h>
#include <span>
#include <string>
#include <string_view>

struct ElfParser {
	ElfParser(std::span<uint8_t> elfdata)
		: rawdata{elfdata}
		, elf_header((Elf32_Ehdr *)elfdata.data())
		, section_headers{(Elf32_Shdr *)(elfdata.data() + elf_header->e_shoff), elf_header->e_shnum}
		, prog_headers{(Elf32_Phdr *)(elfdata.data() + elf_header->e_phoff), elf_header->e_phnum}
		, str_sec_header{&section_headers[elf_header->e_shstrndx]}
		, string_table{(char *)(elfdata.data() + str_sec_header->sh_offset), str_sec_header->sh_size} {
		pr_info("elf data is at %08x++%x\n", elfdata.data(), elfdata.size_bytes());

		auto dyn_string_sec = std::find_if(section_headers.begin(), section_headers.end(), [&](auto &sec) {
			printf("checking |%s| (%zu chars)\n", section_name(sec).data(), section_name(sec).size());
			return (section_name(sec) == ".dynstr");
		});
		if (dyn_string_sec != section_headers.end()) {
			dyn_strings = {(char *)elfdata.subspan(dyn_string_sec->sh_offset).data(), dyn_string_sec->sh_size};
			pr_info("Dyn strings begin at %p, for %zu\n", dyn_strings.data(), dyn_strings.size());
		} else {
			pr_info("No .dynstr section found\n");
		}
	}

	void print_prog_headers() {
		for (auto &prog : prog_headers) {
			pr_info("Program header: t:%x o:%x vaddr:%x paddr:%x fsz:%x memz:%x f:%x aln:%x\n",
					prog.p_type,
					prog.p_offset,
					prog.p_vaddr,
					prog.p_paddr,
					prog.p_filesz,
					prog.p_memsz,
					prog.p_flags,
					prog.p_align);

			// if (prog.p_type == PT_LOAD && prog.p_flags & (PF_R | PF_X)) {
			// 	pr_info("Loadable, Executable, Readable program\n");
			// }
		}
	}
	void print_sec_headers() {
		for (auto &sec : section_headers) {
			auto name = string_table.substr(sec.sh_name);
			pr_info("Section: Name: %s ", name.data());
			pr_info("name_offset:%x t:%x f:%x addr:%x off:%x sz:%x link:%x info:%x aln:%x entsz:%x\n",
					sec.sh_name,
					sec.sh_type,
					sec.sh_flags,
					sec.sh_addr,
					sec.sh_offset,
					sec.sh_size,
					sec.sh_link,
					sec.sh_info,
					sec.sh_addralign,
					sec.sh_entsize);
		}
	}

	//TODO:
	struct Section {
		Section(ElfParser &parent, Elf32_Shdr &header)
			: header{header}
			, parent{parent} {
		}

		bool is_code() {
			return header.sh_type == SHT_PROGBITS && (header.sh_flags & SHF_ALLOC) && (header.sh_flags & SHF_EXECINSTR);
		}
		bool is_rodata() {
			return header.sh_type == SHT_PROGBITS && (header.sh_flags & SHF_ALLOC) && (header.sh_flags & SHF_MERGE) &&
				   (header.sh_flags & SHF_STRINGS);
		}
		// std::string_view section_name(Elf32_Shdr &sec) {
		// 	return parent.string_table.substr(sec.sh_name);
		// }

		uint8_t *section_start(Elf32_Shdr &sec) {
			return parent.rawdata.data() + sec.sh_offset;
		}

		uint8_t *section_end(Elf32_Shdr &sec) {
			return parent.rawdata.data() + sec.sh_offset + sec.sh_size;
		}

		Elf32_Shdr &header;
		ElfParser &parent;
		std::string_view name;
	};

	bool is_code(Elf32_Shdr &sec) {
		return sec.sh_type == SHT_PROGBITS && (sec.sh_flags & SHF_ALLOC) && (sec.sh_flags & SHF_EXECINSTR);
	}

	bool is_rodata(Elf32_Shdr &sec) {
		return sec.sh_type == SHT_PROGBITS && (sec.sh_flags & SHF_ALLOC) && (sec.sh_flags & SHF_MERGE) &&
			   (sec.sh_flags & SHF_STRINGS);
	}

	std::string_view section_name(Elf32_Shdr &sec) {
		//End string at first null char
		const char *s = string_table.substr(sec.sh_name).data();
		auto len = std::string(s).length();
		return string_table.substr(sec.sh_name, len);
	}

	uint8_t *section_start(Elf32_Shdr &sec) {
		return rawdata.data() + sec.sh_offset;
	}

	uint8_t *section_end(Elf32_Shdr &sec) {
		return rawdata.data() + sec.sh_offset + sec.sh_size;
	}

	std::span<uint8_t> rawdata;
	Elf32_Ehdr *elf_header{};
	std::span<Elf32_Shdr> section_headers;
	std::span<Elf32_Phdr> prog_headers;
	Elf32_Shdr *str_sec_header;
	std::string_view string_table;
	std::string_view dyn_strings;
};
