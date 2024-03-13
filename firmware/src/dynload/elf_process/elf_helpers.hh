#pragma once
#include "pr_dbg.hh"
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

inline void print_prog_header(Elf32_Phdr &prog) {
	pr_info("Program header: t:%x o:%x vaddr:%x paddr:%x fsz:%x memz:%x f:%x aln:%x\n",
			prog.p_type,
			prog.p_offset,
			prog.p_vaddr,
			prog.p_paddr,
			prog.p_filesz,
			prog.p_memsz,
			prog.p_flags,
			prog.p_align);
}

inline void print_sec_header(Elf32_Shdr &sec, std::string_view string_table) {
	auto name = string_table.substr(sec.sh_name); //name.size() is wrong, but it is null-terminated, so it prints OK
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

inline void print_symbol(Elf32_Sym &sym, std::string_view string_table) {
	auto name = string_table.substr(sym.st_name); //name.size() is wrong, but it is null-terminated, so it prints OK
	pr_info("Symbol: Name: %s ", name.data());
	pr_info("addr = %08x, size = %x, info = %d, other = %d, sec=#%d, name offset = %d\n",
			sym.st_value,
			sym.st_size,
			sym.st_info,
			sym.st_other,
			sym.st_shndx,
			sym.st_name);
}

} // namespace ElfFile
