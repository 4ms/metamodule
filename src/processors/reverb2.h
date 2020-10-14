#pragma once

#include "math.hh"
#include <algorithm>

static float mydsp_faustpower2_f(float value)
{
	return (value * value);
}

class Reverb2 : public AudioProcessor {
public:
	float dryWet = 0.5f;
	float level = 0.7;
	float eq2level = 1;
	float eq2freq = 0.2f;
	float eq1level = 1;
	float eq1freq = 0.7f;
	float hfDamping = 0.1;
	float midRT60 = 0.9;
	float lowRT60 = 0.9;
	float LFcrossover = 0.4;
	float preDelay = 0;

	Reverb2()
	{
		fVslider0 = float(-20.0f);
		fVslider1 = float(0.0f);
		fVslider2 = float(1500.0f);
		fVslider3 = float(0.0f);
		fVslider4 = float(315.0f);
		fVslider5 = float(0.0f);
		fVslider6 = float(2.0f);
		fVslider7 = float(6000.0f);
		fVslider8 = float(3.0f);
		fVslider9 = float(200.0f);
		fVslider10 = float(60.0f);

		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		IOTA = 0;
		for (int l1 = 0; (l1 < 16384); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec15[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec14[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 32768); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 16384); l6 = (l6 + 1)) {
			fVec2[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			fVec3[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec12[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec19[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec18[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 32768); l11 = (l11 + 1)) {
			fVec4[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 4096); l12 = (l12 + 1)) {
			fVec5[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec16[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec23[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec22[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 16384); l16 = (l16 + 1)) {
			fVec6[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 4096); l17 = (l17 + 1)) {
			fVec7[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec20[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec27[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec26[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 32768); l21 = (l21 + 1)) {
			fVec8[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 4096); l22 = (l22 + 1)) {
			fVec9[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec24[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec31[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec30[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 16384); l26 = (l26 + 1)) {
			fVec10[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2048); l27 = (l27 + 1)) {
			fVec11[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec28[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec35[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec34[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 16384); l31 = (l31 + 1)) {
			fVec12[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 4096); l32 = (l32 + 1)) {
			fVec13[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec32[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec39[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec38[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 16384); l36 = (l36 + 1)) {
			fVec14[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 4096); l37 = (l37 + 1)) {
			fVec15[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec36[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec43[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec42[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 16384); l41 = (l41 + 1)) {
			fVec16[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 2048); l42 = (l42 + 1)) {
			fVec17[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec40[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec4[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec5[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec6[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec7[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec8[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec9[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec10[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec11[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec3[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec2[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec45[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec44[l55] = 0.0f;
		}
	}

	virtual float update(float input)
	{
		fVslider10 = map_value(preDelay, 0.0f, 1.0f, 20.0f, 100.0f);
		fVslider9 = map_value(LFcrossover, 0.0f, 1.0f, 50.0f, 1000.0f);
		fVslider8 = map_value(lowRT60, 0.0f, 1.0f, 1.0f, 8.0f);
		fVslider6 = map_value(midRT60, 0.0f, 1.0f, 1.0f, 8.0f);
		fVslider7 = map_value(hfDamping, 0.0f, 1.0f, 1500.0f, 23520.0f);
		fVslider4 = map_value(eq1freq, 0.0f, 1.0f, 40.0f, 2500.0f);
		fVslider5 = map_value(eq1level, 0.0f, 1.0f, -15.0f, 15.0f);
		fVslider2 = map_value(eq2freq, 0.0f, 1.0f, 160.0f, 10000.0f);
		fVslider3 = map_value(eq2level, 0.0f, 1.0f, -15.0f, 15.0f);
		fVslider1 = map_value(dryWet, 0.0f, 1.0f, -1.0f, 1.0f);
		fVslider0 = map_value(level, 0.0f, 1.0f, -70, 40);
		float output = 0;
		float fSlow0 = (0.00100000005f * std::pow(10.0f, (0.0500000007f * float(fVslider0))));
		float fSlow1 = (0.00100000005f * float(fVslider1));
		float fSlow2 = float(fVslider2);
		float fSlow3 = std::pow(10.0f, (0.0500000007f * float(fVslider3)));
		float fSlow4 = (fConst1 * (fSlow2 / std::sqrt(std::max<float>(0.0f, fSlow3))));
		float fSlow5 = ((1.0f - fSlow4) / (fSlow4 + 1.0f));
		float fSlow6 = float(fVslider4);
		float fSlow7 = std::pow(10.0f, (0.0500000007f * float(fVslider5)));
		float fSlow8 = (fConst1 * (fSlow6 / std::sqrt(std::max<float>(0.0f, fSlow7))));
		float fSlow9 = ((1.0f - fSlow8) / (fSlow8 + 1.0f));
		float fSlow10 = float(fVslider6);
		float fSlow11 = std::exp((fConst3 / fSlow10));
		float fSlow12 = mydsp_faustpower2_f(fSlow11);
		float fSlow13 = std::cos((fConst1 * float(fVslider7)));
		float fSlow14 = (1.0f - (fSlow12 * fSlow13));
		float fSlow15 = (1.0f - fSlow12);
		float fSlow16 = (fSlow14 / fSlow15);
		float fSlow17 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow14) / mydsp_faustpower2_f(fSlow15)) + -1.0f)));
		float fSlow18 = (fSlow16 - fSlow17);
		float fSlow19 = (fSlow11 * (fSlow17 + (1.0f - fSlow16)));
		float fSlow20 = float(fVslider8);
		float fSlow21 = ((std::exp((fConst3 / fSlow20)) / fSlow11) + -1.0f);
		float fSlow22 = (1.0f / std::tan((fConst4 * float(fVslider9))));
		float fSlow23 = (1.0f / (fSlow22 + 1.0f));
		float fSlow24 = (1.0f - fSlow22);
		int iSlow25 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst7 * float(fVslider10)))));
		float fSlow26 = std::exp((fConst10 / fSlow10));
		float fSlow27 = mydsp_faustpower2_f(fSlow26);
		float fSlow28 = (1.0f - (fSlow27 * fSlow13));
		float fSlow29 = (1.0f - fSlow27);
		float fSlow30 = (fSlow28 / fSlow29);
		float fSlow31 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow28) / mydsp_faustpower2_f(fSlow29)) + -1.0f)));
		float fSlow32 = (fSlow30 - fSlow31);
		float fSlow33 = (fSlow26 * (fSlow31 + (1.0f - fSlow30)));
		float fSlow34 = ((std::exp((fConst10 / fSlow20)) / fSlow26) + -1.0f);
		float fSlow35 = std::exp((fConst15 / fSlow10));
		float fSlow36 = mydsp_faustpower2_f(fSlow35);
		float fSlow37 = (1.0f - (fSlow36 * fSlow13));
		float fSlow38 = (1.0f - fSlow36);
		float fSlow39 = (fSlow37 / fSlow38);
		float fSlow40 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow37) / mydsp_faustpower2_f(fSlow38)) + -1.0f)));
		float fSlow41 = (fSlow39 - fSlow40);
		float fSlow42 = (fSlow35 * (fSlow40 + (1.0f - fSlow39)));
		float fSlow43 = ((std::exp((fConst15 / fSlow20)) / fSlow35) + -1.0f);
		float fSlow44 = std::exp((fConst20 / fSlow10));
		float fSlow45 = mydsp_faustpower2_f(fSlow44);
		float fSlow46 = (1.0f - (fSlow45 * fSlow13));
		float fSlow47 = (1.0f - fSlow45);
		float fSlow48 = (fSlow46 / fSlow47);
		float fSlow49 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow46) / mydsp_faustpower2_f(fSlow47)) + -1.0f)));
		float fSlow50 = (fSlow48 - fSlow49);
		float fSlow51 = (fSlow44 * (fSlow49 + (1.0f - fSlow48)));
		float fSlow52 = ((std::exp((fConst20 / fSlow20)) / fSlow44) + -1.0f);
		float fSlow53 = std::exp((fConst25 / fSlow10));
		float fSlow54 = mydsp_faustpower2_f(fSlow53);
		float fSlow55 = (1.0f - (fSlow54 * fSlow13));
		float fSlow56 = (1.0f - fSlow54);
		float fSlow57 = (fSlow55 / fSlow56);
		float fSlow58 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow55) / mydsp_faustpower2_f(fSlow56)) + -1.0f)));
		float fSlow59 = (fSlow57 - fSlow58);
		float fSlow60 = (fSlow53 * (fSlow58 + (1.0f - fSlow57)));
		float fSlow61 = ((std::exp((fConst25 / fSlow20)) / fSlow53) + -1.0f);
		float fSlow62 = std::exp((fConst30 / fSlow10));
		float fSlow63 = mydsp_faustpower2_f(fSlow62);
		float fSlow64 = (1.0f - (fSlow63 * fSlow13));
		float fSlow65 = (1.0f - fSlow63);
		float fSlow66 = (fSlow64 / fSlow65);
		float fSlow67 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow64) / mydsp_faustpower2_f(fSlow65)) + -1.0f)));
		float fSlow68 = (fSlow66 - fSlow67);
		float fSlow69 = (fSlow62 * (fSlow67 + (1.0f - fSlow66)));
		float fSlow70 = ((std::exp((fConst30 / fSlow20)) / fSlow62) + -1.0f);
		float fSlow71 = std::exp((fConst35 / fSlow10));
		float fSlow72 = mydsp_faustpower2_f(fSlow71);
		float fSlow73 = (1.0f - (fSlow72 * fSlow13));
		float fSlow74 = (1.0f - fSlow72);
		float fSlow75 = (fSlow73 / fSlow74);
		float fSlow76 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow73) / mydsp_faustpower2_f(fSlow74)) + -1.0f)));
		float fSlow77 = (fSlow75 - fSlow76);
		float fSlow78 = (fSlow71 * (fSlow76 + (1.0f - fSlow75)));
		float fSlow79 = ((std::exp((fConst35 / fSlow20)) / fSlow71) + -1.0f);
		float fSlow80 = std::exp((fConst40 / fSlow10));
		float fSlow81 = mydsp_faustpower2_f(fSlow80);
		float fSlow82 = (1.0f - (fSlow81 * fSlow13));
		float fSlow83 = (1.0f - fSlow81);
		float fSlow84 = (fSlow82 / fSlow83);
		float fSlow85 =
			std::sqrt(std::max<float>(0.0f, ((mydsp_faustpower2_f(fSlow82) / mydsp_faustpower2_f(fSlow83)) + -1.0f)));
		float fSlow86 = (fSlow84 - fSlow85);
		float fSlow87 = (fSlow80 * (fSlow85 + (1.0f - fSlow84)));
		float fSlow88 = ((std::exp((fConst40 / fSlow20)) / fSlow80) + -1.0f);
		float fSlow89 = (0.0f - (std::cos((fConst1 * fSlow6)) * (fSlow9 + 1.0f)));
		float fSlow90 = (0.0f - (std::cos((fConst1 * fSlow2)) * (fSlow5 + 1.0f)));
		fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
		float fTemp0 = input;
		fVec0[(IOTA & 16383)] = fTemp0;
		fRec1[0] = (fSlow1 + (0.999000013f * fRec1[1]));
		float fTemp1 = (fRec1[0] + 1.0f);
		float fTemp2 = (1.0f - (0.5f * fTemp1));
		fRec15[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec15[1]) - (fRec11[1] + fRec11[2]))));
		fRec14[0] = ((fSlow18 * fRec14[1]) + (fSlow19 * (fRec11[1] + (fSlow21 * fRec15[0]))));
		fVec1[(IOTA & 32767)] = ((0.353553385f * fRec14[0]) + 9.99999968e-21f);
		float fTemp3 = float(0);
		fVec2[(IOTA & 16383)] = fTemp3;
		float fTemp4 = (0.300000012f * fVec2[((IOTA - iSlow25) & 16383)]);
		float fTemp5 = (((0.600000024f * fRec12[1]) + fVec1[((IOTA - iConst6) & 32767)]) - fTemp4);
		fVec3[(IOTA & 2047)] = fTemp5;
		fRec12[0] = fVec3[((IOTA - iConst8) & 2047)];
		float fRec13 = (0.0f - (0.600000024f * fTemp5));
		fRec19[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec19[1]) - (fRec7[1] + fRec7[2]))));
		fRec18[0] = ((fSlow32 * fRec18[1]) + (fSlow33 * (fRec7[1] + (fSlow34 * fRec19[0]))));
		fVec4[(IOTA & 32767)] = ((0.353553385f * fRec18[0]) + 9.99999968e-21f);
		float fTemp6 = (((0.600000024f * fRec16[1]) + fVec4[((IOTA - iConst12) & 32767)]) - fTemp4);
		fVec5[(IOTA & 4095)] = fTemp6;
		fRec16[0] = fVec5[((IOTA - iConst13) & 4095)];
		float fRec17 = (0.0f - (0.600000024f * fTemp6));
		fRec23[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec23[1]) - (fRec9[1] + fRec9[2]))));
		fRec22[0] = ((fSlow41 * fRec22[1]) + (fSlow42 * (fRec9[1] + (fSlow43 * fRec23[0]))));
		fVec6[(IOTA & 16383)] = ((0.353553385f * fRec22[0]) + 9.99999968e-21f);
		float fTemp7 = (fVec6[((IOTA - iConst17) & 16383)] + (fTemp4 + (0.600000024f * fRec20[1])));
		fVec7[(IOTA & 4095)] = fTemp7;
		fRec20[0] = fVec7[((IOTA - iConst18) & 4095)];
		float fRec21 = (0.0f - (0.600000024f * fTemp7));
		fRec27[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec27[1]) - (fRec5[1] + fRec5[2]))));
		fRec26[0] = ((fSlow50 * fRec26[1]) + (fSlow51 * (fRec5[1] + (fSlow52 * fRec27[0]))));
		fVec8[(IOTA & 32767)] = ((0.353553385f * fRec26[0]) + 9.99999968e-21f);
		float fTemp8 = (fTemp4 + ((0.600000024f * fRec24[1]) + fVec8[((IOTA - iConst22) & 32767)]));
		fVec9[(IOTA & 4095)] = fTemp8;
		fRec24[0] = fVec9[((IOTA - iConst23) & 4095)];
		float fRec25 = (0.0f - (0.600000024f * fTemp8));
		fRec31[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec31[1]) - (fRec10[1] + fRec10[2]))));
		fRec30[0] = ((fSlow59 * fRec30[1]) + (fSlow60 * (fRec10[1] + (fSlow61 * fRec31[0]))));
		fVec10[(IOTA & 16383)] = ((0.353553385f * fRec30[0]) + 9.99999968e-21f);
		float fTemp9 = (0.300000012f * fVec0[((IOTA - iSlow25) & 16383)]);
		float fTemp10 = (fVec10[((IOTA - iConst27) & 16383)] - (fTemp9 + (0.600000024f * fRec28[1])));
		fVec11[(IOTA & 2047)] = fTemp10;
		fRec28[0] = fVec11[((IOTA - iConst28) & 2047)];
		float fRec29 = (0.600000024f * fTemp10);
		fRec35[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec35[1]) - (fRec6[1] + fRec6[2]))));
		fRec34[0] = ((fSlow68 * fRec34[1]) + (fSlow69 * (fRec6[1] + (fSlow70 * fRec35[0]))));
		fVec12[(IOTA & 16383)] = ((0.353553385f * fRec34[0]) + 9.99999968e-21f);
		float fTemp11 = (fVec12[((IOTA - iConst32) & 16383)] - (fTemp9 + (0.600000024f * fRec32[1])));
		fVec13[(IOTA & 4095)] = fTemp11;
		fRec32[0] = fVec13[((IOTA - iConst33) & 4095)];
		float fRec33 = (0.600000024f * fTemp11);
		fRec39[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec39[1]) - (fRec8[1] + fRec8[2]))));
		fRec38[0] = ((fSlow77 * fRec38[1]) + (fSlow78 * (fRec8[1] + (fSlow79 * fRec39[0]))));
		fVec14[(IOTA & 16383)] = ((0.353553385f * fRec38[0]) + 9.99999968e-21f);
		float fTemp12 = ((fTemp9 + fVec14[((IOTA - iConst37) & 16383)]) - (0.600000024f * fRec36[1]));
		fVec15[(IOTA & 4095)] = fTemp12;
		fRec36[0] = fVec15[((IOTA - iConst38) & 4095)];
		float fRec37 = (0.600000024f * fTemp12);
		fRec43[0] = (0.0f - (fSlow23 * ((fSlow24 * fRec43[1]) - (fRec4[1] + fRec4[2]))));
		fRec42[0] = ((fSlow86 * fRec42[1]) + (fSlow87 * (fRec4[1] + (fSlow88 * fRec43[0]))));
		fVec16[(IOTA & 16383)] = ((0.353553385f * fRec42[0]) + 9.99999968e-21f);
		float fTemp13 = ((fVec16[((IOTA - iConst42) & 16383)] + fTemp9) - (0.600000024f * fRec40[1]));
		fVec17[(IOTA & 2047)] = fTemp13;
		fRec40[0] = fVec17[((IOTA - iConst43) & 2047)];
		float fRec41 = (0.600000024f * fTemp13);
		float fTemp14 = (fRec41 + fRec37);
		float fTemp15 = (fRec29 + (fRec33 + fTemp14));
		fRec4[0] =
			(fRec12[1] +
			 (fRec16[1] +
			  (fRec20[1] +
			   (fRec24[1] +
				(fRec28[1] +
				 (fRec32[1] + (fRec36[1] + (fRec40[1] + (fRec13 + (fRec17 + (fRec21 + (fRec25 + fTemp15))))))))))));
		fRec5[0] = ((fRec28[1] + (fRec32[1] + (fRec36[1] + (fRec40[1] + fTemp15)))) -
					(fRec12[1] + (fRec16[1] + (fRec20[1] + (fRec24[1] + (fRec13 + (fRec17 + (fRec25 + fRec21))))))));
		float fTemp16 = (fRec33 + fRec29);
		fRec6[0] = ((fRec20[1] + (fRec24[1] + (fRec36[1] + (fRec40[1] + (fRec21 + (fRec25 + fTemp14)))))) -
					(fRec12[1] + (fRec16[1] + (fRec28[1] + (fRec32[1] + (fRec13 + (fRec17 + fTemp16)))))));
		fRec7[0] = ((fRec12[1] + (fRec16[1] + (fRec36[1] + (fRec40[1] + (fRec13 + (fRec17 + fTemp14)))))) -
					(fRec20[1] + (fRec24[1] + (fRec28[1] + (fRec32[1] + (fRec21 + (fRec25 + fTemp16)))))));
		float fTemp17 = (fRec41 + fRec33);
		float fTemp18 = (fRec37 + fRec29);
		fRec8[0] = ((fRec16[1] + (fRec24[1] + (fRec32[1] + (fRec40[1] + (fRec17 + (fRec25 + fTemp17)))))) -
					(fRec12[1] + (fRec20[1] + (fRec28[1] + (fRec36[1] + (fRec13 + (fRec21 + fTemp18)))))));
		fRec9[0] = ((fRec12[1] + (fRec20[1] + (fRec32[1] + (fRec40[1] + (fRec13 + (fRec21 + fTemp17)))))) -
					(fRec16[1] + (fRec24[1] + (fRec28[1] + (fRec36[1] + (fRec17 + (fRec25 + fTemp18)))))));
		float fTemp19 = (fRec41 + fRec29);
		float fTemp20 = (fRec37 + fRec33);
		fRec10[0] = ((fRec12[1] + (fRec24[1] + (fRec28[1] + (fRec40[1] + (fRec13 + (fRec25 + fTemp19)))))) -
					 (fRec16[1] + (fRec20[1] + (fRec32[1] + (fRec36[1] + (fRec17 + (fRec21 + fTemp20)))))));
		fRec11[0] = ((fRec16[1] + (fRec20[1] + (fRec28[1] + (fRec40[1] + (fRec17 + (fRec21 + fTemp19)))))) -
					 (fRec12[1] + (fRec24[1] + (fRec32[1] + (fRec36[1] + (fRec13 + (fRec25 + fTemp20)))))));
		float fTemp21 = (0.370000005f * (fRec5[0] + fRec6[0]));
		float fTemp22 = (fSlow89 * fRec3[1]);
		fRec3[0] = (fTemp21 - (fTemp22 + (fSlow9 * fRec3[2])));
		float fTemp23 = (fSlow9 * fRec3[0]);
		float fTemp24 = (0.5f * ((fTemp23 + (fRec3[2] + (fTemp21 + fTemp22))) +
								 (fSlow7 * ((fTemp23 + (fTemp22 + fRec3[2])) - fTemp21))));
		float fTemp25 = (fSlow90 * fRec2[1]);
		fRec2[0] = (fTemp24 - (fTemp25 + (fSlow5 * fRec2[2])));
		float fTemp26 = (fSlow5 * fRec2[0]);
		output = float((0.5f * (fRec0[0] * ((fTemp0 * fTemp1) +
											(fTemp2 * ((fTemp26 + (fRec2[2] + (fTemp24 + fTemp25))) +
													   (fSlow3 * ((fTemp26 + (fTemp25 + fRec2[2])) - fTemp24))))))));
		float fTemp27 = (0.370000005f * (fRec5[0] - fRec6[0]));
		float fTemp28 = (fSlow89 * fRec45[1]);
		fRec45[0] = (fTemp27 - (fTemp28 + (fSlow9 * fRec45[2])));
		float fTemp29 = (fSlow9 * fRec45[0]);
		float fTemp30 = (0.5f * ((fTemp29 + (fRec45[2] + (fTemp27 + fTemp28))) +
								 (fSlow7 * ((fTemp29 + (fTemp28 + fRec45[2])) - fTemp27))));
		float fTemp31 = (fSlow90 * fRec44[1]);
		fRec44[0] = (fTemp30 - (fTemp31 + (fSlow5 * fRec44[2])));
		float fTemp32 = (fSlow5 * fRec44[0]);
		/*output1[i] = float(
			(0.5f *
			 (fRec0[0] * ((fTemp3 * fTemp1) +
						  (fTemp2 * ((fTemp32 + (fRec44[2] + (fTemp30 + fTemp31))) +
									 (fSlow3 * ((fTemp32 + (fTemp31 + fRec44[2])) -
		   fTemp30))))))))*/
		;
		fRec0[1] = fRec0[0];
		IOTA = (IOTA + 1);
		fRec1[1] = fRec1[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
		fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec16[1] = fRec16[0];
		fRec23[1] = fRec23[0];
		fRec22[1] = fRec22[0];
		fRec20[1] = fRec20[0];
		fRec27[1] = fRec27[0];
		fRec26[1] = fRec26[0];
		fRec24[1] = fRec24[0];
		fRec31[1] = fRec31[0];
		fRec30[1] = fRec30[0];
		fRec28[1] = fRec28[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec32[1] = fRec32[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec36[1] = fRec36[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec40[1] = fRec40[0];
		fRec4[2] = fRec4[1];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1];
		fRec7[1] = fRec7[0];
		fRec8[2] = fRec8[1];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1];
		fRec9[1] = fRec9[0];
		fRec10[2] = fRec10[1];
		fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1];
		fRec11[1] = fRec11[0];
		fRec3[2] = fRec3[1];
		fRec3[1] = fRec3[0];
		fRec2[2] = fRec2[1];
		fRec2[1] = fRec2[0];
		fRec45[2] = fRec45[1];
		fRec45[1] = fRec45[0];
		fRec44[2] = fRec44[1];
		fRec44[1] = fRec44[0];
		return output;
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
		}
		if (param_id == 1) {
		}
	}
	virtual void set_samplerate(float sr)
	{
		fSampleRate = sr;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (6.28318548f / fConst0);
		fConst2 = std::floor(((0.219990999f * fConst0) + 0.5f));
		fConst3 = ((0.0f - (6.90775537f * fConst2)) / fConst0);
		fConst4 = (3.14159274f / fConst0);
		fConst5 = std::floor(((0.0191229992f * fConst0) + 0.5f));
		iConst6 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst2 - fConst5))));
		fConst7 = (0.00100000005f * fConst0);
		iConst8 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst5 + -1.0f))));
		fConst9 = std::floor(((0.256891012f * fConst0) + 0.5f));
		fConst10 = ((0.0f - (6.90775537f * fConst9)) / fConst0);
		fConst11 = std::floor(((0.0273330007f * fConst0) + 0.5f));
		iConst12 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst9 - fConst11))));
		iConst13 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst11 + -1.0f))));
		fConst14 = std::floor(((0.192303002f * fConst0) + 0.5f));
		fConst15 = ((0.0f - (6.90775537f * fConst14)) / fConst0);
		fConst16 = std::floor(((0.0292910002f * fConst0) + 0.5f));
		iConst17 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst14 - fConst16))));
		iConst18 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst16 + -1.0f))));
		fConst19 = std::floor(((0.210389003f * fConst0) + 0.5f));
		fConst20 = ((0.0f - (6.90775537f * fConst19)) / fConst0);
		fConst21 = std::floor(((0.0244210009f * fConst0) + 0.5f));
		iConst22 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst19 - fConst21))));
		iConst23 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst21 + -1.0f))));
		fConst24 = std::floor(((0.125f * fConst0) + 0.5f));
		fConst25 = ((0.0f - (6.90775537f * fConst24)) / fConst0);
		fConst26 = std::floor(((0.0134579996f * fConst0) + 0.5f));
		iConst27 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst24 - fConst26))));
		iConst28 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst26 + -1.0f))));
		fConst29 = std::floor(((0.127837002f * fConst0) + 0.5f));
		fConst30 = ((0.0f - (6.90775537f * fConst29)) / fConst0);
		fConst31 = std::floor(((0.0316039994f * fConst0) + 0.5f));
		iConst32 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst29 - fConst31))));
		iConst33 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst31 + -1.0f))));
		fConst34 = std::floor(((0.174713001f * fConst0) + 0.5f));
		fConst35 = ((0.0f - (6.90775537f * fConst34)) / fConst0);
		fConst36 = std::floor(((0.0229039993f * fConst0) + 0.5f));
		iConst37 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst34 - fConst36))));
		iConst38 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst36 + -1.0f))));
		fConst39 = std::floor(((0.153128996f * fConst0) + 0.5f));
		fConst40 = ((0.0f - (6.90775537f * fConst39)) / fConst0);
		fConst41 = std::floor(((0.0203460008f * fConst0) + 0.5f));
		iConst42 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst39 - fConst41))));
		iConst43 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst41 + -1.0f))));
	}

