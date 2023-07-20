#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/ComplexEG_info.hh"
#include "processors/envelope.h"
#include "util/math.hh"
using namespace MathTools;

namespace MetaModule
{

class ComplexEGCore : public CoreProcessor {
	using Info = ComplexEGInfo;
	using ThisCore = ComplexEGCore;

public:
	ComplexEGCore() = default;

	void update() override {
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

	void set_param(int param_id, float val) override {
		switch (param_id) {
			case Info::KnobAttack:
				attackOffset = val;
				break;
			case Info::KnobHold:
				holdOffset = val;
				break;
			case Info::KnobDecay:
				decayOffset = val;
				break;
			case Info::KnobSustain:
				sustainOffset = val;
				break;
			case Info::KnobRelease:
				releaseOffset = val;
				break;
			case Info::KnobA_Curve:
				e.set_attack_curve(val);
				break;
			case Info::KnobD_Curve:
				e.set_decay_curve(val);
				break;
			case Info::KnobR_Curve:
				e.set_release_curve(val);
				break;
		}
	}

	void set_samplerate(float sr) override {
		e.set_samplerate(sr);
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case Info::InputInput:
				gateInput = val;
				break;
			case Info::InputAttack_Cv:
				attackCv = val;
				break;
			case Info::InputHold_Cv:
				holdCv = val;
				break;
			case Info::InputDecay_Cv:
				decayCv = val;
				break;
			case Info::InputSustain_Cv:
				sustainCv = val;
				break;
			case Info::InputRelease_Cv:
				releaseCv = val;
				break;
		}
	}

	float get_output(int output_id) const override {
		if (output_id == Info::OutputOut) {
			return envelopeOutput;
		} else {
			//FIXME: This only works because OutputOut is 5, and the others are 0-4 in AHDSR order
			return (currentStage == output_id) ? 1 : 0;
		}
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

} // namespace MetaModule
