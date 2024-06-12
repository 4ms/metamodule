#pragma once
#include "console//pr_dbg.hh"
#include "dynload/plugin_file_list.hh"
#include "fs/fileio_t.hh"

namespace MetaModule
{

inline bool scan_volume(FileIoC auto &fileio, PluginFileList &plugin_files) {
	pr_trace("Scanning metamodule-plugins dir on volume %d\n", fileio.vol_id());

	bool ok = fileio.foreach_dir_entry(
		PluginDirName, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
			std::string full_path = std::string(PluginDirName) + std::string("/") + std::string(entryname);

			// Scan each dir in metamodule-plugins/
			if (kind == DirEntryKind::Dir) {
				if (entryname.starts_with("."))
					return;
				if (!scan_directory(fileio, plugin_files, full_path))
					pr_err("Failed to scan dir\n");
			}
		});

	if (!ok) {
		pr_err("Failed to read dir on %.32s\n", fileio.volname().data());
	}

	return ok;
}

inline bool scan_directory(FileIoC auto &fileio, PluginFileList &plugin_files, std::string const &path) {
	pr_trace("Scan dir: %s\n", path.c_str());
	bool ok = fileio.foreach_dir_entry(
		path, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
			// Add files:
			if (kind == DirEntryKind::File) {
				if (entryname.ends_with(".so") && !entryname.starts_with(".")) {
					plugin_files.push_back({fileio.vol_id(), path.c_str(), entryname, filesize});
					pr_trace("Found plugin file %s/%.*s\n", path.c_str(), entryname.size(), entryname.data());
				}
			}
		});
	return ok;
}

} // namespace MetaModule
