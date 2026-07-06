#pragma once
#include "pr_dbg.hh"
#include "elf_types.hh"
#include <elf.h>
#include <string_view>

namespace ElfFile
{

inline std::string_view read_string(std::string_view table, uint32_t offset) {
	if (offset >= table.size())
		return "";

	auto endpos = table.substr(offset).find_first_of('\0');
	if (endpos + offset >= table.size())
		return "";

	return table.substr(offset, endpos);
}

inline void print_prog_header(Elf_Phdr &prog) {
	pr_info("Program header: t:%x o:%llx vaddr:%llx paddr:%llx fsz:%llx memz:%llx f:%x aln:%llx\n",
			(unsigned)prog.p_type,
			(unsigned long long)prog.p_offset,
			(unsigned long long)prog.p_vaddr,
			(unsigned long long)prog.p_paddr,
			(unsigned long long)prog.p_filesz,
			(unsigned long long)prog.p_memsz,
			(unsigned)prog.p_flags,
			(unsigned long long)prog.p_align);
}

inline void print_sec_header(Elf_Shdr &sec, std::string_view string_table) {
	auto name = string_table.substr(sec.sh_name); //name.size() is wrong, but it is null-terminated, so it prints OK
	pr_info("Section: Name: %s ", name.data());
	pr_info("name_offset:%x t:%x f:%llx addr:%llx off:%llx sz:%llx link:%x info:%x aln:%llx entsz:%llx\n",
			(unsigned)sec.sh_name,
			(unsigned)sec.sh_type,
			(unsigned long long)sec.sh_flags,
			(unsigned long long)sec.sh_addr,
			(unsigned long long)sec.sh_offset,
			(unsigned long long)sec.sh_size,
			(unsigned)sec.sh_link,
			(unsigned)sec.sh_info,
			(unsigned long long)sec.sh_addralign,
			(unsigned long long)sec.sh_entsize);
}

inline void print_symbol(Elf_Sym &sym, std::string_view string_table) {
	if (sym.st_name >= string_table.size()) {
		pr_info("Symbol offset in string table (%u) > string table size (%u)\n", sym.st_name, string_table.size());
	} else {
		auto name = string_table.substr(sym.st_name); //name.size() is wrong, but it is null-terminated, so it prints OK
		pr_info("Symbol: Name: '%s' ", name.data());
		pr_info("addr = %08llx, size = %llx, info = %d, other = %d, sec=#%d, name offset = %d\n",
				(unsigned long long)sym.st_value,
				(unsigned long long)sym.st_size,
				(int)sym.st_info,
				(int)sym.st_other,
				(int)sym.st_shndx,
				(int)sym.st_name);
	}
}

} // namespace ElfFile
