#include "plugin.hpp"
#include "generic_module.hpp"

Plugin *pluginInstance;
std::unique_ptr<CentralData> centralData;

//////////////// Auto generated ///////////////////////
// include and define models below here

#include "CoreModules/info/SHEV_info.hh"
auto modelSHEV = createModelFromInfo<SHEVInfo>();

#include "CoreModules/info/ENVVCA_info.hh"
auto modelENVVCA = createModelFromInfo<ENVVCAInfo>();

#include "CoreModules/info/DEV_info.hh"
auto modelDEV = createModelFromInfo<DEVInfo>();

#include "CoreModules/info/Att_info.hh"
auto modelAtt = createModelFromInfo<AttInfo>();

#include "CoreModules/info/Freeverb_info.hh"
auto modelFreeverb = createModelFromInfo<FreeverbInfo>();

#include "CoreModules/info/STS_info.hh"
auto modelSTS = createModelFromInfo<STSInfo>();

#include "CoreModules/info/VCA_info.hh"
auto modelVCA = createModelFromInfo<VCAInfo>();

#include "CoreModules/info/VCAM_info.hh"
auto modelVCAM = createModelFromInfo<VCAMInfo>();

#include "CoreModules/info/Tapo_info.hh"
auto modelTapo = createModelFromInfo<TapoInfo>();

#include "CoreModules/info/Shift_info.hh"
auto modelShift = createModelFromInfo<ShiftInfo>();

#include "CoreModules/info/Send_info.hh"
auto modelSend = createModelFromInfo<SendInfo>();

#include "CoreModules/info/SISM_info.hh"
auto modelSISM = createModelFromInfo<SISMInfo>();

#include "CoreModules/info/SH_info.hh"
auto modelSH = createModelFromInfo<SHInfo>();

#include "CoreModules/info/SCM_info.hh"
auto modelSCM = createModelFromInfo<SCMInfo>();

#include "CoreModules/info/RCD_info.hh"
auto modelRCD = createModelFromInfo<RCDInfo>();

#include "CoreModules/info/RCDBO_info.hh"
auto modelRCDBO = createModelFromInfo<RCDBOInfo>();

#include "CoreModules/info/QPLFO_info.hh"
auto modelQPLFO = createModelFromInfo<QPLFOInfo>();

#include "CoreModules/info/QCD_info.hh"
auto modelQCD = createModelFromInfo<QCDInfo>();

#include "CoreModules/info/QCDEXP_info.hh"
auto modelQCDEXP = createModelFromInfo<QCDEXPInfo>();

#include "CoreModules/info/PI_info.hh"
auto modelPI = createModelFromInfo<PIInfo>();

#include "CoreModules/info/PIExp_info.hh"
auto modelPIExp = createModelFromInfo<PIExpInfo>();

#include "CoreModules/info/PEG_info.hh"
auto modelPEG = createModelFromInfo<PEGInfo>();

#include "CoreModules/info/Mixer_info.hh"
auto modelMixer = createModelFromInfo<MixerInfo>();

#include "CoreModules/info/Logic_info.hh"
auto modelLogic = createModelFromInfo<LogicInfo>();

#include "CoreModules/info/LPG_info.hh"
auto modelLPG = createModelFromInfo<LPGInfo>();

#include "CoreModules/info/LIO_info.hh"
auto modelLIO = createModelFromInfo<LIOInfo>();

#include "CoreModules/info/LFO_info.hh"
auto modelLFO = createModelFromInfo<LFOInfo>();

#include "CoreModules/info/L4_info.hh"
auto modelL4 = createModelFromInfo<L4Info>();

#include "CoreModules/info/L4Q_info.hh"
auto modelL4Q = createModelFromInfo<L4QInfo>();

#include "CoreModules/info/Gate8_info.hh"
auto modelGate8 = createModelFromInfo<Gate8Info>();

#include "CoreModules/info/Gate32_info.hh"
auto modelGate32 = createModelFromInfo<Gate32Info>();

#include "CoreModules/info/GRev_info.hh"
auto modelGRev = createModelFromInfo<GRevInfo>();

#include "CoreModules/info/Fade_info.hh"
auto modelFade = createModelFromInfo<FadeInfo>();

#include "CoreModules/info/FadeDelay_info.hh"
auto modelFadeDelay = createModelFromInfo<FadeDelayInfo>();

#include "CoreModules/info/DLD_info.hh"
auto modelDLD = createModelFromInfo<DLDInfo>();

#include "CoreModules/info/Comp_info.hh"
auto modelComp = createModelFromInfo<CompInfo>();

#include "CoreModules/info/CLKM_info.hh"
auto modelCLKM = createModelFromInfo<CLKMInfo>();

#include "CoreModules/info/CLKD_info.hh"
auto modelCLKD = createModelFromInfo<CLKDInfo>();

// #include "CoreModules/info/Att_info.hh"
// auto modelAtt = createModelFromInfo<AttInfo>();

#include "CoreModules/info/ADEnv_info.hh"
auto modelADEnv = createModelFromInfo<ADEnvInfo>();

#include "CoreModules/info/Sequant_info.hh"
auto modelSequant = createModelFromInfo<SequantInfo>();

