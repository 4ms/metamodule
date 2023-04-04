#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/ENVVCA_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "CoreModules/modules/envvca/SSI2162.h"
#include "CoreModules/modules/envvca/TriangleOscillator.h"

inline auto CVToBool = [](float val) -> bool
{
	return val >= 0.5f;
};

inline auto ButtonToBool = [](float val) -> bool
{
	return val > 0;
};


class ENVVCACore : public CoreProcessor {
	using Info = ENVVCAInfo;
	using ThisCore = ENVVCACore;

public:
	ENVVCACore() = default;

	void update() override {

		//TODO: generate rise fall time voltage
		//TODO: convert voltage to time

		auto riseTimeInS = 0.1f;
		auto fallTimeInS = 0.1f;

		osc.setRiseTimeInS(riseTimeInS);
		osc.setFallTimeInS(fallTimeInS);

		runOscillator();

		displayOscillatorState(osc.getState());

		auto triangleOut = osc.getOutput();

		displayEnvelope(triangleOut);
		runAudioPath(triangleOut);
	}

	void runAudioPath(float triangleWave)
	{
		// TODO: Is this correct together with the trimmer
		const float MinGainInV = 1.98f;
		const float MaxGainInV = 47e3f / (47e3f + 1e6f) * 5.f;		

		triangleWave = std::min(triangleWave + MinGainInV, MaxGainInV);

		vca.setScaling(triangleWave);
		signalOut = vca.process(signalIn);
	}

	void displayEnvelope(float val)
	{
		//TODO: set envelope output with envelope scaling slider value
		//TODO: set all three slider LEDs
	}

	void displayOscillatorState(TriangleOscillator::State_t state)
	{
		//TODO: set EOR output
		eorOut = state == TriangleOscillator::State_t::FALLING;
		//TODO: set EOR LED
	}

	void runOscillator()
	{
		//TODO: handle cycle
		//TODO: handle trigger
		//TODO: handle follow
		osc.proceed(timeStepInS);
	}

	void set_param(int param_id, float val) override {
		switch (param_id)
		{
			case ENVVCAInfo::KnobRise_Slider: 
				riseSlider = val;
				break;
			case ENVVCAInfo::KnobFall_Slider:
				fallSlider = val;
				break;
			case ENVVCAInfo::KnobEnv_Level_Slider:
				envLevelSlider = val;
				break;
			case ENVVCAInfo::KnobRise_Cv:
				riseCVKnob = val;
				break;
			case ENVVCAInfo::KnobFall_Cv:
				fallCVKnob = val;
				break;

			case ENVVCAInfo::NumKnobs + ENVVCAInfo::SwitchSlow_Med_Fast_Rise:
				riseTimeSwitch = val;
				break;

			case ENVVCAInfo::NumKnobs + ENVVCAInfo::SwitchSlow_Med_Fast_Fall:
				fallTimeSwitch = val;
				break;

			case ENVVCAInfo::NumKnobs + ENVVCAInfo::SwitchCycle:
				cycleOnButton = ButtonToBool(val);
				break;

			default: break;
		}
	}

	void set_input(int input_id, float val) override {
		switch (input_id)
		{
			case ENVVCAInfo::InputTime_Cv: 
				timeCVIn = val;
				break;
			case ENVVCAInfo::InputTrigger:
				triggerIn = val;
				break;
			case ENVVCAInfo::InputCycle:
				cycleIn = CVToBool(val);
				break;
			case ENVVCAInfo::InputFollow:
				followIn = val;
				break;
			case ENVVCAInfo::InputIn:
				signalIn = val;
				break;
			default: break;
		}
	}

	float get_output(int output_id) const override {

		switch (output_id)
		{
			case ENVVCAInfo::OutputOut: return signalOut;
			case ENVVCAInfo::OutputEnv: return envelopeOut;
			case ENVVCAInfo::OutputEor: return eorOut;
			default:                    return 0.0f;
		}
	}

	void set_samplerate(float sr) override
	{
		timeStepInS = 1.0f / sr;
	}

	float get_led_brightness(int led_id) const override
	{
		switch (led_id)
		{
			case ENVVCAInfo::LedRise_Led:         return 0;
			case ENVVCAInfo::LedFall_Led:         return 0;
			case ENVVCAInfo::LedEor_Led:          return eorOut;
			case ENVVCAInfo::NumDiscreteLeds + 0: return cycleOnButton;
			default:                              return 0.0f;
		}
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	uint32_t riseTimeSwitch;
	uint32_t fallTimeSwitch;
	bool cycleOnButton;

	float riseSlider;
	float fallSlider;
	float envLevelSlider;
	float riseCVKnob;
	float fallCVKnob;

	float signalIn;
	float followIn;
	bool cycleIn;
	float triggerIn;
	float timeCVIn;

	float signalOut;
	float envelopeOut;
	float eorOut;

private:
	SSI2162 vca;
	TriangleOscillator osc;

private:
	float timeStepInS;

};
