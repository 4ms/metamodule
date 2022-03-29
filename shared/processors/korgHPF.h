#pragma once

#include "util/math.hh"
#include "util/math_tables.hh"
#include "util/parameter.hh"
#include <algorithm>
#include <cmath>

using namespace MathTools;

class KorgHPF {
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

		float fTemp0 = float(input);
		float fTemp1 = (fTemp0 - fRec3[1]);
		float fTemp2 = (fTemp0 - (fRec3[1] + (fSlow6 * (((fSlow0 * fTemp1) - fRec1[1]) - (fSlow7 * fRec2[1])))));
		float fRec0 = (fSlow5 * fTemp2);
		float fTemp3 = (fSlow9 * fTemp2);
		float fTemp4 = (fTemp3 - fRec2[1]);
		fRec1[0] = (fRec1[1] + (fSlow8 * (fTemp3 - ((fSlow3 * fTemp4) + (fRec1[1] + fRec2[1])))));
		fRec2[0] = (fRec2[1] + (fSlow8 * fTemp4));
		fRec3[0] = (fRec3[1] + (fSlow8 * fTemp1));
		output = float(fRec0);
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];

		return constrain(output, -1.0f, 1.0f);
	}

	KorgHPF() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
		}

		cutoff.setValue(0.2f);
		q.setValue(1);
		sampleRate.setValue(48000);
	}

private:
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fSlow0, fSlow1, fSlow2, fSlow3, fSlow4, fSlow5, fSlow6, fSlow7, fSlow8, fSlow9;

	float fConst0 = 1;

	static float mydsp_faustpower2_f(float value) {
		return (value * value);
	}

	void calcFilterVariables() {
		fSlow0 = std::tan((fConst0 * std::pow(10.0f, ((3.0f * float(cutoff)) + 1.0f))));
		fSlow1 = (float(q) + -0.707000017f);
		fSlow2 = (fSlow0 + 1.0f);
		fSlow3 = (fSlow0 / fSlow2);
		fSlow4 = (1.0f - (0.215215757f * (((fSlow0 * fSlow1) * (1.0f - fSlow3)) / fSlow2)));
		fSlow5 = (1.0f / fSlow4);
		fSlow6 = (1.0f / fSlow2);
		fSlow7 = (0.0f - fSlow3);
		fSlow8 = (2.0f * fSlow3);
		fSlow9 = (0.215215757f * (fSlow1 / fSlow4));
	}
};
