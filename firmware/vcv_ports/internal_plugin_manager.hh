#pragma once
#include "convert_plugins.hh"
#include "ext_plugin_builtin.hh"
#include "fat_file_io.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/asset_drive/untar.hh"
#include "fs/norflash_layout.hh"
#include "glue/Valley/plugins.hh"
#include "internal_plugins.hh"
#include "plugin/Plugin.hpp"
#include <list>
#include <span>
#include <string_view>

namespace MetaModule
{

struct InternalPluginManager {
	FatFileIO &ramdisk;
	AssetFS &asset_fs;

	std::list<rack::plugin::Plugin> internal_plugins;
	bool asset_fs_valid = true;

	InternalPluginManager(FatFileIO &ramdisk, AssetFS &asset_fs)
		: ramdisk{ramdisk}
		, asset_fs{asset_fs} {
		prepare_ramdisk();
		load_internal_assets();
		load_internal_plugins();
		load_ext_builtin_plugins(internal_plugins);
	}

	void prepare_ramdisk() {
		if (!ramdisk.format_disk()) {
			pr_err("Could not format RamDisk, no assets can be loaded!\n");
			return;
		} else
			pr_dbg("RamDisk formatted and mounted\n");
	}

	void load_internal_assets() {
		auto raw_image = asset_fs.read_image();
		auto asset_tar = Tar::Archive(raw_image);

		if (asset_tar.is_valid()) {
			// asset_tar.print_info();
			asset_fs_valid = true;
		} else {
			pr_err("Internal Assets tar file is not valid\n");
			asset_fs_valid = false;
		}

		auto ramdisk_writer = [&](const std::string_view filename, std::span<const char> buffer) -> uint32_t {
			return ramdisk.write_file(filename, buffer);
		};

		asset_tar.extract_files(ramdisk_writer);

		ramdisk.debug_print_disk_info();
	}

