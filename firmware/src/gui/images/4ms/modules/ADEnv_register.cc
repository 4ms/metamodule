#include "CoreModules/moduleFactory.hh"
#include "lvgl.h"
LV_IMG_DECLARE(ADEnv_artwork_240);

static const bool ADEnv_faceplate_register =
	ModuleFactory::registerModuleFaceplate("ADEnv", (void *)(&ADEnv_artwork_240));
