#pragma once

#include "processors/tools/cubicDist.h"
#include "processors/tools/delayLine.h"
#include "util/math.hh"
#include "util/math_tables.hh"
#include "util/parameter.h"
#include <cmath>

using namespace MathTools;

class Phaser {
public:
	Parameter<float> lfoDepth;
	Parameter<float> feedback;
	Parameter<float> lfoSpeed;
	Parameter<float> freqMax;
	Parameter<float> freqMin;
	Parameter<float> width;
	Parameter<float> sampleRate;
	float update(float input)
	{
		if (sampleRate.isChanged()) {
			fConst0 = constrain(sampleRate.getValue(), 1.0f, 192000.0f);
			fConst1 = (1.0f / fConst0);
			fConst2 = (6.28318548f / fConst0);
		}

		int changeDetected = 0;
		changeDetected += lfoDepth.isChanged();
		changeDetected += feedback.isChanged();
		changeDetected += lfoSpeed.isChanged();
		changeDetected += freqMax.isChanged();
		changeDetected += freqMin.isChanged();
		changeDetected += width.isChanged();
		if (changeDetected > 0) {
			fVslider0 = lfoDepth.getValue();
			fVslider1 = map_value(width.getValue(), 0.0f, 1.0f, 50.0f, 5000.0f);
			fVslider2 = feedback.getValue();
			fVslider3 = map_value(freqMin.getValue(), 0.0f, 1.0f, 1.0f, 10000.0f);
			fVslider4 = map_value(freqMax.getValue(), 0.0f, 1.0f, 1.0f, 10000.0f);
			fVslider5 = map_value(lfoSpeed.getValue(), 0.0f, 1.0f, 0.1f, 10.0f);
			fSlow0 = (0.5f * float(fVslider0));
			fSlow1 = (1.0f - fSlow0);
			fSlow2 = expf((fConst1 * (0.0f - (3.14159274f * float(fVslider1)))));
			fSlow3 = fSlow2 * fSlow2;
			fSlow4 = float(fVslider2);
			fSlow5 = (0.0f - (2.0f * fSlow2));
			fSlow6 = float(fVslider3);
			fSlow7 = (fConst2 * fSlow6);
			fSlow8 = (0.5f * (0.0f - (fConst2 * (fSlow6 - float(fVslider4)))));
			fSlow9 = (fConst2 * float(fVslider5));
			fSlow10 = std::sin(fSlow9);
			fSlow11 = std::cos(fSlow9);
		}
		float fTemp0 = input;
		iVec0[0] = 1;
		fRec7[0] = ((fSlow10 * fRec8[1]) + (fSlow11 * fRec7[1]));
		fRec8[0] = ((float((1 - iVec0[1])) + (fSlow11 * fRec8[1])) - (fSlow10 * fRec7[1]));
		float fTemp1 = std::cos((fSlow7 + (fSlow8 * (1.0f - fRec7[0]))));
		fRec6[0] = ((fTemp0 + (fSlow4 * fRec0[1])) - ((fSlow5 * (fRec6[1] * fTemp1)) + (fSlow3 * fRec6[2])));
		fRec5[0] = ((fSlow3 * (fRec6[0] - fRec5[2])) + (fRec6[2] + (fSlow5 * (fTemp1 * (fRec6[1] - fRec5[1])))));
		fRec4[0] = ((fSlow3 * (fRec5[0] - fRec4[2])) + (fRec5[2] + (fSlow5 * (fTemp1 * (fRec5[1] - fRec4[1])))));
		fRec3[0] = ((fSlow3 * (fRec4[0] - fRec3[2])) + (fRec4[2] + (fSlow5 * (fTemp1 * (fRec4[1] - fRec3[1])))));
		fRec2[0] = ((fSlow3 * (fRec3[0] - fRec2[2])) + (fRec3[2] + (fSlow5 * (fTemp1 * (fRec3[1] - fRec2[1])))));
		fRec1[0] = ((fSlow3 * (fRec2[0] - fRec1[2])) + (fRec2[2] + (fSlow5 * (fTemp1 * (fRec2[1] - fRec1[1])))));
		fRec0[0] = ((fSlow3 * fRec1[0]) + ((fSlow5 * (fTemp1 * fRec1[1])) + fRec1[2]));
		float output = float(((fSlow1 * fTemp0) + (fSlow0 * fRec0[0])));
		iVec0[1] = iVec0[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec1[2] = fRec1[1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		return output;
	}

	Phaser()
	{
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec7[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec8[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) {
			fRec6[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 3); l6 = (l6 + 1)) {
			fRec3[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
			fRec2[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec1[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec0[l9] = 0.0f;
		}
	}

private:
	float fVslider0;
	float fConst0;
	float fConst1;
	float fVslider1;
	float fVslider2;
	int iVec0[2];
	float fConst2;
	float fVslider3;
	float fVslider4;
	float fVslider5;
	float fRec7[2];
	float fRec8[2];
	float fRec6[3];
	float fRec5[3];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec0[2];
	float fSlow0;
	float fSlow1;
	float fSlow2;
	float fSlow3;
	float fSlow4;
	float fSlow5;
	float fSlow6;
	float fSlow7;
	float fSlow8;
	float fSlow9;
	float fSlow10;
	float fSlow11;
};
