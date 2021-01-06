#include "plugin.hpp"

Plugin *pluginInstance;

void init(Plugin *p)
{
	pluginInstance = p;

	// Add modules here
p->addModel(modelLowpassfilter);
p->addModel(modelLowpassgate);
p->addModel(modelClkmultiplier);
p->addModel(modelClkdivider);
	// p->addModel(modelDual_opener);
	// p->addModel(modelDspTemplate);
	// p->addModel(modelAdjTest);

	p->addModel(modelExpander);
	p->addModel(modelPatchPlayer);

	//Layout Templates:
	p->addModel(modelTemplate4);
	p->addModel(modelTemplate8);
	p->addModel(modelTemplate12);
	p->addModel(modelTemplate16);

	//CoreModules:
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

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
