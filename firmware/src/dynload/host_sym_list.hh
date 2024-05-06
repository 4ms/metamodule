#pragma once
#include "elf_process/host_symbol.hh"
#include "ld.h"
#include "sym_list_parse.hh"
#include <span>
#include <vector>

namespace MetaModule
{

inline std::vector<ElfFile::HostSymbol> get_host_symbols() {
	auto symlist = std::string_view{reinterpret_cast<const char *>(A7_SYMS), A7_SYMS_SZ};

	symlist = symlist.substr(0, symlist.find_first_of('\0'));

	return parse_symlist(symlist);
}

} // namespace MetaModule
