#include "plugin.hh"
#include "generic_module.hh"

rack::Plugin *pluginInstance;
using namespace MetaModule;

//////////////// Auto generated ///////////////////////
// include and define models below here


///////////////////////////////////////////////////////

void init(rack::Plugin *p) {
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
}
