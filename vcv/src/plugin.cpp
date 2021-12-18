#include "plugin.hpp"
#include "modules/genericModule.hh"

Plugin *pluginInstance;
std::unique_ptr<CentralData> centralData;

//////////////// Auto generated ///////////////////////
// include and define models below here

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

#include "CoreModules/info/EnOsc_info.hh"
auto modelEnOsc = createModelFromInfo<EnOscInfo>();

#include "CoreModules/info/BuffMult_info.hh"
auto modelBuffMult = createModelFromInfo<BuffMultInfo>();
///////////////////////////////////////////////////////

void init(Plugin *p)
{
	centralData = std::make_unique<CentralData>();

	pluginInstance = p;

	//////////////// Auto generated ///////////////////////
	// Add models below here
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

	// p->addModel(modelInfosc01);
	// p->addModel(modelDjembe);
	// p->addModel(modelBipolarsource);
	// p->addModel(modelMultilfo);
	// p->addModel(modelEnvelopefollower);
	// p->addModel(modelVoltagesource);
	// p->addModel(modelNoise);
	// p->addModel(modelSampleplayer);
	// p->addModel(modelSlewlimiter);
	// p->addModel(modelBandpassfilter);
	// p->addModel(modelHighpassfilter);
	// p->addModel(modelReverb);
	// p->addModel(modelKarplus);
	// p->addModel(modelGateseq16);
	// p->addModel(modelGateseq8);
	// p->addModel(modelOctave);
	// p->addModel(modelMinmax);
	// p->addModel(modelDrum);
	// p->addModel(modelComplexenvelope);
	// p->addModel(modelFmosc);
	// p->addModel(modelStereomixer);
	// p->addModel(modelPanner);
	// p->addModel(modelGateconverter);
	// p->addModel(modelDetune);
	// p->addModel(modelPitchshift);
	// p->addModel(modelSwitch4to1);
	// p->addModel(modelSwitch1to4);
	// p->addModel(modelEightstepprob);
	// p->addModel(modelQuantizer);
	// p->addModel(modelFourstep);
	// p->addModel(modelEightstep);
	// p->addModel(modelBitcrush);
	// p->addModel(modelPhaser);
	// p->addModel(modelFreqshift);
	// p->addModel(modelLowpassfilter);
	// p->addModel(modelLowpassgate);
	// p->addModel(modelClkmultiplier);
	// p->addModel(modelClkdivider);
	// p->addModel(modelLFO);
	// p->addModel(modelAD);
	// p->addModel(modelCrossfade);
	// p->addModel(modelMixer4);
	// p->addModel(modelLogic);
	// p->addModel(modelSampleHold);
	// p->addModel(modelAtt);
	// p->addModel(modelFadeDelay);
	// p->addModel(modelVCA);
	// p->addModel(modelComparator);
	// p->addModel(modelSend);
	// p->addModel(modelHubMini);
	// p->addModel(modelInfosc64bphas);
	///////////////////////////////////////////////////////
}
