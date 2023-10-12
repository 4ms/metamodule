#include "CoreModules/4ms/core/envvca/SSI2162.h"
#include "CoreModules/4ms/core/envvca/TriangleOscillator.h"
#include "CoreModules/4ms/core/helpers/EdgeDetector.h"
#include "CoreModules/4ms/core/helpers/circuit_elements.h"
#include "info/DEV_info.hh"
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "gcem/include/gcem.hpp"
#include "helpers/FlipFlop.h"
#include "helpers/mapping.h"

namespace MetaModule
{

inline auto CVToBool = [](float val) -> bool {
	return val >= 0.5f;
};

struct VoltageToFreqTableRange {
	static constexpr float min = -0.2f;
	static constexpr float max = 0.5f;
};

constinit auto VoltageToFrequencyTableDEV =
	Mapping::LookupTable_t<50>::generate<VoltageToFreqTableRange>([](auto voltage) {
		// voltage offset to not calculate with negative values during fitting
		// once the table is created, we can lookup negative voltages values just fine
		constexpr double VoltageOffset = 0.1;

		// two points in the V->f curve
		// taken from voltages from the model at specific switch positions and expected frequencies from the manual
		constexpr double V_1 = 0.31527 + VoltageOffset;
		constexpr double f_1 = 1.0 / (5 * 60) / 2;
		constexpr double V_2 = -0.055331 + VoltageOffset;
		constexpr double f_2 = 800 * 2;

		// helper constant to limit ranges of intermediate values and improve precision
		constexpr double ArgScalingFactor = 100.0;

		// This does not work in clang because math functions are not constexpr
		// It doesn't work with gcem either because of numeric problems
		// constexpr double arg = std::log2(f_1 / f_2) / (V_1 - V_2);
		// constexpr double b = std::pow(2.0f, arg / ArgScalingFactor);
		// constexpr double a = f_1 / std::pow(std::pow(2.0, arg), V_1);

		// So we just hardcode the factors that GCC produces for now
		constexpr double a = 8.4172569220933146e+3;
		constexpr double b = 6.8957132479261685e-1;

		auto coreFunc = [](double voltage) -> float {
			return float(gcem::pow(b, voltage * ArgScalingFactor) * a);
		};

		// make sure the fitting is correct
		static_assert(gcem::abs(coreFunc(V_1) - f_1) / f_1 < 1e-2f);
		static_assert(gcem::abs(coreFunc(V_2) - f_2) / f_2 < 1e-2f);

		// interpolate
		auto frequency = coreFunc((double)voltage + VoltageOffset);

		return frequency;
	});

class DEVCore : public SmartCoreProcessor<DEVInfo> {
	using Info = DEVInfo;
	using ThisCore = DEVCore;
	using enum Info::Elem;

public:
	DEVCore() 
		: triggerDetectorA(1.0f, 2.0f), triggerDetectorB(1.0f, 2.0f) {

	}

	void update() override {
		auto [riseCV, fallCV] = getRiseAndFallCV();

		// Convert voltage to time without dealing with details of transistor core
		auto VoltageToTime = [](float voltage) -> float {
			auto frequency = VoltageToFrequencyTableDEV.lookup(voltage);

			// limit to valid frequency range
			frequency = std::clamp(frequency, 1.0f / (60 * 3), 20e3f);

			// convert to period length
			auto time = 1.0f / frequency;

			return time;
		};

		oscA.setRiseTimeInS(VoltageToTime(riseCV));
		oscA.setFallTimeInS(VoltageToTime(fallCV));

		runOscillator();

		displayOscillatorState(oscA.getSlopeState());

		displayEnvelope(oscA.getOutput(), oscA.getSlopeState());
		runAudioPath(oscA.getOutput());
	}

	void runAudioPath(float triangleWave) {
		triangleWave = InvertingAmpWithBias(triangleWave, 100e3f, 100e3f, 1.94f);

		constexpr float VCAInputImpendance = 5e3f;
		triangleWave = triangleWave * VoltageDivider(VCAInputImpendance, 2.7e3f);

		// This value influences the maximum gain a lot
		// Tweaked manually to achieve approximately max 0dB
		constexpr float SchottkyForwardVoltage = 0.22f;
		constexpr float MaxGainInV = 5.0f + SchottkyForwardVoltage;
		constexpr float MinGainInV = VoltageDivider(47e3f, 1e6f) * 5.0f - SchottkyForwardVoltage;

		triangleWave = std::clamp(triangleWave, MinGainInV, MaxGainInV);

		vcaA.setScaling(triangleWave);

		// Ignoring input impedance and inverting 400kHz lowpass

		if (auto input = getInput<AudioAIn>(); input) {
			auto output = vcaA.process(*input);
			setOutput<AudioAOut>(output);
		} else {
			setOutput<AudioAOut>(0.f);
		}

		// Ignoring output impedance and inverting 400kHz lowpass
	}

