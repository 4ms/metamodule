#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"

using namespace MathTools;

struct AxolotiMath {
	static uint32_t _mtofextended(uint32_t pitch)
	{
		//TODO
		return pitch;
	}
};

template<typename T>
void MTOFEXTENDED(uint32_t pitch, T &freq)
{
	freq = AxolotiMath::_mtofextended(pitch);
}

template<typename T>
void SINE2TINTERP(uint32_t Phase, T &r)
{
	float idx = (float)Phase / (float)((1 << 12) - 1);
	r = sinTable.interp_by_index(idx);
}

class Infosc01Core : public CoreProcessor {

public:
	uint32_t inlet_reset;	  //bool32 rising
	uint32_t inlet_phase;	  //frac32 bipolar
	uint32_t inlet_pitch;	  //frac32 bipolar
	uint32_t outlet_wave;	  //frac32 bipolar
	uint32_t param_lvl = 0;	  //frac32
	uint32_t param_pitch = 0; //frac32

	uint32_t r = 0;
	uint32_t Phase = 0;

	Infosc01Core() {}

	void update(void) override {}

	void update_params()
	{
		if (inlet_reset && r) {
			Phase = inlet_phase << 4;
			r = 0;
		} else {
			if (!inlet_reset)
				r = 1;
		}
		{
			int32_t freq;
			MTOFEXTENDED(param_pitch + inlet_pitch, freq);
			Phase += freq >> 2;
			int32_t r;
			SINE2TINTERP(Phase, r);
			outlet_wave = ___SMMUL(r, param_lvl << 1);
		}

		void set_param(int const param_id, const float val) override
		{
			switch (param_id) {
			}
		}
		void set_samplerate(const float sr) override {}

		void set_input(const int input_id, const float val) override
		{
			switch (input_id) {
			}
		}

		float get_output(const int output_id) const override
		{
			float output = 0;
			switch (output_id) {
			}
			return output;
		}

	private:
	public:
		// Auto generated:
		// clang-format off
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 1;
	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{};
	static inline const StaticString<LongNameChars> description{"infinite-oscillator-01"};
	static constexpr char typeID[20] = "INFOSC01";
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<Infosc01Core>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	StaticString<LongNameChars> get_description() override { return description; }
		// clang-format on
	};
