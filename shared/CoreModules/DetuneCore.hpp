#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/Detune_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "processors/pitchShift.h"
#include "util/math.hh"

class InterpRandomGenerator {
public:
	float frequency = 1;

	float update() {
		phaccu += frequency / sampleRate;
		if (phaccu >= 1.0f) {
			phaccu -= 1.0f;
			lastValue = currentValue;
			currentValue = MathTools::randomNumber(-1.0f, 1.0f);
		}

		outputValue = MathTools::interpolate(lastValue, currentValue, phaccu);
		return (outputValue);
	}

	void set_samplerate(float sr) {
		sampleRate = sr;
	}

private:
	float sampleRate = 48000.f;
	float currentValue = 0;
	float lastValue = 0;
	float phaccu = 0;
	float outputValue = 0;
};

class DetuneCore : public CoreProcessor {
	using Info = DetuneInfo;
	using ThisCore = DetuneCore;

public:
	DetuneCore() {
		p.mix = 1.0f;
		p.windowSize = 240;
	}

	void update() override {
		float addWow = 0;
		float addFlutter = 0;
		float finalWow = 0;
		float finalFlutter = 0;
		if (detuneCvConnected == false) {
			finalWow = wowDepth;
			finalFlutter = flutterDepth;
		} else {
			finalWow = MathTools::constrain(wowDepth + cvAmount, 0.0f, 1.0f);
			finalFlutter = MathTools::constrain(flutterDepth + cvAmount, 0.0f, 1.0f);
		}
		addWow = wowGen.update() * (finalWow * finalWow);
		addFlutter = flutterGen.update() * (finalFlutter * finalFlutter);
		p.shiftAmount = addWow + addFlutter;
		signalOutput = p.update(signalInput);
	}

	void set_param(const int param_id, const float val) override {
		switch (param_id) {
			case 0:
				wowGen.frequency = MathTools::map_value(val, 0.0f, 1.0f, 0.1f, 5.0f);
				break;
			case 1:
				wowDepth = val;
				break;
			case 2:
				flutterGen.frequency = MathTools::map_value(val, 0.0f, 1.0f, 5.0f, 30.0f);
				break;
			case 3:
				flutterDepth = val;
				break;
		}
	}

	void set_samplerate(const float sr) override {
		p.setSampleRate(sr);
		flutterGen.set_samplerate(sr);
		wowGen.set_samplerate(sr);
	}

	void set_input(const int input_id, const float val) override {
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				cvAmount = val;
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

	void mark_input_unpatched(const int input_id) override {
		if (input_id == 1)
			detuneCvConnected = false;
	}

	void mark_input_patched(const int input_id) override {
		if (input_id == 1)
			detuneCvConnected = true;
	}

	float get_led_brightness(const int led_id) const override {
		return 0.f;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	PitchShift<9600> p;
	float flutterDepth = 0;
	float wowDepth = 0;

	float signalInput = 0;
	float signalOutput = 0;

	bool detuneCvConnected = false;
	float cvAmount = 0;

	InterpRandomGenerator flutterGen;
	InterpRandomGenerator wowGen;
};
