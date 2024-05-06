#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/MPEG_info.hh"

#include "peg/main.hh"

#include "helpers/FlipFlop.h"

namespace MetaModule
{

class MPEGCore : public SmartCoreProcessor<MPEGInfo> {
	using Info = MPEGInfo;
	using ThisCore = MPEGCore;
	using enum Info::Elem;

public:
	MPEGCore() :
		pingIn(1.f,2.f),
		cycleIn(1.f,2.f),
		triggerIn(1.f,2.f),
		timerPhase(0),
		timerPhaseIncrement(1.0f)
	{
		// TODO: maybe calling these is not required
		sideloadDrivers();
		sideloadSystemSettings();
		peg.update_all_envelopes();
	};

	void update() override {
		sideloadDrivers();
		sideloadSystemSettings();

		timerPhase += timerPhaseIncrement;
		while (timerPhase > 1.0f)
		{
			peg.update_all_envelopes();
			timerPhase -= 1.0f;
		}

		peg.update();
	}

	void set_samplerate(float sr) override {
		timerPhaseIncrement = float(PEG::MiniPEG::kDacSampleRate) / sr;
	}

private:
	void sideloadDrivers()
	{
		auto MapOutputFunc = [](auto val) -> uint16_t
		{
			auto result = val / CVInputFullScaleInV + 0.5f;
			return uint16_t(std::clamp(result, 0.f, 1.f) * 4095.f);
		};

		peg.adc_dma_buffer[CV_SHAPE]   = MapOutputFunc(getInput<ShapeCvIn>().value_or(0.f));
		peg.adc_dma_buffer[CV_DIVMULT] = MapOutputFunc(getInput<DivIn>().value_or(0.f));

		auto MapKnobFunc = [](auto val) -> uint16_t
		{
			return uint16_t(val * 4095.f);
		};

		peg.adc_dma_buffer[POT_SCALE]   = MapKnobFunc(getState<ScaleKnob>());
		peg.adc_dma_buffer[POT_OFFSET]  = MapKnobFunc(getState<OffsetKnob>());
		peg.adc_dma_buffer[POT_SHAPE]   = MapKnobFunc(getState<ShapeKnob>());
		peg.adc_dma_buffer[POT_DIVMULT] = MapKnobFunc(getState<Div_MultKnob>());

		peg.digio.PingBut.sideload_set(getState<PingButton>() == MomentaryButton::State_t::PRESSED);
		peg.digio.CycleBut.sideload_set(getState<CycleButton>() == MomentaryButton::State_t::PRESSED);

		peg.digio.PingJack.sideload_set(pingIn(getInput<PingTrigIn>().value_or(0.f)));
		peg.digio.CycleJack.sideload_set(cycleIn(getInput<CycleTrigIn>().value_or(0.f)));
		peg.digio.TrigJack.sideload_set(triggerIn(getInput<TriggerIn>().value_or(0.f)));

		setOutput<EofOut>(peg.digio.EOJack.sideload_get() ? TriggerOutputInV : 0.f);

		auto MapDACFunc = [](auto val) -> float
		{
			return float(val) / 4095.f;
		};

		setOutput<EnvOut>(MapDACFunc(peg.dac_vals[0]) * EnvelopeOutFullScaleInV + EnvelopeOutOffsetInV);
		setOutput<_5VEnvOut>(MapDACFunc(peg.dac_vals[1]) * 5.f);

		auto PWMToFloatFunc = [](uint16_t pwm_val) -> float
		{
			return float(pwm_val) / float(4095);
		};

		setLED<EnvOutLight>(std::array<float,3>{PWMToFloatFunc(peg.pwm_vals[PWM_ENVA_R]),PWMToFloatFunc(peg.pwm_vals[PWM_ENVA_G]),PWMToFloatFunc(peg.pwm_vals[PWM_ENVA_B])});
		setLED<_5VEnvLight>(std::array<float,3>{PWMToFloatFunc(peg.pwm_vals[PWM_ENVB_R]),PWMToFloatFunc(peg.pwm_vals[PWM_ENVB_G]),PWMToFloatFunc(peg.pwm_vals[PWM_ENVB_B])});
		setLED<CycleButton>(std::array<float,3>{PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_R]),PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_G]),PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_B])});
		setLED<PingButton>(std::array<float,3>{PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_R]),PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_G]),PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_B])});
		setLED<EofLight>(PWMToFloatFunc(peg.pwm_vals[PWM_EOF_LED]));
	}

	void sideloadSystemSettings()
	{
		peg.settings.limit_skew          = getState<SkewLimitAltParam>();
		//TODO: this might need scaling
		peg.settings.free_running_ping   = getState<FreeNRunningPingAltParam>();
		peg.settings.trigout_is_trig     = getState<EofJackTypeAltParam>();
		peg.settings.trigin_function     = TrigInFunctions(getState<TrigJackModeAltParam>());
		peg.settings.trigout_function    = TrigOutFunctions(getState<EofJackModeAltParam>());
		peg.settings.cycle_jack_behavior = CycleJackBehaviors(getState<CycleJackModeAltParam>());
		peg.settings.shift_value         = int32_t(getState<ShiftAltParam>() * 4095.f - 2048.f);
	}

private:
	static constexpr float CVInputFullScaleInV     = -10.0f;
	static constexpr float TriggerOutputInV        = 5.0f;
	static constexpr float EnvelopeOutFullScaleInV = -20.0f;
	static constexpr float EnvelopeOutOffsetInV    = 10.0f;

private:
	PEG::MiniPEG peg;

private:
	FlipFlop pingIn;
	FlipFlop cycleIn;
	FlipFlop triggerIn;

private:
	float timerPhase;
	float timerPhaseIncrement;

public:
	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on
};

} // namespace MetaModule
