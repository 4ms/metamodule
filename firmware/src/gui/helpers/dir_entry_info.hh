#pragma once
#include "fs/dir_entry_kind.hh"
#include "fs/volumes.hh"
#include <string>

namespace MetaModule
{

struct EntryInfo {
	DirEntryKind kind{};
	Volume vol{};
	std::string path;
	std::string name;

	bool operator==(const EntryInfo &that) const = default;
};

} // namespace MetaModule