	void displayEnvelope(float val, TriangleOscillator::SlopeState_t slopeState) {
		setLED<RiseASlider>(slopeState == TriangleOscillator::SlopeState_t::RISING ? val / 8.f : 0);
		setLED<FallASlider>(slopeState == TriangleOscillator::SlopeState_t::FALLING ? val / 8.f : 0);

		val = val / VoltageDivider(100e3f, 100e3f);
		val *= getState<LevelAKnob>() * 2.0f - 1.0f;
		val += getState<OffsetAKnob>() * 20.0f - 10.0f;
		setOutput<EnvAOut>(val);
		setLED<EnvALedLight>(val / 8.f);
	}

	void displayOscillatorState(TriangleOscillator::SlopeState_t slopeState) {
		if (slopeState == TriangleOscillator::SlopeState_t::FALLING) {
			setOutput<EorAOut>(8.f);
			// setLED<EorLedLight>(true);
		} else {
			setOutput<EorAOut>(0);
			// setLED<EorLedLight>(false);
		}
	}

	void runOscillator() {
		bool isCycling =
			(getState<CycleAButton>() == LatchingButton::State_t::DOWN) ^ CVToBool(getInput<CycleTrig_In>().value_or(0.0f));

		oscA.setCycling(isCycling);
		if (cycleLEDA != isCycling) {
			cycleLEDA = isCycling;
			setLED<CycleAButton>(cycleLEDA);
		}

		if (auto inputFollowValue = getInput<FollowAIn>(); inputFollowValue) {
			oscA.setTargetVoltage(*inputFollowValue);
		}

		if (auto triggerInputValue = getInput<TrigAIn>(); triggerInputValue) {
			if (triggerEdgeDetectorA(triggerDetectorA(*triggerInputValue))) {
				oscA.doRetrigger();
			}
		}

		oscA.proceed(timeStepInS);
	}

	std::pair<float, float> getRiseAndFallCV() {
		auto ProcessCVOffset = [](auto slider, Toggle3pos::State_t range) -> float {
			// Slider plus resistor in parallel to tweak curve
			const float SliderImpedance = 100e3f;
			auto offset = 5.0f * VoltageDivider(slider * SliderImpedance + 17.4e3f,
												0 + ParallelCircuit(100e3f, (1.0f - slider) * SliderImpedance));

			// Select one of three bias voltages
			auto BiasFromRange = [](auto range) -> float {
				if (range == Toggle3pos::State_t::UP) {
					return -12.0f * VoltageDivider(1e3f, 10e3f);
				} else if (range == Toggle3pos::State_t::DOWN) {
					return 12.0f * VoltageDivider(1e3f, 8.2e3f);
				} else {
					// middle position, and fail-safe default
					return 0.0f;
				}
			};

			auto bias = BiasFromRange(range);

			return InvertingAmpWithBias(offset, 100e3f, 100e3f, bias);
		};

		if (auto timeCVValue = getInput<TimeCvAIn>(); timeCVValue) {
			// scale down cv input
			const auto scaledTimeCV = *timeCVValue * -100e3f / 137e3f;

			// apply attenuverter knobs
			rScaleLEDsA = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, getState<RiseAKnob>() * scaledTimeCV);
			fScaleLEDsA = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, getState<FallBKnob>() * scaledTimeCV);
		}

		// sum with static value from fader + range switch
		auto riseRange = getState<SlowMedFastRiseASwitch>();
		auto fallRange = getState<SlowMedFastFallASwitch>();
		riseCVA = -rScaleLEDsA - ProcessCVOffset(getState<RiseASlider>(), riseRange);
		fallCVA = -fScaleLEDsA - ProcessCVOffset(getState<FallASlider>(), fallRange);

		// TODO: LEDs only need to be updated ~60Hz instead of 48kHz
		setLED<RiseLedALight>(BipolarColor_t{rScaleLEDsA / 10.f});
		setLED<FallLedALight>(BipolarColor_t{fScaleLEDsA / 10.f});

		// TODO: low pass filter

		// apply rise time limit and scale down
		constexpr float DiodeDropInV = 1.0f;
		const float ClippingVoltage = 5.0f * VoltageDivider(100e3f, 2e3f) + DiodeDropInV;
		riseCVA = riseCVA * VoltageDivider(2.2e3f + 33e3f, 16.9e3f);
		riseCVA = std::min(riseCVA, ClippingVoltage);
		riseCVA = riseCVA * VoltageDivider(2.2e3f, 33e3f);

		// scale down falling CV without additional limiting
		fallCVA = fallCVA * VoltageDivider(2.2e3f, 10e3f + 40.2e3f);

		return {riseCVA, fallCVA};
	}

	void set_samplerate(float sr) override {
		timeStepInS = 1.0f / sr;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	// temporary results that are buffered
	float cycleLEDA;
	float cycleLEDB;
	float riseCVA;
	float riseCVB;
	float fallCVA;
	float fallCVB;
	float rScaleLEDsA = 0.f;
	float fScaleLEDsA = 0.f;
	float rScaleLEDsB = 0.f;
	float fScaleLEDsB = 0.f;

	FlipFlop triggerDetectorA;
	EdgeDetector triggerEdgeDetectorA;

	FlipFlop triggerDetectorB;
	EdgeDetector triggerEdgeDetectorB;

private:
	SSI2162 vcaA;
	TriangleOscillator oscA;

	SSI2162 vcaB;
	TriangleOscillator oscB;

private:
	float timeStepInS = 1.f / 48000.f;
};

} // namespace MetaModule
