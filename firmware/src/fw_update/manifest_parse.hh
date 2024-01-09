#pragma once
#include "pr_dbg.hh"
#include "update_file.hh"
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

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

	updatefile->type = (n["type"].val() == "app")			  ? MetaModule::UpdateType::App :
					   (n["type"].val() == "wifi-app")		  ? MetaModule::UpdateType::WifiApp :
					   (n["type"].val() == "wifi-firmware")	  ? MetaModule::UpdateType::WifiFirmware :
					   (n["type"].val() == "wifi-filesystem") ? MetaModule::UpdateType::WifiFilesystem :
																MetaModule::UpdateType::Invalid;

	if (n.has_child("md5")) {
		auto md5 = n["md5"].val();
		auto md5_sv = std::string_view{md5.data(), md5.size()};
		updatefile->md5 = md5_sv;
	}

	return true;
}

struct ManifestParser {

	// returns true if file data is valid manifest json file (does not check md5 or if files exist)
	// creates the list of files we need
	UpdateManifest parse(std::span<char> json) {
		UpdateManifest manifest{};

		// ryml has issues with tabs in json sometimes:
		std::replace(json.begin(), json.end(), '\t', ' ');

		ryml::Tree tree = ryml::parse_in_place(ryml::substr(json.data(), json.size()));

		if (tree.num_children(0) == 0) {
			pr_dbg("Manifest not valid json or yaml\n");
			return manifest;
		}

		ryml::ConstNodeRef root = tree.rootref();

		if (!root.has_child("version")) {
			pr_dbg("Manifest file has no root node with key 'version'\n");
			return manifest;
		}

		if (!root.has_child("files")) {
			pr_dbg("Manifest file has no root node with key 'files'\n");
			return manifest;
		}

		root["version"] >> manifest.version;
		root["files"] >> manifest.files;

		return manifest;
	}
};

} // namespace MetaModule
