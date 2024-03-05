#include "console/pr_dbg.hh"
#include "elf_process/host_symbol.hh"
#include <span>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

namespace MetaModule
{

inline bool read(ryml::ConstNodeRef const &n, ElfFile::HostSymbol *symbol) {
	if (!n.is_map() || !n.has_child("Name") || !n.has_child("Addr")) {
		return false;
	}

	n["Name"] >> symbol->name;
	n["Addr"] >> symbol->address;
	if (n.has_child("Hash"))
		n["Hash"] >> symbol->hash;
	else
		symbol->hash = 0;

	if (symbol->address == 0 || symbol->name.size() == 0) {
		return false;
	}

	return true;
}

inline std::vector<ElfFile::HostSymbol> parse_symlist(std::string_view yaml) {
	std::vector<ElfFile::HostSymbol> syms;

	ryml::Tree tree = ryml::parse_in_arena(ryml::csubstr(yaml.data(), yaml.size()));

	if (tree.num_children(0) <= 0) {
		pr_err("Host symbol file not valid yaml\n");
		return {};
	}

	ryml::ConstNodeRef root = tree.rootref();

	for (const auto sym : root.child(0)) {
		ElfFile::HostSymbol s;
		if (read(sym, &s)) {
			syms.push_back(s);
		}
	}

	return syms;
}

} // namespace MetaModule
