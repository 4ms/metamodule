#pragma once
#include "VCV_adaptor/plugin/Plugin.hpp"
#include "conf/ramdisk_conf.hh"
#include "fs/asset_fs.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
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
	AssetFS asset_fs;

	std::list<rack::plugin::Plugin> internal_plugins;

	PluginFileLoader plugin_file_loader;

	PluginManager(FileStorageProxy &file_storage_proxy, RamDrive &ramdisk_storage)
		: file_storage_proxy{file_storage_proxy}
		, ramdisk_ops{ramdisk_storage}
		, ramdisk{&ramdisk_ops, Volume::RamDisk}
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

	enum class State { Ready, IsLoading, Done } state = State::Ready;
};

} // namespace MetaModule
