#pragma once
#include "CoreModules/moduleTypes.h"
#include "axoloti-wrapper/axoloti_math.h"
#include "coreProcessor.h"
#include "util/math.hh"
#include <cstdint>

using namespace MathTools;

class Infosc64bphaseCore : public CoreProcessor {

public:
	///////////////////////////////////////
	// MARK: Local Data
	int gen;
	uint64_t Phase, pPhase;
	int32_t pfrq, ppfrq, ppitch;
	int32_t env;
	int32_t ps1, ps2, pps1, pps2, ppmix, pmix;
	int32_t mod;
	int32_t wave[4096];
	int32_t WAVER(uint32_t phs, int32_t &out)
	{
		int32_t p1, p2, mx;
		mx = ((uint32_t)phs << 12) >> 1;
		p1 = (uint32_t)phs >> 20;
		p2 = (p1 + 1) & 4095;
		p1 = wave[p1];
		p2 = wave[p2];
		out = p1 + ___SMMUL((p2 - p1) << 1, mx);

		///?axoloti code doesn't have a return
		return 0;
	};

	// END MARK: Local Data
	//////////////////////////////////////////

	// Any variables declared in K-rate code and used in S-rate code must be declared here instead of in K-rate code:
	int32_t freq;
	int32_t mix, s1, s2;
	int32_t rate;

	Infosc64bphaseCore()
	{
		axoloti_math_init();

		/////////////////////////////////////////////
		// MARK: Init Code:

		Phase = 0;

		for (int i = 0; i < 4096; i++) {
			wave[i] = 0;
		}
		// int hrm = 1;
		int32_t gain = 0x7FFFFFFF; //(1 << 31) - 1;
		for (int j = 1; j < 128; j++) {
			for (int i = 0; i < 4096; i++) {
				wave[i] += ___SMMUL(sine2t[(i * j + (j << 8)) & 4095], gain) / j >> 4;
			}
			//gain=(GenerateRandomNumber()>>1);
		}

		// END MARK: Init Code
		////////////////////////////////////////////
	}

	void update(void) override
	{
		if (s_rate_counter++ >= s_rate_ratio) {
			s_rate_counter = 0;
			update_params();
		}

		////////////////////////////////////////////
		// MARK: S-rate Code:

		Phase += (int64_t)freq << 11;
		pPhase += (int64_t)pfrq << 11;
		mod += rate;
		int32_t r1, r2, t1, t2, sum = 0;
		for (int i = 0; i < param_stack; i++) {

			int j;
			if (param_octaved) {
				j = 1 << i;
			} else {
				j = i + 1;
			}
			int32_t p2 = ((mod * (param_indexrelated > 0 ? j : 1)) + param_shift * i);
			SINE2TINTERP(p2, p2)
			p2 = ___SMMUL(p2, param_mod) << 6;
			WAVER(((Phase >> s1) * j) + p2, r1);
			WAVER(((Phase >> s2) * j) + p2, r2);
			r1 >>= 1;
			r2 >>= 1;
			r1 += ___SMMUL(r2 - r1, mix) << 1;
			if (param_damped) {
				r1 /= j;
			}
			sum += r1 >> i;
			if (env > 0) {
				WAVER(((pPhase >> ps1) * j) + p2, t1);
				WAVER(((pPhase >> ps2) * j) + p2, t2);
				t1 >>= 1;
				t2 >>= 1;
				t1 += ___SMMUL(t2 - t1, pmix) << 1;
				if (param_damped) {
					t1 /= j;
				}
				sum += (___SMMUL(env, t1 - r1) << 1) >> i;
			}
		}
		outlet_wave = sum;
		if (env > 0) {
			env = __USAT(env - (1 << 26), 31);
		}
		// END MARKL S-rate Code
		////////////////////////////////////////////
	}

