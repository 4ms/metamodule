#pragma once
#include "VCV_adaptor/plugin/Plugin.hpp"
#include "conf/ramdisk_conf.hh"
#include "fs/asset_fs.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/fileio_t.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin_loader.hh"
#include <list>

extern rack::plugin::Plugin *pluginInstance;

extern rack::plugin::Model *modelEvenVCO;
extern rack::plugin::Model *modelRampage;
extern rack::plugin::Model *modelABC;
extern rack::plugin::Model *modelSpringReverb;
extern rack::plugin::Model *modelMixer;
extern rack::plugin::Model *modelSlewLimiter;
extern rack::plugin::Model *modelDualAtenuverter;
extern rack::plugin::Model *modelPercall;
extern rack::plugin::Model *modelHexmixVCA;
extern rack::plugin::Model *modelChoppingKinky;
extern rack::plugin::Model *modelKickall;
extern rack::plugin::Model *modelSamplingModulator;
extern rack::plugin::Model *modelMorphader;
extern rack::plugin::Model *modelADSR;
extern rack::plugin::Model *modelSTMix;
extern rack::plugin::Model *modelChannelStrip;
extern rack::plugin::Model *modelPonyVCO;
extern rack::plugin::Model *modelMotionMTR;

namespace MetaModule
{

struct PluginManager {
	FileStorageProxy &file_storage_proxy;
	RamDiskOps ramdisk_ops;
	FatFileIO ramdisk;
	AssetFS &asset_fs;

	std::list<rack::plugin::Plugin> internal_plugins;

	PluginFileLoader plugin_file_loader;

	PluginManager(FileStorageProxy &file_storage_proxy, RamDrive &ramdisk_storage, AssetFS &asset_fs)
		: file_storage_proxy{file_storage_proxy}
		, ramdisk_ops{ramdisk_storage}
		, ramdisk{&ramdisk_ops, Volume::RamDisk}
		, asset_fs{asset_fs}
		, plugin_file_loader{file_storage_proxy} {

		//Load internal plugins
		//TODO: how to do this from build system?
		auto &befaco_plugin = internal_plugins.emplace_back("Befaco");
		pluginInstance = &befaco_plugin;
		befaco_plugin.addModel(modelEvenVCO);
		befaco_plugin.addModel(modelPonyVCO);
		// befaco_plugin.addModel(modelRampage);
		// befaco_plugin.addModel(modelABC);
		// befaco_plugin.addModel(modelMixer);
		// befaco_plugin.addModel(modelSlewLimiter);
		// befaco_plugin.addModel(modelDualAtenuverter);
		// befaco_plugin.addModel(modelPercall);
		// befaco_plugin.addModel(modelHexmixVCA);
		// befaco_plugin.addModel(modelChoppingKinky);
		// befaco_plugin.addModel(modelKickall);
		// befaco_plugin.addModel(modelSamplingModulator);
		// befaco_plugin.addModel(modelMorphader);
		// befaco_plugin.addModel(modelADSR);
		// befaco_plugin.addModel(modelSTMix);
		// befaco_plugin.addModel(modelChannelStrip);
		// befaco_plugin.addModel(modelMotionMTR);
		// befaco_plugin.addModel(modelSpringReverb);

		internal_plugins.emplace_back("AudibleInstruments");
		//TODO

		internal_plugins.emplace_back("hetrickcv");
		//TODO

		internal_plugins.emplace_back("nonlinearcircuits");
		//TODO

		if (!ramdisk.format_disk()) {
			pr_err("Could not format RamDisk, no assets can be loaded!\n");
			return;
		} else
			pr_dbg("RamDisk formatted and mounted\n");

		DirTree<FileEntry> dir_tree;
		// add_directory(asset_fs.lfs_io, dir_tree);
	}

	static constexpr unsigned MaxAssetDirRecursion = 4;
	bool add_directory(FileIoC auto &fileio, DirTree<FileEntry> &dir_tree, unsigned recursion_depth = 0) {
		pr_trace("Scanning dir: '%s'\n", dir_tree.name.data());

		bool ok = fileio.lfs_io.foreach_dir_entry(
			dir_tree.name, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
				// std::string full_path = dir + "/" + std::string(entryname);
				// std::string full_path = std::string(entryname);

				if (kind == DirEntryKind::Dir) {
					if (!entryname.starts_with(".") && recursion_depth < MaxAssetDirRecursion) {
						pr_dbg("%s/\n", entryname.data());
						dir_tree.dirs.emplace_back(entryname);
					}
				}

				if (kind == DirEntryKind::File) {
					pr_dbg("%s\n", entryname.data());
					dir_tree.files.push_back(FileEntry{std::string(entryname), filesize, timestamp});
				}
			});

