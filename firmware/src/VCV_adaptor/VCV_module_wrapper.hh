#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "VCV_adaptor/engine/Light.hpp"
#include "VCV_adaptor/engine/Param.hpp"
#include "VCV_adaptor/engine/ParamQuantity.hpp"
#include "VCV_adaptor/engine/Port.hpp"
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
		if (id < (int)paramQuantities.size()) {
			val *= (paramQuantities[id]->maxValue - paramQuantities[id]->minValue);
			val += paramQuantities[id]->minValue;

			if (paramQuantities[id]->snapEnabled)
				val = std::round(val);

			paramQuantities[id]->setDisplayValue(val);
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

	std::vector<rack::engine::Param> params;
	std::vector<rack::engine::Input> inputs;
	std::vector<rack::engine::Output> outputs;
	std::vector<rack::engine::Light> lights;

	std::vector<std::unique_ptr<rack::engine::ParamQuantity>> paramQuantities;

	ProcessArgs args{48000.f, 1.f / 48000.f, 0};
};
