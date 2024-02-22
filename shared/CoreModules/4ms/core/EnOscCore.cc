#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "enosc/ui.hh"
#include "info/EnOsc_info.hh"

namespace MetaModule
{

class EnOscCore : public SmartCoreProcessor<EnOscInfo> {
	using Info = EnOscInfo;
	using ThisCore = EnOscCore;
	using enum Info::Elem;
	enum { NumKnobs = Info::KnobWarp + 1 };

	enum { kBlockSize = 64 };
	enum { kUiUpdateRate = 60 };
	enum { kUiProcessRate = 20 };

public:
	EnOscCore() = default;

	void update() override {
		// Low-priority thread
		// in while loop:
		if (ui_process_ctr++ > ui_process_throttle) {
			ui_process_ctr = 0;
			enosc.Process(); //EventHandler::Process
		}

		if (ui_update_ctr++ > ui_update_throttle) {
			ui_update_ctr = 0;
			enosc.Update(); //LED update
		}

		// SampleRate / BlockRate (6kHz for 48k)
		if (++block_ctr >= kBlockSize) {
			block_ctr = 0;
			enosc.Poll();
			enosc.osc().Process(out_block_);
		}

		sideloadDrivers();
	}

	void sideloadDrivers()
	{
		enosc.set_potcv(AdcInput::POT_BALANCE, getState<BalanceKnob>());
		enosc.set_potcv(AdcInput::POT_MOD, getState<CrossFmKnob>());
		enosc.set_potcv(AdcInput::POT_DETUNE, getState<DetuneKnob>());
		enosc.set_potcv(AdcInput::POT_PITCH, getState<PitchKnob>());
		enosc.set_potcv(AdcInput::POT_ROOT, getState<RootKnob>());
		enosc.set_potcv(AdcInput::POT_SCALE, getState<ScaleKnob>());
		enosc.set_potcv(AdcInput::POT_SPREAD, getState<SpreadKnob>());
		enosc.set_potcv(AdcInput::POT_TWIST, getState<TwistKnob>());
		enosc.set_potcv(AdcInput::POT_WARP, getState<WarpKnob>());

		// TODO: check mapping
		enosc.set_learn_button(getState<LearnButton>() == MomentaryButton::State_t::PRESSED);
		enosc.set_freeze_button(getState<FreezeButton>() == MomentaryButton::State_t::PRESSED);

		auto SwitchStateMapping = [](float val)
		{
			// DOWN=0 / MID=0.5 / UP=1.0
			return val < 0.25f ? Switches::State::DOWN : val < 0.75f ? Switches::State::MID : Switches::State::UP;
		};

		// TODO: check mapping
		enosc.switches().scale_.set(SwitchStateMapping(getState<ScaleSwitch>()));
		enosc.switches().mod_.set(  SwitchStateMapping(getState<CrossFmSwitch>()));
		enosc.switches().twist_.set(SwitchStateMapping(getState<TwistSwitch>()));
		enosc.switches().warp_.set( SwitchStateMapping(getState<WarpSwitch>()));

		enosc.set_stereo_mode(SplitMode(getState<StereosplitAltParam>()));
		enosc.set_freeze_mode(SplitMode(getState<FreezesplitAltParam>()));
		enosc.set_num_osc(getState<NumoscAltParam>());
		enosc.set_crossfade(getState<CrossfadeAltParam>());
		enosc.set_fine_tune(getState<FinetuneAltParam>());

		auto InputScalingFunc = [](float valInV)
		{
			return (((valInV / 5.0f) * -0.5f) + 0.5f);
		};

		if (auto val = getInput<BalanceJackIn>(); val)  enosc.set_potcv(AdcInput::CV_BALANCE,         InputScalingFunc(*val));
		if (auto val = getInput<CrossFmJackIn>(); val)  enosc.set_potcv(AdcInput::CV_MOD,             InputScalingFunc(*val));
		if (auto val = getInput<PitchJackIn>(); val)    enosc.set_pitchroot_cv(SpiAdcInput::CV_PITCH, InputScalingFunc(*val));
		if (auto val = getInput<RootJackIn>(); val)     enosc.set_pitchroot_cv(SpiAdcInput::CV_ROOT,  InputScalingFunc(*val));
		if (auto val = getInput<ScaleJackIn>(); val)    enosc.set_potcv(AdcInput::CV_SCALE,           InputScalingFunc(*val));
		if (auto val = getInput<SpreadJackIn>(); val)   enosc.set_potcv(AdcInput::CV_SPREAD,          InputScalingFunc(*val));
		if (auto val = getInput<TwistJackIn>(); val)    enosc.set_potcv(AdcInput::CV_TWIST,           InputScalingFunc(*val));
		if (auto val = getInput<WarpJackIn>(); val)     enosc.set_potcv(AdcInput::CV_WARP,            InputScalingFunc(*val));

		if (auto val = getInput<FreezeJackIn>(); val)   enosc.set_freeze_gate(InputScalingFunc(*val) > 0.5f);
		if (auto val = getInput<LearnJackIn>(); val)    enosc.set_learn_gate( InputScalingFunc(*val) > 0.5f);

		auto OutputScalingFunc = [](auto sample)
		{
			return  f::inclusive(sample).repr() * 4.5f; //hardware model is about 4.5Vp
		};

		setOutput<OutAOut>(OutputScalingFunc(out_block_[block_ctr].l));
		setOutput<OutBOut>(OutputScalingFunc(out_block_[block_ctr].r));

		auto MapLEDColor = [](auto val)
		{
			return std::array<float,3>{f::inclusive(val.red()).repr(), f::inclusive(val.green()).repr(), f::inclusive(val.blue()).repr()};
		};

		setLED<LearnButton>(MapLEDColor(enosc.get_learn_led_color()));
		setLED<FreezeButton>(MapLEDColor(enosc.get_freeze_led_color()));
	}

	void set_samplerate(float sr) override {
		if (sample_rate_ != sr) {
			sample_rate_ = sr;
			ui_process_throttle = (unsigned)sample_rate_ / kUiProcessRate;
			ui_update_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
		}
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	Ui<kUiUpdateRate, kBlockSize> enosc;
	Buffer<Frame, kBlockSize> out_block_;
	DynamicData dydata;
	Math math;

	float sample_rate_ = 48000.f;

	unsigned ui_process_throttle = (unsigned)sample_rate_ / kUiProcessRate;
	unsigned ui_process_ctr = ui_process_throttle;

	unsigned ui_update_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
	unsigned ui_update_ctr = ui_update_throttle;

	unsigned block_ctr = kBlockSize;
};

} // namespace MetaModule
