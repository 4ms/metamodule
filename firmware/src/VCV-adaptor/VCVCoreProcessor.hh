#pragma once
#include "CoreModules/moduleFactory.hh"
#include "VCV-adaptor/light.hh"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/param.hh"
#include "VCV-adaptor/port.hh"
#include "coreProcessor.h"
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
	// These are defined in the info header (FIXME: calculate them by iterating Info::Elements)
	std::array<Param, NUM_PARAMS> params;
	std::array<Port, NUM_INPUTS> inputs;
	std::array<Port, NUM_OUTPUTS> outputs;
	std::array<Light, NUM_LIGHTS> lights;

	ProcessArgs args{48000.f, 1.f / 48000.f, 0};

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<Core>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ElementInfoView::makeView<Info>());
	// clang-format on
};