		if (!ok) {
			pr_err("Failed to read dir on %.32s\n", fileio.volname().data());
			return false;
		}

		for (auto &dir : dir_tree.dirs) {
			pr_trace("[%d] Entering subdir: %.*s\n", recursion_depth, dir.name.size(), dir.name.data());
			ok = add_directory(fileio, dir, recursion_depth + 1);
			if (!ok) {
				pr_err("Failed to add subdir\n");
			}
		}

		return ok;
	}

	void load_internal_assets() {
		// TODO: Save internal assets on LittleFS NOR Flash Driver,
		// Load internal plugin assets to RamDisk
	}

	void start_loading_plugins() {
		state = State::IsLoading;

		ramdisk.unmount_drive();
		plugin_file_loader.start();
	}

	auto process_loading() {
		auto result = plugin_file_loader.process();
		if (result.state == PluginFileLoader::State::Success) {
			if (state == State::IsLoading) {
				state = State::Done;
				pr_info("All plugins loaded\n");

				ramdisk.print_dir("/", 4);
			}
		}
		return result;
	}

	void test_write() {
		const char w[24] = "Testing some file\ndata\n";
		auto bytes_written = ramdisk.write_file("checkfile", w);
		pr_dbg("Wrote %zu bytes\n", bytes_written);
	}

	void test_read() {
		auto filinfo = ramdisk.get_file_info("checkfile");
		pr_dbg("Checkfile = %d bytes\n", filinfo.size);

		std::array<char, 128> r{0};
		auto bytes_read = ramdisk.read_file("checkfile", r);
		pr_dbg("%.*s\n", bytes_read, &r[0]);
	}

	static bool
	deep_copy_dirs(FileIoC auto &fileio_from, FileIoC auto &fileio_to, std::string dir, unsigned recursion_depth = 0) {
		pr_trace("[%d] Deep copy of %s\n", recursion_depth, dir.c_str());

		bool ok = fileio_from.foreach_dir_entry(
			dir, [&](std::string_view entryname, uint32_t timestamp, uint32_t filesize, DirEntryKind kind) {
				std::string full_path = dir + "/" + std::string(entryname);

				// Copy files:
				if (kind == DirEntryKind::File) {
					if (entryname.ends_with(".so") || entryname.starts_with('.')) {
						pr_trace("Skipping file %s\n", full_path.c_str());
						return;
					}
					if (filesize > 1024 * 1024) {
						pr_warn("Skipping large file %s (%zu bytes)", full_path.c_str(), filesize);
						return;
					}

					std::vector<char> filedata(filesize);
					auto bytes_read = fileio_from.read_file(full_path, filedata);

					if (bytes_read == filesize) {
						std::string write_path = full_path.substr(PluginDirName.length() + 1);
						if (fileio_to.write_file(write_path, filedata)) {
							pr_trace("Wrote %s (%zu bytes)\n", write_path.c_str(), filesize);
						} else
							pr_err("Failed to copy file %s (%zu bytes)\n", write_path.c_str(), filesize);
					} else
						pr_err("Failed to read file %s (%zu bytes)\n", full_path.c_str(), filesize);
				}

				// Follow dirs:
				if (kind == DirEntryKind::Dir) {
					if (entryname.starts_with("."))
						return;
					if (recursion_depth < 4) {
						pr_trace("Entering dir: %s\n", full_path.c_str());
						ok = deep_copy_dirs(fileio_from, fileio_to, full_path, recursion_depth + 1);
					} else
						pr_warn("Found dir: %s, but recursion level is at max, ignoring\n", full_path.c_str());
				}
			});

		if (!ok)
			pr_err("Failed to read dir on %.32s\n", fileio_from.volname().data());

		return ok;
	}

	enum class State { Ready, IsLoading, Done } state = State::Ready;
};

} // namespace MetaModule
