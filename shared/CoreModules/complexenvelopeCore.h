#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/envelope.h"

using namespace MathTools;

class ComplexenvelopeCore : public CoreProcessor {
	static inline const int NumInJacks = 6;
	static inline const int NumOutJacks = 6;
	static inline const int NumKnobs = 8;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Attack","Hold","Decay","Sustain","Release","Attack Curve", "Decay Curve", "Release Curve"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output", "Attack Stage", "Decay Stage", "Release Stage", "Hold Stage", "Sustain Stage"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Gate In", "Attack", "Hold", "Decay", "Sustain", "Release"};
	static inline const StaticString<LongNameChars> description{"Complex Envelope"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
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

		currentStage = e.getStage();
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
		if (output_id < 1) {
			output = envelopeOutput;
		} else {
			if (currentStage == (output_id - 1)) {
				output = 1;
			} else {
				output = 0;
			}
		}

		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ComplexenvelopeCore>();
	}
	static constexpr char typeID[20] = "COMPLEXENVELOPE";
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
	int currentStage = 0;
	Envelope e;
};
