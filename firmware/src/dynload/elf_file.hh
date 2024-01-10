#pragma once
#include "elf_helpers.hh"
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

		populate_sections();
		find_dyn_strings();
		symbol_table = find_section(".symtab");
		dyn_symbol_table = find_section(".dynsym");
		find_raw_symbols();

		pr_dbg("elf data is at %08x++%x\n", elfdata.data(), elfdata.size_bytes());
	}

	void print_sec_headers() {
		for (auto &sec : raw_section_headers) {
			print_sec_header(sec, string_table);
		}
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

	std::optional<ElfSymbol> find_symbol(std::string_view name) {
		auto symbol = std::ranges::find_if(
			raw_symbols, [&](Elf32_Sym &sym) { return read_string(string_table, sym.st_name) == name; });
		if (symbol != raw_symbols.end())
			return *symbol;
		else
			return {};
	}

	std::optional<ElfSymbol> find_dyn_symbol(std::string_view name) {
		auto symbol = std::ranges::find_if(raw_dyn_symbols, [&](Elf32_Sym &sym) {
			print_symbol(sym, dyn_string_table);
			return read_string(dyn_string_table, sym.st_name) == name;
		});
		if (symbol != raw_dyn_symbols.end())
			return *symbol;
		else
			return {};
	}

	std::vector<ElfSection> sections;

private:
	void populate_sections() {
		for (auto &sec : raw_section_headers) {
			sections.emplace_back(rawdata.data(), string_table, sec);
		}
	}

	std::string_view find_string_table() {
		auto string_header = &raw_section_headers[raw_elf_header->e_shstrndx];
		return {(char *)rawdata.subspan(string_header->sh_offset).data(), string_header->sh_size};
	}

	void find_dyn_strings() {
		auto dyn_string_section = find_section(".dynstr");

		if (dyn_string_section) {
			pr_info("Dyn strings begin at %p, for %zu\n", dyn_string_table.data(), dyn_string_table.size());
			dyn_string_table = {(char *)rawdata.subspan(dyn_string_section->offset()).data(),
								dyn_string_section->size()};
		} else {
			pr_err("No .dynstr section found\n");
			dyn_string_table = "";
		}
	}

	void find_raw_symbols() {
		if (symbol_table)
			raw_symbols = {(Elf32_Sym *)symbol_table->begin(), symbol_table->size()};

		if (dyn_symbol_table)
			raw_dyn_symbols = {(Elf32_Sym *)dyn_symbol_table->begin(), dyn_symbol_table->size()};
	}

	std::span<uint8_t> rawdata;
	Elf32_Ehdr *raw_elf_header{};
	std::span<Elf32_Shdr> raw_section_headers;
	std::span<Elf32_Phdr> raw_prog_headers;

	// String tables:
	std::string_view string_table;
	std::string_view dyn_string_table;

	// Symbol table sections:
	std::optional<ElfSection> symbol_table{};
	std::optional<ElfSection> dyn_symbol_table{};

	std::span<Elf32_Sym> raw_symbols{};
	std::span<Elf32_Sym> raw_dyn_symbols{};
};

} // namespace ElfFile
