#include "plugin.hh"
#include "generic_module.hh"
#include "generic_module_new.hh"
#include "mapping/central_data.hh"

rack::Plugin *pluginInstance;

//////////////// Auto generated ///////////////////////
// include and define models below here

#include "CoreModules/info/SHEV_info.hh"
rack::Model *modelSHEV = GenericModule<SHEVInfo>::create();

#include "CoreModules/info/ENVVCA_info.hh"
rack::Model *modelENVVCA = GenericModuleNew<MetaModule::ENVVCAInfo>::create();

#include "CoreModules/info/DEV_info.hh"
rack::Model *modelDEV = GenericModule<DEVInfo>::create();

#include "CoreModules/info/Freeverb_info.hh"
rack::Model *modelFreeverb = GenericModule<FreeverbInfo>::create();

#include "CoreModules/info/STS_info.hh"
rack::Model *modelSTS = GenericModule<STSInfo>::create();

#include "CoreModules/info/VCAM_info.hh"
rack::Model *modelVCAM = GenericModule<VCAMInfo>::create();

#include "CoreModules/info/Tapo_info.hh"
rack::Model *modelTapo = GenericModule<TapoInfo>::create();

#include "CoreModules/info/Shift_info.hh"
rack::Model *modelShift = GenericModule<ShiftInfo>::create();

#include "CoreModules/info/SISM_info.hh"
rack::Model *modelSISM = GenericModule<SISMInfo>::create();

#include "CoreModules/info/SH_info.hh"
rack::Model *modelSH = GenericModule<SHInfo>::create();

#include "CoreModules/info/SCM_info.hh"
rack::Model *modelSCM = GenericModule<SCMInfo>::create();

#include "CoreModules/info/RCD_info.hh"
rack::Model *modelRCD = GenericModule<RCDInfo>::create();

#include "CoreModules/info/QPLFO_info.hh"
rack::Model *modelQPLFO = GenericModule<QPLFOInfo>::create();

#include "CoreModules/info/QCD_info.hh"
rack::Model *modelQCD = GenericModule<QCDInfo>::create();

#include "CoreModules/info/PI_info.hh"
rack::Model *modelPI = GenericModule<PIInfo>::create();

#include "CoreModules/info/PEG_info.hh"
rack::Model *modelPEG = GenericModule<PEGInfo>::create();

#include "CoreModules/info/Mixer_info.hh"
rack::Model *modelMixer = GenericModule<MixerInfo>::create();

#include "CoreModules/info/LPG_info.hh"
rack::Model *modelLPG = GenericModule<LPGInfo>::create();

#include "CoreModules/info/LIO_info.hh"
rack::Model *modelLIO = GenericModule<LIOInfo>::create();

#include "CoreModules/info/L4_info.hh"
rack::Model *modelL4 = GenericModule<L4Info>::create();

#include "CoreModules/info/Gate8_info.hh"
rack::Model *modelGate8 = GenericModule<Gate8Info>::create();

#include "CoreModules/info/Gate32_info.hh"
rack::Model *modelGate32 = GenericModule<Gate32Info>::create();

#include "CoreModules/info/GRev_info.hh"
rack::Model *modelGRev = GenericModule<GRevInfo>::create();

#include "CoreModules/info/Fade_info.hh"
rack::Model *modelFade = GenericModule<FadeInfo>::create();

#include "CoreModules/info/DLD_info.hh"
rack::Model *modelDLD = GenericModule<DLDInfo>::create();

#include "CoreModules/info/Comp_info.hh"
rack::Model *modelComp = GenericModule<CompInfo>::create();

#include "CoreModules/info/CLKM_info.hh"
rack::Model *modelCLKM = GenericModule<CLKMInfo>::create();

#include "CoreModules/info/CLKD_info.hh"
rack::Model *modelCLKD = GenericModule<CLKDInfo>::create();

#include "CoreModules/info/ADEnv_info.hh"
rack::Model *modelADEnv = GenericModule<ADEnvInfo>::create();

#include "CoreModules/info/Sequant_info.hh"
rack::Model *modelSequant = GenericModule<SequantInfo>::create();

#include "CoreModules/info/Verb_info.hh"
rack::Model *modelVerb = GenericModule<VerbInfo>::create();

#include "CoreModules/info/Switch41_info.hh"
rack::Model *modelSwitch41 = GenericModule<Switch41Info>::create();

#include "CoreModules/info/Switch14_info.hh"
rack::Model *modelSwitch14 = GenericModule<Switch14Info>::create();

#include "CoreModules/info/Seq8_info.hh"
rack::Model *modelSeq8 = GenericModule<Seq8Info>::create();

#include "CoreModules/info/Seq4_info.hh"
rack::Model *modelSeq4 = GenericModule<Seq4Info>::create();

#include "CoreModules/info/Quant_info.hh"
rack::Model *modelQuant = GenericModule<QuantInfo>::create();

#include "CoreModules/info/Prob8_info.hh"
rack::Model *modelProb8 = GenericModule<Prob8Info>::create();

#include "CoreModules/info/Octave_info.hh"
rack::Model *modelOctave = GenericModule<OctaveInfo>::create();

#include "CoreModules/info/MNMX_info.hh"
rack::Model *modelMNMX = GenericModule<MNMXInfo>::create();

#include "CoreModules/info/LPF_info.hh"
rack::Model *modelLPF = GenericModule<LPFInfo>::create();

