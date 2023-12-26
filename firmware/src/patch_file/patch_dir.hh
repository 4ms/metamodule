#pragma once
#include "fs/volumes.hh"
#include "patch_file.hh"
#include <utility>
#include <vector>

namespace MetaModule
{

struct PatchDir {
	std::string name;
	std::vector<PatchDir> dirs;
	std::vector<PatchFile> files;

	PatchDir()
		: name("") {
	}

	PatchDir(std::string name)
		: name{std::move(name)} {
	}

	PatchDir(std::string_view name)
		: name{name} {
	}

	PatchDir(const char *name)
		: name{name} {
	}

	size_t num_entries() {
		return files.size() + dirs.size();
	}
};

} // namespace MetaModule
