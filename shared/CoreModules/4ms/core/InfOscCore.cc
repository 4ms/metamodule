#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/InfOsc_info.hh"

#include "axoloti-wrapper/axoloti_math.h"
#include "util/math.hh"

namespace MetaModule
{

class InfOscCore : public CoreProcessor {
	using Info = InfOscInfo;
	using ThisCore = InfOscCore;

public:
	InfOscCore() {
		axoloti_math_init();

		/////////////////////////////////////////////
		// MARK: Init Code:
		static int32_t _array[LENGTH]; // __attribute__((section(".sdram")));
		array = &_array[0];
		sel = &array[0];
		pos = &array[lENGTH];
		tot = &array[LENGTH - 1];
		{
			int i;
			for (i = 0; i < lENGTH; i++) {
				sel[i] = 0;
				pos[i] = i > 0 ? (1 << 27) + 1 : -1;
			}
		}

		tot[0] = 2;
		upd = 0;

		P1 = 0;
		P2 = 0;

		Ppitch = 0;
		Prange = 0;
		// END MARK: Init Code
		////////////////////////////////////////////
	}

	void update() override {
		if (s_rate_counter++ >= s_rate_ratio) {
			s_rate_counter = 0;
			update_params();
		}

		////////////////////////////////////////////
		// MARK: S-rate Code:

		// int32_t phs1 = inlet_pm << 8; // commented out because it's not used, and compiler gives a warning
		int32_t phs2 = param_phase + (inlet_phase << 5);
		for (int i = 0; i < 4; i++) {
			wave = wave > 0 ? wave : (___SMMUL(wave, Abs) << 5);
			lp += (wave - lp) >> 3;
			wave = lp;
			hp += (wave - hp) >> 6;
			wave -= hp;
			int32_t Fbass = fbass + (___SMMUL(fbass, inlet_lin) << 9);
			P1 += Fbass + (___SMMUL(fm, wave));

			int32_t w1, w2;

			w1 = SHAPE((uint32_t)(P1 << 1), param_modshape);
			w2 = SHAPE((uint32_t)(P1 << 2), param_modshape);
			w3 = SHAPE((uint32_t)(P1 << 3), param_modshape);

			w3 += (___SMMUL(w1 - w3, mix) << 1) + w2;
			r = w3;

			w1 = SHAPE((uint32_t)(P1 << 2) + phs2, param_modshape);
			w2 = SHAPE((uint32_t)(P1 << 3) + phs2, param_modshape);
			w3 = SHAPE((uint32_t)(P1 << 4) + phs2, param_modshape);
			w3 += (___SMMUL(w1 - w3, mix) << 1) + w2;
			wave = w3;
			LP += (r - LP) >> 2;
		}

		outlet_wave = LP >> 1;

		// END MARKL S-rate Code
		////////////////////////////////////////////
	}

