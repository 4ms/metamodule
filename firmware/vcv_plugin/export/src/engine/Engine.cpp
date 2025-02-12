#include "engine/Engine.hpp"

namespace rack::engine
{

struct Engine::Internal {
	float sample_rate = 48000.f;
};

Engine::Engine()
	: internal{new Internal{}} {
}

Engine::~Engine() {
	delete internal;
}

// clang-format off

void Engine::clear(){}
void Engine::clear_NoLock(){}
void Engine::stepBlock(int frames){}
void Engine::setMasterModule(Module *module){}
void Engine::setMasterModule_NoLock(Module *module){}
Module Engine::*getMasterModule(){ return {}; }

float Engine::getSampleRate() { 
	return internal->sample_rate; 
}

void Engine::setSampleRate(float sampleRate) {
	internal->sample_rate = sampleRate;
}

void Engine::setSuggestedSampleRate(float suggestedSampleRate){}

float Engine::getSampleTime() { 
	return 1.f / internal->sample_rate; 
}

void Engine::yieldWorkers(){}
int64_t Engine::getFrame(){ return {}; }
int64_t Engine::getBlock(){ return {}; }
int64_t Engine::getBlockFrame(){ return {}; }
double Engine::getBlockTime(){ return {}; }
int Engine::getBlockFrames(){ return {}; }
double Engine::getBlockDuration(){ return {}; }
double Engine::getMeterAverage(){ return {}; }
double Engine::getMeterMax(){ return {}; }

// Modules
size_t Engine::getNumModules(){ return {}; }
size_t Engine::getModuleIds(int64_t *moduleIds, size_t len){ return {}; }
std::vector<int64_t> Engine::getModuleIds(){ return {}; }
void Engine::addModule(Module *module){}
void Engine::removeModule(Module *module){}
void Engine::removeModule_NoLock(Module *module){}
bool Engine::hasModule(Module *module){ return {}; }
Module *Engine::getModule(int64_t moduleId){ return {}; }
Module *Engine::getModule_NoLock(int64_t moduleId){ return {}; }
void Engine::resetModule(Module *module){}
void Engine::randomizeModule(Module *module){}
void Engine::bypassModule(Module *module, bool bypassed){}
json_t *Engine::moduleToJson(Module *module){ return {}; }
void Engine::moduleFromJson(Module *module, json_t *rootJ){}
void Engine::prepareSaveModule(Module *module){}
void Engine::prepareSave(){}

// Cables
size_t Engine::getNumCables(){ return {}; }
size_t Engine::getCableIds(int64_t *cableIds, size_t len){ return {}; }
std::vector<int64_t> Engine::getCableIds(){ return {}; }
void Engine::addCable(Cable *cable){}
void Engine::addCable_NoLock(Cable *cable){}
void Engine::removeCable(Cable *cable){}
void Engine::removeCable_NoLock(Cable *cable){}
bool Engine::hasCable(Cable *cable){ return {}; }
Cable* Engine::getCable(int64_t cableId){ return {}; }

// Params
void Engine::setParamValue(Module *module, int paramId, float value){
	module->set_param(paramId, value);
}

float Engine::getParamValue(Module *module, int paramId){ 
	return module->getParam(paramId).getValue();
}

void Engine::setParamSmoothValue(Module *module, int paramId, float value){
	setParamValue(module, paramId, value);
}

float Engine::getParamSmoothValue(Module *module, int paramId){ 
	return getParamValue(module, paramId);
}

// ParamHandles
void Engine::addParamHandle(ParamHandle *paramHandle){}
void Engine::removeParamHandle(ParamHandle *paramHandle){}
void Engine::removeParamHandle_NoLock(ParamHandle *paramHandle){}
ParamHandle* Engine::getParamHandle(int64_t moduleId, int paramId){ return {}; }
ParamHandle* Engine::getParamHandle_NoLock(int64_t moduleId, int paramId){ return {}; }
ParamHandle* Engine::getParamHandle(Module *module, int paramId){ return {}; }
void Engine::updateParamHandle(ParamHandle *paramHandle, int64_t moduleId, int paramId, bool overwrite){}
void Engine::updateParamHandle_NoLock(ParamHandle *paramHandle, int64_t moduleId, int paramId, bool overwrite){}

json_t* Engine::toJson(){ return {}; }
void Engine::fromJson(json_t *rootJ){}

void Engine::startFallbackThread(){}

// clang-format on
} // namespace rack::engine
