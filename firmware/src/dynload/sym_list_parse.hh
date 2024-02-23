#include "console/pr_dbg.hh"
#include "host_symbol.hh"
#include <span>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

namespace MetaModule
{

inline bool read(ryml::ConstNodeRef const &n, ElfFile::HostSymbol *symbol) {
	auto sv = std::string_view{n.key().data(), n.key().size()};
	symbol->name = sv; //copy
	symbol->hash = 0;
	n >> symbol->address;

	if (symbol->address == 0 || symbol->name.size() == 0)
		return false;

	return true;
}

inline std::vector<ElfFile::HostSymbol> parse_symlist(std::span<const char> yaml) {
	std::vector<ElfFile::HostSymbol> syms;

	ryml::Tree tree = ryml::parse_in_arena(ryml::csubstr(yaml.data(), yaml.size()));

	if (tree.num_children(0) <= 0) {
		pr_err("Host symbol file not valid yaml\n");
		return {};
	}

	ryml::ConstNodeRef root = tree.rootref();

	//TODO: change yaml structure from key:value to - Name: symbolname\n  Address: 0x...
	// root >> syms;

	for (const auto sym : root.children()) {
		ElfFile::HostSymbol s;
		if (read(sym, &s)) {
			syms.push_back(s);
		}
	}

	return syms;
}

} // namespace MetaModule
