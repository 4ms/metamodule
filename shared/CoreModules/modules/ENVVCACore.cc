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

inline auto ThreeWayToInt = [](float val) -> uint32_t
{
	return val * 2.0f;
};

inline auto VoltageDivider = [](float bottom, float top) -> float
{
	return bottom / (bottom + top);
};

inline auto ParallelCircuit = [](float a, float b) -> float
{
	return (a * b) / (a + b);
};

inline auto InvertingAmpWithBias = [](float in, float r_in, float r_feedback, float bias) -> float
{
	return bias - r_feedback / r_in * (in - bias);
};


class ENVVCACore : public CoreProcessor {
	using Info = ENVVCAInfo;
	using ThisCore = ENVVCACore;

public:
	ENVVCACore() = default;

	void update() override {

		auto [riseCV, fallCV] = getRiseAndFallCV();

		// Convert voltage to time without dealing with integrator details

		// TODO: add follow here?
		auto VoltageToTime = [](float voltage) -> float
		{
			constexpr float CurrentGain = 200.0f;
			constexpr float IntegratorCapacitanceInF = 6.8e-9f;
			constexpr float TransistorUBEInV = 0.7f;

			constexpr float TempCompVoltage = -12.0f * VoltageDivider(500.0f, 47e3f);

			auto current = ((12.0f - (TransistorUBEInV + voltage)) / 8.2e3f) / (CurrentGain + 1) * CurrentGain;

			// printf("Current: %.3fuA\n", current * 1e6f);

			auto voltageSlope = current / IntegratorCapacitanceInF;
			auto time = 12.0f / voltageSlope;

			return time;
		};		

		
		auto riseTimeInS = VoltageToTime(riseCV);
		auto fallTimeInS = VoltageToTime(fallCV);

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
		// TODO: Is this correct together with the trimmer?
		const float MinGainInV = 1.98f;
		const float MaxGainInV = 47e3f / (47e3f + 1e6f) * 5.f;		

		triangleWave = std::min(triangleWave + MinGainInV, MaxGainInV);

		vca.setScaling(triangleWave);
		signalOut = vca.process(signalIn);
	}

	void displayEnvelope(float val)
	{
		envelopeOut = val * envLevelSlider;
		//TODO: set all three slider LEDs
	}

	void displayOscillatorState(TriangleOscillator::State_t state)
	{
		eorOut = state == TriangleOscillator::State_t::FALLING;
	}

	void runOscillator()
	{
		//TODO: handle cycle
		//TODO: handle trigger
		//TODO: handle follow
		osc.proceed(timeStepInS);
	}

	std::pair<float,float> getRiseAndFallCV()
	{
		auto ProcessCVOffset = [](auto slider, auto range) -> float
		{	
			// Slider plus resistor in parallel to tweak curve
			const float SliderImpedance = 100e3f;
			auto offset = 5.0f * VoltageDivider(slider * SliderImpedance + 17.4e3f, 0 + ParallelCircuit(100e3f, (1.0f - slider) * SliderImpedance));

			// Select one of three bias voltages
			auto BiasFromRange = [](auto range) -> float
			{
				if (range == 2)
				{
					return -12.0f * VoltageDivider(1e3f, 10e3f);
				}
				else if (range == 1)
				{
					return 0.0f;
				}
				else
				{
					return 12.0f * VoltageDivider(1e3f, 8.2e3f);
				}
			};

			auto bias = BiasFromRange(range);

			// printf("Range %u -> Bias %.2f\n", range, bias);

			return InvertingAmpWithBias(offset, 100e3f, 100e3f, bias);
		};

		const auto scaledTimeCV = timeCVIn * -100e3f / 137e3f;

		rScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, riseCVKnob * scaledTimeCV);
		fScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, fallCVKnob * scaledTimeCV);

		static volatile uint32_t tmp=0;
		if (tmp == 0)
		{
			printf("TimeCV %.2f, rscale %.2f\n", timeCVIn, rScaleLEDs);
			tmp = 10000;
		}
		else{
			tmp--;
		}

		const auto riseCVOffset = ProcessCVOffset(riseSlider, riseTimeSwitch);
		const auto fallCVOffset = ProcessCVOffset(fallSlider, fallTimeSwitch);

		auto riseCV = rScaleLEDs + riseCVOffset;
		auto fallCV = fScaleLEDs + fallCVOffset;

		//TODO: low pass filter riseCV and fall CV

		constexpr float DiodeDrop = 1.0f;

		riseCV = riseCV * VoltageDivider(2.2e3f + 33e3f, 16.9e3f);
		riseCV = std::min(riseCV, 5.0f * VoltageDivider(100e3f, 2e3f) + DiodeDrop);

		fallCV = fallCV * VoltageDivider(2.2e3f, 10e3f + 40.2e3f);

		return {riseCV, fallCV};
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
				riseTimeSwitch = ThreeWayToInt(val);
				break;

			case ENVVCAInfo::NumKnobs + ENVVCAInfo::SwitchSlow_Med_Fast_Fall:
				fallTimeSwitch = ThreeWayToInt(val);
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
				timeCVIn = val * 5.0f;
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
		// TODO: Here we could also set slider LEDs once they are defined
		// TODO: Rise and Fall LEDs are actually biploar but defined as single color
		switch (led_id)
		{
			case ENVVCAInfo::LedRise_Led:         return rScaleLEDs;
			case ENVVCAInfo::LedFall_Led:         return fScaleLEDs;
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

	float rScaleLEDs;
	float fScaleLEDs;

private:
	SSI2162 vca;
	TriangleOscillator osc;

private:
	float timeStepInS;

};
