#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "VCV_adaptor/engine/Light.hpp"
#include "VCV_adaptor/engine/Param.hpp"
#include "VCV_adaptor/engine/ParamQuantity.hpp"
#include "VCV_adaptor/engine/Port.hpp"
#include "VCV_adaptor/random.hpp"
#include <array>
#include <memory>
#include <vector>

struct ParamScale {
	float range;
	float offset;
};

struct VCVModuleWrapper : CoreProcessor {

	struct ProcessArgs {
		float sampleRate;
		float sampleTime;
		int64_t frame;
	};

	VCVModuleWrapper() ;

	virtual void process(const ProcessArgs &) = 0;

	void update() override ;

	void set_samplerate(float rate) override ;

	void set_param(int id, float val) override ;

	void set_input(const int input_id, const float val) override ;

	float get_output(const int output_id) const override ;

	float get_led_brightness(const int led_id) const override ;

	void mark_all_inputs_unpatched() override ;

	void mark_input_unpatched(const int input_id) override ;

	void mark_input_patched(const int input_id) override ;

	void mark_all_outputs_unpatched() override ;

	void mark_output_unpatched(const int output_id) override ;

	void mark_output_patched(const int output_id) override ;

	std::vector<rack::engine::Param> params;
	std::vector<rack::engine::Input> inputs;
	std::vector<rack::engine::Output> outputs;
	std::vector<rack::engine::Light> lights;

	std::vector<std::unique_ptr<rack::engine::ParamQuantity>> paramQuantities;

	ProcessArgs args{48000.f, 1.f / 48000.f, 0};
};
