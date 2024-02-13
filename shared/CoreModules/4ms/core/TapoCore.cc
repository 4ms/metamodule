#include "info/Tapo_info.hh"
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"

#include "tapo/multitap_delay.hh"
#include "tapo/ui.hh"

namespace MetaModule
{

class TapoCore : public SmartCoreProcessor<TapoInfo> {
	using Info = TapoInfo;
	using ThisCore = TapoCore;
	using enum Info::Elem;

public:
	TapoCore() : audioBufferFillCount(0), gateOutCounter(0), uiSampleCounter(0)
	{
		initialize(DefaultSampleRateInHz);
	}

	void initialize(uint32_t sample_rate)
	{
		currentSampleRate = sample_rate;

		delay.Init((short*)buffer.data(), buffer.size()/sizeof(short) / 2, sample_rate);

		delay.tap_modulo_observable_.set_observer([this]
		{
			onTapDetected();
		});

		ui.Init(&delay, &parameters);

		audioBufferFillCount = 0;
		std::fill(audioBufferTX.begin(), audioBufferTX.end(), ::TapoDelay::ShortFrame{0,0});
	}

	void update() override {

		if (uiSampleCounter++ % UISampleRateDivider == 0)
		{
			sideloadDrivers();

			ui.Poll();
			ui.DoEvents();
		}

		if (audioBufferFillCount == BlockSize)
		{
			ui.ReadParameters();
			delay.Poll();
			delay.Process(&parameters, audioBufferRX.data(), audioBufferTX.data());

			audioBufferFillCount = 0;
		}

		packUnpackBlockBuffers();
		audioBufferFillCount++;

		updateGateOut();
	}

