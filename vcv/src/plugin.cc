#include "plugin.hh"
#include "generic_module.hh"
#include "hub/central_data.hh"

Plugin *pluginInstance;

//////////////// Auto generated ///////////////////////
// include and define models below here

#include "CoreModules/info/SHEV_info.hh"
Model* modelSHEV = createModelFromInfo<SHEVInfo>();

#include "CoreModules/info/ENVVCA_info.hh"
Model* modelENVVCA = createModelFromInfo<ENVVCAInfo>();

#include "CoreModules/info/DEV_info.hh"
Model* modelDEV = createModelFromInfo<DEVInfo>();

#include "CoreModules/info/Freeverb_info.hh"
Model* modelFreeverb = createModelFromInfo<FreeverbInfo>();

#include "CoreModules/info/STS_info.hh"
Model* modelSTS = createModelFromInfo<STSInfo>();

#include "CoreModules/info/VCAM_info.hh"
Model* modelVCAM = createModelFromInfo<VCAMInfo>();

#include "CoreModules/info/Tapo_info.hh"
Model* modelTapo = createModelFromInfo<TapoInfo>();

#include "CoreModules/info/Shift_info.hh"
Model* modelShift = createModelFromInfo<ShiftInfo>();

#include "CoreModules/info/SISM_info.hh"
Model* modelSISM = createModelFromInfo<SISMInfo>();

#include "CoreModules/info/SH_info.hh"
Model* modelSH = createModelFromInfo<SHInfo>();

#include "CoreModules/info/SCM_info.hh"
Model* modelSCM = createModelFromInfo<SCMInfo>();

#include "CoreModules/info/RCD_info.hh"
Model* modelRCD = createModelFromInfo<RCDInfo>();

#include "CoreModules/info/QPLFO_info.hh"
Model* modelQPLFO = createModelFromInfo<QPLFOInfo>();

#include "CoreModules/info/QCD_info.hh"
Model* modelQCD = createModelFromInfo<QCDInfo>();

#include "CoreModules/info/PI_info.hh"
Model* modelPI = createModelFromInfo<PIInfo>();

#include "CoreModules/info/PEG_info.hh"
Model* modelPEG = createModelFromInfo<PEGInfo>();

#include "CoreModules/info/Mixer_info.hh"
Model* modelMixer = createModelFromInfo<MixerInfo>();

#include "CoreModules/info/LPG_info.hh"
Model* modelLPG = createModelFromInfo<LPGInfo>();

#include "CoreModules/info/LIO_info.hh"
Model* modelLIO = createModelFromInfo<LIOInfo>();

#include "CoreModules/info/L4_info.hh"
Model* modelL4 = createModelFromInfo<L4Info>();

#include "CoreModules/info/Gate8_info.hh"
Model* modelGate8 = createModelFromInfo<Gate8Info>();

#include "CoreModules/info/Gate32_info.hh"
Model* modelGate32 = createModelFromInfo<Gate32Info>();

#include "CoreModules/info/GRev_info.hh"
Model* modelGRev = createModelFromInfo<GRevInfo>();

#include "CoreModules/info/Fade_info.hh"
Model* modelFade = createModelFromInfo<FadeInfo>();

#include "CoreModules/info/DLD_info.hh"
Model* modelDLD = createModelFromInfo<DLDInfo>();

#include "CoreModules/info/Comp_info.hh"
Model* modelComp = createModelFromInfo<CompInfo>();

#include "CoreModules/info/CLKM_info.hh"
Model* modelCLKM = createModelFromInfo<CLKMInfo>();

#include "CoreModules/info/CLKD_info.hh"
Model* modelCLKD = createModelFromInfo<CLKDInfo>();

#include "CoreModules/info/ADEnv_info.hh"
Model* modelADEnv = createModelFromInfo<ADEnvInfo>();

#include "CoreModules/info/Sequant_info.hh"
Model* modelSequant = createModelFromInfo<SequantInfo>();

#include "CoreModules/info/Verb_info.hh"
Model* modelVerb = createModelFromInfo<VerbInfo>();