#include "CoreModules/info/StMix_info.hh"
rack::Model *modelStMix = GenericModule<StMixInfo>::create();

#include "CoreModules/info/Source_info.hh"
rack::Model *modelSource = GenericModule<SourceInfo>::create();

#include "CoreModules/info/Slew_info.hh"
rack::Model *modelSlew = GenericModule<SlewInfo>::create();

#include "CoreModules/info/PitchShift_info.hh"
rack::Model *modelPitchShift = GenericModule<PitchShiftInfo>::create();

#include "CoreModules/info/Pan_info.hh"
rack::Model *modelPan = GenericModule<PanInfo>::create();

#include "CoreModules/info/Noise_info.hh"
rack::Model *modelNoise = GenericModule<NoiseInfo>::create();

#include "CoreModules/info/MultiLFO_info.hh"
rack::Model *modelMultiLFO = GenericModule<MultiLFOInfo>::create();

#include "CoreModules/info/KPLS_info.hh"
rack::Model *modelKPLS = GenericModule<KPLSInfo>::create();

#include "CoreModules/info/InfOsc_info.hh"
rack::Model *modelInfOsc = GenericModule<InfOscInfo>::create();

#include "CoreModules/info/HPF_info.hh"
rack::Model *modelHPF = GenericModule<HPFInfo>::create();

#include "CoreModules/info/Gate_info.hh"
rack::Model *modelGate = GenericModule<GateInfo>::create();

#include "CoreModules/info/Follow_info.hh"
rack::Model *modelFollow = GenericModule<FollowInfo>::create();

#include "CoreModules/info/FM_info.hh"
rack::Model *modelFM = GenericModule<FMInfo>::create();

#include "CoreModules/info/Drum_info.hh"
rack::Model *modelDrum = GenericModule<DrumInfo>::create();

#include "CoreModules/info/Djembe_info.hh"
rack::Model *modelDjembe = GenericModule<DjembeInfo>::create();

#include "CoreModules/info/Detune_info.hh"
rack::Model *modelDetune = GenericModule<DetuneInfo>::create();

#include "CoreModules/info/ComplexEG_info.hh"
rack::Model *modelComplexEG = GenericModule<ComplexEGInfo>::create();

#include "CoreModules/info/BPF_info.hh"
rack::Model *modelBPF = GenericModule<BPFInfo>::create();

#include "CoreModules/info/Atvert2_info.hh"
rack::Model *modelAtvert2 = GenericModule<Atvert2Info>::create();

#include "CoreModules/info/SMR_info.hh"
rack::Model *modelSMR = GenericModule<SMRInfo>::create();

#include "CoreModules/modules/enosc/altparam_EnOsc_info.hh"
rack::Model *modelEnOsc = GenericModule<APEnOscInfo>::create();

#include "CoreModules/info/BuffMult_info.hh"
rack::Model *modelBuffMult = GenericModule<BuffMultInfo>::create();
///////////////////////////////////////////////////////

void init(rack::Plugin *p) {
	initializeCentralData();

	pluginInstance = p;

	//////////////// Auto generated ///////////////////////
	// Add models below here
	p->addModel(modelSHEV);
	p->addModel(modelENVVCA);
	p->addModel(modelDEV);
	p->addModel(modelFreeverb);
	p->addModel(modelSTS);
	p->addModel(modelVCAM);
	p->addModel(modelTapo);
	p->addModel(modelShift);
	p->addModel(modelSISM);
	p->addModel(modelSH);
	p->addModel(modelSCM);
	p->addModel(modelRCD);
	p->addModel(modelQPLFO);
	p->addModel(modelQCD);
	p->addModel(modelPI);
	p->addModel(modelPEG);
	p->addModel(modelMixer);
	p->addModel(modelLPG);
	p->addModel(modelLIO);
	p->addModel(modelL4);
	p->addModel(modelGate8);
	p->addModel(modelGate32);
	p->addModel(modelGRev);
	p->addModel(modelFade);
	p->addModel(modelDLD);
	p->addModel(modelComp);
	p->addModel(modelCLKM);
	p->addModel(modelCLKD);
	p->addModel(modelADEnv);

	p->addModel(modelSequant);
	p->addModel(modelVerb);
	p->addModel(modelSwitch41);
	p->addModel(modelSwitch14);
	p->addModel(modelSeq8);
	p->addModel(modelSeq4);
	p->addModel(modelQuant);
	p->addModel(modelProb8);
	p->addModel(modelOctave);
	p->addModel(modelMNMX);
	p->addModel(modelLPF);
	p->addModel(modelAtvert2);
	p->addModel(modelBPF);
	p->addModel(modelBuffMult);
	p->addModel(modelComplexEG);
	p->addModel(modelDetune);
	p->addModel(modelDjembe);
	p->addModel(modelDrum);
	p->addModel(modelEnOsc);
	p->addModel(modelFM);
	p->addModel(modelFollow);
	p->addModel(modelGate);
	p->addModel(modelHPF);
	p->addModel(modelHubMedium);
	p->addModel(modelInfOsc);
	p->addModel(modelKPLS);
	p->addModel(modelMultiLFO);
	p->addModel(modelNoise);
	p->addModel(modelPan);
	p->addModel(modelPitchShift);
	p->addModel(modelSMR);
	p->addModel(modelSlew);
	p->addModel(modelSource);
	p->addModel(modelStMix);
	p->addModel(modelDualAtenuverter);
	///////////////////////////////////////////////////////
}
