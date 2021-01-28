#include "plugin.hpp"

Plugin *pluginInstance;
CentralData *centralData;

void init(Plugin *p)
{
	centralData = new CentralData;

	pluginInstance = p;

	// Add modules here 
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

	p->addModel(modelExpander);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup
	// times of Rack.
}
