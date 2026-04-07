#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <array>
#include <memory>

struct TestModule : public CoreProcessor {
	static constexpr unsigned NumJacks = 4;

	// Mono values
	std::array<float, NumJacks> outs{};

	void update() override {
	}
	void set_samplerate(float sr) override {
	}
	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
		if ((unsigned)input_id < NumJacks)
			outs[input_id] = val;
	}

	float get_output(int output_id) const override {
		if ((unsigned)output_id < NumJacks)
			return outs[output_id];
		return 0.f;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<TestModule>();
	}
};

struct TestPanel : public CoreProcessor {
	static constexpr unsigned NumJacks = 16;

	std::array<float, NumJacks> outs{};

	void update() override {
	}
	void set_samplerate(float sr) override {
	}
	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
		// Passthrough:
		if ((unsigned)input_id < NumJacks)
			outs[input_id] = val;
		printf("TestPanel: set_input(%d, %f)\n", input_id, val);
	}

	float get_output(int output_id) const override {
		if ((unsigned)output_id < NumJacks) {
			printf("TestPanel: get_output(%d) -> %f\n", output_id, outs[output_id]);
			return outs[output_id];
		}
		return 0.f;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<TestPanel>();
	}
};
