#include "plugin.hpp"

Plugin *pluginInstance;

void init(rack::Plugin *p) {
	pluginInstance = p;

	p->addModel(modelBlinds);
	p->addModel(modelBraids);
	p->addModel(modelBranches);
	p->addModel(modelClouds);
	p->addModel(modelElements);
	p->addModel(modelFrames);
	p->addModel(modelKinks);
	p->addModel(modelLinks);
	p->addModel(modelMarbles);
	p->addModel(modelPlaits);
	p->addModel(modelRings);
	p->addModel(modelRipples);
	p->addModel(modelShades);
	p->addModel(modelShelves);
	p->addModel(modelStages);
	p->addModel(modelStreams);
	p->addModel(modelTides);
	p->addModel(modelTides2);
	p->addModel(modelVeils);
	p->addModel(modelWarps);
}