#include "CoreModules/info/Switch41_info.hh"
Model* modelSwitch41 = createModelFromInfo<Switch41Info>();

#include "CoreModules/info/Switch14_info.hh"
Model* modelSwitch14 = createModelFromInfo<Switch14Info>();

#include "CoreModules/info/Seq8_info.hh"
Model* modelSeq8 = createModelFromInfo<Seq8Info>();

#include "CoreModules/info/Seq4_info.hh"
Model* modelSeq4 = createModelFromInfo<Seq4Info>();

#include "CoreModules/info/Quant_info.hh"
Model* modelQuant = createModelFromInfo<QuantInfo>();

#include "CoreModules/info/Prob8_info.hh"
Model* modelProb8 = createModelFromInfo<Prob8Info>();

#include "CoreModules/info/Octave_info.hh"
Model* modelOctave = createModelFromInfo<OctaveInfo>();

#include "CoreModules/info/MNMX_info.hh"
Model* modelMNMX = createModelFromInfo<MNMXInfo>();

#include "CoreModules/info/LPF_info.hh"
Model* modelLPF = createModelFromInfo<LPFInfo>();

#include "CoreModules/info/StMix_info.hh"
Model* modelStMix = createModelFromInfo<StMixInfo>();

#include "CoreModules/info/Source_info.hh"
Model* modelSource = createModelFromInfo<SourceInfo>();

#include "CoreModules/info/Slew_info.hh"
Model* modelSlew = createModelFromInfo<SlewInfo>();

#include "CoreModules/info/PitchShift_info.hh"
Model* modelPitchShift = createModelFromInfo<PitchShiftInfo>();

#include "CoreModules/info/Pan_info.hh"
Model* modelPan = createModelFromInfo<PanInfo>();

#include "CoreModules/info/Noise_info.hh"
Model* modelNoise = createModelFromInfo<NoiseInfo>();

#include "CoreModules/info/MultiLFO_info.hh"
Model* modelMultiLFO = createModelFromInfo<MultiLFOInfo>();

#include "CoreModules/info/KPLS_info.hh"
Model* modelKPLS = createModelFromInfo<KPLSInfo>();

#include "CoreModules/info/InfOsc_info.hh"
Model* modelInfOsc = createModelFromInfo<InfOscInfo>();

#include "CoreModules/info/HPF_info.hh"
Model* modelHPF = createModelFromInfo<HPFInfo>();

#include "CoreModules/info/Gate_info.hh"
Model* modelGate = createModelFromInfo<GateInfo>();

#include "CoreModules/info/Follow_info.hh"
Model* modelFollow = createModelFromInfo<FollowInfo>();

#include "CoreModules/info/FM_info.hh"
Model* modelFM = createModelFromInfo<FMInfo>();

#include "CoreModules/info/Drum_info.hh"
Model* modelDrum = createModelFromInfo<DrumInfo>();

#include "CoreModules/info/Djembe_info.hh"
Model* modelDjembe = createModelFromInfo<DjembeInfo>();

#include "CoreModules/info/Detune_info.hh"
Model* modelDetune = createModelFromInfo<DetuneInfo>();

#include "CoreModules/info/ComplexEG_info.hh"
Model* modelComplexEG = createModelFromInfo<ComplexEGInfo>();

#include "CoreModules/info/BPF_info.hh"
Model* modelBPF = createModelFromInfo<BPFInfo>();

#include "CoreModules/info/Atvert2_info.hh"
Model* modelAtvert2 = createModelFromInfo<Atvert2Info>();

#include "CoreModules/info/SMR_info.hh"
Model* modelSMR = createModelFromInfo<SMRInfo>();

#include "CoreModules/modules/enosc/altparam_EnOsc_info.hh"
Model* modelEnOsc = createModelFromInfo<APEnOscInfo>();

#include "CoreModules/info/BuffMult_info.hh"
Model* modelBuffMult = createModelFromInfo<BuffMultInfo>();
///////////////////////////////////////////////////////

void init(Plugin *p)
{
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
	///////////////////////////////////////////////////////
}
