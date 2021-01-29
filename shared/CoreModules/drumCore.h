#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/macroEnvelope.h"
#include "processors/twoOpFMOscillator.h"

using namespace MathTools;

class DrumCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		float pitchEnvelopeOut = 0;
		float toneEnvelopeOut = 0;
		float noiseEnvelopeOut = 0;
		float fmEnvelopeOut = 0;

		pitchEnvelopeOut = pitchEnvelope.update(gateIn);
		toneEnvelopeOut = toneEnvelope.update(gateIn);
		noiseEnvelopeOut = noiseEnvelope.update(gateIn);
		fmEnvelopeOut = fmEnvelope.update(gateIn);

		osc.set_frequency(baseFrequency + (pitchEnvelopeOut * 2000.0f * pitchAmount));
		osc.modAmount = fmEnvelopeOut * fmAmount;
		auto noiseOut = randomNumber(-1.0f, 1.0f) * noiseEnvelopeOut;

		auto toneOutput = osc.update() * toneEnvelopeOut;

		drumOutput = interpolate(toneOutput, noiseOut, noiseBlend);
	}

	DrumCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				baseFrequency = map_value(val, 0.0f, 1.0f, 20.0f, 1000.0f);
				break;
			case 1:
				pitchEnvelope.set_time(val);
				break;
			case 2:
				pitchAmount = val;
				break;
			case 3:
				osc.ratioFine = map_value(val, 0.0f, 1.0f, 1.0f, 16.0f);
				break;
			case 4:
				fmEnvelope.set_time(val);
				break;
			case 5:
				fmAmount = val;
				break;
			case 6:
				toneEnvelope.set_time(val);
				break;
			case 7:
				noiseEnvelope.set_time(val);
				break;
			case 8:
				noiseBlend = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		pitchEnvelope.set_samplerate(sr);
		toneEnvelope.set_samplerate(sr);
		noiseEnvelope.set_samplerate(sr);
		fmEnvelope.set_samplerate(sr);
		osc.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				gateIn = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = drumOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<DrumCore>();
	}
	static constexpr char typeID[20] = "DRUM";
	static constexpr char description[] = "Drum";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	MacroEnvelope pitchEnvelope{false};
	MacroEnvelope fmEnvelope{false};
	MacroEnvelope toneEnvelope{false};
	MacroEnvelope noiseEnvelope{false};
	TwoOpFM osc;

	float gateIn = 0;
	float drumOutput = 0;
	float baseFrequency = 50;
	float noiseBlend = 0.5f;
	float pitchAmount = 0;
	float fmAmount = 0;
};
