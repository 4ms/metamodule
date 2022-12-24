#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/EnOsc_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "enosc/ui.hh"

#include <iostream>

class EnOscCore : public CoreProcessor {
	using Info = EnOscInfo;
	using ThisCore = EnOscCore;

	enum { kBlockSize = 1 };
	enum { kUiUpdateRate = 120 };
	float sample_rate_ = 48000.f;

	unsigned ui_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
	unsigned ui_ctr = 0;

public:
	EnOscCore() = default;

	void update() override {
		// Low-priority thread:
		if (ui_ctr++ > ui_throttle) {
			ui_ctr = 0;
			enosc.Process(); //EventHandler::Process

			enosc.Update(); //LED update
		}

		enosc.Poll();
		//process SpiAdc channel, freeze_led set color
		//EventHandler::Poll: Polls each event source

		enosc.osc().Process(out_block_);
	}

	Switches::State switchstate(float val) {
		return val < 0.5f ? Switches::State::DOWN : val < 1.5f ? Switches::State::MID : Switches::State::UP;
	}

	// TODO: re-arrange AdcInput enums to match
	void set_param(int param_id, float val) override {
		switch (param_id) {
			case Info::KnobBalance:
				enosc.set_potcv(AdcInput::POT_BALANCE, val);
				break;
			case Info::KnobCross_Fm:
				enosc.set_potcv(AdcInput::POT_MOD, val);
				break;
			case Info::KnobDetune:
				enosc.set_potcv(AdcInput::POT_DETUNE, val);
				break;
			case Info::KnobPitch:
				enosc.set_potcv(AdcInput::POT_PITCH, val);
				break;
			case Info::KnobRoot:
				enosc.set_potcv(AdcInput::POT_ROOT, val);
				break;
			case Info::KnobScale:
				enosc.set_potcv(AdcInput::POT_SCALE, val);
				break;
			case Info::KnobSpread:
				enosc.set_potcv(AdcInput::POT_SPREAD, val);
				break;
			case Info::KnobTwist:
				enosc.set_potcv(AdcInput::POT_TWIST, val);
				break;
			case Info::KnobWarp:
				enosc.set_potcv(AdcInput::POT_WARP, val);
				break;
			case Info::SwitchLearn + Info::NumKnobs:
				enosc.buttons().learn_.set(val > 0.5f);
				break;
			case Info::SwitchFreeze + Info::NumKnobs:
				enosc.buttons().freeze_.set(val > 0.5f);
				break;
			case Info::SwitchScale_Switch + Info::NumKnobs:
				enosc.switches().scale_.set(switchstate(val));
				break;
			case Info::SwitchCross_Fm_Switch + Info::NumKnobs:
				enosc.switches().mod_.set(switchstate(val));
				break;
			case Info::SwitchTwist_Switch + Info::NumKnobs:
				enosc.switches().twist_.set(switchstate(val));
				break;
			case Info::SwitchWarp_Switch + Info::NumKnobs:
				enosc.switches().warp_.set(switchstate(val));
				break;
		}
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case Info::InputBalance_Jack:
				enosc.set_potcv(AdcInput::CV_BALANCE, val);
				break;
			case Info::InputCross_Fm_Jack:
				enosc.set_potcv(AdcInput::CV_MOD, val);
				break;
			case Info::InputPitch_Jack:
				enosc.set_highres_cv(SpiAdcInput::CV_PITCH, val);
				break;
			case Info::InputRoot_Jack:
				enosc.set_highres_cv(SpiAdcInput::CV_ROOT, val);
				break;
			case Info::InputScale_Jack:
				enosc.set_potcv(AdcInput::CV_SCALE, val);
				break;
			case Info::InputSpread_Jack:
				enosc.set_potcv(AdcInput::CV_SPREAD, val);
				break;
			case Info::InputTwist_Jack:
				enosc.set_potcv(AdcInput::CV_TWIST, val);
				break;
			case Info::InputWarp_Jack:
				enosc.set_potcv(AdcInput::CV_WARP, val);
				break;
			case Info::InputFreeze_Jack:
				//TODO:
				break;
			case Info::InputLearn_Jack:
				//TODO:
				break;
		}
	}

	float get_output(int output_id) const override {
		s9_23 sample = output_id == 0 ? out_block_[0].l : out_block_[0].r;
		return f::inclusive(sample).repr();
	}

	void set_samplerate(float sr) override {
		sample_rate_ = sr;
		ui_throttle = (unsigned)sample_rate_ / kUiUpdateRate;
	}

	float get_led_brightness(int led_id) const override {
		if (led_id < 0 || led_id > 5)
			return 0.f;

		if (led_id < 3) {
			auto c = enosc.get_learn_led_color();
			auto el = led_id == 0 ? c.red() : led_id == 1 ? c.green() : c.blue();
			return f::inclusive(el).repr();
		} else {
			auto c = enosc.get_freeze_led_color();
			auto el = led_id == 3 ? c.red() : led_id == 4 ? c.green() : c.blue();
			return f::inclusive(el).repr();
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

	// Parameters params_;
	// Leds leds_;
	// PolypticOscillator<1> enosc_{params_};
	// Persistent<WearLevel<FlashBlock<1, Parameters::AltParameters>>> alt_params_{&params_.alt, params_.default_alt};
	// ButtonsEventSource buttons_;
	// SwitchesEventSource switches_;
	// Control<kBlockSize> control_{params_, enosc_};
};
