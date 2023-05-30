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
		inputs[input_id].setVoltage(val);
	}
	float get_output(const int output_id) const override {
		return outputs[output_id].getVoltage();
	}

	std::array<Param, Info::Knobs.size()> params;
	std::array<Port, Info::InJacks.size()> inputs;
	std::array<Port, Info::OutJacks.size()> outputs;
	std::array<Light, Info::Leds.size()> lights;

	ProcessArgs args{48000.f, 1.f / 48000.f, 0};

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<Core>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ElementInfoView::makeView<Info>());
	// clang-format on
};
