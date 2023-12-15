#pragma once
#include "update_file.hh"
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace MetaModule
{

struct ManifestParser {

	// returns true if file data is valid manifest json file (does not check md5 or if files exist)
	// creates the list of files we need
	bool parse(std::string_view manifest) {
		files.clear();

		//TODO: use ryml to parse manifest => files
		return true;
	}

	std::vector<UpdateFile> files;
};

} // namespace MetaModule
