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

inline std::optional<UpdateFile> parseFile(ryml::ConstNodeRef const &n) {

	if (n.is_map() && n.has_child("type") && n.has_child("filename") && n.has_child("filesize"))
	{
		auto parseFileType = [](const auto& typeString) -> std::optional<UpdateType>
		{
			if (typeString.val() == "app") return MetaModule::UpdateType::App;
			else if (typeString.val() == "wifi-app") return MetaModule::UpdateType::WifiApp;
			else if (typeString.val() == "wifi-firmware") return MetaModule::UpdateType::WifiFirmware;
			else if (typeString.val() == "wifi-filesystem") return MetaModule::UpdateType::WifiFilesystem;
			else return std::nullopt;
		};

		if (auto updateType = parseFileType(n["type"]); updateType)
		{
			UpdateFile updateFile;

			updateFile.type = *updateType;
			n["filename"] >> updateFile.filename;
			n["filesize"] >> updateFile.filesize;

			if (n.has_child("md5")) {
				auto md5 = n["md5"].val();
				auto md5_sv = std::string_view{md5.data(), md5.size()};
				updateFile.md5 = md5_sv;
			}

			return updateFile;
		}
		else
		{
			pr_err("Unknown update type\n");
		}

	}
	return std::nullopt;
}

struct ManifestParser {

	// returns true if file data is valid manifest json file (does not check md5 or if files exist)
	// creates the list of files we need
	std::optional<UpdateManifest> parse(std::span<char> json) {

		// ryml has issues with tabs in json sometimes:
		std::replace(json.begin(), json.end(), '\t', ' ');

		ryml::Tree tree = ryml::parse_in_place(ryml::substr(json.data(), json.size()));

		if (tree.num_children(0) > 0)
		{
			ryml::ConstNodeRef root = tree.rootref();

			if (root.has_child("version"))
			{
				UpdateManifest manifest{};
				root["version"] >> manifest.version;

				if (root.has_child("files"))
				{
					for (auto thisNode : root["files"])
					{
						if (auto thisFile = parseFile(thisNode); thisFile)
						{
							manifest.files.push_back(*thisFile);
						}
					}

					return manifest;
				}
				else
				{
					pr_dbg("Manifest file has no root node with key 'files'\n");
				}
			}
			else
			{
				pr_dbg("Manifest has no version\n");
			}
		}
		else
		{
			pr_dbg("Manifest not valid json or yaml\n");
		}
		
		return std::nullopt;
	}
};

} // namespace MetaModule
