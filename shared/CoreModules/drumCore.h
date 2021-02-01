#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/envelope.h"
#include "processors/twoOpFMOscillator.h"
#include "util/math_tables.hh"

using namespace MathTools;

class DrumCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		auto freqCalc =
			baseFrequency + (envelopes[pitchEnvelope].update(gateIn) * 4000.0f * (pitchAmount * pitchAmount));

		osc.set_frequency(freqCalc * expTable.interp(constrain(pitchCV, 0.0f, 1.0f)));
		osc.modAmount = envelopes[fmEnvelope].update(gateIn) * fmAmount;
		auto noiseOut = randomNumber(-1.0f, 1.0f) * envelopes[noiseEnvelope].update(gateIn);

		auto toneOutput = osc.update() * envelopes[toneEnvelope].update(gateIn);

		drumOutput = interpolate(toneOutput, noiseOut, noiseBlend);
	}

	DrumCore()
	{
		for (int i = 0; i < 4; i++) {
			envelopes[i].sustainEnable = false;
			envelopes[i].set_attack_curve(0);
			envelopes[i].set_decay_curve(0);
			envelopes[i].set_release_curve(0.5f);
			envelopes[i].set_sustain(0.2f);
		}

		envelopes[toneEnvelope].set_envelope_time(0, 1);
		envelopes[toneEnvelope].set_envelope_time(1, 50);
		envelopes[toneEnvelope].set_envelope_time(2, 100);
		envelopes[toneEnvelope].set_envelope_time(3, 2000);
		envelopes[toneEnvelope].set_release_curve(1.0f);

		envelopes[fmEnvelope].set_envelope_time(0, 1);
		envelopes[fmEnvelope].set_envelope_time(1, 0);
		envelopes[fmEnvelope].set_envelope_time(2, 300);
		envelopes[fmEnvelope].set_envelope_time(3, 700);

		envelopes[noiseEnvelope].set_envelope_time(0, 1);
		envelopes[noiseEnvelope].set_envelope_time(1, 0);
		envelopes[noiseEnvelope].set_envelope_time(2, 30);
		envelopes[noiseEnvelope].set_envelope_time(3, 700);
		envelopes[noiseEnvelope].set_release_curve(0.0f);

		envelopes[pitchEnvelope].set_envelope_time(0, 5.0);
		envelopes[pitchEnvelope].set_envelope_time(1, 0);
		envelopes[pitchEnvelope].set_envelope_time(2, 50);
		envelopes[pitchEnvelope].set_envelope_time(3, 2000);
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				baseFrequency = map_value(val, 0.0f, 1.0f, 10.0f, 1000.0f);
				break;
			case 1: // pitch envelope
				envelopes[pitchEnvelope].set_envelope_time(2, pitchDecayTimes.interp(val));
				envelopes[pitchEnvelope].set_envelope_time(3, pitchReleaseTimes.interp(val));
				envelopes[pitchEnvelope].set_sustain(pitchBreakPoint.interp(val));
				break;
			case 2:
				pitchAmount = val;
				break;
			case 3:
				osc.ratioFine = map_value(val, 0.0f, 1.0f, 1.0f, 16.0f);
				break;
			case 4: // fm envelope
				envelopes[fmEnvelope].set_envelope_time(0, map_value(val, 0.0f, 1.0f, 1.0f, 100.0f));
				envelopes[fmEnvelope].set_envelope_time(2, map_value(val, 0.0f, 1.0f, 10.0f, 8000.0f));
				envelopes[fmEnvelope].set_envelope_time(3, map_value(val, 0.0f, 1.0f, 10.0f, 3000.0f));
				envelopes[fmEnvelope].set_sustain(map_value(val, 0.0f, 1.0f, 0.0f, 0.3f));
				break;
			case 5:
				fmAmount = val;
				break;
			case 6: // tone envelope
				envelopes[toneEnvelope].set_envelope_time(0, toneAttackTimes.interp(val));
				envelopes[toneEnvelope].set_envelope_time(1, toneHoldTimes.interp(val));
				envelopes[toneEnvelope].set_envelope_time(2, toneDecayTimes.interp(val));
				envelopes[toneEnvelope].set_envelope_time(3, toneReleaseTimes.interp(val));
				envelopes[toneEnvelope].set_sustain(toneBreakPoint.interp(val));
				break;
			case 7: // noise envelope
				envelopes[noiseEnvelope].set_envelope_time(0, map_value(val, 0.0f, 1.0f, 1.0f, 50.0f));
				envelopes[noiseEnvelope].set_envelope_time(2, map_value(val, 0.0f, 1.0f, 30.0f, 100.0f));
				envelopes[noiseEnvelope].set_envelope_time(3, map_value(val, 0.0f, 1.0f, 100.0f, 3000.0f));
				envelopes[noiseEnvelope].set_sustain(map_value(val, 0.0f, 1.0f, 0.0f, 0.25f));
				break;
			case 8:
				noiseBlend = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		for (int i = 0; i < 4; i++) {
			envelopes[i].set_samplerate(sr);
		}
		osc.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				gateIn = val;
				break;
			case 1:
				pitchCV = val;
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
	enum { pitchEnvelope, fmEnvelope, toneEnvelope, noiseEnvelope };

	Envelope envelopes[4];
	TwoOpFM osc;

	float gateIn = 0;
	float drumOutput = 0;
	float baseFrequency = 50;
	float noiseBlend = 0.5f;
	float pitchAmount = 0;
	float fmAmount = 0;
	float pitchCV = 20;

	InterpArray<float, 4> pitchDecayTimes = {10, 10, 200, 500};
	InterpArray<float, 4> pitchBreakPoint = {0, 0.1, 0.2, 1};
	InterpArray<float, 4> pitchReleaseTimes = {50, 300, 500, 3000};

	InterpArray<float, 7> toneAttackTimes = {1, 1, 3, 5, 7, 9, 20};
	InterpArray<float, 6> toneHoldTimes = {0, 20, 50, 70, 100, 600};
	InterpArray<float, 3> toneDecayTimes = {10, 200, 600};
	InterpArray<float, 4> toneBreakPoint = {0.1, 0.2, 0.8};
	InterpArray<float, 3> toneReleaseTimes = {10, 500, 4000};
};
