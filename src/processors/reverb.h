#pragma once

#include "math.hh"
using namespace MathTools;

class Reverb : public AudioProcessor {
public:
	Reverb()
	{
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec9[l0] = 0.0f;
		}
		IOTA = 0;
		for (int l1 = 0; (l1 < 8192); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec8[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec11[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 8192); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec10[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec13[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 8192); l7 = (l7 + 1)) {
			fVec2[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec12[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec15[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 8192); l10 = (l10 + 1)) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec14[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec17[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 8192); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec19[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 8192); l16 = (l16 + 1)) {
			fVec5[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec18[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec21[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 8192); l19 = (l19 + 1)) {
			fVec6[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec20[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec23[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 8192); l22 = (l22 + 1)) {
			fVec7[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec22[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			fVec8[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec6[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 2048); l26 = (l26 + 1)) {
			fVec9[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec4[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2048); l28 = (l28 + 1)) {
			fVec10[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec2[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 1024); l30 = (l30 + 1)) {
			fVec11[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec0[l31] = 0.0f;
		}
	}

	virtual float update(float input)
	{
		float output = 0;
		float fSlow0 = float(fb1);
		float fSlow1 = float(damp);
		float fSlow2 = (1.0f - fSlow1);
		float fSlow3 = float(fb2);
		float fTemp0 = float(input);
		fRec9[0] = ((fSlow1 * fRec9[1]) + (fSlow2 * fRec8[1]));
		fVec0[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec9[0]));
		fRec8[0] = fVec0[((IOTA - iConst1) & 8191)];
		fRec11[0] = ((fSlow1 * fRec11[1]) + (fSlow2 * fRec10[1]));
		fVec1[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec11[0]));
		fRec10[0] = fVec1[((IOTA - iConst2) & 8191)];
		fRec13[0] = ((fSlow1 * fRec13[1]) + (fSlow2 * fRec12[1]));
		fVec2[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec13[0]));
		fRec12[0] = fVec2[((IOTA - iConst3) & 8191)];
		fRec15[0] = ((fSlow1 * fRec15[1]) + (fSlow2 * fRec14[1]));
		fVec3[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec15[0]));
		fRec14[0] = fVec3[((IOTA - iConst4) & 8191)];
		fRec17[0] = ((fSlow1 * fRec17[1]) + (fSlow2 * fRec16[1]));
		fVec4[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec17[0]));
		fRec16[0] = fVec4[((IOTA - iConst5) & 8191)];
		fRec19[0] = ((fSlow1 * fRec19[1]) + (fSlow2 * fRec18[1]));
		fVec5[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec19[0]));
		fRec18[0] = fVec5[((IOTA - iConst6) & 8191)];
		fRec21[0] = ((fSlow1 * fRec21[1]) + (fSlow2 * fRec20[1]));
		fVec6[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec21[0]));
		fRec20[0] = fVec6[((IOTA - iConst7) & 8191)];
		fRec23[0] = ((fSlow1 * fRec23[1]) + (fSlow2 * fRec22[1]));
		fVec7[(IOTA & 8191)] = (fTemp0 + (fSlow0 * fRec23[0]));
		fRec22[0] = fVec7[((IOTA - iConst8) & 8191)];
		float fTemp1 = ((((((((fRec8[0] + fRec10[0]) + fRec12[0]) + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) +
						 fRec22[0]) +
						(fSlow3 * fRec6[1]));
		fVec8[(IOTA & 2047)] = fTemp1;
		fRec6[0] = fVec8[((IOTA - iConst9) & 2047)];
		float fRec7 = (0.0f - (fSlow3 * fTemp1));
		float fTemp2 = (fRec6[1] + (fRec7 + (fSlow3 * fRec4[1])));
		fVec9[(IOTA & 2047)] = fTemp2;
		fRec4[0] = fVec9[((IOTA - iConst10) & 2047)];
		float fRec5 = (0.0f - (fSlow3 * fTemp2));
		float fTemp3 = (fRec4[1] + (fRec5 + (fSlow3 * fRec2[1])));
		fVec10[(IOTA & 2047)] = fTemp3;
		fRec2[0] = fVec10[((IOTA - iConst11) & 2047)];
		float fRec3 = (0.0f - (fSlow3 * fTemp3));
		float fTemp4 = (fRec2[1] + (fRec3 + (fSlow3 * fRec0[1])));
		fVec11[(IOTA & 1023)] = fTemp4;
		fRec0[0] = fVec11[((IOTA - iConst12) & 1023)];
		float fRec1 = (0.0f - (fSlow3 * fTemp4));
		output = float((fRec1 + fRec0[1]));
		fRec9[1] = fRec9[0];
		IOTA = (IOTA + 1);
		fRec8[1] = fRec8[0];
		fRec11[1] = fRec11[0];
		fRec10[1] = fRec10[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec21[1] = fRec21[0];
		fRec20[1] = fRec20[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
		return output;
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			fb1 = val;
			fb2 = val;
		}
		if (param_id == 1) {
			damp = val;
		}
	}
	virtual void set_samplerate(float sr)
	{
		fConst0 = constrain(sr, 1.0f, 192000.0f);
		iConst1 = int((0.0253061224f * fConst0));
		iConst2 = int((0.0269387756f * fConst0));
		iConst3 = int((0.0289569162f * fConst0));
		iConst4 = int((0.0307482984f * fConst0));
		iConst5 = int((0.0322448984f * fConst0));
		iConst6 = int((0.033809524f * fConst0));
		iConst7 = int((0.0353061222f * fConst0));
		iConst8 = int((0.0366666652f * fConst0));
		iConst9 = constrain(int((0.0126077095f * fConst0)) + -1, 0, 1024);
		iConst10 = constrain(int((0.00999999978f * fConst0)) + -1, 0, 1024);
		iConst11 = constrain(int((0.00773242628f * fConst0)) + -1, 0, 1024);
		iConst12 = constrain(int((0.00510204071f * fConst0)) + -1, 0, 1024);
	}

private:
	float fb1 = 0.2;
	float fb2 = 0.5;
	float damp = 0.3;

	float fRec9[2];
	int IOTA;
	float fVec0[8192];
	float fConst0;
	int iConst1;
	float fRec8[2];
	float fRec11[2];
	float fVec1[8192];
	int iConst2;
	float fRec10[2];
	float fRec13[2];
	float fVec2[8192];
	int iConst3;
	float fRec12[2];
	float fRec15[2];
	float fVec3[8192];
	int iConst4;
	float fRec14[2];
	float fRec17[2];
	float fVec4[8192];
	int iConst5;
	float fRec16[2];
	float fRec19[2];
	float fVec5[8192];
	int iConst6;
	float fRec18[2];
	float fRec21[2];
	float fVec6[8192];
	int iConst7;
	float fRec20[2];
	float fRec23[2];
	float fVec7[8192];
	int iConst8;
	float fRec22[2];
	float fVec8[2048];
	int iConst9;
	float fRec6[2];
	float fVec9[2048];
	int iConst10;
	float fRec4[2];
	float fVec10[2048];
	int iConst11;
	float fRec2[2];
	float fVec11[1024];
	int iConst12;
	float fRec0[2];
};
