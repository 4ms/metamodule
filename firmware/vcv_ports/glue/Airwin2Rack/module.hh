#pragma once
#include "AirwinRegistry.h"
#include "CoreModules/CoreProcessor.hh"
#include "airwin_consolidated_base.h"
#include "util/input_output_buffer.hh"

namespace MetaModuleAirwindows
{

// Use the same param/input/output indices as Airwin2Rack,
// so that patches made on VCV work on MM.

static constexpr unsigned maxParams = 10;
enum ParamIds { PARAM_0 = 0, ATTEN_0 = 11, IN_LEVEL = 22, OUT_LEVEL, NUM_PARAMS };
enum InputIds { INPUT_L, INPUT_R, CV_0, NUM_INPUTS = CV_0 + maxParams };
enum OutputIds { OUTPUT_L, OUTPUT_R, NUM_OUTPUTS };

struct Module : CoreProcessor {
	static constexpr size_t BlockSize = 32;

	Module(unsigned registry_idx) {
		fx = AirwinRegistry::registry[registry_idx].generator();
		num_params = std::min<unsigned>(AirwinRegistry::registry[registry_idx].nParams, maxParams);
	}

	void update() override {
		const float gain = params[IN_LEVEL] * 0.2f;

		inL_buf.put(ins[INPUT_L] * gain);
		inR_buf.put((input_patched[INPUT_R] ? ins[INPUT_R] : ins[INPUT_L]) * gain);

		if (inL_buf.full()) {
			for (auto i = 0u; i < num_params; i++) {
				auto param = params[PARAM_0 + i];

				if (input_patched[CV_0 + i]) {
					auto cv = ins[CV_0 + i] * 0.4f * (params[ATTEN_0 + i] - 0.5f);
					param = std::clamp(param + cv, 0.f, 1.f);
				}

				fx->setParameter(i, param);
			}

			float *in[2] = {inL_buf.data(), inR_buf.data()};
			float *out[2] = {outL_buf.data(), outR_buf.data()};

			fx->processReplacing(in, out, BlockSize);

			inL_buf.reset();
			inR_buf.reset();
			outL_buf.reset();
			outR_buf.reset();
		}

		outs[OUTPUT_L] = outL_buf.get();
		outs[OUTPUT_R] = outR_buf.get();
	}

	void set_samplerate(float sr) override {
		fx->setSampleRate(sr);
	}

	void set_param(int param_id, float val) override {
		if ((unsigned)param_id < params.size())
			params[param_id] = val;
	}

	void set_input(int input_id, float val) override {
		if ((unsigned)input_id < ins.size()) {
			ins[input_id] = val;
		}
	}

	float get_output(int output_id) const override {
		if ((unsigned)output_id < NUM_OUTPUTS)
			return outs[output_id] * 5.f * params[OUT_LEVEL];
		else
			return 0.f;
	}

	void mark_input_patched(int input_id) override {
		if ((unsigned)input_id < NUM_INPUTS)
			input_patched[input_id] = true;
	}

	void mark_input_unpatched(int input_id) override {
		if ((unsigned)input_id < NUM_INPUTS)
			input_patched[input_id] = true;
	}

	unsigned num_params{};
	std::unique_ptr<AirwinConsolidatedBase> fx;

private:
	std::array<float, NUM_PARAMS> params;
	std::array<float, NUM_OUTPUTS> outs;
	std::array<float, NUM_INPUTS> ins;
	std::array<bool, NUM_INPUTS> input_patched;

	InputBuffer<float, BlockSize> inL_buf;
	InputBuffer<float, BlockSize> inR_buf;
	OutputBuffer<float, BlockSize> outL_buf;
	OutputBuffer<float, BlockSize> outR_buf;
};

} // namespace MetaModuleAirwindows