private:
	float fSampleRate = 44100;
	float fVslider0;
	float fRec0[2];
	int IOTA;
	float fVec0[16384];
	float fVslider1;
	float fRec1[2];
	float fConst0;
	float fConst1;
	float fVslider2;
	float fVslider3;
	float fVslider4;
	float fVslider5;
	float fConst2;
	float fConst3;
	float fVslider6;
	float fVslider7;
	float fVslider8;
	float fConst4;
	float fVslider9;
	float fRec15[2];
	float fRec14[2];
	float fVec1[32768];
	float fConst5;
	int iConst6;
	float fVec2[16384];
	float fConst7;
	float fVslider10;
	float fVec3[2048];
	int iConst8;
	float fRec12[2];
	float fConst9;
	float fConst10;
	float fRec19[2];
	float fRec18[2];
	float fVec4[32768];
	float fConst11;
	int iConst12;
	float fVec5[4096];
	int iConst13;
	float fRec16[2];
	float fConst14;
	float fConst15;
	float fRec23[2];
	float fRec22[2];
	float fVec6[16384];
	float fConst16;
	int iConst17;
	float fVec7[4096];
	int iConst18;
	float fRec20[2];
	float fConst19;
	float fConst20;
	float fRec27[2];
	float fRec26[2];
	float fVec8[32768];
	float fConst21;
	int iConst22;
	float fVec9[4096];
	int iConst23;
	float fRec24[2];
	float fConst24;
	float fConst25;
	float fRec31[2];
	float fRec30[2];
	float fVec10[16384];
	float fConst26;
	int iConst27;
	float fVec11[2048];
	int iConst28;
	float fRec28[2];
	float fConst29;
	float fConst30;
	float fRec35[2];
	float fRec34[2];
	float fVec12[16384];
	float fConst31;
	int iConst32;
	float fVec13[4096];
	int iConst33;
	float fRec32[2];
	float fConst34;
	float fConst35;
	float fRec39[2];
	float fRec38[2];
	float fVec14[16384];
	float fConst36;
	int iConst37;
	float fVec15[4096];
	int iConst38;
	float fRec36[2];
	float fConst39;
	float fConst40;
	float fRec43[2];
	float fRec42[2];
	float fVec16[16384];
	float fConst41;
	int iConst42;
	float fVec17[2048];
	int iConst43;
	float fRec40[2];
	float fRec4[3];
	float fRec5[3];
	float fRec6[3];
	float fRec7[3];
	float fRec8[3];
	float fRec9[3];
	float fRec10[3];
	float fRec11[3];
	float fRec3[3];
	float fRec2[3];
	float fRec45[3];
	float fRec44[3];
};