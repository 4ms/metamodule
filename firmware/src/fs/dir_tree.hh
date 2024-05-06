#pragma once
#include "fs/volumes.hh"
#include <string>
#include <utility>
#include <vector>

namespace MetaModule
{

struct FileEntry {
	std::string filename;
	uint32_t filesize;
	uint32_t timestamp;
};

template<typename EntryT = FileEntry>
struct DirTree {
	std::string name;
	std::vector<DirTree> dirs;
	std::vector<EntryT> files;

	DirTree()
		: name("") {
	}

	DirTree(std::string &&name)
		: name{std::move(name)} {
	}

	DirTree(std::string_view name)
		: name{name} {
	}

	DirTree(const char *name)
		: name{name} {
	}

	size_t num_entries() {
		return files.size() + dirs.size();
	}
};

} // namespace MetaModule
