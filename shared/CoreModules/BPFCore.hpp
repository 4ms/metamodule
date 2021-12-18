#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/BPF_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "processors/bpf.h"
#include "processors/oberheimBPF.h"
#include "util/math.hh"

class BPFCore : public CoreProcessor {
	using Info = BPFInfo;
	using ThisCore = BPFCore;

public:
	BPFCore() = default;

	void update(void) override {
		float filterFreq = 523.25f * setPitchMultiple(constrain(cutoffCV + cutoffOffset, -1.0f, 1.0f));
		if (mode == 0) {
			bpf.q = map_value(filterQ, 0.0f, 1.0f, 1.0f, 20.0f);
			bpf.cutoff.setValue(filterFreq);
			signalOutput = bpf.update(signalInput);
		} else if (mode == 1) {
			ober.q = map_value(filterQ, 0.0f, 1.0f, 1.0f, 20.0f);
			ober.cutoff.setValue(audioFreqToNorm(filterFreq));
			signalOutput = ober.update(signalInput);
		}
	}

	void set_param(int const param_id, const float val) override {
		switch (param_id) {
			case 0:
				cutoffOffset = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
			case 1:
				filterQ = val;
				break;
			case 2:
				mode = val;
				break;
		}
	}

	void set_samplerate(const float sr) override {
		bpf.sampleRate.setValue(sr);
	}

	void set_input(const int input_id, const float val) override {
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				cutoffCV = val;
				break;
		}
	}

	float get_output(const int output_id) const override {
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOutput;
				break;
		}
		return output;
	}

	float get_led_brightness(const int led_id) const override {
		return mode;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	int mode = 0;
	float filterQ = 1;
	BandPassFilter bpf;
	OberBPF ober;
	float cutoffCV = 0;
	float cutoffOffset = 0;
	float signalInput = 0;
	float signalOutput = 0;
};
