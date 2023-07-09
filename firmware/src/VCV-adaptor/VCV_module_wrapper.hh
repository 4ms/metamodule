#pragma once
#include "CoreModules/coreProcessor.h"
#include "VCV-adaptor/light.hh"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/param.hh"
#include "VCV-adaptor/port.hh"
#include "elements/param_scales.hh"
#include <array>
#include <memory>
#include <vector>

struct VCVModuleWrapper : CoreProcessor {
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
		if (id < (int)param_scales.size()) {
			val *= param_scales[id].range;
			val += param_scales[id].offset;
		}
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

	// constexpr static typename ElementCount<Info>::Counts counts = ElementCount<Info>::count();

	std::vector<Param> params;
	std::vector<Port> inputs;
	std::vector<Port> outputs;
	std::vector<Light> lights;
	std::vector<PotElementHelper::ParamScale> param_scales;

	ProcessArgs args{48000.f, 1.f / 48000.f, 0};

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	// static std::unique_ptr<CoreProcessor> create() { return std::make_unique<Core>(); }
	// static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ElementInfoView::makeView<Info>());
	// clang-format on
};