#include "CoreModules/info/Verb_info.hh"
auto modelVerb = createModelFromInfo<VerbInfo>();

#include "CoreModules/info/Switch41_info.hh"
auto modelSwitch41 = createModelFromInfo<Switch41Info>();

#include "CoreModules/info/Switch14_info.hh"
auto modelSwitch14 = createModelFromInfo<Switch14Info>();

#include "CoreModules/info/Seq8_info.hh"
auto modelSeq8 = createModelFromInfo<Seq8Info>();

#include "CoreModules/info/Seq4_info.hh"
auto modelSeq4 = createModelFromInfo<Seq4Info>();

#include "CoreModules/info/Quant_info.hh"
auto modelQuant = createModelFromInfo<QuantInfo>();

#include "CoreModules/info/Prob8_info.hh"
auto modelProb8 = createModelFromInfo<Prob8Info>();

#include "CoreModules/info/Octave_info.hh"
auto modelOctave = createModelFromInfo<OctaveInfo>();

#include "CoreModules/info/MNMX_info.hh"
auto modelMNMX = createModelFromInfo<MNMXInfo>();

#include "CoreModules/info/LPF_info.hh"
auto modelLPF = createModelFromInfo<LPFInfo>();

#include "CoreModules/info/StMix_info.hh"
auto modelStMix = createModelFromInfo<StMixInfo>();

#include "CoreModules/info/Source_info.hh"
auto modelSource = createModelFromInfo<SourceInfo>();

#include "CoreModules/info/Slew_info.hh"
auto modelSlew = createModelFromInfo<SlewInfo>();

#include "CoreModules/info/PitchShift_info.hh"
auto modelPitchShift = createModelFromInfo<PitchShiftInfo>();

#include "CoreModules/info/Pan_info.hh"
auto modelPan = createModelFromInfo<PanInfo>();

#include "CoreModules/info/Noise_info.hh"
auto modelNoise = createModelFromInfo<NoiseInfo>();

#include "CoreModules/info/MultiLFO_info.hh"
auto modelMultiLFO = createModelFromInfo<MultiLFOInfo>();

#include "CoreModules/info/KPLS_info.hh"
auto modelKPLS = createModelFromInfo<KPLSInfo>();

#include "CoreModules/info/InfOsc_info.hh"
auto modelInfOsc = createModelFromInfo<InfOscInfo>();

#include "CoreModules/info/HPF_info.hh"
auto modelHPF = createModelFromInfo<HPFInfo>();

#include "CoreModules/info/Gate_info.hh"
auto modelGate = createModelFromInfo<GateInfo>();

#include "CoreModules/info/Follow_info.hh"
auto modelFollow = createModelFromInfo<FollowInfo>();

#include "CoreModules/info/FM_info.hh"
auto modelFM = createModelFromInfo<FMInfo>();

#include "CoreModules/info/Drum_info.hh"
auto modelDrum = createModelFromInfo<DrumInfo>();

#include "CoreModules/info/Djembe_info.hh"
auto modelDjembe = createModelFromInfo<DjembeInfo>();

#include "CoreModules/info/Detune_info.hh"
auto modelDetune = createModelFromInfo<DetuneInfo>();

#include "CoreModules/info/ComplexEG_info.hh"
auto modelComplexEG = createModelFromInfo<ComplexEGInfo>();

#include "CoreModules/info/BPF_info.hh"
auto modelBPF = createModelFromInfo<BPFInfo>();

#include "CoreModules/info/Atvert2_info.hh"
auto modelAtvert2 = createModelFromInfo<Atvert2Info>();

#include "CoreModules/info/SMR_info.hh"
auto modelSMR = createModelFromInfo<SMRInfo>();

#include "CoreModules/enosc/altparam_EnOsc_info.hh"
auto modelEnOsc = createModelFromInfo<APEnOscInfo>();

#include "CoreModules/info/BuffMult_info.hh"
auto modelBuffMult = createModelFromInfo<BuffMultInfo>();
///////////////////////////////////////////////////////

void init(Plugin *p)
{
	centralData = std::make_unique<CentralData>();

	pluginInstance = p;

	//////////////// Auto generated ///////////////////////
	// Add models below here
	p->addModel(modelSHEV);
	p->addModel(modelENVVCA);
	p->addModel(modelDEV);
	p->addModel(modelSend);
	p->addModel(modelLogic);
	p->addModel(modelLFO);
	p->addModel(modelFadeDelay);
	p->addModel(modelAtt);
	p->addModel(modelFreeverb);
	p->addModel(modelSTS);
	p->addModel(modelVCA);
	p->addModel(modelVCAM);
	p->addModel(modelTapo);
	p->addModel(modelShift);
	p->addModel(modelSISM);
	p->addModel(modelSH);
	p->addModel(modelSCM);
	p->addModel(modelRCD);
	p->addModel(modelRCDBO);
	p->addModel(modelQPLFO);
	p->addModel(modelQCD);
	p->addModel(modelQCDEXP);
	p->addModel(modelPI);
	p->addModel(modelPIExp);
	p->addModel(modelPEG);
	p->addModel(modelMixer);
	p->addModel(modelLPG);
	p->addModel(modelLIO);
	p->addModel(modelL4);
	p->addModel(modelL4Q);
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
