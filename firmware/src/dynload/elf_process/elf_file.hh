#pragma once
#include "elf_helpers.hh"
#include "elf_reloc.hh"
#include "elf_section.hh"
#include "elf_symbol.hh"
#include "pr_dbg.hh"
#include <algorithm>
#include <elf.h>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace ElfFile
{

struct Elf {
	Elf(std::span<uint8_t> elfdata)
		: rawdata{elfdata}
		, raw_elf_header((Elf32_Ehdr *)elfdata.data())
		, raw_section_headers{(Elf32_Shdr *)(elfdata.data() + raw_elf_header->e_shoff), raw_elf_header->e_shnum}
		, raw_prog_headers{(Elf32_Phdr *)(elfdata.data() + raw_elf_header->e_phoff), raw_elf_header->e_phnum}
		, string_table{find_string_table()} {

		// pr_info("elf data is at %08x ++ %x\n", elfdata.data(), elfdata.size_bytes());
		// pr_info("phnum: %u\n", raw_elf_header->e_phnum);
		// pr_info("shnum: %u\n", raw_elf_header->e_shnum);
		if (string_table != "") {
			populate_segments();
			populate_sections();
			symbol_table = find_section(".symtab");
			dyn_symbol_table = find_section(".dynsym");
			find_dyn_strings();
			find_sym_strings();

			find_raw_symbols();

			populate_relocations(".rel.dyn");
			populate_relocations(".rel.plt");
		}
	}

	void print_sec_headers() {
		for (auto &sec : raw_section_headers)
			print_sec_header(sec, string_table);
	}

	void print_prog_headers() {
		for (auto &sec : raw_prog_headers)
			print_prog_header(sec);
	}

	size_t load_size() {
		uintptr_t lowest_addr = UINTPTR_MAX;
		uintptr_t highest_addr = 0;
		for (auto &seg : segments) {
			if (seg.is_loadable()) {
				lowest_addr = std::min(seg.address(), lowest_addr);
				highest_addr = std::max(uintptr_t(seg.address() + seg.mem_size()), highest_addr);
			}
		}
		return highest_addr - lowest_addr + 1;
	}

	std::optional<ElfSection> find_section(std::string_view name) {
		auto section = std::ranges::find_if(sections, [&](auto &sec) { return (sec.section_name() == name); });
		if (section != sections.end())
			return *section;
		else {
			pr_err("Section %.*s not found\n", (int)name.size(), name.data());
			return {};
		}
	}

	std::optional<ElfSection> get_section(size_t index) {
		if (index <= sections.size())
			return sections[index];
		else {
			pr_err("Section index %d out of range\n", index);
			return {};
		}
	}

	std::optional<ElfSymbol> find_symbol(std::string_view name) {
		auto symbol = std::ranges::find_if(
			raw_symbols, [&](Elf32_Sym &sym) { return read_string(sym_string_table, sym.st_name) == name; });
		if (symbol != raw_symbols.end())
			return *symbol;
		else
			return {};
	}

	std::optional<ElfSymbol> find_dyn_symbol(std::string_view name) {
		auto symbol = std::ranges::find_if(
			raw_dyn_symbols, [&](Elf32_Sym &sym) { return read_string(dyn_string_table, sym.st_name) == name; });
		if (symbol != raw_dyn_symbols.end())
			return *symbol;
		else
			return {};
	}

	std::vector<ElfSection> sections;
	std::vector<ElfProgramSegment> segments;
	std::vector<ElfReloc> relocs;

private:
	void populate_sections() {
		for (auto &sec : raw_section_headers) {
			sections.emplace_back(rawdata.data(), string_table, sec);
		}
	}

	void populate_segments() {
		for (auto &prog_seg : raw_prog_headers) {
			segments.emplace_back(rawdata.data(), prog_seg);
		}
	}

	void populate_relocations(std::string_view sec_name) {
		if (auto rel_section = find_section(sec_name)) {
			raw_rels = {(Elf32_Rel *)rel_section->begin(), rel_section->num_entries()};

			if (auto linked_symbol_section = get_section(rel_section->linked_section_idx())) {
				auto linked_symbols = linked_symbol_section->get_raw_symbols();

				if (auto linked_string_table_section = get_section(linked_symbol_section->linked_section_idx())) {
					auto linked_string_table = linked_string_table_section->as_string_table();

					if (linked_symbols.begin() != raw_dyn_symbols.begin())
						pr_err("Error: expecting %.*s linked symbol table to be .dynsym, but is idx %d\n",
							   sec_name.size(),
							   sec_name.data(),
							   rel_section->linked_section_idx());

					if (linked_string_table.begin() != dyn_string_table.begin())
						pr_err("Error: expecting %.*s linked string table to be .dynstr, but is idx %d\n",
							   sec_name.size(),
							   sec_name.data(),
							   rel_section->linked_section_idx());

					for (auto &rel : raw_rels) {
						relocs.emplace_back(rel, linked_symbols, linked_string_table);
					}
				}
			}

		} else {
			pr_err("No %.*s section\n", (int)sec_name.size(), sec_name.data());
		}
	}

	std::string_view find_string_table() {
		if (raw_elf_header->e_shstrndx < raw_section_headers.size()) {
			auto string_header = &raw_section_headers[raw_elf_header->e_shstrndx];
			return {(char *)rawdata.subspan(string_header->sh_offset).data(), string_header->sh_size};
		} else
			return "";
	}

	void find_sym_strings() {
		if (auto sym_string_table_section = get_section(symbol_table->linked_section_idx())) {
			sym_string_table = sym_string_table_section->as_string_table();
		} else {
			pr_err("Symbol sections says its string table is section #%u but this is not found\n",
				   symbol_table->linked_section_idx());
		}
	}

	void find_dyn_strings() {
		auto dyn_string_section = find_section(".dynstr");

		if (dyn_string_section) {
			dyn_string_table = dyn_string_section->as_string_table();

			// Check .dynstr is the mlinked string table of the .dynsym section
			if (auto linked_dyn_string_table = get_section(dyn_symbol_table->linked_section_idx())) {
				if (dyn_string_table.begin() != linked_dyn_string_table->as_string_table().begin()) {
					pr_err("Error: dyn symbol section links to a section (#%u) that's not the first .dynstr section\n",
						   dyn_symbol_table->linked_section_idx());
				}
			}

		} else {
			pr_err("No .dynstr section found\n");
			dyn_string_table = "";
		}
	}

	void find_raw_symbols() {
		if (symbol_table)
			raw_symbols = symbol_table->get_raw_symbols();

		if (dyn_symbol_table)
			raw_dyn_symbols = dyn_symbol_table->get_raw_symbols();
	}

	std::span<uint8_t> rawdata;
	Elf32_Ehdr *raw_elf_header{};
	std::span<Elf32_Shdr> raw_section_headers;
	std::span<Elf32_Phdr> raw_prog_headers;

	// String tables:
	std::string_view string_table;
	std::string_view sym_string_table;
	std::string_view dyn_string_table;

	// Symbol table sections:
	std::optional<ElfSection> symbol_table{};
	std::optional<ElfSection> dyn_symbol_table{};

	std::span<Elf32_Sym> raw_symbols{};
	std::span<Elf32_Sym> raw_dyn_symbols{};

	std::span<Elf32_Rel> raw_rels{};
};

} // namespace ElfFile