	void update_params()
	{
		////////////////////////////////////////////
		// MARK: K-rate Code:

		int64_t pitch = param_pitch + inlet_pitch;
		MTOFEXTENDED(pitch, freq);
		pitch -= ___SMMUL(param_track << 4, pitch) << 1;
		pitch += (1 << 28) - param_range;
		mix = ((uint32_t)pitch / 12 << 11) >> 1;
		s1 = pitch / 12 >> 21;
		s2 = s1 + 1;

		if (!(((ppitch - pitch) >> 21) == 0)) {
			env = 0x7FFFFFFF; //(1 << 31) - 1;
			ps1 = pps1;
			ps2 = pps2;
			pmix = ppmix;
			pfrq = ppfrq;
			pPhase = Phase;
		}

		ppitch = pitch;
		ppfrq = freq;
		pps1 = s1;
		pps2 = s2;
		ppmix = mix;

		MTOFEXTENDED(param_rate, rate)
		rate >>= 10;

		param_gen = gen_button | (gen_jack == 1.f);
		if (param_gen && !gen) {
			gen = 1;
			// codec_clearbuffer();
			for (int i = 0; i < 4096; i++) {
				wave[i] = 0;
			}
			// int hrm = 1;
			int32_t gain = 0x7FFFFFFF; //(1 << 31) - 1;
			for (int j = 1; j < 128; j++) {
				for (int i = 0; i < 4096; i++) {
					wave[i] += ___SMMUL(sine2t[(i * j + (j << 8)) & 4095], gain) / j >> 4;
				}
				gain = (GenerateRandomNumber() >> 1);
			}

		} else if (!param_gen) {
			gen = 0;
		}

		// END MARK: K-rate Code
		////////////////////////////////////////////
	}

	void set_param(int param_id, float val) override
	{
		switch (param_id) {
			case (PitchKnob):
				param_pitch.set_from_positive_float(val);
				break;
			case (TrackKnob):
				param_track.set_from_positive_float(val);
				break;
			case (RangeKnob):
				param_range.set_from_positive_float(val);
				break;
			case (StackNumber):
				param_stack = MathTools::constrain<int32_t>(val * 16, 0, 15);
				break;
			case (OctaveToggle):
				param_octaved = (val > 0.5f);
				break;
			case (DampedToggle):
				param_damped = (val > 0.5f);
				break;
			case (GenMomentary):
				gen_button = (val > 0.5f);
				break;
			case (ShiftKnob):
				param_shift.set_from_positive_float(val);
				break;
			case (RateKnob):
				param_rate.set_from_positive_float(val);
				break;
			case (ModKnob):
				param_mod.set_from_positive_float(val);
				break;
			case (IndexrelatedToggle):
				param_indexrelated = (val > 0.5f);
				break;
		}
	}
	void set_samplerate(const float sr) override {}

	void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case (PitchInJack):
				inlet_pitch.set_from_float(val);
				break;
			case (GenJack):
				gen_jack = MathTools::hysteresis_feedback(0.1f, 0.5f, gen_jack, val);
				break;
		}
	}

	float get_output(const int output_id) const override
	{
		return outlet_wave.to_float();
	}

public:
	//Inlets:
	frac32_s<27> inlet_pitch{0};

	//Outlets:
	frac32_s<27> outlet_wave;

	//Params:
	frac32_s<27> param_pitch{0};
	frac32_s<27> param_track{0};
	frac32_s<27> param_range{0};
	int32_t param_stack{};
	bool param_octaved{false};
	bool param_damped{false};
	bool param_gen{false};
	bool gen_button{false};
	float gen_jack{false};
	frac32_u<27> param_shift{0};
	frac32_s<27> param_rate{0};
	frac32_s<27> param_mod{0};
	bool param_indexrelated{false};

	//S/K rate counter
	uint32_t s_rate_counter = 0;
	static constexpr uint32_t s_rate_ratio = 48000 / 3000;

public:
	// Auto generated:
	// clang-format off
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 11;
	enum Knob {PitchKnob, TrackKnob, RangeKnob, StackNumber, OctaveToggle, DampedToggle, GenMomentary, ShiftKnob, RateKnob, ModKnob, IndexrelatedToggle};
	enum InJack {PitchInJack,GenJack}; //TrackJack, RangeJack, StackJack, GenJack, ShiftJack, RateJack, ModJack};
	enum OutJack {WaveOutJack};
	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Pitch", "Track", "Range", "Stack#", "Oct", "Damped", "Gen", "Shift", "Rate", "Mod", "IndexRel"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Out"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Pitch","Gen"};//"Track", "Range", "Stack#","Gen", "Shift", "Rate", "Mod"};
	static inline const StaticString<LongNameChars> description{"infinite-oscillator-64bphase"};
	static constexpr char typeID[20] = "INFOSC64";

	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<Infosc64bphaseCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
};
