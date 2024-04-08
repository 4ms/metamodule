#pragma once
#include "conf/ramdisk_conf.hh"
#include "dynload/plugins.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/asset_drive/untar.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/fileio_t.hh"
#include "patch_file/file_storage_proxy.hh"
#include "plugin/Plugin.hpp"
#include "plugin_loader.hh"
#include <list>

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
		prepare_ramdisk();
		load_internal_assets();
		load_internal_plugins();
	}

	void load_internal_plugins() {
		//Load internal plugins
		//TODO: how to do this from build system?
		auto &befaco_plugin = internal_plugins.emplace_back("Befaco");
		pluginInstance = &befaco_plugin;
		pluginInstance->addModel(modelEvenVCO);
		pluginInstance->addModel(modelPonyVCO);
		pluginInstance->addModel(modelRampage);
		pluginInstance->addModel(modelABC);
		pluginInstance->addModel(modelMixer);
		pluginInstance->addModel(modelSlewLimiter);
		pluginInstance->addModel(modelDualAtenuverter);
		pluginInstance->addModel(modelPercall);
		pluginInstance->addModel(modelHexmixVCA);
		pluginInstance->addModel(modelChoppingKinky);
		pluginInstance->addModel(modelKickall);
		pluginInstance->addModel(modelSamplingModulator);
		pluginInstance->addModel(modelMorphader);
		pluginInstance->addModel(modelADSR);
		pluginInstance->addModel(modelSTMix);
		pluginInstance->addModel(modelChannelStrip);
		pluginInstance->addModel(modelMotionMTR);
		pluginInstance->addModel(modelSpringReverb);

		auto &audins_plugin = internal_plugins.emplace_back("AudibleInstruments");
		pluginInstance = &audins_plugin;
		pluginInstance->addModel(modelBlinds);
		pluginInstance->addModel(modelBraids);
		pluginInstance->addModel(modelBranches);
		pluginInstance->addModel(modelElements);
		pluginInstance->addModel(modelKinks);
		pluginInstance->addModel(modelLinks);
		pluginInstance->addModel(modelMarbles);
		pluginInstance->addModel(modelRings);
		pluginInstance->addModel(modelRipples);
		pluginInstance->addModel(modelShades);
		pluginInstance->addModel(modelShelves);
		pluginInstance->addModel(modelTides2);
		pluginInstance->addModel(modelVeils);
		// NEW:
		pluginInstance->addModel(modelClouds);
		pluginInstance->addModel(modelFrames);
		pluginInstance->addModel(modelPlaits);
		pluginInstance->addModel(modelStages);
		pluginInstance->addModel(modelStreams);
		pluginInstance->addModel(modelTides);
		pluginInstance->addModel(modelWarps);

		auto &hcv_plugin = internal_plugins.emplace_back("hetrickcv");
		pluginInstance = &hcv_plugin;
		pluginInstance->addModel(modelTwoToFour);
		pluginInstance->addModel(modelAnalogToDigital);
		pluginInstance->addModel(modelASR);
		pluginInstance->addModel(modelBinaryGate);
		pluginInstance->addModel(modelBinaryNoise);
		pluginInstance->addModel(modelBitshift);
		pluginInstance->addModel(modelBoolean3);
		pluginInstance->addModel(modelChaos1Op);
		pluginInstance->addModel(modelChaos2Op);
		pluginInstance->addModel(modelChaos3Op);
		pluginInstance->addModel(modelChaoticAttractors);
		pluginInstance->addModel(modelClockedNoise);
		pluginInstance->addModel(modelContrast);
		pluginInstance->addModel(modelCrackle);
		pluginInstance->addModel(modelDigitalToAnalog);
		pluginInstance->addModel(modelDust);
		pluginInstance->addModel(modelExponent);
		pluginInstance->addModel(modelFBSineChaos);
		pluginInstance->addModel(modelFlipFlop);
		pluginInstance->addModel(modelFlipPan);
		pluginInstance->addModel(modelGateDelay);
		pluginInstance->addModel(modelGateJunction);
		pluginInstance->addModel(modelGateJunctionExp);
		pluginInstance->addModel(modelGingerbread);
		pluginInstance->addModel(modelLogicCombine);
		pluginInstance->addModel(modelMidSide);
		pluginInstance->addModel(modelMinMax);
		pluginInstance->addModel(modelPhaseDrivenSequencer);
		pluginInstance->addModel(modelPhaseDrivenSequencer32);
		pluginInstance->addModel(modelPhasorAnalyzer);
		pluginInstance->addModel(modelPhasorBurstGen);
		pluginInstance->addModel(modelPhasorDivMult);
		pluginInstance->addModel(modelPhasorEuclidean);
		pluginInstance->addModel(modelPhasorGates);
		pluginInstance->addModel(modelPhasorGates32);
		pluginInstance->addModel(modelPhasorGates64);
		pluginInstance->addModel(modelPhasorGen);
		pluginInstance->addModel(modelPhasorGeometry);
		pluginInstance->addModel(modelPhasorHumanizer);
		pluginInstance->addModel(modelPhasorOctature);
		pluginInstance->addModel(modelPhasorQuadrature);
		pluginInstance->addModel(modelPhasorRandom);
		pluginInstance->addModel(modelPhasorRanger);
		pluginInstance->addModel(modelPhasorReset);
		pluginInstance->addModel(modelPhasorRhythmGroup);
		pluginInstance->addModel(modelPhasorShape);
		pluginInstance->addModel(modelPhasorShift);
		pluginInstance->addModel(modelPhasorStutter);
		pluginInstance->addModel(modelPhasorSubstepShape);
		pluginInstance->addModel(modelPhasorSwing);
		pluginInstance->addModel(modelPhasorTimetable);
		pluginInstance->addModel(modelPhasorToClock);
		pluginInstance->addModel(modelPhasorToLFO);
		pluginInstance->addModel(modelPhasorToWaveforms);
		pluginInstance->addModel(modelProbability);
		pluginInstance->addModel(modelScanner);
		pluginInstance->addModel(modelVectorMix);
		pluginInstance->addModel(modelWaveshape);
		pluginInstance->addModel(modelXYToPolar);
		// TODO:
		// 	? ? pluginInstance->addModel(modelBlankPanel);
		// 	pluginInstance->addModel(modelComparator);
		// 	pluginInstance->addModel(modelDataCompander);
		// 	pluginInstance->addModel(modelDelta);
		// 	pluginInstance->addModel(modelPhasorMixer);
		// 	pluginInstance->addModel(modelRandomGates);
		// 	pluginInstance->addModel(modelRotator);
		// 	pluginInstance->addModel(modelRungler);

		auto &nlc_plugin = internal_plugins.emplace_back("nonlinearcircuits");
		pluginInstance = &nlc_plugin;
		pluginInstance->addModel(model4Seq);
		pluginInstance->addModel(modelCipher);
		pluginInstance->addModel(modelBOOLs);
		pluginInstance->addModel(modelDivideConquer);
		pluginInstance->addModel(modelDivineCMOS);
		pluginInstance->addModel(modelDoubleNeuron);
		pluginInstance->addModel(modelGenie);
		pluginInstance->addModel(modelLetsSplosh);
		pluginInstance->addModel(modelNeuron);
		pluginInstance->addModel(modelNumberwang);
		pluginInstance->addModel(modelRouter);
		pluginInstance->addModel(modelSegue);
		pluginInstance->addModel(modelSlothApathy);
		pluginInstance->addModel(modelSlothInertia);
		pluginInstance->addModel(modelSlothTorpor);
		pluginInstance->addModel(modelSquidAxon);
		pluginInstance->addModel(modelStatues);
		pluginInstance->addModel(modelTripleSloth);
	}

	void prepare_ramdisk() {
		if (!ramdisk.format_disk()) {
			pr_err("Could not format RamDisk, no assets can be loaded!\n");
			return;
		} else
			pr_dbg("RamDisk formatted and mounted\n");
	}

	void start_loading_plugins() {
		state = State::IsLoading;

		ramdisk.mount_disk();
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

private:
	void load_internal_assets() {
		auto raw_image = asset_fs.read_image();
		auto asset_tar = Tar::Archive(raw_image);
		// asset_tar.print_info();

		auto ramdisk_writer = [&](const std::string_view filename, std::span<const char> buffer) -> uint32_t {
			return ramdisk.write_file(filename, buffer);
		};

		asset_tar.extract_files(ramdisk_writer);
	}

	void test_internal_asset() {
		test_read("4ms/fp/Pan.png");
		test_read("README.txt");
	}

	void test_write(std::string_view filename) {
		const char w[24] = "Testing some file\ndata\n";
		auto bytes_written = ramdisk.write_file(filename, w);
		pr_dbg("Wrote %zu bytes\n", bytes_written);
	}

	void test_read(std::string_view filename) {
		auto filinfo = ramdisk.get_file_info(filename);
		pr_dbg("Check reading %s = %d bytes\n", filename.data(), filinfo.size);

		std::array<char, 128> r{0};
		auto bytes_read = ramdisk.read_file(filename, r);
		pr_dbg("%.*s\n", bytes_read, &r[0]);
	}

	enum class State { Ready, IsLoading, Done } state = State::Ready;
};

} // namespace MetaModule
