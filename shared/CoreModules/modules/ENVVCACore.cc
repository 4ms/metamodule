#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/ENVVCA_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "CoreModules/modules/envvca/SSI2162.h"
#include "CoreModules/modules/envvca/TriangleOscillator.h"
#include "CoreModules/modules/helpers/circuit_elements.h"
#include "CoreModules/modules/helpers/FlipFlop.h"
#include "CoreModules/modules/helpers/EdgeDetector.h"

inline auto CVToBool = [](float val) -> bool
{
	return val >= 1.0f;
};

inline auto ButtonToBool = [](float val) -> bool
{
	return val > 0;
};

inline auto ThreeWayToInt = [](float val) -> uint32_t
{
	return val * 2.0f;
};


class ENVVCACore : public CoreProcessor {
	using Info = ENVVCAInfo;
	using ThisCore = ENVVCACore;

public:
	ENVVCACore() : triggerDetector(1.0f, 2.0f)
	{}

	void update() override {

		auto [riseCV, fallCV] = getRiseAndFallCV();

		// Convert voltage to time without dealing with details of transistor core
		auto VoltageToTime = [](float voltage) -> float
		{
			// two points in the V->f curve
			constexpr float V_1 = 0.4f;
			constexpr float f_1 = 0.09f;
			constexpr float V_2 = 0.06f;
			constexpr float f_2 = 1000.0f;

			// std::pow is not required to be constexpr by the standard
			// so this might not work in clang
			constexpr float b = std::pow(2.0f, std::log2(f_1 / f_2)/(V_1 - V_2));
			constexpr float a = f_1 / std::pow(b, V_1);

			// interpolate
			auto frequency = std::pow(b, voltage) * a;

			// limit to valid frequency range
			frequency = std::clamp(frequency, 1.0f/(60 * 3), 20e3f);

			// convert to period length
			return 1.0f / frequency;
		};		

		osc.setRiseTimeInS(VoltageToTime(riseCV));
		osc.setFallTimeInS(VoltageToTime(fallCV));

		runOscillator();

		displayOscillatorState(osc.getState());

		displayEnvelope(osc.getOutput());
		runAudioPath(osc.getOutput());
	}

	void runAudioPath(float triangleWave)
	{
		triangleWave = InvertingAmpWithBias(triangleWave, 100e3f, 100e3f, 1.94f);

		constexpr float VCAInputImpendance = 5e3f;
		triangleWave = triangleWave * VoltageDivider(VCAInputImpendance, 2.7e3f);

		// This value influences the maximum gain a lot
		// Tweaked manually to achieve approximately max 0dB
		constexpr float SchottkyForwardVoltage = 0.22f;
		constexpr float MaxGainInV = 5.0f + SchottkyForwardVoltage;
		constexpr float MinGainInV = VoltageDivider(47e3f, 1e6f) * 5.0f - SchottkyForwardVoltage;

		triangleWave = std::clamp(triangleWave, MinGainInV, MaxGainInV);

		vca.setScaling(triangleWave);

		// Ignoring input impedance and inverting 400kHz lowpass

		signalOut = vca.process(signalIn);

		// Ignoring output impedance and inverting 400kHz lowpass
	}

	void displayEnvelope(float val)
	{
		val = val / VoltageDivider(100e3f, 100e3f);
		envelopeOut = val * envLevelSlider;
		//TODO: set all three slider LEDs
	}

	void displayOscillatorState(TriangleOscillator::State_t state)
	{
		eorOut = state == TriangleOscillator::State_t::FALLING;
	}

	void runOscillator()
	{
		osc.setCycling(cycleOnButton ^ cycleIn);
		osc.setTargetVoltage(followIn);

		if (triggerEdgeDetector(triggerIn))
		{
			osc.doRetrigger();
		}
		
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

			return InvertingAmpWithBias(offset, 100e3f, 100e3f, bias);
		};

		// scale down cv input
		const auto scaledTimeCV = timeCVIn * -100e3f / 137e3f;

		// apply attenuverter knobs
		rScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, riseCVKnob * scaledTimeCV);
		fScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, fallCVKnob * scaledTimeCV);

		// sum with static value from fader + range switch
		auto riseCV = -rScaleLEDs - ProcessCVOffset(riseSlider, riseTimeSwitch);
		auto fallCV = -fScaleLEDs - ProcessCVOffset(fallSlider, fallTimeSwitch);

		// TODO: low pass filter

		// apply rise time limit and scale down
		constexpr float DiodeDropInV = 1.0f;
		const float ClippingVoltage = 5.0f * VoltageDivider(100e3f, 2e3f) + DiodeDropInV;
		riseCV = riseCV * VoltageDivider(2.2e3f + 33e3f, 16.9e3f);
		riseCV = std::min(riseCV, ClippingVoltage);
		riseCV = riseCV * VoltageDivider(2.2e3f, 33e3f);

		// scale down falling CV without additional limiting
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

	void set_input(int input_id, float val) override
	{
		// map back to actual voltages
		val *= 5.0f;

		switch (input_id)
		{
			case ENVVCAInfo::InputTime_Cv: 
				timeCVIn = val;
				break;
			case ENVVCAInfo::InputTrigger:
				triggerIn = triggerDetector(val);
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

	float get_output(int output_id) const override
	{
		auto getRawOutput = [this](auto id)
		{
			switch (id)
			{
				case ENVVCAInfo::OutputOut: return signalOut;
				case ENVVCAInfo::OutputEnv: return envelopeOut;
				case ENVVCAInfo::OutputEor: return eorOut;
				default:                    return 0.0f;
			}
		};

		// convert voltage to normaized value required for mapping layer
		return getRawOutput(output_id) / 5.0f;
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
			case ENVVCAInfo::NumDiscreteLeds + 0: return cycleOnButton ^ cycleIn;
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
	bool triggerIn;
	float timeCVIn;

	float signalOut;
	float envelopeOut;
	float eorOut;

	float rScaleLEDs;
	float fScaleLEDs;

	FlipFlop triggerDetector;
	EdgeDetector triggerEdgeDetector;

private:
	SSI2162 vca;
	TriangleOscillator osc;

private:
	float timeStepInS;

};
