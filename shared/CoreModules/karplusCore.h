#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/envelope.h"
#include "processors/karplus.h"
#include "util/math.hh"
#include "util/math_tables.hh"

using namespace MathTools;

class KarplusCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 3;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Pitch", "Decay", "Spread"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Gate Input", "Pitch Input"};
	static inline const StaticString<LongNameChars> description{"Karplus"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		auto noiseOut = randomNumber(-1.0f, 1.0f);
		auto noiseBurst = noiseOut * e.update(gateInput);
		k.set_frequency(basePitch * expTable.interp(constrain(pitchInput, 0.0f, 1.0f)));
		karpOut = k.update(noiseBurst);
	}

	KarplusCore()
	{
		e.set_sustain(0.0f);
		e.set_envelope_time(0, 0.1);
		e.set_envelope_time(1, 0);
		e.set_envelope_time(2, 30);
		e.set_decay_curve(0);
		e.set_release_curve(0.5f);
		e.set_sustain(0.1f);
		e.set_envelope_time(3, 200);
		e.sustainEnable = 0;
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				basePitch = map_value(val, 0.0f, 1.0f, 20.0f, 400.0f);
				break;
			case 1:
				k.set_decay(val);
				e.set_sustain(map_value(val, 0.0f, 1.0f, 0.0f, 0.2f));
				e.set_envelope_time(3, map_value(val, 0.0f, 1.0f, 200.0f, 1000.0f));
				break;
			case 2:
				k.set_spread(val);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		k.set_samplerate(sr);
		e.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				gateInput = val;
				break;
			case 1:
				pitchInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = karpOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<KarplusCore>();
	}
	static constexpr char typeID[20] = "KARPLUS";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float karpOut = 0;
	float gateInput = 0;
	float pitchInput = 0;
	float basePitch = 20;

	Karplus k;
	Envelope e;
};
