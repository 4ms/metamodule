#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/element_counter.hh"
#include "CoreModules/moduleFactory.hh"
#include "VCV-adaptor/dsp.hh"
#include "VCV-adaptor/light.hh"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/param.hh"
#include "VCV-adaptor/port.hh"
#include <array>
#include <memory>

template<typename Info, typename Core>
struct VCVCoreProcessor : CoreProcessor {
	struct ProcessArgs {
		float sampleRate;
		float sampleTime;
		int64_t frame;
	};

	virtual void process(const ProcessArgs &) = 0;

	void update() override {
		args.frame++;
		process(args);
	}

	void set_samplerate(float rate) override {
		args.sampleRate = rate;
		args.sampleTime = 1.f / rate;
	}

	void set_param(int id, float val) override {
		val *= param_scales[id].range;
		val += param_scales[id].offset;
		params[id].setValue(val);
	}

	void set_input(const int input_id, const float val) override {
		inputs[input_id].setVoltage(val * 5.f);
	}

	float get_output(const int output_id) const override {
		return outputs[output_id].getVoltage() / 5.f;
	}

	void mark_all_inputs_unpatched() override {
		for (auto &in : inputs)
			in.connected = false;
	}

	void mark_input_unpatched(const int input_id) override {
		inputs[input_id].connected = false;
	}

	void mark_input_patched(const int input_id) override {
		inputs[input_id].connected = true;
	}

	void mark_all_outputs_unpatched() override {
		for (auto &out : outputs)
			out.connected = false;
	}

	void mark_output_unpatched(const int output_id) override {
		outputs[output_id].connected = false;
	}

	void mark_output_patched(const int output_id) override {
		outputs[output_id].connected = true;
	}

	constinit static inline std::array<Param, ElementCount<Info>::count().num_params> params;
	constinit static inline std::array<Port, ElementCount<Info>::count().num_inputs> inputs;
	constinit static inline std::array<Port, ElementCount<Info>::count().num_outputs> outputs;
	constinit static inline std::array<Light, ElementCount<Info>::count().num_lights> lights;

	using ParamScale = typename ElementCount<Info>::ParamScale;
	constexpr static inline std::array<ParamScale, params.size()> param_scales = ElementCount<Info>::get_param_scales();

	ProcessArgs args{48000.f, 1.f / 48000.f, 0};

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<Core>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ElementInfoView::makeView<Info>());
	// clang-format on
};
