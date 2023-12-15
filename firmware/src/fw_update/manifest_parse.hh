#pragma once
#include "pr_dbg.hh"
#include "update_file.hh"
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"
// This must be included after ryml_std.hpp:

namespace MetaModule
{

inline bool read(ryml::ConstNodeRef const &n, UpdateFile *updatefile) {
	if (!n.is_map())
		return false;
	if (!n.has_child("type"))
		return false;
	if (!n.has_child("filename"))
		return false;
	if (!n.has_child("filesize"))
		return false;

	n["filename"] >> updatefile->filename;
	n["filesize"] >> updatefile->filesize;

	updatefile->type = (n["type"].val() == "app")  ? MetaModule::UpdateType::App :
					   (n["type"].val() == "wifi") ? MetaModule::UpdateType::Wifi :
													 MetaModule::UpdateType::Invalid;

	if (n.has_child("md5")) {
		auto md5 = n["md5"].val();
		if (md5.size() == 32) {
			std::string_view sv{md5.data(), md5.size()};
			for (auto i = 0u; i < 4; i++) {
				std::string s{sv.substr(8 * i, 8)};
				updatefile->md5[i] = std::strtoul(s.c_str(), nullptr, 16);
			}
		}
	}

	return true;
}

struct ManifestParser {

	// returns true if file data is valid manifest json file (does not check md5 or if files exist)
	// creates the list of files we need
	bool parse(std::span<char> manifest) {
		files.clear();

		// ryml has issues with tabs in json sometimes:
		std::replace(manifest.begin(), manifest.end(), '\t', ' ');

		ryml::Tree tree = ryml::parse_in_place(ryml::substr(manifest.data(), manifest.size()));

		if (tree.num_children(0) == 0) {
			pr_dbg("Manifest json tree has no children\n");
			return false;
		}

		ryml::ConstNodeRef root = tree.rootref();

		if (!root.has_child("updates")) {
			pr_dbg("Manifest json has no root node with key 'updates'\n");
			return false;
		}

		root["updates"] >> files;

		return true;
	}

	std::vector<UpdateFile> files;
};

} // namespace MetaModule