	void update_params() {
		////////////////////////////////////////////
		// MARK: K-rate Code:

		int32_t Pitch = param_pitch + inlet_pitch;

		// int32_t r; //commented out because only used in S-rate code
		Ppitch += __SSAT(Pitch - Ppitch, 20);
		int64_t pitch = Ppitch;

		int64_t bass = inlet_range + param_range;
		Prange += __SSAT(bass - Prange, 20);
		int32_t track = ___SMMUL(pitch << 1, param_track << 4); //<<4;
		bass = (int64_t)Prange + inlet_mod + track;

		int64_t limit = (60 << 21);

		int64_t out = bass + limit;
		out = out > 0 ? out : -out;
		out = out % (limit << 2);
		out = (out > (limit << 1) ? (limit << 2) - out : out) - limit;
		bass = out;

		pitch -= bass;

		out = pitch + limit;
		out = out > 0 ? out : -out;
		out = out % (limit << 2);
		out = (out > (limit << 1) ? (limit << 2) - out : out) - limit;
		//pitch=out;

		uint64_t pqnt = (uint64_t)pitch + ((uint64_t)12 << 28);
		pqnt = pqnt / 12 >> 21;
		int64_t dif = pqnt - ppitch;
		dif = dif >= 0 ? dif : -dif;
		if (pqnt < ppitch) {
			P1 = (uint64_t)P1 << dif;
		} else if (pqnt > ppitch) {
			P1 = P1 >> dif;
		}

		pitch -= (pqnt - 128) * 12 << 21;

		if (pitch < 0) {
			while (pitch < 0) {
				pitch += (12 << 21);
			}
		} else if (pitch >= (12 << 21)) {
			while (pitch >= (12 << 21)) {
				pitch -= (12 << 21);
			}
		}

		/*uint32_t*/ mix = ((uint64_t)pitch << 8) / 3;
		// int32_t fbass; //commented out because mix and fbass are used in S-rate, so need to be class member variables

		out = (int64_t)pitch + bass + limit;
		out = out > 0 ? out : -out;
		out = out % (limit << 2);
		out = (out > (limit << 1) ? (limit << 2) - out : out) - limit;
		MTOFEXTENDED(pitch + bass, fbass);

		fbass = fbass >> 4;
		ppitch = pqnt;

		/*int32_t*/ fm = param_fm + inlet_fm; //fm is now a member variable (used in S-rate)
		fm = (fm - (___SMMUL(fm, fbass) << 4)) << 3;

		/*int32_t*/ Abs = inlet_abs + param_abs; //Abs is now a member variable (used in S-rate)

		if (inlet_rst && !rst) {
			rst = 1;
			for (int i = 0; i < lENGTH; i++) {
				sel[i] = 0;
				pos[i] = i > 0 ? (1 << 27) + 1 : -1;
			}
			tot[0] = 2;
		} else if (!inlet_rst) {
			rst = 0;
		}
		// int s1 = 0, s2 = 0;
		int32_t Mix;
		int32_t tpos = ((Ppitch + (1 << 27)) & ((1 << 28) - 1)) >> 1;
		int tsel = __USAT(param_wave + (1 << 27), 28) >> 21;
		if (!(tsel == select)) {
			select = tsel;
			upd = 1;
		}

		if (!(tpos == position)) {
			position = tpos;
			upd = 0;
		}

		if (inlet_add && !add) {
			upd = 0;
			add = 1;
			int i = 0;
			for (; i < tot[0]; i++) {
				if (pos[i] > position) {
					break;
				}
			}
			for (int j = tot[0]; j >= i; j--) {
				pos[j + 1] = pos[j];
				sel[j + 1] = sel[j];
			}
			sel[i] = select;
			pos[i] = position;
			tot[0] += 1;
		} else if (!inlet_add) {
			add = 0;
		}

		int32_t start = 0, end = 0, width = 1;
		int32_t Position = (position + (inlet_scan >> 1)) & ((1 << 27) - 1);
		if (!(Position == position)) {
			upd = 0;
		}
		if (tot[0] > 1) {
			for (int i = 0; i < tot[0]; i++) {
				if ((pos[i] <= Position) && (pos[i + 1] >= Position)) {
					start = pos[i];
					end = pos[i + 1];
					if (start == end) {
						end += 1;
					}
					width = end - start;
					// s1 = sel[i];
					// s2 = sel[i + 1];
					break;
				}
			}
			Mix = Position - start;
			Mix = (int64_t)Mix * ((uint32_t)(1 << 31) - 1) / width;

			// int32_t a, b;
			if (upd) {
				// s1 = select;
				Mix = 0;
			}
			// s1 <<= LENGTHPOW; //parent->instancewave_space_design_i.LENGTHPOW;
			// s2 <<= LENGTHPOW; //parent->instancewave_space_design_i.LENGTHPOW;
		} else if (tot[0] == 1) {
			// s1 = sel[0];
			// s2 = sel[0];
			Mix = 0;
			// if (upd) {
			// s1 = select;
			// }
			// s1 <<= LENGTHPOW; //parent->instancewave_space_design_i.LENGTHPOW;
			// s2 <<= LENGTHPOW; //parent->instancewave_space_design_i.LENGTHPOW;

		} else {
			// s1 = 0;
			// s2 = 0;
			// if (upd) {
			// 	s1 = select;
			// 	s2 = select;
			// }
			Mix = 0;
			// s1 <<= LENGTHPOW; //parent->instancewave_space_design_i.LENGTHPOW;
			// s2 <<= LENGTHPOW; //parent->instancewave_space_design_i.LENGTHPOW;
		}

		// END MARK: K-rate Code
		////////////////////////////////////////////
	}

