#pragma once
#include "conf/plugin_file_conf.hh"
#include "console/pr_dbg.hh"
#include "dynload/plugin_file_list.hh"
#include "fs/fileio_t.hh"

namespace MetaModule
{

// plugin_files: a PluginFileList, or anything with its push_back() and max_size()
// (e.g. PluginListSerial::Writer)
inline bool scan_volume(FileIoC auto &fileio, auto &plugin_files, std::string_view dir) {
	pr_trace("Scanning dir %s on volume %d\n", dir.data(), fileio.vol_id());

	bool ok = fileio.foreach_dir_entry(
		dir, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
			if (dir.ends_with("/"))
				dir.remove_suffix(1);
			std::string full_path = std::string(dir) + std::string("/") + std::string(entryname);

			// Add each plugin file (PLUGIN_FILE_EXTENSION)
			if (kind == DirEntryKind::File) {
				if (entryname.ends_with(PLUGIN_FILE_EXTENSION) && !entryname.starts_with(".")) {
					entryname.remove_suffix(sizeof(PLUGIN_FILE_EXTENSION) - 1);
					if (plugin_files.push_back({fileio.vol_id(), full_path.c_str(), entryname, filesize, ""}))
						pr_trace("Found plugin file %s\n", full_path.c_str());
					else
						pr_err("More than %zu plugins found\n", plugin_files.max_size());
				}
			}
		});

	if (!ok) {
		pr_err("Failed to read dir %s on %.32s\n", dir.data(), fileio.volname().data());
	}

	return ok;
}

} // namespace MetaModule
