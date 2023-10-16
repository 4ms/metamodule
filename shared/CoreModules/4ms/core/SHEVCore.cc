#include "CoreModules/4ms/core/envvca/SSI2162.h"
#include "CoreModules/4ms/core/envvca/TriangleOscillator.h"
#include "CoreModules/4ms/core/helpers/EdgeDetector.h"
#include "CoreModules/4ms/core/helpers/circuit_elements.h"
#include "info/SHEV_info.hh"
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

constinit auto VoltageToFrequencyTableSHEV =
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

struct LogTableRange {
	static constexpr float min = 0.0f;
	static constexpr float max = 5.0f;
};

constinit auto LogTableSHEV =
	Mapping::LookupTable_t<50>::generate<LogTableRange>([](auto voltage) {
		auto log = std::log10(29.6f * voltage + 1.0f);

		return log;
	});

struct ExpTableRange {
	static constexpr float min = 0.0f;
	static constexpr float max = 5.0f;
};

constinit auto ExpTableSHEV =
	Mapping::LookupTable_t<50>::generate<ExpTableRange>([](auto voltage) {
		auto exp = (std::exp(voltage) - 1.0f) / 29.682631f;

		return exp;
	});


class SHEVCore : public SmartCoreProcessor<SHEVInfo> {
	using Info = SHEVInfo;
	using ThisCore = SHEVCore;
	using enum Info::Elem;

private:
	template <class Mapping>
	class Channel
	{
	private:
		SSI2162 vca;
		TriangleOscillator osc;

		FlipFlop triggerDetector;
		EdgeDetector triggerEdgeDetector;

	private:
		float cycleLED;
		float riseCV;
		float fallCV;
		float rScaleLEDs = 0.f;
		float fScaleLEDs = 0.f;
		float envOut;

	private:
		float timeStepInS = 1.f / 48000.f;

	private:
		SmartCoreProcessor<SHEVInfo>* parent;

	public:
		Channel(SmartCoreProcessor<SHEVInfo>* parent_)
			: triggerDetector(1.0f, 2.0f), parent(parent_){
		}

		void update(auto input) {
			auto [riseCV, fallCV] = getRiseAndFallCV();

			// Convert voltage to time without dealing with details of transistor core
			auto VoltageToTime = [](float voltage) -> float {
				auto frequency = VoltageToFrequencyTableSHEV.lookup(voltage);

				// limit to valid frequency range
				frequency = std::clamp(frequency, 1.0f / (60 * 3), 20e3f);

				// convert to period length
				auto time = 1.0f / frequency;

				return time;
			};

			osc.setRiseTimeInS(VoltageToTime(riseCV));
			osc.setFallTimeInS(VoltageToTime(fallCV));

			runOscillator();

			displayEnvelope(osc.getOutput(), osc.getSlopeState());

			if(auto vcaCV = parent->getInput<Mapping::VcaCvIn>(); vcaCV) {
				runAudioPath(*vcaCV, input);
			} else {
				runAudioPath(osc.getOutput(), input);
			}		
			
		}

		void runAudioPath(float triangleWave, auto input) {
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

			if (input) {
				auto output = vca.process(*input);
				parent->setOutput<Mapping::AudioOut>(output);
			} else {
				parent->setOutput<Mapping::AudioOut>(0.f);
			}
		}

		void displayEnvelope(float val, TriangleOscillator::SlopeState_t slopeState) {
			parent->setLED<Mapping::RiseSlider>(slopeState == TriangleOscillator::SlopeState_t::RISING ? val / 8.f : 0);
			parent->setLED<Mapping::FallSlider>(slopeState == TriangleOscillator::SlopeState_t::FALLING ? val / 8.f : 0);

			envOut = ExpTableSHEV.lookup(val);
			// envOut *= parent->getState<Mapping::LevelKnob>() * 2.0f - 1.0f;
			// envOut += parent->getState<Mapping::OffsetKnob>() * 20.0f - 10.0f;
			parent->setOutput<Mapping::EnvOut>(envOut);
			parent->setOutput<Mapping::Lin5VOut>(val);
			// setLED<Mapping::EnvLedLight>(val / 8.f);

		}

		auto getEnvOut() {
			return envOut;
		}

		void runOscillator() {
			bool isCycling =
				(parent->getState<Mapping::CycleButton>() == LatchingButton::State_t::DOWN);

			osc.setCycling(isCycling);
			if (cycleLED != isCycling) {
				cycleLED = isCycling;
				parent->setLED<Mapping::CycleButton>(cycleLED);
			}

			if (auto inputFollowValue = parent->getInput<Mapping::FollowIn>(); inputFollowValue) {
				osc.setTargetVoltage(*inputFollowValue);
			}

			if (auto triggerInputValue = parent->getInput<Mapping::TrigIn>(); triggerInputValue) {
				if (triggerEdgeDetector(triggerDetector(*triggerInputValue))) {
					osc.doRetrigger();
				}
			}

			osc.proceed(timeStepInS);
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

			if (auto timeCVValue = parent->getInput<Mapping::TimeCvIn>(); timeCVValue) {
				// scale down cv input
				const auto scaledTimeCV = *timeCVValue * -100e3f / 137e3f;

				// apply attenuverter knobs
				rScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, parent->getState<Mapping::RiseKnob>() * scaledTimeCV);
				fScaleLEDs = InvertingAmpWithBias(scaledTimeCV, 100e3f, 100e3f, parent->getState<Mapping::FallKnob>() * scaledTimeCV);
			}

