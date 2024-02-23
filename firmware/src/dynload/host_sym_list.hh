#pragma once
#include "host_symbol.hh"
#include "ld.h"
#include "sym_list_parse.hh"
#include <span>
#include <vector>

namespace MetaModule
{

inline std::vector<ElfFile::HostSymbol> get_host_symbols() {
	auto symlist_yaml = std::span<char>{reinterpret_cast<char *>(A7_SYMS), A7_SYMS_SZ / sizeof(ElfFile::HostSymbol)};
	return parse_symlist(symlist_yaml);
}

} // namespace MetaModule
