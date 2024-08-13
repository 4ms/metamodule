#pragma once
#include "util/math.hh"
#include "util/parameter.h"
#include <cmath>

using namespace MathTools;

class FreqShift {
public:
	Parameter<float> shift;
	Parameter<float> mix;
	Parameter<float> sampleRate;

	FreqShift()
	{

		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
		}
	}

	float update(float input)
	{
		if (sampleRate.isChanged()) {
			fConst0 = (1.0f / constrain(sampleRate.getValue(), 1.0f, 192000.0f));
		}

		float output = 0;
		float fSlow0 = (fConst0 * shift.getValue());
		float fTemp0 = float(input);
		float fTemp1 = (0.0256900005f * fRec1[1]);
		fRec1[0] = ((fTemp0 + (0.260502011f * fRec1[2])) - fTemp1);
		float fTemp2 = (1.86849999f * fRec0[1]);
		fRec0[0] = ((fRec1[2] + (fTemp2 + fTemp1)) - ((0.870685995f * fRec0[2]) + (0.260502011f * fRec1[0])));
		fRec2[0] = (fSlow0 + (fRec2[1] - std::floor((fSlow0 + fRec2[1]))));
		float fTemp3 = (6.28318548f * std::fmod(fRec2[0], 1.0f));
		float fTemp4 = (1.94632006f * fRec4[1]);
		fRec4[0] = ((fTemp0 + fTemp4) - (0.946569979f * fRec4[2]));
		float fTemp5 = (0.837740004f * fRec3[1]);
		fRec3[0] = ((fRec4[2] + ((0.946569979f * fRec4[0]) + fTemp5)) - ((0.063380003f * fRec3[2]) + fTemp4));
		output = float((((((0.870685995f * fRec0[0]) + fRec0[2]) - fTemp2) * std::cos(fTemp3)) -
						((((0.063380003f * fRec3[0]) + fRec3[2]) - fTemp5) * std::sin(fTemp3))));
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[2] = fRec0[1];
		fRec0[1] = fRec0[0];
		fRec2[1] = fRec2[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		auto mixAmount = mix.getValue();
		return (output * mixAmount + input * (1.0f - mixAmount));
	}

private:
	float fRec1[3];
	float fRec0[3];
	float fConst0;
	float fRec2[2];
	float fRec4[3];
	float fRec3[3];
};
