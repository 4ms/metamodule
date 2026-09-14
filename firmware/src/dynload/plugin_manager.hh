#pragma once
#include "fs/fatfs/fat_file_io.hh"
#include "gui/fonts/ttf.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin_loader.hh"

#include "gui/fonts/fonts.hh"
#include <csetjmp>
#include <ranges>
#include <span>

namespace MetaModule
{

class PluginManager {

public:
	PluginManager(FileStorageProxy &file_storage_proxy, FatFileIO &ramdisk)
		: plugin_file_loader{file_storage_proxy, ramdisk}
		, ramdisk{ramdisk} {
	}

	void start_loading_plugin_list() {
		ramdisk.mount_disk();
		plugin_file_loader.start();
	}

	void load_plugin(unsigned idx) {
		plugin_file_loader.load_plugin(idx);
		ramdisk.debug_print_disk_info();
	}

	void unload_plugin(std::string_view name) {
		for (unsigned i = 0; auto const &plugin : loaded_plugin_list) {
			if (plugin.fileinfo.plugin_name == name) {
				// Unregister the brand first, while the plugin code is still loaded.
				// This destroys each module's CreateModuleFunc std::function, whose
				// type-erasure manager (for a plugin's lambda) lives in the plugin's
				// code. If we did this after erasing/poisoning the code, that manager
				// call would jump into freed/poisoned memory (an 0xEAFFFFFE "bl ." spin)
				// and hang -- which is native-plugin-only, since VCV plugins tear down
				// their create-funcs earlier in ~Plugin.
				// (For VCV plugins ~Plugin's per-module unregister then finds the brand
				// already gone and logs a harmless "failed to remove module" warning.)
				if (ModuleFactory::unregisterBrand(name) > 0)
					pr_dbg("Unregistered brand %s\n", name.data());
				else
					pr_dbg("Failed to unregister brand %s\n", name.data());

				// Mirror of the .init_array constructors run at load time
				run_fini_array(plugin);

				// Cleanup files we copied to the ramdisk
				for (auto const &file : plugin.loaded_files) {
					if (file.ends_with(".bin")) {
						Fonts::free_font(file);
					}
					if (file.ends_with(".ttf")) {
						Fonts::free_ttf(file);
					}
					ramdisk.delete_file(file);
				}

				// Get the location of the code
				auto plug = std::next(loaded_plugin_list.begin(), i);
				auto code = std::span<uint32_t>(reinterpret_cast<uint32_t *>(plug->code.data()), plug->code.size() / 4);

				// Delete it
				loaded_plugin_list.erase(std::next(loaded_plugin_list.begin(), i));

				// Skip the first two words -- malloc/free use these to tag the block
				code = code.subspan(2);
				pr_dbg("Clearing unallocated code block %p to %p (0x%x)\n", code.data(), code.end(), code.size_bytes());
				for (auto &x : code) {
					x = 0xEAFFFFFE; //bl .
				}

				break;
			}
			i++;
		}
		ramdisk.debug_print_disk_info();
	}

	// Strip suffix ".mmplugin" and version "-vX.X.X" from filename
	static std::string_view plugin_name_of(std::string_view filename) {
		if (filename.ends_with(".mmplugin"))
			filename.remove_suffix(9);

		for (auto v = filename.find("-v"); v != std::string_view::npos; v = filename.find("-v", v + 2)) {
			if (v + 2 < filename.size() && isdigit(filename[v + 2]))
				return filename.substr(0, v);
		}

		return filename;
	}

	bool is_plugin_loaded(std::string_view name) {
		for (auto const &plugin : loaded_plugin_list) {
			if (std::string_view{plugin.fileinfo.plugin_name} == name)
				return true;
		}
		return false;
	}

	// Install a plugin file from a volume the A7 can read itself (the developer
	// drive). An already-loaded copy must be unloaded by the caller first --
	// see DevDriveService, which runs the same sequence as the Plugin tab.
	bool start_local_install(FatFileIO &fileio, std::string_view filename) {
		if (plugin_file_loader.is_idle()) {
			return plugin_file_loader.load_local_plugin(fileio, filename);
		} else {
			pr_err("Plugin File Loader busy, cannot install %.*s now\n", (int)filename.size(), filename.data());
			return false;
		}
	}

	auto process_loading() {
		return plugin_file_loader.process(loaded_plugin_list);
	}

	std::pair<int32_t, int32_t> get_free_total_space_kb() {
		return ramdisk.get_free_total_space_kb();
	}

	bool is_idle() {
		return plugin_file_loader.is_idle();
	}

	StaticString<255> plugin_name(unsigned idx) {
		return plugin_file_loader.plugin_name(idx);
	}

	PluginFileList const *found_plugin_list() {
		return plugin_file_loader.found_plugin_list();
	}

	LoadedPluginList const &loaded_plugins() {
		return loaded_plugin_list;
	}

private:
	// Run the plugin's .fini_array destructors, in reverse order (per the ELF spec)
	static void run_fini_array(LoadedPlugin const &plugin) {
		using dtor_func_t = void (*)();

		if (plugin.fini_array.count == 0)
			return;

		auto code_start = reinterpret_cast<uintptr_t>(plugin.code.data());
		auto code_end = code_start + plugin.code.size();

		// The table in the code buffer was relocated at load, so entries are absolute addresses
		auto dtors = std::span<dtor_func_t const>(
			reinterpret_cast<dtor_func_t const *>(plugin.code.data() + plugin.fini_array.offset),
			plugin.fini_array.count);

		// A crashing destructor must not take down the unload
		AbortRescue rescue;
		if (setjmp(rescue.jb) != 0) {
			pr_err("Plugin crashed while running .fini_array destructors\n");
			return;
		}
		rescue.arm();

		for (auto dtor : std::views::reverse(dtors)) {
			auto addr = reinterpret_cast<uintptr_t>(dtor);
			if (addr < code_start || addr >= code_end) {
				pr_err("Skipping .fini_array entry %p: outside plugin code\n", dtor);
				continue;
			}
			pr_trace("Calling dtor %p\n", dtor);
			dtor();
		}
	}

	PluginFileLoader plugin_file_loader;
	LoadedPluginList loaded_plugin_list;
	FatFileIO &ramdisk;
};

} // namespace MetaModule