	void set_param(int param_id, float val) override {
		switch (param_id) {
			case Info::KnobPitch:
				param_pitch.set_from_positive_float(val);
				break;
			case Info::KnobTrack:
				param_track.set_from_positive_float(val);
				break;
			case Info::KnobRange:
				param_range.set_from_positive_float(val);
				break;
			case Info::KnobFm:
				param_fm.set_from_positive_float(val);
				break;
			case Info::KnobAbs:
				param_abs.set_from_positive_float(val);
				break;
			case Info::KnobPhase:
				param_phase.set_from_positive_float(val);
				break;
			case Info::KnobModshape:
				param_modshape = MathTools::constrain<int32_t>(val * 4, 0, 3);
				//[0,0.25) => 0, [0.25,0.5) => 1, [0.5,0.75) => 2, [0.75,..] => 3
				break;
			case Info::KnobWave:
				param_wave.set_from_positive_float(val);
				break;
		}
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case Info::InputAbs_Cv:
				inlet_abs.set_from_float(val);
				break;
			case Info::InputPitch_Cv:
				inlet_pitch.set_from_float(val);
				break;
			case Info::InputRange_Cv:
				inlet_range.set_from_float(val);
				break;
			case Info::InputFm_Cv:
				inlet_fm.set_from_float(val);
				break;
			case Info::InputMod_Cv:
				inlet_mod.set_from_float(val);
				break;
			case Info::InputLin_Cv:
				inlet_lin.set_from_float(val);
				break;
			case Info::InputPhase_Cv:
				inlet_phase.set_from_float(val);
				break;
			case Info::InputPm_Cv:
				inlet_pm.set_from_float(val);
				break;
			case Info::InputScan_Cv:
				inlet_scan.set_from_float(val);
				break;
		}
	}

	float get_output(int output_id) const override {
		if (output_id == Info::OutputOut)
			return outlet_wave.to_float();
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		return 0.f;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	// Any variables declared in K-rate code and used in S-rate code must be declared here instead of in K-rate code:
	int32_t Abs;
	int32_t fbass;
	int32_t fm;
	uint32_t mix;
	int32_t r;

	///////////////////////////////////////
	// MARK: Local Data
	static const uint32_t LENGTHPOW = (7);
	static const uint32_t LENGTH = (1 << 8) + 1;
	static const int32_t lENGTH = (1 << 7);
	static const uint32_t LENGTHMASK = ((1 << 7) - 1);
	int32_t *array;
	int32_t *pos;
	int32_t *sel, *tot;
	int32_t select, position;
	int add, upd, rst; //,lng;

	uint32_t P1, P2, ppitch;
	int32_t /*FRQ,*/ hp, wave, /*pwave,*/ lp, /*r3,*/ w3, LP; //,dclk,pprev,rprev;
	int32_t Ppitch, Prange;

	int32_t tri(int32_t ps) {
		ps += (1 << 30);
		ps = (ps > 0 ? ps : -ps) - (1 << 30);
		return ps = ps >> 4;
	};

	int32_t saw(uint32_t ps) {
		ps = (ps >> 2);
		ps += ps >> 4;
		uint32_t tps = __USAT(ps, 30);
		ps = tps + ((tps - ps) << 4);
		int32_t p2;
		return p2 = ((int32_t)ps - (1 << 29)) >> 3;
	};
	int32_t sqr(int32_t ps) {
		ps += (1 << 30);
		ps = (ps > 0 ? ps : -ps) - (1 << 30);
		return ps = __SSAT(ps, 27);
	};

	int32_t SHAPE(uint32_t ps, int sel) {
		int32_t r;
		switch (sel) {
			case 0:
				r = sinet[ps >> 22] << 11;
				break;
			case 1:
				r = tri(ps);
				break;
			case 2:
				r = saw(ps);
				break;
			case 3:
				r = sqr(ps);
				break;
		}

		return r;
	}
	// END MARK: Local Data
	//////////////////////////////////////////

	//Inlets:
	frac32_s<27> inlet_pitch{0};
	frac32_s<27> inlet_range{0};
	frac32_s<27> inlet_fm{0};
	frac32_s<27> inlet_mod{0};
	frac32_s<27> inlet_abs{0};
	frac32_s<27> inlet_lin{0};
	frac32_s<27> inlet_phase{0};
	frac32_s<27> inlet_pm{0};
	// int32buffer inlet_lin;
	// int32buffer inlet_phase;
	// int32buffer inlet_pm;
	frac32_s<27> inlet_scan{0};
	bool inlet_add = false;
	bool inlet_rst = false;

	//Outlets:
	//int32buffer &outlet_wave;
	frac32_s<27> outlet_wave;

	//Params:
	frac32_s<27> param_pitch{0};
	frac32_s<27> param_track{0};
	frac32_s<27> param_range{0};
	frac32_s<27> param_fm{0};
	frac32_s<27> param_abs{0};
	frac32_u<31> param_phase{0};
	int32_t param_modshape = 0; //Selector: 0 1 2 3
	frac32_s<27> param_wave{0};

	//S/K rate counter
	uint32_t s_rate_counter = 0;
	static constexpr uint32_t s_rate_ratio = 48000 / 3000;
};

} // namespace MetaModule