			// sum with static value from fader + range switch
			auto riseRange = parent->getState<Mapping::SlowMedFastRiseSwitch>();
			auto fallRange = parent->getState<Mapping::SlowMedFastFallSwitch>();
			riseCV = -rScaleLEDs - ProcessCVOffset(parent->getState<Mapping::RiseSlider>(), riseRange);
			fallCV = -fScaleLEDs - ProcessCVOffset(parent->getState<Mapping::FallSlider>(), fallRange);

			// TODO: LEDs only need to be updated ~60Hz instead of 48kHz
			parent->setLED<Mapping::RiseLedLight>(BipolarColor_t{rScaleLEDs / 10.f});
			parent->setLED<Mapping::FallLedLight>(BipolarColor_t{fScaleLEDs / 10.f});

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

		TriangleOscillator::SlopeState_t getOscillatorSlopeState()
		{
			return osc.getSlopeState();
		}

		void set_samplerate(float sr) {
			timeStepInS = 1.0f / sr;
		}

	};

private:
	struct MappingA
	{
		const static Info::Elem AudioIn = AudioAIn;
		const static Info::Elem AudioOut = OutAOut;
		const static Info::Elem RiseSlider = RiseASlider;
		const static Info::Elem FallSlider = FallASlider;
		const static Info::Elem EnvOut = EnvAOut;
		const static Info::Elem EnvLedLight = EnvALedLight;
		const static Info::Elem LevelKnob = LevelAKnob;
		const static Info::Elem OffsetKnob = OffsetAKnob;
		const static Info::Elem CycleButton = CycleAButton;
		const static Info::Elem FollowIn = FollowAIn;
		const static Info::Elem TrigIn = TrigAIn;
		const static Info::Elem RiseKnob = RiseAKnob;
		const static Info::Elem FallKnob = FallAKnob;
		const static Info::Elem TimeCvIn = TimeCvAIn;
		const static Info::Elem SlowMedFastRiseSwitch = SlowMedFastRiseASwitch;
		const static Info::Elem SlowMedFastFallSwitch = SlowMedFastFallASwitch;
		const static Info::Elem RiseLedLight = RiseLedALight;
		const static Info::Elem FallLedLight = FallLedALight;
		const static Info::Elem VcaCvIn = VcaCvAIn;
		const static Info::Elem Lin5VOut = Lin5VAOut;
	};

	struct MappingB
	{
		const static Info::Elem AudioIn = AudioBIn;
		const static Info::Elem AudioOut = OutBOut;
		const static Info::Elem RiseSlider = RiseBSlider;
		const static Info::Elem FallSlider = FallBSlider;
		const static Info::Elem EnvOut = EnvBOut;
		const static Info::Elem EnvLedLight = EnvBLedLight;
		const static Info::Elem LevelKnob = LevelBKnob;
		const static Info::Elem OffsetKnob = OffsetBKnob;
		const static Info::Elem CycleButton = CycleBButton;
		const static Info::Elem FollowIn = FollowBIn;
		const static Info::Elem TrigIn = TrigBIn;
		const static Info::Elem RiseKnob = RiseBKnob;
		const static Info::Elem FallKnob = FallBKnob;
		const static Info::Elem TimeCvIn = TimeCvBIn;
		const static Info::Elem SlowMedFastRiseSwitch = SlowMedFastRiseBSwitch;
		const static Info::Elem SlowMedFastFallSwitch = SlowMedFastFallBSwitch;
		const static Info::Elem RiseLedLight = RiseLedBLight;
		const static Info::Elem FallLedLight = FallLedBLight;
		const static Info::Elem VcaCvIn = VcaCvBIn;
		const static Info::Elem Lin5VOut = Lin5VBOut;
	};

	Channel<MappingA> channelA;
	Channel<MappingB> channelB;

friend Channel<MappingA>;
friend Channel<MappingB>;

public:
	SHEVCore()
		: channelA(this), channelB(this){
		
	}

	void update() override {

		auto inputA = getInput<MappingA::AudioIn>();
		channelA.update(inputA);
		
		if(auto inputB = getInput<MappingB::AudioIn>(); inputB) {
			channelB.update(inputB);
		} else {
			channelB.update(inputA);
		}
		
		displayOscillatorState();

		setOutput<OrOut>(std::max(channelA.getEnvOut(), channelB.getEnvOut()));
	}

	void displayOscillatorState()
	{
		if(auto slopeStateA = channelA.getOscillatorSlopeState(); slopeStateA == TriangleOscillator::SlopeState_t::FALLING) {
			setOutput<EorAOut>(8.f);
			// setLED<EorLedLight>(true);
		} else {
			setOutput<EorAOut>(0);
			// setLED<EorLedLight>(false);
		}

		if(auto slopeStateB = channelB.getOscillatorSlopeState(); slopeStateB == TriangleOscillator::SlopeState_t::RISING) {
			setOutput<EofBOut>(8.f);
			// setLED<EofLedLight>(true);
		} else {
			setOutput<EofBOut>(0);
			// setLED<EofLedLight>(false);
		}
	}

	void set_samplerate(float sr) override {
		channelA.set_samplerate(sr);
		channelB.set_samplerate(sr);
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	

};

} // namespace MetaModule
