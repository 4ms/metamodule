#pragma once
#include "dynload/plugin_file_list.hh"
#include "patch_file/dir_list_serial.hh"
#include <cstring>

// Flat form of PluginFileList, for passing it between cores that don't share a memory layout (MP2:
// PluginFile has a size_t, and the list a size_t count). Same encoding as dir_list_serial.hh.
// MP1 doesn't need this: the M4 fills in the A7's PluginFileList directly.
//
// Format: magic, num plugins, then per plugin: vol, full_path, plugin_name, file_size,
// version_in_filename.

namespace MetaModule::PluginListSerial
{

static constexpr uint32_t Magic = 0x50464C31; // "PFL1"

// Serializes plugin files into buf as they're added. Has the PluginFileList members that
// scan_volume() uses, so it can scan straight into the buffer.
class Writer {
	DirListSerial::Writer w;
	uint32_t num_plugins = 0;

public:
	explicit Writer(std::span<char> buf)
		: w{buf} {
		w.u32(Magic);
		w.u32(0); // num_plugins, filled in by finish()
	}

	bool push_back(PluginFile const &plugin) {
		if (num_plugins >= MaxPlugins)
			return false;

		auto start = w.pos;
		w.u32(static_cast<uint32_t>(plugin.vol));
		w.str(plugin.full_path);
		w.str(plugin.plugin_name);
		w.u32(plugin.file_size);
		w.str(plugin.version_in_filename);

		if (!w.ok) {
			// Didn't fit: drop the partial entry, so the ones before it are still valid
			w.pos = start;
			w.ok = true;
			return false;
		}

		num_plugins++;
		return true;
	}

	size_t max_size() const {
		return MaxPlugins;
	}

	// Returns the number of bytes used, or 0 if the buffer is too small for even an empty list
	uint32_t finish() {
		if (!w.ok)
			return 0;
		std::memcpy(w.buf.data() + sizeof(Magic), &num_plugins, sizeof num_plugins);
		return w.pos;
	}
};

inline bool deserialize(std::span<const char> buf, PluginFileList &list) {
	list.clear();

	DirListSerial::Reader r{buf};
	if (r.u32() != Magic)
		return false;

	// Smallest entry: vol, 3 empty strings, file_size
	auto num_plugins = r.count(5 * sizeof(uint32_t));
	if (num_plugins > MaxPlugins)
		return false;

	for (auto i = 0u; i < num_plugins; i++) {
		PluginFile plugin;
		auto vol = r.u32();
		plugin.full_path.copy(r.str());
		plugin.plugin_name.copy(r.str());
		plugin.file_size = r.u32();
		plugin.version_in_filename.copy(r.str());

		if (!r.ok || vol >= static_cast<uint32_t>(Volume::MaxVolumes))
			return false;
		plugin.vol = static_cast<Volume>(vol);

		list.push_back(plugin);
	}

	return r.ok;
}

} // namespace MetaModule::PluginListSerial
