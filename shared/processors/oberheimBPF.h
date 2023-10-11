#pragma once
#include "util/math.hh"
#include "util/math_tables.hh"
#include "util/parameter.hh"
#include <algorithm>
#include <cmath>

class OberBPF {
public:
	Parameter<float> cutoff;
	Parameter<float> q;
	Parameter<float> sampleRate;

	float update(float input) {
		float output = 0;
		if (sampleRate.isChanged()) {
			auto tempSamplerate = MathTools::constrain(sampleRate.getValue(), 1.0f, 192000.0f);
			fConst0 = (3.14159274f / std::min<float>(192000.0f, std::max<float>(1.0f, float(tempSamplerate))));
		}
		if (q.isChanged() || cutoff.isChanged()) {
			calcFilterVariables();
		}
		input = input / MaxAudioValue;
		float fTemp0 = input - (fRec1[1] + (fSlow1 * fRec2[1]));
		float fTemp1 = fSlow3 * fTemp0;
		float fTemp2 = std::clamp<float>(fRec2[1] + fTemp1, MinAudioValue, MaxAudioValue);
		float fTemp3 = (fTemp2 * (1.0f - (0.333333343f * mydsp_faustpower2_f(fTemp2))));
		float fRec0 = fTemp3;
		fRec1[0] = (fRec1[1] + (fSlow4 * fTemp3));
		fRec2[0] = (fTemp1 + fTemp3);
		output = float(fRec0);
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];

		return output * MaxAudioValue;
	}

	OberBPF() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
		}

		cutoff.setValue(0.2f);
		q.setValue(1);
		sampleRate.setValue(48000);
	}

private:
	float fRec1[2];
	float fRec2[2];
	float fSlow0, fSlow1, fSlow2, fSlow3, fSlow4;
	float fConst0 = 1;

	static float mydsp_faustpower2_f(float value) {
		return (value * value);
	}

	void calcFilterVariables() {
		fSlow0 = std::tan((fConst0 * std::pow(10.0f, ((3.0f * float(cutoff.getValue()) + 1.0f)))));
		fSlow1 = ((1.0f / float(q.getValue())) + fSlow0);
		fSlow2 = ((fSlow0 * fSlow1) + 1.0f);
		fSlow3 = (fSlow0 / fSlow2);
		fSlow4 = (2.0f * fSlow0);
	}

	static constexpr float MinAudioValue = -10.f;
	static constexpr float MaxAudioValue = 10.f;
};
