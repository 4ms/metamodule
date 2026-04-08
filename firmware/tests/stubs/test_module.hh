#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <array>
#include <memory>

struct TestModule : public CoreProcessor {
	static constexpr unsigned NumJacks = 4;

	// Mono values
	std::array<float, NumJacks> mono{};

	void update() override {
	}
	void set_samplerate(float sr) override {
	}
	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
		if ((unsigned)input_id < NumJacks)
			mono[input_id] = val;
	}

	float get_output(int output_id) const override {
		if ((unsigned)output_id < NumJacks)
			return mono[output_id];
		return 0.f;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<TestModule>();
	}
};
