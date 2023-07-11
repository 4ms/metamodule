#pragma once
#include "VCV-adaptor/VCV_module_wrapper.hh"
#include "VCV-adaptor/common.hpp"
#include "VCV-adaptor/engine/Light.hpp"
#include "VCV-adaptor/engine/LightInfo.hpp"
#include "VCV-adaptor/engine/Param.hpp"
#include "VCV-adaptor/engine/ParamQuantity.hpp"
#include "VCV-adaptor/engine/Port.hpp"
#include "VCV-adaptor/engine/PortInfo.hpp"
#include "VCV-adaptor/json.hpp"
#include <vector>

namespace rack::engine
{

struct Module : VCVModuleWrapper {
	int64_t id = -1;
	ParamQuantity stubParamQuantity;
	PortInfo stubInputInfo;
	PortInfo stubOutputInfo;
	LightInfo stubLightInfo;

	// Expander not supported
	struct Expander {
		int64_t moduleId = -1;
		Module *module = nullptr;
		void *producerMessage = nullptr;
		void *consumerMessage = nullptr;
		bool messageFlipRequested = false;
		void requestMessageFlip() {
			messageFlipRequested = true;
		}
	};
	Expander leftExpander;
	Expander rightExpander;

	// Bypass not supported:
	// struct BypassRoute {
	// 	int inputId = -1;
	// 	int outputId = -1;
	// };
	// std::vector<BypassRoute> bypassRoutes;

	void config(unsigned num_params, unsigned num_inputs, unsigned num_outputs, unsigned num_lights = 0) {
		params.resize(num_params);
		inputs.resize(num_inputs);
		outputs.resize(num_outputs);
		lights.resize(num_lights);

		param_scales.resize(num_params);
	}

	template<class TParamQuantity = ParamQuantity>
	TParamQuantity *configParam(int paramId,
								float minValue,
								float maxValue,
								float defaultValue,
								std::string_view name = "",
								std::string_view unit = "",
								float displayBase = 0.f,
								float displayMultiplier = 1.f,
								float displayOffset = 0.f) {
		if (paramId < (int)param_scales.size()) {
			param_scales[paramId].range = maxValue - minValue;
			param_scales[paramId].offset = minValue;
		}

		return nullptr;
	}

	template<class TSwitchQuantity = SwitchQuantity>
	TSwitchQuantity *configSwitch(int paramId,
								  float minValue,
								  float maxValue,
								  float defaultValue,
								  std::string_view name = "",
								  std::vector<std::string> labels = {}) {
		return configParam<TSwitchQuantity>(paramId, minValue, maxValue, defaultValue, name);
		//sw->labels = labels
	}

	template<class TSwitchQuantity = SwitchQuantity>
	TSwitchQuantity *configButton(int paramId, std::string_view name = "") {
		return configParam<TSwitchQuantity>(paramId, 0.f, 1.f, 0.f, name);
		// sq->randomizeEnabled = false;
	}

	template<class TPortInfo = PortInfo>
	TPortInfo *configInput(int portId, std::string_view name = "") {
		return &stubInputInfo;
	}

	template<class TPortInfo = PortInfo>
	TPortInfo *configOutput(int portId, std::string_view name = "") {
		return &stubOutputInfo;
	}

	template<class TLightInfo = LightInfo>
	TLightInfo *configLight(int lightId, std::string_view name = "") {
		return &stubLightInfo;
	}

	void configBypass(int inputId, int outputId) {
		printf("Bypass not supported\n");
		// Bypass not supported
	}

	// Not supported:
	std::string_view createPatchStorageDirectory() {
		return "";
	}
	std::string_view getPatchStorageDirectory() {
		return "";
	}

	// Model* not supported
	// plugin::Model *getModel() {
	// 	return model;
	// }

	int64_t getId() {
		return id;
	}
	int getNumParams() {
		return params.size();
	}
	Param &getParam(int index) {
		return params[index];
	}
	int getNumInputs() {
		return inputs.size();
	}
	Input &getInput(int index) {
		return inputs[index];
	}
	int getNumOutputs() {
		return outputs.size();
	}
	Output &getOutput(int index) {
		return outputs[index];
	}
	int getNumLights() {
		return lights.size();
	}
	Light &getLight(int index) {
		return lights[index];
	}
	ParamQuantity *getParamQuantity(int index) {
		return &stubParamQuantity;
	}
	PortInfo *getInputInfo(int index) {
		return &stubInputInfo;
	}
	PortInfo *getOutputInfo(int index) {
		return &stubOutputInfo;
	}
	LightInfo *getLightInfo(int index) {
		return &stubLightInfo;
	}
	Expander &getLeftExpander() {
		return leftExpander;
	}
	Expander &getRightExpander() {
		return rightExpander;
	}
	Expander &getExpander(int side) {
		return side ? rightExpander : leftExpander;
	}

	virtual void processBypass(const ProcessArgs &args) {
	}

	virtual json_t *toJson() {
		return nullptr;
	}
	virtual void fromJson(json_t *rootJ) {
	}
	virtual json_t *paramsToJson() {
		return nullptr;
	}
	virtual void paramsFromJson(json_t *rootJ) {
	}
	virtual json_t *dataToJson() {
		return nullptr;
	}
	virtual void dataFromJson(json_t *rootJ) {
	}

	///////////////////////
	// Events
	///////////////////////

	struct AddEvent {};
	virtual void onAdd(const AddEvent &e) {
	}

	struct RemoveEvent {};
	virtual void onRemove(const RemoveEvent &e) {
	}

	struct BypassEvent {};
	virtual void onBypass(const BypassEvent &e) {
	}

	struct UnBypassEvent {};
	virtual void onUnBypass(const UnBypassEvent &e) {
	}

	struct PortChangeEvent {
		bool connecting;
		Port::Type type;
		int portId;
	};
	virtual void onPortChange(const PortChangeEvent &e) {
	}

	struct SampleRateChangeEvent {
		float sampleRate;
		float sampleTime;
	};
	virtual void onSampleRateChange() {
	}
	virtual void onSampleRateChange(const SampleRateChangeEvent &e) {
	}

	struct ExpanderChangeEvent {
		bool side;
	};
	virtual void onExpanderChange(const ExpanderChangeEvent &e) {
	}

	struct ResetEvent {};
	virtual void onReset(const ResetEvent &e) {
	}

	struct RandomizeEvent {};
	virtual void onRandomize(const RandomizeEvent &e) {
	}

	struct SaveEvent {};
	virtual void onSave(const SaveEvent &e) {
	}

	struct SetMasterEvent {};
	virtual void onSetMaster(const SetMasterEvent &e) {
	}

	struct UnsetMasterEvent {};
	virtual void onUnsetMaster(const UnsetMasterEvent &e) {
	}

	bool isBypassed() {
		return false;
	}
	// TODO: What are these for?
	// PRIVATE void setBypassed(bool bypassed) {
	// }
	// PRIVATE const float *meterBuffer();
	// PRIVATE int meterLength();
	// PRIVATE int meterIndex();
	// PRIVATE void doProcess(const ProcessArgs &args);
	// PRIVATE static void jsonStripIds(json_t *rootJ);
};

} // namespace rack::engine
