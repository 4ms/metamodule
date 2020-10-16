#pragma once

#include "../util/math_tables.hh"
#include "audio_processor.hh"
//#include "debug.hh"
#include "math.hh"
#include "tools/cubicDist.h"
#include "tools/delayLine.h"
#include <cmath>
#include <algorithm>

using namespace MathTools;

class Phaser : public AudioProcessor {
public:
	

	virtual float update(float input)
	{
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
		set_samplerate(48000.0f);
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

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			
		}
		if (param_id == 1) {
			
		}

		lfoDepth=0.5;
		lfoSpeed=0.1;
		freqMax=0.9;
		freqMin=0.1;
		width=0.9;
		feedback=0.9;

		fVslider0 = lfoDepth;
		fVslider1 = map_value(width,0,1,50,5000);
		fVslider2 = feedback;
		fVslider3 = map_value(freqMin,0,1,1,10000);
		fVslider4 = map_value(freqMax,0,1,1,10000);
		fVslider5 = lfoSpeed;
		fSlow0 = (0.5f * float(fVslider0));
		fSlow1 = (1.0f - fSlow0);
		fSlow2 = std::exp((fConst1 * (0.0f - (3.14159274f * float(fVslider1)))));
		fSlow3 = fSlow2*fSlow2;
		fSlow4 = float(fVslider2);
		fSlow5 = (0.0f - (2.0f * fSlow2));
		fSlow6 = float(fVslider3);
		fSlow7 = (fConst2 * fSlow6);
		fSlow8 = (0.5f * (0.0f - (fConst2 * (fSlow6 - float(fVslider4)))));
		fSlow9 = (fConst2 * float(fVslider5));
		fSlow10 = std::sin(fSlow9);
		fSlow11 = std::cos(fSlow9);
	}
	virtual void set_samplerate(float sr)
	{
		fSampleRate = sr;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (6.28318548f / fConst0);
	}

private:

float fVslider0;
	int fSampleRate;
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

		float lfoDepth;
		float feedback;
		float lfoSpeed;
		float freqMax;
		float freqMin;
		float width;
};
