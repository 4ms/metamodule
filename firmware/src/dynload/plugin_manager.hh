#pragma once
#include "VCV_adaptor/plugin/Plugin.hpp"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "patch_file/file_storage_proxy.hh"
#include "static_buffers.hh"
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
extern rack::plugin::Model *modelMuxlicer;
extern rack::plugin::Model *modelMex;
extern rack::plugin::Model *modelNoisePlethora;
extern rack::plugin::Model *modelChannelStrip;
extern rack::plugin::Model *modelPonyVCO;
extern rack::plugin::Model *modelMotionMTR;

namespace MetaModule
{

struct PluginManager {
	RamDiskOps ramdisk_ops{StaticBuffers::virtdrive};
	FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};
	FileStorageProxy &file_storage_proxy;

	std::list<rack::plugin::Plugin> internal_plugins;

	PluginManager(FileStorageProxy &file_storage_proxy)
		: file_storage_proxy{file_storage_proxy} {

		//Load internal plugins
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

		// Sometimes:
		// befaco_plugin.addModel(modelSpringReverb);

		// Never:
		// befaco_plugin.addModel(modelMuxlicer);
		// befaco_plugin.addModel(modelMex);
		// befaco_plugin.addModel(modelNoisePlethora);

		internal_plugins.emplace_back("AudibleInstruments");
		internal_plugins.emplace_back("hetrickcv");
		internal_plugins.emplace_back("nonlinearcircuits");

		load_assets();
	}

	void load_assets() {
		// TODO: load internal plugin assets
		if (!ramdisk.format_disk()) {
			pr_err("Could not format RamDisk, no assets can be loaded!\n");
			return;
		}

		file_storage_proxy.request_copy_system_plugin_assets();

		while (true) {
			auto msg = file_storage_proxy.get_message();
			if (msg.message_type == FileStorageProxy::CopyPluginAssetsOK) {
				ramdisk.print_dir("res", 3);
				break;
			}
			if (msg.message_type == FileStorageProxy::CopyPluginAssetsFail) {
				pr_err("Failed to copy system plugin assets to ramdisk\n");
				break;
			}
		}
	}
};

} // namespace MetaModule
