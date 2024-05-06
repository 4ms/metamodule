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
		triggerIn(1.f,2.f)
	{

	};

	void update() override {
		sideloadDrivers();
		sideloadSystemSettings();
		peg.update();
	}

	void set_samplerate(float sr) override {
	}

private:
	void sideloadDrivers()
	{
		peg.adc_dma_buffer[0] = uint16_t(std::clamp(getInput<ShapeCvIn>().value_or(0.f) / -10.f + 0.5f, 0.f, 1.f) * 4095.f);
		peg.adc_dma_buffer[1] = uint16_t(std::clamp(getInput<DivIn>().value_or(0.f) / -10.f + 0.5f, 0.f, 1.f) * 4095.f);
		peg.adc_dma_buffer[2] = uint16_t(getState<ScaleKnob>() * 4095.f);
		peg.adc_dma_buffer[3] = uint16_t(getState<OffsetKnob>() * 4095.f);
		peg.adc_dma_buffer[4] = uint16_t(getState<ShapeKnob>() * 4095.f);
		peg.adc_dma_buffer[5] = uint16_t(getState<Div_MultKnob>() * 4095.f);

		peg.digio.PingBut.sideload_set(getState<PingButton>() == MomentaryButton::State_t::PRESSED);
		peg.digio.CycleBut.sideload_set(getState<CycleButton>() == MomentaryButton::State_t::PRESSED);

		peg.digio.PingJack.sideload_set(pingIn(getInput<PingTrigIn>().value_or(0.f)));
		peg.digio.CycleJack.sideload_set(cycleIn(getInput<CycleTrigIn>().value_or(0.f)));
		peg.digio.TrigJack.sideload_set(triggerIn(getInput<TriggerIn>().value_or(0.f)));

		setOutput<EofOut>(peg.digio.EOJack.sideload_get() ? 5.0f : 0.f);

		setOutput<EnvOut>(-20.f/4095.f * float(peg.dac_vals[0]) + 10.f);
		setOutput<_5VEnvOut>( float(peg.dac_vals[1]) / 4095.f * 5.f);

		auto pwmToFloat = [](uint16_t pwm_val){return float(pwm_val)/float(std::numeric_limits<uint16_t>::max());};

		setLED<EnvOutLight>(std::array<float,3>{pwmToFloat(peg.pwm_vals[0]),pwmToFloat(peg.pwm_vals[1]),pwmToFloat(peg.pwm_vals[2])});
		setLED<_5VEnvLight>(std::array<float,3>{pwmToFloat(peg.pwm_vals[3]),pwmToFloat(peg.pwm_vals[4]),pwmToFloat(peg.pwm_vals[5])});
		setLED<CycleButton>(std::array<float,3>{pwmToFloat(peg.pwm_vals[6]),pwmToFloat(peg.pwm_vals[7]),pwmToFloat(peg.pwm_vals[8])});
		setLED<PingButton>(std::array<float,3>{pwmToFloat(peg.pwm_vals[9]),pwmToFloat(peg.pwm_vals[10]),pwmToFloat(peg.pwm_vals[11])});
		setLED<EofLight>(pwmToFloat(peg.pwm_vals[12]));
	}

	void sideloadSystemSettings()
	{
		peg.settings.limit_skew = getState<SkewLimitAltParam>();
		//TODO: this might need scaling
		peg.settings.free_running_ping = getState<FreeNRunningPingAltParam>();
		peg.settings.trigout_is_trig = getState<EofJackTypeAltParam>();
		peg.settings.trigin_function = TrigInFunctions(getState<TrigJackModeAltParam>());
		peg.settings.trigout_function = TrigOutFunctions(getState<EofJackModeAltParam>());

		peg.settings.cycle_jack_behavior = CycleJackBehaviors(getState<CycleJackModeAltParam>());
		peg.settings.shift_value = int32_t(getState<ShiftAltParam>() * 4095.f - 2048.f);
	}

private:
	PEG::MiniPEG peg;

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	FlipFlop pingIn;
	FlipFlop cycleIn;
	FlipFlop triggerIn;
};

} // namespace MetaModule
