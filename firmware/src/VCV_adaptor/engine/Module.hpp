#pragma once
#include "VCV_adaptor/VCV_module_wrapper.hh"
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/engine/Light.hpp"
#include "VCV_adaptor/engine/LightInfo.hpp"
#include "VCV_adaptor/engine/Param.hpp"
#include "VCV_adaptor/engine/Port.hpp"
#include "VCV_adaptor/engine/PortInfo.hpp"
#include "VCV_adaptor/json.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include <vector>

namespace rack::engine
{

struct Module : VCVModuleWrapper {
	plugin::Model *model = nullptr;
	int64_t id = -1;

	std::vector<std::unique_ptr<PortInfo>> inputInfos;
	std::vector<std::unique_ptr<PortInfo>> outputInfos;
	std::vector<std::unique_ptr<LightInfo>> lightInfos;

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
		for (auto &x : params)
			x.value = 0;

		inputs.resize(num_inputs);
		for (auto &x : inputs)
			x.voltage = 0;

		outputs.resize(num_outputs);
		for (auto &x : outputs)
			x.voltage = 0;

		lights.resize(num_lights);
		for (auto &x : lights)
			x.value = 0;

		paramQuantities.resize(num_params);

		inputInfos.resize(num_inputs);

		outputInfos.resize(num_outputs);

		lightInfos.resize(num_lights);
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

		if (paramId >= (int)paramQuantities.size())
			return nullptr;

		if (paramQuantities[paramId])
			paramQuantities[paramId].reset();

		paramQuantities[paramId] = std::make_unique<TParamQuantity>();

		// TODO: is any of this necessary? In case a VCV module reads its own PQs?
		paramQuantities[paramId]->ParamQuantity::module = this;
		paramQuantities[paramId]->ParamQuantity::paramId = paramId;
		paramQuantities[paramId]->ParamQuantity::minValue = minValue;
		paramQuantities[paramId]->ParamQuantity::maxValue = maxValue;
		paramQuantities[paramId]->ParamQuantity::defaultValue = defaultValue;
		paramQuantities[paramId]->ParamQuantity::name = name;
		paramQuantities[paramId]->ParamQuantity::unit = unit;
		paramQuantities[paramId]->ParamQuantity::displayBase = displayBase;
		paramQuantities[paramId]->ParamQuantity::displayMultiplier = displayMultiplier;
		paramQuantities[paramId]->ParamQuantity::displayOffset = displayOffset;

		Param *p = &params[paramId];
		p->value = defaultValue;

		return static_cast<TParamQuantity *>(paramQuantities[paramId].get());
	}

	template<class TSwitchQuantity = SwitchQuantity>
	TSwitchQuantity *configSwitch(int paramId,
								  float minValue,
								  float maxValue,
								  float defaultValue,
								  std::string_view name = "",
								  std::vector<std::string> labels = {}) {
		TSwitchQuantity *sq = configParam<TSwitchQuantity>(paramId, minValue, maxValue, defaultValue, name);
		sq->snapEnabled = true;
		// sq->labels = labels;
		return sq;
	}

	template<class TSwitchQuantity = SwitchQuantity>
	TSwitchQuantity *configButton(int paramId, std::string_view name = "") {
		TSwitchQuantity *sq = configParam<TSwitchQuantity>(paramId, 0.f, 1.f, 0.f, name);
		// sq->randomizeEnabled = false;
		sq->snapEnabled = true;
		return sq;
	}

	template<class TPortInfo = PortInfo>
	TPortInfo *configInput(int portId, std::string_view name = "") {
		if (portId >= (int)inputs.size() || portId >= (int)inputInfos.size())
			return nullptr;

		if (inputInfos[portId])
			inputInfos[portId].reset();

		inputInfos[portId] = std::make_unique<TPortInfo>();

		// TODO: is any of this necessary? In case a VCV module reads its own inputInfos?
		inputInfos[portId]->PortInfo::module = this;
		inputInfos[portId]->PortInfo::type = Port::INPUT;
		inputInfos[portId]->PortInfo::portId = portId;
		inputInfos[portId]->PortInfo::name = name;
		return static_cast<TPortInfo *>(inputInfos[portId].get());
	}

	template<class TPortInfo = PortInfo>
	TPortInfo *configOutput(int portId, std::string_view name = "") {
		if (portId >= (int)outputs.size() || portId >= (int)outputInfos.size())
			return nullptr;

		if (outputInfos[portId])
			outputInfos[portId].reset();

		outputInfos[portId] = std::make_unique<TPortInfo>();

		// TODO: is any of this necessary? In case a VCV module reads its own outputInfos?
		outputInfos[portId]->PortInfo::module = this;
		outputInfos[portId]->PortInfo::type = Port::INPUT;
		outputInfos[portId]->PortInfo::portId = portId;
		outputInfos[portId]->PortInfo::name = name;
		return static_cast<TPortInfo *>(outputInfos[portId].get());
	}

	template<class TLightInfo = LightInfo>
	TLightInfo *configLight(int lightId, std::string_view name = "") {
		if (lightId >= (int)lights.size() || lightId >= (int)lightInfos.size())
			return nullptr;

		if (lightInfos[lightId])
			lightInfos[lightId].reset();

		lightInfos[lightId] = std::make_unique<TLightInfo>();

		// TODO: is any of this necessary? In case a VCV module reads its own lightInfos?
		lightInfos[lightId]->LightInfo::module = this;
		lightInfos[lightId]->LightInfo::lightId = lightId;
		lightInfos[lightId]->LightInfo::name = name;

		return static_cast<TLightInfo *>(lightInfos[lightId].get());
	}

	void configBypass(int inputId, int outputId) {
		// printf("Bypass not supported\n");
		// Bypass not supported
	}

	// Not supported:
	std::string_view createPatchStorageDirectory() {
		return "";
	}
	std::string_view getPatchStorageDirectory() {
		return "";
	}

	plugin::Model *getModel() {
		return model;
	}

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
		if (index >= (int)paramQuantities.size())
			return nullptr;
		return paramQuantities[index].get();
	}
	PortInfo *getInputInfo(int index) {
		if (index >= (int)inputInfos.size())
			return nullptr;
		return inputInfos[index].get();
	}
	PortInfo *getOutputInfo(int index) {
		if (index >= (int)outputInfos.size())
			return nullptr;
		return outputInfos[index].get();
	}
	LightInfo *getLightInfo(int index) {
		if (index >= (int)lightInfos.size())
			return nullptr;
		return lightInfos[index].get();
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
	virtual void onReset() {
	}
	virtual void onReset(const ResetEvent &e) {
	}

	struct RandomizeEvent {};
	virtual void onRandomize(const RandomizeEvent &e) {
	}

	virtual void onRandomize() {
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
