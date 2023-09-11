#pragma once
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/engine/Cable.hpp"
#include "VCV_adaptor/engine/Module.hpp"
#include "VCV_adaptor/engine/ParamHandle.hpp"
#include <vector>

namespace rack::engine
{

struct Engine {
	float getSampleRate() {
		return 48000;
	}

	// void setSuggestedSampleRate(float suggestedSampleRate);
	float getSampleTime() {
		return 1.f / getSampleRate();
	}
	// void yieldWorkers();
	// int64_t getBlock();
	// int64_t getFrame();
	// void setFrame(int64_t frame);
	// int64_t getBlockFrame();
	// double getBlockTime();
	// int getBlockFrames();
	// double getBlockDuration();
	// double getMeterAverage();
	// double getMeterMax();

	// size_t getNumModules();
	// size_t getModuleIds(int64_t *moduleIds, size_t len);
	// std::vector<int64_t> getModuleIds();
	// void addModule(Module *module);
	// void removeModule(Module *module);
	// bool hasModule(Module *module);
	// Module *getModule(int64_t moduleId);
	// Module *getModule_NoLock(int64_t moduleId);
	// void resetModule(Module *module);
	// void randomizeModule(Module *module);
	// void bypassModule(Module *module, bool bypassed);
	// json_t *moduleToJson(Module *module);
	// void moduleFromJson(Module *module, json_t *rootJ);
	// void prepareSaveModule(Module *module);
	// void prepareSave();

	// size_t getNumCables();
	// size_t getCableIds(int64_t *cableIds, size_t len);
	// std::vector<int64_t> getCableIds();
	// void addCable(Cable *cable);
	// void removeCable(Cable *cable);
	// bool hasCable(Cable *cable);
	// Cable *getCable(int64_t cableId);

	// void setParamValue(Module *module, int paramId, float value);
	// float getParamValue(Module *module, int paramId);
	// void setParamSmoothValue(Module *module, int paramId, float value);
	// float getParamSmoothValue(Module *module, int paramId);

	// void addParamHandle(ParamHandle *paramHandle);
	// void removeParamHandle(ParamHandle *paramHandle);
	// ParamHandle *getParamHandle(int64_t moduleId, int paramId);
	// ParamHandle *getParamHandle_NoLock(int64_t moduleId, int paramId);
	// DEPRECATED ParamHandle *getParamHandle(Module *module, int paramId);

	// void updateParamHandle(ParamHandle *paramHandle, int64_t moduleId, int paramId, bool overwrite = true);
	// void updateParamHandle_NoLock(ParamHandle *paramHandle, int64_t moduleId, int paramId, bool overwrite = true);

	// json_t *toJson();
	// void fromJson(json_t *rootJ);
};

} // namespace rack::engine
