#pragma once
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"

#define FAUSTFLOAT float

using namespace MathTools;

template<uint32_t SAMPLERATE>
class DjembeCore : public CoreProcessor {
	static inline const int NumInJacks = 5;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 4;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Freq", "Gain", "Sharpness", "Strike"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{
		"Freq", "Gain", "Sharpness", "Strike", "Trigger"};
	static inline const StaticString<LongNameChars> description{"Djembe"};

	enum Params { Freq = 0, Gain = 1, Sharpness = 2, Strike = 3, Trigger = 4 };

public:
	DjembeCore()
		: fConst1{(12348.0f / SAMPLERATE)}
		, fConst2{(17640.0f / SAMPLERATE)}
		, iConst3{int((0.0253061224f * SAMPLERATE))}
		, iConst4{int((0.0269387756f * SAMPLERATE))}
		, iConst5{int((0.0289569162f * SAMPLERATE))}
		, iConst6{int((0.0307482984f * SAMPLERATE))}
		, iConst7{int((0.0322448984f * SAMPLERATE))}
		, iConst8{int((0.033809524f * SAMPLERATE))}
		, iConst9{int((0.0353061222f * SAMPLERATE))}
		, iConst10{int((0.0366666652f * SAMPLERATE))}
		, iConst11{int((0.0126077095f * SAMPLERATE))}
		, iConst12{std::min<int>(1024, std::max<int>(0, (iConst11 + -1)))}
		, iConst13{int((0.00999999978f * SAMPLERATE))}
		, iConst14{std::min<int>(1024, std::max<int>(0, (iConst13 + -1)))}
		, iConst15{int((0.00773242628f * SAMPLERATE))}
		, iConst16{std::min<int>(1024, std::max<int>(0, (iConst15 + -1)))}
		, iConst17{int((0.00510204071f * SAMPLERATE))}
		, iConst18{std::min<int>(1024, std::max<int>(0, (iConst17 + -1)))}
		, fConst19{(0.00104308384f * SAMPLERATE)}
	{
		IOTA = 0;

		// Combine these loops
		for (int i = 0; i < 2; i++) {
			fRec9[i] = 0.0f;
			fRec8[i] = 0.0f;
			fRec11[i] = 0.0f;
			fRec10[i] = 0.0f;
			fRec13[i] = 0.0f;
			fRec0[i] = 0.0f;
			fRec12[i] = 0.0f;
			fRec14[i] = 0.0f;
			fRec15[i] = 0.0f;
			fRec16[i] = 0.0f;
			fRec17[i] = 0.0f;
			fRec18[i] = 0.0f;
			fRec19[i] = 0.0f;
			fRec20[i] = 0.0f;
			fRec21[i] = 0.0f;
			fRec22[i] = 0.0f;
			fRec23[i] = 0.0f;
			fRec24[i] = 0.0f;
			fRec26[i] = 0.0f;
			fRec28[i] = 0.0f;
			fRec2[i] = 0.0f;
			fRec30[i] = 0.0f;
			fRec32[i] = 0.0f;
			fRec33[i] = 0.0f;
			fRec34[i] = 0.0f;
			fRec35[i] = 0.0f;
			fRec36[i] = 0.0f;
			fRec37[i] = 0.0f;
			fRec38[i] = 0.0f;
			fRec39[i] = 0.0f;
			fRec40[i] = 0.0f;
			fRec41[i] = 0.0f;
			fRec42[i] = 0.0f;
			fRec43[i] = 0.0f;
			fRec44[i] = 0.0f;
			fRec45[i] = 0.0f;
			fRec46[i] = 0.0f;
			fRec47[i] = 0.0f;
			fRec4[i] = 0.0f;
			fRec6[i] = 0.0f;
		}
		for (int i = 0; i < 1024; i++) {
			fVec11[i] = 0.0f;
		}
		for (int i = 0; i < 2048; i++) {
			fVec10[i] = 0.0f;
			fVec20[i] = 0.0f;
			fVec21[i] = 0.0f;
			fVec22[i] = 0.0f;
			fVec23[i] = 0.0f;
			fVec8[i] = 0.0f;
		}
		for (int i = 0; i < 8192; i++) {
			fVec0[i] = 0.0f;
			fVec1[i] = 0.0f;
			fVec9[i] = 0.0f;
			fVec12[i] = 0.0f;
			fVec13[i] = 0.0f;
			fVec14[i] = 0.0f;
			fVec15[i] = 0.0f;
			fVec16[i] = 0.0f;
			fVec17[i] = 0.0f;
			fVec18[i] = 0.0f;
			fVec19[i] = 0.0f;
			fVec2[i] = 0.0f;
			fVec3[i] = 0.0f;
			fVec4[i] = 0.0f;
			fVec5[i] = 0.0f;
			fVec6[i] = 0.0f;
			fVec7[i] = 0.0f;
		}

		// Todo: convert these to human param names
		fEntry0 = FAUSTFLOAT(0.0f);
		fHslider0 = FAUSTFLOAT(0.5f);
		fEntry1 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fEntry2 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.33329999999999999f);
		fEntry3 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fEntry4 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.5f);
	}

	void update() override
	{
		update_params();

		FAUSTFLOAT *input0 = inputs[0];
		FAUSTFLOAT *input1 = inputs[1];
		FAUSTFLOAT *output0 = outputs[0];
		FAUSTFLOAT *output1 = outputs[1];

		float fSlow0 = ((fConst1 * std::min<float>((float(fEntry0) + float(fHslider0)), 1.0f)) + 0.699999988f);
		float fSlow1 = (fConst2 * std::min<float>((float(fEntry1) + float(fHslider1)), 1.0f));
		float fSlow2 = (1.0f - fSlow1);
		float fSlow3 = std::min<float>((float(fEntry2) + float(fHslider2)), 1.0f);
		float fSlow4 = (0.100000001f * fSlow3);
		float fSlow5 = ((fConst1 * std::min<float>((float(fEntry3) + float(fHslider3)), 1.0f)) + 0.699999988f);
		float fSlow6 = (1.0f - fSlow3);
		int iSlow7 = int((fConst19 * std::min<float>((float(fEntry4) + float(fHslider4)), 1.0f)));
		int iSlow8 = (iConst3 + iSlow7);
		int iSlow9 = (iConst4 + iSlow7);
		int iSlow10 = (iConst5 + iSlow7);
		int iSlow11 = (iConst6 + iSlow7);
		int iSlow12 = (iConst7 + iSlow7);
		int iSlow13 = (iConst8 + iSlow7);
		int iSlow14 = (iConst9 + iSlow7);
		int iSlow15 = (iConst10 + iSlow7);
		int iSlow16 = (iSlow7 + -1);
		int iSlow17 = std::min<int>(1024, std::max<int>(0, (iConst11 + iSlow16)));
		int iSlow18 = std::min<int>(1024, std::max<int>(0, (iConst13 + iSlow16)));
		int iSlow19 = std::min<int>(1024, std::max<int>(0, (iConst15 + iSlow16)));
		int iSlow20 = std::min<int>(1024, std::max<int>(0, (iConst17 + iSlow16)));
		// for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		fRec9[0] = ((fSlow1 * fRec9[1]) + (fSlow2 * fRec8[1]));
		float fTemp0 = float(input0[i0]);
		float fTemp1 = float(input1[i0]);
		float fTemp2 = (fSlow4 * (fTemp0 + fTemp1));
		fVec0[(IOTA & 8191)] = ((fSlow0 * fRec9[0]) + fTemp2);
		fRec8[0] = fVec0[((IOTA - iConst3) & 8191)];
		fRec11[0] = ((fSlow1 * fRec11[1]) + (fSlow2 * fRec10[1]));
		fVec1[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec11[0]));
		fRec10[0] = fVec1[((IOTA - iConst4) & 8191)];
		fRec13[0] = ((fSlow1 * fRec13[1]) + (fSlow2 * fRec12[1]));
		fVec2[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec13[0]));
		fRec12[0] = fVec2[((IOTA - iConst5) & 8191)];
		fRec15[0] = ((fSlow1 * fRec15[1]) + (fSlow2 * fRec14[1]));
		fVec3[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec15[0]));
		fRec14[0] = fVec3[((IOTA - iConst6) & 8191)];
		fRec17[0] = ((fSlow1 * fRec17[1]) + (fSlow2 * fRec16[1]));
		fVec4[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec17[0]));
		fRec16[0] = fVec4[((IOTA - iConst7) & 8191)];
		fRec19[0] = ((fSlow1 * fRec19[1]) + (fSlow2 * fRec18[1]));
		fVec5[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec19[0]));
		fRec18[0] = fVec5[((IOTA - iConst8) & 8191)];
		fRec21[0] = ((fSlow1 * fRec21[1]) + (fSlow2 * fRec20[1]));
		fVec6[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec21[0]));
		fRec20[0] = fVec6[((IOTA - iConst9) & 8191)];
		fRec23[0] = ((fSlow1 * fRec23[1]) + (fSlow2 * fRec22[1]));
		fVec7[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec23[0]));
		fRec22[0] = fVec7[((IOTA - iConst10) & 8191)];
		float fTemp3 = ((((((((fRec8[0] + fRec10[0]) + fRec12[0]) + fRec14[0]) + fRec16[0]) + fRec18[0]) + fRec20[0]) +
						 fRec22[0]) +
						(fSlow5 * fRec6[1]));
		fVec8[(IOTA & 2047)] = fTemp3;
		fRec6[0] = fVec8[((IOTA - iConst12) & 2047)];
		float fRec7 = (0.0f - (fSlow5 * fTemp3));
		float fTemp4 = (fRec6[1] + (fRec7 + (fSlow5 * fRec4[1])));
		fVec9[(IOTA & 2047)] = fTemp4;
		fRec4[0] = fVec9[((IOTA - iConst14) & 2047)];
		float fRec5 = (0.0f - (fSlow5 * fTemp4));
		float fTemp5 = (fRec4[1] + (fRec5 + (fSlow5 * fRec2[1])));
		fVec10[(IOTA & 2047)] = fTemp5;
		fRec2[0] = fVec10[((IOTA - iConst16) & 2047)];
		float fRec3 = (0.0f - (fSlow5 * fTemp5));
		float fTemp6 = (fRec2[1] + (fRec3 + (fSlow5 * fRec0[1])));
		fVec11[(IOTA & 1023)] = fTemp6;
		fRec0[0] = fVec11[((IOTA - iConst18) & 1023)];
		float fRec1 = (0.0f - (fSlow5 * fTemp6));
		output0[i0] = FAUSTFLOAT(((fRec1 + fRec0[1]) + (fSlow6 * fTemp0)));
		fRec33[0] = ((fSlow1 * fRec33[1]) + (fSlow2 * fRec32[1]));
		fVec12[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec33[0]));
		fRec32[0] = fVec12[((IOTA - iSlow8) & 8191)];
		fRec35[0] = ((fSlow1 * fRec35[1]) + (fSlow2 * fRec34[1]));
		fVec13[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec35[0]));
		fRec34[0] = fVec13[((IOTA - iSlow9) & 8191)];
		fRec37[0] = ((fSlow1 * fRec37[1]) + (fSlow2 * fRec36[1]));
		fVec14[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec37[0]));
		fRec36[0] = fVec14[((IOTA - iSlow10) & 8191)];
		fRec39[0] = ((fSlow1 * fRec39[1]) + (fSlow2 * fRec38[1]));
		fVec15[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec39[0]));
		fRec38[0] = fVec15[((IOTA - iSlow11) & 8191)];
		fRec41[0] = ((fSlow1 * fRec41[1]) + (fSlow2 * fRec40[1]));
		fVec16[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec41[0]));
		fRec40[0] = fVec16[((IOTA - iSlow12) & 8191)];
		fRec43[0] = ((fSlow1 * fRec43[1]) + (fSlow2 * fRec42[1]));
		fVec17[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec43[0]));
		fRec42[0] = fVec17[((IOTA - iSlow13) & 8191)];
		fRec45[0] = ((fSlow1 * fRec45[1]) + (fSlow2 * fRec44[1]));
		fVec18[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec45[0]));
		fRec44[0] = fVec18[((IOTA - iSlow14) & 8191)];
		fRec47[0] = ((fSlow1 * fRec47[1]) + (fSlow2 * fRec46[1]));
		fVec19[(IOTA & 8191)] = (fTemp2 + (fSlow0 * fRec47[0]));
		fRec46[0] = fVec19[((IOTA - iSlow15) & 8191)];
		float fTemp7 = ((((((((fRec32[0] + fRec34[0]) + fRec36[0]) + fRec38[0]) + fRec40[0]) + fRec42[0]) + fRec44[0]) +
						 fRec46[0]) +
						(fSlow5 * fRec30[1]));
		fVec20[(IOTA & 2047)] = fTemp7;
		fRec30[0] = fVec20[((IOTA - iSlow17) & 2047)];
		float fRec31 = (0.0f - (fSlow5 * fTemp7));
		float fTemp8 = (fRec30[1] + (fRec31 + (fSlow5 * fRec28[1])));
		fVec21[(IOTA & 2047)] = fTemp8;
		fRec28[0] = fVec21[((IOTA - iSlow18) & 2047)];
		float fRec29 = (0.0f - (fSlow5 * fTemp8));
		float fTemp9 = (fRec28[1] + (fRec29 + (fSlow5 * fRec26[1])));
		fVec22[(IOTA & 2047)] = fTemp9;
		fRec26[0] = fVec22[((IOTA - iSlow19) & 2047)];
		float fRec27 = (0.0f - (fSlow5 * fTemp9));
		float fTemp10 = (fRec26[1] + (fRec27 + (fSlow5 * fRec24[1])));
		fVec23[(IOTA & 2047)] = fTemp10;
		fRec24[0] = fVec23[((IOTA - iSlow20) & 2047)];
		float fRec25 = (0.0f - (fSlow5 * fTemp10));
		output1[i0] = FAUSTFLOAT(((fRec25 + fRec24[1]) + (fSlow6 * fTemp1)));
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
		fRec33[1] = fRec33[0];
		fRec32[1] = fRec32[0];
		fRec35[1] = fRec35[0];
		fRec34[1] = fRec34[0];
		fRec37[1] = fRec37[0];
		fRec36[1] = fRec36[0];
		fRec39[1] = fRec39[0];
		fRec38[1] = fRec38[0];
		fRec41[1] = fRec41[0];
		fRec40[1] = fRec40[0];
		fRec43[1] = fRec43[0];
		fRec42[1] = fRec42[0];
		fRec45[1] = fRec45[0];
		fRec44[1] = fRec44[0];
		fRec47[1] = fRec47[0];
		fRec46[1] = fRec46[0];
		fRec30[1] = fRec30[0];
		fRec28[1] = fRec28[0];
		fRec26[1] = fRec26[0];
		fRec24[1] = fRec24[0];
		// }
	}

	void update_params()
	{
		// ui_interface->addNumEntry("AllpassCoefCV", &fEntry3, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		// ui_interface->addNumEntry("CombCoefCV", &fEntry0, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		// ui_interface->addNumEntry("DampCV", &fEntry1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		// ui_interface->addNumEntry("DryWetCV", &fEntry2, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		// ui_interface->addNumEntry("SpreadCV", &fEntry4, 0.0f, 0.0f, 40000.0f, 1.0f);
		// ui_interface->addHorizontalSlider("APFeed", &fHslider3, 0.5f, 0.0f, 1.0f, 0.0250000004f);
		// ui_interface->addHorizontalSlider("Damp", &fHslider1, 0.5f, 0.0f, 1.0f, 0.0250000004f);
		// ui_interface->addHorizontalSlider("RoomSize", &fHslider0, 0.5f, 0.0f, 1.0f, 0.0250000004f);
		// ui_interface->addHorizontalSlider("Stereo Spread", &fHslider4, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		// ui_interface->addHorizontalSlider("Wet", &fHslider2, 0.333299994f, 0.0f, 1.0f, 0.0250000004f);
	}

	void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case Freq:
				break;

			case Gain:
				// new_damp = val;
				// damp_needs_update = true;
				break;

			case Sharpness:
				break;

			case Strike:
				break;
		}
	}

	void set_samplerate(const float sr) override
	{
		fSampleRate = sr;
	}

	void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case Freq:
				break;

			case Gain:
				// new_damp = val;
				// damp_needs_update = true;
				break;

			case Sharpness:
				break;

			case Strike:
				break;

			case Trigger:
				break;
		}
	}

	float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<DjembeCore>();
	}

	static constexpr char typeID[20] = "DJEMBE";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float signalOut = 0;

	int fSampleRate = 48000;
	const float fConst1;
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider0;
	const float fConst2;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fHslider1;
	float fRec9[2];
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fHslider2;
	int IOTA;
	float fVec0[8192];
	const int iConst3;
	float fRec8[2];
	float fRec11[2];
	float fVec1[8192];
	const int iConst4;
	float fRec10[2];
	float fRec13[2];
	float fVec2[8192];
	const int iConst5;
	float fRec12[2];
	float fRec15[2];
	float fVec3[8192];
	const int iConst6;
	float fRec14[2];
	float fRec17[2];
	float fVec4[8192];
	const int iConst7;
	float fRec16[2];
	float fRec19[2];
	float fVec5[8192];
	const int iConst8;
	float fRec18[2];
	float fRec21[2];
	float fVec6[8192];
	const int iConst9;
	float fRec20[2];
	float fRec23[2];
	float fVec7[8192];
	const int iConst10;
	float fRec22[2];
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fHslider3;
	float fVec8[2048];
	const int iConst11;
	const int iConst12;
	float fRec6[2];
	float fVec9[2048];
	const int iConst13;
	const int iConst14;
	float fRec4[2];
	float fVec10[2048];
	const int iConst15;
	const int iConst16;
	float fRec2[2];
	float fVec11[1024];
	const int iConst17;
	const int iConst18;
	float fRec0[2];
	float fRec33[2];
	float fVec12[8192];
	const float fConst19;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fHslider4;
	float fRec32[2];
	float fRec35[2];
	float fVec13[8192];
	float fRec34[2];
	float fRec37[2];
	float fVec14[8192];
	float fRec36[2];
	float fRec39[2];
	float fVec15[8192];
	float fRec38[2];
	float fRec41[2];
	float fVec16[8192];
	float fRec40[2];
	float fRec43[2];
	float fVec17[8192];
	float fRec42[2];
	float fRec45[2];
	float fVec18[8192];
	float fRec44[2];
	float fRec47[2];
	float fVec19[8192];
	float fRec46[2];
	float fVec20[2048];
	float fRec30[2];
	float fVec21[2048];
	float fRec28[2];
	float fVec22[2048];
	float fRec26[2];
	float fVec23[2048];
	float fRec24[2];

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
};

/*
import("stdfaust.lib");
freqknob = hslider("v: djembe/freq", 60, 20, 500, 1);
freqcv = nentry("freqcv [CV:2]", 1, 1, 32, 0.001);
freqtotal = freqknob * freqcv;

trigbutton = button("Trigger");
gate = button("gate [CV:1]");

strikecv = nentry("v: jacks/strikecv [CV:3]", 0, 0, 1, 0.01);
sharpcv = nentry("v: jacks/shaprcv [CV:4]", 0, 0, 1, 0.01);
gaincv = nentry("v: jacks/gaincv [CV:5]", 0, 0, 1, 0.01);

strikepos = hslider("v: djembe/strike", 0.3, 0, 1, 0.01) + strikecv, 1 :min;
strikesharpness = hslider("v: djembe/sharpness", 0.5, 0, 1, 0.01) + sharpcv, 1 :min;
strikegain = hslider("v: djembe/gain", 1, 0, 1, 0.01) + gaincv, 1 :min;
process = trigbutton + gate : pm.djembe(freqtotal, strikepos, strikesharpness, strikegain);
*/
