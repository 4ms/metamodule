#pragma once

#include "util/math.hh"
#include "util/math_tables.hh"
#include "util/parameter.hh"
#include <algorithm>
#include <cmath>

using namespace MathTools;

class LowPassFilter {
public:
	Parameter<float> cutoff;
	Parameter<float> q;
	Parameter<float> sampleRate;

	float update(float input) {
		float output = 0;
		if (sampleRate.isChanged()) {
			auto tempSamplerate = constrain(sampleRate.getValue(), 1.0f, 192000.0f);
			fConst0 = (3.14159274f / min<float>(192000.0f, max<float>(1.0f, float(tempSamplerate))));
		}
		if (q.isChanged() || cutoff.isChanged()) {
			calcFilterVariables();
		}

		fRec0[0] = (float(input) - (fSlow3 * ((fSlow4 * fRec0[2]) + (fSlow5 * fRec0[1]))));
		output = float((fSlow3 * (fRec0[2] + (fRec0[0] + (2.0f * fRec0[1])))));
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		return constrain(output, -1.0f, 1.0f);
	}

	LowPassFilter() {
		for (int i = 0; i < 3; i++) {
			fRec0[i] = 0.0f;
		}
		cutoff.setValue(262);
		q.setValue(1);
		sampleRate.setValue(48000);
	}

private:
	float fRec0[3];
	float fSlow0, fSlow1, fSlow2, fSlow3, fSlow4, fSlow5;
	float fConst0 = 1;

	static float mydsp_faustpower2_f(float value) {
		return (value * value);
	}

	void calcFilterVariables() {
		fSlow0 = (1.0f / float(q.getValue()));
		fSlow1 = std::tan((fConst0 * float(cutoff.getValue())));
		fSlow2 = (1.0f / fSlow1);
		fSlow3 = (1.0f / (((fSlow0 + fSlow2) / fSlow1) + 1.0f));
		fSlow4 = (((fSlow2 - fSlow0) / fSlow1) + 1.0f);
		fSlow5 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow1))));
	}
};
