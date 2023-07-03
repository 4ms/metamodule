#include "CoreModules/SmartCoreProcessor.h"
#include "CoreModules/info/ENVVCA_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "CoreModules/modules/envvca/SSI2162.h"
#include "CoreModules/modules/envvca/TriangleOscillator.h"
#include "CoreModules/modules/helpers/circuit_elements.h"
#include "gcem/include/gcem.hpp"
#include "CoreModules/modules/helpers/EdgeDetector.h"
#include "helpers/FlipFlop.h"
#include "helpers/mapping.h"

inline auto CVToBool = [](float val) -> bool
{
	return val >= 0.5f;
};


#if __clang__
constinit auto VoltageToFrequencyTable = Mapping::LookupTable_t<-1, 5, 50>::generate([](auto voltage)
#else
constinit auto VoltageToFrequencyTable = Mapping::LookupTable_t<-0.1f, 0.5f, 50>::generate([](auto voltage)
#endif
{
    // two points in the V->f curve
    constexpr double V_1 = 0.4;
    constexpr double f_1 = 0.09;
    constexpr double V_2 = 0.06;
    constexpr double f_2 = 1000.0;

    // std::pow is not required to be constexpr by the standard
    // so this might not work in clang
    constexpr double ArgScalingFactor = 10.0;
    constexpr double arg = gcem::log2(f_1 / f_2) / (V_1 - V_2);
    constexpr double b = gcem::pow(2.0f, arg / ArgScalingFactor);
    constexpr double a = f_1 / gcem::pow(gcem::pow(2.0, arg), V_1);

    // interpolate
    auto frequency = float(gcem::pow(b, double(voltage) * ArgScalingFactor) * a);

    return frequency;
});


class ENVVCACore : public SmartCoreProcessor<MetaModule::ENVVCAInfo> {
	using ENVVCAInfo = MetaModule::ENVVCAInfo;
	using Info = MetaModule::ENVVCAInfo;
	using ThisCore = ENVVCACore;
	using enum Info::Elem;

public:
	ENVVCACore() : triggerDetector(1.0f, 2.0f)
	{}

	void update() override
	{
		auto [riseCV, fallCV] = getRiseAndFallCV();

		// Convert voltage to time without dealing with details of transistor core
		auto VoltageToTime = [](float voltage) -> float
		{
			auto frequency = VoltageToFrequencyTable.lookup(voltage);

			// limit to valid frequency range
			frequency = std::clamp(frequency, 1.0f/(60 * 3), 20e3f);

			// convert to period length
			return 1.0f / frequency;
		};

		osc.setRiseTimeInS(VoltageToTime(riseCV));
		osc.setFallTimeInS(VoltageToTime(fallCV));

		runOscillator();

		displayOscillatorState(osc.getState());

		displayEnvelope(osc.getOutput(), osc.getState());
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

		if (auto input = getInput(AudioIn); input) {
			auto output = vca.process(*input);
			setOutput(AudioOut, output);
		} else {
			setOutput(AudioOut, 0.f);
		}

		// Ignoring output impedance and inverting 400kHz lowpass
	}

	void displayEnvelope(float val, TriangleOscillator::State_t state)
	{
		val = val / VoltageDivider(100e3f, 100e3f);
		val *= getState<LevelSlider>();
		setOutput(EnvOut, val);
		setLED(LevelSlider, val / 8.f);
		// FIXME: slider lights should show if env is increasing or decreasing in voltage,
		// even during State_t::FOLLOW
		setLED(RiseSlider, state == TriangleOscillator::State_t::RISING ? val / 8.f : 0);
		setLED(FallSlider, state == TriangleOscillator::State_t::FALLING ? val / 8.f : 0);
	}

	void displayOscillatorState(TriangleOscillator::State_t state)
	{
		if (state == TriangleOscillator::State_t::FALLING) {
			setOutput(Eor, 8.f);
			setLED(EorLed, 1);
		} else {
			setOutput(Eor, 0);
			setLED(EorLed, 0);
		}
	}

	void runOscillator() {
		bool isCycling = (getState<CycleButton>() == MetaModule::LatchingButton::State_t::DOWN) ^ CVToBool(getInput(CycleJack).value_or(0.0f));

		osc.setCycling(isCycling);
		if (cycleLED != isCycling){
			cycleLED = isCycling;
			setLED(CycleButton, cycleLED);
		}

		if (auto inputFollowValue = getInput(Follow); inputFollowValue) {
			osc.setTargetVoltage(*inputFollowValue);
		}

		if (auto triggerInputValue = getInput(Trigger); triggerInputValue) {
			if (triggerEdgeDetector(triggerDetector(*triggerInputValue))) {
				osc.doRetrigger();
			}
		}
		
		osc.proceed(timeStepInS);
	}

	std::pair<float,float> getRiseAndFallCV()
	{
		auto ProcessCVOffset = [](auto slider, MetaModule::Toggle3pos::State_t range) -> float
		{	
			// Slider plus resistor in parallel to tweak curve
			const float SliderImpedance = 100e3f;
			auto offset = 5.0f * VoltageDivider(slider * SliderImpedance + 17.4e3f, 0 + ParallelCircuit(100e3f, (1.0f - slider) * SliderImpedance));

			// Select one of three bias voltages
			auto BiasFromRange = [](auto range) -> float
			{
				if (range == MetaModule::Toggle3pos::State_t::UP)
				{
					return -12.0f * VoltageDivider(1e3f, 10e3f);
				}
				else if (range == MetaModule::Toggle3pos::State_t::DOWN)
				{
					return 12.0f * VoltageDivider(1e3f, 8.2e3f);
				}
				else
				{
					// middle position, and fail-safe default
					return 0.0f;
				}
			};

			auto bias = BiasFromRange(range);

			return InvertingAmpWithBias(offset, 100e3f, 100e3f, bias);
		};

		if (auto timeCVValue = getInput(TimeCv); timeCVValue) {
			// scale down cv input
			const auto scaledTimeCV = *timeCVValue * -100e3f / 137e3f;

			// apply attenuverter knobs
			rScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, getState<RiseCvAtten>() * scaledTimeCV);
			fScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, getState<FallCvAtten>() * scaledTimeCV);
		}

		// sum with static value from fader + range switch
		auto riseRange = getState<RiseSwitch>();
		auto fallRange = getState<FallSwitch>();
		riseCV = -rScaleLEDs - ProcessCVOffset(getState<RiseSlider>(), riseRange);
		fallCV = -fScaleLEDs - ProcessCVOffset(getState<FallSlider>(), fallRange);

		// TODO: LEDs only need to be updated ~60Hz instead of 48kHz
		// FIXME: Safer way to select the sub-element of a multi-color LED?
		auto rise_positive = std::max(rScaleLEDs / 10.f, 0.f);
		auto rise_negative = -std::min(rScaleLEDs / 10.f, 0.f);
		setLED(RiseCvLed, rise_negative, 0);
		setLED(RiseCvLed, rise_positive, 1);

		auto fall_positive = std::max(fScaleLEDs / 10.f, 0.f);
		auto fall_negative = -std::min(fScaleLEDs / 10.f, 0.f);
		setLED(FallCvLed, fall_negative, 0);
		setLED(FallCvLed, fall_positive, 1);

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


	void set_samplerate(float sr) override
	{
		timeStepInS = 1.0f / sr;
	}

	// TODO: Here we could also set slider LEDs once they are defined
	// TODO: Rise and Fall LEDs are actually biploar but defined as single color

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, MetaModule::ModuleInfoView2::makeView<Info>());
	// clang-format on

private:
	// temporary results that are buffered
	float cycleLED;
	float riseCV;
	float fallCV;
	float rScaleLEDs = 0.f;
	float fScaleLEDs = 0.f;

	FlipFlop triggerDetector;
	EdgeDetector triggerEdgeDetector;

private:
	SSI2162 vca;
	TriangleOscillator osc;

private:
	float timeStepInS = 1.f/48000.f;

};
