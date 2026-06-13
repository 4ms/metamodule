#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <array>
#include <memory>

// A test module with controllable poly buffers on inputs and outputs.
// Used by patch_player poly cable tests.
// The test stub (plugin_module.cc) detects this via dynamic_cast and returns its poly buffers.
struct TestPolyModule : public CoreProcessor {
	static constexpr unsigned NumOutputs = 2;
	static constexpr unsigned NumInputs = 2;

	// Poly output data: voltages[output_id][channel] and channel count
	std::array<std::array<float, MaxPolyChannels>, NumOutputs> output_poly{};
	std::array<uint8_t, NumOutputs> output_channels{1, 1};

	// Poly input data: voltages[input_id][channel] and channel count
	std::array<std::array<float, MaxPolyChannels>, NumInputs> input_poly{};
	std::array<uint8_t, NumInputs> input_channels{0, 0};

	// Mono values (used when poly buffers are not consulted)
	std::array<float, NumOutputs> outputs_mono{};
	std::array<float, NumInputs> inputs_mono{};

	void update() override {
	}
	void set_samplerate(float sr) override {
	}
	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
		if ((unsigned)input_id < NumInputs)
			inputs_mono[input_id] = val;
	}

	float get_output(int output_id) const override {
		if ((unsigned)output_id < NumOutputs)
			return outputs_mono[output_id];
		return 0.f;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<TestPolyModule>();
	}
};
