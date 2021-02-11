#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "util/math.hh"
#include "util/math_tables.hh"

using namespace MathTools;

class AdCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		int stage = (int)phaccu;
		float envFrequency;
		if (stage == 0) {
			envFrequency = 1000.0f / attackTime;
		} else {
			envFrequency = 1000.0f / decayTime;
		}

		float wrappedPhase = phaccu - (long)phaccu;

		if (stage == 0) {
			float rise = 0;
			float linearRise = map_value(phaccu, 0.0f, 1.0f, attackSample, 1.0f);
			if (aShape <= 0.5f) {
				auto expoRise = map_value(pow9Table.closest(wrappedPhase), 0.0f, 1.0f, attackSample, 1.0f);
				float interpVal = aShape * 2.0f;
				rise = interpolate(expoRise, linearRise, interpVal);
			} else {
				float interpVal = aShape * 2.0f - 1.0f;
				auto logRise = map_value(1.0f - pow9Table.closest(1.0f - phaccu), 0.0f, 1.0f, attackSample, 1.0f);
				rise = interpolate(wrappedPhase, logRise, interpVal);
			}
			envOut = rise;

		} else if (stage == 1) {
			float fall = 0;
			auto linearCurve = map_value(wrappedPhase, 0.0f, 1.0f, 1.0f, 0.0f);

			float interpVal = 0.0f;
			if (dShape <= 0.5f) {
				auto expoFall = map_value(pow9Table.closest(1.0f - wrappedPhase), 1.0f, 0.0f, 1.0f, 0.0f);
				interpVal = dShape * 2.0f;
				fall = interpolate(expoFall, linearCurve, interpVal);
			} else {
				interpVal = dShape * 2.0f - 1.0f;
				auto logFall = map_value(pow9Table.closest(wrappedPhase), 0.0f, 1.0f, 1.0f, 0.0f);
				fall = interpolate(linearCurve, logFall, interpVal);
			}
			envOut = fall;
		} else {
			envOut = 0;
		}

		phaccu += envFrequency / sampleRate;
	}

	AdCore() {}

	virtual void set_param(const int param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				attackTime = map_value(val, 0.0f, 1.0f, 1.0f, 1200.0f);
				break;
			case 1:
				decayTime = map_value(val, 0.0f, 1.0f, 1.0f, 1200.0f);
				break;
			case 2:
				aShape = val;
				break;
			case 3:
				dShape = val;
				break;
		}
	}

	virtual void set_samplerate(const float sr) override
	{
		sampleRate = sr;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				lastGate = currentGate;
				currentGate = val > 0;
				if (currentGate > lastGate) {
					attackSample = envOut;
					phaccu = 0;
				}
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = envOut;
				break;
			case 1:
				output = phaccu >= 1;
				break;
			case 2:
				output = phaccu >= 2;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<AdCore>();
	}
	static constexpr char typeID[20] = "ADENV";
	static constexpr char description[] = "Attack Decay Envelope";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int currentGate = 0;
	int lastGate = 0;
	float attackTime = 0.1f;
	float decayTime = 0.1f;
	float envOut = 0;
	float aShape = 0;
	float dShape = 0;
	float attackSample = 0;

	float phaccu = 0;

	float sampleRate = 48000;
};
