#pragma once

#include "util/math.hh"
#include "util/math_tables.hh"
#include "util/parameter.hh"
#include <algorithm>
#include <cmath>

using namespace MathTools;

class MoogLadder {
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

		float fTemp0 =
			((fSlow4 * (float(input) -
						(fSlow5 * (((fRec1[1] + (fSlow1 * fRec2[1])) + (fSlow6 * fRec3[1])) + (fSlow7 * fRec4[1]))))) -
			 fRec4[1]);
		float fTemp1 = ((fRec4[1] + (fSlow2 * fTemp0)) - fRec3[1]);
		float fTemp2 = ((fRec3[1] + (fSlow2 * fTemp1)) - fRec2[1]);
		float fTemp3 = ((fRec2[1] + (fSlow2 * fTemp2)) - fRec1[1]);
		float fRec0 = (fRec1[1] + (fSlow2 * fTemp3));
		fRec1[0] = (fRec1[1] + (fSlow8 * fTemp3));
		fRec2[0] = (fRec2[1] + (fSlow8 * fTemp2));
		fRec3[0] = (fRec3[1] + (fSlow8 * fTemp1));
		fRec4[0] = (fRec4[1] + (fSlow8 * fTemp0));
		output = float(fRec0);
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];

		return constrain(output, -1.0f, 1.0f);
	}

	MoogLadder() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
		}

		cutoff.setValue(1.0f);
		q.setValue(1);
		sampleRate.setValue(48000);
		fConst0 = (3.14159274f / min<float>(192000.0f, max<float>(1.0f, float(sampleRate.getValue()))));
	}

private:
	float fConst0;
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fSlow0, fSlow1, fSlow2, fSlow3, fSlow4, fSlow5, fSlow6, fSlow7, fSlow8;

	static float mydsp_faustpower4_f(float value) {
		return (((value * value) * value) * value);
	}
	static float mydsp_faustpower2_f(float value) {
		return (value * value);
	}
	static float mydsp_faustpower3_f(float value) {
		return ((value * value) * value);
	}

	void calcFilterVariables() {
		fSlow0 = cutoff.getValue();
		fSlow1 = std::tan((fConst0 * std::pow(10.0f, ((2.88000011f * fSlow0) + 1.0f))));
		fSlow2 = (fSlow1 / (fSlow1 + 1.0f));
		fSlow3 = ((3.9000001f - (0.899999976f * std::pow((0.959999979f * fSlow0), 0.200000003f))) *
				  (q.getValue() + -0.707000017f));
		fSlow4 = (1.0f / ((0.0411641225f * (fSlow3 * mydsp_faustpower4_f(fSlow1))) + 1.0f));
		fSlow5 = (0.0411641225f * fSlow3);
		fSlow6 = mydsp_faustpower2_f(fSlow1);
		fSlow7 = mydsp_faustpower3_f(fSlow1);
		fSlow8 = (2.0f * fSlow2);
	}
};
