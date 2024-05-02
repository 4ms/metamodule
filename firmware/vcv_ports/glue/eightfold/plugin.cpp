#include "plugin.hpp"

Plugin *pluginInstance;

void init(Plugin *p) {
	pluginInstance = p;

	p->addModel(modelSDOrcasHeartV2);
	// p->addModel(modelSDFormation);
	// p->addModel(modelSDLines);
}
