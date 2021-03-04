#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/envelope.h"

using namespace MathTools;

class ComplexenvelopeCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		float finalAttack = constrain(attackCv + attackOffset, 0.0f, 1.0f);
		float finalHold = constrain(holdCv + holdOffset, 0.0f, 1.0f);
		float finalDecay = constrain(decayCv + decayOffset, 0.0f, 1.0f);
		float finalSustain = constrain(sustainCv + sustainOffset, 0.0f, 1.0f);
		float finalRelease = constrain(releaseCv + releaseOffset, 0.0f, 1.0f);

		e.set_envelope_time(0, map_value(finalAttack, 0.0f, 1.0f, 0.1f, 1000.0f));
		e.set_envelope_time(1, map_value(finalHold, 0.0f, 1.0f, 0.0f, 1000.0f));
		e.set_envelope_time(2, map_value(finalDecay, 0.0f, 1.0f, 0.1f, 1000.0f));
		e.set_envelope_time(3, map_value(finalRelease, 0.0f, 1.0f, 0.1f, 1000.0f));

		e.set_sustain(finalSustain);
		envelopeOutput = e.update(gateInput);
	}

	ComplexenvelopeCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0: // attack
				attackOffset = val;
				break;
			case 1: // hold
				holdOffset = val;
				break;
			case 2: // decay
				decayOffset = val;
				break;
			case 3: // sustain
				sustainOffset = val;
				break;
			case 4: // release
				releaseOffset = val;
				break;
			case 5:
				e.set_attack_curve(val);
				break;
			case 6:
				e.set_decay_curve(val);
				break;
			case 7:
				e.set_release_curve(val);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		e.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				gateInput = val;
				break;
			case 1:
				attackCv = val;
				break;
			case 2:
				holdCv = val;
				break;
			case 3:
				decayCv = val;
				break;
			case 4:
				sustainCv = val;
				break;
			case 5:
				releaseCv = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = envelopeOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ComplexenvelopeCore>();
	}
	static constexpr char typeID[20] = "COMPLEXENVELOPE";
	static constexpr char description[] = "Complex Envelope";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float gateInput = 0;
	float envelopeOutput = 0;

	float attackOffset = 0;
	float holdOffset = 0;
	float decayOffset = 0;
	float sustainOffset = 0;
	float releaseOffset = 0;

	float attackCv = 0;
	float holdCv = 0;
	float decayCv = 0;
	float sustainCv = 0;
	float releaseCv = 0;
	Envelope e;
};