	void set_samplerate(float sr) override {
		initialize(std::round(sr));
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	void packUnpackBlockBuffers()
	{
		auto monoInput = int16_t(getInput<AudioIn>().value_or(0) * 32767.0 / AudioInputFullScaleInVolts);
		audioBufferRX[audioBufferFillCount] = {monoInput, monoInput};

		setOutput<AudioOut1Out>(float(audioBufferTX[audioBufferFillCount].l) / 32768.0 * AudioOutputFullScaleInVolts);
		setOutput<AudioOut2Out>(float(audioBufferTX[audioBufferFillCount].r) / 32768.0 * AudioOutputFullScaleInVolts);
	}

	void sideloadDrivers()
	{
		using namespace ::TapoDelay;

		auto& adc      = ui.getADCDriver();
		auto& buttons  = ui.getButtonDriver();
		auto& leds     = ui.getLEDDriver();
		auto& switches = ui.getSwitchDriver();
		auto& gate     = ui.getGateInputDriver();

		adc.set(ADC_SCALE_POT,      getState<TimeKnob>());
		adc.set(ADC_FEEDBACK_POT,   getState<FeedbackKnob>());
		adc.set(ADC_MODULATION_POT, getState<ModulationKnob>());
		adc.set(ADC_DRYWET_POT, 	getState<DryWetKnob>());
		adc.set(ADC_MORPH_POT, 		getState<MorphKnob>());
		adc.set(ADC_GAIN_POT, 		getState<LevelKnob>());

		// TODO: make bipolar
		if (auto val=getInput<TimeJackIn>(); val)       adc.set(ADC_SCALE_CV, *val);
		if (auto val=getInput<FeedbackJackIn>(); val)   adc.set(ADC_FEEDBACK_CV, *val);
		if (auto val=getInput<ModulationJackIn>(); val) adc.set(ADC_MODULATION_CV, *val);
		if (auto val=getInput<DryWetJackIn>(); val)     adc.set(ADC_DRYWET_CV, *val);
		
		// TODO: make unipolar
		if (auto val=getInput<TapIn>(); val)            adc.set(ADC_TAPTRIG_CV, *val);
		if (auto val=getInput<VelocityIn>(); val)       adc.set(ADC_VEL_CV, *val);
		if (auto val=getInput<ExtClockIn>(); val)       adc.set(ADC_CLOCK_CV, *val);

		// TODO: set threshold
		if (auto val=getInput<RepeatJackIn>(); val)  gate.set(GATE_INPUT_REPEAT, *val > GateInputThresholdInVolts);

		// not force sensitive
		adc.set(ADC_FSR_CV, getState<TapSensorButton>() == MomentaryButton::State_t::PRESSED ? TapSensorPressedIntensity : 0.0);

		buttons.set(BUTTON_1,      getState<Button1Button>() == MomentaryButton::State_t::RELEASED);
		buttons.set(BUTTON_2,      getState<Button2Button>() == MomentaryButton::State_t::RELEASED);
		buttons.set(BUTTON_3,      getState<Button3Button>() == MomentaryButton::State_t::RELEASED);
		buttons.set(BUTTON_4,      getState<Button4Button>() == MomentaryButton::State_t::RELEASED);
		buttons.set(BUTTON_5,      getState<Button5Button>() == MomentaryButton::State_t::RELEASED);
		buttons.set(BUTTON_6,      getState<Button6Button>() == MomentaryButton::State_t::RELEASED);
		buttons.set(BUTTON_REPEAT, getState<RepeatButton>()  == MomentaryButton::State_t::RELEASED);
		buttons.set(BUTTON_DELETE, getState<DeleteButton>()  == MomentaryButton::State_t::RELEASED);

		auto SwitchStateMappingEdit = [](auto val) -> uint8_t
		{
			// map position VCV -> firmware
			switch(val)
			{
				case 0:  return 2; // overdub
				case 1:  return 0; // off
				case 2:  return 1; // normal
				default: return 0;
			}
		};

		auto SwitchStateMappingVelo = [](auto val) -> uint8_t
		{
			// map position VCV -> firmware
			switch(val)
			{
				case 0:  return 1; // lp
				case 1:  return 0; // amp 
				case 2:  return 2; // bp
				default: return 0;
			}
		};


		switches.set(SWITCH_EDIT, SwitchStateMappingEdit(getState<AddOffInsSwitch>()));
		switches.set(SWITCH_VELO, SwitchStateMappingVelo(getState<ResAmpLpfSwitch>()));

		setLED<Button1Button>(std::array{leds.get(LED_BUT1_R), leds.get(LED_BUT1_G), leds.get(LED_BUT1_B)});
		setLED<Button2Button>(std::array{leds.get(LED_BUT2_R), leds.get(LED_BUT2_G), leds.get(LED_BUT2_B)});
		setLED<Button3Button>(std::array{leds.get(LED_BUT3_R), leds.get(LED_BUT3_G), leds.get(LED_BUT3_B)});
		setLED<Button4Button>(std::array{leds.get(LED_BUT4_R), leds.get(LED_BUT4_G), leds.get(LED_BUT4_B)});
		setLED<Button5Button>(std::array{leds.get(LED_BUT5_R), leds.get(LED_BUT5_G), leds.get(LED_BUT5_B)});
		setLED<Button6Button>(std::array{leds.get(LED_BUT6_R), leds.get(LED_BUT6_G), leds.get(LED_BUT6_B)});

		setLED<RepeatButton>(std::array{!leds.get(LED_REPEAT_R), !leds.get(LED_REPEAT_G), !leds.get(LED_REPEAT_B)});
		setLED<DeleteButton>(std::array{!leds.get(LED_DELETE_G), !leds.get(LED_DELETE_G), !leds.get(LED_DELETE_B)});

		// TODO: make this an actual red LED
		setLED<TapLedLight>(std::array{leds.get(LED_TAP), false, false});
	}

	void onTapDetected()
	{
		pingGateOut();
		ui.PingGateLed();
	}

private:
	void updateGateOut()
	{
		if (gateOutCounter != 0 and --gateOutCounter == 0)
		{
			setOutput<GateOut>(0);
		}
	}

	void pingGateOut()
	{
		gateOutCounter = GateOnLengthInS * currentSampleRate ;
		setOutput<GateOut>(GateMaxOutputVoltage);
	}	

private:
	static constexpr float GateOnLengthInS             = 4.0e-3f;
	static constexpr float GateMaxOutputVoltage        = 8.0f;
	static constexpr uint32_t UISampleRateDivider      = 32;     // Needs to be a power of 2
	static constexpr float TapSensorPressedIntensity   = 1.0f;
	static constexpr float GateInputThresholdInVolts   = 0.5f;
	static constexpr float AudioInputFullScaleInVolts  = 11.0f;
	static constexpr float AudioOutputFullScaleInVolts = 17.0f;
	static constexpr uint32_t DefaultSampleRateInHz    = 48000;

private:
	float currentSampleRate;

private:
	static constexpr std::size_t BufferSizeInBytes = 0x02000000;
	using Buffer_t = std::array<uint8_t,BufferSizeInBytes>;

	Buffer_t buffer;

	::TapoDelay::MultitapDelay delay;
	::TapoDelay::Parameters parameters;
	::TapoDelay::Ui ui;
	
	static constexpr std::size_t BlockSize = ::TapoDelay::kBlockSize;
	std::array<::TapoDelay::ShortFrame,BlockSize> audioBufferRX;
	std::array<::TapoDelay::ShortFrame,BlockSize> audioBufferTX;
	std::size_t audioBufferFillCount;

	uint32_t gateOutCounter;

	uint32_t uiSampleCounter;
};

} // namespace MetaModule

