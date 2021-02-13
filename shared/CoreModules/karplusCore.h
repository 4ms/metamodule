#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/envelope.h"
#include "processors/karplus.h"
#include "util/math.hh"
#include "util/math_tables.hh"

using namespace MathTools;

class KarplusCore : public CoreProcessor {
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
		e.set_envelope_time(0, 1);
		e.set_envelope_time(1, 0);
		e.set_envelope_time(2, 2);
		e.set_envelope_time(3, 1);
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
	static constexpr char description[] = "Karplus";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float decay = 0;
	float karpOut = 0;
	float gateInput = 0;
	float pitchInput = 0;
	float basePitch = 20;

	Karplus k;
	Envelope e;
};
