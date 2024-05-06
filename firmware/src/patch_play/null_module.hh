#pragma once
#include "CoreModules/CoreProcessor.hh"

namespace MetaModule
{

class NullModule : public CoreProcessor {
public:
	NullModule() = default;

	void update() override {
	}

	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
	}

	float get_output(int output_id) const override {
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}
};

} // namespace MetaModule
