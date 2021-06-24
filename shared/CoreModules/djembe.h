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

		IOTA = 0;

		// Combine these loops
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec9[l0] = 0.0f;
		}
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
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec33[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 8192); l33 = (l33 + 1)) {
			fVec12[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec32[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec35[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 8192); l36 = (l36 + 1)) {
			fVec13[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec34[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec37[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 8192); l39 = (l39 + 1)) {
			fVec14[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec36[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec39[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 8192); l42 = (l42 + 1)) {
			fVec15[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec38[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec41[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 8192); l45 = (l45 + 1)) {
			fVec16[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec40[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec43[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 8192); l48 = (l48 + 1)) {
			fVec17[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec42[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec45[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 8192); l51 = (l51 + 1)) {
			fVec18[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec44[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec47[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 8192); l54 = (l54 + 1)) {
			fVec19[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec46[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 2048); l56 = (l56 + 1)) {
			fVec20[l56] = 0.0f;
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec30[l57] = 0.0f;
		}
		for (int l58 = 0; (l58 < 2048); l58 = (l58 + 1)) {
			fVec21[l58] = 0.0f;
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec28[l59] = 0.0f;
		}
		for (int l60 = 0; (l60 < 2048); l60 = (l60 + 1)) {
			fVec22[l60] = 0.0f;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec26[l61] = 0.0f;
		}
		for (int l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			fVec23[l62] = 0.0f;
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec24[l63] = 0.0f;
		}
	}

	void update() override
	{
		update_params();
	}

	void update_params() {}

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
