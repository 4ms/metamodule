#include "plugin.hpp"

Plugin *pluginInstance;

void init(rack::Plugin *p) {
	pluginInstance = p;

	p->addModel(modelEvenVCO);
	p->addModel(modelPonyVCO);
	p->addModel(modelRampage);
	p->addModel(modelABC);
	p->addModel(modelAtte);
	p->addModel(modelAxBC);
	p->addModel(modelMixer);
	p->addModel(modelMixer2);
	p->addModel(modelMuDi);
	p->addModel(modelSlewLimiter);
	p->addModel(modelSlew);
	p->addModel(modelDualAtenuverter);
	p->addModel(modelPercall);
	p->addModel(modelHexmixVCA);
	p->addModel(modelChoppingKinky);
	p->addModel(modelKickall);
	p->addModel(modelSamplingModulator);
	p->addModel(modelMorphader);
	p->addModel(modelADSR);
	p->addModel(modelSTMix);
	p->addModel(modelChannelStrip);
	p->addModel(modelMotionMTR);
	p->addModel(modelSpringReverb);
	p->addModel(modelBurst);
	p->addModel(modelVoltio);
	p->addModel(modelOctaves);	
	p->addModel(modelBandit);
}