	void load_internal_plugins() {
		//Load internal plugins
		// TODO: use the glue/BRAND/plugin.cpp::init() function for each brand...
		// 		 But, somehow get around the issue of multiple definitions of global symbol pluginInstance

#ifndef BUILD_DYN_PLUGIN_Befaco
		auto &befaco_plugin = internal_plugins.emplace_back("Befaco");
		befaco_plugin.slug = "Befaco";
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
		pluginInstance->addModel(modelBurst);
		pluginInstance->addModel(modelVoltio);
		pluginInstance->addModel(modelOctaves);
		pluginInstance->addModel(modelNoisePlethora);
		pluginInstance->addModel(modelMuxlicer);
		pluginInstance->addModel(modelBandit);
#endif

#ifndef BUILD_DYN_PLUGIN_AudibleInstruments
		auto &audins_plugin = internal_plugins.emplace_back("AudibleInstruments");
		audins_plugin.slug = "AudibleInstruments";
		pluginInstance = &audins_plugin;
		AudibleInstruments::addModel(&audins_plugin, modelBlinds);
		AudibleInstruments::addModel(&audins_plugin, modelBraids);
		AudibleInstruments::addModel(&audins_plugin, modelBranches);
		AudibleInstruments::addModel(&audins_plugin, modelElements);
		AudibleInstruments::addModel(&audins_plugin, modelKinks);
		AudibleInstruments::addModel(&audins_plugin, modelLinks);
		AudibleInstruments::addModel(&audins_plugin, modelMarbles);
		AudibleInstruments::addModel(&audins_plugin, modelRings);
		AudibleInstruments::addModel(&audins_plugin, modelRipples);
		AudibleInstruments::addModel(&audins_plugin, modelShades);
		AudibleInstruments::addModel(&audins_plugin, modelShelves);
		AudibleInstruments::addModel(&audins_plugin, modelTides2);
		AudibleInstruments::addModel(&audins_plugin, modelVeils);
		AudibleInstruments::addModel(&audins_plugin, modelClouds);
		AudibleInstruments::addModel(&audins_plugin, modelFrames);
		AudibleInstruments::addModel(&audins_plugin, modelPlaits);
		AudibleInstruments::addModel(&audins_plugin, modelStages);
		AudibleInstruments::addModel(&audins_plugin, modelStreams);
		AudibleInstruments::addModel(&audins_plugin, modelTides);
		AudibleInstruments::addModel(&audins_plugin, modelWarps);
#endif

#ifndef BUILD_DYN_PLUGIN_hetrickcv
		auto &hcv_plugin = internal_plugins.emplace_back("hetrickcv");
		hcv_plugin.slug = "hetrickcv";
		pluginInstance = &hcv_plugin;
		pluginInstance->addModel(modelTwoToFour);
		pluginInstance->addModel(modelAnalogToDigital);
		pluginInstance->addModel(modelASR);
		pluginInstance->addModel(modelBinaryCounter);
		pluginInstance->addModel(modelBinaryGate);
		pluginInstance->addModel(modelBinaryNoise);
		pluginInstance->addModel(modelBitshift);
		pluginInstance->addModel(modelBoolean3);
		pluginInstance->addModel(modelChaos1Op);
		pluginInstance->addModel(modelChaos2Op);
		pluginInstance->addModel(modelChaos3Op);
		pluginInstance->addModel(modelChaoticAttractors);
		pluginInstance->addModel(modelClockedNoise);
		pluginInstance->addModel(modelComparator);
		pluginInstance->addModel(modelContrast);
		pluginInstance->addModel(modelCrackle);
		pluginInstance->addModel(modelDataCompander);
		pluginInstance->addModel(modelDelta);
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
		pluginInstance->addModel(modelPhasorFreezer);
		pluginInstance->addModel(modelPhasorGates);
		pluginInstance->addModel(modelPhasorGates32);
		pluginInstance->addModel(modelPhasorGates64);
		pluginInstance->addModel(modelPhasorGen);
		pluginInstance->addModel(modelPhasorGeometry);
		pluginInstance->addModel(modelPhasorHumanizer);
		pluginInstance->addModel(modelPhasorMixer);
		pluginInstance->addModel(modelPhasorOctature);
		pluginInstance->addModel(modelPhasorProbability);
		pluginInstance->addModel(modelPhasorQuadrature);
		pluginInstance->addModel(modelPhasorRandom);
		pluginInstance->addModel(modelPhasorRanger);
		pluginInstance->addModel(modelPhasorReset);
		pluginInstance->addModel(modelPhasorRhythmGroup);
		pluginInstance->addModel(modelPhasorShape);
		pluginInstance->addModel(modelPhasorShift);
		pluginInstance->addModel(modelPhasorSplitter);
		pluginInstance->addModel(modelPhasorStutter);
		pluginInstance->addModel(modelPhasorSubstepShape);
		pluginInstance->addModel(modelPhasorSwing);
		pluginInstance->addModel(modelPhasorTimetable);
		pluginInstance->addModel(modelPhasorToClock);
		pluginInstance->addModel(modelPhasorToLFO);
		pluginInstance->addModel(modelPhasorToWaveforms);
		pluginInstance->addModel(modelProbability);
		pluginInstance->addModel(modelRandomGates);
		pluginInstance->addModel(modelRotator);
		pluginInstance->addModel(modelRungler);
		pluginInstance->addModel(modelScanner);
		pluginInstance->addModel(modelTrigShaper);
		pluginInstance->addModel(modelVectorMix);
		pluginInstance->addModel(modelWaveshape);
		pluginInstance->addModel(modelXYToPolar);
#endif

#ifndef BUILD_DYN_PLUGIN_nonlinearcircuits
		auto &nlc_plugin = internal_plugins.emplace_back("nonlinearcircuits");
		nlc_plugin.slug = "nonlinearcircuits";
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
		pluginInstance->addModel(modelSplish);
		pluginInstance->addModel(modelStatues);
		pluginInstance->addModel(modelTripleSloth);
#endif

#ifndef BUILD_DYN_PLUGIN_eightfold
		auto &eightfold_plugin = internal_plugins.emplace_back("eightfold");
		eightfold_plugin.slug = "eightfold";
		pluginInstance = &eightfold_plugin;
		pluginInstance->addModel(modelSDOrcasHeartV2);
#endif

#ifndef BUILD_DYN_PLUGIN_Valley
		auto &Valley_plugin = internal_plugins.emplace_back("Valley");
		pluginInstance = &Valley_plugin;
		pluginInstance->addModel(modelTopograph);
		pluginInstance->addModel(modelUGraph);
		pluginInstance->addModel(modelPlateau);
#endif
	}
};
} // namespace MetaModule
