#include "plugin.hpp"
#include "modules/genericModule.hh"

Plugin *pluginInstance;
std::unique_ptr<CentralData> centralData;

/////// TODO: Auto generated:
#include "CoreModules/info/enosc_info.hh"
auto modelEnOsc = createModelFromInfo<EnOscInfo>();
#include "CoreModules/info/buffmult_info.hh"
auto modelBuffMult = createModelFromInfo<BuffMultInfo>();
///////

void init(Plugin *p)
{
	centralData = std::make_unique<CentralData>();

	pluginInstance = p;

	// TODO: Auto generated
	// Add modules here
	p->addModel(modelEnOsc);
	p->addModel(modelBuffMult);
	///////

	p->addModel(modelHubMedium);
	p->addModel(modelInfosc01);
	p->addModel(modelDjembe);
	p->addModel(modelBipolarsource);
	p->addModel(modelMultilfo);
	p->addModel(modelEnvelopefollower);
	p->addModel(modelVoltagesource);
	p->addModel(modelNoise);
	p->addModel(modelSampleplayer);
	p->addModel(modelSlewlimiter);
	p->addModel(modelBandpassfilter);
	p->addModel(modelHighpassfilter);
	p->addModel(modelReverb);
	p->addModel(modelKarplus);
	p->addModel(modelGateseq16);
	p->addModel(modelGateseq8);
	p->addModel(modelOctave);
	p->addModel(modelMinmax);
	p->addModel(modelDrum);
	p->addModel(modelComplexenvelope);
	p->addModel(modelFmosc);
	p->addModel(modelStereomixer);
	p->addModel(modelPanner);
	p->addModel(modelGateconverter);
	p->addModel(modelDetune);
	p->addModel(modelPitchshift);
	p->addModel(modelSwitch4to1);
	p->addModel(modelSwitch1to4);
	p->addModel(modelEightstepprob);
	p->addModel(modelQuantizer);
	p->addModel(modelFourstep);
	p->addModel(modelEightstep);
	p->addModel(modelBitcrush);
	p->addModel(modelPhaser);
	p->addModel(modelFreqshift);
	p->addModel(modelLowpassfilter);
	p->addModel(modelLowpassgate);
	p->addModel(modelClkmultiplier);
	p->addModel(modelClkdivider);
	p->addModel(modelLFO);
	p->addModel(modelAD);
	p->addModel(modelCrossfade);
	p->addModel(modelMixer4);
	p->addModel(modelLogic);
	p->addModel(modelSampleHold);
	p->addModel(modelAtt);
	p->addModel(modelFadeDelay);
	p->addModel(modelVCA);
	p->addModel(modelComparator);
	p->addModel(modelSend);
	p->addModel(modelHubMini);
	p->addModel(modelInfosc64bphas);
}
