#pragma once
#include "convert_plugins.hh"
#include "ext_plugin_builtin.hh"
#include "fat_file_io.hh"
#include "fs/asset_drive/asset_fs.hh"
#include "fs/asset_drive/untar.hh"
#include "glue/RackCore/plugins.hh"
#include "glue/Valley/plugins.hh"
#include "gui/fonts/fonts_init.hh"
#include "internal_plugins.hh"
#include "plugin/Plugin.hpp"
#include <context.hpp>
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
		ModuleFactory::setBrandDisplayName("4msCompany", "4ms");
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
		// asset_tar.print_contents();

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

		Fonts::init_fonts(ramdisk);

		ramdisk.make_dir("/usr");
	}

	void load_internal_plugins() {
		rack::contextSet(nullptr);

		// Set 4ms display names
		// TODO: read from plugin-mm.json
		ModuleFactory::setModuleDisplayName("4msCompany:TSP", "Basic Wav Player");
		ModuleFactory::setModuleDisplayName("4msCompany:L4", "Listen Four");
		ModuleFactory::setModuleDisplayName("4msCompany:DEV", "Dual EnvVCA");
		ModuleFactory::setModuleDisplayName("4msCompany:SHEV", "Shaped Dual EnvVCA");
		ModuleFactory::setModuleDisplayName("4msCompany:DLD", "Dual Looping Delay");
		ModuleFactory::setModuleDisplayName("4msCompany:KPLS", "Karplus");
		ModuleFactory::setModuleDisplayName("4msCompany:KPLS", "Percussion Interface");
		ModuleFactory::setModuleDisplayName("4msCompany:SH", "Sample/Hold");
		ModuleFactory::setModuleDisplayName("4msCompany:StMix", "Stereo Mixed");
		ModuleFactory::setModuleDisplayName("4msCompany:Switch14", "Stereo 1 to 4");
		ModuleFactory::setModuleDisplayName("4msCompany:Switch41", "Stereo 4 to 1");
		ModuleFactory::setModuleDisplayName("4msCompany:VCAM", "VCA Matrix");
		ModuleFactory::setModuleDisplayName("4msCompany:Tapo", "Tapographic Delay");
		ModuleFactory::setModuleDisplayName("4msCompany:CLKD", "Clock Divider");
		ModuleFactory::setModuleDisplayName("4msCompany:CLKM", "Clock Multiplier");

		//Load internal plugins
		// TODO: use the glue/BRAND/plugin.cpp::init() function for each brand...
		// 		 But, somehow get around the issue of multiple definitions of global symbol pluginInstance

#ifdef BUILD_INTERNAL_Befaco
		pluginInstance = &internal_plugins.emplace_back("Befaco");
		befacoPluginInstance = pluginInstance;
		befacoPluginInstance->slug = "Befaco";
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
		pluginInstance->addModel(modelAtte);
		pluginInstance->addModel(modelAxBC);
		pluginInstance->addModel(modelMixer2);
		pluginInstance->addModel(modelMuDi);
		pluginInstance->addModel(modelSlew);
#endif

#ifdef BUILD_INTERNAL_AudibleInstruments
		pluginInstance = &internal_plugins.emplace_back("AudibleInstruments");
		pluginInstance->slug = "AudibleInstruments";
		audibleInstrumentsPluginInstance = pluginInstance;
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelBlinds);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelBraids);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelBranches);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelElements);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelKinks);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelLinks);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelMarbles);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelRings);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelRipples);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelShades);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelShelves);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelTides2);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelVeils);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelClouds);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelFrames);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelPlaits);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelStages);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelStreams);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelTides);
		AudibleInstruments::addModel(audibleInstrumentsPluginInstance, modelWarps);
#endif

#ifdef BUILD_INTERNAL_hetrickcv
		pluginInstance = &internal_plugins.emplace_back("HetrickCV");
		pluginInstance->slug = "HetrickCV";
		hetrickcvPluginInstance = pluginInstance;
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
		pluginInstance->addModel(modelClockToPhasor);
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
		pluginInstance->addModel(modelNormals);
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
		pluginInstance->addModel(modelPhasorToRandom);
		pluginInstance->addModel(modelPhasorToWaveforms);
		pluginInstance->addModel(modelPolymetricPhasors);
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

#ifdef BUILD_INTERNAL_nonlinearcircuits
		pluginInstance = &internal_plugins.emplace_back("NonlinearCircuits");
		pluginInstance->slug = "NonlinearCircuits";
		nonlinearcircuitsPluginInstance = pluginInstance;
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

#ifdef BUILD_INTERNAL_eightfold
		pluginInstance = &internal_plugins.emplace_back("eightfold");
		pluginInstance->slug = "eightfold";
		eightfoldPluginInstance = pluginInstance;
		pluginInstance->addModel(modelSDOrcasHeartV2);
#endif

#ifdef BUILD_INTERNAL_Valley
		pluginInstance = &internal_plugins.emplace_back("Valley");
		valleyPluginInstance = pluginInstance;
		pluginInstance->addModel(modelTopograph);
		pluginInstance->addModel(modelUGraph);
		pluginInstance->addModel(modelPlateau);
		pluginInstance->addModel(modelFeline);
		pluginInstance->addModel(modelAmalgam);
		pluginInstance->addModel(modelInterzone);
#endif

#ifdef BUILD_INTERNAL_RackCore
		pluginInstance = &internal_plugins.emplace_back("RackCore");
		rackCorePluginInstance = pluginInstance;
		pluginInstance->addModel(rack::core::modelMIDI_CV);
		pluginInstance->addModel(rack::core::modelCV_MIDI);
#endif
	}
};
} // namespace MetaModule
