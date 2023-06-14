#include "CoreModules/SmartCoreProcessor.h"
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

class ENVVCACore : public SmartCoreProcessor<MetaModule::ENVVCAInfo> {
	using ENVVCAInfo = MetaModule::ENVVCAInfo;
	using Info = MetaModule::ENVVCAInfo;
	using ThisCore = ENVVCACore;

public:
	ENVVCACore() : triggerDetector(1.0f, 2.0f)
	{}

	void update() override
	{
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
			const float b = std::pow(2.0f, std::log2(f_1 / f_2) / (V_1 - V_2));
			const float a = f_1 / std::pow(b, V_1);

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

		if (auto input = getInput(ENVVCAInfo::InputIn); input)
		{
			auto output = vca.process(*input);
			setOutput(ENVVCAInfo::OutputOut, output);
			setLED(ENVVCAInfo::LedEor_Led, output);			
		}
		else
		{
			setLED(ENVVCAInfo::LedEor_Led, 0.f);
			setOutput(ENVVCAInfo::OutputOut, 0.f);
		}

		// Ignoring output impedance and inverting 400kHz lowpass
	}

	void displayEnvelope(float val)
	{
		val = val / VoltageDivider(100e3f, 100e3f);
		setOutput(ENVVCAInfo::OutputEnv, val * getKnob(ENVVCAInfo::KnobEnv_Level_Slider));
		//TODO: set all three slider LEDs
	}

	void displayOscillatorState(TriangleOscillator::State_t state)
	{
		setOutput(ENVVCAInfo::OutputEor, state == TriangleOscillator::State_t::FALLING);
	}

	void runOscillator()
	{
		bool isCycling = ButtonToBool(getSwitch(ENVVCAInfo::SwitchCycle)) ^ CVToBool(getInput(ENVVCAInfo::InputCycle).value_or(0.0f));

		osc.setCycling(isCycling);
		if (cycleLED != isCycling){
		cycleLED = isCycling;
			setLED(ENVVCAInfo::LedCycle_Led, cycleLED);
		}


		if (auto inputFollowValue = getInput(ENVVCAInfo::InputFollow); inputFollowValue)
		{
			osc.setTargetVoltage(*inputFollowValue);
		}

		if (auto triggerInputValue = getInput(ENVVCAInfo::InputTrigger); triggerInputValue)
		{
			if (triggerEdgeDetector(triggerDetector(*triggerInputValue)))
			{
				osc.doRetrigger();
			}
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

		if (auto timeCVValue = getInput(ENVVCAInfo::InputTime_Cv); timeCVValue)
		{
			// scale down cv input
			const auto scaledTimeCV = *timeCVValue * -100e3f / 137e3f;

			// apply attenuverter knobs
			auto rScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, getKnob(ENVVCAInfo::KnobRise_Cv) * scaledTimeCV);
			auto fScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, getKnob(ENVVCAInfo::KnobFall_Cv) * scaledTimeCV);

			// sum with static value from fader + range switch
			riseCV = -rScaleLEDs - ProcessCVOffset(getKnob(ENVVCAInfo::KnobRise_Slider), ThreeWayToInt(getSwitch(ENVVCAInfo::SwitchSlow_Med_Fast_Rise)));
			fallCV = -fScaleLEDs - ProcessCVOffset(getKnob(ENVVCAInfo::KnobFall_Slider), ThreeWayToInt(getSwitch(ENVVCAInfo::SwitchSlow_Med_Fast_Fall)));

			setLED(ENVVCAInfo::LedRise_Led, rScaleLEDs);
			setLED(ENVVCAInfo::LedFall_Led, fScaleLEDs);

			// TODO: low pass filter

			// apply rise time limit and scale down
			constexpr float DiodeDropInV = 1.0f;
			const float ClippingVoltage = 5.0f * VoltageDivider(100e3f, 2e3f) + DiodeDropInV;
			riseCV = riseCV * VoltageDivider(2.2e3f + 33e3f, 16.9e3f);
			riseCV = std::min(riseCV, ClippingVoltage);
			riseCV = riseCV * VoltageDivider(2.2e3f, 33e3f);

			// scale down falling CV without additional limiting
			fallCV = fallCV * VoltageDivider(2.2e3f, 10e3f + 40.2e3f);
		}

		return {riseCV, fallCV};
	}


	void set_samplerate(float sr) override
	{
		timeStepInS = 1.0f / sr;
	}

	// TODO: Here we could also set slider LEDs once they are defined
	// TODO: Rise and Fall LEDs are actually biploar but defined as single color

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ElementInfoView::makeView<Info>());
	// clang-format on

private:
	// TODO required until switches with light are supported
	float cycleLED;

	// temporary results that are buffered
	float riseCV;
	float fallCV;

	FlipFlop triggerDetector;
	EdgeDetector triggerEdgeDetector;

private:
	SSI2162 vca;
	TriangleOscillator osc;

private:
	float timeStepInS;

};
